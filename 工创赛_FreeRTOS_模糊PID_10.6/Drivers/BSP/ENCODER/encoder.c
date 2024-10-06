#include "encoder.h"
#include "./BSP/TIMER/btim.h"



/***********************************
*	����M���ٷ���ÿ10ms��һ�α����̵�ֵ������
*	��뾶��λΪmm����ʽ�� 10 ��ʾ10ms
*	�ɵ�ת��Ϊ    (Encoder_TIM/(����������*���ٱ�*4))/10
*	�ɵ����ٶ�Ϊ ( (Encoder_TIM/(����������*���ٱ�*4)) * 2 * pi * R ) / 10
*	����:N20ֱ�����  ������7�� ���ٱ�Ϊ1:50 R=D/2 =22.5mm �ٶ��趨ֵΪ10
*		r(ת��) = 10/(7*50*4)/0.01 = 0.7143rad/s  (���ﵥλ��s)
		v(���ٶ�) = r * 2*pi*R = 100.97mm/s = 0.1m/s
************************************/

//��ȡ������
void Reading(int16_t *L_Val,int16_t *R_Val)
{

	*L_Val=TIM2->CNT; //��ȡ����
	TIM2->CNT = 0;
	*R_Val=TIM3->CNT;
	TIM3->CNT = 0;
}
void Readingback(int16_t *L_Val,int16_t *R_Val)
{

	*L_Val=TIM5->CNT; //��ȡ����
	TIM5->CNT = 0;
	*R_Val=TIM4->CNT;
	TIM4->CNT = 0;
}
