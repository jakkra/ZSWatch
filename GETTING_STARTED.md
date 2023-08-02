# Getting Started
- [Setting up the environment](#setting-up-the-environment)
- [Compiling](#compiling)
- [Running and developing the ZSWatch SW without the actual ZSWatch HW](#running-and-developing-the-zswatch-sw-without-the-actual-zswatch-hw)
  * [Native Posix](#native-posix)
  * [nRF5340 dev kit](#nrf5340-dev-kit)
- [Getting Gadgetbridge setup](#getting-gadgetbridge-setup)
  * [Pairing](#pairing)
  * [Weather](#weather)

If you have received or built a ZSWatch there are a few things you need to know before starting.

1. On the dock v1 Rev 1 the watch connector is rotated 180 degrees. Meaning you need to connect the watch 180 degree rotated (see image below).
2. Be careful when connecting the watch to the dock.
    - Check orientation.
    - Check that the pins are not "offsetted".
<div align="center">

<img src=".github/dock_connect.jpg" width="50%"/>
<br>
<sub>
  Note the usage for the dock v1 Rev1.
</sub>
</div>


## Setting up the environment
Download and install the tools needed for flashing.
- [SEGGER J-Link](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack)
- [nRF Commond line tools](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download)

Two options, either set up toolchain and everything by following [Zephyr Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) or you can use the in my opinion easier approch by using the [Nordic Toolchain manager](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/getting_started/assistant.html). 
Everything works with both Zephyr and with nRF Connect (Nordic Semi. Zephyr fork). If you are new to Zephyr I suggest installing using Nordic Toolchain manager together with the nRF Connect VSCode plugin as I think that is a bit easier.

*Tested with both*
- Zephyr 3.4.0
- nRF Connect SDK 2.4.0

## Compiling

After setting up the environment using one of the two above options you can compile the application from either command line or within VSCode.

Building [with command line](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/getting_started/programming.html#building-on-the-command-line):

`west build --board zswatch_nrf5340_cpuapp@1 -- -DOVERLAY_CONFIG="{debug/release}.conf`

Compiling [from VSCode nRF Connect plugin](https://nrfconnect.github.io/vscode-nrf-connect/get_started/build_app_ncs.html):
- Press "Add folder as Application". 
- Choose `zswatch_nrf5340_cpuapp` as the board and nRF Connect SDK 2.4.0.
- Set revision to 1 or 2 depending on what version of ZSWatch is used. If your watch is built before Aug. 1 2023 it's revision 1. Revision 2 adds external flash.
- Press "Add fragment", here choose either debug (for develping) or release (for daily use).
- Press Create Application

__NOTE (Zephyr only)__
<br>
If you are building with Zephyr you need in addition manually compile and flash the `zephyr/samples/bluetooth/hci_rpmsg` sample and flash that to the NET core. With nRF Connect this is done automatically thanks to the `child_image/hci_rpmsg.conf`. For convenience I have also uploaded a pre-compiled [hex image for NET CPU](app/child_image/GENERATED_CP_NETWORK_merged_domains.hex) if you don't want to recompile it yourself. Flash it using following:
<br>
`nrfjprog -f NRF53 --coprocessor CP_NETWORK --program app/child_image/GENERATED_CP_NETWORK_merged_domains.hex --chiperase`

To build the NET core image:
Command line: 
- Navigate to `zephyr/samples/bluetooth/hci_rpmsg`
- Fill in "this_folder" in this command and run it `west build --board zswatch_nrf5340_cpunet@1 -- -DBOARD_ROOT=this_folder/app  -DOVERLAY_CONFIG=nrf5340_cpunet_df-bt_ll_sw_split.conf`
- `west flash`
- This only needs to be done once, unless you do a full erase or recover of the nRF5340, which you typically don't do.

VScode:
- Add `zephyr/samples/bluetooth/hci_rpmsg` as an application.
- Select `zswatch_nrf5340_cpunet` as board (VSCode should pick this one up automatically if you added the ZSWatch application earlier).
- Set revision to 1 or 2 depending on what version of ZSWatch is used. If your watch is built before Aug. 1 2023 it's revision 1. Revision 2 adds external flash.
- Press `Add Fragment` and select the `nrf5340_cpunet_df-bt_ll_sw_split.conf`
- Done, press `Build Configuration`.

## Running and developing the ZSWatch SW without the actual ZSWatch HW
Two options, either using a nRF5340 dev kit or running on Linux using Zephyr native posix port.
### Native Posix
- Follow the steps here [https://docs.zephyrproject.org/latest/connectivity/bluetooth/bluetooth-tools.html#using-a-zephyr-based-ble-controller](https://docs.zephyrproject.org/latest/connectivity/bluetooth/bluetooth-tools.html#using-a-zephyr-based-ble-controller) to get the BLE Controller up and running. Verify it's working by following: [https://docs.zephyrproject.org/latest/connectivity/bluetooth/bluetooth-tools.html#using-zephyr-based-controllers-with-bluez](https://docs.zephyrproject.org/latest/connectivity/bluetooth/bluetooth-tools.html#using-zephyr-based-controllers-with-bluez), use this also to find the number assigned to your HCI dongle which is input later as the `--bt-dev=hciX`
- Compile the zephyr/samples/bluetooth/hci_usb with following additions to prj.conf:
```
CONFIG_BT_EXT_ADV=y
CONFIG_BT_PER_ADV=y
CONFIG_BT_PER_ADV_SYNC=y
CONFIG_BT_PER_ADV_SYNC_MAX=2
```
- Follow the steps [https://docs.zephyrproject.org/latest/boards/posix/native_posix/doc/index.html#peripherals](https://docs.zephyrproject.org/latest/boards/posix/native_posix/doc/index.html#peripherals) for Display Driver.

- Finally to build and run do following from the `app` folder:
```
west build -b native_posix
sudo btmgmt --index <index_x_from_above> power off
sudo ./build/zephyr/zephyr.exe --bt-dev=hciX
```
Or if you want to be able to debug:
```
sudo gdb -ex=r --args build/zephyr/zephyr.exe --bt-dev=hciX
```

If you want to scale up the SDL window (4x) apply the patch in `app/zephyr_patches/sdl_upscale.patch`

https://github.com/jakkra/ZSWatch/assets/4318648/3b3e4831-a217-45a9-8b90-7b48cea7647e

### nRF5340 dev kit
This is possible, what you need is a [nRF5340-DK](https://www.digikey.se/en/products/detail/nordic-semiconductor-asa/NRF5340-DK/13544603) (or EVK-NORA-B1) and a breakout of the screen I use [https://www.waveshare.com/1.28inch-touch-lcd.htm](https://www.waveshare.com/1.28inch-touch-lcd.htm).
<br>
You may also add _any_ of the sensors on the ZSWatch, Sparkfun for example have them all:<br>
[BMI270](https://www.sparkfun.com/products/17353)
[BME688](https://www.sparkfun.com/products/19096)
[BMP581](https://www.sparkfun.com/products/20170)
[MAX30101](https://www.sparkfun.com/products/16474)
[LIS2MDL](https://www.sparkfun.com/products/19851)

When using the nRF5340-DK all you need to do is to replace `zswatch_nrf5340_cpuapp` with `nrf5340dk_nrf5340_cpuapp` as the board in the compiling instructions above. You may also need to tweak the pin assignment in [app/boards/nrf5340dk_nrf5340_cpuapp.overlay](app/boards/nrf5340dk_nrf5340_cpuapp.overlay) for your needs.

## Getting Gadgetbridge setup
Install the Android app [GadgetBridge](https://codeberg.org/Freeyourgadget) or [from Play Store here](https://play.google.com/store/apps/details?id=com.espruino.gadgetbridge.banglejs&hl=en_US)
- In Gadgetbridge press plus button to add ZSWatch
- It will scan and you should see a device called ZSWatch, long press it.
- Select in the dropdown Bangle.js as the device.

### Pairing
To get communication with your phone working you need to pair ZSWatch.
- In ZSWatch go to Settings -> Bluetooth -> Enable pairing.
- Now go **reconnect** to the watch from Gadgetbridge app.
- You should now be paired and a popup should be seen on ZSWatch.

### Weather
To get weather working follow the instructions [here](https://codeberg.org/Freeyourgadget/Gadgetbridge/wiki/Weather).