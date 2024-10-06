#ifndef __PWM_H
#define __PWM_H

#include "./BSP/TIMER/btim.h"
#include "./BSP/PWM/pwm.h"

#define MOTOR1_PWM_ENABLE()      HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1)  //AIN1     PA2
#define MOTOR2_PWM_ENABLE()      HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2)   //AIN2     PA3

void TIM_SetTIM14Compare1(uint32_t compare);
void PWM14_Init(uint16_t arr, uint16_t psc);
void TIM_SetTIM8Compare1(uint32_t compare);
void TIM_SetTIM8Compare2(uint32_t compare);
void TIM_SetTIM8Compare3(uint32_t compare);
void TIM_SetTIM8Compare4(uint32_t compare);
void PWM_Init(uint16_t arr, uint16_t psc);
extern TIM_HandleTypeDef htim8;
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
#endif  

