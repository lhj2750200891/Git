#include "main.h"

void GPIO_Init(void)
{
	LED_Init();
}


/*
函数功能：各GPIO引脚的初始化
入口参数：无
返回值：无
*/
void LED_Init(void)
{
	LED0(1);
	LED1(1);
	LED2(1);
}
