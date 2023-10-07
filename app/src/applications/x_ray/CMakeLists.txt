if(CONFIG_APPLICATIONS_X_RAY)
    FILE(GLOB app_sources *.c)
    target_sources(app PRIVATE ${app_sources})
endif()