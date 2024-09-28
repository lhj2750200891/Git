#ifndef __STEPPER_MOTOR_H
#define __STEPPER_MOTOR_H

#include "sys.h"

/* 步进电机参数相关宏 */
#define PULSE_REV       6400.0               /* 每圈脉冲数（细分数32） */
#define MAX_STEP_ANGLE  0.05625              /* 步距/细分数 */

typedef struct
{
    int angle ;                             /* 设置需要旋转的角度 */
    uint8_t dir;                            /* 方向 */
    uint8_t en;                             /* 使能 */
    volatile uint32_t pulse_count;          /* 脉冲个数记录 */
    volatile int add_pulse_count;           /* 脉冲个数累计 */  
} STEPPER_MOTOR;

enum dir
{
    CCW = 0,                                /* 逆时针旋转 */
    CW =1,                                    /* 顺时针旋转 */
};  

typedef struct
{
    uint32_t StepMotor1;  
		uint32_t StepMotor2; 
		uint32_t StepMotor3; 
		uint32_t StepMotor4; 
 
} Step_Pulse_Add;

extern STEPPER_MOTOR g_stepper;
extern int Step_Angle,StepMotor_Num;
extern Step_Pulse_Add Pulse_Add;
/******************************************************************************************/
/* 步进电机引脚定义*/

#define STEPPER_MOTOR_1       1              /* 步进电机接口序号 */
#define STEPPER_MOTOR_2       2
#define STEPPER_MOTOR_3       3
#define STEPPER_MOTOR_4       4
/*     步进电机方向引脚定义     */

#define STEPPER_DIR1_GPIO_PIN                  GPIO_PIN_0
#define STEPPER_DIR1_GPIO_PORT                 GPIOG
#define STEPPER_DIR1_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PF口时钟使能 */
#define STEPPER_DIR1_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PF口时钟使能 */

#define STEPPER_DIR2_GPIO_PIN                  GPIO_PIN_1
#define STEPPER_DIR2_GPIO_PORT                 GPIOG
#define STEPPER_DIR2_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PF口时钟使能 */
#define STEPPER_DIR2_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PF口时钟使能 */

#define STEPPER_DIR3_GPIO_PIN                  GPIO_PIN_2
#define STEPPER_DIR3_GPIO_PORT                 GPIOG
#define STEPPER_DIR3_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PB口时钟使能 */
#define STEPPER_DIR3_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PB口时钟使能 */

#define STEPPER_DIR4_GPIO_PIN                  GPIO_PIN_3
#define STEPPER_DIR4_GPIO_PORT                 GPIOG
#define STEPPER_DIR4_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PH口时钟使能 */
#define STEPPER_DIR4_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PH口时钟使能 */

/*----------------------- 方向引脚控制 -----------------------------------*/
/* 由于我们使用的是共阳极解法,并且硬件对电平做了取反操作，所以当 x = 1有效，x = 0时无效*/  
#define ST1_DIR(x)    do{ x ? \
                              HAL_GPIO_WritePin(STEPPER_DIR1_GPIO_PORT, STEPPER_DIR1_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(STEPPER_DIR1_GPIO_PORT, STEPPER_DIR1_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)  

#define ST2_DIR(x)    do{ x ? \
                              HAL_GPIO_WritePin(STEPPER_DIR2_GPIO_PORT, STEPPER_DIR2_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(STEPPER_DIR2_GPIO_PORT, STEPPER_DIR2_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)  

#define ST3_DIR(x)    do{ x ? \
                              HAL_GPIO_WritePin(STEPPER_DIR3_GPIO_PORT, STEPPER_DIR3_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(STEPPER_DIR3_GPIO_PORT, STEPPER_DIR3_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)  

#define ST4_DIR(x)    do{ x ? \
                              HAL_GPIO_WritePin(STEPPER_DIR4_GPIO_PORT, STEPPER_DIR4_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(STEPPER_DIR4_GPIO_PORT, STEPPER_DIR4_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)  
                        

/******************************************************************************************/
void StepMotor_STOP(void);
/* 外部接口函数*/
void stepper_init(uint16_t arr, uint16_t psc);              /* 步进电机接口初始化 */
void stepper_star(uint8_t motor_num,uint8_t dir);                       /* 开启步进电机 */
void stepper_stop(uint8_t motor_num);                       /* 关闭步进电机 */   
void Set_Stepper_Speed(double ARR);
void stepper_pwmt_speed(uint16_t speed,uint32_t Channel);			
void Step_Motor_SetAngle(uint16_t angle, uint8_t dir,uint8_t motor_num);													
#endif
