/*
基础配置部分包括：
1.3个LED配置，端口检测正常 -->A4、E6、E4
2.3个KEY配置，端口检测正常 -->E7、E8、E9
3.usart端口检测正常，重定向正常
4.ADC检测电压端口检测正常，电压值正常显示、正常变化
5.2个定时器（TIM6、TIM7）分别用于计时，定时正常
6.1个高级定时器，用于驱动直流电机（C6、C7、C8、C9）
7.直流电机编码器读值完成（TIM4、TIM5）
8.PID速度环与速度位置双闭环控制
9.mpu6050陀螺仪dmp库移植成功
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
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//PA8-->舵机
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);//PA11-->舵机
	
	HAL_UART_Receive_IT(&huart1,revbuf1,sizeof(revbuf1));
	HAL_UART_Receive_IT(&huart2,revbuf2,sizeof(revbuf2));
	HAL_UART_Receive_IT(&huart3,revbuf3,sizeof(revbuf3));
	
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);//右轮
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);//左轮
	
	HAL_ADC_Start(&hadc1);
	
	PID_param_init();

	//陀螺仪
	MPU_Init(); //初始化MPU6050
	while(mpu_dmp_init()) //DMP初始化
	{
		printf("DMP初始化失败!失败代码：%d\r\n",mpu_dmp_init());
	}

  while (1)
  {

		if(mpu_dmp_get_data(&pitch, &roll, &yaw)==0)
		{
			printf("pitch:%.3f\r\n",pitch);
			printf("roll:%.3f\r\n",roll);
			printf("yaw:%.3f\r\n",yaw);
			printf("电池电压：%.2fV\r\n",ADC_Vol);
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

