#ifndef __LCD_H_
#define __LCD_H_

#include "stdio.h"	
#include "sys.h"
#include "delay.h"
/**********************************
����ͷ�ļ�
**********************************/

typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned short int  uint16; /* 16 bits */
typedef unsigned long int   uint32; /* 32 bits */
typedef unsigned long long  uint64; /* 64 bits */

typedef char                int8;   /*  8 bits */
typedef short int           int16;  /* 16 bits */
typedef long  int           int32;  /* 32 bits */
typedef long  long          int64;  /* 64 bits */
typedef unsigned char INT8U;
typedef unsigned char uchar;
typedef unsigned char uint8;

typedef unsigned int INT16U;
typedef unsigned int uint;
#define u8 uint8
/**********************************
PIN�ڶ���
**********************************/
//#define LCD1602_DB  P0      //data bus ��������
//sbit LCD1602_RS = P3^5;
//sbit LCD1602_RW = P3^6;
//sbit LCD1602_EN = P3^4;	 
#define LCD1602_RS_1 PDout(0)=1
#define LCD1602_RS_0 PDout(0)=0

#define LCD1602_RW_1  PDout(1)=1
#define LCD1602_RW_0  PDout(1)=0

#define LCD1602_EN_1  PDout(2)=1
#define LCD1602_EN_0  PDout(2)=0


/**********************************
��������
**********************************/
void display(u8 x,u8 y,int num,int tt);
void lcd_gpio_ini(void);
void Read_Busy(void);           //æ��⺯�����ж�bit7��0������ִ�У�1��ֹ
void Lcd1602_Write_Cmd(unsigned char cmd);     //д����
void Lcd1602_Write_Data(unsigned char dat);   //д����
void LcdSetCursor(unsigned char x,unsigned char y);  //������ʾ
void DisplayOneChar (uchar X,uchar Y,uchar DData); // дһ���ֽ�
//��ʾһ���ֽ��ַ�
void DisplayOneStr (uchar X,uchar Y,uchar DData);
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);     //��ʾ�ַ���
void InitLcd1602(void);              //1602��ʼ��
					  

#endif
