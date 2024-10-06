/*
* @fuction name��FUZZY_PID_CONTROL
* @fuction description�� ģ������Ӧ�����㷨��Ϊ�˷������Ĭ��e��ec��[-3,3]���䣬
* ����ı�e��ec��Χ����������������(Ke��Kec=N/emax)����������(Ku=umax/N)�����´����
*	�����������������������Լ���Ȩƽ������ģ����PID��������ʽPID�㷨���㷨�����ο�����ӭ����
*	Xidian University - China
*/
/*Written By Mr.YangShunhang in 240811*/
/*Improved by Mr. Yang Shunhang in 241004*/
#include "./SYSTEM/usart/usart.h"
 #include "./BSP/FuzzyPid/fuzzypid.h"
#include "math.h"
#include "moto.h"
#include "pid.h"
 #include "./BSP/LED/led.h"
float MAX_Err;
FuzzyPID fuzzy(float e,float ec) // e ��Ŀ��ֵ�ͷ���ֵ����� ec�����仯��(���e��΢��) 
{
     float etemp,ectemp;
     float eLefttemp,ecLefttemp;
     float eRighttemp ,ecRighttemp;

     int eLeftIndex,ecLeftIndex;
     int eRightIndex,ecRightIndex;
     FuzzyPID      fuzzy_PID;
		 e = e/MAX_Err*3.0f;
		 ec = ec/MAX_Err*3.0f;
		 etemp = e > 3.0f ? 0.0f : 
              (e < -3.0f ? 0.0f : 
              (e >= 0.0f ? (e >= 2.0f ? 2.5f : 
              (e >= 1.0f ? 1.5f : 0.5f)) : 
              (e >= -1.0f ? -0.5f : 
              (e >= -2.0f ? -1.5f : 
              (e >= -3.0f ? -2.5f : 0.0f)))));

     eLeftIndex = (int)e;
     eRightIndex = eLeftIndex;
     eLeftIndex = (int)((etemp-0.5f) + 3.0f);        //[-3,3] -> [0,6]
     eRightIndex = (int)((etemp+0.5f) + 3.0f);

		 eLefttemp = (etemp == 0.0f) ? 0.0f : ((etemp + 0.5f) - e);
		 eRighttemp = (etemp == 0.0f) ? 0.0f : (e - (etemp - 0.5f));

		 ectemp = ec > 3.0f ? 0.0f : 
                (ec < -3.0f ? 0.0f : 
                (ec >= 0.0f ? (ec >= 2.0f ? 2.5f : 
                (ec >= 1.0f ? 1.5f : 0.5f)) : 
                (ec >= -1.0f ? -0.5f : 
                (ec >= -2.0f ? -1.5f : 
                (ec >= -3.0f ? -2.5f : 0.0f)))));

     ecLeftIndex = (int)((ectemp-0.5f) + 3.0f);        //[-3,3] -> [0,6]
     ecRightIndex = (int)((ectemp+0.5f) + 3.0f);

     ecLefttemp =ectemp == 0.0f ? 0.0f:((ectemp+0.5f)-ec);
     ecRighttemp=ectemp == 0.0f ? 0.0f:( ec-(ectemp-0.5f));

/*************************************��ģ��*************************************/
	fuzzy_PID.Kp = (eLefttemp * ecLefttemp *  fuzzyRuleKp[ecLeftIndex][eLeftIndex]
					+ eLefttemp * ecRighttemp * fuzzyRuleKp[ecRightIndex][eLeftIndex]
					+ eRighttemp * ecLefttemp * fuzzyRuleKp[ecLeftIndex][eRightIndex]
					+ eRighttemp * ecRighttemp * fuzzyRuleKp[ecRightIndex][eRightIndex]);

	fuzzy_PID.Ki =   (eLefttemp * ecLefttemp * fuzzyRuleKi[ecLeftIndex][eLeftIndex]
					+ eLefttemp * ecRighttemp * fuzzyRuleKi[ecRightIndex][eLeftIndex]
					+ eRighttemp * ecLefttemp * fuzzyRuleKi[ecLeftIndex][eRightIndex]
					+ eRighttemp * ecRighttemp * fuzzyRuleKi[ecRightIndex][eRightIndex]);

	fuzzy_PID.Kd = (eLefttemp * ecLefttemp *    fuzzyRuleKd[ecLeftIndex][eLeftIndex]
					+ eLefttemp * ecRighttemp * fuzzyRuleKd[ecRightIndex][eLeftIndex]
					+ eRighttemp * ecLefttemp * fuzzyRuleKd[ecLeftIndex][eRightIndex]
					+ eRighttemp * ecRighttemp * fuzzyRuleKd[ecRightIndex][eRightIndex]);
	return fuzzy_PID;

}

/*
* @fuction name��FuzzyPid_one_Out
* @fuction description�� ��������ٶȻ�
*/
float FuzzyPid_one_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0,ep=0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static FuzzyPID pid= {1.2, 0.1, 0.2};
	static int sumE = 0;                   //�ۼ�ƫ��
	static int lastE = 0;
	FuzzyPID OUT = {0, 0, 0};
	e = tar - cur;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE;            // ���仯��
	sumE += e;
	ep = lastE;
	lastE = e;
	
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd

	return (pid.Kp+OUT.Kp) * (e - lastE) +
	                  (pid.Ki+OUT.Ki) * e +
	                 (pid.Kd+OUT.Kd) *(e -2*ec+ep);
}

float FuzzyPid_two_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0,ep=0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static FuzzyPID pid= {1.2, 0.1, 0.2};
	static int sumE = 0;                   //�ۼ�ƫ��
	static int lastE = 0;
	FuzzyPID OUT = {0, 0, 0};
	e = tar - cur;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE;            // ���仯��
	sumE += e;
	ep = lastE;
	lastE = e;
	
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd

	return (pid.Kp+OUT.Kp) * (e - lastE) +
	                  (pid.Ki+OUT.Ki) * e +
	                 (pid.Kd+OUT.Kd) *(e -2*ec+ep);
}

float FuzzyPid_three_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0,ep=0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static FuzzyPID pid= {1.2, 0.1, 0.2};
	static int sumE = 0;                   //�ۼ�ƫ��
	static int lastE = 0;
	FuzzyPID OUT = {0, 0, 0};
	e = tar - cur;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE;            // ���仯��
	sumE += e;
	ep = lastE;
	lastE = e;
	
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd

	return (pid.Kp+OUT.Kp) * (e - lastE) +
	                  (pid.Ki+OUT.Ki) * e +
	                 (pid.Kd+OUT.Kd) *(e -2*ec+ep);
}

float FuzzyPid_four_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0,ep=0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static FuzzyPID pid= {1.2, 0.1, 0.2};
	static int sumE = 0;                   //�ۼ�ƫ��
	static int lastE = 0;
	FuzzyPID OUT = {0, 0, 0};
	e = tar - cur;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE;            // ���仯��
	sumE += e;
	ep = lastE;
	lastE = e;
	
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd

	return (pid.Kp+OUT.Kp) * (e - lastE) +
	                  (pid.Ki+OUT.Ki) * e +
	                 (pid.Kd+OUT.Kd) *(e -2*ec+ep);
}

//������ز���
//��������λ�û���ֻ��Ҫ����Ӧ��Ŀ��ֵ������ڲ�������
int num =0;

void fuzzy_control(float tar1,float tar2,float tar3,float tar4)
{
		MAX_Err = tar1;
		num = FuzzyPid_one_Out(tar1,Encoder1);
		PWM1_Set(num);
	/////////////////////
		MAX_Err = tar2;
		num = FuzzyPid_two_Out(tar2,Encoder2);
		PWM2_Set(num);
	////////////////////
		MAX_Err = tar3;
		num = FuzzyPid_three_Out(tar3,Encoder4);
		PWM3_Set(num);
	////////////////////
		MAX_Err = tar4;
		num = FuzzyPid_four_Out(tar4,Encoder3);
		PWM4_Set(num);
}


int sumE_1 = 0,sumE_2 = 0,sumE_3 = 0,sumE_4 = 0;
int lastE_1 = 0,lastE_2 = 0,lastE_3 = 0,lastE_4 = 0;
////λ��
/*��ǰ�ֵ�PID����*/
extern int fuzzypid_clearflag ;
float FuzzyPid_position1_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static PID pid= {0.2, 0.00001, 0.32};
	FuzzyPID OUT = {0, 0, 0};
	e = cur - tar;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE_1;            // ���仯��
	sumE_1 += e;
	lastE_1 = e;
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd
	
	return (pid.Kp+OUT.Kp)*e + (pid.Kd+OUT.Kd)*ec + (pid.Ki+OUT.Ki)*sumE_1; //�������ֵ
}

/*��ǰ�ֵ�PID����*/
float FuzzyPid_position2_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static PID pid= {0.2, 0.00001, 0.32};

	FuzzyPID OUT = {0, 0, 0};
	e = cur - tar;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE_2;            // ���仯��
	sumE_2 += e;
	lastE_2 = e;
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd
	
	return (pid.Kp+OUT.Kp)*e + (pid.Kd+OUT.Kd)*ec + (pid.Ki+OUT.Ki)*sumE_2; //�������ֵ
}

/*����ֵ�PID����*/
float FuzzyPid_position3_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static PID pid= {0.2, 0.00001, 0.32};
	
	FuzzyPID OUT = {0, 0, 0};
	e = cur - tar;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE_3;            // ���仯��
	sumE_3 += e;
	lastE_3 = e;
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd

	return (pid.Kp+OUT.Kp)*e + (pid.Kd+OUT.Kd)*ec + (pid.Ki+OUT.Ki)*sumE_3; //�������ֵ
}

/*�Һ��ֵ�PID����*/
float FuzzyPid_position4_Out(float tar,float cur)  // Ŀ��ֵ , ʵ��ֵ
{
   float e = 0,ec = 0;       // ���e ���仯��ec(���e��΢��)  ϵͳ���������� ��һ��Ϊ��
	static PID pid= {0.2, 0.00001, 0.32};

	FuzzyPID OUT = {0, 0, 0};
	e = cur - tar;             //  ʵ��ֵ-Ŀ��ֵ
	ec = e - lastE_4;            // ���仯��
	sumE_4 += e;
	lastE_4 = e;
	OUT = fuzzy(e, ec);      //ģ�����Ƶ���  kp��ki��kd

	return (pid.Kp+OUT.Kp)*e + (pid.Kd+OUT.Kd)*ec + (pid.Ki+OUT.Ki)*sumE_4; //�������ֵ
}
void fuzzypid_clearerr(void)
{

 sumE_1 = 0;sumE_2 = 0;sumE_3 = 0;sumE_4 = 0;
 lastE_1 = 0;lastE_2 = 0;lastE_3 = 0;lastE_4 = 0;
left1 = 0;right1 = 0;left2 = 0;right2 = 0;
tarA = 0;tarB = 0;tarC = 0;tarD = 0;
}

/*���������λ���������*/
extern int16_t Encoder1,Encoder2;
int left1 = 0,right1 = 0,left2 = 0,right2 = 0;
int spdL,spdR,spdBL,spdBR;//�ɱ�Ϊ�ֲ�
int Pwm1,Pwm2;

float tarA = 0,tarB = 0,tarC = 0,tarD = 0;//����Ŀ��ֵ�趨����ʱ������Ŀ��ֵ����;
int Xan_spd = 20;//���崮��PID�⻷λ�û�������޷�ֵ�������޸�������ı��ٶ�,ע���Ǳ��������ٶ�Ŷ,�ĸ�����һ�����ٶ�,��ֻ��λ�û�����Ķ���
/*
		*ABCD�ֱ��Ӧ ǰ����  ������

*/
float fuzzy_position_A_control(void)
{
		if(tarA>=0) MAX_Err = tarA+8;//����Ҫ���й�һ�� �ҵ���˼�ǽ����鵽  3  -  -3
		else MAX_Err = tarA-8;
		left1 += Encoder1;
		spdL = FuzzyPid_position1_Out(tarA,left1);
		spdL = Xianfu(spdL,Xan_spd);
		//Pwm1 = FuzzyPid_one_Out(spdL,Encoder1);
		if(myabs(left1)<=myabs(tarA)) return spdL;//PWM1_Set(spdL);
		else return 0;//PWM1_Set(0);
		

}

float fuzzy_position_B_control(void)
{
		if(tarB>=0) MAX_Err = tarB+8;//����Ҫ���й�һ�� �ҵ���˼�ǽ����鵽  3  -  -3
		else MAX_Err = tarB-8;
		right1 += Encoder2;
		spdR = FuzzyPid_position2_Out(tarB,right1);
		spdR = Xianfu(spdR,Xan_spd);
		//Pwm1 = FuzzyPid_one_Out(spdL,Encoder1);
		if(myabs(right1)<=myabs(tarB)) return spdR;//PWM1_Set(spdL);
		else return 0;//PWM1_Set(0);

}

float fuzzy_position_C_control(void)
{
		if(tarC>=0) MAX_Err = tarC+8;
		else MAX_Err = tarC-8;
		left2 += Encoder4;
		spdBL = FuzzyPid_position3_Out(tarC,left2);
		spdBL = Xianfu(spdBL,Xan_spd);
		//Pwm2 = FuzzyPid_two_Out(spdR,Encoder2);
		
		if(myabs(left2)<=myabs(tarC)) return spdBL;//PWM2_Set(spdBL);
		else {
			return 0;
			//PWM2_Set(0);
			//right1 = 0;
		}
}

float fuzzy_position_D_control(void)
{
		if(tarD>=0) MAX_Err = tarD+8;//����Ҫ���й�һ�� �ҵ���˼�ǽ����鵽  3  -  -3
		else MAX_Err = tarD-8;
		right2 += Encoder3;
		spdBR = FuzzyPid_position4_Out(tarD,right2);
		spdBR = Xianfu(spdBR,Xan_spd);
		//Pwm1 = FuzzyPid_one_Out(spdL,Encoder1);
		if(myabs(right2)<=myabs(tarD)) return spdBR;//PWM1_Set(spdL);
		else return 0;//PWM1_Set(0);
}

void moto_wait(void)
{
			while(1)
			{
				LED1(0);
				vTaskDelay(5);
				if(yaw_assisted == 1)
				{
				if((myabs(left1)>=myabs(tarA))&&(myabs(right1)>=myabs(tarB))&&
					(myabs(left2)>=myabs(tarC))&&(myabs(right2)>=myabs(tarD))&&!(Encoder3 || Encoder4 ||Encoder1 || Encoder2)&&((int)yaw == yaw_set_value)){
				
					fuzzypid_clearerr();
					LED1(1);
					break;
				}
			}
				else{
				if((myabs(left1)>=myabs(tarA))&&(myabs(right1)>=myabs(tarB))&&
					(myabs(left2)>=myabs(tarC))&&(myabs(right2)>=myabs(tarD))&&!(Encoder3 || Encoder4 ||Encoder1 || Encoder2)){
				
					fuzzypid_clearerr();
					LED1(1);
					break;
				}
				}
			
			}
}

void Moto_Config(int dis,enum dirction Direction_of_movement,int yaw_setting)
{
	switch(Direction_of_movement)
	{
		case front:{
					yaw_assisted = 1;
					yaw_set_value = yaw_setting;
					tarA = dis;
					tarB = dis;
					tarC = dis;
					tarD = dis;
					moto_wait();
					break;
		}
		case back:{
					yaw_assisted = 1;
					yaw_set_value = yaw_setting;
					tarA = -dis;
					tarB = -dis;
					tarC = -dis;
					tarD = -dis;
					moto_wait();
					break;
		}
		case left:{
					yaw_assisted = 1;
					yaw_set_value = yaw_setting;
					tarA = -dis;
					tarB = dis;
					tarC = dis;
					tarD = -dis;
					moto_wait();
					break;
		}
		case right:{
					yaw_assisted = 1;
					yaw_set_value = yaw_setting;
					tarA = dis;
					tarB = -dis;
					tarC = -dis;
					tarD = dis;
					moto_wait();
					break;
		}
		default : break;
	
	}
	
}

void turn90(bool dir)
{
	if(dir == L)
	{
			yaw_assisted = 0;
			tarA = -2200;
			tarB = 2200;
			tarC = -2200;
			tarD = 2200;
			moto_wait();
	}
	else if(dir == R)
	{
			yaw_assisted = 0;
			tarA = 2200;
			tarB = -2200;
			tarC = 2200;
			tarD = -2200;
			moto_wait();
	
	}

}
