#include "mn_spi.h"





///************************************模拟spi***************/
//-------宏定义引脚--------
short icm_gyro_y,icm_acc_z,icm_acc_y,icm_acc_x,icm_gyro_x,icm_gyro_z;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      通过SPI写一个byte,同时读取一个byte
//  @param      byte        发送的数据    
//  @return     uint8       return 返回status状态
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 icm_simspi_wr_byte(uint8 byte)
{
	  int i;
	  int tmep=0;
    for( i=0; i<8; i++)
    {
			  tmep=byte&0x80;
			 if(tmep) 
			 {
				 ICM20602_MOSI(1);
			 }
			 else
			 {
				 ICM20602_MOSI(0);
			 }
        byte <<= 1;
        ICM20602_SCK (0);  
				delay_us(1);			
        byte |= ICM20602_MISO;        
        ICM20602_SCK (1);
    }	
    return(byte);                                      		
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      将val写入cmd对应的寄存器地址,同时返回status字节
//  @param      cmd         命令字
//  @param      val         待写入寄存器的数值
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_w_reg_byte(uint8 cmd, uint8 val)
{
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_W;
    icm_simspi_wr_byte(cmd);                      	
    icm_simspi_wr_byte(val);                               	
    ICM20602_CSN (1);                                    	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_r_reg_byte(uint8 cmd, uint8 *val)
{
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_R;
    icm_simspi_wr_byte(cmd);                               	
    *val = icm_simspi_wr_byte(0);                           	
    ICM20602_CSN (1);                                    	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @param      num         读取的数量
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_r_reg_bytes(uint8 cmd, uint8 *val, uint8 num)
{
    uint16 i;
	  uint8 temp=0;
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_R;
    icm_simspi_wr_byte(cmd);                      	            
    for(i=0; i<num; i++)	
	{
        temp = icm_simspi_wr_byte(0);   
				val[i]=temp;    
	}		
    ICM20602_CSN (1);                                    		
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602自检函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm20602_self4_check(void)
{
    uint8 val;
    do
    {
        icm_simspi_r_reg_byte(ICM20602_WHO_AM_I,&val);
		  	display(0,1,val,5);
        //卡在这里原因有以下几点
        //1 MPU6050坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
    }while(0x12 != val);
}

void spi_gpio_ini(void)
{
    GPIO_InitTypeDef GPIO_Initure;

	//  __HAL_RCC_GPIOC_CLK_ENABLE();           	//开启GPIOD时钟
	  __HAL_RCC_GPIOA_CLK_ENABLE();           	//开启GPIOD时钟
	 
    GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	  GPIO_Initure.Pin=GPIO_PIN_6;
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	  GPIO_Initure.Pin=GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	  
	  ICM20602_CSN(1);
		ICM20602_SCK(1);
		ICM20602_MOSI(0);
   

}
void systick_delay_ms(int ms)
{
	delay_ms(ms);
}

void icm20602_init_simspi(void)
{
    uint8 val;
    
    spi_gpio_ini();
   
    icm20602_self4_check();//检测
    
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,0x80);//复位设备
    systick_delay_ms(2);
    do
    {//等待复位成功
        icm_simspi_r_reg_byte(ICM20602_PWR_MGMT_1,&val);
    }while(0x41 != val);
    
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,     0x01);            //时钟设置
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_2,     0x00);            //开启陀螺仪和加速度计
    icm_simspi_w_reg_byte(ICM20602_CONFIG,         0x01);            //176HZ 1KHZ
    icm_simspi_w_reg_byte(ICM20602_SMPLRT_DIV,     0x07);            //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm_simspi_w_reg_byte(ICM20602_GYRO_CONFIG,    0x18);            //±2000 dps
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG,   0x00);  //10          //±8g
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG_2, 0x23);            //Average 8 samples   44.8HZ
    
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata_simspi(void)
{
    uint8 dat[6];
    
    icm_simspi_r_reg_bytes(ICM20602_ACCEL_XOUT_H, dat, 6);
    icm_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro_simspi(void)
{
    uint8 dat[6];
    
    icm_simspi_r_reg_bytes(ICM20602_GYRO_XOUT_H, dat, 6);
    icm_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}
