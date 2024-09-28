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
	Show_Str(245,0,BLUE,YELLOW,"Time: ",16,1);
	LCD_ShowString(0,25,16,"Voltage: (V)",1);
	LCD_ShowString(0,45,16,"yaw: (degree)",1);
	LCD_ShowString(0,65,16,"pitch: (degree)",1);
	LCD_ShowString(0,85,16,"roll: (degree)",1);
	
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
//	LCD_ShowNum(105,20,ADC_Vol,1,16);  //��������
//	LCD_ShowNum(80,20,ADC_Vol2,2,16); //С������
	LCD_ShowFloat(125,45,yaw,3,1,16);
	LCD_ShowFloat(125,65,pitch,3,1,16);
	LCD_ShowFloat(125,85,roll,3,1,16);
	
}
/*****************************************************************************
 * @name       :void main_test(void)
 * @date       :2018-08-09 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void main_test(void)
{
	Gui_StrCenter(0,30,RED,BLUE,"ȫ������",16,1);//������ʾ
	Gui_StrCenter(0,60,RED,BLUE,"�ۺϲ��Գ���",16,1);//������ʾ	
	Gui_StrCenter(0,90,GREEN,BLUE,"3.5\" ILI9488 320X480",16,1);//������ʾ
	Gui_StrCenter(0,120,BLUE,BLUE,"xiaoFeng@QDtech 2018-08-06",16,1);//������ʾ
	delay_ms(1500);		
	delay_ms(1500);
}



/*****************************************************************************
 * @name       :void Chinese_Font_test(void)
 * @date       :2018-08-09 
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Chinese_Font_test(void)
{	
	Show_Str(10,30,BLUE,YELLOW,"16X16:ȫ�����Ӽ������޹�˾��ӭ��",16,0);
	Show_Str(10,50,BLUE,YELLOW,"16X16:Welcomeȫ������",16,0);
	Show_Str(10,70,BLUE,YELLOW,"24X24:���������Ĳ���",24,1);
	Show_Str(10,100,BLUE,YELLOW,"32X32:�������",32,1);
	delay_ms(1200);
}

void Touch_Test(void)
{
//	u8 key;
//	u16 i=0;
//	u16 j=0;
//	u16 colorTemp=0;
//	TP_Init();
//	KEY_Init();
//	LED_Init();
//	DrawTestPage("����9:Touch����(��KEY0��У׼)  ");
//	LCD_ShowString(lcddev.width-24,0,16,"RST",1);//��ʾ��������
//	POINT_COLOR=RED;
//	LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,RED); 
//		while(1)
//	{
//	 	key=KEY_Scan(1);
//		tp_dev.scan(0); 		 
//		if(tp_dev.sta&TP_PRES_DOWN)			//������������
//		{	
//		 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
//			{	
//				if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)
//				{
//					DrawTestPage("����9:Touch����(��KEY0��У׼)  ");//���
//					LCD_ShowString(lcddev.width-24,0,16,"RST",1);//��ʾ��������
//					POINT_COLOR=colorTemp;
//					LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,POINT_COLOR); 
//				}
//				else if((tp_dev.x>(lcddev.width-60)&&tp_dev.x<(lcddev.width-50+20))&&tp_dev.y<20)
//				{
//				LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,ColorTab[j%5]); 
//				POINT_COLOR=ColorTab[(j++)%5];
//				colorTemp=POINT_COLOR;
//				delay_ms(10);
//				}

//				else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,POINT_COLOR);		//��ͼ	  			   
//			}
//		}else delay_ms(10);	//û�а������µ�ʱ�� 	    
//		if(key==1)	//KEY_RIGHT����,��ִ��У׼����
//		{

//			LCD_Clear(WHITE);//����
//		    TP_Adjust();  //��ĻУ׼ 
//			TP_Save_Adjdata();	 
//			DrawTestPage("����9:Touch����(��KEY0��У׼)  ");
//			LCD_ShowString(lcddev.width-24,0,16,"RST",1);//��ʾ��������
//			POINT_COLOR=colorTemp;
//			LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,POINT_COLOR); 
//		}
//		i++;
//		if(i==30)
//		{
//			i=0;
//			LED0=!LED0;
//			//break;
//		}
//	}   
}



