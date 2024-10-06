

#include "./BSP/GPIO/gpio.h"
#include "./SYSTEM/delay/delay.h"
#include "adc.h"
/**
 * @brief       ������ʼ������
 * @param       ��
 * @retval      ��
 */
void gpio_init(void)
{
	  
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO���ò����洢���� */
		/*ѭ����ʼ��*/
    L3_GPIO_CLK_ENABLE();
	  L2_GPIO_CLK_ENABLE();
		L1_GPIO_CLK_ENABLE();
		M_GPIO_CLK_ENABLE();
		R1_GPIO_CLK_ENABLE();
	  R2_GPIO_CLK_ENABLE();
		R3_GPIO_CLK_ENABLE();
	
    gpio_init_struct.Pin = L3_GPIO_PIN | L2_GPIO_PIN |L1_GPIO_PIN |M_GPIO_PIN |R1_GPIO_PIN |R2_GPIO_PIN |R3_GPIO_PIN;                       /* KEY0���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_NOPULL;                        /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(GPIOD, &gpio_init_struct);           /* KEY0����ģʽ����,�������� */

		
		LIGHT_GPIO_CLK_ENABLE();
		gpio_init_struct.Pin = LIGHT_GPIO_PIN;                   /* LED0���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(LIGHT_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED0���� */

    gpio_init_struct.Pin = LIGHT_GPIO_PIN;                   /* LED1���� */
    HAL_GPIO_Init(LIGHT_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED1���� */
    
		LIGHT(0);
		
		BEEP_GPIO_CLK_ENABLE();
		gpio_init_struct.Pin = BEEP_GPIO_PIN;                   /* LED0���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(BEEP_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED0���� */

    gpio_init_struct.Pin = BEEP_GPIO_PIN;                   /* LED1���� */
    HAL_GPIO_Init(BEEP_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED1���� */
    
		BEEP(1);

}




















