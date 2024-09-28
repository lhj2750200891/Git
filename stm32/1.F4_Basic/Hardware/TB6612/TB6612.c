#include "TB6612.h"
#include "main.h"
#include "TIM.h"

/*
��pwm�������У����Ƶ�ʹ��ߣ��������������̵�����Ϊ��ֹ�������̣�����psc=4��arr=8399����Ƶ��Ϊ84000000/((4+1)(8399+1))=2kHz,����Ƶ��1k-20k
*/
/*
�������ܣ�����ֵ����
��ڲ�����������
����ֵ�������
*/
uint32_t myabs(int x)
{
	if(x>=0) return x;
	else return -x;
}

/*
�������ܣ��޷�����
��ڲ�����������
����ֵ�������
*/
int Xianfu(int data,int max)
{	
    if(data<-max) data=-max;	
    if(data> max) data= max;	
    return data;
}

/*
�������ܣ�����pwmͨ��ռ�ձ�
��ڲ�����dutyĿ��ռ�ձ�
����ֵ����
*/
void PWMA_Set(int duty)
{
	uint16_t compare=0;
	compare=myabs(duty);
	if(duty>=0)
	{
		AIN1(0);
		AIN2(1);
	}
	else
	{
		AIN1(1);
		AIN2(0);		
	}
	//__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,compare*84);
	TIM8->CCR1 = compare*84;
}

void PWMB_Set(int duty)
{
	uint16_t compare=0;
	compare=myabs(duty);
	if(duty>=0)
	{
		BIN1(1);
		BIN2(0);
	}
	else
	{
		BIN1(0);
		BIN2(1);		
	}
	//__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,compare*84);
	TIM8->CCR2 = compare*84;
}

void PWMC_Set(int duty)
{
	uint16_t compare=0;
	compare=myabs(duty);
	if(duty>=0)
	{
		CIN1(0);
		CIN2(1);
	}
	else
	{
		CIN1(1);
		CIN2(0);		
	}
	//__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,compare*84);
	TIM8->CCR3 = compare*84;
}

void PWMD_Set(int duty)
{
	uint16_t compare=0;
	compare=myabs(duty);
	if(duty>=0)
	{
		DIN1(1);
		DIN2(0);
	}
	else
	{
		DIN1(0);
		DIN2(1);		
	}
	//__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,compare*84);
	TIM8->CCR4 = compare*84;
}

//////////////////////////////////////////////////////////////////////���///////////////////////////////////////////////////////////////////////////////////////
/*
�������ܣ����ƶ����ת�Ƕ�
��ڲ���������
����ֵ����
*/
void Servo1_Angle(int Angle)   //PA8
{
	int Duty=0;
	Duty=((Angle*42/9)+210);//����180�ȶ��
//	Duty=((Angle*100/9)+500);//����180�ȶ��
//Duty=(Angle*50/9)+500;//����360�ȶ��
//Duty=(Angle*200/27)+500;//����270�ȶ��
	TIM1->CCR1 = Duty;
}

void Servo2_Angle(int Angle)   //PA11
{
	int Duty=0;
	Duty=((Angle*42/9)+210);//����180�ȶ��
//	Duty=((Angle*100/9)+500);//����180�ȶ��
//Duty=(Angle*50/9)+500;//����360�ȶ��
//Duty=(Angle*200/27)+500;//����270�ȶ��
	TIM1->CCR4 = Duty;
}
