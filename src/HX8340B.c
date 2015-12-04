
/*
 * HX8340B.c
 *
 *  Created on: 2015Äê9ÔÂ11ÈÕ
 *      Author: QQQLC
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "HX8340B.h"


// Initialize a GPIO pin for writing
void HX8340B_MilliSleep(int milliseconds)
{
	usleep(milliseconds * 1000);
}

mraa_gpio_context HX8340B_InitPin(int pin)
{
	usleep(10000);
	mraa_gpio_context context = mraa_gpio_init(pin);
	if (context == NULL)
	{
		fprintf(stderr, "Failed to open pin:" );
		fprintf(stderr, "%d\n", pin);
	}
	mraa_gpio_dir(context, MRAA_GPIO_OUT);
	mraa_gpio_use_mmaped(context, 1);
	mraa_gpio_write(context, 1);

	return context;
}

void HX8340B_InitMmap()
{
	int mmap_fd;
	if ((mmap_fd = open(MMAP_PATH, O_RDWR)) < 0)
	{
		fprintf(stderr, "open GPIO device:\n");
	}

	struct stat fd_stat;
	fstat(mmap_fd, &fd_stat);

	uint8_t* mmap_reg = (uint8_t*) mmap(NULL, fd_stat.st_size,
			PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, mmap_fd, 0);
	if (mmap_reg == MAP_FAILED)
	{
		fprintf(stderr, "failed to mmap GPIO device\n");
	}

	uint8_t offset = ((HX8340B_EDISON_DATA0 / 32) * sizeof(uint32_t));
	g_MmapRegisterSet = mmap_reg + offset + 0x34;
	g_MmapRegisterClear = mmap_reg + offset + 0x4c;
}

inline void HX8340B_Write8(uint8_t value)
{
//	uint32_t set = (uint32_t) value << (HX8340B_EDISON_DATA0 % 32);
//	uint32_t clear = ((uint32_t) ((uint8_t) ~value) << (HX8340B_EDISON_DATA0 % 32))
//			| (uint32_t) 1u << (HX8340B_EDISON_WR % 32);
//	uint32_t setWr = (uint32_t) 1 << (HX8340B_EDISON_WR % 32);
//	*(volatile uint32_t*) g_MmapRegisterSet = set;
//	*(volatile uint32_t*) g_MmapRegisterClear = clear;
//	*(volatile uint32_t*) g_MmapRegisterSet = setWr;

	uint32_t set = ((uint32_t) value << (HX8340B_EDISON_DATA0 % 32))|(uint32_t) 1u << (HX8340B_EDISON_WR % 32);
	uint32_t clear = ((uint32_t) ((uint8_t) ~value) << (HX8340B_EDISON_DATA0 % 32))
			| (uint32_t) 1u << (HX8340B_EDISON_WR % 32);
	*(volatile uint32_t*) g_MmapRegisterClear = clear;
	*(volatile uint32_t*) g_MmapRegisterSet = set;
}

inline void HX8340B_Write16(uint16_t pix)
{
	uint8_t tmp = (uint8_t)(pix&0xFF);

	HX8340B_Write8((uint8_t)(pix>>8));
	HX8340B_Write8(tmp);
}

void HX8340B_WriteRegister8(uint8_t a, uint8_t d)

{
	CD_COMMAND;
	CS_ACTIVE;
	HX8340B_Write8(a);
	CD_DATA;
	HX8340B_Write8(d);
	CS_IDLE;
}

void HX8340B_fill(unsigned int a)
{
	unsigned int j,i;
	CD_COMMAND;
	CS_ACTIVE;
	HX8340B_Write8(0x22);
	CD_DATA;
	for (j = 0;j < 176;j++)
	{
		for (i = 0;i < 220;i++)
		{
			//CS_ACTIVE;
			HX8340B_Write8(a>>8);
			HX8340B_Write8(a);
			//CS_IDLE;
			//HX8340B_Write8(0xe0);
		}
	}
	CS_IDLE;
}

void HX8340B_flush(uint16_t* buffer)
{
	unsigned int i;
	CD_COMMAND;
	CS_ACTIVE;
	HX8340B_Write8(0x22);
	CD_DATA;
	for (i = 0;i < HX8340B_WIDTH*HX8340B_HEIGHT;i++)
	{
		//CS_ACTIVE;
		//HX8340B_Write8(*mmap++);
		//HX8340B_Write8(*mmap++);
		HX8340B_Write16(*buffer++);
		//CS_IDLE;
		//HX8340B_Write8(0xe0);
	}
	CS_IDLE;
}

void HX8340B_display_pic(char * filename)
{
	FILE * f;

	uint8_t mmap[HX8340B_WIDTH * HX8340B_HEIGHT *2];

	if((f = fopen(filename,"rb"))!=NULL)
	{
		fseek(f,BMP_OFFSET,SEEK_SET);
		fread(mmap,2,HX8340B_WIDTH * HX8340B_HEIGHT,f);
		fclose(f);

		HX8340B_flush(mmap);
	}
}

void HX8340B_display_bmp24(char * filename)
{
	FILE * f;
	int x,y;
	int offset = 0;

	uint8_t mmap[HX8340B_WIDTH * HX8340B_HEIGHT *3];

	if((f = fopen(filename,"rb"))!=NULL)
	{
		//fseek(f,BMP_OFFSET,SEEK_SET);
		//fseek(f,55,SEEK_SET);
		fread(mmap, 26, 1, f);
		offset=mmap[10]+mmap[11]*256+mmap[12]*65536-26;
		fread(mmap, offset, 1, f);
		fread(mmap,3,HX8340B_WIDTH * HX8340B_HEIGHT,f);
		fclose(f);

//		for(y=HX8340B_HEIGHT-1;y >= 0;y--)
//		{
//			for (x = HX8340B_WIDTH-1; x >= 0; x--)
//			{
//				frame_buffer [y][x]= (uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3]>>3)|(uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3+1]>>2)<<5|(uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3+2]>>3)<<11;
//			}
//		}
		for(y=0;y<HX8340B_HEIGHT;y++)
		{
			for (x =  0;x < HX8340B_WIDTH; x++)
			{
				//frame_buffer [y][x]= (uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3]>>3)|(uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3+1]>>2)<<5|(uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3+2]>>3)<<11;
				frame_buffer [HX8340B_HEIGHT-y-1][HX8340B_WIDTH-x-1]= (uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3]>>3)|(uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3+1]>>2)<<5|(uint16_t)(mmap[(y*HX8340B_WIDTH+x)*3+2]>>3)<<11;
			}
		}
	}
	else
	{
		fprintf(stderr, "open bmp24 ERROR!\n");
		return;
	}
	HX8340B_flush(frame_buffer);
}

void HX8340B_InitDisplay()
{
	RST_ACTIVE;
	HX8340B_MilliSleep(1);
	RST_IDLE;
	HX8340B_MilliSleep(150);
	// Initialize display
	HX8340B_WriteRegister8(0x60, 0x00);
	HX8340B_WriteRegister8(0x60, 0x00); //PTBA[15:8]
	HX8340B_WriteRegister8(0x61, 0x06); //PTBA[7:0]
	HX8340B_WriteRegister8(0x62, 0x00); //STBA[15:8]
	HX8340B_WriteRegister8(0x63, 0xD9); //STBA[7:0]
	HX8340B_WriteRegister8(0x73, 0x70); //OPON[7:0],SET OPON=70h, default 38h
	//Gamma 2.2 Setting
	HX8340B_WriteRegister8(0x40, 0x01); //
	HX8340B_WriteRegister8(0x41, 0x30); //
	HX8340B_WriteRegister8(0x42, 0x62); //
	HX8340B_WriteRegister8(0x43, 0x00); //
	HX8340B_WriteRegister8(0x44, 0x79); //
	HX8340B_WriteRegister8(0x45, 0x05); //
	HX8340B_WriteRegister8(0x46, 0x0D); //
	HX8340B_WriteRegister8(0x47, 0xC7); //
	HX8340B_WriteRegister8(0x48, 0x04); //
	HX8340B_WriteRegister8(0x50, 0x76); //
	HX8340B_WriteRegister8(0x51, 0x00); //
	HX8340B_WriteRegister8(0x52, 0x76); //
	HX8340B_WriteRegister8(0x53, 0x10); //
	HX8340B_WriteRegister8(0x54, 0xA2); //
	HX8340B_WriteRegister8(0x55, 0x0C); //
	HX8340B_WriteRegister8(0x56, 0x01); //
	HX8340B_WriteRegister8(0x57, 0xA9); //
	//Power Voltage Setting
	HX8340B_WriteRegister8(0x1F, 0x03); //VRH=4.65V
	HX8340B_WriteRegister8(0x20, 0x01); //BT (VGH~15V,VGL~-10V,DDVDH~5V)
	HX8340B_WriteRegister8(0x24, 0x1C); //VMH(VCOM High voltage3.2V)
	HX8340B_WriteRegister8(0x25, 0x34); //VML(VCOM Low voltage -1.2V)
	//****VCOM offset**///
	HX8340B_WriteRegister8(0x23, 0x5e); //reload from OTP// For Flicker adjust  005f
	//Power on Setting
	HX8340B_WriteRegister8(0x18, 0x44); //I/P_RADJ,N/P_RADJ, Normal mode 60Hz
	HX8340B_WriteRegister8(0x1B, 0x44); //FS1 Pumping Clock= 2 x line frequency
	HX8340B_WriteRegister8(0x21, 0x01); //OSC_EN='1', start Osc
	HX8340B_WriteRegister8(0x01, 0x00); //SLP='0', out sleep
	HX8340B_WriteRegister8(0x1C, 0x03); //AP=011
	HX8340B_WriteRegister8(0x19, 0x06); // VOMG=1,PON=1, DK=0,
	HX8340B_MilliSleep(10);
	//262k/65k color selection
	HX8340B_WriteRegister8(0x17, 0x05); //default 0x06 262k color // 0x05 65k color
	//Display ON Setting
	HX8340B_WriteRegister8(0x26, 0x84); //PT=10,GON=0, DTE=0, D=0100
	HX8340B_MilliSleep(80);
	HX8340B_WriteRegister8(0x26, 0xB8); //PT=10,GON=1, DTE=1, D=1000
	HX8340B_MilliSleep(80);
	HX8340B_WriteRegister8(0x26, 0xBC); //PT=10,GON=1, DTE=1, D=1100
	//Set GRAM Area
	HX8340B_WriteRegister8(0x16, 0xE8);//set XYV
	HX8340B_WriteRegister8(0x02, 0x00);
	HX8340B_WriteRegister8(0x03, 0x00); //Column Start
	HX8340B_WriteRegister8(0x04, 0x00);
	HX8340B_WriteRegister8(0x05, 0xDB); //Column End
	HX8340B_WriteRegister8(0x06, 0x00);
	HX8340B_WriteRegister8(0x07, 0x00); //Row Start
	HX8340B_WriteRegister8(0x08, 0x00);
	HX8340B_WriteRegister8(0x09, 0xAF); //Row End
}

void HX8340B_init()
{

	g_rstPinCtx = HX8340B_InitPin(HX8340B_RST);
	g_csPinCtx = HX8340B_InitPin(HX8340B_CS);
	g_cdPinCtx = HX8340B_InitPin(HX8340B_CD);
	g_wrPinCtx = HX8340B_InitPin(HX8340B_WR);
	g_rdPinCtx = HX8340B_InitPin(HX8340B_RD);
	//g_blPinCtx = HX8340B_InitPin(HX8340B_BL);

	int i;
	for (i = 0; i < 8;i++)
	{
		g_dataPinCtx[i] = HX8340B_InitPin(HX8340B_DATA[i]);
	}
}

void refresh_frame()
{
	HX8340B_display_bmp24("/tmp/page.bmp");
}

int main()
{
  	HX8340B_init();
	HX8340B_InitMmap();
	HX8340B_InitDisplay();
	HX8340B_display_bmp24("/mostfun/panel/bg/logo.bmp");
	sleep(1);
	
	fprintf(stderr, "fill ok\n");
	signal(SIGINT,refresh_frame);

	printf("begin\n");
	for(;;)
	{
		pause();
		
	    printf("refresh\n");
	}
	return MRAA_SUCCESS;
}
