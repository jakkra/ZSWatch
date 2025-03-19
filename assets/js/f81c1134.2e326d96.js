"use strict";(self.webpackChunkwebsite=self.webpackChunkwebsite||[]).push([[8130],{7735:e=>{e.exports=JSON.parse('{"archive":{"blogPosts":[{"id":"funding","metadata":{"permalink":"/blog/funding","source":"@site/blog/2025-03-14-funding/index.md","title":"We received funding!","description":"For the last few months there have not been much progress in ZSWatch. But that\'s about to change, because we have received 50 000 \u20ac from the NLnet Foundation to take ZSWatch to the next level!","date":"2025-03-14T00:00:00.000Z","tags":[{"inline":false,"label":"ZSWatch","permalink":"/blog/tags/zswatch","description":"ZSWatch core"},{"inline":false,"label":"NLnet Foundation","permalink":"/blog/tags/nlnet","description":"Anything regarding NLnet Foundation"}],"readingTime":2.255,"hasTruncateMarker":true,"authors":[{"name":"Jakob Krantz","title":"Senior Software Engineer and ZSWatch Creator and Maintainer","url":"https://jakobkrantz.se","page":{"permalink":"/blog/authors/jakkra"},"socials":{"github":"https://github.com/jakkra","linkedin":"https://www.linkedin.com/in/jakob-krantz-ba9a97127/"},"imageURL":"https://github.com/jakkra.png","key":"jakkra"}],"frontMatter":{"slug":"funding","title":"We received funding!","authors":["jakkra"],"tags":["zswatch","nlnet"]},"unlisted":false,"nextItem":{"title":"ZSWatch Intro","permalink":"/blog/intro"}},"content":"import ZSWatchLogo from \'./ZSWatch_logo_with_text.png\';\\nimport NlnetLogo from \'./NGI0Core_tag.png\';\\nimport NGI0CoreLogo from \'./nlnet_banner.png\';\\nimport SubscriptionForm from \'@site/src/components/SubscriptionForm\';\\n\\n<p float=\\"left\\">\\n  <img src={ZSWatchLogo} width=\\"33%\\" />\\n  <img src={NlnetLogo} width=\\"33%\\" /> \\n  <img src={NGI0CoreLogo} width=\\"33%\\" />\\n</p>\\n\\n\\nFor the last few months there have not been much progress in ZSWatch. **But** that\'s about to change, because we have received 50 000 \u20ac from the [NLnet Foundation](https://nlnet.nl/project/ZSWatch/) to take ZSWatch to the next level!\\n\\nThe NLnet Foundation is funded by the European Commission\'s *Next Generation Internet*:\\n\\n> We support organisations and people who contribute to an open internet for all. We fund projects that help fix the internet through open hardware, open software, open standards, open science and open data.\\n\\nWhich ZSWatch falls pretty well under.\\n\\nBelow we go into more details about what this means.\\n\\n\x3c!-- truncate --\x3e\\n### How the funding will be used\\n\\nThe funding will allow [me] to work 50% and [Daniel] to work 20% on ZSWatch. The rest of the money will go to hardware and hardware prototyping costs. The funded project will run for 1 year.\\n\\nThe goal is to both rework and improve ZSWatch. Mainly to make it more accessible to a broader audience and grow the community. This will be done by making it cheaper, easier to assemble and use more accessible parts. Right now getting all parts and assembling a ZSWatch is not super easy, this we aim to change!\\n\\n**Our goal is within one year have a robust watch that is easy to assembly that you can easily get your hands on!**\\n\\n### High level plan\\nThere are so much more details defined, but including that would make this post very long. So here is the high level tasks we aim to finish.\\n:::tip Goals\\n    - New daughter board for health tracking.\\n        - This will be a optional PCB that connects to the main PCB.\\n        - Since HR algorithms are no easy task, we are planning to use [MAX32664(C) Biometric Snesor Hub with embedded algorithms](https://www.analog.com/en/products/max32664.html).\\n    - New main board.\\n        - Cheaper.\\n        - Optimize physical layout for improved mechanical assembly.\\n        - Changes to accomodate the daughter board.\\n    - Change of components on ZSWatch.\\n    - New simpler dock.\\n    - Case redesign.\\n    - Production test software.\\n    - Documentation using [Docusaurus](https://docusaurus.io/).\\n        - You are reading on it now!\\n        - We will host the blog and all documentation.\\n    - Improve software usability.\\n    - Lightwight app store.\\n        - We want to investigate [Zephyr LLEXT](https://docs.zephyrproject.org/latest/services/llext/index.html) to see if it\'s feasable to dynamically load applications to ZSWatch.\\n    - Testing.\\n        - We need more automated tests to easy catch regressions.\\n    - Phone integration improvements.\\n:::\\n\\nWe will post updates of our progress so don\'t forget to sign up for our email list!\\n\\n<SubscriptionForm/>\\n\\n[me]: https://github.com/jakkra\\n[Daniel]: https://github.com/kampi"},{"id":"intro","metadata":{"permalink":"/blog/intro","source":"@site/blog/2025-03-13-zswatch-into/index.md","title":"ZSWatch Intro","description":"If you have not heard of ZSWatch before, here is a short intro!","date":"2025-03-13T00:00:00.000Z","tags":[{"inline":false,"label":"ZSWatch","permalink":"/blog/tags/zswatch","description":"ZSWatch core"},{"inline":true,"label":"intro","permalink":"/blog/tags/intro"}],"readingTime":2.315,"hasTruncateMarker":true,"authors":[{"name":"Jakob Krantz","title":"Senior Software Engineer and ZSWatch Creator and Maintainer","url":"https://jakobkrantz.se","page":{"permalink":"/blog/authors/jakkra"},"socials":{"github":"https://github.com/jakkra","linkedin":"https://www.linkedin.com/in/jakob-krantz-ba9a97127/"},"imageURL":"https://github.com/jakkra.png","key":"jakkra"}],"frontMatter":{"slug":"intro","title":"ZSWatch Intro","authors":["jakkra"],"tags":["zswatch","intro"]},"unlisted":false,"prevItem":{"title":"We received funding!","permalink":"/blog/funding"}},"content":"If you have not heard of ZSWatch before, here is a short intro!\\n\x3c!-- truncate --\x3e\\nimport ZSWatchLogo from \'./ZSWatch_logo_with_text.png\';\\nimport SubscriptionForm from \'@site/src/components/SubscriptionForm\';\\nimport ReactPlayer from \'react-player\'\\nimport HardwareOverview from \'@site/static/img/Hardware_Overview_transparent.png\'\\n\\nBuilt on the [Zephyr\u2122 Project](https://www.zephyrproject.org/) RTOS, hence the name **ZSWatch** - *Zephyr Smartwatch*.\\n\\nZSWatch is a free and open source smartwatch you can build almost from scratch - including software, hardware, and mechanics. Everything from the lowest level BLE radio driver code to PCB and casing is available and can be customised to suit your needs. \\n\\n\\n<center>Video walking through some of the UI and features.</center>\\n<ReactPlayer width=\\"100%\\" playing muted controls url=\'https://github.com/jakkra/ZSWatch/assets/4318648/ec1a94fd-a682-4559-9e68-f3e5bfcbe682\' />\\n\\n### Software\\nShort feature overview:\\n- Bluetooth LE communications with [GadgetBridge](https://codeberg.org/Freeyourgadget/Gadgetbridge) Android app.\\n- Multiple Watchfaces showing:\\n  - Standard stuff such as time, date, battery\\n  - Weather\\n  - Step count\\n  - Number of unread notifications\\n  - Environmental data\\n  - ...\\n- Pop-up notifications\\n- Application picker and app concept\\n  - Setting menu system, with easy extendability\\n  - Music control app\\n  - Settings app\\n  - Compass app\\n  - etc.\\n- Step counting\\n- Gestures\\n- iOS support (limited)\\n- And much more\\n...\\n\\n### Hardware\\nZSWatch is equipped with a range of powerful hardware components that make it a versatile and capable smartwatch.\\n\\n<img src={HardwareOverview} />\\n\\n<details>\\n    <summary>Components description</summary>\\n    - nRF5340 BLE chip ([u-blox NORA-B10 module](https://www.u-blox.com/en/product/nora-b1-series-open-cpu)): The watch is powered by a 128 MHz dual-core nRF5340 BLE chip, providing high-performance processing capabilities.\\n    \\n    - Nordic [nPM1300](https://docs.nordicsemi.com/category/npm1300-category) PMIC: The power management integrated circuit ensures efficient power delivery and battery life estimations.\\n\\n    - 240x240 round display: ZSWatch features a vibrant and responsive 240x240 round display with a capacitive touch screen, ensuring a smooth and intuitive user experience.\\n\\n    - IMU [Bosch BMI270](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi270-ds000.pdf): The integrated IMU allows for advanced features such as gesture-based navigation and smartwatch wake-up by arm movement.\\n\\n    - Bosch [BME688](https://www.bosch-sensortec.com/products/environmental-sensors/gas-sensors/bme688/) Environmental sensor: The BME688 sensor provides AI-enhanced environmental data, enabling the watch to monitor air quality and other environmental parameters.\\n\\n    - Bosch [BMP581](https://www.bosch-sensortec.com/products/environmental-sensors/pressure-sensors/bmp581/) High-performance pressure sensor: The BMP581 sensor offers accurate pressure measurements with a precision of approximately 20cm.\\n\\n    - ST [LIS2MDLTR](https://www.st.com/resource/en/datasheet/lis2mdl.pdf) Magnetometer: The magnetometer enables the watch to detect magnetic fields, opening up possibilities for compass and navigation applications.\\n\\n    - Macronix [MX25U51245GZ4I00](https://www.mouser.de/datasheet/2/819/MX25U51245G_2c_1_8V_2c_512Mb_2c_v1_4-3371129.pdf) 64 MB external flash: The external flash provides large storage space for data and UI resources.\\n\\n    - Broadcom [APDS-9306-065](https://docs.broadcom.com/docs/AV02-4755EN) Light Sensor: The light sensor enables automatic brightness control.\\n\\n    - Micro Crystal [RV-8263-C8](https://www.microcrystal.com/en/products/real-time-clock-rtc-modules/rv-8263-c8) RTC: The real-time clock module ensures accurate timekeeping and supports alarm functions.\\n\\n    - Knowles [SPK0641HT4H-1](https://www.knowles.com/docs/default-source/model-downloads/spk0641ht4h-1-rev-a.pdf) I2S microphone: The built-in microphone allows for audio recording and voice control capabilities.\\n\\n\\n    Option to not mount sensors: ZSWatch offers the flexibility to exclude certain sensors, allowing for cost optimization based on specific requirements.\\n\\n    This powerful combination of hardware components ensures that ZSWatch delivers a rich and immersive smartwatch experience.\\n</details>\\n\\n<SubscriptionForm/>"}]}}')}}]);