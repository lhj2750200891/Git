/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
/******************************************************************�����ض���*********************************************************************************/
#include "stdio.h"  
#include "string.h"

int fputc(int ch, FILE *stream)
{
    /* �����жϴ����Ƿ������ */
    while((USART1->SR & 0X40) == 0);
 
    /* ���ڷ�����ɣ������ַ����� */
    USART1->DR = (uint8_t) ch;
 
    return ch;
}

//�ض���c�⺯��sacnf�����ݽ��ռĴ�����USART_RDR��
//int fgetc(FILE *filename)
//{
//	while( (USART2->SR & (1 << 5)) == 0){};
//	return USART2->DR;
//}

/* �ض���C�⺯��������,printf */
//int fputc(int ch,FILE *f)
//{
//    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 1000);
//    return (ch);
//}
 
//int fgetc(FILE *f)
//{
//    int ch;
//    HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, 1000);
//    return ch;
//}
////�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((USART2->SR&0X40)==0) //ѭ������,ֱ���������   
//    USART2->DR = (uint8_t) ch;      
//	return ch;
//}
/******************************************************************�����ض���*********************************************************************************/
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA2_Stream2;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/*******************************************************����1**********************************************************************************************/
/* ���ջ���, ���USART_REC_LEN���ֽ�. */
uint8_t g_usart_rx_buf[USART_REC_LEN];

/*  ����״̬
 *  bit15��      ������ɱ�־
 *  bit14��      ���յ�0x0d
 *  bit13~0��    ���յ�����Ч�ֽ���Ŀ
*/
uint16_t g_usart_rx_sta = 0;												//����״̬���	

uint8_t g_rx_buffer[RXBUFFERSIZE];                  /* HAL��ʹ�õĴ��ڽ��ջ��� */

UART_HandleTypeDef g_uart1_handle;                  /* UART��� */
/*******************************************************����1**********************************************************************************************/

/*******************************************************����2**********************************************************************************************/
/* ���ջ���, ���USART_REC_LEN���ֽ�. */
uint8_t g_usart2_rx_buf[USART2_REC_LEN];

/*  ����״̬
 *  bit15��      ������ɱ�־
 *  bit14��      ���յ�0x0d
 *  bit13~0��    ���յ�����Ч�ֽ���Ŀ
*/
uint16_t g_usart2_rx_sta = 0;												//����״̬���	

uint8_t g_rx2_buffer[RX2BUFFERSIZE];                  /* HAL��ʹ�õĴ��ڽ��ջ��� */

UART_HandleTypeDef g_uart2_handle;                  /* UART��� */
/*******************************************************����2**********************************************************************************************/

/*******************************************************����3**********************************************************************************************/
/* ���ջ���, ���USART_REC_LEN���ֽ�. */
uint8_t g_usart3_rx_buf[USART3_REC_LEN];

/*  ����״̬
 *  bit15��      ������ɱ�־
 *  bit14��      ���յ�0x0d
 *  bit13~0��    ���յ�����Ч�ֽ���Ŀ
*/
uint16_t g_usart3_rx_sta = 0;												//����״̬���	

uint8_t g_rx3_buffer[RX3BUFFERSIZE];                  /* HAL��ʹ�õĴ��ڽ��ջ��� */

UART_HandleTypeDef g_uart3_handle;                  /* UART��� */
/*******************************************************����3**********************************************************************************************/

/***************************************************���ڻص�����*****************************************************************************************/
uint8_t revbuf1[6];
uint8_t revbuf2[6];
uint8_t revbuf3[6];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{		
		/*����1���жϺ���*/
    if(huart->Instance == USART1)             /* ����Ǵ���1 */
    {
			HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin); 
			HAL_UART_Transmit_IT(&huart1,revbuf1,sizeof(revbuf1));
			HAL_UART_Receive_IT(&huart1,revbuf1,sizeof(revbuf1));
    }
		/*����2���жϺ���*/
		if(huart->Instance == USART2)             /* ����Ǵ���1 */
    { 
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			HAL_UART_Transmit_IT(&huart2,revbuf2,sizeof(revbuf2));
			HAL_UART_Receive_IT(&huart2,revbuf2,sizeof(revbuf2));
		}
		/*����2���жϺ���*/
		if(huart->Instance == USART3)             /* ����Ǵ���1 */
    {
      HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
			HAL_UART_Transmit_IT(&huart3,revbuf3,sizeof(revbuf3));
			HAL_UART_Receive_IT(&huart3,revbuf3,sizeof(revbuf3));
		}
}
/***************************************************���ڻص�����*****************************************************************************************/

///**
// * @brief       ����1�жϷ�����
// * @param       ��
// * @retval      ��
// */
//void USART1_IRQn(void)
//{ 
//    uint32_t timeout = 0;
//    uint32_t maxDelay = 0x1FFFF;
//    
//    HAL_UART_IRQHandler(&g_uart1_handle);       /* ����HAL���жϴ����ú��� */

//    timeout = 0;
//    while (HAL_UART_GetState(&g_uart1_handle) != HAL_UART_STATE_READY) /* �ȴ����� */
//    {
//        timeout++;                              /* ��ʱ���� */
//        if(timeout > maxDelay)
//        {
//            break;
//        }
//    }
//     
//    timeout=0;
//    
//    /* һ�δ������֮�����¿����жϲ�����RxXferCountΪ1 */
//    while (HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE) != HAL_OK)
//    {
//        timeout++;                              /* ��ʱ���� */
//        if (timeout > maxDelay)
//        {
//            break;
//        }
//    }
//}

///**
// * @brief       ����2�жϷ�����
// * @param       ��
// * @retval      ��
// */
//void USART2_IRQn(void)
//{ 
//    uint32_t timeout = 0;
//    uint32_t maxDelay = 0x1FFFF;
//    
//    HAL_UART_IRQHandler(&g_uart2_handle);       /* ����HAL���жϴ����ú��� */

//    timeout = 0;
//    while (HAL_UART_GetState(&g_uart2_handle) != HAL_UART_STATE_READY) /* �ȴ����� */
//    {
//        timeout++;                              /* ��ʱ���� */
//        if(timeout > maxDelay)
//        {
//            break;
//        }
//    }
//     
//    timeout=0;
//    
//    /* һ�δ������֮�����¿����жϲ�����RxXferCountΪ1 */
//    while (HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)g_rx2_buffer, RX2BUFFERSIZE) != HAL_OK)
//    {
//        timeout++;                              /* ��ʱ���� */
//        if (timeout > maxDelay)
//        {
//            break;
//        }
//    }
//}

///**
// * @brief       ����3�жϷ�����
// * @param       ��
// * @retval      ��
// */
//void USART3_IRQn(void)
//{ 
//    uint32_t timeout = 0;
//    uint32_t maxDelay = 0x1FFFF;
//    
//    HAL_UART_IRQHandler(&g_uart3_handle);       /* ����HAL���жϴ����ú��� */

//    timeout = 0;
//    while (HAL_UART_GetState(&g_uart3_handle) != HAL_UART_STATE_READY) /* �ȴ����� */
//    {
//        timeout++;                              /* ��ʱ���� */
//        if(timeout > maxDelay)
//        {
//            break;
//        }
//    }
//     
//    timeout=0;
//    
//    /* һ�δ������֮�����¿����жϲ�����RxXferCountΪ1 */
//    while (HAL_UART_Receive_IT(&g_uart3_handle, (uint8_t *)g_rx3_buffer, RX2BUFFERSIZE) != HAL_OK)
//    {
//        timeout++;                              /* ��ʱ���� */
//        if (timeout > maxDelay)
//        {
//            break;
//        }
//    }
//}
/* USER CODE END 1 */
