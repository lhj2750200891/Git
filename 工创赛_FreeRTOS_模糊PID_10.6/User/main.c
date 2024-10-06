/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */
 #include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "./BSP/MOTO/moto.h"
#include "pwm.h"
#include "oled.h"
#include "./BSP/TIMER/btim.h"
#include "./BSP/ADC/adc.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
//#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SRAM/sram.h"
#include "./MALLOC/malloc.h"
#include "freertos_demo.h"
#include "./BSP/GPIO/gpio.h"
#include "./BSP/NRF24L01/nrf24l01.h"
#include "./BSP/HWT101/HWT101.h"
#include "./BSP/Software_LCD3.5/lcd.h"
#include "./BSP/Software_LCD3.5/test.h"
#include "./BSP/Software_LCD3.5/spi.h"

int16_t Encoder1,Encoder2,Encoder3,Encoder4;
int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7); /* ����ʱ��,168Mhz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
  usart2_init(115200);  
		led_init();                         /* ��ʼ��LED */																				
	  OLED_Init();											  /* ��ʼ��oled */
    key_init();                         /* ��ʼ������ */
		gpio_init();                        /* ��ʼ��GPIO */
	  MX_TIM2_Init();                     /* ��ʱ��2��ʼ��(������) */
    MX_TIM3_Init();											/* ��ʱ��3��ʼ��(������) */
    MX_TIM4_Init();											/* ��ʱ��4��ʼ��(������) */
    MX_TIM5_Init();											/* ��ʱ��5��ʼ��(������) */
		PWM_Init(8400-1,0);									/* ��ʱ��8��ʼ��(���PWM) */
	  HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);//������ʱ��2
	  HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);//������ʱ��3
	  HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);//������ʱ��4
	  HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);//������ʱ��5
	  adc_init();                             /* ��ʼ��ADC */
		moto_init();
		MPU_Init();
    mpu_dmp_init();											//��ʼ��MPU6050
	  PID_param_init();                      /*��ʼ��PID����*/
		PWM14_Init(20000-1, 84-1);					/*��ʱ��14��ʼ��  ���*/
	  //nrf24l01_init();                    /* ��ʼ��NRF24L01 */
   // sram_init();                        /* SRAM��ʼ�� */
    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */
    my_mem_init(SRAMEX);                /* ��ʼ���ⲿSRAM�ڴ�� */
    my_mem_init(SRAMCCM);               /* ��ʼ���ڲ�CCM�ڴ�� */
		//usart_init(115200);
		HWT101_Init();  //HWT101
		LCD_GPIO_Init();
		LCD_Init();
		LCD_Static_Show();
		
    freertos_demo();                    /* ����FreeRTOS���� */
		
}
/***************
														����̫��
													����ʵ��̫��
														������̫��
														 ����̫��
													ʵ����̫������
										���� ʵ����̫������  ��
									����   ʵ����̫������  ̫��
								����     ʵ����̫������    ̫��
							����       ʵ����̫������      ̫��
						����        ����ʵ������̫��    �� ��������
						����       ����ʵ����̫��      �� ����������
						��        ����̫���ɼ�̫��        ��������
						          ����̫�����ɼ���					
											 ��������   �ɼ���
											  ��̫��     ��̫��
												 ����        ����
												 ����         ����
												 ����         ����
												 ��̫         ��̫
												���         ���
												ƤЬ         ƤЬ���
												���         ��� ���
												���

												������¥������BUG

***************/
