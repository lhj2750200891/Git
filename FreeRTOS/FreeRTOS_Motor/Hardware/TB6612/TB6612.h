#ifndef __TB6612_H
#define __TB6612_H

#include"main.h"

#define AIN1(x)   do{ x ? \
                      HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define AIN2(x)   do{ x ? \
                      HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define BIN1(x)   do{ x ? \
                      HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define BIN2(x)   do{ x ? \
                      HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define CIN1(x)   do{ x ? \
                      HAL_GPIO_WritePin(CIN1_GPIO_Port,CIN1_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(CIN1_GPIO_Port,CIN1_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define CIN2(x)   do{ x ? \
                      HAL_GPIO_WritePin(CIN2_GPIO_Port,CIN2_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(CIN2_GPIO_Port,CIN2_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define DIN1(x)   do{ x ? \
                      HAL_GPIO_WritePin(DIN1_GPIO_Port,DIN1_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(DIN1_GPIO_Port,DIN1_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

#define DIN2(x)   do{ x ? \
                      HAL_GPIO_WritePin(DIN2_GPIO_Port,DIN2_Pin,GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(DIN2_GPIO_Port,DIN2_Pin,GPIO_PIN_RESET); \
                  }while(0)       /* LED0 = RED */

uint32_t myabs(int x);
int Xianfu(int data,int max);
void PWMA_Set(int duty);
void PWMB_Set(int duty);
void PWMC_Set(int duty);
void PWMD_Set(int duty);		
void Servo1_Angle(int Angle);
void Servo2_Angle(int Angle);									
#endif
