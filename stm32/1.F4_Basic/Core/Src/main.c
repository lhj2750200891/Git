/*
�������ò��ְ�����
1.3��LED���ã��˿ڼ������ -->A4��E6��E4
2.3��KEY���ã��˿ڼ������ -->E7��E8��E9
3.usart�˿ڼ���������ض�������
4.ADC����ѹ�˿ڼ����������ѹֵ������ʾ�������仯
5.2����ʱ����TIM6��TIM7���ֱ����ڼ�ʱ����ʱ����
6.1���߼���ʱ������������ֱ�������C6��C7��C8��C9��
7.ֱ�������������ֵ��ɣ�TIM4��TIM5��
8.PID�ٶȻ����ٶ�λ��˫�ջ�����
9.mpu6050������dmp����ֲ�ɹ�
*/
#include "main.h"

uint8_t i=0;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_TIM5_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
	GPIO_Init();
	
	HAL_TIM_Base_Start_IT(&htim6);  //10ms
	HAL_TIM_Base_Start_IT(&htim7);  //200ms
	
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//PA8-->���
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);//PA11-->���
	
	HAL_UART_Receive_IT(&huart1,revbuf1,sizeof(revbuf1));
	HAL_UART_Receive_IT(&huart2,revbuf2,sizeof(revbuf2));
	HAL_UART_Receive_IT(&huart3,revbuf3,sizeof(revbuf3));
	
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);//����
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);//����
	
	HAL_ADC_Start(&hadc1);
	
	PID_param_init();

	//������
	MPU_Init(); //��ʼ��MPU6050
	while(mpu_dmp_init()) //DMP��ʼ��
	{
		printf("DMP��ʼ��ʧ��!ʧ�ܴ��룺%d\r\n",mpu_dmp_init());
	}

  while (1)
  {

		if(mpu_dmp_get_data(&pitch, &roll, &yaw)==0)
		{
			printf("pitch:%.3f\r\n",pitch);
			printf("roll:%.3f\r\n",roll);
			printf("yaw:%.3f\r\n",yaw);
			printf("��ص�ѹ��%.2fV\r\n",ADC_Vol);
			printf("-----------------------------------------------------------\r\n");
			HAL_Delay(800);
		}
		Key_Control();
  }
}






















void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

