/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7); /* 设置时钟,168Mhz */
    delay_init(168);                    /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
  usart2_init(115200);  
		led_init();                         /* 初始化LED */																				
	  OLED_Init();											  /* 初始化oled */
    key_init();                         /* 初始化按键 */
		gpio_init();                        /* 初始化GPIO */
	  MX_TIM2_Init();                     /* 定时器2初始化(编码器) */
    MX_TIM3_Init();											/* 定时器3初始化(编码器) */
    MX_TIM4_Init();											/* 定时器4初始化(编码器) */
    MX_TIM5_Init();											/* 定时器5初始化(编码器) */
		PWM_Init(8400-1,0);									/* 定时器8初始化(电机PWM) */
	  HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);//开启定时器2
	  HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);//开启定时器3
	  HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);//开启定时器4
	  HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);//开启定时器5
	  adc_init();                             /* 初始化ADC */
		moto_init();
		MPU_Init();
    mpu_dmp_init();											//初始化MPU6050
	  PID_param_init();                      /*初始化PID参数*/
		PWM14_Init(20000-1, 84-1);					/*定时器14初始化  舵机*/
	  //nrf24l01_init();                    /* 初始化NRF24L01 */
   // sram_init();                        /* SRAM初始化 */
    my_mem_init(SRAMIN);                /* 初始化内部SRAM内存池 */
    my_mem_init(SRAMEX);                /* 初始化外部SRAM内存池 */
    my_mem_init(SRAMCCM);               /* 初始化内部CCM内存池 */
		//usart_init(115200);
		HWT101_Init();  //HWT101
		LCD_GPIO_Init();
		LCD_Init();
		LCD_Static_Show();
		
    freertos_demo();                    /* 运行FreeRTOS例程 */
		
}
/***************
														鸡你太美
													鸡你实在太美
														鸡你是太美
														 鸡你太美
													实在是太美鸡你
										鸡你 实在是太美鸡你  美
									鸡你   实在是太美鸡美  太美
								鸡你     实在是太美鸡美    太美
							鸡你       实在是太美鸡美      太美
						鸡你        鸡你实在是美太美    （ 美篮球球）
						鸡鸡       鸡你实在是太美      （ 篮球篮球球）
						鸡        鸡你太美裆鸡太啊        （蓝蓝球）
						          鸡你太美裆裆鸡美					
											 鸡你美裆   裆鸡美
											  鸡太美     鸡太美
												 鸡美        鸡美
												 鸡美         鸡美
												 鸡美         鸡美
												 鸡太         鸡太
												金猴         金猴
												皮鞋         皮鞋金猴
												金光         金光 大道
												大道

												坤坤镇楼，不出BUG

***************/
