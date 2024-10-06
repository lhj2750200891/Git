#include "pwm.h"

/************************************************
*	PWM实验
*	功能：呼吸灯
*	TIM1;CH1;
*************************************************/

TIM_HandleTypeDef  TIM8_Handler;         //定时器1句柄
TIM_OC_InitTypeDef TIM8_CHnHandler;      //定时器1 PWM句柄

/*TIM1初始化函数*/
void PWM_Init(uint16_t arr, uint16_t psc)
{
	TIM8_Handler.Instance = TIM8;
	TIM8_Handler.Init.Prescaler = psc;
	TIM8_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM8_Handler.Init.Period = arr;
	TIM8_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//	TIM1_Handler.Init.RepetitionCounter = 0;
	
	HAL_TIM_PWM_Init(&TIM8_Handler);
	
	TIM8_CHnHandler.OCMode = TIM_OCMODE_PWM1;
	TIM8_CHnHandler.Pulse = arr / 2;
	/*PWM输出极性*/
	TIM8_CHnHandler.OCPolarity = TIM_OCPOLARITY_HIGH;
	
	
	/*通道1*/
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &TIM8_CHnHandler, TIM_CHANNEL_1 );
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &TIM8_CHnHandler, TIM_CHANNEL_2 );
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &TIM8_CHnHandler, TIM_CHANNEL_3 );
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &TIM8_CHnHandler, TIM_CHANNEL_4 );
	HAL_TIM_PWM_Start(&TIM8_Handler, TIM_CHANNEL_1 );
	HAL_TIM_PWM_Start(&TIM8_Handler, TIM_CHANNEL_2 );
	HAL_TIM_PWM_Start(&TIM8_Handler, TIM_CHANNEL_3 );
	HAL_TIM_PWM_Start(&TIM8_Handler, TIM_CHANNEL_4 );
}

/***************************************
*	定时器底层驱动,此函数会被HAL_TIM_PWM_Init()调用
*	时钟使能，引脚配置
****************************************/

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM8_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	GPIO_Initure.Alternate = GPIO_AF3_TIM8;
	HAL_GPIO_Init(GPIOC, &GPIO_Initure);
	
	__HAL_RCC_TIM13_CLK_ENABLE();
	__HAL_RCC_TIM14_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
	GPIO_Initure.Pin = GPIO_PIN_9;
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	GPIO_Initure.Alternate = GPIO_AF9_TIM14;
	HAL_GPIO_Init(GPIOF, &GPIO_Initure);
	
	GPIO_Initure.Pin = GPIO_PIN_8;
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	GPIO_Initure.Alternate = GPIO_AF9_TIM13;
	HAL_GPIO_Init(GPIOF, &GPIO_Initure);
}

/*设置占空比*/
void TIM_SetTIM8Compare1(uint32_t compare)
{
	TIM8->CCR1 = compare;
}
void TIM_SetTIM8Compare2(uint32_t compare)
{
	TIM8->CCR2 = compare;
}
void TIM_SetTIM8Compare3(uint32_t compare)
{
	TIM8->CCR3 = compare;
}
void TIM_SetTIM8Compare4(uint32_t compare)
{
	TIM8->CCR4 = compare;
}


TIM_HandleTypeDef  TIM14_Handler;         //定时器1句柄
TIM_OC_InitTypeDef TIM14_CHnHandler;      //定时器1 PWM句柄

void PWM14_Init(uint16_t arr, uint16_t psc)
{
	TIM14_Handler.Instance = TIM14;
	TIM14_Handler.Init.Prescaler = psc;
	TIM14_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM14_Handler.Init.Period = arr;
	TIM14_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//	TIM1_Handler.Init.RepetitionCounter = 0;
	
	HAL_TIM_PWM_Init(&TIM14_Handler);
	
	TIM14_CHnHandler.OCMode = TIM_OCMODE_PWM1;
	TIM14_CHnHandler.Pulse = 1300;
	/*PWM输出极性*/
	TIM14_CHnHandler.OCPolarity = TIM_OCPOLARITY_HIGH;
	
	/*通道1*/
	HAL_TIM_PWM_ConfigChannel(&TIM14_Handler, &TIM14_CHnHandler, TIM_CHANNEL_1 );
	HAL_TIM_PWM_Start(&TIM14_Handler, TIM_CHANNEL_1 );

}


TIM_HandleTypeDef  TIM13_Handler;         //定时器1句柄
TIM_OC_InitTypeDef TIM13_CHnHandler;      //定时器1 PWM句柄
void PWM13_Init(uint16_t arr, uint16_t psc)
{
	TIM13_Handler.Instance = TIM13;
	TIM13_Handler.Init.Prescaler = psc;
	TIM13_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM13_Handler.Init.Period = arr;
	TIM13_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//	TIM1_Handler.Init.RepetitionCounter = 0;
	
	HAL_TIM_PWM_Init(&TIM13_Handler);
	
	TIM13_CHnHandler.OCMode = TIM_OCMODE_PWM1;
	TIM13_CHnHandler.Pulse = 920;
	/*PWM输出极性*/
	TIM13_CHnHandler.OCPolarity = TIM_OCPOLARITY_HIGH;
	
	
	/*通道1*/
	HAL_TIM_PWM_ConfigChannel(&TIM13_Handler, &TIM13_CHnHandler, TIM_CHANNEL_1 );
	HAL_TIM_PWM_Start(&TIM13_Handler, TIM_CHANNEL_1 );

}
void TIM_SetTIM14Compare1(uint32_t compare)
{
	TIM14->CCR1 = compare;
}
void TIM_SetTIM13Compare1(uint32_t compare)
{
	TIM13->CCR1 = compare;
}
