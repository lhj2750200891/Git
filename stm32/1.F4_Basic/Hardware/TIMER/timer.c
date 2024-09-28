#include "LED.h"
#include "gpio.h"
#include "KEY.h"
#include "timer.h"
#include "tim.h"
#include "stdio.h"
#include "adc.h"
#include "pid.h"
#include "TB6612.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

/*ȫ�ֱ����Ķ���*/
int CNT1=0,CNT2=0;
int16_t EncoderA=0,EncoderB=0;   //10MS�ڵ�������
int16_t S_EncoderA=0,S_EncoderB=0;//�����ۼ�
/*ȫ�ֱ��������ã�extern��*/

/*
�������ܣ�HAL�ⶨʱ����ȡ��������ֵ
��ڲ�������
����ֵ����
*/
void Reading(int16_t *L_Val,int16_t *R_Val)
{
	*R_Val=TIM5->CNT; //��ȡ����
	TIM5->CNT = 0;
	*L_Val=-TIM4->CNT;
	TIM4->CNT = 0;
}

/*
�������ܣ�HAL�ⶨʱ���Ļص�����
��ڲ�������
����ֵ����
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM6)   //10ms
	{
		CNT1++;
		Reading(&EncoderA,&EncoderB);   //��ȡ��ɣ��Զ�����
		S_EncoderB+=EncoderB;
		S_EncoderA+=EncoderA;
		if(keyflag==1)
		{
			speed_pid();
			addPID.target_val = 10;	
			add2PID.target_val = 10;
			printf("���֣�%d\r\n",EncoderA);
			printf("���֣�%d\r\n",EncoderB);
		}
		if(keyflag==2)
		{
			speed_pid();
			PWMC_Set(0);
			PWMD_Set(0);
			printf("���֣�%d\r\n",EncoderA);
			printf("���֣�%d\r\n",EncoderB);
		}
		if(keyflag==3)
		{
			Motor_Control_ClosedLoop();
			printf("���֣�%d\r\n",S_EncoderA);
			printf("���֣�%d\r\n",S_EncoderB);
		}
	}
	
	if(htim->Instance==TIM7)   //200ms
	{
		CNT2++;
		ADC_Vol=(double)StartAndGetOneResult()*3.3*11/4096;//��ȡת����ADֵ
		if(CNT2==5)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			CNT2=0;
		}
	}	
}
