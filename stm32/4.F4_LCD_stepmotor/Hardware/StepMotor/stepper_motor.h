#ifndef __STEPPER_MOTOR_H
#define __STEPPER_MOTOR_H

#include "sys.h"

/* �������������غ� */
#define PULSE_REV       6400.0               /* ÿȦ��������ϸ����32�� */
#define MAX_STEP_ANGLE  0.05625              /* ����/ϸ���� */

typedef struct
{
    int angle ;                             /* ������Ҫ��ת�ĽǶ� */
    uint8_t dir;                            /* ���� */
    uint8_t en;                             /* ʹ�� */
    volatile uint32_t pulse_count;          /* ���������¼ */
    volatile int add_pulse_count;           /* ��������ۼ� */  
} STEPPER_MOTOR;

enum dir
{
    CCW = 0,                                /* ��ʱ����ת */
    CW =1,                                    /* ˳ʱ����ת */
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
/* ����������Ŷ���*/

#define STEPPER_MOTOR_1       1              /* ��������ӿ���� */
#define STEPPER_MOTOR_2       2
#define STEPPER_MOTOR_3       3
#define STEPPER_MOTOR_4       4
/*     ��������������Ŷ���     */

#define STEPPER_DIR1_GPIO_PIN                  GPIO_PIN_0
#define STEPPER_DIR1_GPIO_PORT                 GPIOG
#define STEPPER_DIR1_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PF��ʱ��ʹ�� */
#define STEPPER_DIR1_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PF��ʱ��ʹ�� */

#define STEPPER_DIR2_GPIO_PIN                  GPIO_PIN_1
#define STEPPER_DIR2_GPIO_PORT                 GPIOG
#define STEPPER_DIR2_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PF��ʱ��ʹ�� */
#define STEPPER_DIR2_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PF��ʱ��ʹ�� */

#define STEPPER_DIR3_GPIO_PIN                  GPIO_PIN_2
#define STEPPER_DIR3_GPIO_PORT                 GPIOG
#define STEPPER_DIR3_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PB��ʱ��ʹ�� */
#define STEPPER_DIR3_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PB��ʱ��ʹ�� */

#define STEPPER_DIR4_GPIO_PIN                  GPIO_PIN_3
#define STEPPER_DIR4_GPIO_PORT                 GPIOG
#define STEPPER_DIR4_GPIO_CLK_ENABLE()         do{  __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)    /* PH��ʱ��ʹ�� */
#define STEPPER_DIR4_GPIO_CLK_DISABLE()         do{  __HAL_RCC_GPIOG_CLK_DISABLE(); }while(0)    /* PH��ʱ��ʹ�� */

/*----------------------- �������ſ��� -----------------------------------*/
/* ��������ʹ�õ��ǹ������ⷨ,����Ӳ���Ե�ƽ����ȡ�����������Ե� x = 1��Ч��x = 0ʱ��Ч*/  
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
/* �ⲿ�ӿں���*/
void stepper_init(uint16_t arr, uint16_t psc);              /* ��������ӿڳ�ʼ�� */
void stepper_star(uint8_t motor_num,uint8_t dir);                       /* ����������� */
void stepper_stop(uint8_t motor_num);                       /* �رղ������ */   
void Set_Stepper_Speed(double ARR);
void stepper_pwmt_speed(uint16_t speed,uint32_t Channel);			
void Step_Motor_SetAngle(uint16_t angle, uint8_t dir,uint8_t motor_num);													
#endif
