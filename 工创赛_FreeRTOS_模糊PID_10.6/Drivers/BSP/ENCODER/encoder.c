#include "encoder.h"
#include "./BSP/TIMER/btim.h"



/***********************************
*	用于M测速法，每10ms读一次编码盘的值并清零
*	设半径单位为mm，公式中 10 表示10ms
*	可得转速为    (Encoder_TIM/(编码器线数*减速比*4))/10
*	可得线速度为 ( (Encoder_TIM/(编码器线数*减速比*4)) * 2 * pi * R ) / 10
*	举例:N20直流电机  编码器7线 减速比为1:50 R=D/2 =22.5mm 速度设定值为10
*		r(转速) = 10/(7*50*4)/0.01 = 0.7143rad/s  (这里单位是s)
		v(线速度) = r * 2*pi*R = 100.97mm/s = 0.1m/s
************************************/

//读取并清零
void Reading(int16_t *L_Val,int16_t *R_Val)
{

	*L_Val=TIM2->CNT; //读取计数
	TIM2->CNT = 0;
	*R_Val=TIM3->CNT;
	TIM3->CNT = 0;
}
void Readingback(int16_t *L_Val,int16_t *R_Val)
{

	*L_Val=TIM5->CNT; //读取计数
	TIM5->CNT = 0;
	*R_Val=TIM4->CNT;
	TIM4->CNT = 0;
}
