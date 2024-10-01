#include "LED.h"
#include "gpio.h"
#include "KEY.h"
#include "timer.h"
#include "tim.h"

/*全局变量的定义*/
int CNT1=0,CNT2=0;

/*全局变量的引用（extern）*/



/*
函数功能：HAL库定时器的回调函数
入口参数：无
返回值：无
*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM6)   //10ms
	{
		CNT1++;
		if(CNT1==100)
		{
			HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
			CNT1=0;
		}
	}
	if(htim->Instance==TIM7)   //200ms
	{
		CNT2++;
		if(CNT2==5)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			CNT2=0;
		}
	}	
}
