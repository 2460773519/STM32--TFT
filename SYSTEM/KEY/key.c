#include "key.h"

u8 fx=0;
u8 key_numd=0;
void key_int(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();           	//开启GPIOE时钟
	  __HAL_RCC_GPIOC_CLK_ENABLE();           	//开启GPIOC时钟
	 
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|
	                   GPIO_PIN_2|GPIO_PIN_3; 				
	if(fx==0) GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//输出
	if(fx==1) GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	if(fx==0) {PEout(0)=0; PEout(1)=0; PEout(2)=0; PEout(3)=0;}
	
	
	GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5|
	                 GPIO_PIN_6; 				
	if(fx==1) GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//输出
	if(fx==0) GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	if(fx==1) {PEout(4)=0; PEout(5)=0; PEout(6)=0;}
	
		GPIO_Initure.Pin=GPIO_PIN_13;
	                  				
	if(fx==1) GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//输出
	if(fx==0) GPIO_Initure.Mode=GPIO_MODE_INPUT;     //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	if(fx==1) PCout(13)=0;
}

void SPI_5_gpio(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	//开启GPIOA时钟

	
    GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    PBout(11)=1;
	  PBout(12)=1;
	  PBout(13)=1;
	  PBout(14)=1;
	  PBout(15)=1;

}

u8 get_key(void)
{
	fx=0;
	key_int();
	if(PEin(4)==0) 
	{
		fx=1;
	  key_int();
		if(PEin(0)==0) return 1;
		if(PEin(1)==0) return 5;
		if(PEin(2)==0) return 9;
		if(PEin(3)==0) return 13;
	}
		
	if(PEin(5)==0) 
	{
		fx=1;
	  key_int();
		if(PEin(0)==0) return 2;
		if(PEin(1)==0) return 6;
		if(PEin(2)==0) return 10;
		if(PEin(3)==0) return 14;
	}
		
	if(PEin(6)==0) 
	{
		fx=1;
	  key_int();
		if(PEin(0)==0) return 3;
		if(PEin(1)==0) return 7;
		if(PEin(2)==0) return 11;
		if(PEin(3)==0) return 15;
	}
		
	if(PCin(13)==0) 
	{
		fx=1;
	  key_int();
		if(PEin(0)==0) return 4;
		if(PEin(1)==0) return 8;
		if(PEin(2)==0) return 12;
		if(PEin(3)==0) return 16;
	}
	return 0;
}

