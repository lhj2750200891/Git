#ifndef __OLED_H
#define __OLED_H
#include "stdint.h"
#include "main.h"

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define DC_Pin GPIO_PIN_15
#define DC_GPIO_Port GPIOG
#define OLED_DC_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* ����IO��ʱ��ʹ�� */

#define RST_Pin GPIO_PIN_14
#define RST_GPIO_Port GPIOG
#define OLED_RST_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* ����IO��ʱ��ʹ�� */

#define SDIN_Pin GPIO_PIN_13
#define SDIN_GPIO_Port GPIOG
#define OLED_CS_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* ����IO��ʱ��ʹ�� */

#define SCLK_Pin GPIO_PIN_12
#define SCLK_GPIO_Port GPIOG
#define OLED_CLK_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* ����IO��ʱ��ʹ�� */

//OLED�����ú���
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);
void OLED_DrawPoint_Shu(uint8_t x,uint8_t y,uint8_t t);
void OLED_Show(void);

#endif

