#include "LED.h"
#include "gpio.h"
#include "KEY.h"

void GPIO_Init(void)
{
	LED_Init();
}


/*
�������ܣ���GPIO���ŵĳ�ʼ��
��ڲ�������
����ֵ����
*/
void LED_Init(void)
{
	LED0(1);
	LED1(1);
	LED2(1);
}
