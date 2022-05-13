#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "LCD1602.h"
#include "mn_spi.h"
#include "spi.h"
#include "key.h"
#include "math.h"
#include "my.h"
#include "SEEKFREE_18TFT.h"



u8 text_data=7;
u8 shangdian=1;
int ii=0;
float count_tt=0;
u8 can_matlab=0,matlab_num=0;
int main(void)
{
    HAL_Init();                    	 			//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   			//设置时钟,72M
    LED_Init();
		delay_init(72);  
	  uart_init_1(9600);
	  uart_init_3(9600);
	  SPI_5_gpio();
  	Init_FPGA();
    InitLcd1602(); 
	  LcdShowStr(0,0,"chenweichao");
  
	  disp_zuobiao();

  	while(1)
	  {

			if(key_numd==1||(gengxin==1&&se==3)||(se==4&&time_go==0)||shangdian==1)
			{

			  n_i=0;ii=0;PBout(11)=0;delay_ms(1);PBout(11)=1;delay_ms(200);time_now=0;
				gengxin=2;  
				shangdian=0;
				time_go=1;
			} //发送FFT数据               B11

		 if(time_go==2)
	   {
			 FFT_display();
			 time_go=0;
		 }
			
	  }
}
