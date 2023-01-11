<div align="center">
  <h1>zWatch</h1>
<img src=".github/in_use.jpg"/>
<sub>
  Smartwatch built from scratch-ish.
</sub>
</div>

## Hardware Features v1.0
- 1.28" 240x240 IPS TFT Circular Display with [GC9A01 driver](https://www.buydisplay.com/1-28-inch-tft-lcd-display-240x240-round-circle-screen-for-smart-watch).
- Accelerometer for step counting etc. [(LIS2DS12TR)](https://www.st.com/content/ccc/resource/technical/document/datasheet/ce/32/55/ac/e1/87/46/84/DM00177048.pdf/files/DM00177048.pdf/jcr:content/translations/en.DM00177048.pdf).
- Pulse oximetry and heartrate using [(MAX30101EFD)](https://datasheets.maximintegrated.com/en/ds/MAX30101.pdf)).
- nRF52833 BLE chip [(u-blox ANNA-B402 module)](https://content.u-blox.com/sites/default/files/ANNA-B402_DataSheet_UBX-20032372.pdf).
- Vibration motor with haptics driver to give better vibration control [(DRV2603RUNT)](https://www.ti.com/lit/ds/symlink/drv2603.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1662847620221).
- External 8MB flash [(MX25R6435FZNIL0)](https://static6.arrow.com/aropdfconversion/a35c4dff799e6b2e44732bd665796d74a8a3f62a/244684669660894mx25r6435f20wide20range2064mb20v1..pdf).
- Battery charger and battery supervisor ([MAX1811ESA+ datasheet](https://datasheets.maximintegrated.com/en/ds/MAX1811.pdf), [TLV840MAPL3](https://www.ti.com/lit/ds/symlink/tlv840-q1.pdf?ts=1662823963602&ref_url=https%253A%252F%252Fwww.ti.com%252Fpower-management%252Fsupervisor-reset-ic%252Fproducts.html)).
- 220 mAh Li-Po battery.
- Sapphire Crystal Glass to protect the display.

## Charger/Dock
- Basic pogo-pin dock that connects the power and SWD pins to the bottom of the watch.

### Upcoming Hardware features in zWatch v2.0
- nRF5340 BLE chip (u-blox NORA-B10 module)
- **Touch screen** with [same size and features as V1](https://www.buydisplay.com/240x240-round-ips-tft-lcd-display-1-28-inch-capactive-touch-circle-screen)
- 8MB external flash will *probably* be removed due to larger size of NORA-B10 vs. ANNA-B40.
- Find another way to dock the clock for charging and programming, maybe can find some connector similar to what smartwatches normally have.

## Software Features
- Bluetooth LE communications with [GadgetBridge](https://codeberg.org/Freeyourgadget) Android app.
- Watchface that shows:
   - Standard stuff as time, date, battery.
   - Weather.
   - Step count.
   - Number unread notifications.
   - Heart rate (not implemented yet however).
- Pop-up notifications.
- Setting menu system, with easy extendability.
- Application picker and app concept.
   - Music control app.
   - Settings app.
   - etc.
- Step counting.

### Mayor not yet implemented SW Features
- Heart rate, right now only collects the raw data, but no heart rate is calculated from it.
- Proper BLE pairing, currently removed due to flash constraints.

## Android phone communication
Fortunately there is a great Android app called [GadgetBridge](https://codeberg.org/Freeyourgadget) which handles everything needed on the phone side, such as notifications management, music control and so much more... The zWatch right now pretends to be one of the supported Smart Watches in Gadgetbridge, following the same API as it does. In future there may be a point adding native support, we'll see.

## zWatch in action
|*Music control*|*Accelerometer for step count and tap detection*|
|---|---|
|  <img src=".github/music.gif" />    |  <img src=".github/accel.gif" height="360" /> |
|*Notifications from phone (Gmail here)*|*Settings*|
|  <img src=".github/notifications.gif"  />    |  <img src=".github/settings.gif"/> |

## PCB
A 4 layer board which measures 36mm in diameter designed in KiCad.

<p float="left">
<img src=".github/pcb.jpg" height="510"/>
<img src=".github/parts.jpg" height="510"/>
</p>
