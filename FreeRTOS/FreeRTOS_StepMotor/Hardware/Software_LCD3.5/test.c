#include "main.h"
#include "pic.h"

//========================variable==========================//
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//定义颜色数组
//=====================end of variable======================//
/*
入口参数：无
函数功能：驱动LCD显示不变的静态量
返回值：无
*/
void LCD_Static_Show(void)
{
	LCD_ShowString(0,0,16,"Time: (s)",1);
	LCD_ShowString(0,25,16,"Voltage: (V)",1);
	LCD_ShowString(0,45,16,"yaw: (degree)",1);
	
	LCD_DrawLine(240,0,240,320);   //划线分割为左右两部分
	LCD_DrawLine(0,160,480,160);   //划线分割为上下两部分
	//绘制表格
	LCD_DrawLine(360,0,360,160);   //划线分割为左右两部分
	LCD_DrawLine(120,0,120,160);   //划线分割为左右两部分
	LCD_DrawLine(0,22,480,22);   //划线分割为上下两部分
	LCD_DrawLine(0,42,480,42);   //划线分割为上下两部分
	LCD_DrawLine(0,62,480,62);   //划线分割为上下两部分
	LCD_DrawLine(0,82,480,82);   //划线分割为上下两部分
	LCD_DrawLine(0,102,480,102);   //划线分割为上下两部分
	LCD_DrawLine(0,122,480,122);   //划线分割为上下两部分
	LCD_DrawLine(0,142,480,142);   //划线分割为上下两部分
	
	//图片显示
	Gui_Drawbmp16(25,240,gImage_qq);
}

/*
入口参数：无
函数功能：驱动LCD显示变化的动态量
返回值：无
*/
void LCD_Dynamic_Show(void)
{
	LCD_ShowNum(125,0,Time,3,16);  //整数部分
	LCD_ShowFloat(125,25,ADC_Vol,2,2,16);
	LCD_ShowFloat(125,45,HWT101_yaw,3,2,16);
	
}

