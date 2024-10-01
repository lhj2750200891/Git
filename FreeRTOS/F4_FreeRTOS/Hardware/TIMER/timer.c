#include "main.h"

/*定时器中断中所用到的全局变量的定义*/
int CNT1=0,CNT2=0;
int16_t EncoderA=0,EncoderB=0;   //10MS内的脉冲数
int16_t S_EncoderA=0,S_EncoderB=0;//脉冲累计
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
		Reading(&EncoderA,&EncoderB);   //读取完成，自动清零
		S_EncoderB+=EncoderB;
		S_EncoderA+=EncoderA;
		if(keyflag==1)
		{
			speed_pid();
			addPID.target_val = 10;	
			add2PID.target_val = 10;
			printf("左轮%d\r\n",EncoderA);
			printf("右轮%d\r\n",EncoderB);
		}
		if(keyflag==2)
		{
			speed_pid();
			PWMC_Set(0);
			PWMD_Set(0);
			printf("左轮%d\r\n",EncoderA);
			printf("右轮%d\r\n",EncoderB);
		}
		if(keyflag==3)
		{
			Motor_Control_ClosedLoop();
			printf("左轮%d\r\n",EncoderA);
			printf("右轮%d\r\n",EncoderB);
		}
	}
	
	if(htim->Instance==TIM7)   //200ms
	{
		CNT2++;
		ADC_Vol=(double)StartAndGetOneResult()*3.3*11/4096;//读取转换的AD值
		if(CNT2==5)
		{
			
			CNT2=0;
		}
	}	
  if (htim->Instance == TIM10)  //FreeRTOS的时基，时间片，1ms
	{
    HAL_IncTick();
  }
}
