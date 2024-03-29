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

#ifndef LV_ATTRIBUTE_IMG_GOOGLE_CALENDAR_ICON
#define LV_ATTRIBUTE_IMG_GOOGLE_CALENDAR_ICON
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_GOOGLE_CALENDAR_ICON uint8_t google_calendar_icon_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x53, 0xc3, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x2f, 0xff, 0x2f, 0xff, 0x2f, 0xff, 0x2f, 0xc3, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x2f, 0xff, 0x2f, 0xff, 0x2f, 0xff, 0x2f, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x2f, 0xff, 0x2f, 0xff, 0x2f, 0xff, 0x2f, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x53, 0xfe, 0x97, 0xff, 0x97, 0xff, 0x97, 0xff, 0x97, 0xff, 0x97, 0xff, 0x97, 0xff, 0x97, 0xff, 0x97, 0xff, 0x73, 0xfe, 0x72, 0xff, 0x72, 0xff, 0x72, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xbb, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xbb, 0xff, 0x77, 0xff, 0xdf, 0xff, 0x77, 0xff, 0x77, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbb, 0xff, 0x77, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x77, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbb, 0xff, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xdf, 0xff, 0x77, 0xff, 0xdf, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x9b, 0xff, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x53, 0xff, 0x53, 0xff, 0x53, 0xff, 0x97, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 
  0x32, 0xff, 0x32, 0xff, 0x32, 0xff, 0x56, 0xfe, 0x7a, 0xff, 0x7a, 0xff, 0x7a, 0xff, 0x7a, 0xff, 0x7a, 0xff, 0x7a, 0xff, 0x7a, 0xff, 0x7a, 0xff, 0xd1, 0xff, 0xed, 0xff, 0xed, 0xfe, 0xed, 0xb4, 
  0x31, 0xff, 0x31, 0xff, 0x31, 0xff, 0x31, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0xcd, 0xff, 0xe9, 0xff, 0xe9, 0xa2, 0xe5, 0x16, 
  0x31, 0xff, 0x31, 0xff, 0x31, 0xff, 0x31, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0xcd, 0xff, 0xe9, 0xa2, 0xe9, 0x13, 0x00, 0x00, 
  0x31, 0xc3, 0x31, 0xff, 0x31, 0xff, 0x31, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0xad, 0xb4, 0xe5, 0x16, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x3f, 0x44, 0xc3, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x9c, 0x23, 0xff, 0x5a, 0x1b, 0xff, 0x5a, 0x1b, 0xff, 0x5a, 0x1b, 0xc3, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x9c, 0x23, 0xff, 0x5a, 0x1b, 0xff, 0x5a, 0x1b, 0xff, 0x5a, 0x1b, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x9c, 0x23, 0xff, 0x5a, 0x1b, 0xff, 0x5a, 0x1b, 0xff, 0x5a, 0x1b, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x7f, 0x54, 0xfe, 0x3f, 0x75, 0xff, 0x3f, 0x75, 0xff, 0x3f, 0x75, 0xff, 0x3f, 0x75, 0xff, 0x3f, 0x75, 0xff, 0x3f, 0x75, 0xff, 0x3f, 0x75, 0xff, 0x3e, 0x75, 0xff, 0x57, 0x5c, 0xfe, 0xf4, 0x53, 0xff, 0xf4, 0x53, 0xff, 0xf4, 0x53, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x75, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0x69, 0xfe, 0xff, 0xc1, 0xfd, 0xff, 0xc1, 0xfd, 0xff, 0xc1, 0xfd, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x75, 0xff, 0xdf, 0xff, 0xff, 0x1f, 0xd7, 0xff, 0xff, 0x95, 0xff, 0x1f, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf7, 0xff, 0x1f, 0xd7, 0xff, 0xff, 0xff, 0xff, 0x89, 0xfe, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x75, 0xff, 0xbf, 0xf7, 0xff, 0xff, 0x95, 0xff, 0x7f, 0xae, 0xff, 0x1e, 0x65, 0xff, 0x1f, 0xd7, 0xff, 0x5e, 0x75, 0xff, 0x1e, 0x65, 0xff, 0xdf, 0xff, 0xff, 0x89, 0xfe, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x75, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0x7f, 0xae, 0xff, 0x5e, 0x75, 0xff, 0xbf, 0xf7, 0xff, 0xdf, 0xc6, 0xff, 0x5e, 0x75, 0xff, 0xdf, 0xff, 0xff, 0x89, 0xfe, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x75, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0x7f, 0xae, 0xff, 0x5e, 0x75, 0xff, 0x9f, 0xe7, 0xff, 0x9f, 0xe7, 0xff, 0x5e, 0x75, 0xff, 0xdf, 0xff, 0xff, 0x89, 0xfe, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x75, 0xff, 0x9f, 0xe7, 0xff, 0xff, 0x95, 0xff, 0xdf, 0xc6, 0xff, 0x1e, 0x65, 0xff, 0x1f, 0xd7, 0xff, 0x9f, 0xe7, 0xff, 0x5e, 0x75, 0xff, 0xdf, 0xff, 0xff, 0x89, 0xfe, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 
  0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x44, 0xff, 0x3f, 0x75, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xc6, 0xff, 0x9e, 0x85, 0xff, 0x7f, 0xae, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf7, 0xff, 0xdf, 0xc6, 0xff, 0xdf, 0xff, 0xff, 0x89, 0xfe, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 0xe0, 0xfd, 0xff, 
  0x3e, 0x44, 0xff, 0x3e, 0x44, 0xff, 0x3e, 0x44, 0xff, 0x3e, 0x75, 0xff, 0xdf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0x89, 0xfe, 0xff, 0xc1, 0xfd, 0xff, 0xc1, 0xfd, 0xff, 0xc1, 0xfd, 0xff, 
  0x0d, 0x24, 0xff, 0x0d, 0x24, 0xff, 0x0d, 0x24, 0xff, 0x8e, 0x3c, 0xfe, 0xf0, 0x6d, 0xff, 0x10, 0x6e, 0xff, 0x10, 0x6e, 0xff, 0x10, 0x6e, 0xff, 0x10, 0x6e, 0xff, 0x10, 0x6e, 0xff, 0x10, 0x6e, 0xff, 0xf0, 0x6d, 0xff, 0xc8, 0xd3, 0xff, 0x05, 0xf3, 0xff, 0x25, 0xf3, 0xfe, 0x84, 0xf3, 0xb4, 
  0x07, 0x1c, 0xff, 0x07, 0x1c, 0xff, 0x07, 0x1c, 0xff, 0x68, 0x24, 0xff, 0x4a, 0x35, 0xff, 0x4a, 0x35, 0xff, 0x4a, 0x35, 0xff, 0x4a, 0x35, 0xff, 0x4a, 0x35, 0xff, 0x4a, 0x35, 0xff, 0x4a, 0x35, 0xff, 0x2a, 0x3d, 0xff, 0xe8, 0xba, 0xff, 0x07, 0xf2, 0xff, 0x07, 0xf2, 0xa2, 0x87, 0xf1, 0x16, 
  0x07, 0x1c, 0xff, 0x07, 0x1c, 0xff, 0x07, 0x1c, 0xff, 0x68, 0x24, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x2a, 0x3d, 0xff, 0xe8, 0xba, 0xff, 0x07, 0xf2, 0xa2, 0x27, 0xea, 0x13, 0x00, 0x00, 0x00, 
  0x07, 0x1c, 0xc3, 0x07, 0x1c, 0xff, 0x07, 0x1c, 0xff, 0x68, 0x24, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x4a, 0x3d, 0xff, 0x2a, 0x3d, 0xff, 0x48, 0xab, 0xb4, 0x87, 0xf1, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x44, 0x3f, 0xc3, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x23, 0x9c, 0xff, 0x1b, 0x5a, 0xff, 0x1b, 0x5a, 0xff, 0x1b, 0x5a, 0xc3, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x23, 0x9c, 0xff, 0x1b, 0x5a, 0xff, 0x1b, 0x5a, 0xff, 0x1b, 0x5a, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x23, 0x9c, 0xff, 0x1b, 0x5a, 0xff, 0x1b, 0x5a, 0xff, 0x1b, 0x5a, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x54, 0x7f, 0xfe, 0x75, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0x75, 0x3e, 0xff, 0x5c, 0x57, 0xfe, 0x53, 0xf4, 0xff, 0x53, 0xf4, 0xff, 0x53, 0xf4, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xfe, 0x69, 0xff, 0xfd, 0xc1, 0xff, 0xfd, 0xc1, 0xff, 0xfd, 0xc1, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0xff, 0xdf, 0xff, 0xd7, 0x1f, 0xff, 0x95, 0xff, 0xff, 0xd7, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbf, 0xff, 0xd7, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x89, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0xf7, 0xbf, 0xff, 0x95, 0xff, 0xff, 0xae, 0x7f, 0xff, 0x65, 0x1e, 0xff, 0xd7, 0x1f, 0xff, 0x75, 0x5e, 0xff, 0x65, 0x1e, 0xff, 0xff, 0xdf, 0xff, 0xfe, 0x89, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xae, 0x7f, 0xff, 0x75, 0x5e, 0xff, 0xf7, 0xbf, 0xff, 0xc6, 0xdf, 0xff, 0x75, 0x5e, 0xff, 0xff, 0xdf, 0xff, 0xfe, 0x89, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xae, 0x7f, 0xff, 0x75, 0x5e, 0xff, 0xe7, 0x9f, 0xff, 0xe7, 0x9f, 0xff, 0x75, 0x5e, 0xff, 0xff, 0xdf, 0xff, 0xfe, 0x89, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0xe7, 0x9f, 0xff, 0x95, 0xff, 0xff, 0xc6, 0xdf, 0xff, 0x65, 0x1e, 0xff, 0xd7, 0x1f, 0xff, 0xe7, 0x9f, 0xff, 0x75, 0x5e, 0xff, 0xff, 0xdf, 0xff, 0xfe, 0x89, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 
  0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x44, 0x3f, 0xff, 0x75, 0x3f, 0xff, 0xff, 0xdf, 0xff, 0xc6, 0xdf, 0xff, 0x85, 0x9e, 0xff, 0xae, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbf, 0xff, 0xc6, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xfe, 0x89, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 0xfd, 0xe0, 0xff, 
  0x44, 0x3e, 0xff, 0x44, 0x3e, 0xff, 0x44, 0x3e, 0xff, 0x75, 0x3e, 0xff, 0xf7, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xfe, 0x89, 0xff, 0xfd, 0xc1, 0xff, 0xfd, 0xc1, 0xff, 0xfd, 0xc1, 0xff, 
  0x24, 0x0d, 0xff, 0x24, 0x0d, 0xff, 0x24, 0x0d, 0xff, 0x3c, 0x8e, 0xfe, 0x6d, 0xf0, 0xff, 0x6e, 0x10, 0xff, 0x6e, 0x10, 0xff, 0x6e, 0x10, 0xff, 0x6e, 0x10, 0xff, 0x6e, 0x10, 0xff, 0x6e, 0x10, 0xff, 0x6d, 0xf0, 0xff, 0xd3, 0xc8, 0xff, 0xf3, 0x05, 0xff, 0xf3, 0x25, 0xfe, 0xf3, 0x84, 0xb4, 
  0x1c, 0x07, 0xff, 0x1c, 0x07, 0xff, 0x1c, 0x07, 0xff, 0x24, 0x68, 0xff, 0x35, 0x4a, 0xff, 0x35, 0x4a, 0xff, 0x35, 0x4a, 0xff, 0x35, 0x4a, 0xff, 0x35, 0x4a, 0xff, 0x35, 0x4a, 0xff, 0x35, 0x4a, 0xff, 0x3d, 0x2a, 0xff, 0xba, 0xe8, 0xff, 0xf2, 0x07, 0xff, 0xf2, 0x07, 0xa2, 0xf1, 0x87, 0x16, 
  0x1c, 0x07, 0xff, 0x1c, 0x07, 0xff, 0x1c, 0x07, 0xff, 0x24, 0x68, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x2a, 0xff, 0xba, 0xe8, 0xff, 0xf2, 0x07, 0xa2, 0xea, 0x27, 0x13, 0x00, 0x00, 0x00, 
  0x1c, 0x07, 0xc3, 0x1c, 0x07, 0xff, 0x1c, 0x07, 0xff, 0x24, 0x68, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x4a, 0xff, 0x3d, 0x2a, 0xff, 0xab, 0x48, 0xb4, 0xf1, 0x87, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0xf5, 0x85, 0x41, 0xc3, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xdc, 0x6e, 0x22, 0xff, 0xd3, 0x66, 0x17, 0xff, 0xd3, 0x66, 0x17, 0xff, 0xd3, 0x67, 0x19, 0xc3, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xdc, 0x6e, 0x22, 0xff, 0xd3, 0x66, 0x17, 0xff, 0xd3, 0x66, 0x17, 0xff, 0xd3, 0x66, 0x17, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xdc, 0x6e, 0x22, 0xff, 0xd3, 0x66, 0x17, 0xff, 0xd3, 0x66, 0x17, 0xff, 0xd3, 0x66, 0x17, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf5, 0x8d, 0x4e, 0xfe, 0xf7, 0xa4, 0x72, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xf3, 0xa3, 0x70, 0xff, 0xb4, 0x87, 0x5b, 0xfe, 0x9d, 0x7d, 0x52, 0xff, 0x9d, 0x7d, 0x52, 0xff, 0x9d, 0x7d, 0x52, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xff, 0xf9, 0xf6, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xf6, 0xf9, 0xf7, 0xff, 0x49, 0xca, 0xf5, 0xff, 0x07, 0xb8, 0xf7, 0xff, 0x07, 0xb8, 0xf7, 0xff, 0x07, 0xb8, 0xf7, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xff, 0xf9, 0xf6, 0xff, 0xfb, 0xe1, 0xcd, 0xff, 0xf4, 0xbd, 0x93, 0xff, 0xfb, 0xe1, 0xcd, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xfe, 0xf4, 0xec, 0xff, 0xfb, 0xe1, 0xcd, 0xff, 0xf9, 0xfd, 0xfb, 0xff, 0x44, 0xce, 0xfd, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xfe, 0xf4, 0xec, 0xff, 0xf4, 0xbd, 0x93, 0xff, 0xf7, 0xcb, 0xa9, 0xff, 0xf0, 0x9f, 0x62, 0xff, 0xfb, 0xe1, 0xcd, 0xff, 0xf1, 0xa6, 0x6d, 0xff, 0xf0, 0x9f, 0x62, 0xff, 0xf6, 0xf9, 0xf7, 0xff, 0x44, 0xce, 0xfd, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xff, 0xf9, 0xf6, 0xff, 0xf7, 0xcb, 0xa9, 0xff, 0xf1, 0xa6, 0x6d, 0xff, 0xfe, 0xf4, 0xec, 0xff, 0xf9, 0xd6, 0xbc, 0xff, 0xf1, 0xa6, 0x6d, 0xff, 0xf6, 0xf9, 0xf7, 0xff, 0x44, 0xce, 0xfd, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xff, 0xf9, 0xf6, 0xff, 0xff, 0xf9, 0xf6, 0xff, 0xf7, 0xcb, 0xa9, 0xff, 0xf1, 0xa6, 0x6d, 0xff, 0xfd, 0xee, 0xe3, 0xff, 0xfd, 0xee, 0xe3, 0xff, 0xf1, 0xa6, 0x6d, 0xff, 0xf6, 0xf9, 0xf7, 0xff, 0x44, 0xce, 0xfd, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xfd, 0xee, 0xe3, 0xff, 0xf4, 0xbd, 0x93, 0xff, 0xf9, 0xd6, 0xbc, 0xff, 0xf0, 0x9f, 0x62, 0xff, 0xfb, 0xe1, 0xcd, 0xff, 0xfd, 0xee, 0xe3, 0xff, 0xf1, 0xa6, 0x6d, 0xff, 0xf6, 0xf9, 0xf7, 0xff, 0x44, 0xce, 0xfd, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 
  0xf4, 0x85, 0x42, 0xff, 0xf4, 0x85, 0x42, 0xff, 0xf4, 0x83, 0x3f, 0xff, 0xf7, 0xa4, 0x72, 0xff, 0xff, 0xf9, 0xf6, 0xff, 0xf9, 0xd6, 0xbc, 0xff, 0xf3, 0xb1, 0x80, 0xff, 0xf7, 0xcb, 0xa9, 0xff, 0xff, 0xfd, 0xfb, 0xff, 0xfe, 0xf4, 0xec, 0xff, 0xf9, 0xd6, 0xbc, 0xff, 0xf6, 0xf9, 0xf7, 0xff, 0x44, 0xce, 0xfd, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 0x02, 0xbc, 0xfb, 0xff, 
  0xee, 0x84, 0x40, 0xff, 0xee, 0x84, 0x40, 0xff, 0xee, 0x84, 0x40, 0xff, 0xf3, 0xa3, 0x70, 0xff, 0xf9, 0xf8, 0xf2, 0xff, 0xf9, 0xfd, 0xfb, 0xff, 0xf9, 0xfd, 0xfb, 0xff, 0xf9, 0xfd, 0xfb, 0xff, 0xf9, 0xfd, 0xfb, 0xff, 0xf9, 0xfd, 0xfb, 0xff, 0xf9, 0xfd, 0xfb, 0xff, 0xf6, 0xf9, 0xf7, 0xff, 0x44, 0xce, 0xfd, 0xff, 0x07, 0xb8, 0xf7, 0xff, 0x07, 0xb8, 0xf7, 0xff, 0x07, 0xb8, 0xf7, 0xff, 
  0x68, 0x81, 0x22, 0xff, 0x68, 0x81, 0x22, 0xff, 0x68, 0x81, 0x22, 0xff, 0x6e, 0x91, 0x34, 0xfe, 0x7d, 0xbc, 0x68, 0xff, 0x7f, 0xbe, 0x68, 0xff, 0x7f, 0xbe, 0x68, 0xff, 0x7f, 0xbe, 0x68, 0xff, 0x7f, 0xbe, 0x68, 0xff, 0x7f, 0xbe, 0x68, 0xff, 0x7f, 0xbe, 0x68, 0xff, 0x7d, 0xbc, 0x68, 0xff, 0x3e, 0x79, 0xcc, 0xff, 0x27, 0x60, 0xf0, 0xff, 0x28, 0x62, 0xee, 0xfe, 0x23, 0x6f, 0xef, 0xb4, 
  0x35, 0x80, 0x17, 0xff, 0x35, 0x80, 0x17, 0xff, 0x35, 0x80, 0x17, 0xff, 0x3e, 0x8a, 0x1e, 0xff, 0x50, 0xa7, 0x31, 0xff, 0x50, 0xa7, 0x31, 0xff, 0x50, 0xa7, 0x31, 0xff, 0x50, 0xa7, 0x31, 0xff, 0x50, 0xa7, 0x31, 0xff, 0x50, 0xa7, 0x31, 0xff, 0x50, 0xa7, 0x31, 0xff, 0x50, 0xa3, 0x37, 0xff, 0x3d, 0x5c, 0xbb, 0xff, 0x35, 0x40, 0xed, 0xff, 0x36, 0x41, 0xec, 0xa2, 0x3a, 0x2e, 0xf3, 0x16, 
  0x38, 0x80, 0x18, 0xff, 0x38, 0x80, 0x18, 0xff, 0x38, 0x80, 0x18, 0xff, 0x3e, 0x8a, 0x1e, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x52, 0xa5, 0x3a, 0xff, 0x3d, 0x5c, 0xbb, 0xff, 0x36, 0x41, 0xec, 0xa2, 0x36, 0x43, 0xe4, 0x13, 0x00, 0x00, 0x00, 0x00, 
  0x38, 0x80, 0x18, 0xc3, 0x38, 0x80, 0x18, 0xff, 0x38, 0x80, 0x18, 0xff, 0x3e, 0x8a, 0x1e, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x53, 0xa8, 0x34, 0xff, 0x52, 0xa5, 0x3a, 0xff, 0x40, 0x67, 0xa9, 0xb4, 0x3a, 0x2e, 0xf3, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t google_calendar_icon = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 16,
  .header.h = 16,
  .data_size = 256 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = google_calendar_icon_map,
};
