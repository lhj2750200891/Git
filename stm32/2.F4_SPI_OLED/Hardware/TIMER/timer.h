#ifndef __TIMER_H
#define __TIMER_H

#include"main.h"

extern int16_t EncoderA,EncoderB;
extern int16_t S_EncoderA,S_EncoderB;
extern int16_t AX,AY,AZ,GX,GY,GZ;//陀螺仪的6个数据
void Reading(int16_t *L_Val,int16_t *R_Val);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
