
#ifndef __GPIO_H
#define __GPIO_H

#include "./SYSTEM/sys/sys.h"
/* ���� ���� */
/*ѭ����ʼ��*/
#define L3_GPIO_PORT                  GPIOD
#define L3_GPIO_PIN                   GPIO_PIN_6
#define L3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define L2_GPIO_PORT                  GPIOD
#define L2_GPIO_PIN                   GPIO_PIN_5
#define L2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define L1_GPIO_PORT                  GPIOD
#define L1_GPIO_PIN                   GPIO_PIN_4
#define L1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define M_GPIO_PORT                  GPIOD
#define M_GPIO_PIN                   GPIO_PIN_3
#define M_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define R1_GPIO_PORT                  GPIOD
#define R1_GPIO_PIN                   GPIO_PIN_2
#define R1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define R2_GPIO_PORT                  GPIOD
#define R2_GPIO_PIN                   GPIO_PIN_1
#define R2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define R3_GPIO_PORT                  GPIOD
#define R3_GPIO_PIN                   GPIO_PIN_0
#define R3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

/******************************************************************************************/

#define L3       HAL_GPIO_ReadPin(L3_GPIO_PORT, L3_GPIO_PIN)     /* ��ȡKEY0���� */
#define L2       HAL_GPIO_ReadPin(L2_GPIO_PORT, L2_GPIO_PIN)     /* ��ȡKEY0���� */
#define L1       HAL_GPIO_ReadPin(L1_GPIO_PORT, L1_GPIO_PIN)     /* ��ȡKEY0���� */
#define M        HAL_GPIO_ReadPin(M_GPIO_PORT, M_GPIO_PIN)     /* ��ȡKEY0���� */
#define R1       HAL_GPIO_ReadPin(R1_GPIO_PORT, R1_GPIO_PIN)     /* ��ȡKEY0���� */
#define R2       HAL_GPIO_ReadPin(R2_GPIO_PORT, R2_GPIO_PIN)     /* ��ȡKEY0���� */
#define R3       HAL_GPIO_ReadPin(R4_GPIO_PORT, R3_GPIO_PIN)     /* ��ȡKEY0���� */

#define LIGHT_GPIO_PORT                  GPIOD
#define LIGHT_GPIO_PIN                   GPIO_PIN_8
#define LIGHT_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)             /* PF��ʱ��ʹ�� */
#define LIGHT(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIGHT_GPIO_PORT, LIGHT_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIGHT_GPIO_PORT, LIGHT_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */
#define BEEP_GPIO_PORT                  GPIOD
#define BEEP_GPIO_PIN                   GPIO_PIN_9
#define BEEP_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)             /* PF��ʱ��ʹ�� */
#define BEEP(x)   do{ x ? \
                      HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */
/******************************************************************************************/
/* �ⲿ�ӿں���*/
void gpio_init(void);                                                                            /* ��ʼ�� */

#endif
