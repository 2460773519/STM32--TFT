/*********************************************************************************************************************


 ********************************************************************************************************************/


#ifndef _SEEKFREE_18TFT_h
#define _SEEKFREE_18TFT_h

#include "mn_spi.h"
#include "delay.h"
#include "sys.h"
#include "stdio.h"	
#include "SEEKFREE_FONT.h"


//--------------------软件SPI--------------------


#define	TFT_SCL_SIMSPI_PIN 		C7				//定义SPI_SCK引脚
#define	TFT_SDA_SIMSPI_PIN		C9   			//定义SPI_MOSI引脚
#define TFT_REST_SIMSPI_PIN  	A9			//定义复位引脚
#define TFT_DC_SIMSPI_PIN	  	B8				//液晶命令位引脚定义
#define TFT_CS_SIMSPI_PIN	  	C15				//定义SPI_CS引脚
#define TFT_BL_SIMSPI_PIN	  	A15				//液晶背光引脚定义  


#define	TFT_SCL_SIMSPI(x)	(PCout(7) = x)
#define	TFT_SDA_SIMSPI(x)	(PCout(9)	 = x)
#define TFT_REST_SIMSPI(x) 	(PAout(9) = x)	
#define TFT_DC_SIMSPI(x)   	(PBout(8)	 = x)
#define TFT_CS_SIMSPI(x) 	(PCout(15)	 = x)
#define TFT_BL_SIMSPI(x) 	(PAout(15)	 = x)



//--------------------硬件SPI--------------------



//-----------------------------------------------    


//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	    0xF800	//红色
//#define BLUE         	    0x001F  //蓝色
//#define YELLOW       	    0xFFE0	//黄色
//#define GREEN        	    0x07E0	//绿色
//#define WHITE        	    0xFFFF	//白色
//#define BLACK        	    0x0000	//黑色 
//#define GRAY  			0X8430 	//灰色
//#define BROWN 			0XBC40 	//棕色
//#define PURPLE    		0XF81F	//紫色
//#define PINK    		    0XFE19	//粉色

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

//定义写字笔的颜色
#define TFT_PENCOLOR    RED

//定义背景颜色
#define TFT_BGCOLOR	    WHITE

     
     
//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
#define TFT_DISPLAY_DIR 2

#if (0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)
	#define	TFT_X_MAX	128	//液晶X方宽度
	#define TFT_Y_MAX	160 //液晶Y方宽度
#elif (2==TFT_DISPLAY_DIR || 3==TFT_DISPLAY_DIR)
	#define	TFT_X_MAX	160	//液晶X方宽度
	#define TFT_Y_MAX	128 //液晶Y方宽度
#else
#error "TFT_DISPLAY_DIR 定义错误"
     
#endif

//--------------------软件SPI--------------------
void lcd_init_simspi(void);
void lcd_clear_simspi(int color);
void lcd_drawpoint_simspi(uint16 x,uint16 y,uint16 color);
void lcd_showchar_simspi(uint16 x,uint16 y,const int8 dat);
void lcd_showstr_simspi(uint16 x,uint16 y,const int8 dat[]);
void lcd_showint8_simspi(uint16 x,uint16 y,int8 dat);
void lcd_showuint8_simspi(uint16 x,uint16 y,uint8 dat);
void lcd_showint16_simspi(uint16 x,uint16 y,int16 dat);
void lcd_showuint16_simspi(uint16 x,uint16 y,uint16 dat);
void lcd_showint32_simspi(uint16 x,uint16 y,int32 dat,uint8 num);
void lcd_showfloat_simspi(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);

void lcd_showchar_simspi_my(uint16 x,uint16 y,const int8 dat);
void lcd_showchar_simspi_my_name(uint16 x,uint16 y,const int8 dat);
void lcd_showint16_simspi_my(uint16 x,uint16 y,int16 dat);




#endif
