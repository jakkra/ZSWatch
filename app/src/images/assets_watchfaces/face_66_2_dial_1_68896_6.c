
// File generated by bin2lvgl
// developed by fbiego.
// https://github.com/fbiego
// modified by Daniel Kampert.
// https://github.com/kampi
// Watchface: 66_2_dial

#include <lvgl.h>

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

const LV_ATTRIBUTE_MEM_ALIGN uint8_t face_66_2_dial_1_68896_data_6[] = {
	0x02,0x6C,0xFF,0x02,0x4B,0xFF,0x02,0xAD,0xFF,0x03,0x4E,0xFF,0x03,0x6F,0xFF,0x03,0x2E,0xFF,0x02,0xCD,0xFF,0x02,0x8C,0xFF,0x02,0xAD,0xFF,0x02,0xAC,0xFF,0x02,0xCD,0xFF,0x02,0xAD,0xFF,0x02,0xAD,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0x6C,0xFF,0x02,0x6C,0xFF,0x02,0x4C,0xFF,0x02,0x4C,0xFF,0x02,0x6D,0xFF,0x02,0x8D,0xFF,0x02,0x8D,0xFF,0x02,0x6D,0xFF,0x02,0x6D,0xFF,0x02,0x4C,0xFF,0x02,0x4C,0xFF,0x02,0x4C,0xFF,0x02,0x2C,0xFF,0x02,0x2B,0xFF,0x02,0x2B,0xFF,0x02,0x2B,0xFF,0x02,0x2B,0xFF,0x02,0x2B,0xFF,
	0x02,0x0B,0xFF,0x01,0xEB,0xFF,0x01,0xEB,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0x6C,0xFF,0x02,0x6B,0xFF,0x02,0xED,0xFF,0x03,0x6F,0xFF,0xD6,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0xAD,0xFF,0x02,0xAC,0xFF,0x02,0x8C,0xFF,0xD6,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0xAD,0xFF,0x02,0xCD,0xFF,0xBE,0x39,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x02,0xCD,0xFF,0x02,0xAD,0xFF,0x02,0x8C,0xFF,0xBE,0x39,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x02,0xED,0xFF,0x02,0xED,0xFF,0xBE,0x39,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x02,0x8C,0xFF,0xBE,0x39,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x8D,0x56,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x8C,0xF5,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x8D,0x56,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x56,0xFF,0x02,0xED,0xFF,0x02,0xED,0xFF,0x02,0xED,0xFF,0x02,0xCD,0xFF,0x02,0xCD,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0x8C,0xFF,0x02,0x2B,0xFF,0x01,0xEA,0xFF,0x01,0xEA,0xFF,0x01,0xEA,0xFF,0x01,0xCA,0xFF,0x01,0xCA,0xFF,0x02,0x0B,0xFF,0x02,0x4B,0xFF,0x02,0x4C,0xFF,
	0x02,0x0B,0xFF,0x01,0xCA,0xFF,0x01,0xCA,0xFF,0x01,0xEA,0xFF,0x02,0x0B,0xFF,0x02,0x0B,0xFF,0x01,0xEA,0xFF,0x8D,0x56,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0xB6,0xFF,0x03,0x2E,0xFF,0x03,0x2E,0xFF,0x03,0x0D,0xFF,0x02,0xED,0xFF,0x02,0xED,0xFF,0x02,0xCD,0xFF,0x02,0x8C,0xFF,0x02,0x8B,0xFF,0x02,0x6B,0xFF,0x02,0x6B,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0x4B,0xFF,0x01,0xEA,0xFF,0x01,0xEA,0xFF,0x01,0xEA,0xFF,
	0x01,0xC9,0xFF,0x01,0xC9,0xFF,0x02,0x0A,0xFF,0x02,0x4B,0xFF,0x02,0x6C,0xFF,0x02,0x4B,0xFF,0x01,0xEA,0xFF,0x01,0xAA,0xFF,0x01,0xEA,0xFF,0x02,0x2B,0xFF,0x02,0x2C,0xFF,0x8D,0x56,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0xB6,0xFF,0x03,0x6E,0xFF,0x03,0x6E,0xFF,0x03,0x4E,0xFF,0x03,0x4E,0xFF,0x03,0x4E,0xFF,0x03,0x2D,0xFF,0x02,0xED,0xFF,0x02,0xAC,0xFF,0x02,0x8B,0xFF,0x02,0x4B,0xFF,0x02,0x4B,0xFF,0x02,0x4B,0xFF,
	0x02,0x4B,0xFF,0x02,0x4B,0xFF,0x02,0x2B,0xFF,0x01,0xEA,0xFF,0x01,0xC9,0xFF,0x01,0xA9,0xFF,0x01,0xA9,0xFF,0x02,0x0A,0xFF,0x02,0x4B,0xFF,0x02,0x6C,0xFF,0x02,0x6C,0xFF,0x02,0x2B,0xFF,0x01,0xCA,0xFF,0x01,0xEA,0xFF,0x02,0x2B,0xFF,0x8C,0xF5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0xB6,0xFF,0x04,0x4E,0xFF,0x04,0x0E,0xFF,0x03,0xCE,0xFF,0x03,0xAF,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x03,0x4E,0xFF,0x03,0x4E,0xFF,
	0x03,0x2E,0xFF,0x03,0x2D,0xFF,0x02,0xED,0xFF,0x02,0xCD,0xFF,0x02,0x8C,0xFF,0x02,0x4B,0xFF,0x02,0x2B,0xFF,0x02,0x0A,0xFF,0x01,0xEA,0xFF,0x01,0xEA,0xFF,0x01,0xC9,0xFF,0x01,0xA9,0xFF,0x01,0xEA,0xFF,0x02,0x4B,0xFF,0x02,0x6C,0xFF,0x02,0x8C,0xFF,0x02,0x6C,0xFF,0x02,0x0B,0xFF,0x01,0xCA,0xFF,0x8C,0xF5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x95,0xFF,0x03,0x4C,0xFF,0x03,0xED,0xFF,0x04,0x2D,0xFF,0x04,0x8E,0xFF,
	0x04,0xAE,0xFF,0x04,0xAE,0xFF,0x04,0x6E,0xFF,0x03,0xEF,0xFF,0x03,0x6F,0xFF,0x03,0x6E,0xFF,0x03,0x2E,0xFF,0x03,0x0D,0xFF,0x02,0xED,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0x6B,0xFF,0x02,0x2B,0xFF,0x01,0xEA,0xFF,0x01,0xEA,0xFF,0x02,0x0A,0xFF,0x02,0x4B,0xFF,0x02,0x8C,0xFF,0x02,0x8C,0xFF,0x02,0x6C,0xFF,0x8C,0xF5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x56,0xFF,
	0x03,0x2D,0xFF,0x03,0x4E,0xFF,0x03,0x6D,0xFF,0x03,0x8D,0xFF,0x03,0xED,0xFF,0x04,0x2D,0xFF,0x04,0x2D,0xFF,0x04,0x0E,0xFF,0x03,0xCD,0xFF,0x03,0xCD,0xFF,0x03,0xCD,0xFF,0x03,0xCD,0xFF,0x03,0xAE,0xFF,0x03,0xAE,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x03,0x2D,0xFF,0x03,0x0D,0xFF,0x02,0xED,0xFF,0x02,0xCD,0xFF,0x02,0xAC,0xFF,0x02,0x6B,0xFF,0x02,0x2B,0xFF,0x02,0x0A,0xFF,0x02,0x2B,0xFF,0x02,0x4B,0xFF,0x02,0x8C,0xFF,0x8C,0xF5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0xB6,0xFF,0x03,0xAF,0xFF,0x03,0xAF,0xFF,0x03,0x8E,0xFF,0x03,0x4E,0xFF,0x03,0x4E,0xFF,0x03,0x8D,0xFF,0x03,0x6D,0xFF,0x03,0x8D,0xFF,0x03,0x8D,0xFF,0x03,0x8D,0xFF,0x03,0x8D,0xFF,0x03,0x6D,0xFF,0x03,0x6D,0xFF,0x03,0x6D,0xFF,0x03,0x6D,0xFF,0x03,0x2D,0xFF,0x03,0x0D,0xFF,0x02,0xEC,0xFF,0x02,0xCD,0xFF,0x02,0xCD,0xFF,0x02,0xCC,0xFF,0x02,0xAC,0xFF,0x02,0x6B,0xFF,0x02,0x2B,0xFF,0x02,0x2B,0xFF,0x02,0x2B,0xFF,0x02,0x4B,0xFF,0x8C,0xF5,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0xB6,0xFF,0x03,0xEE,0xFF,0x04,0x2F,0xFF,0x04,0x2F,0xFF,0x04,0x0F,0xFF,0x04,0x0F,0xFF,0x03,0xEF,0xFF,0x03,0xAF,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x03,0x6E,0xFF,0x03,0x2D,0xFF,0x03,0x2D,0xFF,0x03,0x0D,0xFF,0x02,0xEC,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0xAB,0xFF,0x02,0x8B,0xFF,0x02,0x6B,0xFF,0x02,0x8B,0xFF,0x02,0x6B,0xFF,0x02,0x8B,0xFF,0x02,0xAB,0xFF,0x02,0xAB,0xFF,
	0x02,0xAB,0xFF,0x02,0xAC,0xFF,0x02,0x8B,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x56,0xFF,0x03,0x8E,0xFF,0x03,0xAE,0xFF,0x03,0xEE,0xFF,0x04,0x0E,0xFF,0x04,0x2E,0xFF,0x04,0x2E,0xFF,0x04,0x4E,0xFF,0x04,0x6E,0xFF,0x04,0x6E,0xFF,0x04,0x6E,0xFF,0x04,0x4E,0xFF,0x04,0x6E,0xFF,0x04,0x2E,0xFF,0x03,0xEF,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x03,0x2D,0xFF,0x03,0x0D,0xFF,0x02,0xEC,0xFF,0x02,0xEC,0xFF,
	0x02,0xEC,0xFF,0x02,0xEC,0xFF,0x02,0xEC,0xFF,0x02,0xCC,0xFF,0x02,0xCC,0xFF,0x02,0xCC,0xFF,0x03,0x0D,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0xB6,0xFF,0x03,0xEF,0xFF,0x03,0xEF,0xFF,0x03,0xEE,0xFF,0x03,0xCF,0xFF,0x03,0xCF,0xFF,0x03,0xEF,0xFF,0x03,0xEF,0xFF,0x03,0xCF,0xFF,0x03,0xAE,0xFF,0x03,0xAE,0xFF,0x03,0x8E,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x03,0x2D,0xFF,0x03,0x2D,0xFF,0x03,0x0D,0xFF,
	0x02,0xEC,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0xAC,0xFF,0x02,0xCC,0xFF,0x02,0xEC,0xFF,0x03,0x2D,0xFF,0x03,0x4E,0xFF,0x03,0x4E,0xFF,0x03,0x6E,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0xB6,0xFF,0x03,0xCF,0xFF,0x04,0x2F,0xFF,0x04,0x4F,0xFF,0x04,0x4F,0xFF,0x04,0x6E,0xFF,0x04,0x6E,0xFF,0x04,0x4F,0xFF,0x04,0x4F,0xFF,0x04,0x2E,0xFF,0x03,0xEF,0xFF,0x03,0xCE,0xFF,0x03,0xAE,0xFF,
	0x03,0xAE,0xFF,0x03,0x8D,0xFF,0x03,0x8D,0xFF,0x03,0x6D,0xFF,0x03,0x6D,0xFF,0x03,0x8D,0xFF,0x03,0xCD,0xFF,0x03,0xCD,0xFF,0x03,0xCD,0xFF,0x03,0xEE,0xFF,0x03,0xEE,0xFF,0x03,0xEF,0xFF,0x03,0xAF,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x56,0xFF,0x03,0x8E,0xFF,0x03,0xCE,0xFF,0x04,0x0E,0xFF,0x04,0x2E,0xFF,0x04,0x6E,0xFF,0x04,0x6E,0xFF,0x04,0x6E,0xFF,0x04,0x8E,0xFF,
	0x04,0x6E,0xFF,0x04,0x4F,0xFF,0x04,0x2E,0xFF,0x04,0x0E,0xFF,0x03,0xEE,0xFF,0x03,0xEE,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x04,0x2E,0xFF,0x04,0x2D,0xFF,0x04,0x2E,0xFF,0x04,0x0E,0xFF,0x04,0x0F,0xFF,0x03,0xCE,0xFF,0x03,0xAF,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x03,0x6E,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x56,0xFF,0x03,0x8E,0xFF,0x03,0xAE,0xFF,0x03,0xAE,0xFF,0x03,0xCE,0xFF,
	0x03,0xEE,0xFF,0x03,0xEE,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x04,0x2F,0xFF,0x04,0x4F,0xFF,0x04,0x2F,0xFF,0x03,0xEE,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x03,0xEE,0xFF,0x03,0xCD,0xFF,0x03,0xAE,0xFF,0x03,0xAE,0xFF,0x03,0x8E,0xFF,0x03,0x6E,0xFF,0x03,0x8D,0xFF,0x03,0x8D,0xFF,0x03,0x8D,0xFF,0x03,0xCE,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x56,0xFF,
	0x03,0xED,0xFF,0x04,0x2E,0xFF,0x04,0x2E,0xFF,0x04,0x2F,0xFF,0x04,0x2F,0xFF,0x04,0x2F,0xFF,0x04,0x2F,0xFF,0x04,0x2F,0xFF,0x04,0x0F,0xFF,0x04,0x0F,0xFF,0x04,0x70,0xFF,0x05,0x11,0xFF,0x04,0x70,0xFF,0x03,0xCF,0xFF,0x03,0xCF,0xFF,0x03,0xEF,0xFF,0x03,0xCF,0xFF,0x03,0xCF,0xFF,0x03,0xCE,0xFF,0x03,0xEE,0xFF,0x04,0x0E,0xFF,0x04,0x0E,0xFF,0x04,0x4E,0xFF,0x04,0x4F,0xFF,0x04,0x4F,0xFF,0x04,0x4F,0xFF,0x04,0x70,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xF5,0xFF,0x02,0xCC,0xFF,0x03,0x4C,0xFF,0x03,0xED,0xFF,0x04,0x6E,0xFF,0x04,0x6E,0xFF,0x04,0x6E,0xFF,0x04,0x8E,0xFF,0x04,0x8E,0xFF,0x04,0x8E,0xFF,0x04,0x8E,0xFF,0x04,0x8F,0xFF,0x04,0x8F,0xFF,0x05,0x11,0xFF,0x05,0x11,0xFF,0x04,0x6E,0xFF,0x04,0x8E,0xFF,0x04,0x8E,0xFF,0x04,0x8E,0xFF,0x04,0xCD,0xFF,0x04,0xCD,0xFF,0x04,0xCD,0xFF,0x04,0xAE,0xFF,0x04,0x4F,0xFF,0x04,0x4F,0xFF,0x04,0x4F,0xFF,0x04,0x2F,0xFF,0x04,0x2E,0xFF,0x8C,0xB3,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xB9,0xFF,0x04,0x4E,0xFF,0x04,0x2F,0xFF,0x04,0x0F,0xFF,
	0x04,0x0E,0xFF,0x04,0x2E,0xFF,0x04,0x4F,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xBE,0xB9,0xFF,0x04,0x2F,0xFF,0x04,0x4F,0xFF,0x04,0x8F,0xFF,0x04,0x8F,0xFF,0x04,0x4E,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xB9,0xFF,0x04,0x8F,0xFF,0x04,0x4E,0xFF,0x03,0x4B,0xFF,0x02,0x69,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xB9,0xFF,0x02,0x69,0xFF,0x00,0xA3,0xFF,0x00,0x22,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0x83,0xFF,0x00,0x83,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0xA3,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0xD3,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x42,0xFF,0x01,0x06,0xFF,0x02,0x49,0xFF,0x03,0x0B,0xFF,0x02,0xCB,0xFF,0x02,0x8B,0xFF,0x02,0xEB,0xFF,0x03,0x0B,0xFF,0x02,0xEB,0xFF,0x02,0xAB,0xFF,0x02,0x4B,0xFF,0x03,0x2E,0xFF,0x03,0x8D,0xFF,0x03,0xED,0xFF,0x04,0x6D,0xFF,0x04,0x4E,0xFF,0x04,0x4E,0xFF,0x03,0xED,0xFF,0x8C,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x42,0xFF,0x00,0x42,0xFF,0x00,0xA4,0xFF,0x01,0x88,0xFF,0x02,0x8A,0xFF,0x02,0xEB,0xFF,0x03,0x4B,0xFF,0x03,0x4B,0xFF,0x03,0x0B,0xFF,0x03,0x0B,0xFF,0x03,0x0B,0xFF,0x03,0x4C,0xFF,0x03,0xEB,0xFF,0x04,0x2C,0xFF,0x04,0x2C,0xFF,0x03,0xCD,0xFF,0x03,0x0B,0xFF,0x01,0x45,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x62,0xFF,0x00,0x63,0xFF,0x00,0x83,0xFF,0x00,0x83,0xFF,0x00,0xC4,0xFF,0x01,0x25,0xFF,0x01,0xC8,0xFF,0x02,0x49,0xFF,0x02,0xCB,0xFF,0x03,0x0B,0xFF,0x03,0x4B,0xFF,0x03,0x4B,0xFF,0x03,0x4B,0xFF,0x02,0x8A,0xFF,0x02,0x29,0xFF,0x01,0xA7,0xFF,
	0x00,0xC4,0xFF,0x00,0xA3,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x62,0xFF,0x00,0x83,0xFF,0x00,0x83,0xFF,0x00,0x63,0xFF,0x00,0x42,0xFF,0x00,0x62,0xFF,0x00,0x82,0xFF,0x00,0xC3,0xFF,0x01,0x04,0xFF,0x01,0x24,0xFF,0x01,0x45,0xFF,0x01,0x24,0xFF,
	0x01,0x24,0xFF,0x00,0xE4,0xFF,0x00,0xC4,0xFF,0x00,0xA3,0xFF,0x00,0x83,0xFF,0x00,0xA4,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x82,0xFF,0x00,0x83,0xFF,0x00,0xA4,0xFF,0x00,0x83,0xFF,0x00,0x62,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,
	0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x43,0xFF,0x00,0x63,0xFF,0x00,0x83,0xFF,0x00,0xA4,0xFF,0x00,0xC4,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xB3,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x83,0xFF,0x00,0x83,0xFF,0x00,0xA3,0xFF,0x00,0x83,0xFF,
	0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x62,0xFF,0x00,0x83,0xFF,0x00,0xA4,0xFF,0x00,0x83,0xFF,0x00,0xA4,0xFF,0x00,0xA4,0xFF,0x00,0xE5,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xB3,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,
	0x00,0x83,0xFF,0x00,0x83,0xFF,0x00,0x83,0xFF,0x00,0x62,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x62,0xFF,0x00,0xA4,0xFF,0x00,0xA4,0xFF,0x00,0xA4,0xFF,0x00,0xA4,0xFF,0x00,0xC4,0xFF,0x00,0xC4,0xFF,0x01,0x05,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xB3,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0xA3,0xFF,0x00,0x83,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x62,0xFF,0x00,0xA4,0xFF,0x00,0xE5,0xFF,0x00,0xE4,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xB3,0xFF,0x8C,0xB3,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0xA3,0xFF,0x00,0x83,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0x61,0xFF,0x00,0x61,0xFF,0x00,0x41,0xFF,0x00,0x41,0xFF,0x00,0x62,0xFF,0x00,0xC4,0xFF,0x01,0x05,0xFF,0x00,0xE5,0xFF,0x00,0xE5,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x00,0xC5,0xFF,0x01,0x06,0xFF,0x01,0x06,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xB3,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x83,0xFF,0x00,0x82,0xFF,0x00,0x62,0xFF,0x00,0x82,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0xA3,0xFF,0x01,0x05,0xFF,0x01,0x05,0xFF,0x00,0xE5,0xFF,0x00,0xE5,0xFF,0x01,0x06,0xFF,0x00,0xE5,0xFF,0x00,0xE5,0xFF,0x01,0x26,0xFF,0x01,0x06,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xB3,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0xA3,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x00,0xE5,0xFF,0x00,0xE5,0xFF,0x01,0x06,0xFF,0x01,0x06,0xFF,0x00,0xC5,0xFF,0x01,0x06,0xFF,
	0x01,0x47,0xFF,0x01,0x06,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xB3,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x82,0xFF,0x00,0x62,0xFF,0x00,0x82,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0xA3,0xFF,0x00,0xE4,0xFF,0x01,0x05,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,
	0x01,0x26,0xFF,0x01,0x06,0xFF,0x00,0xE5,0xFF,0x01,0x26,0xFF,0x01,0x67,0xFF,0x01,0x26,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0xA3,0xFF,0x00,0xE4,0xFF,0x01,0x05,0xFF,
	0x00,0xE5,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x26,0xFF,0x01,0x26,0xFF,0x01,0x06,0xFF,0x01,0x06,0xFF,0x01,0x47,0xFF,0x01,0x47,0xFF,0x01,0x26,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,
	0x00,0x82,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x00,0xE5,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x01,0x47,0xFF,0x01,0x26,0xFF,0x01,0x06,0xFF,0x01,0x26,0xFF,0x01,0xA8,0xFF,0x01,0x26,0xFF,0x01,0x26,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,
	0x00,0x82,0xFF,0x00,0x83,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0xA3,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x01,0x05,0xFF,0x00,0xE5,0xFF,0x01,0x06,0xFF,0x01,0x47,0xFF,0x01,0x46,0xFF,0x01,0x26,0xFF,0x01,0x27,0xFF,0x01,0xA8,0xFF,0x01,0x06,0xFF,0x01,0x27,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x83,0xFF,0x00,0x83,0xFF,0x00,0x82,0xFF,0x00,0x83,0xFF,0x00,0xE4,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x06,0xFF,0x01,0x06,0xFF,0x01,0x06,0xFF,0x01,0x26,0xFF,0x01,0x67,0xFF,0x01,0x67,0xFF,0x01,0x26,0xFF,0x01,0x67,0xFF,0x01,0x87,0xFF,0x01,0x47,0xFF,0x01,0x67,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x83,0xFF,0x00,0x82,0xFF,0x00,0x83,0xFF,0x00,0xC4,0xFF,0x01,0x05,0xFF,0x00,0xC5,0xFF,0x01,0x05,0xFF,0x01,0x06,0xFF,0x01,0x05,0xFF,0x01,0x26,0xFF,0x01,0x47,0xFF,0x01,0xC8,0xFF,0x01,0x67,0xFF,0x01,0x26,0xFF,0x01,0x67,0xFF,0x01,0x67,0xFF,0x01,0xA8,0xFF,0x01,0xA8,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x83,0xFF,0x00,0x62,0xFF,0x00,0xA3,0xFF,0x01,0x05,0xFF,0x00,0xE5,0xFF,0x00,0xE5,0xFF,0x01,0x06,0xFF,0x01,0x06,0xFF,0x01,0x05,0xFF,0x01,0x26,0xFF,0x01,0xA7,0xFF,0x02,0x29,0xFF,0x01,0x87,0xFF,0x01,0x27,0xFF,0x01,0xA8,0xFF,0x01,0x67,0xFF,0x01,0xE8,0xFF,0x01,0xA8,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x82,0xFF,0x00,0xA3,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x06,0xFF,0x00,0xE5,0xFF,0x01,0x26,0xFF,0x01,0x26,0xFF,0x01,0x06,0xFF,0x01,0x67,0xFF,0x01,0xE8,0xFF,0x02,0x29,0xFF,0x01,0x87,0xFF,0x01,0x47,0xFF,0x01,0xC8,0xFF,0x01,0x87,0xFF,
	0x02,0x29,0xFF,0x01,0xA8,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0x82,0xFF,0x00,0xA3,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x01,0x26,0xFF,0x01,0x06,0xFF,0x01,0x26,0xFF,0x01,0x26,0xFF,0x01,0x06,0xFF,0x01,0x87,0xFF,0x02,0x29,0xFF,0x01,0xE8,0xFF,
	0x01,0x67,0xFF,0x01,0x67,0xFF,0x01,0xC8,0xFF,0x01,0x87,0xFF,0x02,0x29,0xFF,0x01,0xC8,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0xA3,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x26,0xFF,0x01,0x67,0xFF,0x01,0x06,0xFF,0x01,0x67,0xFF,0x01,0x46,0xFF,
	0x01,0x26,0xFF,0x01,0xC8,0xFF,0x02,0x29,0xFF,0x01,0x87,0xFF,0x01,0x67,0xFF,0x01,0xE8,0xFF,0x02,0x29,0xFF,0x01,0xA8,0xFF,0x01,0xE8,0xFF,0x01,0x87,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0xC4,0xFF,0x00,0xE5,0xFF,0x01,0x05,0xFF,0x01,0x46,0xFF,
	0x01,0x67,0xFF,0x01,0x26,0xFF,0x01,0x67,0xFF,0x01,0x67,0xFF,0x01,0x67,0xFF,0x02,0x29,0xFF,0x02,0x29,0xFF,0x01,0x47,0xFF,0x01,0x87,0xFF,0x02,0x49,0xFF,0x02,0x29,0xFF,0x01,0x87,0xFF,0x01,0x88,0xFF,0x01,0x47,0xFF,0x8C,0xB3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,
	0x00,0xE4,0xFF,0x01,0x05,0xFF,0x01,0x06,0xFF,0x01,0x67,0xFF,0x01,0x87,0xFF,0x01,0x26,0xFF,0x01,0x87,0xFF,0x01,0x87,0xFF,0x01,0x87,0xFF,0x02,0x49,0xFF,0x01,0xE8,0xFF,0x01,0x47,0xFF,0x01,0xE8,0xFF,0x02,0x69,0xFF,0x01,0xA8,0xFF,0x01,0x67,0xFF,0x01,0x67,0xFF,0x01,0x47,0xFF,0x8C,0xD3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x8C,0x92,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x92,0xFF,0x00,0xA3,0xFF,0xBD,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0x62,0xFF,0x00,0xC3,0xFF,0x00,0xA3,0xFF,0xBD,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0x62,0xFF,0x00,0x62,0xFF,0x00,0xC3,0xFF,0x00,0xC3,0xFF,0x00,0xA3,0xFF,0xBD,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0x62,0xFF,0x00,0x82,0xFF,0x00,0x62,0xFF,0x00,0xC3,0xFF,0x00,0xC3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0xBD,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0xC3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0xD6,0xBA,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0xC3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0x00,0xA3,0xFF,0xD6,0xBA,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF7,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,0x00,0x82,0xFF,
    };

const lv_img_dsc_t face_66_2_dial_1_68896_6 = {
    .header.always_zero = 0,
    .header.w = 36,
    .header.h = 63,
    .data_size = sizeof(face_66_2_dial_1_68896_data_6),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = face_66_2_dial_1_68896_data_6};
