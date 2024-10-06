#ifndef _SPI_H_
#define _SPI_H
#include "./SYSTEM/sys/sys.h"


/*  LCD显示屏GPIO引脚配置与宏定义*/
#define LCD_TIRQ_Pin GPIO_PIN_13
#define LCD_TIRQ_GPIO_Port GPIOF
#define LCD_TD0_Pin GPIO_PIN_14
#define LCD_TD0_GPIO_Port GPIOF
#define LCD_TD1_Pin GPIO_PIN_15
#define LCD_TD1_GPIO_Port GPIOF
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

//液晶控制口置1操作语句宏定义

#define	SPI_MOSI_SET  	HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET) //LCD_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	HAL_GPIO_WritePin(LCD_SCK_GPIO_Port,LCD_SCK_Pin,GPIO_PIN_SET) //LCD_CTRL->BSRR=SPI_SCLK    


//液晶控制口置0操作语句宏定义

#define	SPI_MOSI_CLR  	HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET) //LCD_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	HAL_GPIO_WritePin(LCD_SCK_GPIO_Port,LCD_SCK_Pin,GPIO_PIN_RESET) //LCD_CTRL->BRR=SPI_SCLK    

void LCD_GPIO_Init(void);
void  SPIv_WriteData(u8 Data);

#endif
