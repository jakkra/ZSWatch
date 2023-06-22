<div align="center">
  <h1>ZSWatch</h1>

[![License](https://img.shields.io/badge/License-GPL%203.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![discord](https://img.shields.io/badge/chat-discord-blue?logo=discord&logoColor=white)](https://discord.gg/8XfNBmDfbY)

<img src=".github/in_use.jpg"/>
<sub>
  ZSWatch v2
</sub>
</div>
<br/>
<br/>


Smartwatch built from scratch, both hardware and software. Built on the [Zephyr™ Project](https://www.zephyrproject.org/) RTOS, hence the name **ZSWatch** - *Zephyr Smartwatch*.
<br/>

<kbd><img title="Overview" src=".github/many_in_row.jpg"/></kbd><br/>

<kbd><img title="Overview" src=".github/v2_overview.jpg"/></kbd><br/>

**Synced remote control over BLE**

[https://user-images.githubusercontent.com/64562059/234390129-321d4f35-cb4b-45e8-89d9-20ae292f34fc.mp4](https://github.com/jakkra/ZSWatch/assets/4318648/8d0f40c2-d519-4db1-8634-b43caa502cbe)

<br/>


## Building or getting one
I have received quite some requests regarding building or getting the ZSWatch, I am very close to finish with v2. If you want to get notified when I'm done with v2 then simply press the `Watch` button (next to Fork and Star) -> `Custom -> Releases` and you will see in your feed when it's released.
<br/>
**Or** you can fill in your **[mail here (Google form)](https://forms.gle/G48Sm5zDe9aCaYtT9)** and I'll send a reminder when it's ready (or if I decide to make a few kits, who knows).
<br/>

# Table of content ZSWatch
- [Building or getting one](#building-or-getting-one)
- [Hardware features](#hardware-features)
- [Charger/Dock](#chargerdock)
- [Enclosure/Casing](#enclosurecasing)
- [Software Features](#software-features)
  * [Larger not yet implemented SW Features and TODOs](#larger-not-yet-implemented-sw-features-and-todos)
- [Android phone communication](#android-phone-communication)
  * [Pairing](#pairing)
- [PCB](#pcb)
- [ZSWatch v1 in action (Note old, not updated for latest HW and SW).](#zswatch-v1-in-action-note-old-not-updated-for-latest-hw-and-sw)
- [Environment, Compiling and running the code](#environment-compiling-and-running-the-code)
  * [Setting up the environment](#setting-up-the-environment)
  * [Compiling](#compiling)
  * [Running and developing the ZSWatch SW without the actual ZSWatch HW](#running-and-developing-the-zswatch-sw-without-the-actual-zswatch-hw)
- [Writing apps for the Application Manager](#writing-apps-for-the-application-manager)
- [Licence GPL-3.0](#licence-gpl-30)

## Hardware features
- nRF5340 BLE chip (u-blox NORA-B10 module).
  - 128 MHz Dual core.
  - 512 KB RAM (Will allow double buffered of data to the screen and larger framebuffers to decrease lag/tearing).
  - 1 MB Flash.
  - 30 MHz SPI for display.
- **Touch screen** with [240x240 round disply](https://www.buydisplay.com/240x240-round-ips-tft-lcd-display-1-28-inch-capactive-touch-circle-screen)
- IMU [Bosch BMI270](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi270-ds000.pdf), with this one it's possible to do many fancy things such as navigation using gestures and the typical smartwatch wakeup by moving the arm so the display is viewable.
- Bosch [BME688](https://www.bosch-sensortec.com/products/environmental-sensors/gas-sensors/bme688/) Environmental sensor with AI.
- Bosch [BMP581](https://www.bosch-sensortec.com/products/environmental-sensors/pressure-sensors/bmp581/) High performance pressure sensor accuracy in units of ~20cm's.
- ST [LIS2MDLTR](https://www.st.com/resource/en/datasheet/lis2mdl.pdf) Magnetometer.
- Analog Devices [MAX30101](https://www.analog.com/en/products/max30101.html) Heart-Rate Monitor and Pulse Oximeter Sensor.
- Option to not mount some sensors to save BOM cost.

## Charger/Dock
PCB done, casing to be designed. Idea is that watch will sit on top.
Built int debugger. Will be an option without debugger also (requires licence).
<p float="left">
<img src=".github/dock.jpg" width="65%"/>
</p>

## Enclosure/Casing
3D printed casing with 3D printed buttons. Does it's job, but would like to do something else, maybe CNC. Buttons are not 100% perfect right now.

## Software Features
- Bluetooth LE communications with [GadgetBridge](https://codeberg.org/Freeyourgadget/Gadgetbridge) Android app.
- Also support Bluetooth Direction Finding so the watch can act as a tag and is trackable using any [u-blox AoA antenna board](https://www.u-blox.com/en/product/ant-b10-antenna-board)
- Watchface that shows:
   - Standard stuff as time, date, battery
   - Weather
   - Step count
   - Number unread notifications
   - Heart rate (not implemented yet however)
   - ...
- Pop-up notifications
- [Application picker and app concept](#writing-apps-for-the-application-manager)
   - [Setting menu system, with easy extendability](app/src/applications/settings/)
   - [Music control app](app/src/applications/music_control/)
   - [Settings app](app/src/applications/settings/)
   - [Compass app](app/src/applications/compass/)
   - etc.
- Step counting
- Gestures
- And much more
...

### Larger not yet implemented SW Features and TODOs
There are almost endless of posiblities for features that could be implemented, see [here for full progress](https://github.com/users/jakkra/projects/1) for my current ideas and progress.

## Android phone communication
Fortunately there is a great Android app called [GadgetBridge](https://codeberg.org/Freeyourgadget) which handles everything needed on the phone side, such as notifications management, music control and so much more... The ZSWatch right now pretends to be one of the supported Smart Watches in Gadgetbridge, following the same API as it does. In future there may be a point adding native support, we'll see.

### Pairing
- In the watch go to Settings -> Bluetooth -> Enable pairing
- Now go reconnect to the watch from Gadgetbridge app.
- You should now be paired.

## PCB
A 4 layer board which measures 38mm in diameter designed in KiCad.

<p float="left">
<img src=".github/pcb_features.png" width="90%" object-fit="cover"/>
</p>
<p float="left">
<img src=".github/v2_render_wip_back.png" width="49%" object-fit="cover"/>
<img src=".github/layer1_and_4_v2.PNG" width="41%" object-fit="cover"/>
</p>

## ZSWatch v1 in action (Note old, not updated for latest HW and SW).
|*Music control*|*Accelerometer for step count and tap detection*|
|---|---|
|  <img src=".github/music.gif" object-fit="cover" /> |  <img src=".github/accel.gif" object-fit="cover" /> |
|*Notifications from phone (Gmail here)*|*Settings*|
|  <img src=".github/notifications.gif" object-fit="cover" />    |  <img src=".github/settings.gif" object-fit="cover"/> |


https://github.com/jakkra/ZSWatch/assets/4318648/8d8ec724-8145-4a30-b241-e69a8c2853bf


## Environment, Compiling and running the code
### Setting up the environment
Two options, either set up toolchain and everything by following [Zephyr Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) or you can use the in my opinion easier approch by using the [Nordic Toolchain manager](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/getting_started/assistant.html). 
Everything works with both Zephyr and with nRF Connect (Nordic Semi. Zephyr fork). If you are new to Zephyr I suggest installing using Nordic Toolchain manager together with the nRF Connect VSCode plugin as I think that is a bit easier.

*Tested with both*
- Zephyr 3.3.0
- nRF Connect SDK 2.3.0

### Compiling

After setting up the environment using one of the two above options you can compile the application from either command line or within VSCode.

Building [with command line](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/getting_started/programming.html#building-on-the-command-line):

`west build --board zswatch_nrf5340_cpuapp`

Compiling [from VSCode nRF Connect plugin](https://nrfconnect.github.io/vscode-nrf-connect/get_started/build_app_ncs.html):
- Press "Add folder as Application". 
- Choose `zswatch_nrf5340_cpuapp` as the board and nRF Connect SDK 2.3.0.
- Press Create Application

__NOTE__
<br>
If you are building with Zephyr you need in addition manually compile and flash the `zephyr/samples/bluetooth/hci_rpmsg` sample and flash that to the NET core. With nRF Connect this is done automatically thanks to the `child_image/hci_rpmsg.conf`. For convenience I have also uploaded a pre-compiled [hex image for NET CPU](app/child_image/GENERATED_CP_NETWORK_merged_domains.hex) if you don't want to recompile it yourself. Flash it using following:
<br>
`nrfjprog -f NRF53 --coprocessor CP_NETWORK --program app/child_image/GENERATED_CP_NETWORK_merged_domains.hex --chiperase`

To build the NET core image:
Command line: 
- Navigate to `zephyr/samples/bluetooth/hci_rpmsg`
- Fill in "this_folder" in this command and run it `west build --board zswatch_nrf5340_cpunet -- -DBOARD_ROOT=this_folder/app  -DOVERLAY_CONFIG=nrf5340_cpunet_df-bt_ll_sw_split.conf`
- `west flash`
- This only needs to be done once, unless you do a full erase or recover of the nRF5340, which you typically don't do.

VScode:
- Add `zephyr/samples/bluetooth/hci_rpmsg` as an application.
- Select `zswatch_nrf5340_cpunet` as board (VSCode should pick this one up automatically if you added the ZSWatch application earlier).
- Press `Add Fragment` and select the `nrf5340_cpunet_df-bt_ll_sw_split.conf`
- Done, press `Build Configuration`.

### Running and developing the ZSWatch SW without the actual ZSWatch HW
Two options, either using a nRF5340 dev kit or running on Linux using Zephyr native posix port.
#### Native Posix
TODO add more info.

https://github.com/jakkra/ZSWatch/assets/4318648/3b3e4831-a217-45a9-8b90-7b48cea7647e

#### nRF5340 dev kit
This is possible, what you need is a [nRF5340-DK](https://www.digikey.se/en/products/detail/nordic-semiconductor-asa/NRF5340-DK/13544603) (or EVK-NORA-B1) and a breakout of the screen I use [https://www.waveshare.com/1.28inch-touch-lcd.htm](https://www.waveshare.com/1.28inch-touch-lcd.htm).
<br>
You may also add _any_ of the sensors on the ZSWatch, Sparkfun for example have them all:<br>
[BMI270](https://www.sparkfun.com/products/17353)
[BME688](https://www.sparkfun.com/products/19096)
[BMP581](https://www.sparkfun.com/products/20170)
[MAX30101](https://www.sparkfun.com/products/16474)
[LIS2MDL](https://www.sparkfun.com/products/19851)

When using the nRF5340-DK all you need to do is to replace `zswatch_nrf5340_cpuapp` with `nrf5340dk_nrf5340_cpuapp` as the board in the compiling instructions above. You may also need to tweak the pin assignment in [app/boards/nrf5340dk_nrf5340_cpuapp.overlay](app/boards/nrf5340dk_nrf5340_cpuapp.overlay) for your needs.

## Writing apps for the Application Manager
Check out [the sample application](app/src/applications/template/) for the general app design. The main idea is each app have an `<app_name>_app.c` file which registers the app, chooses icon and drives the logic for the app. Then there should be one or more files named for example `<app_name>_ui.c` containing pure LVGL code with no dependencies to Zephyr or the watch software. The idea is that this UI code should be runnable in a LVGL simulator to speed up development of UI, however right now that's not set up yet. The `<app_name>_app.c` will do all logic and call functions in `<app_name>_ui.c` to update the UI accordingly. 

Each application needs to have a way to close itself, for example a button, and then through callback tell the `application_manager.c` to close the app:

When user clicks an app in the app picker:
- `application_manager.c` deletes it's UI elements and calls the `application_start_fn`.
- `<app_name>_app.c` will do necessary init and then call the `<app_name>_ui.c` to draw the app UI.
- User can now navigate arund and the application and do whatever.

When user for example presses a close button in the application:
- Typically a callback from the UI code in `<app_name>_ui.c` will call `<app_name>_app.c` to tell that user requested to close the app. `<app_name>_app.c` will notify `application_manager.c` that it want to close itself. `application_manager.c` will then call `<app_name>_app.c` `application_stop_fn` and `<app_name>_app.c` will tell UI to close then do necessary de-init and return.
- `application_manager.c` will now draw the app picker again.

The application manager can also at any time close a running application by calling it's `application_stop_fn`.

## Licence GPL-3.0
Main difference from MIT is now that if anyone want to build something more with this, then they need to also open source their changes back to the project, which I thinks is fair. This is so everyone can benefit from those improvements. If you think this is wrong for some reason feel free to contact me, I'm open to change the LICENCE.
