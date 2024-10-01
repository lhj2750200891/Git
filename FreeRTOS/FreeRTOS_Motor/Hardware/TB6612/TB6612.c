#include "main.h"

/*
在pwm的配置中，如果频率过高，会引起驱动发烫的现象，为防止驱动发烫，设置psc=4，arr=8399，则频率为84000000/((4+1)(8399+1))=2kHz,建议频率1k-20k
*/
/*
函数功能：绝对值函数
入口参数：输入量
返回值：输出量
*/
uint32_t myabs(int x)
{
	if(x>=0) return x;
	else return -x;
}

/*
函数功能：限幅函数
入口参数：输入量
返回值：输出量
*/
int Xianfu(int data,int max)
{	
    if(data<-max) data=-max;	
    if(data> max) data= max;	
    return data;
}

/*
函数功能：设置pwm通道占空比
入口参数：duty目标占空比
返回值：无
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

//////////////////////////////////////////////////////////////////////舵机///////////////////////////////////////////////////////////////////////////////////////
/*
函数功能：控制舵机旋转角度
入口参数：度数
返回值：无
*/
void Servo1_Angle(int Angle)   //PA8
{
	int Duty=0;
	Duty=((Angle*42/9)+210);//对于180度舵机
//	Duty=((Angle*100/9)+500);//对于180度舵机
//Duty=(Angle*50/9)+500;//对于360度舵机
//Duty=(Angle*200/27)+500;//对于270度舵机
	TIM1->CCR1 = Duty;
}

void Servo2_Angle(int Angle)   //PA11
{
	int Duty=0;
	Duty=((Angle*42/9)+210);//对于180度舵机
//	Duty=((Angle*100/9)+500);//对于180度舵机
//Duty=(Angle*50/9)+500;//对于360度舵机
//Duty=(Angle*200/27)+500;//对于270度舵机
	TIM1->CCR4 = Duty;
}
