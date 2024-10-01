#ifndef __HWT101_H
#define __HWT101_H

#include <stdint.h>

extern float fAngle[3];
extern float HWT101_yaw;

void HWT101_Init(void);
void CopeCmdData(unsigned char ucData);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
static void AutoScanSensor(void);
void HWT101_GetData(void);
									
#endif
