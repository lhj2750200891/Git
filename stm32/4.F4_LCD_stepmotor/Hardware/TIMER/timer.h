#ifndef __TIMER_H
#define __TIMER_H

#include"main.h"
extern int Time;
extern int16_t EncoderA,EncoderB;
extern int16_t S_EncoderA,S_EncoderB;
void Reading(int16_t *L_Val,int16_t *R_Val);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
