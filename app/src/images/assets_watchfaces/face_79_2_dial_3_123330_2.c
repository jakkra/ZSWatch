
// File generated by bin2lvgl
// developed by fbiego.
// https://github.com/fbiego
// modified by Daniel Kampert.
// https://github.com/kampi
// Watchface: 79_2_dial

#include <lvgl.h>

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

const LV_ATTRIBUTE_MEM_ALIGN uint8_t face_79_2_dial_3_123330_data_2[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x19,0x65,0xFF,0x32,0x29,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xE3,0xFF,0x4B,0x0D,0xFF,0x6D,0x15,0xFF,0x21,0xE7,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xE3,0xFF,0x3A,0xAB,0xFF,0x5C,0x31,0xFF,0x8E,0x7B,0xFF,0x9F,0x7F,0xFF,0x9F,0x7F,0xFF,0x9F,0x7F,0xFF,0x9F,0x7F,0xFF,0x85,0xF9,0xFF,0x5C,0x31,0xFF,0x64,0x93,0xFF,0x19,0x65,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0xE7,0xFF,0x00,0x00,0x00,0x4B,0xAF,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0x9F,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0x9F,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0x3A,0xAB,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x32,0x29,0xFF,0x29,0xC7,0xFF,0x7D,0x77,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x3F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x3F,0xFF,0xA7,0x5F,0xFF,0xA7,0x5F,0xFF,0xA7,0x3F,0xFF,0xA7,0x5F,0xFF,0x3A,0xAB,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3A,0xAB,0xFF,0x29,0xC7,0xFF,0x85,0xD9,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,
	0xA7,0x3F,0xFF,0xA7,0x3F,0xFF,0x3A,0xAB,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3A,0xAB,0xFF,0x3A,0xAB,0xFF,0x6D,0x15,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,
	0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0xA7,0x1F,0xFF,0x19,0x65,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x8B,0xFF,0x6C,0x53,0xFF,0x5B,0xF1,0xFF,0xAE,0xFF,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,
	0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0xAF,0x1F,0xFF,0x85,0xD9,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x45,0xFF,0x9E,0x9D,0xFF,0x42,0x8B,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,
	0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0xAE,0xFF,0xFF,0x42,0x8B,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xC3,0xFF,0x32,0x29,0xFF,0x9E,0x9D,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0x9E,0x9D,0xFF,
	0x6C,0x53,0xFF,0x32,0x29,0xFF,0x00,0x00,0x00,0x42,0x8B,0xFF,0x9E,0x9D,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0x8D,0x99,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAE,0x3D,0xFF,0xAE,0xDF,0xFF,0xAE,0xBF,0xFF,0xAE,0xDF,0xFF,0xAE,0xBF,0xFF,0xAE,0xBF,0xFF,0xAE,0xBF,0xFF,0xAE,0xBF,0xFF,
	0x63,0xB1,0xFF,0x08,0x62,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x45,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xDF,0xFF,0xAE,0xBF,0xFF,0x08,0x62,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x8B,0xFF,0x9D,0xDB,0xFF,0x8D,0x99,0xFF,0x5B,0x4F,0xFF,0x63,0xB1,0xFF,0x9D,0xDB,0xFF,
	0x9D,0xDB,0xFF,0x21,0x45,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x62,0xFF,0xB6,0xBF,0xFF,0xB6,0xBF,0xFF,0xB6,0xBF,0xFF,0xB6,0xBF,0xFF,0xB6,0xBF,0xFF,0xB6,0xBF,0xFF,0xB6,0xBF,0xFF,0xB6,0xBF,0xFF,0x29,0xA7,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x8B,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0xBF,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0x29,0xA7,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8C,0xD7,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0xB6,0x9F,0xFF,0x29,0xA7,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x87,0xFF,0x52,0xAD,0xFF,0xAE,0x3D,0xFF,0xBE,0x7F,0xFF,0xBE,0x7F,0xFF,0xBE,0x7F,0xFF,0xBE,0x7F,0xFF,0xBE,0x7F,0xFF,0xBE,0x7F,0xFF,0xBE,0x7F,0xFF,0x29,0xA7,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8C,0xD7,0xFF,0x31,0x87,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0x08,0x62,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x4B,0xFF,0x42,0x4B,0xFF,0x6B,0x71,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x5F,0xFF,0xBE,0x3F,0xFF,0xBE,0x5F,0xFF,0x9D,0x39,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x62,0xFF,0x21,0x25,0xFF,0x00,0x00,0x00,0xB5,0xDD,0xFF,0xBE,0x3F,0xFF,0xC6,0x3E,0xFF,0xBE,0x3F,0xFF,0xBE,0x3F,0xFF,0xBE,0x3F,0xFF,0xBE,0x3F,0xFF,0xBE,0x3F,0xFF,0x42,0x4B,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x52,0xAD,0xFF,0x00,0x00,0x00,0x42,0x4B,0xFF,0xC6,0x1F,0xFF,0xC6,0x1F,0xFF,0xC6,0x1F,0xFF,0xC6,0x1F,0xFF,0xC6,0x1F,0xFF,0xC6,0x1F,0xFF,0xC6,0x1F,0xFF,0x9C,0xF9,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAD,0x5B,0xFF,0xC5,0xFE,0xFF,0xC5,0xFE,0xFF,0xC5,0xFF,0xFF,0xC5,0xFF,0xFF,0xC5,0xFF,0xFF,0xC5,0xFE,0xFF,0xC6,0x1F,0xFF,0x31,0x87,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x0F,0xFF,0xC5,0xFE,0xFF,0xC5,0xFE,0xFF,0xC5,0xFF,0xFF,0xC5,0xDF,0xFF,0xC5,0xFE,0xFF,0xC5,0xFE,0xFF,0xC5,0xFF,0xFF,
	0x6B,0x71,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xC3,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4A,0x2B,0xFF,0xCD,0xDF,0xFF,0xCD,0xDE,0xFF,0xCD,0xDF,0xFF,0xCD,0xDE,0xFF,0xCD,0xDE,0xFF,0xCD,0xDE,0xFF,
	0xCD,0xDE,0xFF,0xB4,0xFB,0xFF,0x08,0x61,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x52,0xAD,0xFF,0xC5,0x3D,0xFF,0x00,0x00,0x00,0x29,0x05,0xFF,0x83,0x53,0xFF,0xCD,0xDE,0xFF,0xCD,0xBF,0xFF,0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,
	0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,0x21,0x25,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x41,0xFF,0x9C,0x57,0xFF,0x83,0x53,0xFF,0x08,0x41,0xFF,0x00,0x00,0x00,0x73,0x31,0xFF,0xCD,0xBF,0xFF,0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,
	0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,0xCD,0xBE,0xFF,0xCD,0x9E,0xFF,0x52,0xAD,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x67,0xFF,0xAC,0x79,0xFF,0x41,0xA9,0xFF,0x08,0x62,0xFF,0x62,0x4D,0xFF,0xB4,0xFB,0xFF,0xD5,0x9E,0xFF,0xD5,0x9E,0xFF,0xD5,0x9E,0xFF,
	0xD5,0x9E,0xFF,0xD5,0x9E,0xFF,0xD5,0x9E,0xFF,0xD5,0x9E,0xFF,0xD5,0x9E,0xFF,0x93,0xB5,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6A,0xCF,0xFF,0x6A,0xCF,0xFF,0x00,0x00,0x00,0x93,0xB5,0xFF,0xC5,0x3D,0xFF,0xD5,0x7E,0xFF,0xD5,0x7E,0xFF,0xD5,0x7E,0xFF,
	0xD5,0x7E,0xFF,0xD5,0x7E,0xFF,0xD5,0x7E,0xFF,0xD5,0x7E,0xFF,0xD5,0x7E,0xFF,0xD5,0x7E,0xFF,0xAC,0x79,0xFF,0x08,0x41,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xA3,0xFF,0x18,0xA3,0xFF,0x00,0x00,0x00,0x51,0xEB,0xFF,0xD5,0x7E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,
	0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xCC,0xFC,0xFF,0x29,0x05,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x05,0xFF,0xCC,0xFC,0xFF,0xDD,0x5E,0xFF,
	0xD5,0x5E,0xFF,0xDD,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xDD,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0xD5,0x5E,0xFF,0x31,0x67,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x05,0xFF,0xCC,0xFC,0xFF,
	0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xCC,0xFC,0xFF,0xA4,0x17,0xFF,0x41,0xA9,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x05,0xFF,
	0xCC,0xFC,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x3E,0xFF,0xDD,0x3E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xAB,0xB7,0xFF,0x00,0x00,0x00,0x39,0x47,0xFF,0x51,0xEB,0xFF,0x00,0x00,0x00,0x08,0x41,0xFF,0x41,0xA9,0xFF,0x08,0x41,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x51,0xEB,0xFF,0x83,0x53,0xFF,0xC4,0x7A,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDC,0xFE,0xFF,0xDC,0xFE,0xFF,0xDD,0x1E,0xFF,0xDC,0xFE,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDD,0x1E,0xFF,0xDC,0xFE,0xFF,0xDD,0x1E,0xFF,0xD4,0x9C,0xFF,0x62,0x4D,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x08,0x41,0xFF,0x9B,0x55,0xFF,0x9B,0x55,0xFF,0xD4,0x9C,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0xE4,0xFE,0xFF,0x82,0xB1,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x59,0xCB,0xFF,0xC4,0x7A,0xFF,0xAB,0xB7,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xFE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xFE,0xFF,0xE4,0xDE,0xFF,0x28,0xE5,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x39,0x47,0xFF,0xD4,0x9C,0xFF,0x92,0xF3,0xFF,0xE4,0xBE,0xFF,0xE4,0xDE,0xFF,0xE4,0xBE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xBE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xE4,0xDE,0xFF,0xD4,0x9C,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBB,0xB8,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0xE4,0xBE,0xFF,0x92,0xF3,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x49,0x69,0xFF,0xEC,0xBE,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,0xEC,0xBE,0xFF,
	0xEC,0xBE,0xFF,0x18,0x83,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0xE5,0xFF,0xDC,0x5C,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,
	0xEC,0x9E,0xFF,0xEC,0x9E,0xFF,0x59,0xCB,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDC,0x3C,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xB3,0x57,0xFF,0xA3,0x15,0xFF,0x72,0x4F,0xFF,0x72,0x4F,0xFF,
	0x72,0x4F,0xFF,0x72,0x4F,0xFF,0x69,0xED,0xFF,0x18,0x83,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0xE5,0xFF,0xBB,0xB8,0xFF,0xF4,0x5E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xEC,0x7E,0xFF,0xB3,0x57,0xFF,0x72,0x4F,0xFF,0x49,0x69,0xFF,0x18,0x83,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x59,0xCB,0xFF,0xBB,0xB8,0xFF,0xF4,0x5E,0xFF,0xF4,0x5E,0xFF,0xF4,0x5E,0xFF,0xF4,0x5E,0xFF,0xF4,0x5E,0xFF,0xA3,0x15,0xFF,0x59,0xCB,0xFF,0x08,0x41,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x41,0xFF,0x39,0x27,0xFF,0x39,0x27,0xFF,0x28,0xE5,0xFF,0x08,0x41,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };

const lv_img_dsc_t face_79_2_dial_3_123330_2 = {
    .header.always_zero = 0,
    .header.w = 34,
    .header.h = 44,
    .data_size = sizeof(face_79_2_dial_3_123330_data_2),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = face_79_2_dial_3_123330_data_2};
