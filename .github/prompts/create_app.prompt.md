---
agent: agent
---
# Application Creation Prompt
We are going to create a pplication for my open source smartwatch. We typically create apps in LVGL Editor which uses XML to define the UI and C for the logic. It will generate the lvgl c code for us. 

Only generate minimal LVGL UI code in c code, focus on the XML design. You can create re-usable components in XML also.

Always ask the user if they have a reference mockup or design for the app before starting.

LVGL Editor project: app/lvgl_editor
Example code and readme for LVGL Editor usage: app/lvgl_editor
Extra API docs etc: app/lvgl_editor_examples_do_not_modify

And to use context7 to fetch more api docs etc. as needed.

Always study the provided docs and samples to understand how to best create the app.

There are some examples how LVGL editor integrates with the watch app framework in app/src/applications/music_control/music_control_app.c and app/src/ui/app_picker/app_picker_ui.c

For reference how applications are structured also check any application in the app/src/applications/ folder.

Let the user know if anything is unclear, please come with suggestions if you have ideas on improvements etc.

# Worflow
1. You will create the xml design for the app in LVGL Editor format.
2. Ask the user to generate the lvgl c code using LVGL Editor.
3. You will then create the app logic in C code, integrating with the watch app framework as needed.
4. Iterate steps 2 and 3 until the app is complete.
west build --build-dir /home/jakkra/Documents/ZSWatch/app/build_dbg_dk /home/jakkra/Documents/ZSWatch/app --pristine --board watchdk@1/nrf5340/cpuapp --sysbuild -- -DEXTRA_CONF_FILE="boards/debug.conf;boards/log_on_uart.conf" -DEXTRA_DTC_OVERLAY_FILE="boards/log_on_uart.overlay" -DDEBUG_THREAD_INFO=Off -Dapp_DEBUG_THREAD_INFO=Off -Dmcuboot_DEBUG_THREAD_INFO=Off -Dipc_radio_DEBUG_THREAD_INFO=Off -Db0n_DEBUG_THREAD_INFO=Off -DBOARD_ROOT="/home/jakkra/Documents/ZSWatch/app"