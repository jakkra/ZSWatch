if(CONFIG_APPLICATIONS_QR_CODE)
    FILE(GLOB app_sources *.c)
    target_sources(app PRIVATE ${app_sources})
endif()
