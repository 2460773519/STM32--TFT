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

//-------常用颜色----------
#define RED     	0XF800    //红色
#define GREEN   	0X07E0    //绿色
#define BLUE    	0X001F    //蓝色
#define BRED    	0XF81F
#define GRED    	0XFFE0    //灰色
#define GBLUE   	0X07FF    //
#define BLACK   	0X0000    //黑色
#define WHITE   	0XFFFF    //白色
#define YELLOW  	0xFFE0    //黄色


#endif
