#include "PID.h"
#include "gpio.h"
#include "TB6612.h"
#include "main.h"
#include "timer.h"
#include "MPU6050.h"

/*定义PID结构体型的全局变量*/
PID addPID;
PID add2PID;
PID PositionPID;
PID Position2PID;
PID yawPID;

/*定义mode结构体型的全局变量*/
mode chosemode;  //模式选择

/*定义yaw结构体型的全局变量*/
Angle yawcontrol;  

/*pid闭环控制所用到的全局变量定义*/
int16_t left_speed=0,right_speed=0;  //脉冲的累计，用于位置环中计步，应用在速度位置双闭环控制中
int16_t speedL=0,speedR=0;//实际速度，由位置式pid的返回值所决定其大小,应用在速度位置双闭环控制中
int16_t Speed_LMax=0,Speed_RMax=0;//用于限幅函数，控制输出速度的最大值
int yaw_out=0,yaw_speedL=0,yaw_speedR=0;  //用于角度速度双闭环控制中
/*
函数功能：PID参数初始化
入口参数：无
返回值：无
说明：通过改变addPID.target_val的值，改变电机的目标速度，通过改变addPID.Kp、addPID.Ki、addPID.Kd改变pid参数
*/
void PID_param_init(void)
{
 /*速度PID的参数（左轮）*/
	addPID.target_val=0;	//目标值
	addPID.output_val=0.0;
	addPID.Error=0.0;
	addPID.LastError=0.0;
	addPID.integral=0.0;

	addPID.Kp = 5;
//	addPID.Kp = 1.1*log10(6.8*abs(addPID.Error)+10);
	addPID.Ki = 0.6;//0.8
	addPID.Kd = 0;

  /*速度PID的参数（右轮）*/
	add2PID.target_val=0;		//目标值
	add2PID.output_val=0.0;
	add2PID.Error=0.0;
	add2PID.LastError=0.0;
	add2PID.integral=0.0;

	add2PID.Kp = 5;
	add2PID.Ki = 0.6;
	add2PID.Kd = 0;

  /*位置PID的参数*/
	PositionPID.target_val=0;				
	PositionPID.output_val=0.0;
	PositionPID.Error=0.0;
	PositionPID.LastError=0.0;
	PositionPID.integral=0.0;

	PositionPID.Kp = 0.3;  
	PositionPID.Ki = 0.0001;
	PositionPID.Kd = 0.18;

	
	Position2PID.target_val=0;				
	Position2PID.output_val=0.0;
	Position2PID.Error=0.0;
	Position2PID.LastError=0.0;
	Position2PID.integral=0.0;

	Position2PID.Kp = 0.6;  
	Position2PID.Ki = 0.0001;
	Position2PID.Kd = 0.18;
	
//陀螺仪参数yaw的PID
	yawPID.target_val=0;				
	yawPID.output_val=0.0;
	yawPID.Error=0.0;
	yawPID.LastError=0.0;
	yawPID.integral=0.0;

	yawPID.Kp = 1.1;  
	yawPID.Ki = 0;
	yawPID.Kd = 0.6;
}

/*
函数功能：速度PID算法实现
入口参数：actual_val:实际值
返回值：无
说明：通过PID计算后的输出
 */
float addPID_realize(PID *pid, float actual_val)
{
	/*计算目标值与实际值的误差*/
	pid->Error = pid->target_val - actual_val;
	

	/*PID算法实现(套公式！！)*/
	pid->output_val += pid->Kp * (pid->Error - pid-> LastError) +
	                  pid->Ki * pid->Error +
	                  pid->Kd *(pid->Error -2*pid->LastError+pid->PrevError);
	/*误差传递*/
	pid-> PrevError = pid->LastError;
	pid-> LastError = pid->Error;

	/*返回当前实际值*/
	return pid->output_val;
}

/*
函数功能：位置PID算法实现
入口参数：actual_val:实际值
返回值：无
说明：通过PID计算后的输出
 */
float PosionPID_realize(PID *pid, float actual_val)
{
	/*计算目标值与实际值的误差*/
	pid->Error = pid->target_val - actual_val;
	
	/*积分项*/
	pid->integral += pid->Error;

	/*PID算法实现*/
	pid->output_val = pid->Kp * pid->Error +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->Error -pid->LastError);
	/*误差传递*/
	pid-> LastError = pid->Error;

	/*返回当前实际值*/
	return pid->output_val;
}

/*
函数功能：增量式pid单环控制
入口参数：无
返回值：无
*/
void speed_pid(void)
{
		left_speed  = addPID_realize(&addPID,EncoderA);
		right_speed = addPID_realize(&add2PID,EncoderB);
		PWMC_Set(left_speed);
		PWMD_Set(right_speed);
}

/*
函数功能：速度位置双闭环pid控制
入口参数：无
返回值：无
*/
void Motor_Control_ClosedLoop(void)
{
	//左轮
	S_EncoderA+=EncoderA;
	speedL=PosionPID_realize(&PositionPID,S_EncoderA);
	speedL=Xianfu(speedL,Speed_LMax);
	addPID.target_val=speedL;
	speedL=addPID_realize(&addPID,EncoderA);
	PWMC_Set(speedL);
	if(myabs(S_EncoderA-PositionPID.target_val)<10)
	{
		addPID.target_val=0;
		speedL=addPID_realize(&addPID,EncoderA);
		PWMC_Set(speedL);
		S_EncoderA=0;
		PositionPID.target_val=0;
		PositionPID.Error=0;
		PositionPID.integral=0;
		PositionPID.LastError=0;
	}
	
	//右轮
	S_EncoderB+=EncoderB;
	speedR=PosionPID_realize(&Position2PID,S_EncoderB);
	speedR=Xianfu(speedR,Speed_RMax);
	add2PID.target_val=speedR;
	speedR=addPID_realize(&add2PID,EncoderB);
	PWMD_Set(speedR);
	if(myabs(S_EncoderB-Position2PID.target_val)<15)
	{
		add2PID.target_val=0;
		speedR=addPID_realize(&add2PID,EncoderB);
		PWMD_Set(speedR);
		S_EncoderB=0;
		Position2PID.target_val=0;
		Position2PID.Error=0;
		Position2PID.integral=0;
		Position2PID.LastError=0;
	}	
}

/*
函数功能：清除PID参数
入口参数：无
返回值：无
*/
void clear(void)
{
	S_EncoderA=0;
	PositionPID.target_val=0;
	PositionPID.Error=0.0;
	PositionPID.LastError=0.0;
	PositionPID.integral=0.0;
	S_EncoderB=0;
	Position2PID.target_val=0;
	Position2PID.Error=0.0;
	Position2PID.LastError=0.0;
	Position2PID.integral=0.0;
}

/*
函数功能：速度角度双闭环pid控制
入口参数：无
返回值：无
*/
int yawspd_set=20,Xans_speed=15;

void Speed_Angle_ClosedLoop(void)
{
	yaw_out = PosionPID_realize(&yawPID,yaw);
	yaw_out = Xianfu(yaw_out,Xans_speed);
	if(yawspd_set>0 && yawspd_set<=Xans_speed) yawspd_set=Xans_speed;
	else if(yawspd_set<0 && yawspd_set>-Xans_speed) yawspd_set=-Xans_speed;
	addPID.target_val=yawspd_set-yaw_out;
	add2PID.target_val=yawspd_set+yaw_out;
	yaw_speedL=addPID_realize(&addPID,EncoderA);
	yaw_speedR=addPID_realize(&add2PID,EncoderB);
	PWMC_Set(yaw_speedL);
	PWMD_Set(yaw_speedR);
}

/*
函数功能：速度位置双闭环pid，执行体参数
入口参数：speedL/speedR闭环速度，circleL/circleR闭环位置（脉冲和）
返回值：无
*/
void Motor_ClosedLoop_Step(int speedL,int speedR,float circleL,float circleR)
{
	Speed_LMax=speedL,Speed_RMax=speedR,PositionPID.target_val=1560*circleL*1.00f,Position2PID.target_val=1560*circleR*1.00f;
	while(1)
	{
		if(myabs(S_EncoderB-Position2PID.target_val)<15)
		{
			clear ();
			break;
		}
	}
}
