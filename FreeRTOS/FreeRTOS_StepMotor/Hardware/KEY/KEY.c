#include "KEY.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "gpio.h"
#include "stdint.h"
#include "LED.h"
#include "PID.h"

int KeyNum=0;
int keyflag=0;
uint8_t key_scan(uint8_t mode)
{
   static uint8_t key_up = 1;  /* 鏉炬墜鏍囧織*/
   uint8_t keyval = 0;
	 if (mode) key_up = 1;       /* 妯″紡閫夋嫨锛宮ode=1锛屾敮鎸佽繛鎸夛紝涓嶆澗鎵嬬殑鎯呭喌涓嬩竴鐩存墽琛屾寜閿悗鐨勬寚浠?*/

   if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0))  /* 掳麓录眉藟驴陋卤陽疚?1, 菕訍葞尧一赂枚掳麓录眉掳麓蟼脕藸*/
   {
     HAL_Delay(10);           /* 娑堟姈 */
     key_up = 0;

     if (KEY0 == 0)  keyval = 1;

     if (KEY1 == 0)  keyval = 2;

     if (KEY2 == 0)  keyval = 3;
   }
   else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1)         /*鏉炬墜妫?娴? */
   {
     key_up = 1;
   }

   return keyval;              /* 路碌禄丶眉值 */
}

void Key_Control(void)
{
	KeyNum = key_scan(0);
   if(KeyNum == 1)
   {
			id++;
			if(id>4) id = 1;
		 printf("步进电机ID：%d\r\n",id);            
   }
   else if(KeyNum == 2)                           /* 按下KEY1开启电机 */
   {
		 keyflag=2;
     if(Step_Run_Flag == 0)
     {
       Step_Angle = 45;
       g_stepper.angle = Step_Angle;
       g_stepper.dir = CW;
       printf("旋转的角度为：%d\r\n",Step_Angle); 
		 }   
   }
   else if(KeyNum == 3)                           /* 按下KEY2关闭电机 */
   {
		 keyflag=3;
     if(Step_Run_Flag == 0 && id == 1)
     {
       Step_Angle = 0;                                  /* 角度清0，以便下次设置 */
       Step_Motor_SetAngle(g_stepper.angle, g_stepper.dir, STEPPER_MOTOR_1); /* 开启旋转 */
       printf("开启旋转\r\n");
     } 
     else if(Step_Run_Flag == 0 && id == 2)
     {
       Step_Angle = 0;                                  /* 角度清0，以便下次设置 */
       Step_Motor_SetAngle(g_stepper.angle, g_stepper.dir, STEPPER_MOTOR_2); /* 开启旋转 */
       printf("开启旋转\r\n");
     } 
     else if(Step_Run_Flag == 0 && id == 3)
     {
       Step_Angle = 0;                                  /* 角度清0，以便下次设置 */
       Step_Motor_SetAngle(g_stepper.angle, g_stepper.dir, STEPPER_MOTOR_3); /* 开启旋转 */
       printf("开启旋转\r\n");
     }
     else if(Step_Run_Flag == 0 && id == 4)
     {
       Step_Angle = 0;                                  /* 角度清0，以便下次设置 */
       Step_Motor_SetAngle(g_stepper.angle, g_stepper.dir, STEPPER_MOTOR_4); /* 开启旋转 */
       printf("开启旋转\r\n");
     }
   }
//	if(KeyNum==1)
//	{
//		keyflag=1;
//		KeyNum=0;
//		LED0(1);
//		LED1(1);
//		LED2(0);
//	}
//	
//	if(KeyNum==2)
//	{
//		keyflag=2;
//		KeyNum=0;
//		LED0(0);
//		LED1(1);
//		LED2(1);
//	}
//	
//	if(KeyNum==3)
//	{
//		keyflag=3;
//		KeyNum=0;
//		Motor_ClosedLoop_Step(10,10,3,6);
//	}	
}
