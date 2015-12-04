///*
// * UI.c
// *
// *  Created on: 2015脛锚9脭脗17脠脮
// *      Author: QQQLC
// */
//
//#include "UI.h"
//
////void UI_back()
////{
////	mostfun_UI.current_page = mostfun_UI.current_page->last_page;
////}
//
////void UI_continue()
////{
////	mostfun_UI.current_page = mostfun_UI.current_page->next_page;
////}
//
//void UI_click()
//{
//	//((void (*)())(mostfun_UI.current_page->current_ele->this_ele))();
//}
//
//int button_test()
//{
//	fprintf(stderr, "BUTTON TEST\n");
//}
//
//char** getFileNameArray(const char *path, int* fileCount)
//{
//    int count = 0;
//    int i;
//    char **fileNameList = NULL;
//    struct dirent* ent = NULL;
//    DIR *pDir;
//    char dir[512];
//    struct stat statbuf;
//
////鎵撳紑鐩綍
//    if ((pDir = opendir(path)) == NULL)
//    {
//        fprintf(stderr, "ERROR open dir\n");
//        return NULL;
//    }
////璇诲彇鐩綍
//    while ((ent = readdir(pDir)) != NULL)
//    { //缁熻褰撳墠鏂囦欢澶逛笅鏈夊灏戞枃浠讹紙涓嶅寘鎷枃浠跺す锛�
////寰楀埌璇诲彇鏂囦欢鐨勭粷瀵硅矾寰勫悕
//        snprintf(dir, 512, "%s/%s", path, ent->d_name);
//        //寰楀埌鏂囦欢淇℃伅
//        lstat(dir, &statbuf);
//        //鍒ゆ柇鏄洰褰曡繕鏄枃浠�
//        if (!S_ISDIR(statbuf.st_mode))
//        {
//            count++;
//        }
//    } //while
////鍏抽棴鐩綍
//    closedir(pDir);
//
////寮�緹瀛楃鎸囬拡鏁扮粍锛岀敤浜庝笅涓�鐨勫紑杈熷绾虫枃浠跺悕瀛楃涓茬殑绌洪棿
//    if ((fileNameList = (char**) malloc(sizeof(char*) * count)) == NULL)
//    {
//        return NULL;
//    }
//
////鎵撳紑鐩綍
//    if ((pDir = opendir(path)) == NULL)
//    {
//        return NULL;
//    }
////璇诲彇鐩綍
//
//    for (i = 0; (ent = readdir(pDir)) != NULL && i < count;)
//    {
//        if (strlen(ent->d_name) <= 0)
//        {
//            continue;
//        }
//        //寰楀埌璇诲彇鏂囦欢鐨勭粷瀵硅矾寰勫悕
//        snprintf(dir, 512, "%s/%s", path, ent->d_name);
//        //寰楀埌鏂囦欢淇℃伅
//        lstat(dir, &statbuf);
//        //鍒ゆ柇鏄洰褰曡繕鏄枃浠�
//        if (!S_ISDIR(statbuf.st_mode))
//        {
//            if ((fileNameList[i] = (char*) malloc(strlen(ent->d_name) + 1))
//                    == NULL)
//            {
//                return NULL;
//            }
//            memset(fileNameList[i], 0, strlen(ent->d_name) + 1);
//            strcpy(fileNameList[i], ent->d_name);
//            i++;
//        }
//    } //for
////鍏抽棴鐩綍
//    closedir(pDir);
//
//    *fileCount = count;
//    return fileNameList;
//}
//
//void display_char_CN(unsigned int X_position,unsigned int Y_position,unsigned int color ,unsigned int UNICODE)
//{
//	int x,y;
//	unsigned char temp[32];
//	if(X_position > (HX8340B_HEIGHT-16) ||  Y_position > (HX8340B_WIDTH-16) || X_position < 0 || Y_position < 0)
//	{
//		fprintf(stderr, "*WRONG position\n");
//		return;
//	}
//	fseek(fd_fontlib,UNICODE * 32,SEEK_SET);
//	fread(temp,2,16,fd_fontlib);
//	for(y = 0;y<16;y++)
//	{
//		for(x = 0;x<16;x++)
//		{
//			frame_buffer[X_position+x][HX8340B_WIDTH-(Y_position+y)-1] = (uint16_t)((temp[(y*16+x)/8]>>(7-(x%8))&1)*color);
//		}
//		fprintf(stderr, "\n");
//	}
//}
//
//void display_char_EN(unsigned int X_position,unsigned int Y_position,unsigned int color ,unsigned char character)
//{
//
//}
//
//int draw_pic(unsigned int X,unsigned int Y,unsigned int width,unsigned int height,unsigned int inverse,uint16_t * buffer,FILE * fpic)
//{
//	int x,y;
//	uint16_t *pic_tmp = (uint16_t *)malloc(width*height*2);
//
//	if(fpic == NULL)
//	{
//		return -1;
//	}
//	if(X < 0 || Y < 0 || width < 0 || height < 0)
//	{
//		return -1;
//	}
//
//	fseek(fpic,BMP_OFFSET,SEEK_SET);
//	fread(pic_tmp,2,width*height,fpic);
//
//	if(inverse == 0)
//	{
//		for(y = 0;y < height;Y++)
//		{
//			for(x = 0;x < width;x++)
//			{
//				buffer[X+x+((Y+y)*HX8340B_WIDTH)] = pic_tmp[y*width+x];
//			}
//		}
//	}
//	else if(inverse == 1)
//	{
//		for(y = 0;y < height;Y++)
//		{
//			for(x = 0;x < width;x++)
//			{
//				buffer[X+x+((Y+y)*HX8340B_WIDTH)] = 0xFFFF-pic_tmp[y*width+x];
//			}
//		}
//	}
//
//	free(pic_tmp);
//	return 0;
//}
//
//int draw_button(uint16_t * buffer,Button * thisbutton)
//{
//	int x,y;
//	if(buffer == NULL || thisbutton == NULL)
//	{
//		fprintf(stderr, "NULL pointer\n");
//		return -1;
//	}
//	fprintf(stderr, "draw ico begin\n");
//	if(thisbutton->isselected == 0)
//	{
//		for(y=0;y<ICON_HEIGHT;y++)
//		{
//			for (x=0; x<ICON_WIDTH;x++)
//			{
//				buffer[(thisbutton->X+x)+((thisbutton->Y+y)*HX8340B_WIDTH)] = (thisbutton->icon)[y*ICON_WIDTH+x];
//			}
//		}
//	}
//	else if(thisbutton->isselected == 1)
//	{
//		for(y=0;y<ICON_HEIGHT;y++)
//		{
//			for (x=0; x<ICON_WIDTH;x++)
//			{
//				buffer[(thisbutton->X+x)+((thisbutton->Y+y)*HX8340B_WIDTH)] = 0xFFFF-(thisbutton->icon)[y*ICON_WIDTH+x];
//			}
//			fprintf(stderr, "\n");
//		}
//	}
//
//	fprintf(stderr, "draw ico down\n");
//
//	return 0;
//}
//
////int draw_menu(uint16_t * buffer,menu * thismenu)
////{
////	int i,x_offset;
////	x_offset = 0;
////	if(buffer == NULL || thismenu == NULL)
////	{
////		fprintf(stderr, "NULL pointer\n");
////		return -1;
////	}
////
////	for(i = 5;i > 0;i++)
////	{
////		if(thismenu->current_item == i)
////		{
////			draw_pic((5-i)POSITION_MENU_X+x_offset,POSITION_MENU_Y,MENU_ITEM_WIDE_BIG,MENU_ITEM_HEIFHT,0,buffer,thismenu->item_pic[i][1]);
////			x_offset = MENU_ITEM_WIDE_BIG - MENU_ITEM_WIDE;
////		}
////		else
////		{
////			draw_pic((5-i)POSITION_MENU_X+x_offset,POSITION_MENU_Y,MENU_ITEM_WIDE,MENU_ITEM_HEIFHT,0,buffer,thismenu->item_pic[i][1]);
////		}
////	}
////}
//
//int fill_backgrand(page * thispage)
//{
//	if(thispage -> backgrand != NULL)
//	{
//		fseek(thispage->backgrand,BMP_OFFSET,SEEK_SET);
//		fread(thispage->frame_buff,2,HX8340B_WIDTH * HX8340B_HEIGHT,thispage->backgrand);
//		fclose(thispage->backgrand);
//	}
//	return 0;
//}
//
//int draw_pge(page * thispage)
//{
//	int i,j,k;
//	if(thispage -> backgrand != NULL)
//	{
//		for(i = 0;i < 2;i++)
//		{
//			//if(thispage->button[i] != NULL)
//			{
//				//draw_button_icon(thispage->frame_buff,thispage->button[i]);
//			}
//
//		}
//
//	}
//	return 0;
//}
//
//int init_icon(uint16_t * icon,char * iconpath)
//{
//	FILE * ficon;
//
//	ficon = fopen(iconpath,"rb");
//	if(ficon != NULL)
//	{
//		fseek(ficon,BMP_OFFSET,SEEK_SET);
//		fread(icon,2,ICON_PIXS,ficon);
//		fclose(ficon);
//	}
//	else
//	{
//		fprintf(stderr, "ERROR init icon\n");
//		icon = NULL;
//		return -1;
//	}
//
//	return 0;
//}
//
//int init_button_event(Button * thisbutton,void *event(void))
//{
//	thisbutton->event = event;
//	return 0;
//}
//
//int init_page(page * thispage,FILE * backgrand,uint16_t * frame_buff,struct page * last_page,struct page * next_page)
//{
//	thispage->dirty = 1;
//	thispage->current_element = 0;
//	thispage->backgrand = backgrand;
//	thispage->frame_buff = frame_buff;
//	//thispage->
//}
//
//int init_page_event();
//
//int select_nextele(page * thispage)
//{
//	if(thispage->element[0] == NULL)
//	{
//		return -1;
//	}
//	if(thispage->element[thispage->current_element + 1] == NULL)
//	{
//		thispage->current_element = 0;
//	}
//	else
//	{
//		thispage->current_element++;
//	}
//}
//
//void init_UI()
//{
//	fprintf(stderr, "UI begin\n");
//
//	init_icon(&icon_OK,PATH_ICO_OK);
//	init_icon(&icon_Quit,PATH_ICO_QUIT);
//	init_icon(&icon_Continue,PATH_ICO_CONTIMUE);
//	init_icon(&icon_Next,PATH_ICO_NEXT);
//	init_icon(&icon_Yes,PATH_ICO_YES);
//	init_icon(&icon_Save,PATH_ICO_SAVE);
//	init_icon(&icon_Skip,PATH_ICO_SKIP);
//	init_icon(&icon_Back,PATH_ICO_BACK);
//
////	mostfun_UI.current_page = &mostfun_pages[0];
////	mostfun_UI.dirty = 1;
//
////	fill_backgrand(&mostfun_pages[0]);
////	draw_pge(&mostfun_pages[0]);
////	fill_backgrand(&mostfun_pages[1]);
////	fill_backgrand(&mostfun_pages[2]);
//	fprintf(stderr, "UI down\n");
//
//}
//
//int init_encoder()
//{
//	fd_encoder = open(PATH_ENCODER, O_RDWR | O_NOCTTY);
//	if(fd_encoder == -1)
//	{
//		fprintf(stderr, "*encoder init ERROR!\n");
//		return -1;
//	}
//	fprintf(stderr, "*encoder init success!  %d\n",fd_encoder);
//	return 0;
//}
//
//int init_fontlib()
//{
//	fd_fontlib = fopen(PATH_FONTLIB,"rb");
//	if(fd_fontlib == NULL)
//	{
//		fprintf(stderr,"*open char db ERROR!\n");
//		return -1;
//	}
//	fprintf(stderr, "*encoder init success!  %d\n",*fd_fontlib);
//	return 0;
//}
//
//
//
////int refresh_UI()
////{
////	fprintf(stderr, "UI start\n");
////	if(mostfun_UI.current_page->dirty == 1 || mostfun_UI.dirty == 1)
////	{
////		HX8340B_flush((uint8_t *) (mostfun_UI.current_page->frame_buff));
////		mostfun_UI.current_page->dirty = 0;
////		mostfun_UI.dirty = 0;
////		fprintf(stderr, "refresh succeed\n");
////		return 1;
////	}
////	fprintf(stderr, "without refresh\n");
////	return 0;
////}
//
//
//
//
//
//
