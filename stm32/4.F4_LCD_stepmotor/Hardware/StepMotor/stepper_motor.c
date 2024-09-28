#include "main.h"

STEPPER_MOTOR g_stepper = {0};
Step_Pulse_Add Pulse_Add;
void StepMotor_STOP(void)
{
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH1);     /* �رն�ӦPWMͨ�� */
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH2);     /* �رն�ӦPWMͨ�� */
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH3);     /* �رն�ӦPWMͨ�� */
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH4);     /* �رն�ӦPWMͨ�� */
}

/**
 * @brief       ��ʼ������������IO��, ��ʹ��ʱ��
 * @param       arr: �Զ���װֵ
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void stepper_init(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct;

    STEPPER_DIR1_GPIO_CLK_ENABLE();                                 /* DIR1ʱ��ʹ�� */
    STEPPER_DIR2_GPIO_CLK_ENABLE();                                 /* DIR2ʱ��ʹ�� */
    STEPPER_DIR3_GPIO_CLK_ENABLE();                                 /* DIR3ʱ��ʹ�� */
    STEPPER_DIR4_GPIO_CLK_ENABLE();                                 /* DIR4ʱ��ʹ�� */    

    gpio_init_struct.Pin = STEPPER_DIR1_GPIO_PIN;                   /* DIR1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                    /* ������� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                          /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;                   /* ���� */
    HAL_GPIO_Init(STEPPER_DIR1_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR1���� */

    gpio_init_struct.Pin = STEPPER_DIR2_GPIO_PIN;                   /* DIR2���� */
    HAL_GPIO_Init(STEPPER_DIR2_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR2���� */

    gpio_init_struct.Pin = STEPPER_DIR3_GPIO_PIN;                   /* DIR3���� */
    HAL_GPIO_Init(STEPPER_DIR3_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR3���� */

    gpio_init_struct.Pin = STEPPER_DIR4_GPIO_PIN;                   /* DIR4���� */
    HAL_GPIO_Init(STEPPER_DIR4_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR4���� */
    
    atim_timx_oc_chy_init(arr, psc);                                /* ��ʼ��PUL���ţ��Լ�����ģʽ�� */
}

/**
 * @brief       �����������
 * @param       motor_num: ��������ӿ����
 * @retval      ��
 */
void stepper_star(uint8_t motor_num,uint8_t dir)
{
		HAL_TIM_Base_Start_IT(&TIM8_Handle);
    switch(motor_num)
    {
        case STEPPER_MOTOR_1 :
        {
						ST1_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH1);     /* ������ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_2 :
        {
						ST2_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH2);     /* ������ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_3 :
        {
						ST3_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH3);     /* ������ӦPWMͨ�� */
            break;  
        }
        case STEPPER_MOTOR_4 :
        {
						ST4_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH4);     /* ������ӦPWMͨ�� */
            break;
        }
        default : break;
    }
}

/**
 * @brief       �رղ������
 * @param       motor_num: ��������ӿ����
 * @retval      ��
 */
void stepper_stop(uint8_t motor_num)
{
		HAL_TIM_Base_Stop_IT(&TIM8_Handle);
    switch(motor_num)
    {
        case STEPPER_MOTOR_1 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH1);     /* �رն�ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_2 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH2);     /* �رն�ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_3 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH3);     /* �رն�ӦPWMͨ�� */
            break;  
        }
        case STEPPER_MOTOR_4 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH4);     /* �رն�ӦPWMͨ�� */
            break;
        }
        default : break;
    }
}

/*
	�������ܣ������������
	��ڲ�������
	����ֵ����
	arr = 400ʱ��f=168000000/400/168=2500,��T=0.4ms������0.4ms��һ����һȦ6400������Ҫ2.56s��ת��r=1/2.56=0.39
*/
void Set_Stepper_Speed(double ARR)    //��λ��תÿ��
{
	 ARR = (int)156.25/ARR;
	 __HAL_TIM_SetAutoreload(&TIM8_Handle,ARR);
   __HAL_TIM_SetCompare(&TIM8_Handle,ATIM_TIM8_PWM_CH1,ARR/2);
	 __HAL_TIM_SetAutoreload(&TIM8_Handle,ARR);
   __HAL_TIM_SetCompare(&TIM8_Handle,ATIM_TIM8_PWM_CH2,ARR/2);
	 __HAL_TIM_SetAutoreload(&TIM8_Handle,ARR);
	 __HAL_TIM_SetCompare(&TIM8_Handle,ATIM_TIM8_PWM_CH3,ARR/2);
	 __HAL_TIM_SetAutoreload(&TIM8_Handle,ARR);
   __HAL_TIM_SetCompare(&TIM8_Handle,ATIM_TIM8_PWM_CH4,ARR/2);
}
/*
 �������ܣ����õ���ٶ�
 ��ڲ�����speed��������װ��ֵ��С
 ��ڲ�����Channel�����ö�ʱ��ͨ��
 ����ֵ����
*/
void stepper_pwmt_speed(uint16_t speed,uint32_t Channel)
{
    __HAL_TIM_SetAutoreload(&TIM8_Handle,speed);
    __HAL_TIM_SetCompare(&TIM8_Handle,Channel,__HAL_TIM_GET_AUTORELOAD(&TIM8_Handle)>>1);
}

/*
�������ܣ���������Ʋ�
��ڲ�����angle �������ת�̶��Ƕȣ�dir ����motor_num �������ID
����ֵ����
ע��������*�����/ϸ���� = ��ת�Ƕ�
*/
int Step_Angle=0,StepMotor_Num;
void Step_Motor_SetAngle(uint16_t angle, uint8_t dir,uint8_t motor_num)
{
	if(motor_num==STEPPER_MOTOR_1) StepMotor_Num=1;   /* ����ֱ�Ʋ� */
	else if(motor_num==STEPPER_MOTOR_2) StepMotor_Num=2;
	else if(motor_num==STEPPER_MOTOR_3) StepMotor_Num=3;
	else if(motor_num==STEPPER_MOTOR_4) StepMotor_Num=4;
	else StepMotor_Num=0;
	
	g_stepper.pulse_count = angle / MAX_STEP_ANGLE;
	if(g_stepper.pulse_count == 0) 
  {
     stepper_stop(motor_num);
  }
  else stepper_star(motor_num,dir);
}
