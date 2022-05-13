#include "my.h"

int fft_read[128]={0};
int fft_imag[128]={0};
int rus[128]={0};
u8 se=4;
u8 gengxin=0;
u8 t=0;
u8 FFT_out[256]={0};   //     0       1        2       3
u8 DAC_bili=2; // 0 1 2 3 =>> 0.5     2        4       6      //幅值缩放
u8 DAC_lei=0;  // 0 1 2 3 =>> 正弦    矩形     三角    锯齿
u8 DAC_F1=2;   // 0 1 2 3 =>> 400K    200K     100K     1 K 
u8 DAC_Fc=1;   // 0 1 2 3 =>> 25M     2.5M     250K    2.5K  ; 可以采10M到 20HZ的信号
u8 FPGA_constant=0;  //8位高到低位 DAC_Fc DAC_F1 DAC_lei DAC_bili
u8 ddd_bbb=20;      //幅值 500mv = 16, 300mv =10   1000mv= 32; 
void caidan(void)
{
	if(se!=3&&se!=4) lcd_showstr_simspi(0,t,"->");
	if(key_numd==13)
	{
		t=t+1;
		if(t>5) t=5;
		key_numd=0;
			lcd_clear_simspi(WHITE);
	}
	if(key_numd==9)
	{
		t=t-1;
		if(t<0) t=0;
		key_numd=0;
		lcd_clear_simspi(WHITE);
	}
	
	if(key_numd==15)
	{
		if(t==0) se=1;
		if(t==1) se=2;
		if(t==2) {se=3;}
		if(t==3){ se=4; disp_zuobiao();}
		t=0;
		lcd_clear_simspi(WHITE);
	}
	
	if(se==0)  //目录
	{
		lcd_showstr_simspi(20,0,"FPGA_Parameter");
		lcd_showstr_simspi(20,1,"STM32_Parameter");
		lcd_showstr_simspi(20,2,"FFT_display");
		lcd_showstr_simspi(20,3,"time_now_display");
		
		LCD_Show_CH_Font16(20,90,3);
		LCD_Show_CH_Font16(40,90,4);
		LCD_Show_CH_Font16(60,90,5);
		LCD_Show_CH_Font16(80,90,6);
		LCD_Show_CH_Font16(100,90,7);

		
		LCD_Show_CH_Font16(20,70,0);
		LCD_Show_CH_Font16(40,70,0);
		LCD_Show_CH_Font16(60,70,0);
	}
	
	if(se==1) 
	{
		lcd_showstr_simspi(20,0,"DAC_bili:"); lcd_showuint8_simspi(100,0,DAC_bili);
		lcd_showstr_simspi(20,1,"DAC_lei:");  lcd_showuint8_simspi(100,1,DAC_lei);
		lcd_showstr_simspi(20,2,"DAC_F1:");   lcd_showuint8_simspi(100,2,DAC_F1); 
		lcd_showstr_simspi(20,3,"DAC_Fc:");   lcd_showuint8_simspi(100,3,DAC_Fc);
		
		lcd_showstr_simspi(20,4,"OK_Send_to_FPGA");
		
		lcd_showstr_simspi(20,7,"NOW_STA");   lcd_showuint8_simspi(100,7,FPGA_constant);

		
		if(key_numd==10)
		{
			if(t==0) DAC_bili=DAC_bili+1;
			if(t==1) DAC_lei=DAC_lei+1;
			if(t==2) DAC_F1=DAC_F1+1;
			if(t==3) DAC_Fc=DAC_Fc+1;
			
			  FPGA_constant=0;
			  FPGA_constant=(FPGA_constant|DAC_Fc)<<2;
				FPGA_constant=(FPGA_constant|DAC_F1)<<2;
		    FPGA_constant=(FPGA_constant|DAC_lei)<<2;
				FPGA_constant=(FPGA_constant|DAC_bili);
				//8位高到低位 DAC_Fc DAC_F1 DAC_lei DAC_bili；
				HAL_UART_Transmit(&UART3_Handler,&FPGA_constant,1,1000);
		}
		
		if(key_numd==14)
		{
			if(t==0) DAC_bili=DAC_bili-1;
			if(t==1) DAC_lei=DAC_lei-1;
			if(t==2) DAC_F1=DAC_F1-1;
			if(t==3) DAC_Fc=DAC_Fc-1;
			
		  	FPGA_constant=0;
			  FPGA_constant=(FPGA_constant|DAC_Fc)<<2;
				FPGA_constant=(FPGA_constant|DAC_F1)<<2;
		    FPGA_constant=(FPGA_constant|DAC_lei)<<2;
				FPGA_constant=(FPGA_constant|DAC_bili);
				//8位高到低位 DAC_Fc DAC_F1 DAC_lei DAC_bili；
				HAL_UART_Transmit(&UART3_Handler,&FPGA_constant,1,1000);
		}
		}
	

  if(se==3) 
	{
		if(gengxin==3)
		{		
			disp_zuobiao();
			FFT_display();
			gengxin=0;
		}
	}
	
	if(se==4) 
	{
		 if(time_go==2)
	   {
			 FFT_display();
			// fqtl();
			 time_go=0;
		 }
	}
	
	if(key_numd==11)
	{
		
		lcd_clear_simspi(WHITE);
		if(se==1){ se=4;	disp_zuobiao();}
		else se=0;
		t=0;		
	}
	

	
}
void TFT_xian(u8 x1,u8 y1,u8 x2,u8 y2,uint16 color)  //上连下
{
	u8 n=0,m=0;
	float k=0;
	if(y1==y2&&x2==x1)
	{
			lcd_drawpoint_simspi(x1,y1,color);
	}
	else
	{
		if(abs(y2-y1)<=abs((x2-x1)))
		{
			if(x2>=x1)
			{
				k=100*(y2-y1)/(x2-x1);
				for(n=x1;n<(x2);n++)
				{
					lcd_drawpoint_simspi(n,y1+k*(n-x1)/100,color);
				}
			}
			else
			{
				k=100*(y2-y1)/(x2-x1);
				for(n=x2;n<(x1);n++)
				{
					lcd_drawpoint_simspi(n,y1+k*(n-x1)/100,color);
				}
			}
		}
		else 
		{
			if(y2>y1)
			{
				k=100*(x2-x1)/(y2-y1);
				for(n=y1;n<(y2);n++)
				{
					lcd_drawpoint_simspi(x1+k*(n-y1)/100,n,color);
				}
			}
			else
			{
				k=100*(x2-x1)/(y2-y1);
				for(n=y2;n<(y1);n++)
				{
					lcd_drawpoint_simspi(x1+k*(n-y1)/100,n,color);
				}
			}
		}
	}	


}

void FFT_display(void)
{
	
	u8 m=0,n=0;
	int temp=0;
  uint32 now_max_wei=0;
	int mmm=0;
	u8 fff_5[5]={0};
	

  get_fudu();
	
	now_max_wei=find_max(FFT_out,128,&mmm);
	
	lcd_showint16_simspi(90,1,mmm*(1000/32.0));
	
  lcd_showstr_simspi(140,1,"MV");
	for(n=2;n<128;n++)
	{
		if(FFT_out[n]<=4) FFT_out[n]=FFT_out[n];
	 	FFT_out[n]= (FFT_out[n]+FFT_out[n-1]+FFT_out[n+1])/3;
	}
	
	fqtl(fff_5);
////////////////////////////////////////////////////0/////////////////////////////////////
  	//now_max_wei=find_max(FFT_out,127,&mmm); //(i+2)*10
    now_max_wei=fff_5[0];
  	if(DAC_Fc==3) now_max_wei=(2500/256)*now_max_wei;
		if(DAC_Fc==2) now_max_wei=(250000/256)*now_max_wei;
 	  if(DAC_Fc==1) now_max_wei=(2500000/256)*now_max_wei;
	  if(DAC_Fc==0) now_max_wei=(25000000/256)*now_max_wei;
	  if(now_max_wei>=1000000){now_max_wei=now_max_wei/1000000; lcd_showstr_simspi(122,0,"MHZ");}
	  else if(now_max_wei>=1000){now_max_wei=now_max_wei/1000; lcd_showstr_simspi(122,0,"KHZ");}
		else lcd_showstr_simspi(120,0,"HZ");	
	if(now_max_wei>10)
	{
		 if(now_max_wei%10>=6) 
	 {
		 now_max_wei=now_max_wei-now_max_wei%10+10;
	 }
	 else
	 {	
		 now_max_wei=now_max_wei-now_max_wei%10;
	 }
	}	
	 lcd_showint16_simspi_my(85,0,now_max_wei);
	display(7,1,now_max_wei,4);
	LcdShowStr(0,1,"now_pl");
	LcdShowStr(12,1,"KHZ");
	//////////////////////////////////1////////////////////////////////////////////
	  now_max_wei=fff_5[1];
  	if(DAC_Fc==3) now_max_wei=(2500/256)*now_max_wei;
		if(DAC_Fc==2) now_max_wei=(250000/256)*now_max_wei;
 	  if(DAC_Fc==1) now_max_wei=(2500000/256)*now_max_wei;
	  if(DAC_Fc==0) now_max_wei=(25000000/256)*now_max_wei;
	  if(now_max_wei>=1000000){now_max_wei=now_max_wei/1000000;}
	  else if(now_max_wei>=1000){now_max_wei=now_max_wei/1000;}

	if(now_max_wei>10)
	{
		 if(now_max_wei%10>=6) 
	 {
		 now_max_wei=now_max_wei-now_max_wei%10+10;
	 }
	 else
	 {	
		 now_max_wei=now_max_wei-now_max_wei%10;
	 }
	}	
	 lcd_showint16_simspi_my(25,1,now_max_wei);
		//////////////////////////////////2////////////////////////////////////////////
	  now_max_wei=fff_5[2];
  	if(DAC_Fc==3) now_max_wei=(2500/256)*now_max_wei;
		if(DAC_Fc==2) now_max_wei=(250000/256)*now_max_wei;
 	  if(DAC_Fc==1) now_max_wei=(2500000/256)*now_max_wei;
	  if(DAC_Fc==0) now_max_wei=(25000000/256)*now_max_wei;
	  if(now_max_wei>=1000000){now_max_wei=now_max_wei/1000000;}
	  else if(now_max_wei>=1000){now_max_wei=now_max_wei/1000;}

	if(now_max_wei>10)
	{
		 if(now_max_wei%10>=6) 
	 {
		 now_max_wei=now_max_wei-now_max_wei%10+10;
	 }
	 else
	 {	
		 now_max_wei=now_max_wei-now_max_wei%10;
	 }
	}	
	 lcd_showint16_simspi_my(55,1,now_max_wei);
		//////////////////////////////////3////////////////////////////////////////////
	  now_max_wei=fff_5[3];
  	if(DAC_Fc==3) now_max_wei=(2500/256)*now_max_wei;
		if(DAC_Fc==2) now_max_wei=(250000/256)*now_max_wei;
 	  if(DAC_Fc==1) now_max_wei=(2500000/256)*now_max_wei;
	  if(DAC_Fc==0) now_max_wei=(25000000/256)*now_max_wei;
	  if(now_max_wei>=1000000){now_max_wei=now_max_wei/1000000;}
	  else if(now_max_wei>=1000){now_max_wei=now_max_wei/1000;}

	if(now_max_wei>10)
	{
		 if(now_max_wei%10>=6) 
	 {
		 now_max_wei=now_max_wei-now_max_wei%10+10;
	 }
	 else
	 {	
		 now_max_wei=now_max_wei-now_max_wei%10;
	 }
	}	
	// lcd_showint16_simspi_my(85,1,now_max_wei);
	
		//////////////////////////////////3////////////////////////////////////////////
	  now_max_wei=fff_5[4];
  	if(DAC_Fc==3) now_max_wei=(2500/256)*now_max_wei;
		if(DAC_Fc==2) now_max_wei=(250000/256)*now_max_wei;
 	  if(DAC_Fc==1) now_max_wei=(2500000/256)*now_max_wei;
	  if(DAC_Fc==0) now_max_wei=(25000000/256)*now_max_wei;
	  if(now_max_wei>=1000000){now_max_wei=now_max_wei/1000000;}
	  else if(now_max_wei>=1000){now_max_wei=now_max_wei/1000;}

	if(now_max_wei>10)
	{
		 if(now_max_wei%10>=6) 
	 {
		 now_max_wei=now_max_wei-now_max_wei%10+10;
	 }
	 else
	 {	
		 now_max_wei=now_max_wei-now_max_wei%10;
	 }
	}	
	// lcd_showint16_simspi_my(115,1,now_max_wei);
	
	
	
	
	
	
	for(n=0;n<128;n++)  //(0,0)=> (20,110)
	{
		 //temp=FFT_out[n];
		if(FFT_out[n]<=5) temp=FFT_out[n];
		else
		{
//			if(n>=2) temp= (FFT_out[n-2]+FFT_out[n+2]+FFT_out[n]+FFT_out[n-1]+FFT_out[n+1])/5;
     temp=FFT_out[n];
		}
		  temp=FFT_out[n]*ddd_bbb;
		TFT_xian(n+20,110,n+20,110-(temp*80/256),BLUE);
		TFT_xian(n+20+1,110-(temp*80/256),n+20+1,30,WHITE);
	//	lcd_drawpoint_simspi(n+20,100-FFT_out[n],BLUE);
	}
	
}

void Init_FPGA(void)
{
		    FPGA_constant=0;
			  FPGA_constant=(FPGA_constant|DAC_Fc)<<2;
				FPGA_constant=(FPGA_constant|DAC_F1)<<2;
		    FPGA_constant=(FPGA_constant|DAC_lei)<<2;
				FPGA_constant=(FPGA_constant|DAC_bili);
				//8位高到低位 DAC_Fc DAC_F1 DAC_lei DAC_bili；
				HAL_UART_Transmit(&UART3_Handler,&FPGA_constant,1,1000);
}

void disp_zuobiao(void)
{
	TFT_xian(20,110,153,110,BLACK);
	TFT_xian(20,5,20,110,BLACK);
	TFT_xian(148,105,153,110,BLACK);
	TFT_xian(148,115,153,110,BLACK);
	TFT_xian(20,5,25,10,BLACK);
	TFT_xian(20,5,15,10,BLACK);
 	lcd_showchar_simspi_my(12,13,'Y');
	lcd_showchar_simspi_my(140,112,'X');
	TFT_xian(30,110,30,115,BLACK);
	TFT_xian(40,110,40,115,BLACK);
	TFT_xian(50,110,50,115,BLACK);
	TFT_xian(60,110,60,115,BLACK);
	TFT_xian(70,110,70,115,BLACK);
	TFT_xian(80,110,80,115,BLACK);
	TFT_xian(90,110,90,115,BLACK);
	TFT_xian(100,110,100,115,BLACK);
	TFT_xian(110,110,110,115,BLACK);
	TFT_xian(120,110,120,115,BLACK);
	lcd_showchar_simspi_my(20-2,114,'0');
	lcd_showchar_simspi_my(30-2,114,'1');
	lcd_showchar_simspi_my(40-2,114,'2');
	lcd_showchar_simspi_my(50-2,113,'3');
	lcd_showchar_simspi_my(60-2,114,'4');
	lcd_showchar_simspi_my(70-2,114,'5');
	lcd_showchar_simspi_my(80-2,114,'6');
	lcd_showchar_simspi_my(90-2,114,'7');
	lcd_showchar_simspi_my(100-2,114,'8');
	lcd_showchar_simspi_my(111-2,114,'9');
	lcd_showchar_simspi_my(120-2,114,'1');lcd_showchar_simspi_my(125-2,114,'0');
	
	TFT_xian(10,90,20,90,BLACK);
	TFT_xian(10,70,20,70,BLACK);
	TFT_xian(10,50,20,50,BLACK);
	TFT_xian(10,30,20,30,BLACK);
	TFT_xian(10,100,20,100,BLACK);
	TFT_xian(10,80,20,80,BLACK);
	TFT_xian(10,60,20,60,BLACK);
	TFT_xian(10,40,20,40,BLACK);
	lcd_showchar_simspi_my(10,110,'0');
	lcd_showchar_simspi_my(10,90-5,'1');
	lcd_showchar_simspi_my(10,70-5,'2');
	lcd_showchar_simspi_my(10,50-5,'3');
	lcd_showchar_simspi_my(10,30-5, '4');
	
	LCD_Show_CH_Font16(30,0,11);
	LCD_Show_CH_Font16(50-5,0,12);
	LCD_Show_CH_Font16(70-10,0,13);
	LCD_Show_CH_Font16(90-15,0,14);
	
}


int find_max(u8 *p,int length,int *max)
{
	int i=0,j=0;
	int max1=-999;
	int deix=0;
	
	for(i=0;i<length;i++)
	{
		if(max1<p[i]){ max1=p[i]; deix=i;}
	}
	*max=max1;
	return deix;
}

void fqtl(u8 f_5[])
{
	int i=9,j,t=0,n;
	u8 sz2[128]={0};
	int max_1=0,max_2=0,max_3=0,max_4=0,max_5=0;
	int ff1=0,ff2=0,ff3=0,ff4=0,ff5=0;
	for(n=2;n<128;n++)
	{
		if(FFT_out[n]<=5) FFT_out[n]=FFT_out[n];
		else FFT_out[n]= (FFT_out[n-2]+FFT_out[n+2]+FFT_out[n]+FFT_out[n-1]+FFT_out[n+1])/5;
	}
	for(n=2;n<125;n++)
	{
		if(FFT_out[n-1]<=FFT_out[n]&&FFT_out[n+1]<=FFT_out[n])
		{
			sz2[n]=FFT_out[n];
		}
		else sz2[n]=0;
	}
	
	f_5[0]=find_max(sz2,128,&max_1);
	for(n=0;n<=f_5[0]+2;n++) sz2[n]=0;
	
	f_5[1]=find_max(sz2,128,&max_2);
	for(n=0;n<=f_5[1]+2;n++) sz2[n]=0;
	
	f_5[2]=find_max(sz2,128,&max_3);
	for(n=0;n<=f_5[2]+2;n++) sz2[n]=0;
	
	f_5[3]=find_max(sz2,128,&max_4);
	for(n=0;n<=f_5[3]+2;n++) sz2[n]=0;
	
	f_5[4]=find_max(sz2,128,&max_5);
	for(n=0;n<=f_5[4]+2;n++) sz2[n]=0;

//	lcd_showint16_simspi_my(85,0,ff1);
//	lcd_showint16_simspi_my(85,1,ff2);
//	lcd_showint16_simspi_my(85,2,ff3);
//	lcd_showint16_simspi_my(85,3,ff4);
//	lcd_showint16_simspi_my(85,4,ff5);
//	sz2[t]=255;
}

void get_fudu(void)
{
	int i,j,t;
	
	for(i=0;i<256;i++)
	{
		if(FFT_out[i]>=128) FFT_out[i]=256-FFT_out[i];
	}
	
	for(i=0;i<256;i++)
	{
		if(i<128) 
		{
			fft_read[i]=FFT_out[i]*FFT_out[i];
			if(i<=3) fft_read[i]=0;
		}
		else  
		{
			fft_imag[i-128]=FFT_out[i]*FFT_out[i];
			if(i<=i-128+3) fft_imag[i]=0;
		}
	}
	
	for(i=0;i<128;i++)
	{
		FFT_out[i]=sqrt(fft_read[i]+fft_imag[i]);
	}
	
}
