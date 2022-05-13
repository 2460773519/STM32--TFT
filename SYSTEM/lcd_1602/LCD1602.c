#include "LCD1602.h"


void in_io()
{
	  GPIO_InitTypeDef GPIO_Initure;
	
    GPIO_Initure.Pin=GPIO_PIN_7; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

}
void out_io()
{
	  GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin=GPIO_PIN_7; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

}

void lcd_cmd(u8 cmd)
{
	 u8 tmep=0;
	 u8 sz[8]={0};
   u8 i=0;
	 tmep=cmd;
	 
	 for(i=0;i<8;i++)
	 {
		 sz[i]=tmep&(0x01);
		 tmep=tmep>>1;
	 }
	 PDout(7)= sz[7];
	 PDout(6)= sz[6];
	 PDout(5)= sz[5];
	 PDout(4)= sz[4];

	 LCD1602_EN_1; 
   delay_ms(1);
	 LCD1602_EN_0; 
//	  Read_Busy();

	 PDout(7)= sz[3];
	 PDout(6)= sz[2];
	 PDout(5)= sz[1];
	 PDout(4)= sz[0];

	 LCD1602_EN_1; 
	 delay_ms(1);
	 LCD1602_EN_0; 
//	 delay_ms(5);
}

void lcd_cmd_dd(u8 cmd)
{
	 u8 tmep=0;
	 u8 sz[8]={0};
   u8 i=0;
	 tmep=cmd;
	 for(i=0;i<8;i++)
	 {
		 sz[i]=tmep&(0x01);
		 tmep=tmep>>1;
	 }
	 PDout(7)= sz[7];
	 PDout(6)= sz[6];
	 PDout(5)= sz[5];
	 PDout(4)= sz[4];

	 LCD1602_EN_1; 
   delay_ms(1);
	 LCD1602_EN_0; 
	 


}
void lcd_gpio_ini(void)
{
    GPIO_InitTypeDef GPIO_Initure;

	  __HAL_RCC_GPIOD_CLK_ENABLE();           	//开启GPIOD时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6| GPIO_PIN_7; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);


	
   LCD1602_RS_0;
	 LCD1602_RW_0;
	 LCD1602_EN_0;
}

void Read_Busy()           //忙检测函数，判断bit7是0，允许执行；1禁止
{
	  PDout(7)=1;
	  in_io();
    LCD1602_RS_0;
    LCD1602_RW_1;
    LCD1602_EN_1;
    while(PDin(7));  //等待LCM不忙
    LCD1602_EN_0;
	  out_io();
}

void Lcd1602_Write_Cmd(unsigned char cmd)     //写命令
{
    Read_Busy();
    LCD1602_RS_0;
    LCD1602_RW_0;
    lcd_cmd(cmd); 
	  //delay_ms(5);
}

void Lcd1602_Write_Cmd_dd(unsigned char cmd)     //写命令
{
	 // Read_Busy();
    LCD1602_RS_0;
    LCD1602_RW_0;
    lcd_cmd_dd(cmd); 
	  //delay_ms(5);
}

void Lcd1602_Write_Data(unsigned char dat)   //写数据
{
      Read_Busy();
      LCD1602_RS_1;       
      LCD1602_RW_0;
      lcd_cmd(dat);
      delay_ms(5);	
}

void LcdSetCursor(unsigned char x,unsigned char y)  //坐标显示
{
    unsigned char addr;
    if(y == 0)
        addr = 0x00 + x;
    else
        addr = 0x40 + x;
    
    Lcd1602_Write_Cmd(addr|0x80);
}
//*************************显示一个字节数据
void DisplayOneChar (uchar X,uchar Y,uchar DData)
{
 if(Y) X|=0X40;   //Y=1显示第二行，Y=0显示第一行
 X|=0X80;
 Lcd1602_Write_Cmd(X); //X用来选择哪一位
 Lcd1602_Write_Data(DData); //DData用来写数据
}

//显示一个字节字符
void DisplayOneStr (uchar X,uchar Y,uchar DData)
{
	DisplayOneChar (X++,Y,DData/16 + '0');
	DisplayOneChar (X,Y,DData%16 + '0');
}
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str)     //显示字符串
{
    LcdSetCursor(x,y);      //当前字符的坐标
    while(*str != '\0')
    {
        Lcd1602_Write_Data(*str++);
    }
}
void display(u8 x,u8 y,int num,int tt)
{
	int i=0;
	u8 sz[10]={0};
	u8 sz1[10]={0};
	
 // LcdShowStr(x,y,"     ");
	if(num>=0)
	{
		for(i=0;i<tt;i++)
		{
			sz[i]=num%10+'0';
			num=num/10;
		}
		
		for(i=0;i<tt;i++)
		{
			sz1[i]=sz[tt-1-i];
		}
		sz1[tt]='\0';
    if(x==0) LcdShowStr(x,y," ");
		else     LcdShowStr(x-1,y," ");
		
		LcdShowStr(x,y,sz1);
  }
	else
	{
		num=-num;
			for(i=0;i<tt;i++)
		{
			sz[i]=num%10+'0';
			num=num/10;
		}
		
		for(i=0;i<tt;i++)
		{
			sz1[i]=sz[tt-1-i];
		}
		sz1[tt]='\0';
		if(x==0) LcdShowStr(x,y,"-");
		else     LcdShowStr(x-1,y,"-");
			
		LcdShowStr(x,y,sz1);
	}

}
  

void InitLcd1602()              //1602初始化
{
	int i=0;
   delay_ms(300);
	  lcd_gpio_ini();
//    Lcd1602_Write_Cmd_dd(0x22);  //四线nb
//   	Lcd1602_Write_Cmd_dd(0x22);  //四线nb
//		Lcd1602_Write_Cmd_dd(0x22);  //四线nb
////	
//	  Lcd1602_Write_Cmd(0x28);
	for(i=5;i>0;i--)
	{
		 Lcd1602_Write_Cmd(0x28);
	}

    Lcd1602_Write_Cmd(0x01);
    Lcd1602_Write_Cmd(0x06);
		Lcd1602_Write_Cmd(0x0f);    //清屏 
    Lcd1602_Write_Cmd(0x0c);    //清屏 
  
}
