/*
 * HX8340B.h
 *
 *  Created on: 2015Äê9ÔÂ11ÈÕ
 *      Author: QQQLC
 */

#ifndef HX8340B_H_
#define HX8340B_H_
/*
 * Author: Ivan De Cesaris <ivan.de.cesaris@intel.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mraa.h"
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

// Size of the HX8340B display, note it's different from SCREENWIDTH/SCREENHEIGHT
#define HX8340B_WIDTH   176
#define HX8340B_HEIGHT  220

 #define BMP_OFFSET 70

// Helper macros to switch GPIO pins
#define RD_ACTIVE  mraa_gpio_write(g_rdPinCtx, 0)
#define RD_IDLE    mraa_gpio_write(g_rdPinCtx, 1)
#define WR_ACTIVE  mraa_gpio_write(g_wrPinCtx, 0)
#define WR_IDLE    mraa_gpio_write(g_wrPinCtx, 1)
#define CD_COMMAND mraa_gpio_write(g_cdPinCtx, 0)
#define CD_DATA    mraa_gpio_write(g_cdPinCtx, 1)
#define CS_ACTIVE  mraa_gpio_write(g_csPinCtx, 0)
#define CS_IDLE    mraa_gpio_write(g_csPinCtx, 1)
#define RST_ACTIVE mraa_gpio_write(g_rstPinCtx, 0)
#define RST_IDLE   mraa_gpio_write(g_rstPinCtx, 1)

// Data write strobe, ~2 instructions and always inline
#define WR_STROBE { uint32_t bit = (uint32_t)((uint32_t)1 << (HX8340B_EDISON_WR % 32)); \
	*(volatile uint32_t*)g_MmapRegisterClear = bit; \
	*(volatile uint32_t*)g_MmapRegisterSet = bit; }


// Edison pin assignments for HX8340B controller
static const int HX8340B_CS = 23;
static const int HX8340B_CD = 47;
static const int HX8340B_WR = 33;
static const int HX8340B_RD = 24;
static const int HX8340B_RST = 9;
static const int HX8340B_DATA[8] = { 37, 51, 50, 38, 31, 45, 32, 46 };

// GPIO pins to drive display
static mraa_gpio_context g_csPinCtx = 0;
static mraa_gpio_context g_cdPinCtx = 0;
static mraa_gpio_context g_wrPinCtx = 0;
static mraa_gpio_context g_rdPinCtx = 0;
static mraa_gpio_context g_rstPinCtx = 0;
static mraa_gpio_context g_dataPinCtx[8] = { 0 };

// First hardware pin number of the data bits, ie 40-47, and WR flag assumed in the same % 32 range
static const int HX8340B_EDISON_DATA0 = 40;
static const int HX8340B_EDISON_WR = 48;

// Memory mapped registers to set the data pins faster than through MRAA interface
static uint8_t *g_MmapRegisterSet = NULL;
static uint8_t *g_MmapRegisterClear = NULL;

static uint16_t frame_buffer[HX8340B_HEIGHT][HX8340B_WIDTH];
//static uint16_t * display_point = (uint16_t)frame_buffer;

// This is an absolute path to a resource file found within sysfs.
// Might not always be correct. First thing to check if mmap stops
// working. Check the device for 0x1199 and Intel Vendor (0x8086)
#define MMAP_PATH "/sys/devices/pci0000:00/0000:00:0c.0/resource0"


void HX8340B_init();
mraa_gpio_context HX8340B_InitPin(int pin);
void HX8340B_InitMmap();
void HX8340B_InitDisplay();
void HX8340B_WriteRegister8(uint8_t a, uint8_t d);
void HX8340B_draw_pix(unsigned int X,unsigned int Y,uint16_t color,uint16_t * frame_buffer);
void HX8340B_fill(unsigned int a);
void HX8340B_flush(uint16_t* buffer);
void HX8340B_display_pic(char * filename);
void HX8340B_display_bmp24(char * filename);
inline void HX8340B_Write8(uint8_t value);


#endif /* HX8340B_H_ */
