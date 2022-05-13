#ifndef __MY1_H
#define __MY1_H

#include "led.h"
#include "sys.h"
#include "LCD1602.h"
#include "key.h"
#include "usart.h"
#include "math.h"
#include "SEEKFREE_18TFT.h"

extern u8 FFT_out[256];
extern u8 se;
extern u8 gengxin;
void caidan(void);
void FFT_display(void);
void TFT_xian(u8 x1,u8 y1,u8 x2,u8 y2,uint16 color);
void Init_FPGA(void);
void disp_zuobiao(void);
int find_max(u8 *p,int length,int *max);
void fqtl(u8 f_5[]);
void get_fudu(void);







#endif



