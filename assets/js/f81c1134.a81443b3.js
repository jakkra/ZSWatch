"use strict";(self.webpackChunkwebsite=self.webpackChunkwebsite||[]).push([[130],{7735:e=>{e.exports=JSON.parse('{"archive":{"blogPosts":[{"id":"funding","metadata":{"permalink":"/blog/funding","source":"@site/blog/2025-03-14-funding/index.md","title":"Funding","description":"We received funding from the NLnet Foundation!","date":"2025-03-14T00:00:00.000Z","tags":[{"inline":false,"label":"ZSWatch","permalink":"/blog/tags/zswatch","description":"ZSWatch core"},{"inline":false,"label":"NLnet Foundation","permalink":"/blog/tags/nlnet","description":"Anything regarding NLnet Foundation"}],"readingTime":2.18,"hasTruncateMarker":true,"authors":[{"name":"Jakob Krantz","title":"Senior Software Engineer and ZSWatch Creator and Maintainer","url":"https://jakobkrantz.se","page":{"permalink":"/blog/authors/jakkra"},"socials":{"github":"https://github.com/jakkra","linkedin":"https://www.linkedin.com/in/jakob-krantz-ba9a97127/"},"imageURL":"https://github.com/jakkra.png","key":"jakkra"}],"frontMatter":{"slug":"funding","title":"Funding","authors":["jakkra"],"tags":["zswatch","nlnet"]},"unlisted":false,"nextItem":{"title":"ZSWatch Intro","permalink":"/blog/intro"}},"content":"### **We received funding from the [NLnet Foundation](https://nlnet.nl/project/ZSWatch/)!**\\r\\nimport ZSWatchLogo from \'./ZSWatch_logo_with_text.png\';\\r\\nimport NlnetLogo from \'./NGI0Core_tag.png\';\\r\\nimport NGI0CoreLogo from \'./nlnet_banner.png\';\\r\\n\\r\\n<p float=\\"left\\">\\r\\n  <img src={ZSWatchLogo} width=\\"33%\\" />\\r\\n  <img src={NlnetLogo} width=\\"33%\\" /> \\r\\n  <img src={NGI0CoreLogo} width=\\"33%\\" />\\r\\n</p>\\r\\nClick title to read more!\\r\\n\\r\\n\x3c!-- truncate --\x3e\\r\\nFor the last few months there have not been much progress in ZSWatch. **But** that\'s about to change, because we have received 50 000 \u20ac from the [NLnet Foundation](https://nlnet.nl/project/ZSWatch/) to take ZSWatch to the next level!\\r\\n\\r\\nThe NLnet Foundation is funded by the European Commission\'s *Next Generation Internet*:\\r\\n\\r\\n> We support organisations and people who contribute to an open internet for all. We fund projects that help fix the internet through open hardware, open software, open standards, open science and open data.\\r\\n\\r\\nWhich ZSWatch falls pretty well under.\\r\\n\\r\\n### How the funding will be used\\r\\n\\r\\nThe funding will allow [me] to work 50% and [Daniel] to work 20% on ZSWatch. The rest of the money will go to hardware and hardware prototyping costs. The funded project will run for 1 year.\\r\\n\\r\\nThe goal is to both rework and improve ZSWatch. Mainly to make it more accessible to a broader audience and grow the community. This will be done by making it cheaper, easier to assemble and use more accessible parts.\\r\\n\\r\\n**Our goal is within one year have a robust watch that is easy to assembly that you can easily get your hands on!**\\r\\n\\r\\n### High level plan\\r\\nThere are so much more details defined, but including that would make this post very long. So here is the high level tasks we aim to finish.\\r\\n:::tip Goals\\r\\n    - New daughter board for health tracking.\\r\\n        - This will be a optional PCB that connects to the main PCB.\\r\\n        - Since HR algorithms are no easy task, we are planning to use [MAX32664(C) Biometric Snesor Hub with embedded algorithms](https://www.analog.com/en/products/max32664.html).\\r\\n    - New main board.\\r\\n        - Cheaper.\\r\\n        - Optimize physical layout for improved mechanical assembly.\\r\\n        - Changes to accomodate the daughter board.\\r\\n    - Change of components on ZSWatch.\\r\\n    - New simpler dock.\\r\\n    - Case redesign.\\r\\n    - Production test software.\\r\\n    - Documentation using [Docusaurus](https://docusaurus.io/).\\r\\n        - You are reading on it now!\\r\\n        - We will host the blog and all documentation.\\r\\n    - Improve software usability.\\r\\n    - Lightwight app store.\\r\\n        - We want to investigate [Zephyr LLEXT](https://docs.zephyrproject.org/latest/services/llext/index.html) to see if it\'s feasable to dynamically load applications to ZSWatch.\\r\\n    - Testing.\\r\\n        - We need more automated tests to easy catch regressions.\\r\\n    - Phone integration improvements.\\r\\n:::\\r\\n\\r\\nWe will post updates of our progress so don\'t forget to sign up for our email list!\\r\\n\\r\\nimport SubscriptionForm from \'@site/src/components/SubscriptionForm\';\\r\\n\\r\\n<SubscriptionForm/>\\r\\n\\r\\n[me]: https://github.com/jakkra\\r\\n[Daniel]: https://github.com/kampi"},{"id":"intro","metadata":{"permalink":"/blog/intro","source":"@site/blog/2025-03-13-zswatch-into/index.md","title":"ZSWatch Intro","description":"If you have not heard of ZSWatch before, here is a short intro!","date":"2025-03-13T00:00:00.000Z","tags":[{"inline":false,"label":"ZSWatch","permalink":"/blog/tags/zswatch","description":"ZSWatch core"}],"readingTime":0.375,"hasTruncateMarker":true,"authors":[{"name":"Jakob Krantz","title":"Senior Software Engineer and ZSWatch Creator and Maintainer","url":"https://jakobkrantz.se","page":{"permalink":"/blog/authors/jakkra"},"socials":{"github":"https://github.com/jakkra","linkedin":"https://www.linkedin.com/in/jakob-krantz-ba9a97127/"},"imageURL":"https://github.com/jakkra.png","key":"jakkra"}],"frontMatter":{"slug":"intro","title":"ZSWatch Intro","authors":["jakkra"],"tags":["zswatch"]},"unlisted":false,"prevItem":{"title":"Funding","permalink":"/blog/funding"}},"content":"If you have not heard of ZSWatch before, here is a short intro!\\r\\n\x3c!-- truncate --\x3e\\r\\nimport ZSWatchLogo from \'./ZSWatch_logo_with_text.png\';\\r\\n\\r\\n<img src={ZSWatchLogo} />\\r\\n\\r\\nZSWatch is a free and open source smartwatch you can build almost from scratch - including software, hardware, and mechanics. Everything from the lowest level BLE radio driver code to PCB and casing is available for introspection or to be customised to suit your needs. \\r\\n\\r\\nTODO: Write more intro to new people"}]}}')}}]);