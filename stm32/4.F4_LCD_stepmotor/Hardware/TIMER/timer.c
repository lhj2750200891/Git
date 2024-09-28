#include "main.h"

/*ȫ�ֱ����Ķ���*/
int CNT1=0,CNT2=0,Time=0;
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
//		Reading(&EncoderA,&EncoderB);   //��ȡ��ɣ��Զ�����
//		S_EncoderB+=EncoderB;
//		S_EncoderA+=EncoderA;
//		if(keyflag==1)
//		{
//			speed_pid();
//			addPID.target_val = 10;	
//			add2PID.target_val = 10;
//			printf("���֣�%d\r\n",EncoderA);
//			printf("���֣�%d\r\n",EncoderB);
//		}
//		if(keyflag==2)
//		{
//			speed_pid();
//			PWMA_Set(0);
//			PWMB_Set(0);
//			printf("���֣�%d\r\n",EncoderA);
//			printf("���֣�%d\r\n",EncoderB);
//		}
//		if(keyflag==3)
//		{
//			Motor_Control_ClosedLoop();
//			printf("���֣�%d\r\n",S_EncoderA);
//			printf("���֣�%d\r\n",S_EncoderB);
//		}
	}
	
	if(htim->Instance==TIM7)   //200ms
	{
		CNT2++;
		ADC_Vol=(double)StartAndGetOneResult()*3.3*11/4096;//��ȡת����ADֵ
		ADC_Vol1=ADC_Vol*100;
		ADC_Vol2=(int)ADC_Vol1%100;
		//OLED_Show();
		if(CNT2==5)
		{
			Time++;
			CNT2=0;
		}
	}
  if(htim->Instance==TIM8)   //���Ʋ�������Ķ�ʱ��
  {
     Step_Run_Flag = 1;                             /* ��־λ��һ */
		 if(StepMotor_Num==1)    //�ж�����һ���������
		 {
				Pulse_Add.StepMotor1++;   //������ۼ���
		 }
		 else if(StepMotor_Num==2)
		 {
				Pulse_Add.StepMotor2++;   //������ۼ���
		 }
		 else if(StepMotor_Num==3)
		 {
				Pulse_Add.StepMotor3++;   //������ۼ���
		 }
		 else if(StepMotor_Num==4)
		 {
				Pulse_Add.StepMotor4++;   //������ۼ���
		 }
		 
     g_stepper.pulse_count--;                    /* ÿһ�������������-- */
     if(g_stepper.dir == CW)
     {
        g_stepper.add_pulse_count++;             /* ����λ��++ */
     }else
     {
        g_stepper.add_pulse_count--;             /* ����λ��-- */
     }

     if(g_stepper.pulse_count<=0 && StepMotor_Num == 1)                /* ������������0��ʱ�� ������Ҫ���͵������������ɣ�ֹͣ��ʱ����� */
     {
         printf("�ۼ���ת�ĽǶ�:%d\r\n",(int)(g_stepper.add_pulse_count*MAX_STEP_ANGLE));  /* ��ӡ�ۼ�ת���˶��ٽǶ� */
         stepper_stop(STEPPER_MOTOR_1);          /* ֹͣ�ӿ�һ��� */
         Step_Run_Flag = 0;
     }
     else if(g_stepper.pulse_count<=0 && StepMotor_Num == 2)                /* ������������0��ʱ�� ������Ҫ���͵������������ɣ�ֹͣ��ʱ����� */
     {
         printf("�ۼ���ת�ĽǶ�:%d\r\n",(int)(g_stepper.add_pulse_count*MAX_STEP_ANGLE));  /* ��ӡ�ۼ�ת���˶��ٽǶ� */
         stepper_stop(STEPPER_MOTOR_2);          /* ֹͣ�ӿ�һ��� */
         Step_Run_Flag = 0;
     }
     else if(g_stepper.pulse_count<=0 && StepMotor_Num == 3)                /* ������������0��ʱ�� ������Ҫ���͵������������ɣ�ֹͣ��ʱ����� */
     {
         printf("�ۼ���ת�ĽǶ�:%d\r\n",(int)(g_stepper.add_pulse_count*MAX_STEP_ANGLE));  /* ��ӡ�ۼ�ת���˶��ٽǶ� */
         stepper_stop(STEPPER_MOTOR_3);          /* ֹͣ�ӿ�һ��� */
         Step_Run_Flag = 0;
     }
     else if(g_stepper.pulse_count<=0 && StepMotor_Num == 4)                /* ������������0��ʱ�� ������Ҫ���͵������������ɣ�ֹͣ��ʱ����� */
     {
         printf("�ۼ���ת�ĽǶ�:%d\r\n",(int)(g_stepper.add_pulse_count*MAX_STEP_ANGLE));  /* ��ӡ�ۼ�ת���˶��ٽǶ� */
         stepper_stop(STEPPER_MOTOR_4);          /* ֹͣ�ӿ�һ��� */
         Step_Run_Flag = 0;
     }
   } 	
}
