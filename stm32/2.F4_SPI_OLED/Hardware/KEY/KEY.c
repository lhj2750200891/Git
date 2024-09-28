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
	if(KeyNum==1)
	{
		keyflag=1;
		KeyNum=0;
		LED0(1);
		LED1(1);
		LED2(0);
	}
	
	if(KeyNum==2)
	{
		keyflag=2;
		KeyNum=0;
		LED0(0);
		LED1(1);
		LED2(1);
	}
	
	if(KeyNum==3)
	{
		keyflag=3;
		KeyNum=0;
		Motor_ClosedLoop_Step(10,10,3,3);
	}	
}
