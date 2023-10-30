SET(SOURCES 
    screens/iaq_ui.c
    images/iaq_img_socket_png.c
    images/iaq_img_scale_png.c
    images/iaq_img_cursor_png.c)

target_sources(app PRIVATE ${SOURCES})