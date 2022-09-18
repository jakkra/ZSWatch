# Smart Watch

A 4 layer board and measures 36mm in diameter. I will "hand solder" top side using a hot plate and the bottom probably with hot air, almost all components are on the top. Tjose are the layers:

1. Signal
2. GND
3. Power 1V8 and 3V3 (except 3 traces I had to run on this layer as I forgot the buttons after routing everything...)
4. Signal

Features and datasheets:

* nRF52833 (SIP module) microcontroller running on 1V8.
* Power management
   * LiPo charger [MAX1811ESA+ datasheet](https://datasheets.maximintegrated.com/en/ds/MAX1811.pdf)
   * Battery supervisor (low voltage protection) [TLV840MAPL3... datasheet](https://www.ti.com/lit/ds/symlink/tlv840-q1.pdf?ts=1662823963602&ref_url=https%253A%252F%252Fwww.ti.com%252Fpower-management%252Fsupervisor-reset-ic%252Fproducts.html)
   * 1V8 regulator [XC9265C181MR-G datasheet](https://www.torexsemi.com/file/xc9265/XC9265.pdf)
   * Battery level reading circuit with moset [DMC2400UV-7 datasheet](https://www.diodes.com/assets/Datasheets/DMC2400UV.pdf)
* Accelerometer and step counter [LIS2DS12TR datasheet](https://www.st.com/content/ccc/resource/technical/document/datasheet/ce/32/55/ac/e1/87/46/84/DM00177048.pdf/files/DM00177048.pdf/jcr:content/translations/en.DM00177048.pdf)
* Vibration motor driver [DRV2603RUNT datasheet](https://www.ti.com/lit/ds/symlink/drv2603.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1662847620221)
* External 8MB Flash [MX25R6435FZNIL0 datasheet](https://static6.arrow.com/aropdfconversion/a35c4dff799e6b2e44732bd665796d74a8a3f62a/244684669660894mx25r6435f20wide20range2064mb20v1..pdf)
* Biometric sensor (heart rate etc.)
   * [MAX30101EFD datasheet](https://datasheets.maximintegrated.com/en/ds/MAX30101.pdf)
   * 5V boost regulator  [TPS61023DRLT datasheet](https://www.ti.com/lit/ds/symlink/tps61023.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1662847882782) and it's [app note](https://pdfserv.maximintegrated.com/en/an/AN6409.pdf)
* Round display

1. 1.8V <=> logic shifter [TXB0104QRUTRQ1 datasheet](https://www.ti.com/lit/ds/symlink/txb0104-q1.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1662908379294&ref_url=https%253A%252F%252Fwww.ti.com%252Fgeneral%252Fdocs%252Fsuppproductinfo.tsp%253FdistId%253D10%2526gotoUrl%253Dhttps%253A%252F%252Fwww.ti.com%252Flit%252Fgpn%252Ftxb0104-q1)
2. [Display datasheet](https://www.buydisplay.com/download/ic/GC9A01A.pdf)
3. 3V3 voltage regulator (same as 1V8 one in Power Management)