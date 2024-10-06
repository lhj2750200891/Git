#include "./BSP/MOTO/moto.h"
#include "pwm.h"
#include "oled.h"
#include "./SYSTEM/usart/usart.h"
#include "control.h"
#include "./BSP/GPIO/gpio.h"
#include "pid.h"  
#include "encoder.h"
#include "./BSP/NRF24L01/nrf24l01.h"
#include "./BSP/TIMER/btim.h"
#include "./SYSTEM/USART/usart.h"
 #include "./BSP/FuzzyPid/fuzzypid.h"
#include "./BSP/LED/led.h"
#include "./BSP/HWT101/HWT101.h"

enum mode pidmode;
int globel_speed;
int globel_position;
int left_speed,right_speed;
float pitch, roll,yaw; 			//欧拉角
int yaw_assisted = 1; // 航向角矫正选项，默认1为开启航向角矫正
int yaw_set_value = 0;//航向角设定值，默认0,在拐角处转向的时候变为90/-90/等等等等

/*Written By Mr.YangShunhang in 240811*/
/*@ 更新日志
*@  将PID内环改为比例-误差对数函数的PID模式，消除了速度环的误差
*@  外环位置环依然是模糊控制
*@  Improved by Mr. Yang Shunhang in 241005
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		/*10ms中断  定时器7*/
    if (htim == (&g_tim7_handle))//使用这个if的话可以自动清除中断标志位
    {
			Reading(&Encoder1,&Encoder2);      
			Readingback(&Encoder3,&Encoder4);
			//mpu_dmp_get_data(&pitch,&roll,&yaw);
			HWT101_GetData();
			if(pidmode==yaw_speed)
			{ 
			 yawspeed();													//串级：速度和陀螺仪的航向角
			}
			else if(pidmode==speedpid)
			{
				speed_pid();			//速度
				//gary_pid(globel_speed);
			}
			else if(pidmode==spd_position)
			{
				MotorControl();		//速度和位置
			}
			else if(pidmode == fuzzyspd_pid)
			{
				if(yaw_assisted == 1)
				{
					add_pid_normal(fuzzy_position_A_control()-yaw_output(),fuzzy_position_B_control()+yaw_output(),
																	fuzzy_position_C_control()-yaw_output(),fuzzy_position_D_control()+yaw_output());
				}else{
							add_pid_normal(fuzzy_position_A_control(),fuzzy_position_B_control(),
																	fuzzy_position_C_control(),fuzzy_position_D_control());
				}

			}
	  }
			/*1s中断  定时器6*/
		  else if (htim == (&g_tim6_handle))//使用这个if的话可以自动清除中断标志位
    {
			
				//HAL_GPIO_TogglePin(LED1_GPIO_PORT,LED1_GPIO_PIN);
		}
				
}




void gary(uint8_t left,uint8_t right)
{
	PWM1_Set(left);
	PWM2_Set(right);
	if(L2)
	{
		PWM1_Set(left);
	  PWM2_Set(right+10);
	}
	else if((!L2)&&L1)
	{
		PWM1_Set(left);
	  PWM2_Set(right+5);
	}
	else if((!L2)&&(!L1)&&M)
	{
		PWM1_Set(left);
	  PWM2_Set(right);
	}
	else if((!L2)&&(!L1)&&(!M)&&R1&&(!R2))
	{
		PWM1_Set(left+5);
	  PWM2_Set(right);
	}
	else if((!L2)&&(!L1)&&(!M)&&(!R1)&&R2)
	{
		PWM1_Set(left+10);
		PWM2_Set(right);
	}
	else
	{
		PWM1_Set(0);
		PWM2_Set(0);
	}
}

void gary_pid(uint8_t speed)
{

	if(L2)
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed*1.4;	
	}
	else if((!L2)&&L1)
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed*1.2;	
	}
	else if((!L2)&&(!L1)&&M)
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed;	
	}
	else if((!L2)&&(!L1)&&(!M)&&R1&&(!R2))
	{
		addPID.target_val = speed*1.2;	
		add2PID.target_val = speed;	
	}
	else if((!L2)&&(!L1)&&(!M)&&(!R1)&&R2)
	{
		addPID.target_val = speed*1.4;	
		add2PID.target_val = speed;	
	}
	else
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed+5;	
	}
}
void gary_pid_rod(uint8_t speed)
{

	if(L2)
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed*1.6;	
	}
	else if((!L2)&&L1)
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed*1.6;	
	}
	else if((!L2)&&(!L1)&&M)
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed*1.4;	
	}
	else if((!L2)&&(!L1)&&(!M)&&R1&&(!R2))
	{
		addPID.target_val = speed*1.4;	
		add2PID.target_val = speed;	
	}
	else if((!L2)&&(!L1)&&(!M)&&(!R1)&&R2)
	{
		addPID.target_val = speed*1.4;	
		add2PID.target_val = speed;	
	}
	else
	{
		addPID.target_val = speed;	
		add2PID.target_val = speed+5;	
	}
}

