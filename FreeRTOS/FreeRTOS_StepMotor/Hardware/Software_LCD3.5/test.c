#include "main.h"
#include "pic.h"

//========================variable==========================//
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//������ɫ����
//=====================end of variable======================//
/*
��ڲ�������
�������ܣ�����LCD��ʾ����ľ�̬��
����ֵ����
*/
void LCD_Static_Show(void)
{
	LCD_ShowString(0,0,16,"Time: (s)",1);
	LCD_ShowString(0,25,16,"Voltage: (V)",1);
	LCD_ShowString(0,45,16,"yaw: (degree)",1);
	
	LCD_DrawLine(240,0,240,320);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,160,480,160);   //���߷ָ�Ϊ����������
	//���Ʊ��
	LCD_DrawLine(360,0,360,160);   //���߷ָ�Ϊ����������
	LCD_DrawLine(120,0,120,160);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,22,480,22);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,42,480,42);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,62,480,62);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,82,480,82);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,102,480,102);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,122,480,122);   //���߷ָ�Ϊ����������
	LCD_DrawLine(0,142,480,142);   //���߷ָ�Ϊ����������
	
	//ͼƬ��ʾ
	Gui_Drawbmp16(25,240,gImage_qq);
}

/*
��ڲ�������
�������ܣ�����LCD��ʾ�仯�Ķ�̬��
����ֵ����
*/
void LCD_Dynamic_Show(void)
{
	LCD_ShowNum(125,0,Time,3,16);  //��������
	LCD_ShowFloat(125,25,ADC_Vol,2,2,16);
	LCD_ShowFloat(125,45,HWT101_yaw,3,2,16);
	
}

