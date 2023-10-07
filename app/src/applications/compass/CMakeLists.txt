if(CONFIG_APPLICATIONS_USE_COMPASS)
    FILE(GLOB app_sources *.c)
    target_sources(app PRIVATE ${app_sources})
endif()