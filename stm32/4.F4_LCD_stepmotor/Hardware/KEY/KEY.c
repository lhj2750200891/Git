#include "KEY.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "gpio.h"
#include "stdint.h"
#include "LED.h"
#include "PID.h"

uint8_t key,keyflag;

void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO配置参数存储变量 */
    KEY0_GPIO_CLK_ENABLE();                                     /* KEY0时钟使能 */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1时钟使能 */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2时钟使能 */

    gpio_init_struct.Pin = KEY0_GPIO_PIN;                       /* KEY0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY0_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY1_GPIO_PIN;                       /* KEY1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);           /* KEY1引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY2_GPIO_PIN;                       /* KEY2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &gpio_init_struct);           /* KEY2引脚模式设置,上拉输入 */

}

/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键): WK_UP > KEY2 > KEY1 > KEY0!!
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY0_PRES, 1, KEY0按下
 *              KEY1_PRES, 2, KEY1按下
 *              KEY2_PRES, 3, KEY2按下
 *              WKUP_PRES, 4, WKUP按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        delay_ms(10);           /* 去抖动 */
        key_up = 0;

        if (KEY0 == 0)  keyval = KEY0_PRES;

        if (KEY1 == 0)  keyval = KEY1_PRES;

        if (KEY2 == 0)  keyval = KEY2_PRES;

    }
    else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}

void Key_Control(void)
{
   key = key_scan(0);
   if(key == KEY0_PRES)
   {
			id++;
			if(id>4) id = 1;
      printf("旋转的角度为：%d\r\n",Step_Angle);            
   }
   else if(key == KEY1_PRES)                           /* 按下KEY1开启电机 */
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
   else if(key == KEY2_PRES)                           /* 按下KEY2关闭电机 */
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
}
