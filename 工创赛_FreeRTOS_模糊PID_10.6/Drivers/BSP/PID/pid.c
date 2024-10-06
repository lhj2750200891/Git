#include "pid.h"  
#include "./BSP/MOTO/moto.h"
#include "control.h"
#include "math.h"
/*定义一个PID结构体型的全局变量*/
PID addPID;
PID add2PID;
PID add3PID;
PID add4PID;
PID PosionPID;
PID Posion2PID;
PID yawPID;
void PID_param_init()
{


	/* 初始化参数 改速度：addPID.target_val。改位置：PosionPID.target_val;
	   命运的馈赠早已在暗中标好了他的价格，23 11 12，冲！！！
	   2024 1 .1 移植freertos,新年加油
	   如果要单拆开速度环去用的话，直接用PWM_Set(Speed=addPID_realize(&addPID,Encoder1));就好了吧
	*/
  /*位置PID的参数*/
	PosionPID.target_val=0;				
	PosionPID.output_val=0.0;
	PosionPID.Error=0.0;
	PosionPID.LastError=0.0;
	PosionPID.integral=0.0;

	PosionPID.Kp = 2.6;  
	PosionPID.Ki = 0.0006;
	PosionPID.Kd = 0.18;

	
	Posion2PID.target_val=0;				
	Posion2PID.output_val=0.0;
	Posion2PID.Error=0.0;
	Posion2PID.LastError=0.0;
	Posion2PID.integral=0.0;

	Posion2PID.Kp = 0.6;  
	Posion2PID.Ki = 0.0001;
	Posion2PID.Kd = 0.18;
 /*速度PID的参数（左轮）*/
	addPID.target_val=0;	//目标值
	addPID.output_val=0.0;
	addPID.Error=0.0;
	addPID.LastError=0.0;
	addPID.integral=0.0;

	//addPID.Kp = 1.2;
	addPID.Kp = 1.1*log10(6.8*abs(addPID.Error)+10);
	addPID.Ki = 0.3;//0.8
	addPID.Kd = 0;

  /*速度PID的参数（右轮）*/
	add2PID.target_val=0;		//目标值
	add2PID.output_val=0.0;
	add2PID.Error=0.0;
	add2PID.LastError=0.0;
	add2PID.integral=0.0;

	add2PID.Kp = 1.1*log10(6.8*abs(addPID.Error)+10);
	add2PID.Ki = 0.3;
	add2PID.Kd = 0;
	
	add3PID.target_val=0;	//目标值
	add3PID.output_val=0.0;
	add3PID.Error=0.0;
	add3PID.LastError=0.0;
	add3PID.integral=0.0;

	//addPID.Kp = 1.2;
	add3PID.Kp = 1.1*log10(6.8*abs(addPID.Error)+10);
	add3PID.Ki = 0.3;//0.8
	add3PID.Kd = 0;

  /*速度PID的参数（右轮）*/
	add4PID.target_val=0;		//目标值
	add4PID.output_val=0.0;
	add4PID.Error=0.0;
	add4PID.LastError=0.0;
	add4PID.integral=0.0;

	add4PID.Kp = 1.1*log10(6.8*abs(addPID.Error)+10);
	add4PID.Ki = 0.3;
	add4PID.Kd = 0;
//陀螺仪走直线的PID
	yawPID.target_val=0;				
	yawPID.output_val=0.0;
	yawPID.Error=0.0;
	yawPID.LastError=0.0;
	yawPID.integral=0.0;

	yawPID.Kp = 1.1;  
	yawPID.Ki = 0;
	yawPID.Kd = 0.6;
	
}

/**
  * @brief  设置目标值
  * @param  val		目标值(位置pid)
  *	@note 	无
  * @retval 无
  */
void set_PID_target(float temp_val)
{  
	PosionPID.target_val = temp_val;    // 设置当前的目标值
}

/**
  * @brief  获取目标值
  * @param  无
  *	@note 	无
  * @retval 目标值
  */
float get_pid_target(PID *pid)
{
  return pid->target_val;    // 获取当前的目标值
}

/**
  * @brief  设置位置比例、积分、微分系数
  * @param  p：比例系数 P
  * @param  i：积分系数 i
  * @param  d：微分系数 d
  *	@note 	无
  * @retval 无
  */
void set_PID(float p, float i, float d)
{
	PosionPID.Kp = p;    // 设置比例系数 P
	PosionPID.Ki = i;    // 设置积分系数 I
	PosionPID.Kd = d;    // 设置微分系数 D
}
/**
  * @brief  速度PID算法实现
  * @param  actual_val:实际值
  *	@note 	无
  * @retval 通过PID计算后的输出
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

/**
  * @brief  位置PID算法实现
  * @param  actual_val:实际值
  *	@note 	无
  * @retval 通过PID计算后的输出
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

/*求绝对值函数*/
int16_t myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
int Xianfu(int data,int max)
{	
    if(data<-max) data=-max;	
    if(data> max) data= max;	
    return data;
}
/**
串级PID的实现
 //int16_t Encoder_Speed =0;
//int16_t Position =0;
int16_t SpeedFL,SpeedFR,SpeedBL,SpeedBR;//实际速度
int Pos_FL,Pos_FR,Pos_BL,Pos_BR;
int max_speed;*/
int16_t SpeedFL,SpeedFR;//实际速度
int Pos_FL,Pos_FR;
int Lmax_speed,Rmax_speed;
void MotorControl(void)
{
		/*左前轮*/
	Pos_FL+=Encoder1;    //2.速度积分得到位置
	SpeedFL=PosionPID_realize(&PosionPID,Pos_FL);//3.输入位置式PID计算
	SpeedFL = Xianfu(SpeedFL,Lmax_speed);								//速度限幅
	addPID.target_val = SpeedFL;    					 // 位置环给到速度环的输入
	SpeedFL=addPID_realize(&addPID,Encoder1);//4.输入速度式PID计算
	PWM1_Set(SpeedFL);  //5.PWM输出给电机
	if(myabs(Pos_FL-PosionPID.target_val)<20)
	{

	addPID.target_val=0;
	SpeedFL=addPID_realize(&addPID,Encoder1);
	PWM1_Set(SpeedFL);
	Pos_FL=0;
	PosionPID.target_val=0;	
	PosionPID.Error=0.0;
	PosionPID.LastError=0.0;
	PosionPID.integral=0.0;
	}
		/*右前轮*/
	Pos_FR+=Encoder2;    //2.速度积分得到位置
	SpeedFR=PosionPID_realize(&Posion2PID,Pos_FR);//3.输入位置式PID计算
	SpeedFR = Xianfu(SpeedFR,Rmax_speed);								//速度限幅
	add2PID.target_val = SpeedFR;    					 // 位置环给到速度环的输入
	SpeedFR=addPID_realize(&add2PID,Encoder2);//4.输入速度式PID计算
	PWM2_Set(SpeedFR);  //5.PWM输出给电机
	if(myabs(Pos_FR-Posion2PID.target_val)<20)
	{
	add2PID.target_val=0;
	SpeedFR=addPID_realize(&add2PID,Encoder2);
	PWM2_Set(SpeedFR);
	Pos_FR=0;
	Posion2PID.target_val=0;
	Posion2PID.Error=0.0;
	Posion2PID.LastError=0.0;
	Posion2PID.integral=0.0;
	}
}
void clear_piderr(void)
{
	Pos_FL=0;
	PosionPID.target_val=0;	
	PosionPID.Error=0.0;
	PosionPID.LastError=0.0;
	PosionPID.integral=0.0;
	Pos_FR=0;
	Posion2PID.target_val=0;
	Posion2PID.Error=0.0;
	Posion2PID.LastError=0.0;
	Posion2PID.integral=0.0;
}
void speed_pid(void)
{
				left_speed  = addPID_realize(&addPID,Encoder1);
				right_speed = addPID_realize(&add2PID,Encoder2);
				PWM1_Set(left_speed);
				PWM2_Set(right_speed);
}
void add_pid_normal(int tar1,int tar2,int tar3,int tar4)
{
			addPID.target_val = tar1;
			add2PID.target_val = tar2;
			add3PID.target_val = tar3;
			add4PID.target_val = tar4;
			PWM1_Set(addPID_realize(&addPID,Encoder1));
			PWM2_Set(addPID_realize(&add2PID,Encoder2));
			PWM3_Set(addPID_realize(&add3PID,Encoder4));
			PWM4_Set(addPID_realize(&add4PID,Encoder3));	
}
///*陀螺仪——速度串级PID的实现*////
//mode chosemode;
extern float yaw;
int yaw_out;
int Ls,Rs;

yawctrl yawcontrol ;

void yawspeed(void)
{
			yawPID.target_val=yawcontrol.direction;				
			yaw_out = PosionPID_realize(&yawPID,yaw);
			yaw_out = Xianfu(yaw_out,5);
			if(yawcontrol.speed>0&&yawcontrol.speed<5) yawcontrol.speed=5;										//不能让speed-yaw_out小于0
			else if(yawcontrol.speed<0&&yawcontrol.speed>-5) yawcontrol.speed=-5;	
			addPID.target_val = yawcontrol.speed-yaw_out;    				   	 // 位置环给到速度环的输入
			add2PID.target_val = yawcontrol.speed + yaw_out;
			Ls=addPID_realize(&addPID,Encoder1);//4.输入速度式PID计算
			Rs=addPID_realize(&add2PID,Encoder2);//4.输入速度式PID计算
			PWM1_Set(Ls);
			PWM2_Set(Rs);
}
extern int yaw_set_value ;
float yaw_output(void)
{
	static int speed = 0;
		PosionPID.target_val=yaw_set_value;
		speed = PosionPID_realize(&PosionPID,(int)yaw);
		speed = Xianfu(speed , 15);
		return  speed;
}



