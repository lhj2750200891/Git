#ifndef __STEPPER_TIM_H
#define __STEPPER_TIM_H

#include "sys.h"

/******************************************************************************************/
/* �߼���ʱ�� ���� */

 /* TIMX PWM ���� 
 * Ĭ��ʹ�õ���TIM8_CH1.
 * ע��: ͨ���޸��⼸���궨��, ����֧��TIM1/TIM8��ʱ��
 */
#define ATIM_TIM8_PWM_CH1_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH1_GPIO_PIN             GPIO_PIN_6
#define ATIM_TIM8_PWM_CH1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PI��ʱ��ʹ�� */

#define ATIM_TIM8_PWM_CH2_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH2_GPIO_PIN             GPIO_PIN_7
#define ATIM_TIM8_PWM_CH2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PI��ʱ��ʹ�� */

#define ATIM_TIM8_PWM_CH3_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH3_GPIO_PIN             GPIO_PIN_8
#define ATIM_TIM8_PWM_CH3_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PI��ʱ��ʹ�� */

#define ATIM_TIM8_PWM_CH4_GPIO_PORT            GPIOC
#define ATIM_TIM8_PWM_CH4_GPIO_PIN             GPIO_PIN_9
#define ATIM_TIM8_PWM_CH4_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)     /* PC��ʱ��ʹ�� */

#define ATIM_TIMX_PWM_CHY_GPIO_AF              GPIO_AF3_TIM8

#define ATIM_TIMX_PWM                          TIM8
#define ATIM_TIMX_UP_IRQn                      TIM8_UP_TIM13_IRQn
#define ATIM_TIMX_UP_IRQHandler                TIM8_UP_TIM13_IRQHandler
#define ATIM_TIM8_PWM_CH1                      TIM_CHANNEL_1                                    /* ͨ��1 */
#define ATIM_TIM8_PWM_CH2                      TIM_CHANNEL_2                                    /* ͨ��2 */
#define ATIM_TIM8_PWM_CH3                      TIM_CHANNEL_3                                    /* ͨ��3 */
#define ATIM_TIM8_PWM_CH4                      TIM_CHANNEL_4                                    /* ͨ��4 */

#define ATIM_TIMX_PWM_CHY_CLK_ENABLE()         do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)       /* TIM8 ʱ��ʹ�� */

extern TIM_HandleTypeDef TIM8_Handle;                                                        /* ��ʱ��x��� */
extern uint8_t Step_Run_Flag;   //��������˶���־
/******************************************************************************************/

void atim_timx_oc_chy_init(uint16_t arr, uint16_t psc);                                         /* �߼���ʱ�� PWM��ʼ������ */

#endif

















