#include <string.h>
#include <stdio.h>
#include "wit_c_sdk.h"
#include "HWT101.h"
#include "./SYSTEM/usart/usart.h"

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80

static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
static void AutoScanSensor(void);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
float fAngle[3];
float HWT101_yaw=0;
    
void HWT101_Init(void)
{
	WitRegisterCallBack(SensorDataUpdata);
	AutoScanSensor();
}

void CopeCmdData(unsigned char ucData)
{
	 static unsigned char s_ucData[50], s_ucRxCnt = 0;
	
	 s_ucData[s_ucRxCnt++] = ucData;
	 if(s_ucRxCnt<3)return;										//Less than three data returned
	 if(s_ucRxCnt >= 50) s_ucRxCnt = 0;
	 if(s_ucRxCnt >= 3)
	 {
		 if((s_ucData[1] == '\r') && (s_ucData[2] == '\n'))
		 {
		  	s_cCmd = s_ucData[0];
			  memset(s_ucData,0,50);//
			  s_ucRxCnt = 0;
	   } 
		 else 
		 {
			 s_ucData[0] = s_ucData[1];
			 s_ucData[1] = s_ucData[2];
			 s_ucRxCnt = 2;
			}
	  }
}




static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
		int i;
    for(i = 0; i < uiRegNum; i++)
    {
				s_cDataUpdate |= ANGLE_UPDATE;
				uiReg++;
    }
}

static void AutoScanSensor(void)
{
	int i, iRetry;
	
	for(i = 1; i < 10; i++)
	{
		//MX_USART2_UART_Init();
		usart2_init(115200);
		iRetry = 2;
		do
		{
			s_cDataUpdate = 0;
			WitReadReg(AX, 3);
			HAL_Delay(100);
			if(s_cDataUpdate != 0)
			{
				printf("%d baud find sensor\r\n\r\n", 115200);
				return ;
			}
			iRetry--;
		}while(iRetry);		
	}
	printf("can not find sensor\r\n");
	printf("please check your connection\r\n");
}

void HWT101_GetData(void)
{
		if(s_cDataUpdate)
		{
			   for(int i = 0; i < 3; i++)
			   {
			   	  fAngle[i] = sReg[Roll+i] / 32768.0f * 180.0f;
			   }
			   if(s_cDataUpdate & ANGLE_UPDATE)
			   {
					 HWT101_yaw=fAngle[2];
			   	 s_cDataUpdate &= ~ANGLE_UPDATE;
			   }
		}
}

