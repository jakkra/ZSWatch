
// File generated by bin2lvgl
// developed by fbiego.
// https://github.com/fbiego
// modified by Daniel Kampert.
// https://github.com/kampi
// Watchface: 80_2_dial

#include <lvgl.h>

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

const LV_ATTRIBUTE_MEM_ALIGN uint8_t face_80_2_dial_64_119072_data_0[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x85,0x51,0xFF,0x6C,0x4E,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x53,0x4B,0xFF,0x19,0x23,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x88,0xFF,0xC7,0xFA,0xFF,
	0x5B,0xCC,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x64,0x0D,0xFF,0xBF,0xDA,0xFF,0x08,0x61,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0xC5,0xFF,0xC7,0xFA,0xFF,0x4B,0x2A,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x6C,0x8F,0xFF,0xAF,0x17,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x82,0xFF,0xC7,0xFA,0xFF,0x53,0x4B,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x85,0x72,0xFF,0xA6,0xB6,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xC2,0xFF,0x64,0x2D,0xFF,0x85,0x72,0xFF,0x6C,0x8F,0xFF,0x21,0x64,0xFF,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5B,0xED,0xFF,0x8D,0xB3,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xC2,0xFF,0x53,0x6B,0xFF,0x21,0x64,0xFF,0xC7,0xFA,0xFF,0x53,0x6B,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x4B,0x0A,0xFF,0x08,0x81,0xFF,0x74,0xAF,0xFF,0xAF,0x38,0xFF,0x96,0x14,0xFF,0x85,0x52,0xFF,0x8D,0xD3,0xFF,0xAF,0x38,0xFF,0x85,0x51,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x44,0xFF,0xBF,0xDA,0xFF,
	0x95,0xF4,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x95,0xF4,0xFF,0x7D,0x31,0xFF,0x10,0xA2,0xFF,0xC7,0xFA,0xFF,0x53,0x6B,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0xC9,0xFF,0xB7,0x38,0xFF,0x29,0xC6,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x19,0x03,0xFF,0x9E,0x75,0xFF,0x96,0x34,0xFF,0x00,0x00,0x00,0x32,0x06,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC7,0xFA,0xFF,0x8D,0xD3,0xFF,0x00,0x00,0x00,0x21,0x85,0xFF,0x10,0xC2,0xFF,0x8D,0xD3,0xFF,0x7D,0x31,0xFF,
	0x08,0x41,0xFF,0xC7,0xFA,0xFF,0x4A,0xE9,0xFF,0x00,0x00,0x00,0x08,0x61,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xB9,0xFF,0x6C,0x4E,0xFF,0x9E,0x55,0xFF,0x6C,0x8F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xFF,0xBF,0x99,0xFF,0x74,0xAF,0xFF,0x19,0x23,0xFF,0xC7,0xFA,0xFF,0x10,0xA2,0xFF,0x85,0x92,0xFF,0x85,0x72,0xFF,0x08,0x41,0xFF,0xC7,0xFA,0xFF,0x4B,0x4B,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3A,0x68,0xFF,0xAF,0x17,0xFF,0x08,0x81,0xFF,0xBF,0x99,0xFF,0x5B,0xAC,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x41,0xFF,0xC7,0xFA,0xFF,0x63,0xED,0xFF,0x21,0x85,0xFF,0xC7,0xFA,0xFF,0x00,0x00,0x00,0x8D,0xB3,0xFF,0x74,0xD0,0xFF,0x10,0xA2,0xFF,0xC7,0xFA,0xFF,0x42,0xC9,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xFF,0x96,0x34,0xFF,
	0x00,0x00,0x00,0x10,0xE2,0xFF,0xAF,0x17,0xFF,0x5B,0xAC,0xFF,0x19,0x03,0xFF,0x00,0x00,0x00,0x08,0x81,0xFF,0xC7,0xFA,0xFF,0x53,0x6B,0xFF,0x31,0xE6,0xFF,0xC7,0xFA,0xFF,0x00,0x20,0xFF,0x8D,0xD3,0xFF,0x74,0xD0,0xFF,0x08,0x61,0xFF,0xC7,0xFA,0xFF,0x42,0xC9,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xFF,0x96,0x14,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x19,0x24,0xFF,0xC7,0xFA,0xFF,0x42,0x88,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
	0x08,0x82,0xFF,0xC7,0xFA,0xFF,0x21,0x64,0xFF,0x53,0x4B,0xFF,0xC7,0xFA,0xFF,0x00,0x00,0x00,0x96,0x14,0xFF,0x74,0xD0,0xFF,0x19,0x03,0xFF,0xC7,0xFA,0xFF,0x4B,0x2A,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0xA5,0xFF,0xAF,0x17,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x5B,0xAC,0xFF,0x96,0x34,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4B,0x0A,0xFF,0xA6,0xB6,0xFF,0x00,0x00,0x00,0x5B,0xCC,0xFF,0xC7,0xFA,0xFF,0x00,0x41,0xFF,
	0x8D,0xD3,0xFF,0x74,0xF0,0xFF,0x21,0x64,0xFF,0x42,0xC9,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA6,0xD7,0xFF,0x7D,0x11,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x9E,0x55,0xFF,0x74,0xAF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x64,0xFF,0x96,0x34,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x64,0x0D,0xFF,0xC7,0xFA,0xFF,0x00,0x00,0x00,0x95,0xF4,0xFF,0x8D,0xB3,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x85,0x51,0xFF,0xB7,0x99,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x53,0x6B,0xFF,0xB7,0x79,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x64,0x0D,0xFF,0xA6,0x96,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x64,0x0D,0xFF,0xC7,0xFA,0xFF,0x08,0x61,0xFF,0x74,0xAF,0xFF,0xB7,0x58,0xFF,0x7D,0x10,0xFF,0x6C,0x4E,0xFF,0x74,0xD0,0xFF,0xAE,0xF7,0xFF,0x9E,0x95,0xFF,0x08,0x82,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xA6,0xD7,0xFF,0x95,0xF4,0xFF,0x08,0x81,0xFF,0x00,0x00,0x00,0x4B,0x2A,0xFF,0xC7,0xFA,0xFF,0x3A,0x68,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x64,0x0D,0xFF,0xC7,0xFA,0xFF,0x00,0x00,0x00,0x29,0xC6,0xFF,0x8D,0xB3,0xFF,0x96,0x14,0xFF,0x8D,0xD3,0xFF,0x53,0x8B,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xFF,0x8D,0xB3,0xFF,0xAE,0xF7,0xFF,0xA6,0x96,0xFF,0xAF,0x17,0xFF,0x3A,0x88,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x64,0x0D,0xFF,0xC7,0xFA,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0xA5,0xFF,0x3A,0x68,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x74,0xAF,0xFF,
	0xC7,0xFA,0xFF,0x29,0xE6,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7D,0x10,0xFF,0x8D,0xD3,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,
    };

const lv_img_dsc_t face_80_2_dial_64_119072_0 = {
    .header.always_zero = 0,
    .header.w = 25,
    .header.h = 18,
    .data_size = sizeof(face_80_2_dial_64_119072_data_0),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = face_80_2_dial_64_119072_data_0};
