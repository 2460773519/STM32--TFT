#include "timer.h"
#include "led.h"
#include "usart.h"
#include "mn_spi.h"
#include "LCD1602.h"
#include "key.h"
#include "my.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103������
//��ʱ���ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/11/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
int time_now=0;
//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
}

//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,8,8);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

//�ص���������ʱ���жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static u8 ii=0;
    if(htim==(&TIM3_Handler))
    {
			if(gengxin==0)
			{
				ii++;
				if(ii>2) 
				{
					ii=0;
					gengxin=1;
				}
			}
			
//				key_numd=get_key();
//			if(key_numd!=0) LED1=!LED1;
//			if(key_numd==1||(time_now==500&&se==3))
//			{
//			 n_i=0;ii=0;PBout(11)=0;delay_ms(1);PBout(11)=1;delay_ms(200);time_now=0;
//				gengxin=1;
//			} //����FFT����              B11
//			if(key_numd==5){PBout(12)=0;delay_ms(200);PBout(12)=1;}            //����FFTģ�鸴λ
//      if(key_numd==6){PBout(13)=0;delay_ms(200);PBout(13)=1;}            //����FFTģ�鸴λ
//			if(key_numd==7){PBout(14)=0;delay_ms(200);PBout(14)=1;}            //����FFTģ�鸴λ
//			if(key_numd==8){PBout(15)=0;delay_ms(200);PBout(15)=1;}   
			
			
     //����FFTģ�鸴λ
//			
			
//			display(13,0,data[ii],3);
//			if(ii>256) ii=0;
//			get_icm20602_accdata_simspi();
//			get_icm20602_gyro_simspi();
    //  LED0=!LED0;
    }
}
