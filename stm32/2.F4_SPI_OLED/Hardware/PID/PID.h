#ifndef __PID_H
#define __PID_H

#include "stdint.h"

#define speedpid 1
#define spd_position 2
#define yaw_speed 3
#define free 4

typedef struct
{
	float target_val;   //目标值
	float Error;          /*第 k 次偏差 */
	float LastError;     /* Error[-1],第 k-1 次偏差 */
	float PrevError;    /* Error[-2],第 k-2 次偏差 */
	float Kp,Ki,Kd;     //比例、积分、微分系数
	float integral;     //积分值
	float output_val;   //输出值
}PID;	  //PID结构体成员-->参数

typedef struct
{
	int pidmode;
	
}mode;  //PID结构体成员-->工作模式

typedef struct
{
	int direction;
	int speed;
}Angle;   //关于yaw的结构体成员-->角度yaw

extern PID addPID;
extern PID add2PID;
extern PID PositionPID;
extern PID Position2PID;
extern PID yawPID;
extern mode chosemode;
extern Angle yawcontrol;  

extern int16_t left_speed,right_speed;//速度pid计算后的结果
extern int16_t speedL,speedR;//实际速度，由位置式pid的返回值所决定其大小,应用在速度位置双闭环控制中
extern int16_t Speed_LMax,Speed_RMax;//用于限幅函数，控制输出速度的最大值
extern int yaw_out,yaw_speedL,yaw_speedR;
void PID_param_init(void);
float addPID_realize(PID *pid, float actual_val);
float PosionPID_realize(PID *pid, float actual_val);
void speed_pid(void);
void Motor_Control_ClosedLoop(void);
void clear(void);
void Speed_Angle_ClosedLoop(void);//速度角度双闭环控制
void Motor_ClosedLoop_Step(int speedL,int speedR,float circleL,float circleR); //速度位置双闭环控制
#endif
