/*********************************************************************************************************************


 ********************************************************************************************************************/


#ifndef _SEEKFREE_18TFT_h
#define _SEEKFREE_18TFT_h

#include "mn_spi.h"
#include "delay.h"
#include "sys.h"
#include "stdio.h"	
#include "SEEKFREE_FONT.h"


//--------------------���SPI--------------------


#define	TFT_SCL_SIMSPI_PIN 		C7				//����SPI_SCK����
#define	TFT_SDA_SIMSPI_PIN		C9   			//����SPI_MOSI����
#define TFT_REST_SIMSPI_PIN  	A9			//���帴λ����
#define TFT_DC_SIMSPI_PIN	  	B8				//Һ������λ���Ŷ���
#define TFT_CS_SIMSPI_PIN	  	C15				//����SPI_CS����
#define TFT_BL_SIMSPI_PIN	  	A15				//Һ���������Ŷ���  


#define	TFT_SCL_SIMSPI(x)	(PCout(7) = x)
#define	TFT_SDA_SIMSPI(x)	(PCout(9)	 = x)
#define TFT_REST_SIMSPI(x) 	(PAout(9) = x)	
#define TFT_DC_SIMSPI(x)   	(PBout(8)	 = x)
#define TFT_CS_SIMSPI(x) 	(PCout(15)	 = x)
#define TFT_BL_SIMSPI(x) 	(PAout(15)	 = x)



//--------------------Ӳ��SPI--------------------



//-----------------------------------------------    


//-------������ɫ��SEEKFREE_FONT.h�ļ��ж���----------
//#define RED          	    0xF800	//��ɫ
//#define BLUE         	    0x001F  //��ɫ
//#define YELLOW       	    0xFFE0	//��ɫ
//#define GREEN        	    0x07E0	//��ɫ
//#define WHITE        	    0xFFFF	//��ɫ
//#define BLACK        	    0x0000	//��ɫ 
//#define GRAY  			0X8430 	//��ɫ
//#define BROWN 			0XBC40 	//��ɫ
//#define PURPLE    		0XF81F	//��ɫ
//#define PINK    		    0XFE19	//��ɫ

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

//����д�ֱʵ���ɫ
#define TFT_PENCOLOR    RED

//���屳����ɫ
#define TFT_BGCOLOR	    WHITE

     
     
//������ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180
//2 ����ģʽ
//3 ����ģʽ  ��ת180
#define TFT_DISPLAY_DIR 2

#if (0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)
	#define	TFT_X_MAX	128	//Һ��X�����
	#define TFT_Y_MAX	160 //Һ��Y�����
#elif (2==TFT_DISPLAY_DIR || 3==TFT_DISPLAY_DIR)
	#define	TFT_X_MAX	160	//Һ��X�����
	#define TFT_Y_MAX	128 //Һ��Y�����
#else
#error "TFT_DISPLAY_DIR �������"
     
#endif

//--------------------���SPI--------------------
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
