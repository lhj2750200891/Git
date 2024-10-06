#ifndef _CONTROL_H
#define _CONTROL_H
#include "./SYSTEM/sys/sys.h"
#include "./BSP/GPIO/gpio.h"
#include "FreeRTOS.h"
 #include "pid.h"  
#include "./BSP/MOTO/moto.h"
#include "oled.h"
#include "./BSP/KEY/key.h"
#include "freertos_demo.h"
#include "./SYSTEM/DELAY/delay.h"
#include "./SYSTEM/USART/usart.h"
#include "./BSP/Software_LCD3.5/lcd.h"
#include "./BSP/GPIO/gpio.h"
#include "./BSP/TIMER/btim.h"
 #include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
/*FreeRTOS*********************************************************************************************/
#include "task.h"
 #include "./BSP/LED/led.h"
 enum mode{
		frees,
		speedpid,
		spd_position,
		yaw_speed,
		fuzzyspd_pid
};
 extern int yaw_set_value , yaw_assisted ;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

void gary(uint8_t left,uint8_t right);
void gary_pid(uint8_t speed);
void gary_pid_rod(uint8_t speed);
extern int left_speed,right_speed;
extern int  globel_position , globel_speed;
extern float pitch, roll,yaw; 			//Å·À­½Ç
#endif
