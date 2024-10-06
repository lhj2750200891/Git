#ifndef __PID_H
#define __PID_H
#include "./SYSTEM/sys/sys.h"
#include "control.h"
typedef struct
{
	float target_val;   //目标值
	float Error;          /*第 k 次偏差 */
	float LastError;     /* Error[-1],第 k-1 次偏差 */
	float PrevError;    /* Error[-2],第 k-2 次偏差 */
	float Kp,Ki,Kd;     //比例、积分、微分系数
	float integral;     //积分值
	float output_val;   //输出值
}PID;
extern int16_t Encoder1,Encoder2;
extern PID addPID;
extern PID add2PID;
extern PID PosionPID;
extern PID Posion2PID;
extern int16_t Position ;
extern int16_t Speed;//实际速度
void  PID_param_init(void);
void  set_PID_target(float temp_val);
float get_pid_target(PID *pid);
void  set_PID(float p, float i, float d);
float addPID_realize(PID *pid, float actual_val);
float PosionPID_realize(PID *pid, float actual_val);
void MotorControl(void);
void speed_pid(void);
void yawspeed(void);
extern int SUM;
extern int16_t SpeedFL,SpeedFR;//实际速度
extern int Pos_FL,Pos_FR;
extern int  Lmax_speed,Rmax_speed;;
extern int16_t Speed;
typedef struct {
		int direction;
		int speed;
}yawctrl;
int Xianfu(int data,int max);
int16_t myabs(int a);
extern enum mode pidmode;
//extern mode chosemode;
int16_t myabs(int a);
void clear_piderr(void);
extern yawctrl yawcontrol ;
float yaw_output(void);
void add_pid_normal(int tar1,int tar2,int tar3,int tar4);
#endif

