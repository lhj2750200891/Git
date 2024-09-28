#include "sys.h"

#ifndef _SPI_H_
#define _SPI_H_

//Һ�����ƿ���1�������궨��

#define	SPI_MOSI_SET  	HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET) //LCD_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	HAL_GPIO_WritePin(LCD_SCK_GPIO_Port,LCD_SCK_Pin,GPIO_PIN_SET) //LCD_CTRL->BSRR=SPI_SCLK    


//Һ�����ƿ���0�������궨��

#define	SPI_MOSI_CLR  	HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET) //LCD_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	HAL_GPIO_WritePin(LCD_SCK_GPIO_Port,LCD_SCK_Pin,GPIO_PIN_RESET) //LCD_CTRL->BRR=SPI_SCLK    

void  SPIv_WriteData(u8 Data);

#endif
