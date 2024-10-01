#ifndef __TIMER_H
#define __TIMER_H

#include"main.h"

extern int16_t EncoderC,EncoderD;
extern int16_t S_EncoderC,S_EncoderD;
void Reading(int16_t *L_Val,int16_t *R_Val);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
