#include "spi.h"

void LCD_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  __HAL_RCC_GPIOG_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12|LCD_TIRQ_Pin|LCD_TD0_Pin|LCD_TD1_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOG,LCD_TCS_Pin|LCD_TCLK_Pin|LCD_SCK_Pin|D0_Pin|D1_Pin|RES_Pin|DC_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_12|LCD_TIRQ_Pin|LCD_TD0_Pin|LCD_TD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

void  SPIv_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
	  if(Data&0x80)	
	  SPI_MOSI_SET; //Êä³öÊý¾Ý
      else SPI_MOSI_CLR;
	   
      SPI_SCLK_CLR;       
      SPI_SCLK_SET;
      Data<<=1; 
	}
}
