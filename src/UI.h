///*
// * UI.h
// *
// *  Created on: 2015Äê9ÔÂ17ÈÕ
// *      Author: QQQLC
// */
//
//#ifndef UI_H_
//#define UI_H_
//
//#include <string.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <dirent.h>
//
//#include "HX8340B.h"
//
//#define MAX_ITEMS 256
//
//#define FRAME_BUFFER_PAFES 32
//#define BMP_OFFSET 70
//
//#define ATTR_PAGE   	0x00
//#define ATTR_MENU		0x01
//#define ATTR_LIST		0x02
//#define ATTR_TEXTBOX	0x03
//#define ATTR_BUTTON 	0x04
//
//
//
//#define ICON_HEIGHT 64
//#define ICON_WIDTH 	32
//#define ICON_PIXS (ICON_WIDTH*ICON_HEIGHT)
//
//#define PATH_QR 	 	"/tmp/QRcode.bmp"
//#define PATH_ENCODER 	"/dev/ttymcu0"
//#define PATH_FONTLIB 	"/home/ziku.mostfun"
//#define PATH_ICO_OK	 	"/home/OK.bmp"
//#define PATH_ICO_QUIT	"/home/Quit.bmp"
//#define PATH_ICO_CONTIMUE	"/home/Continue.bmp"
//#define PATH_ICO_NEXT	"/home/Next.bmp"
//#define PATH_ICO_YES	"/home/Yes.bmp"
//#define PATH_ICO_SAVE	"/home/Save.bmp"
//#define PATH_ICO_SKIP	"/home/Skip.bmp"
//#define PATH_ICO_BACK	"/home/Back.bmp"
//#define PATH_ICO_PRINT	"/home/Print.bmp"
//
//#define PATH_GCODES		"/home"
//
//#define PATH_BKGD_BLACK "/home/black.bmp"
//#define PATH_BKGD_MOSTFUN "/home/mostfun.bmp"
//#define PATH_BKGD_QR	"/home/gif/qr.bmp"
//#define PATH_BKGD_PAUSED "/home/paused.bmp"
//#define PATH_BKGD_PRINTER_FILES	"/home/printerfiles.bmp"
//#define PATH_BKGD_SD_FILES 	"/home/sdpiles.bmp"
//#define PATH_BKGD_PAUSED_FILES 	"/home/pausedfiles.bmp"
//#define PATH_BKGD_REFILL0	"/home/refill0.bmp"
//#define PATH_BKGD_REFILL1	"/home/refill1.bmp"
//#define PATH_BKGD_REFILL2	"/home/refill2.bmp"
//#define PATH_BKGD_REFILL3	"/home/refill3.bmp"
//#define PATH_SAVING			"/home/saving.bmp"
//#define PATH_GOODBYE		"/home/googdbye.bmp"
//
//#define POSITION_MENU_X		16
//#define POSITION_MENU_Y		0
//#define MENU_ITEM_WIDE  	27
//#define MENU_ITEM_WIDE_BIG	36
//#define MENU_ITEM_HEIFHT	200
//
//static uint16_t pages_frame_buffer[FRAME_BUFFER_PAFES][HX8340B_HEIGHT*HX8340B_WIDTH];
//
//static FILE * fd_fontlib;
//static int fd_encoder;
//static unsigned char encoder_value;
//
//typedef struct _Button
//{
//	int type;
//	void (*event)(void);
//	int isselected;
//	unsigned int X;
//	unsigned int Y;
//	unsigned int width;
//	unsigned int height;
//
//	unsigned int button_color;
//	unsigned int text_color;
//
//	char * name;
//	uint16_t * icon;
//}Button;
//
//typedef struct _Text_box
//{
//	int type;
//	int isselected;
//	unsigned int X;
//	unsigned int Y;
//	unsigned int width;
//	unsigned int height;
//
//	unsigned int text_color;
//}Text_box;
//
//typedef struct _text_list
//{
//
//	int type;
//	void (*event)(void);
//	char * title;
//	unsigned int text_color;
//	unsigned int item_sum;
//	unsigned int current_item;
//	char * item[MAX_ITEMS];
//}text_list;
//
//typedef struct _menu
//{
//	int type;
//	void (*event)(void);
//	int isselected;
//	unsigned int text_color;
//	unsigned int item_sum;
//	unsigned int current_item;
//
//	FILE * item_pic[5][2];
////	char * menu_item[5];
//}menu;
//
//typedef struct _progress_bar
//{
//	int type;
//	void (*event)(void);
//	int isselected;
//	unsigned int X;
//	unsigned int Y;
//	unsigned int width;
//	unsigned int height;
//
//	unsigned int percent;
//}progress_bar;
//
//typedef struct _page
//{
//	int dirty;
//	FILE * backgrand;
//	uint16_t * frame_buff;
//
//	struct page * last_page;
//	struct page * next_page;
//
//	unsigned int current_element;
//	void * element[5];
//
//	void (*draw)(void);
//	void (*click)(void);
//	void (*press)(void);
//	void (*left)(void);
//	void (*right)(void);
//}page;
//
//typedef struct _UI
//{
//	page * current_page;
//	int dirty;
//
//	void (*select_last_ele)(void);
//	void (*select_next_ele)(void);
//	void (*click_this_ele)(void);
//	void (*pressed)(void);
//}UI;
//
//typedef struct _printer
//{
//
//}printer;
//
//void init_UI();
//int fill_backgrand(page * thispage);
//int draw_page(page * thispage);
//void UI_back();
//void UI_continue();
//void UI_click();
//void UI_last_ele();
//void UI_next_ele();
//void display_char_CN(unsigned int X_position,unsigned int Y_position,unsigned int color ,unsigned int UNICODE);
//void display_char_EN(unsigned int X_position,unsigned int Y_position,unsigned int color ,unsigned char character);
//char ** getFileNameArray(const char *path, int* fileCount);
//int get_printer_status();
//
//static uint16_t icon_OK[ICON_HEIGHT*ICON_WIDTH];
//static uint16_t icon_Quit[ICON_HEIGHT*ICON_WIDTH];
//static uint16_t icon_Continue[ICON_HEIGHT*ICON_WIDTH];
//static uint16_t icon_Next[ICON_HEIGHT*ICON_WIDTH];
//static uint16_t icon_Yes[ICON_HEIGHT*ICON_WIDTH];
//static uint16_t icon_Save[ICON_HEIGHT*ICON_WIDTH];
//static uint16_t icon_Skip[ICON_HEIGHT*ICON_WIDTH];
//static uint16_t icon_Back[ICON_HEIGHT*ICON_WIDTH];
//
//
//static Button button_OK=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_OK,
//};
//static Button button_Quit=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_Quit,
//};
//static Button button_Continue=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_Continue,
//};
//static Button button_Next=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_Next,
//};
//static Button button_Yes=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_Yes,
//};
//static Button button_Save=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_Save,
//};
//static Button button_Skip=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_Skip,
//};
//static Button button_Back=
//{
//	.type = ATTR_BUTTON,
//	.event = NULL,
//	.isselected = 0,
//	.X = 100,
//	.Y = 100,
//	.width = 32,
//	.height = 64,
//	.icon = icon_Back,
//};
////static Button button_Print=
////{
////	.type = ATTR_BUTTON,
////	.event = NULL,
////	.isselected = 0,
////	.X = 100,
////	.Y = 100,
////	.width = 32,
////	.height = 64,
////	.icon = icon_Print,
////};
//
////static menu menu_main=
////{
////	.type = ATTR_MENU,
////	.event = NULL,
////	.isselected = 0,
////	.text_color = 0xFFFF,
////	.item_sum = 5,
////	.current_item = 0,
////	.menu_item[0] = "QR-code",
////	.menu_item[1] = "Files in printer",
////	.menu_item[2] = "Files in SD card",
////	.menu_item[3] = "Filament refill",
////	.menu_item[4] = "Paused files list",
////};
//
////enum MENU_ITEMS
////{
////	MENU_QR_CODE,
////	MENU_FILES_IN_PRINTER,
////	MENU_FILES_IN_SD_CARD,
////	MENU_PAUSED_FILES,
////	MENU_FLIAMENT_REFILL
////};
////
////static page mostfun_pages[32];
////
////mostfun_pages[0]=
////{
////	.dirty = 1,
////	.backgrand = NULL,
////}
////
////static UI mostfun_UI;
//
//
//#endif /* UI_H_ */
