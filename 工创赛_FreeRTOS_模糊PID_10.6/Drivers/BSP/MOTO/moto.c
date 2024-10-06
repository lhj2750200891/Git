#include "./BSP/MOTO/moto.h"
#include "./SYSTEM/delay/delay.h"
#include "pwm.h"
#include "control.h"
#include "pid.h"  
#include <stdbool.h>
#include "./SYSTEM/usart/usart.h"

/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void moto_init(void)
{
	  /* 配置PA8为人体存在模块 */
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO配置参数存储变量 */

    MOTO1A_GPIO_CLK_ENABLE();
	  MOTO1B_GPIO_CLK_ENABLE();
	  MOTO2A_GPIO_CLK_ENABLE();
	  MOTO2A_GPIO_CLK_ENABLE();
    MOTO3A_GPIO_CLK_ENABLE();
	  MOTO3B_GPIO_CLK_ENABLE();
	  MOTO4A_GPIO_CLK_ENABLE();
	  MOTO4A_GPIO_CLK_ENABLE();
    gpio_init_struct.Pin = MOTO1A_GPIO_PIN | MOTO1B_GPIO_PIN | MOTO2A_GPIO_PIN | MOTO2B_GPIO_PIN 
																			| MOTO3A_GPIO_PIN | MOTO3B_GPIO_PIN | MOTO4A_GPIO_PIN | MOTO4B_GPIO_PIN; /* 引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(MOTO1A_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */
	  HAL_GPIO_Init(MOTO1B_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */
	  HAL_GPIO_Init(MOTO2A_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */
	  HAL_GPIO_Init(MOTO2B_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */
	  HAL_GPIO_Init(MOTO3A_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */
	  HAL_GPIO_Init(MOTO3B_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */
	  HAL_GPIO_Init(MOTO4A_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */
	  HAL_GPIO_Init(MOTO4B_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */

}

void PWM1_Set(int pwm)
{
  	if(pwm > 0)
	{
		MOTO1A(0);
		MOTO1B(1);
		TIM_SetTIM8Compare1(pwm*84);
	}
	else
	{
		MOTO1A(1);
		MOTO1B(0);
		TIM_SetTIM8Compare1(-pwm*84);
	}
}
void PWM2_Set(int pwm)
{
  	if(pwm > 0)
	{
		MOTO2A(1);
		MOTO2B(0);
		TIM_SetTIM8Compare2(pwm*84);
	}
	else
	{
		MOTO2A(0);
		MOTO2B(1);
		TIM_SetTIM8Compare2(-pwm*84);
	}
}
void PWM4_Set(int pwm)
{
  	if(pwm > 0)
	{
		MOTO4A(1);
		MOTO4B(0);
		TIM_SetTIM8Compare4(pwm*84);
	}
	else
	{
		MOTO4A(0);
		MOTO4B(1);
		TIM_SetTIM8Compare4(-pwm*84);
	}
}
void PWM3_Set(int pwm)
{
  	if(pwm > 0)
	{
		MOTO3A(0);
		MOTO3B(1);
		TIM_SetTIM8Compare3(pwm*84);
	}
	else
	{
		MOTO3A(1);
		MOTO3B(0);
		TIM_SetTIM8Compare3(-pwm*84);
	}
}

//左轮和右轮以一起的速度，向前走多少圈
void spd_pos(int targetspeed,float Circle)
{
			//targetposition = Circle*1040*1.04;//20或者30减速比，霍尔编码器精度为13，AB双相4倍频，20*13*4=1040或者30*13*4=1560
			PosionPID.target_val =Circle*1560;		
			Posion2PID.target_val =Circle*1560;		
			Lmax_speed = targetspeed;
			Rmax_speed = targetspeed;
}
// 左轮速度，右轮速度，左轮距离，右轮距离，距离是脉冲值
void spd_encoder(int speedL, int speedR, int encoder1,int encoder2)
{			
			Lmax_speed = speedL;
			Rmax_speed = speedR;
			PosionPID.target_val =	encoder1;		
			Posion2PID.target_val =	encoder2;		


}


void turnangle(bool Dir,float angle)
{
			//targetposition = Circle*1040*1.04;//20或者30减速比，霍尔编码器精度为13，AB双相4倍频，20*13*4=1040或者30*13*4=1560
		if(angle>90) angle = 90 ;
			if(Dir==Left)
			{
				PosionPID.target_val =-angle/180*1560*1.18f;		
				Posion2PID.target_val =angle/180*1560*1.18f;		
			}
			else if(Dir == Right)
			{
				PosionPID.target_val =angle/180*1560*1.18f;		
				Posion2PID.target_val =-angle/180*1560*1.18f;	
			}
			Lmax_speed = 10;
			Rmax_speed = 10;
}


void uart_wait(int t)
{
//	HAL_NVIC_DisableIRQ(USART_UX_IRQn);
//	vTaskDelay(t);
//	HAL_NVIC_EnableIRQ(USART_UX_IRQn);  

}








