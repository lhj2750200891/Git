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
#include "adc.h"
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
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOE
#define LED0_Pin GPIO_PIN_4
#define LED0_GPIO_Port GPIOA
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
#define CIN1_Pin GPIO_PIN_5
#define CIN1_GPIO_Port GPIOG
#define CIN2_Pin GPIO_PIN_6
#define CIN2_GPIO_Port GPIOG
#define DIN1_Pin GPIO_PIN_7
#define DIN1_GPIO_Port GPIOG
#define DIN2_Pin GPIO_PIN_8
#define DIN2_GPIO_Port GPIOG
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
