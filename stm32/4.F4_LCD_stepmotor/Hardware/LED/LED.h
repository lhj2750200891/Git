#ifndef __LED_H
#define __LED_H

#include"main.h"

#define LED0(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define LED1(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define LED2(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

void GPIO_Init(void);		
void LED_Init(void);									
#endif
