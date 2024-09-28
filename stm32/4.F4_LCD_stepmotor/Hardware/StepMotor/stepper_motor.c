#include "main.h"

STEPPER_MOTOR g_stepper = {0};
Step_Pulse_Add Pulse_Add;
void StepMotor_STOP(void)
{
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH1);     /* 关闭对应PWM通道 */
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH2);     /* 关闭对应PWM通道 */
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH3);     /* 关闭对应PWM通道 */
	HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH4);     /* 关闭对应PWM通道 */
}

/**
 * @brief       初始化步进电机相关IO口, 并使能时钟
 * @param       arr: 自动重装值
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void stepper_init(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct;

    STEPPER_DIR1_GPIO_CLK_ENABLE();                                 /* DIR1时钟使能 */
    STEPPER_DIR2_GPIO_CLK_ENABLE();                                 /* DIR2时钟使能 */
    STEPPER_DIR3_GPIO_CLK_ENABLE();                                 /* DIR3时钟使能 */
    STEPPER_DIR4_GPIO_CLK_ENABLE();                                 /* DIR4时钟使能 */    

    gpio_init_struct.Pin = STEPPER_DIR1_GPIO_PIN;                   /* DIR1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                    /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                          /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;                   /* 低速 */
    HAL_GPIO_Init(STEPPER_DIR1_GPIO_PORT, &gpio_init_struct);       /* 初始化DIR1引脚 */

    gpio_init_struct.Pin = STEPPER_DIR2_GPIO_PIN;                   /* DIR2引脚 */
    HAL_GPIO_Init(STEPPER_DIR2_GPIO_PORT, &gpio_init_struct);       /* 初始化DIR2引脚 */

    gpio_init_struct.Pin = STEPPER_DIR3_GPIO_PIN;                   /* DIR3引脚 */
    HAL_GPIO_Init(STEPPER_DIR3_GPIO_PORT, &gpio_init_struct);       /* 初始化DIR3引脚 */

    gpio_init_struct.Pin = STEPPER_DIR4_GPIO_PIN;                   /* DIR4引脚 */
    HAL_GPIO_Init(STEPPER_DIR4_GPIO_PORT, &gpio_init_struct);       /* 初始化DIR4引脚 */
    
    atim_timx_oc_chy_init(arr, psc);                                /* 初始化PUL引脚，以及脉冲模式等 */
}

/**
 * @brief       开启步进电机
 * @param       motor_num: 步进电机接口序号
 * @retval      无
 */
void stepper_star(uint8_t motor_num,uint8_t dir)
{
		HAL_TIM_Base_Start_IT(&TIM8_Handle);
    switch(motor_num)
    {
        case STEPPER_MOTOR_1 :
        {
						ST1_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH1);     /* 开启对应PWM通道 */
            break;
        }
        case STEPPER_MOTOR_2 :
        {
						ST2_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH2);     /* 开启对应PWM通道 */
            break;
        }
        case STEPPER_MOTOR_3 :
        {
						ST3_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH3);     /* 开启对应PWM通道 */
            break;  
        }
        case STEPPER_MOTOR_4 :
        {
						ST4_DIR(dir);
            HAL_TIM_PWM_Start(&TIM8_Handle, ATIM_TIM8_PWM_CH4);     /* 开启对应PWM通道 */
            break;
        }
        default : break;
    }
}

/**
 * @brief       关闭步进电机
 * @param       motor_num: 步进电机接口序号
 * @retval      无
 */
void stepper_stop(uint8_t motor_num)
{
		HAL_TIM_Base_Stop_IT(&TIM8_Handle);
    switch(motor_num)
    {
        case STEPPER_MOTOR_1 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH1);     /* 关闭对应PWM通道 */
            break;
        }
        case STEPPER_MOTOR_2 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH2);     /* 关闭对应PWM通道 */
            break;
        }
        case STEPPER_MOTOR_3 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH3);     /* 关闭对应PWM通道 */
            break;  
        }
        case STEPPER_MOTOR_4 :
        {
            HAL_TIM_PWM_Stop(&TIM8_Handle, ATIM_TIM8_PWM_CH4);     /* 关闭对应PWM通道 */
            break;
        }
        default : break;
    }
}

/*
	函数功能：步进电机调速
	入口参数：无
	返回值：无
	arr = 400时，f=168000000/400/168=2500,则T=0.4ms，所以0.4ms走一步，一圈6400步，需要2.56s，转速r=1/2.56=0.39
*/
void Set_Stepper_Speed(double ARR)    //单位是转每秒
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
 函数功能：设置电机速度
 入口参数：speed，设置重装载值大小
 入口参数：Channel，设置定时器通道
 返回值：无
*/
void stepper_pwmt_speed(uint16_t speed,uint32_t Channel)
{
    __HAL_TIM_SetAutoreload(&TIM8_Handle,speed);
    __HAL_TIM_SetCompare(&TIM8_Handle,Channel,__HAL_TIM_GET_AUTORELOAD(&TIM8_Handle)>>1);
}

/*
函数功能：步进电机计步
入口参数：angle 步进电机转固定角度，dir 方向，motor_num 步进电机ID
返回值：无
注：脉冲数*步距角/细分数 = 旋转角度
*/
int Step_Angle=0,StepMotor_Num;
void Step_Motor_SetAngle(uint16_t angle, uint8_t dir,uint8_t motor_num)
{
	if(motor_num==STEPPER_MOTOR_1) StepMotor_Num=1;   /* 方便分别计步 */
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
