#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
#include "KEY.h"
#include "LED.h"
#include "TB6612.h"
#include "pid.h"
#include "timer.h"
#include "math.h"
#include "stdio.h"
/////////////////////////////////////////////
#include "tim.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "main.h"
#include "usart.h"
////////////////////////////////////////////
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "RTOS.h"
#include "HWT101.h"
#include "wit_c_sdk.h"
#include "lcd.h"
#include "spi.h"
#include "gui.h"
#include "test.h"

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

/* USER CODE BEGIN Private defines */
#define delay_ms HAL_Delay
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
