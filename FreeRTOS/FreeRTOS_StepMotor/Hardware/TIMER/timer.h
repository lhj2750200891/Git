#ifndef __TIMER_H
#define __TIMER_H

#include"main.h"

extern int Time;
extern int16_t EncoderA,EncoderB,EncoderC,EncoderD;
extern int16_t S_EncoderA,S_EncoderB,S_EncoderC,S_EncoderD;
void Reading(int16_t *L1_Val,int16_t *R1_Val,int16_t *L2_Val,int16_t *R2_Val);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
