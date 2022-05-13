#include "SEEKFREE_18TFT.h"


//-------------------------------------------------------------------------------------------------------------------
//  ���º�����ʹ�����SPIͨ�ţ���Ƚ�Ӳ��SPI�����SPI���Ÿ���������ʹ��������ͨIO
//-------------------------------------------------------------------------------------------------------------------


void TFT_SPI_GPIO_INIT(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	//����GPIOAʱ��
	  __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	  __HAL_RCC_GPIOC_CLK_ENABLE();           	//����GPIOAʱ��

    GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_15;				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
	  GPIO_Initure.Pin=GPIO_PIN_9|GPIO_PIN_15;				//PB8
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	  GPIO_Initure.Pin=GPIO_PIN_8;				//PB8
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeIndex_simspi(uint8 dat)			//д����
{	
	uint8 i=8;
	
  TFT_CS_SIMSPI(0);
	TFT_DC_SIMSPI(0);
	TFT_SCL_SIMSPI(0);
	
	while(i--)
	{
		if(dat&0x80){TFT_SDA_SIMSPI(1);}
		else{TFT_SDA_SIMSPI(0);}
		TFT_SCL_SIMSPI(1);
		
		TFT_SCL_SIMSPI(0);
		dat<<=1;
	}	
    TFT_CS_SIMSPI(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_simspi(uint8 dat)			//д����
{
    uint8 i=8;
	
    TFT_CS_SIMSPI(0);
	TFT_DC_SIMSPI(1);
	TFT_SCL_SIMSPI(0);
	while(i--)
	{
	  	if(dat&0x80){TFT_SDA_SIMSPI(1);}
	  	else{TFT_SDA_SIMSPI(0);}
	  	TFT_SCL_SIMSPI(1);
		
	  	TFT_SCL_SIMSPI(0);
	  	dat<<=1;
	}
    TFT_CS_SIMSPI(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_16bit_simspi(uint16 dat)	//��Һ����дһ��16λ����
{
	  uint8 i=16;
	
    TFT_CS_SIMSPI(0);
    TFT_DC_SIMSPI(1);
    TFT_SCL_SIMSPI(0);
	
	while(i--)
	{
	  	if(dat&0x8000){TFT_SDA_SIMSPI(1);}
	  	else{TFT_SDA_SIMSPI(0);}
	  	TFT_SCL_SIMSPI(1);
		
	  	TFT_SCL_SIMSPI(0);
	  	dat<<=1;
	}
	
    TFT_CS_SIMSPI(1);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����������
//  @param      x_start     	����x��������
//  @param      y_start     	����y��������
//  @param      x_end       	����x������յ�
//  @param      y_end       	����y������յ�
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_set_region(0,0,10,10);// x��y����㶼��0���յ㶼��10
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_region_simspi(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	

    
#if (0 == TFT_DISPLAY_DIR || 1 == TFT_DISPLAY_DIR)
    lcd_writeIndex_simspi(0x2a);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(x_start+2));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(x_end+2));

	lcd_writeIndex_simspi(0x2b);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_start+1));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_end+1));	

#elif(2 == TFT_DISPLAY_DIR || 3 == TFT_DISPLAY_DIR)
    lcd_writeIndex_simspi(0x2a);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(x_start+1));
	lcd_writeData_simspi(0x0);
	lcd_writeData_simspi((uint8)(x_end+1));

	lcd_writeIndex_simspi(0x2b);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_start+2));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_end+2));	

#endif
    
    lcd_writeIndex_simspi(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����������
//  @param      color     		��ɫ����
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_clear(YELLOW);// ȫ������Ϊ��ɫ
//-------------------------------------------------------------------------------------------------------------------
void lcd_clear_simspi(int color)
{
 	uint8 i,j;
	lcd_set_region_simspi(0,0,TFT_X_MAX-1,TFT_Y_MAX-1);
 	for (i=0;i<TFT_Y_MAX;i++)
    	for (j=0;j<TFT_X_MAX;j++)
        	lcd_writeData_16bit_simspi(color);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʼ��
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_init_simspi(void)
{	
	  TFT_SPI_GPIO_INIT();
	
    TFT_REST_SIMSPI(0);
    delay_ms(10);
    TFT_REST_SIMSPI(1);
    delay_ms(120);
    lcd_writeIndex_simspi(0x11);
    delay_ms(120);

    lcd_writeIndex_simspi(0xB1); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB2); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB3); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB4);
    lcd_writeData_simspi(0x07); 

    lcd_writeIndex_simspi(0xC0); 
    lcd_writeData_simspi(0xA2); 
    lcd_writeData_simspi(0x02); 
    lcd_writeData_simspi(0x84); 
    lcd_writeIndex_simspi(0xC1); 
    lcd_writeData_simspi(0xC5); 
    
    lcd_writeIndex_simspi(0xC2); 
    lcd_writeData_simspi(0x0A); 
    lcd_writeData_simspi(0x00); 
    
    lcd_writeIndex_simspi(0xC3); 
    lcd_writeData_simspi(0x8A); 
    lcd_writeData_simspi(0x2A); 
    lcd_writeIndex_simspi(0xC4); 
    lcd_writeData_simspi(0x8A); 
    lcd_writeData_simspi(0xEE); 
    
    lcd_writeIndex_simspi(0xC5);
    lcd_writeData_simspi(0x0E); 
    
    lcd_writeIndex_simspi(0x36);
    switch(TFT_DISPLAY_DIR)//y x v
    {
        case 0: lcd_writeData_simspi(1<<7 | 1<<6 | 0<<5);  break;  //����ģʽ
        case 1: lcd_writeData_simspi(0<<7 | 0<<6 | 0<<5);  break;  //����ģʽ  ��ת180
        case 2: lcd_writeData_simspi(1<<7 | 0<<6 | 1<<5);  break;  //����ģʽ
        case 3: lcd_writeData_simspi(0<<7 | 1<<6 | 1<<5);  break;  //����ģʽ  ��ת180
    }

    lcd_writeIndex_simspi(0xe0); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x1a); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x18); 
    lcd_writeData_simspi(0x2f); 
    lcd_writeData_simspi(0x28); 
    lcd_writeData_simspi(0x20); 
    lcd_writeData_simspi(0x22); 
    lcd_writeData_simspi(0x1f); 
    lcd_writeData_simspi(0x1b); 
    lcd_writeData_simspi(0x23); 
    lcd_writeData_simspi(0x37); 
    lcd_writeData_simspi(0x00); 	
    lcd_writeData_simspi(0x07); 
    lcd_writeData_simspi(0x02); 
    lcd_writeData_simspi(0x10); 
    
    lcd_writeIndex_simspi(0xe1); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x1b); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x17); 
    lcd_writeData_simspi(0x33); 
    lcd_writeData_simspi(0x2c); 
    lcd_writeData_simspi(0x29); 
    lcd_writeData_simspi(0x2e); 
    lcd_writeData_simspi(0x30); 
    lcd_writeData_simspi(0x30); 
    lcd_writeData_simspi(0x39); 
    lcd_writeData_simspi(0x3f); 
    lcd_writeData_simspi(0x00); 
    lcd_writeData_simspi(0x07); 
    lcd_writeData_simspi(0x03); 
    lcd_writeData_simspi(0x10);  
    
    lcd_writeIndex_simspi(0x2a);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x00+2);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x80+2);
    
    lcd_writeIndex_simspi(0x2b);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x00+3);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x80+3);
    
    lcd_writeIndex_simspi(0xF0); 
    lcd_writeData_simspi(0x01); 
    lcd_writeIndex_simspi(0xF6);
    lcd_writeData_simspi(0x00); 
    
    lcd_writeIndex_simspi(0x3A);
    lcd_writeData_simspi(0x05); 
    lcd_writeIndex_simspi(0x29);

    lcd_clear_simspi(WHITE);//ȫ��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ������
//  @param      x     	        ����x��������
//  @param      y     	        ����y��������
//  @param      dat       	    ��Ҫ��ʾ����ɫ
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_drawpoint(0,0,RED);  //����0,0��һ����ɫ�ĵ�
//-------------------------------------------------------------------------------------------------------------------
void lcd_drawpoint_simspi(uint16 x,uint16 y,uint16 color)
{
    lcd_set_region_simspi(x,y,x,y);
    lcd_writeData_16bit_simspi(color);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ�ַ�
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ���ַ�
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showchar(0,0,'x');//����0,0дһ���ַ�x
//-------------------------------------------------------------------------------------------------------------------
void lcd_showchar_simspi(uint16 x,uint16 y,const int8 dat)
{
	uint8 i,j;
	uint8 temp;
    
	for(i=0; i<16; i++)
	{
		lcd_set_region_simspi(x,y+i,x+7,y+i);
		temp = tft_ascii[dat-32][i];//��32��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո���ascii�������32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	lcd_writeData_16bit_simspi(TFT_PENCOLOR);
			else			lcd_writeData_16bit_simspi(TFT_BGCOLOR);
			temp>>=1;
		}
	}
}


void lcd_showchar_simspi_my(uint16 x,uint16 y,const int8 dat)
{
	uint8 i,j;
	uint8 temp;
    
	for(i=0; i<16; i++)
	{
		lcd_set_region_simspi(x,y+i,x+7,y+i);
		temp = tft_ascii_my[dat-32][i];//��32��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո���ascii�������32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	lcd_writeData_16bit_simspi(TFT_PENCOLOR);
			else			lcd_writeData_16bit_simspi(TFT_BGCOLOR);
			temp>>=1;
		}
	}
}
const uint8  my_name_1[][16] = 
{


{0x20,0x00,0x20,0x40,0xFE,0x43,0x20,0x20,0x20,0x10,0xFC,0x89,0x00,0x80,0xFC,0x41},
{0x04,0x21,0x04,0x11,0xFC,0x89,0x00,0x80,0x88,0x40,0xD0,0x23,0x3E,0x10,0x04,0x0C},/*"��",0*/
/* (16 X 16 , ���� )*/

{0x20,0x04,0x20,0x08,0x20,0x08,0x20,0x00,0xFF,0x7F,0x20,0x01,0x20,0x11,0x20,0x11},
{0x20,0x09,0x10,0x05,0x10,0x03,0x08,0x41,0x88,0x41,0x44,0x41,0x22,0x7E,0x01,0x00},/*"��",1*/
/* (16 X 16 , ���� )*/

{0x84,0x20,0x08,0x21,0x08,0x11,0x1F,0x00,0xD0,0x7F,0x08,0x04,0x08,0x04,0x9C,0x3F},
{0x2A,0x04,0x09,0x04,0xC8,0x7F,0x08,0x04,0x08,0x04,0x08,0x04,0x08,0x04,0x08,0x04},/*"��",2*/
/* (16 X 16 , ���� )*/

{0x10,0x00,0x10,0xFF,0x14,0x08,0x74,0x04,0x14,0x7F,0x14,0x41,0xFE,0x49,0x00,0x49},
{0x10,0x49,0x54,0x49,0x54,0x49,0x54,0x45,0x42,0x14,0x20,0x22,0x18,0x41,0x86,0x80},/*"Ƶ",0*/
/* (16 X 16 , ���� )*/

{0x40,0x10,0x82,0x08,0xE4,0x3F,0x04,0x05,0x20,0x25,0x40,0x15,0xF7,0x7F,0x04,0x00},
{0xC4,0x1F,0x44,0x10,0x44,0x10,0xC4,0x1F,0x54,0x10,0x4C,0x10,0xC4,0x1F,0x40,0x10},/*"��",1*/
/* (16 X 16 , ���� )*/

{0x00,0x02,0x20,0x02,0x20,0x04,0x10,0x04,0x08,0x08,0x04,0x10,0x02,0x20,0xF9,0x47},
{0x20,0x04,0x20,0x04,0x20,0x04,0x10,0x04,0x10,0x04,0x08,0x04,0x84,0x02,0x02,0x01},/*"��",2*/
/* (16 X 16 , ���� )*/

{0x08,0x10,0x08,0x38,0x88,0x07,0x88,0x00,0xBF,0x00,0x88,0x00,0x8C,0x7F,0x9C,0x08},
{0xAA,0x08,0x8A,0x08,0x89,0x08,0x88,0x08,0x88,0x08,0x48,0x08,0x48,0x08,0x28,0x08},/*"��",3*/
/* (16 X 16 , ���� )*/

{0x10,0x01,0x10,0x12,0x50,0x12,0x48,0x10,0x48,0x10,0x8C,0x08,0x8C,0x08,0x8A,0x08},
{0x09,0x05,0x08,0x05,0x08,0x02,0x08,0x02,0x08,0x05,0x88,0x08,0x48,0x10,0x28,0x60},/*"��",4*/
/* (16 X 16 , ���� )*/

{0x00,0x00,0x00,0x00,0x20,0x30,0x20,0x0C,0x10,0x00,0xE0,0x3E,0x98,0x12,0x98,0x0C},
{0x58,0x60,0x10,0x5F,0x10,0x59,0x10,0x49,0x10,0x79,0x10,0x46,0x00,0x00,0x00,0x00},/*"��",0*/
/* (16 X 16 , ���� )*/

{0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x0E,0xF0,0x03,0xD0,0x04,0x90,0x0B,0xF0,0x02},
{0x90,0x01,0x10,0x07,0x88,0x02,0x88,0x02,0x04,0x03,0x82,0x0C,0x70,0x78,0x00,0x00},/*"��",1*/
/* (16 X 16 , ���� )*/

{0x00,0x00,0x00,0x18,0x10,0x09,0x30,0x05,0x00,0x1E,0x00,0x15,0x58,0x15,0x8E,0x0D},
{0x08,0x7F,0xC8,0x08,0x88,0x17,0x98,0x10,0x08,0x0B,0x80,0x10,0x00,0x0F,0x00,0x00},/*"��",2*/
/* (16 X 16 , ���� )*/

{0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x08,0x88,0x08,0xB0,0x04,0xA0,0x02,0x80,0x0C},
{0xF8,0x1B,0x00,0x08,0x00,0x0F,0xE0,0x08,0x00,0x08,0x80,0x0F,0x70,0x00,0x00,0x00},/*"��",0*/
/* (16 X 16 , ���� )*/

{0x00,0x00,0x00,0x04,0x20,0x04,0x40,0x02,0x00,0x7E,0xFE,0x09,0x00,0x08,0x78,0x0A},
{0x48,0x0A,0x78,0x0A,0x48,0x0A,0x78,0x0A,0x48,0x10,0x60,0x1C,0x40,0x08,0x00,0x00},/*"ǰ",1*/
/* (16 X 16 , ���� )*/

{0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x3F,0xE0,0x04,0x28,0x1A,0xF8,0x25,0x24,0x29},
{0xA4,0x25,0x64,0x25,0x20,0x25,0x20,0x1C,0x10,0x32,0x0C,0x21,0x80,0x00,0x00,0x00},/*"Ƶ",2*/
/* (16 X 16 , ���� )*/

{0x00,0x00,0x80,0x00,0x80,0x07,0xE0,0x00,0x40,0x0A,0xD8,0x01,0xB0,0x08,0x48,0x13},
{0xE8,0x00,0x00,0x71,0xFE,0x0F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x00},/*"��",3*/
/* (16 X 16 , ���� )*/





};
void lcd_showchar_simspi_my_name(uint16 x,uint16 y,const int8 dat)
{
	uint8 i,j,t;
	uint8 temp;
    
	for(t=0;t<2;t++)
	{
	for(i=0; i<16; i++)
	{
		lcd_set_region_simspi(x,y+i,x+15,y+i);
		temp = my_name_1[t][i];//��32��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո���ascii�������32
		for(j=0; j<8; j++)
		{
			if(temp&0x80)	lcd_writeData_16bit_simspi(TFT_PENCOLOR);
			else			lcd_writeData_16bit_simspi(TFT_BGCOLOR);
			temp<<=1;
		}
	}
  }
}

void LCD_Show_CH_Font16(u16 x,u16 y,u8 index)
{      
		u8 temp,t,t1;
		u16 y0=x;   
    for(t=0;t<32;t++)//ÿ��16*16�ĺ��ֵ��� ��32���ֽ�
    {   
				if(t<16)temp=my_name_1[index*2][t];      //ǰ16���ֽ�
				else temp=my_name_1[index*2+1][t-16];    //��16���ֽ�                          
					for(t1=0;t1<8;t1++)
				{// lcd_drawpoint(0,0,RED);
				if(temp&0x01) lcd_drawpoint_simspi(x,y,TFT_PENCOLOR);//��ʵ�ĵ�
				else          lcd_drawpoint_simspi(x,y,WHITE);   //���հ׵㣨ʹ�ñ���ɫ��
				temp>>=1;
				x++;
				if((x-y0)==16)
				{
				x=y0;
				y++;
				break;
				}
				}    
						}          
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ�ַ���
//  @param      x     	        ����x��������  ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y��������  ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ���ַ���
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showstr(0,0,"seekfree");
//-------------------------------------------------------------------------------------------------------------------
void lcd_showstr_simspi(uint16 x,uint16 y,const int8 dat[])
{
	uint16 j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		lcd_showchar_simspi(x+8*j,y*16,dat[j]);
		j++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ8λ�з���
//  @param      x     	        ����x��������  ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y��������  ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������int8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint8(0,0,x);//xΪint8����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint8_simspi(uint16 x,uint16 y,int8 dat)
{
	uint8 a[3];
	uint8 i=0;
	if(dat<0)
	{
		lcd_showchar_simspi(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar_simspi(x,y*16,' ');
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ8λ�޷���
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������uint8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint8(0,0,x);//xΪuint8����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint8_simspi(uint16 x,uint16 y,uint8 dat)
{
	uint8 a[3];
	uint8 i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ16λ�з���
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������int16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint16(0,0,x);//xΪint16����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint16_simspi(uint16 x,uint16 y,int16 dat)
{
	uint8 a[5];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar_simspi(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar_simspi(x,y*16,' ');

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

void lcd_showint16_simspi_my(uint16 x,uint16 y,int16 dat)
{
	uint8 a[3];
	uint8 i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ16λ�޷���
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������uint16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint16(0,0,x);//xΪuint16����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint16_simspi(uint16 x,uint16 y,uint16 dat)
{
	uint8 a[5];
	uint8 i;

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ32λ�з���(ȥ������������Ч��0)
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������uint32
//  @param      num       	    ��Ҫ��ʾ��λ�� ���10λ  ������������
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint32(0,0,x,3);//x����Ϊint32 uint16 int16 uint8 int8����
//  Sample usage:               ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint32_simspi(uint16 x,uint16 y,int32 dat,uint8 num)
{
    int8    buff[34];
    uint8   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//����
    else
    {
        buff[0] = ' ';
        length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';

    lcd_showstr_simspi(x, y, buff);	//��ʾ����
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ������(ȥ������������Ч��0)
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������float��double
//  @param      num       	    ����λ��ʾ����   ���10λ  
//  @param      pointnum        С��λ��ʾ����   ���6λ
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showfloat(0,0,x,2,3);//��ʾ������   ������ʾ2λ   С����ʾ��λ
//  @note                       �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//                              ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//                              �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//                              ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void lcd_showfloat_simspi(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum)
{
    uint8   length;
	int8    buff[34];
	int8    start,end,point;

	if(6<pointnum)  pointnum = 6;
    if(10<num)      num = 10;
        
    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//����
    else
    {
        length = zf_sprintf( &buff[1],"%f",dat);
        length++;
    }
    point = length - 7;         //����С����λ��
    start = point - num - 1;    //������ʼλ
    end = point + pointnum + 1; //�������λ
    while(0>start)//����λ����  ĩβӦ�����ո�
    {
        buff[end] = ' ';
        end++;
        start++;
    }
    
    if(0>dat)   buff[start] = '-';
    else        buff[start] = ' ';
    
    buff[end] = '\0';

    lcd_showstr_simspi(x, y, buff);	//��ʾ����
}


//-------------------------------------------------------------------------------------------------------------------
//  ���º�����ʹ��Ӳ��SPIͨ�ţ���Ƚ����IIC���ٶȱ����IIC�졣
//-------------------------------------------------------------------------------------------------------------------
