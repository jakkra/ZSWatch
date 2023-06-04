from zswatch_ble_control import zsw_send_nus_commands, zsw_list_uart_devices
import argparse, sys
from enum import Enum


class Buttons(Enum):
    TOP_RIGHT = 0
    TOP_LEFT = 1
    BOTTOM_RIGHT = 2
    BOTTOM_LEFT = 3


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Tool to send commands to ZSWatch with the NUS Service. If no address specified it will look for all BLE devices with the NUS service."
    )

    parser.add_argument(
        "--address",
        dest="address",
        required=False,
        help="Mac of ZSWatch to send command to",
    )

    parser.add_argument(
        "--timeout",
        dest="timeout",
        default=5,
        required=False,
        help="Scan timeout for ZSWatch discovery",
    )

    args = parser.parse_args()

    commands = [
        ("Control:{}".format(int(Buttons.TOP_RIGHT.value)), 0),  # Wakeup
        ("Control:{}".format(Buttons.TOP_LEFT.value), 1),
        ("Control:{}".format(Buttons.BOTTOM_LEFT.value), 0.5),
        ("Control:{}".format(Buttons.BOTTOM_LEFT.value), 0.5),
        ("Control:{}".format(Buttons.BOTTOM_LEFT.value), 0.5),
        ("Control:{}".format(Buttons.BOTTOM_LEFT.value), 0.5),
        ("Control:{}".format(Buttons.BOTTOM_LEFT.value), 0.5),
        ("Control:{}".format(Buttons.TOP_RIGHT.value), 0.5),
        ("Control:{}".format(Buttons.BOTTOM_RIGHT.value), 2),
        ("Control:{}".format(Buttons.BOTTOM_RIGHT.value), 1),
    ]

    if args.address == None:
        devices = zsw_list_uart_devices(timeout=int(args.timeout))
        print("Found {0} ZSWatch:es".format(len(devices)))
        print("Note, not all of these might be ZSWatch:es, TODO")
        print(devices)
        if len(devices) > 0:
            zsw_send_nus_commands(list(devices.values()), commands)
    else:
        zsw_send_nus_commands(args.address, commands)

    print("All commands sent!")
