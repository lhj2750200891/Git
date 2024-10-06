
#ifndef __MOTO_H
#define __MOTO_H
#include "pid.h" 
#include <stdbool.h>
#include "./SYSTEM/sys/sys.h"
/* 引脚 定义 */

#define MOTO1A_GPIO_PORT                  GPIOG
#define MOTO1A_GPIO_PIN                   GPIO_PIN_0
#define MOTO1A_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define MOTO1B_GPIO_PORT                  GPIOG
#define MOTO1B_GPIO_PIN                   GPIO_PIN_1
#define MOTO1B_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define MOTO2A_GPIO_PORT                  GPIOG
#define MOTO2A_GPIO_PIN                   GPIO_PIN_2
#define MOTO2A_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define MOTO2B_GPIO_PORT                  GPIOG
#define MOTO2B_GPIO_PIN                   GPIO_PIN_3
#define MOTO2A_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define MOTO3A_GPIO_PORT                  GPIOG
#define MOTO3A_GPIO_PIN                   GPIO_PIN_5
#define MOTO3A_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define MOTO3B_GPIO_PORT                  GPIOG
#define MOTO3B_GPIO_PIN                   GPIO_PIN_6
#define MOTO3B_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define MOTO4A_GPIO_PORT                  GPIOG
#define MOTO4A_GPIO_PIN                   GPIO_PIN_7
#define MOTO4A_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define MOTO4B_GPIO_PORT                  GPIOG
#define MOTO4B_GPIO_PIN                   GPIO_PIN_8
#define MOTO4B_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

/*运动模式*/
#define Cascade 0
#define Velocity  1

/******************************************************************************************/

#define MOTO1A(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO1A_GPIO_PORT, MOTO1A_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO1A_GPIO_PORT, MOTO1A_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define MOTO1B(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO1B_GPIO_PORT, MOTO1B_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO1B_GPIO_PORT, MOTO1B_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define MOTO2A(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO2A_GPIO_PORT, MOTO2A_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO2A_GPIO_PORT, MOTO2A_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define MOTO2B(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO2B_GPIO_PORT, MOTO2B_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO2B_GPIO_PORT, MOTO2B_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */
#define MOTO3A(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO3A_GPIO_PORT, MOTO3A_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO3A_GPIO_PORT, MOTO3A_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define MOTO3B(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO3B_GPIO_PORT, MOTO3B_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO3B_GPIO_PORT, MOTO3B_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define MOTO4A(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO4A_GPIO_PORT, MOTO4A_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO4A_GPIO_PORT, MOTO4A_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define MOTO4B(x)   do{ x ? \
                      HAL_GPIO_WritePin(MOTO4B_GPIO_PORT, MOTO4B_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(MOTO4B_GPIO_PORT, MOTO4B_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define Right 1
#define Left 0							
/******************************************************************************************/
/* 外部接口函数*/
void moto_init(void);                                                                            /* 初始化 */
void PWM1_Set(int pwm);
void PWM2_Set(int pwm);		
void PWM3_Set(int pwm);
void PWM4_Set(int pwm);
void spd_pos(int targetspeed,float Circle);				
void turnangle(bool Dir,float angle);		
void uart_wait(int t);	
void spd_encoder(int speedL, int speedR, int encoder1,int encoder2);		
								
#endif
