#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_UI_IMG_DISCORD_PNG
#define LV_ATTRIBUTE_IMG_UI_IMG_DISCORD_PNG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_UI_IMG_DISCORD_PNG uint8_t ui_img_discord_png_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x0c, 0x6f, 0x5f, 0x6f, 0xa5, 0x6f, 0xc3, 0x6f, 0xc3, 0x6f, 0xa5, 0x6f, 0x5f, 0x6f, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x5c, 0x6f, 0xe8, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xe7, 0x6f, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x6f, 0x82, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x6f, 0x5c, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0x5a, 0x00, 0x00, 
  0x6f, 0x0c, 0x6f, 0xe8, 0x6f, 0xff, 0x93, 0xff, 0xbb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0xff, 0x93, 0xff, 0x6f, 0xff, 0x6f, 0xe6, 0x73, 0x0b, 
  0x6f, 0x61, 0x6f, 0xff, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0x5e, 
  0x6f, 0xa6, 0x6f, 0xff, 0x97, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x97, 0xff, 0x6f, 0xff, 0x6f, 0xa4, 
  0x6f, 0xc4, 0x6f, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0x4e, 0xff, 0x6f, 0xc5, 
  0x6f, 0xc3, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x4e, 0xff, 0x4a, 0xff, 0xff, 0xff, 0xff, 0xff, 0x4e, 0xff, 0x6e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0xff, 0x6f, 0xc7, 
  0x6f, 0xa5, 0x73, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0xff, 0x6f, 0xa8, 
  0x6f, 0x5f, 0x73, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x73, 0xff, 0x6f, 0x5f, 
  0x6f, 0x0c, 0x6f, 0xe7, 0x93, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xff, 0x6e, 0xff, 0x93, 0xff, 0x93, 0xff, 0x73, 0xff, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x93, 0xff, 0x6f, 0xe7, 0x73, 0x0b, 
  0x00, 0x00, 0x6f, 0x5a, 0x6f, 0xff, 0x6f, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0x58, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x6f, 0x80, 0x6f, 0xff, 0x6f, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0x7f, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x5a, 0x6f, 0xe7, 0x6f, 0xff, 0x4e, 0xff, 0x4e, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xff, 0x6f, 0xe7, 0x6f, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x0b, 0x6f, 0x5d, 0x6f, 0xab, 0x6f, 0xcb, 0x6f, 0xc9, 0x6f, 0xa8, 0x6f, 0x60, 0x73, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x5b, 0x0c, 0x78, 0x5b, 0x5f, 0x78, 0x63, 0xa5, 0x78, 0x63, 0xc3, 0x78, 0x63, 0xc3, 0x78, 0x63, 0xa5, 0x78, 0x5b, 0x5f, 0x78, 0x5b, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x5b, 0x5c, 0x78, 0x63, 0xe8, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xe7, 0x78, 0x5b, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x63, 0x82, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x78, 0x5b, 0x5c, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x98, 0x63, 0xff, 0x98, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x98, 0x63, 0xff, 0x98, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x78, 0x5b, 0x5a, 0x00, 0x00, 0x00, 
  0x78, 0x5b, 0x0c, 0x78, 0x63, 0xe8, 0x78, 0x63, 0xff, 0x18, 0x7c, 0xff, 0x99, 0xb5, 0xff, 0xfa, 0xbd, 0xff, 0xb9, 0xb5, 0xff, 0x3b, 0xc6, 0xff, 0x3b, 0xc6, 0xff, 0xda, 0xbd, 0xff, 0x1a, 0xc6, 0xff, 0xba, 0xb5, 0xff, 0x18, 0x7c, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0xe6, 0xb7, 0x63, 0x0b, 
  0x78, 0x63, 0x61, 0x78, 0x63, 0xff, 0x78, 0x63, 0xff, 0x7e, 0xef, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x7e, 0xef, 0xff, 0x57, 0x5b, 0xff, 0x78, 0x63, 0xff, 0x78, 0x63, 0x5e, 
  0x78, 0x63, 0xa6, 0x78, 0x63, 0xff, 0xd9, 0x94, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x97, 0x8c, 0xff, 0x57, 0x5b, 0xff, 0x78, 0x63, 0xa4, 
  0x78, 0x63, 0xc4, 0x78, 0x63, 0xff, 0x5b, 0xc6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9b, 0xd6, 0xff, 0x1a, 0xc6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3b, 0xc6, 0xff, 0x9c, 0xd6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5c, 0xce, 0xff, 0xf4, 0x52, 0xff, 0x37, 0x5b, 0xc5, 
  0x78, 0x63, 0xc3, 0x78, 0x63, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x52, 0xff, 0x6f, 0x42, 0xff, 0x7e, 0xef, 0xff, 0x7e, 0xef, 0xff, 0x91, 0x4a, 0xff, 0x13, 0x5b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf7, 0xff, 0xf4, 0x52, 0xff, 0x15, 0x5b, 0xc7, 
  0x78, 0x63, 0xa5, 0xb8, 0x6b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb9, 0xb5, 0xff, 0xf7, 0x9c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x18, 0x9d, 0xff, 0xda, 0xb5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x56, 0x63, 0xff, 0x36, 0x5b, 0xa8, 
  0x78, 0x5b, 0x5f, 0xd8, 0x73, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xde, 0xff, 0x7e, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0xef, 0xff, 0xfd, 0xde, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd7, 0x6b, 0xff, 0x57, 0x5b, 0x5f, 
  0x78, 0x5b, 0x0c, 0x78, 0x63, 0xe7, 0x58, 0x84, 0xff, 0xdc, 0xde, 0xff, 0xff, 0xff, 0xff, 0x38, 0xa5, 0xff, 0x94, 0x6b, 0xff, 0x36, 0x84, 0xff, 0x36, 0x84, 0xff, 0xb5, 0x6b, 0xff, 0x7a, 0xa5, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xde, 0xff, 0x79, 0x84, 0xff, 0x57, 0x5b, 0xe7, 0xb7, 0x63, 0x0b, 
  0x00, 0x00, 0x00, 0x78, 0x5b, 0x5a, 0x78, 0x63, 0xff, 0x15, 0x53, 0xff, 0xb1, 0x4a, 0xff, 0xb1, 0x4a, 0xff, 0xb2, 0x4a, 0xff, 0xb2, 0x4a, 0xff, 0xd3, 0x52, 0xff, 0xf4, 0x52, 0xff, 0x15, 0x53, 0xff, 0x36, 0x5b, 0xff, 0x36, 0x5b, 0xff, 0x57, 0x5b, 0xff, 0x78, 0x63, 0x58, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x63, 0x80, 0x78, 0x63, 0xff, 0x15, 0x5b, 0xff, 0xb2, 0x4a, 0xff, 0xb2, 0x4a, 0xff, 0xd3, 0x52, 0xff, 0xf4, 0x52, 0xff, 0xf4, 0x52, 0xff, 0x15, 0x53, 0xff, 0x36, 0x5b, 0xff, 0x57, 0x5b, 0xff, 0x78, 0x63, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x5b, 0x5a, 0x78, 0x63, 0xe7, 0x36, 0x5b, 0xff, 0xd3, 0x52, 0xff, 0xf4, 0x52, 0xff, 0xf4, 0x52, 0xff, 0x15, 0x53, 0xff, 0x36, 0x5b, 0xff, 0x57, 0x5b, 0xe7, 0x78, 0x63, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x63, 0x0b, 0x78, 0x63, 0x5d, 0x15, 0x5b, 0xab, 0xf4, 0x52, 0xcb, 0x35, 0x5b, 0xc9, 0x36, 0x5b, 0xa8, 0x37, 0x5b, 0x60, 0xb7, 0x63, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x78, 0x0c, 0x5b, 0x78, 0x5f, 0x63, 0x78, 0xa5, 0x63, 0x78, 0xc3, 0x63, 0x78, 0xc3, 0x63, 0x78, 0xa5, 0x5b, 0x78, 0x5f, 0x5b, 0x78, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x78, 0x5c, 0x63, 0x78, 0xe8, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xe7, 0x5b, 0x78, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x78, 0x82, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x5b, 0x78, 0x5c, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x98, 0xff, 0x63, 0x98, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x98, 0xff, 0x63, 0x98, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0x5b, 0x78, 0x5a, 0x00, 0x00, 0x00, 
  0x5b, 0x78, 0x0c, 0x63, 0x78, 0xe8, 0x63, 0x78, 0xff, 0x7c, 0x18, 0xff, 0xb5, 0x99, 0xff, 0xbd, 0xfa, 0xff, 0xb5, 0xb9, 0xff, 0xc6, 0x3b, 0xff, 0xc6, 0x3b, 0xff, 0xbd, 0xda, 0xff, 0xc6, 0x1a, 0xff, 0xb5, 0xba, 0xff, 0x7c, 0x18, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0xe6, 0x63, 0xb7, 0x0b, 
  0x63, 0x78, 0x61, 0x63, 0x78, 0xff, 0x63, 0x78, 0xff, 0xef, 0x7e, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xef, 0x7e, 0xff, 0x5b, 0x57, 0xff, 0x63, 0x78, 0xff, 0x63, 0x78, 0x5e, 
  0x63, 0x78, 0xa6, 0x63, 0x78, 0xff, 0x94, 0xd9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x97, 0xff, 0x5b, 0x57, 0xff, 0x63, 0x78, 0xa4, 
  0x63, 0x78, 0xc4, 0x63, 0x78, 0xff, 0xc6, 0x5b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6, 0x9b, 0xff, 0xc6, 0x1a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x3b, 0xff, 0xd6, 0x9c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x5c, 0xff, 0x52, 0xf4, 0xff, 0x5b, 0x37, 0xc5, 
  0x63, 0x78, 0xc3, 0x63, 0x78, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x52, 0xd0, 0xff, 0x42, 0x6f, 0xff, 0xef, 0x7e, 0xff, 0xef, 0x7e, 0xff, 0x4a, 0x91, 0xff, 0x5b, 0x13, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbf, 0xff, 0x52, 0xf4, 0xff, 0x5b, 0x15, 0xc7, 
  0x63, 0x78, 0xa5, 0x6b, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0xb9, 0xff, 0x9c, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9d, 0x18, 0xff, 0xb5, 0xda, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x63, 0x56, 0xff, 0x5b, 0x36, 0xa8, 
  0x5b, 0x78, 0x5f, 0x73, 0xd8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfd, 0xff, 0xef, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x7e, 0xff, 0xde, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6b, 0xd7, 0xff, 0x5b, 0x57, 0x5f, 
  0x5b, 0x78, 0x0c, 0x63, 0x78, 0xe7, 0x84, 0x58, 0xff, 0xde, 0xdc, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x38, 0xff, 0x6b, 0x94, 0xff, 0x84, 0x36, 0xff, 0x84, 0x36, 0xff, 0x6b, 0xb5, 0xff, 0xa5, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfe, 0xff, 0x84, 0x79, 0xff, 0x5b, 0x57, 0xe7, 0x63, 0xb7, 0x0b, 
  0x00, 0x00, 0x00, 0x5b, 0x78, 0x5a, 0x63, 0x78, 0xff, 0x53, 0x15, 0xff, 0x4a, 0xb1, 0xff, 0x4a, 0xb1, 0xff, 0x4a, 0xb2, 0xff, 0x4a, 0xb2, 0xff, 0x52, 0xd3, 0xff, 0x52, 0xf4, 0xff, 0x53, 0x15, 0xff, 0x5b, 0x36, 0xff, 0x5b, 0x36, 0xff, 0x5b, 0x57, 0xff, 0x63, 0x78, 0x58, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x78, 0x80, 0x63, 0x78, 0xff, 0x5b, 0x15, 0xff, 0x4a, 0xb2, 0xff, 0x4a, 0xb2, 0xff, 0x52, 0xd3, 0xff, 0x52, 0xf4, 0xff, 0x52, 0xf4, 0xff, 0x53, 0x15, 0xff, 0x5b, 0x36, 0xff, 0x5b, 0x57, 0xff, 0x63, 0x78, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x78, 0x5a, 0x63, 0x78, 0xe7, 0x5b, 0x36, 0xff, 0x52, 0xd3, 0xff, 0x52, 0xf4, 0xff, 0x52, 0xf4, 0xff, 0x53, 0x15, 0xff, 0x5b, 0x36, 0xff, 0x5b, 0x57, 0xe7, 0x63, 0x78, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0xb7, 0x0b, 0x63, 0x78, 0x5d, 0x5b, 0x15, 0xab, 0x52, 0xf4, 0xcb, 0x5b, 0x35, 0xc9, 0x5b, 0x36, 0xa8, 0x5b, 0x37, 0x60, 0x63, 0xb7, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x6a, 0x55, 0x0c, 0xc1, 0x6b, 0x5b, 0x5f, 0xc0, 0x6b, 0x5d, 0xa5, 0xc0, 0x6b, 0x5c, 0xc3, 0xc0, 0x6b, 0x5c, 0xc3, 0xc0, 0x6b, 0x5d, 0xa5, 0xc1, 0x6b, 0x5b, 0x5f, 0xbf, 0x6a, 0x55, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x6c, 0x5b, 0x5c, 0xc0, 0x6b, 0x5c, 0xe8, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xe7, 0xc1, 0x6c, 0x5b, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x6c, 0x5c, 0x82, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xbf, 0x6c, 0x5c, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xbf, 0x6c, 0x5b, 0x5c, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6e, 0x5f, 0xff, 0xbf, 0x6e, 0x61, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xbf, 0x6e, 0x61, 0xff, 0xc0, 0x6e, 0x5f, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc1, 0x6c, 0x5b, 0x5a, 0x00, 0x00, 0x00, 0x00, 
  0xbf, 0x6a, 0x55, 0x0c, 0xc0, 0x6b, 0x5c, 0xe8, 0xc0, 0x6b, 0x5c, 0xff, 0xbf, 0x7f, 0x74, 0xff, 0xc9, 0xb1, 0xac, 0xff, 0xcd, 0xbd, 0xba, 0xff, 0xca, 0xb5, 0xb1, 0xff, 0xd7, 0xc3, 0xbf, 0xff, 0xd9, 0xc3, 0xc0, 0xff, 0xd2, 0xb9, 0xb4, 0xff, 0xd0, 0xbf, 0xbc, 0xff, 0xcd, 0xb2, 0xad, 0xff, 0xc2, 0x80, 0x75, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc0, 0x6c, 0x5c, 0xe6, 0xb9, 0x74, 0x5d, 0x0b, 
  0xc0, 0x6c, 0x5c, 0x61, 0xc0, 0x6b, 0x5c, 0xff, 0xbf, 0x6d, 0x5e, 0xff, 0xef, 0xea, 0xe9, 0xff, 0xf7, 0xf5, 0xf4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf5, 0xf5, 0xff, 0xf1, 0xeb, 0xe9, 0xff, 0xb4, 0x67, 0x59, 0xff, 0xc0, 0x6b, 0x5c, 0xff, 0xc1, 0x6a, 0x5c, 0x5e, 
  0xc0, 0x6c, 0x5c, 0xa6, 0xc0, 0x6b, 0x5c, 0xff, 0xc4, 0x97, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb9, 0x91, 0x8a, 0xff, 0xb5, 0x66, 0x58, 0xff, 0xbf, 0x6b, 0x5c, 0xa4, 
  0xc1, 0x6b, 0x5c, 0xc4, 0xc0, 0x6b, 0x5c, 0xff, 0xd9, 0xc7, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xcf, 0xcd, 0xff, 0xd1, 0xc1, 0xbd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd4, 0xc2, 0xbe, 0xff, 0xe0, 0xd1, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdd, 0xc8, 0xc4, 0xff, 0x9d, 0x5a, 0x4f, 0xff, 0xb5, 0x65, 0x58, 0xc5, 
  0xc0, 0x6b, 0x5c, 0xc3, 0xc0, 0x6b, 0x5c, 0xff, 0xf7, 0xf4, 0xf4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x82, 0x57, 0x4e, 0xff, 0x7a, 0x4a, 0x41, 0xff, 0xf0, 0xea, 0xe9, 0xff, 0xf0, 0xea, 0xe9, 0xff, 0x88, 0x51, 0x47, 0xff, 0x95, 0x60, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf4, 0xf3, 0xff, 0xa2, 0x5d, 0x50, 0xff, 0xaa, 0x61, 0x55, 0xc7, 
  0xc0, 0x6b, 0x5d, 0xa5, 0xc0, 0x72, 0x64, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0xb2, 0xae, 0xff, 0xb9, 0x9d, 0x98, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xc0, 0xa0, 0x9a, 0xff, 0xd1, 0xb7, 0xb2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xaf, 0x69, 0x5d, 0xff, 0xb2, 0x63, 0x57, 0xa8, 
  0xc1, 0x6b, 0x5b, 0x5f, 0xbf, 0x79, 0x6d, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe4, 0xda, 0xd8, 0xff, 0xf0, 0xeb, 0xea, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xeb, 0xea, 0xff, 0xeb, 0xdd, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0xfd, 0xff, 0xba, 0x76, 0x6a, 0xff, 0xb7, 0x66, 0x56, 0x5f, 
  0xbf, 0x6a, 0x55, 0x0c, 0xc0, 0x6b, 0x5c, 0xe7, 0xbc, 0x89, 0x7f, 0xff, 0xe3, 0xd8, 0xd6, 0xff, 0xfd, 0xfc, 0xfc, 0xff, 0xbe, 0xa3, 0x9e, 0xff, 0x9c, 0x6e, 0x66, 0xff, 0xad, 0x83, 0x7c, 0xff, 0xb0, 0x84, 0x7c, 0xff, 0xa9, 0x73, 0x6a, 0xff, 0xcc, 0xaa, 0xa3, 0xff, 0xfe, 0xfc, 0xfc, 0xff, 0xed, 0xdd, 0xda, 0xff, 0xc5, 0x8c, 0x82, 0xff, 0xb8, 0x68, 0x58, 0xe7, 0xb9, 0x74, 0x5d, 0x0b, 
  0x00, 0x00, 0x00, 0x00, 0xc1, 0x6c, 0x5b, 0x5a, 0xc0, 0x6b, 0x5c, 0xff, 0xa6, 0x5e, 0x52, 0xff, 0x87, 0x54, 0x4a, 0xff, 0x8a, 0x54, 0x4b, 0xff, 0x8d, 0x53, 0x49, 0xff, 0x92, 0x55, 0x4a, 0xff, 0x97, 0x57, 0x4c, 0xff, 0x9c, 0x5a, 0x4e, 0xff, 0xa4, 0x60, 0x53, 0xff, 0xac, 0x64, 0x58, 0xff, 0xb0, 0x63, 0x55, 0xff, 0xb8, 0x67, 0x59, 0xff, 0xbf, 0x6b, 0x5d, 0x58, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x6c, 0x5c, 0x80, 0xc0, 0x6b, 0x5c, 0xff, 0xaa, 0x61, 0x54, 0xff, 0x8d, 0x53, 0x49, 0xff, 0x92, 0x55, 0x4a, 0xff, 0x97, 0x57, 0x4c, 0xff, 0x9c, 0x5a, 0x4e, 0xff, 0xa2, 0x5d, 0x50, 0xff, 0xaa, 0x60, 0x53, 0xff, 0xb0, 0x63, 0x55, 0xff, 0xb8, 0x67, 0x59, 0xff, 0xc1, 0x6a, 0x5c, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x6c, 0x5b, 0x5a, 0xc0, 0x6b, 0x5c, 0xe7, 0xaf, 0x63, 0x55, 0xff, 0x98, 0x58, 0x4c, 0xff, 0x9c, 0x5a, 0x4e, 0xff, 0xa2, 0x5d, 0x50, 0xff, 0xaa, 0x60, 0x53, 0xff, 0xb0, 0x63, 0x55, 0xff, 0xb8, 0x68, 0x58, 0xe7, 0xbf, 0x6b, 0x5d, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb9, 0x74, 0x5d, 0x0b, 0xc0, 0x6b, 0x5d, 0x5d, 0xab, 0x5f, 0x54, 0xab, 0xa3, 0x5d, 0x50, 0xcb, 0xab, 0x62, 0x54, 0xc9, 0xb2, 0x63, 0x57, 0xa8, 0xb7, 0x65, 0x58, 0x60, 0xb9, 0x74, 0x5d, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t ui_img_discord_png = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 16,
  .header.h = 16,
  .data_size = 256 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = ui_img_discord_png_map,
};
