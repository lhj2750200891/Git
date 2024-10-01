#ifndef __STEPPER_TIM_H
#define __STEPPER_TIM_H

#include "sys.h"

/******************************************************************************************/
/* 高级定时器 定义 */

 /* TIMX PWM 定义 
 * 默认使用的是TIM8_CH1.
 * 注意: 通过修改这几个宏定义, 可以支持TIM1/TIM8定时器
 */
#define ATIM_TIM8_PWM_CH1_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH1_GPIO_PIN             GPIO_PIN_6
#define ATIM_TIM8_PWM_CH1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PI口时钟使能 */

#define ATIM_TIM8_PWM_CH2_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH2_GPIO_PIN             GPIO_PIN_7
#define ATIM_TIM8_PWM_CH2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PI口时钟使能 */

#define ATIM_TIM8_PWM_CH3_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH3_GPIO_PIN             GPIO_PIN_8
#define ATIM_TIM8_PWM_CH3_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PI口时钟使能 */

#define ATIM_TIM8_PWM_CH4_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH4_GPIO_PIN             GPIO_PIN_9
#define ATIM_TIM8_PWM_CH4_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PC口时钟使能 */

#define ATIM_TIMX_PWM_CHY_GPIO_AF              GPIO_AF3_TIM8

#define ATIM_TIMX_PWM                          TIM8
#define ATIM_TIMX_UP_IRQn                      TIM8_UP_TIM13_IRQn
#define ATIM_TIMX_UP_IRQHandler                TIM8_UP_TIM13_IRQHandler
#define ATIM_TIM8_PWM_CH1                      TIM_CHANNEL_1                                    /* 通道1 */
#define ATIM_TIM8_PWM_CH2                      TIM_CHANNEL_2                                    /* 通道2 */
#define ATIM_TIM8_PWM_CH3                      TIM_CHANNEL_3                                    /* 通道3 */
#define ATIM_TIM8_PWM_CH4                      TIM_CHANNEL_4                                    /* 通道4 */

#define ATIM_TIMX_PWM_CHY_CLK_ENABLE()         do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)       /* TIM8 时钟使能 */

extern TIM_HandleTypeDef TIM8_Handle;                                                        /* 定时器x句柄 */
extern uint8_t Step_Run_Flag;   //步进电机运动标志
/******************************************************************************************/

void atim_timx_oc_chy_init(uint16_t arr, uint16_t psc);                                         /* 高级定时器 PWM初始化函数 */

#endif

















