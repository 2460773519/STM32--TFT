/*********************************************************************************************************************


 ********************************************************************************************************************/


#ifndef _SEEKFREE_FONT_h
#define _SEEKFREE_FONT_h

#include "sys.h"
#include "LCD1602.h"




extern const uint8  tft_ascii[95][16];
extern const uint8  tft_ascii_my[95][16];
extern const uint8  oled_8x16[];
extern const uint8  oled_6x8[][6];

//extern const uint8  my_name[1][16];

//-------������ɫ----------
#define RED     	0XF800    //��ɫ
#define GREEN   	0X07E0    //��ɫ
#define BLUE    	0X001F    //��ɫ
#define BRED    	0XF81F
#define GRED    	0XFFE0    //��ɫ
#define GBLUE   	0X07FF    //
#define BLACK   	0X0000    //��ɫ
#define WHITE   	0XFFFF    //��ɫ
#define YELLOW  	0xFFE0    //��ɫ


#endif
