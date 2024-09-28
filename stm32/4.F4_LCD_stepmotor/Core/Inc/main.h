/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "math.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "KEY.h"
#include "LED.h"
#include "TB6612.h"
#include "stdio.h"
#include "pid.h"
#include "timer.h"
#include "math.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "delay.h"
#include "oled.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "stepper_motor.h"
#include "stepper_tim.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern uint8_t id;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOE
#define LED0_Pin GPIO_PIN_4
#define LED0_GPIO_Port GPIOA
#define LCD_TIRQ_Pin GPIO_PIN_13
#define LCD_TIRQ_GPIO_Port GPIOF
#define LCD_TD0_Pin GPIO_PIN_14
#define LCD_TD0_GPIO_Port GPIOF
#define LCD_TD1_Pin GPIO_PIN_15
#define LCD_TD1_GPIO_Port GPIOF
#define AIN1_Pin GPIO_PIN_0
#define AIN1_GPIO_Port GPIOG
#define AIN2_Pin GPIO_PIN_1
#define AIN2_GPIO_Port GPIOG
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_8
#define KEY2_GPIO_Port GPIOE
#define KEY0_Pin GPIO_PIN_9
#define KEY0_GPIO_Port GPIOE
#define BIN1_Pin GPIO_PIN_2
#define BIN1_GPIO_Port GPIOG
#define BIN2_Pin GPIO_PIN_3
#define BIN2_GPIO_Port GPIOG
#define LCD_TCS_Pin GPIO_PIN_4
#define LCD_TCS_GPIO_Port GPIOG
#define LCD_TCLK_Pin GPIO_PIN_5
#define LCD_TCLK_GPIO_Port GPIOG
#define LCD_SCK_Pin GPIO_PIN_8
#define LCD_SCK_GPIO_Port GPIOG
#define D0_Pin GPIO_PIN_12
#define D0_GPIO_Port GPIOG
#define D1_Pin GPIO_PIN_13
#define D1_GPIO_Port GPIOG
#define RES_Pin GPIO_PIN_14
#define RES_GPIO_Port GPIOG
#define DC_Pin GPIO_PIN_15
#define DC_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
