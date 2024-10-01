#ifndef __KEY_H
#define __KEY_H

#include "stdint.h"

#define KEY0 HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)

extern int keyflag;
uint8_t key_scan(uint8_t mode);
void Key_Control(void);
#endif
