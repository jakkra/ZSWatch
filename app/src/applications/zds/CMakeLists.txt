if (CONFIG_DEMO_BUILD)
FILE(GLOB app_sources *.c)
target_sources(app PRIVATE ${app_sources})
endif()
