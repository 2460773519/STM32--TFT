#ifndef __LCD_H_
#define __LCD_H_

#include "stdio.h"	
#include "sys.h"
#include "delay.h"
/**********************************
包含头文件
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
PIN口定义
**********************************/
//#define LCD1602_DB  P0      //data bus 数据总线
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
函数声明
**********************************/
void display(u8 x,u8 y,int num,int tt);
void lcd_gpio_ini(void);
void Read_Busy(void);           //忙检测函数，判断bit7是0，允许执行；1禁止
void Lcd1602_Write_Cmd(unsigned char cmd);     //写命令
void Lcd1602_Write_Data(unsigned char dat);   //写数据
void LcdSetCursor(unsigned char x,unsigned char y);  //坐标显示
void DisplayOneChar (uchar X,uchar Y,uchar DData); // 写一个字节
//显示一个字节字符
void DisplayOneStr (uchar X,uchar Y,uchar DData);
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);     //显示字符串
void InitLcd1602(void);              //1602初始化
					  

#endif
