#include "PID.h"
#include "gpio.h"
#include "TB6612.h"
#include "main.h"
#include "timer.h"
#include "MPU6050.h"

/*����PID�ṹ���͵�ȫ�ֱ���*/
PID addPID;
PID add2PID;
PID PositionPID;
PID Position2PID;
PID yawPID;

/*����mode�ṹ���͵�ȫ�ֱ���*/
mode chosemode;  //ģʽѡ��

/*����yaw�ṹ���͵�ȫ�ֱ���*/
Angle yawcontrol;  

/*pid�ջ��������õ���ȫ�ֱ�������*/
int16_t left_speed=0,right_speed=0;  //������ۼƣ�����λ�û��мƲ���Ӧ�����ٶ�λ��˫�ջ�������
int16_t speedL=0,speedR=0;//ʵ���ٶȣ���λ��ʽpid�ķ���ֵ���������С,Ӧ�����ٶ�λ��˫�ջ�������
int16_t Speed_LMax=0,Speed_RMax=0;//�����޷���������������ٶȵ����ֵ
int yaw_out=0,yaw_speedL=0,yaw_speedR=0;  //���ڽǶ��ٶ�˫�ջ�������
/*
�������ܣ�PID������ʼ��
��ڲ�������
����ֵ����
˵����ͨ���ı�addPID.target_val��ֵ���ı�����Ŀ���ٶȣ�ͨ���ı�addPID.Kp��addPID.Ki��addPID.Kd�ı�pid����
*/
void PID_param_init(void)
{
 /*�ٶ�PID�Ĳ��������֣�*/
	addPID.target_val=0;	//Ŀ��ֵ
	addPID.output_val=0.0;
	addPID.Error=0.0;
	addPID.LastError=0.0;
	addPID.integral=0.0;

	addPID.Kp = 5;
//	addPID.Kp = 1.1*log10(6.8*abs(addPID.Error)+10);
	addPID.Ki = 0.6;//0.8
	addPID.Kd = 0;

  /*�ٶ�PID�Ĳ��������֣�*/
	add2PID.target_val=0;		//Ŀ��ֵ
	add2PID.output_val=0.0;
	add2PID.Error=0.0;
	add2PID.LastError=0.0;
	add2PID.integral=0.0;

	add2PID.Kp = 5;
	add2PID.Ki = 0.6;
	add2PID.Kd = 0;

  /*λ��PID�Ĳ���*/
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
	
//�����ǲ���yaw��PID
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
�������ܣ��ٶ�PID�㷨ʵ��
��ڲ�����actual_val:ʵ��ֵ
����ֵ����
˵����ͨ��PID���������
 */
float addPID_realize(PID *pid, float actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	pid->Error = pid->target_val - actual_val;
	

	/*PID�㷨ʵ��(�׹�ʽ����)*/
	pid->output_val += pid->Kp * (pid->Error - pid-> LastError) +
	                  pid->Ki * pid->Error +
	                  pid->Kd *(pid->Error -2*pid->LastError+pid->PrevError);
	/*����*/
	pid-> PrevError = pid->LastError;
	pid-> LastError = pid->Error;

	/*���ص�ǰʵ��ֵ*/
	return pid->output_val;
}

/*
�������ܣ�λ��PID�㷨ʵ��
��ڲ�����actual_val:ʵ��ֵ
����ֵ����
˵����ͨ��PID���������
 */
float PosionPID_realize(PID *pid, float actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	pid->Error = pid->target_val - actual_val;
	
	/*������*/
	pid->integral += pid->Error;

	/*PID�㷨ʵ��*/
	pid->output_val = pid->Kp * pid->Error +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->Error -pid->LastError);
	/*����*/
	pid-> LastError = pid->Error;

	/*���ص�ǰʵ��ֵ*/
	return pid->output_val;
}

/*
�������ܣ�����ʽpid��������
��ڲ�������
����ֵ����
*/
void speed_pid(void)
{
		left_speed  = addPID_realize(&addPID,EncoderA);
		right_speed = addPID_realize(&add2PID,EncoderB);
		PWMC_Set(left_speed);
		PWMD_Set(right_speed);
}

/*
�������ܣ��ٶ�λ��˫�ջ�pid����
��ڲ�������
����ֵ����
*/
void Motor_Control_ClosedLoop(void)
{
	//����
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
	
	//����
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
�������ܣ����PID����
��ڲ�������
����ֵ����
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
�������ܣ��ٶȽǶ�˫�ջ�pid����
��ڲ�������
����ֵ����
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
�������ܣ��ٶ�λ��˫�ջ�pid��ִ�������
��ڲ�����speedL/speedR�ջ��ٶȣ�circleL/circleR�ջ�λ�ã�����ͣ�
����ֵ����
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
