/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define USART_REC_LEN   200                     /* �����������ֽ��� 200 */
#define USART_EN_RX     1                       /* ʹ�ܣ�1��/��ֹ��0������1���� */
#define RXBUFFERSIZE    1                       /* �����С */

#define USART2_REC_LEN   200                     /* �����������ֽ��� 200 */
#define USART2_EN_RX     1                       /* ʹ�ܣ�1��/��ֹ��0������1���� */
#define RX2BUFFERSIZE    1                       /* �����С */

#define USART3_REC_LEN   200                     /* �����������ֽ��� 200 */
#define USART3_EN_RX     1                       /* ʹ�ܣ�1��/��ֹ��0������1���� */
#define RX3BUFFERSIZE    1                       /* �����С */

extern UART_HandleTypeDef g_uart1_handle;       /* UART��� */
extern uint8_t  g_usart_rx_buf[USART_REC_LEN];  /* ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t g_usart_rx_sta;                 /* ����״̬��� */
extern uint8_t g_rx_buffer[RXBUFFERSIZE];       /* HAL��USART����Buffer */

extern UART_HandleTypeDef g_uart2_handle;       /* UART��� */
extern uint8_t  g_usart2_rx_buf[USART2_REC_LEN];  /* ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t g_usart2_rx_sta;                 /* ����״̬��� */
extern uint8_t g_rx2_buffer[RX2BUFFERSIZE];       /* HAL��USART����Buffer */

extern UART_HandleTypeDef g_uart3_handle;       /* UART��� */
extern uint8_t  g_usart3_rx_buf[USART3_REC_LEN];  /* ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t g_usart3_rx_sta;                 /* ����״̬��� */
extern uint8_t g_rx3_buffer[RX3BUFFERSIZE];       /* HAL��USART����Buffer */

extern	uint8_t revbuf1[6];
extern	uint8_t revbuf2[6];
extern	uint8_t revbuf3[6];
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

