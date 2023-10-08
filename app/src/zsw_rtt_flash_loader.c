#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <SEGGER_RTT.h>

LOG_MODULE_REGISTER(zsw_rtt_flash_loader);

#define SPI_FLASH_SECTOR_SIZE        4096

#define RTT_RECIVE_BUFFER_SIZE SPI_FLASH_SECTOR_SIZE

#define TRANSFER_TIMEOUT_MS		5000

#define START_LOAD_SEQUENCE "LOADER_START"
#define STOP_LOAD_SEQUENCE 	"LOADER_END"
#define DUMP_FLASH_SEQUENCE "DUMP_START"
#define READ_DONE_SEQUENCE	"DUMP_END"

#define RTT_CHANNEL_NAME	"FlashLoaderChannel"

struct flash_partition_search_user_data {
    int     found_part_id;
    char*   search_label_name;
};

static void rtt_load_flash_thread(void *, void *, void *);
static void rtt_dump_flash_thread(void *, void *, void *);

K_THREAD_STACK_DEFINE(rtt_work_thread_stack, 8192);
static struct k_thread rtt_work_thread;

static uint8_t data_buf[SPI_FLASH_SECTOR_SIZE];
static uint8_t up_buffer[SPI_FLASH_SECTOR_SIZE + 1];
static uint8_t down_buffer[SPI_FLASH_SECTOR_SIZE + 1];

static const struct flash_area *flash_area;

static int loader_write_flash(int partition_id, int buf_idx, uint8_t* buf, int len)
{
    int rc;
    if (len != SPI_FLASH_SECTOR_SIZE) {
        LOG_ERR("Buflen must be same size as SPI_FLASH_SECTOR_SIZE: %d", SPI_FLASH_SECTOR_SIZE);
        return -EINVAL;
    }

#ifdef CONFIG_ERASE_PROGRESSIVELY
    rc = flash_area_erase(flash_area, buf_idx * SPI_FLASH_SECTOR_SIZE, SPI_FLASH_SECTOR_SIZE);
    if (rc != 0) {
        printk("Flash erase failed! %d", rc);
        return rc;
    }
#endif

    rc = flash_area_write(flash_area, buf_idx * SPI_FLASH_SECTOR_SIZE, buf, len);
    if (rc != 0) {
        printk("Flash write failed! %d\n", rc);
        return rc;
    }	

    return 0;
}

static int loader_read_flash(int partition_id, int buf_idx, uint8_t* buf, int len)
{
    int rc;

    rc = flash_area_read(flash_area, buf_idx * SPI_FLASH_SECTOR_SIZE, buf, len);
    if (rc != 0) {
        printk("Flash read failed! %d\n", rc);
        return rc;
    }

    return 0;
}

static void flash_part_iter_cb(const struct flash_area *fa, void *user_data)
{
	struct flash_partition_search_user_data* search_data = (struct flash_partition_search_user_data*)user_data;
	const char *fa_label = flash_area_label(fa);
	if (fa_label == NULL) {
		return;
	}
    if (strcmp(search_data->search_label_name, fa_label) == 0) {
        search_data->found_part_id = fa->fa_id;
    }
}

static int find_partition_id_from_label(char* label)
{
    struct flash_partition_search_user_data search_data = {
        .search_label_name = label,
        .found_part_id = -ENOENT
    };

    flash_area_foreach(flash_part_iter_cb, &search_data);

    if (search_data.found_part_id >= 0) {
        LOG_DBG("Found target partition id: %d", search_data.found_part_id);
    } else {
        LOG_ERR("Partition label not found: %s", label + 1);
    }

    return search_data.found_part_id;
}

static bool check_start_sequence(uint8_t* buf, uint32_t len, int* partition_id)
{
    char* partition_label;
    if (strncmp(buf, START_LOAD_SEQUENCE, strlen(START_LOAD_SEQUENCE)) == 0) {
        partition_label = strchr(buf, ':');
        if (partition_label) {
            *partition_id = find_partition_id_from_label(partition_label + 1);
            return true;
        } else {
            LOG_WRN("No partition label found");
        }
    }

    return false;
}

static bool check_end_sequence(uint8_t* buf, uint32_t len)
{
    if (memcmp(buf, STOP_LOAD_SEQUENCE, strlen(STOP_LOAD_SEQUENCE)) == 0) {
        printk("End sequence received\n");
        return true;
    }

    return false;
}

static bool check_read_sequence(uint8_t* buf, uint32_t len, int* partition_id)
{
    char* partition_label;
    if (memcmp(buf, DUMP_FLASH_SEQUENCE, strlen(DUMP_FLASH_SEQUENCE)) == 0) {
        partition_label = strchr(buf, ':');
        if (partition_label) {
            *partition_id = find_partition_id_from_label(partition_label + 1);
            return true;
        } else {
            LOG_WRN("No partition label found");
        }
    }

    return false;
}

static void rtt_load_flash_thread(void * partition_id_param, void *, void *)
{
    int ret;
    int len;
    int block_index = 0;
    int buffer_index = 0;
    int bytes_flashed = 0;
    uint8_t partition_id = (uint8_t)((uint32_t)partition_id_param);
    uint32_t len_to_read;
    uint32_t last_activity_ms = k_uptime_get_32();

    ret = flash_area_open(partition_id, &flash_area);

    if (ret != 0) {
        LOG_ERR("FAIL: unable to find flash area %d: %d\n", (int)partition_id, ret);
        return;
    }

#ifndef CONFIG_ERASE_PROGRESSIVELY
    ret = flash_area_erase(flash_area, 0, flash_area->fa_size);
    LOG_WRN("Erasing flash area ... %d", ret);
#endif

    while (1) {
        len_to_read = sizeof(data_buf) - buffer_index;
        len = SEGGER_RTT_Read(CONFIG_RTT_TRANSFER_CHANNEL, data_buf, len_to_read);

        if (len <= 0) {
            if (k_uptime_get_32() - last_activity_ms > TRANSFER_TIMEOUT_MS) {
                printk("RTT Transfer timeout. Aborting.\n");
                break;
            }
            k_msleep(100);
            continue;
        }

        last_activity_ms = k_uptime_get_32();
        if (check_end_sequence(data_buf, len)) {
            printk("RTT Transfer done: %d bytes flashed\n", bytes_flashed);
            break;
        } else if (len == len_to_read) {
            ret = loader_write_flash((int)partition_id, block_index, data_buf, sizeof(data_buf));
            if (ret != 0) {
                printk("loader_write_flash failed: %dn", ret);
                break;
            }
            block_index++;
            buffer_index = 0;
            bytes_flashed += sizeof(data_buf);
            if (block_index % 10 == 0) {
                printk("RTT: Received %d (%d)\n", bytes_flashed, block_index);
            }
        } else {
            buffer_index += len;
            if (buffer_index > sizeof(data_buf)) {
                __ASSERT(false, "Something wrong got size %d", buffer_index);
            }
        }
    }

    flash_area_close(flash_area);
}

static void rtt_dump_flash_thread(void * partition_id_param, void *, void *)
{
    int ret;
    int len;
    int buffer_index = 0;
    int bytes_sent = 0;
    uint8_t partition_id = (uint8_t)((uint32_t)partition_id_param);
    uint32_t len_to_send;
    uint32_t last_activity_ms = k_uptime_get_32();

    ret = flash_area_open(partition_id, &flash_area);

    if (ret != 0) {
        LOG_ERR("FAIL: unable to find flash area %d: %d\n", (int)partition_id, ret);
        return;
    }

#ifndef CONFIG_ERASE_PROGRESSIVELY
    ret = flash_area_erase(flash_area, 0, flash_area->fa_size);
    LOG_WRN("Erasing flash area ... %d", ret);
#endif

    while (buffer_index < flash_area->fa_size / SPI_FLASH_SECTOR_SIZE) {
        ret = loader_read_flash((int)partition_id, buffer_index, data_buf, sizeof(data_buf));
        if (ret != 0) {
            printk("loader_read_flash failed: %dn", ret);
            break;
        }
        len_to_send = sizeof(data_buf);
        while (len_to_send > 0) {
            len = SEGGER_RTT_Write(CONFIG_RTT_TRANSFER_CHANNEL, data_buf, sizeof(data_buf));
            bytes_sent += len;
            len_to_send -= len;
            if (len > 0) {
                last_activity_ms = k_uptime_get_32();
            } else {
                if (k_uptime_get_32() - last_activity_ms > TRANSFER_TIMEOUT_MS) {
                    printk("RTT Transfer timeout. Aborting.\n");
                }
            }
            if (buffer_index % 10 == 0) {
                printk("RTT: Sent %d (%d)\n", bytes_sent, buffer_index);
            }
            k_msleep(1);
        }
        buffer_index++;
    }
    printk("Done sending %d bytes\n", bytes_sent);

    // Sleep a bit so python code can read the last bytes
    k_msleep(2000);
    SEGGER_RTT_Write(CONFIG_RTT_TRANSFER_CHANNEL, READ_DONE_SEQUENCE, strlen(READ_DONE_SEQUENCE));
    k_msleep(2000);

    flash_area_close(flash_area);
}

int zsw_rtt_flash_loader_start(void)
{
    int partition_id;

    SEGGER_RTT_ConfigUpBuffer(CONFIG_RTT_TRANSFER_CHANNEL, RTT_CHANNEL_NAME,
                    up_buffer, sizeof(up_buffer),
                    SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
    SEGGER_RTT_ConfigDownBuffer(CONFIG_RTT_TRANSFER_CHANNEL, RTT_CHANNEL_NAME,
                    down_buffer, sizeof(down_buffer),
                    SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    while (1) {
        int len = SEGGER_RTT_Read(CONFIG_RTT_TRANSFER_CHANNEL, data_buf, sizeof(data_buf));

        if (len <= 0) {
            k_msleep(100);
            //SEGGER_RTT_Write(CONFIG_RTT_TRANSFER_CHANNEL, "READY", strlen("READY"));
            continue;
        }

        if (check_start_sequence(data_buf, len, &partition_id)) {
            printk("Load sequence received: %s partition ID: %d\n", data_buf, partition_id);
            k_tid_t tid = k_thread_create(&rtt_work_thread, rtt_work_thread_stack, K_KERNEL_STACK_SIZEOF(rtt_work_thread_stack),
                      rtt_load_flash_thread, (void*)partition_id, NULL, NULL, CONFIG_NUM_COOP_PRIORITIES-2, 0, K_NO_WAIT);
            k_thread_join(tid, K_FOREVER);
            printk("Load thread done\n");
        } else if (check_read_sequence(data_buf, len, &partition_id)) {
            printk("Read sequence received: %s partition ID: %d\n", data_buf, partition_id);
            k_tid_t tid = k_thread_create(&rtt_work_thread, rtt_work_thread_stack, K_KERNEL_STACK_SIZEOF(rtt_work_thread_stack),
                      rtt_dump_flash_thread, (void*)partition_id, NULL, NULL, CONFIG_NUM_COOP_PRIORITIES-2, 0, K_NO_WAIT);
            k_thread_join(tid, K_FOREVER);
            printk("Read thread done\n");
        } else {
            printk("Unknown sequence received\n");
        }
    }

    return 0;
}
