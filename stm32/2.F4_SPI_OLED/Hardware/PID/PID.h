#ifndef __PID_H
#define __PID_H

#include "stdint.h"

#define speedpid 1
#define spd_position 2
#define yaw_speed 3
#define free 4

typedef struct
{
	float target_val;   //Ŀ��ֵ
	float Error;          /*�� k ��ƫ�� */
	float LastError;     /* Error[-1],�� k-1 ��ƫ�� */
	float PrevError;    /* Error[-2],�� k-2 ��ƫ�� */
	float Kp,Ki,Kd;     //���������֡�΢��ϵ��
	float integral;     //����ֵ
	float output_val;   //���ֵ
}PID;	  //PID�ṹ���Ա-->����

typedef struct
{
	int pidmode;
	
}mode;  //PID�ṹ���Ա-->����ģʽ

typedef struct
{
	int direction;
	int speed;
}Angle;   //����yaw�Ľṹ���Ա-->�Ƕ�yaw

extern PID addPID;
extern PID add2PID;
extern PID PositionPID;
extern PID Position2PID;
extern PID yawPID;
extern mode chosemode;
extern Angle yawcontrol;  

extern int16_t left_speed,right_speed;//�ٶ�pid�����Ľ��
extern int16_t speedL,speedR;//ʵ���ٶȣ���λ��ʽpid�ķ���ֵ���������С,Ӧ�����ٶ�λ��˫�ջ�������
extern int16_t Speed_LMax,Speed_RMax;//�����޷���������������ٶȵ����ֵ
extern int yaw_out,yaw_speedL,yaw_speedR;
void PID_param_init(void);
float addPID_realize(PID *pid, float actual_val);
float PosionPID_realize(PID *pid, float actual_val);
void speed_pid(void);
void Motor_Control_ClosedLoop(void);
void clear(void);
void Speed_Angle_ClosedLoop(void);//�ٶȽǶ�˫�ջ�����
void Motor_ClosedLoop_Step(int speedL,int speedR,float circleL,float circleR); //�ٶ�λ��˫�ջ�����
#endif
