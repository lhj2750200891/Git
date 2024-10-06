#include "pic.h"
#include "spi.h"
#include "lcd.h"
#include "gui.h"
#include "test.h"
#include "./SYSTEM/sys/sys.h"
#include "./BSP/HWT101/HWT101.h"
#include "./SYSTEM/usart/usart.h"

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
	GUI_DrawFont32(180, 200, BLACK, WHITE, "��",1);  //�Ӻţ�λ�ò���
	
	LCD_DrawLine(240,0,240,160);   //���߷ָ�Ϊ����������
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
//	Gui_Drawbmp16(25,240,gImage_qq);
	K210_Number_Show();   //k210���յ�������ʾ����

}

/*
��ڲ�������
�������ܣ�����LCD��ʾ�仯�Ķ�̬��
����ֵ����
*/
void LCD_Dynamic_Show(void)
{
//	LCD_ShowNum(125,0,Time,3,16);  //��������
//	//LCD_ShowFloat(125,25,ADC_Vol,2,2,16);
	LCD_ShowFloat(125,45,HWT101_yaw,3,2,16);	
	//LCD_ShowFloat(125,45,ANGLE,3,2,16);	
}

int k210_num=0;
void K210_Number_Show(void)
{
	switch(k210_num)
	{
		case 0: LCD_Number123_Show(); LCD_NumberShow_123();break;
		case 1: LCD_Number123_Show(); LCD_NumberShow_321();break;
	}
}


void LCD_Number123_Show(void)
{
	GUI_DrawFont32(0, 200, BLACK, WHITE, "һ",1);
  GUI_DrawFont32(60, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(120, 200, BLACK, WHITE, "��",1);
}

void LCD_Number132_Show(void)
{
	GUI_DrawFont32(0, 200, BLACK, WHITE, "һ",1);
  GUI_DrawFont32(60, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(120, 200, BLACK, WHITE, "��",1);
}
void LCD_Number213_Show(void)
{
	GUI_DrawFont32(0, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(60, 200, BLACK, WHITE, "һ",1);
	GUI_DrawFont32(120, 200, BLACK, WHITE, "��",1);
}

void LCD_Number231_Show(void)
{
	GUI_DrawFont32(0, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(60, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(120, 200, BLACK, WHITE, "һ",1);
}
void LCD_Number312_Show(void)
{
	GUI_DrawFont32(0, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(60, 200, BLACK, WHITE, "һ",1);
	GUI_DrawFont32(120, 200, BLACK, WHITE, "��",1);
}

void LCD_Number321_Show(void)
{
	GUI_DrawFont32(0, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(60, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(120, 200, BLACK, WHITE, "һ",1);
}

void LCD_NumberShow_123(void)
{
	GUI_DrawFont32(240, 200, BLACK, WHITE, "һ",1);
  GUI_DrawFont32(300, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(360, 200, BLACK, WHITE, "��",1);
}

void LCD_NumberShow_132(void)
{
	GUI_DrawFont32(240, 200, BLACK, WHITE, "һ",1);
  GUI_DrawFont32(300, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(360, 200, BLACK, WHITE, "��",1);
}
void LCD_NumberShow_213(void)
{
	GUI_DrawFont32(240, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(300, 200, BLACK, WHITE, "һ",1);
	GUI_DrawFont32(360, 200, BLACK, WHITE, "��",1);
}

void LCD_NumberShow_231(void)
{
	GUI_DrawFont32(240, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(300, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(360, 200, BLACK, WHITE, "һ",1);
}
void LCD_NumberShow_312(void)
{
	GUI_DrawFont32(240, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(300, 200, BLACK, WHITE, "һ",1);
	GUI_DrawFont32(360, 200, BLACK, WHITE, "��",1);
}

void LCD_NumberShow_321(void)
{
	GUI_DrawFont32(240, 200, BLACK, WHITE, "��",1);
  GUI_DrawFont32(300, 200, BLACK, WHITE, "��",1);
	GUI_DrawFont32(360, 200, BLACK, WHITE, "һ",1);
}
