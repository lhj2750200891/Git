/**
 ****************************************************************************************************
 * @file        btim.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-15
 * @brief       ������ʱ�� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211015
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __BTIM_H
#define __BTIM_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ������ʱ�� ���� */

/* TIMX �ж϶��� 
 * Ĭ�������TIM6/TIM7
 * ע��: ͨ���޸���4���궨��,����֧��TIM1~TIM8����һ����ʱ��.
 */
 extern int16_t Encoder1,Encoder2;
#define BTIM_TIM7_INT                       TIM7
#define BTIM_TIM7_INT_IRQn                  TIM7_IRQn
#define BTIM_TIM7_INT_IRQHandler            TIM7_IRQHandler
#define BTIM_TIM7_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM7_CLK_ENABLE(); }while(0)  /* TIM3 ʱ��ʹ�� */

#define BTIM_TIM6_INT                       TIM6
#define BTIM_TIM6_INT_IRQn                  TIM6_DAC_IRQn
#define BTIM_TIM6_INT_IRQHandler            TIM6_IRQHandler
#define BTIM_TIM6_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM6_CLK_ENABLE(); }while(0)  /* TIM3 ʱ��ʹ�� */
/******************************************************************************************/

void btim_tim7_int_init(uint16_t arr, uint16_t psc);
void btim_tim6_int_init(uint16_t arr, uint16_t psc);
//void MX_TIM6_Init(void);
extern TIM_HandleTypeDef g_tim7_handle;        /* ��ʱ��3��� */
extern TIM_HandleTypeDef g_tim6_handle;        /* ��ʱ��3��� */
extern TIM_HandleTypeDef htim2;

extern TIM_HandleTypeDef htim3;

extern TIM_HandleTypeDef htim4;

extern TIM_HandleTypeDef htim5;
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM5_Init(void);
void Error_Handler(void);
#endif

















