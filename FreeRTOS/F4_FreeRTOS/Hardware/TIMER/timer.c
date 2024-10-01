#include "main.h"

/*定时器中断中所用到的全局变量的定义*/
int CNT1=0,CNT2=0;
int16_t EncoderC=0,EncoderD=0;   //10MS内的脉冲数
int16_t S_EncoderC=0,S_EncoderD=0;//脉冲累计
/*全局变量的引用extern()*/

/*
函数功能：hal库定时器读取编码器的值
入口参数：无
返回值：无
*/
void Reading(int16_t *L_Val,int16_t *R_Val)
{
	*R_Val=TIM5->CNT; //读取计数
	TIM5->CNT = 0;
	*L_Val=-TIM4->CNT;
	TIM4->CNT = 0;
}

/*
函数功能：hal库定时器的回调函数
入口参数：无
返回值：无
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM6)   //10ms
	{
		CNT1++;
		Reading(&EncoderC,&EncoderD);   //读取完成，自动清零
		S_EncoderC+=EncoderC;
		S_EncoderD+=EncoderD;
		if(keyflag==1)
		{
			speed_pid();
			addPID.target_val = 10;	
			add2PID.target_val = 10;
		}
		if(keyflag==2)
		{
			Speed_Angle_ClosedLoop();
		}
		if(keyflag==3)
		{
			Motor_Control_ClosedLoop();
		}
	}
	
	if(htim->Instance==TIM7)   //200ms
	{
		CNT2++;
		ADC_Vol=(double)StartAndGetOneResult()*3.3*11/4096;//读取转换的AD值
		HWT101_GetData();
		if(CNT2==5)
		{
			printf("angle:%.3f\r\n",HWT101_yaw);
			printf("power:%.3f\r\n",ADC_Vol);
			CNT2=0;
		}
	}	
  if (htim->Instance == TIM10)  //FreeRTOS的时基，时间片，1ms
	{
    HAL_IncTick();
  }
}
