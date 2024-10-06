#ifndef __FUZZYPID_H
#define __FUZZYPID_H
#include "./SYSTEM/sys/sys.h"
#include "stdbool.h"
#define NL   -3
#define NM	 -2
#define NS	 -1
#define ZE	 0
#define PS	 1
#define PM	 2
#define PL	 3

//注意：static PID pid= {0, 0, 0};  需要自己赋值

static const float fuzzyRuleKp[7][7]={
	PL,	PL,	PM,	PM,	PS,	PS,	ZE,
	PL,	PL,	PM,	PM,	PS,	ZE,	ZE,
	PM,	PM,	PM,	PS,	ZE,	NS,	NM,
	PM,	PS,	PS,	ZE,	NS,	NM,	NM,
	PS,	PS,	ZE,	NS,	NS,	NM,	NM,
	ZE,	ZE,	NS,	NM,	NM,	NM,	NL,
	ZE,	NS,	NS,	NM,	NM,	NL,	NL
};

static const float fuzzyRuleKi[7][7]={
	NL,	NL,	NL,	NM,	NM,	ZE,	ZE,
	NL,	NL,	NM,	NM,	NS,	ZE,	ZE,
	NM,	NM,	NS,	NS,	ZE,	PS,	PS,
	NM,	NS,	NS,	ZE,	PS,	PS,	PM,
	NS,	NS,	ZE,	PS,	PS,	PM,	PM,
	ZE,	ZE,	PS,	PM,	PM,	PL,	PL,
	ZE,	ZE,	PS,	PM,	PL,	PL,	PL
};

static const float fuzzyRuleKd[7][7]={
	PS,	PS,	ZE,	ZE,	ZE,	PL,	PL,
	NS,	NS,	NS,	NS,	ZE,	NS,	PM,
	NL,	NL,	NM,	NS,	ZE,	PS,	PM,
	NL,	NM,	NM,	NS,	ZE,	PS,	PM,
	NL,	NM,	NS,	NS,	ZE,	PS,	PS,
	NM,	NS,	NS,	NS,	ZE,	PS,	PS,
	PS,	ZE,	ZE,	ZE,	ZE,	PL,	PL
};

typedef struct{
	float Kp;
	float Ki;
	float Kd;
}FuzzyPID;

 enum dirction{
		front,
		back,
		left,
		right
};
#define L 0
#define R 1
FuzzyPID fuzzy(float e,float ec); // 模糊PID自整定函数
//float FuzzyPid_Out(float tar,float cur);  // 目标值 , 实际值
void fuzzy_control(float cur1,float cur2,float cur3,float cur4);
extern int tar1,tar2;
float fuzzy_position_A_control(void);
float fuzzy_position_B_control(void);
float fuzzy_position_C_control(void);
float fuzzy_position_D_control(void);
extern float tarA ,tarB ,tarC ,tarD ;//这是目标值设定，到时候改这个目标值即可;
extern int left1 ,right1 ,left2 ,right2 ;
void fuzzypid_clearerr(void);
void moto_wait(void);
void turn90(bool dir);
void Moto_Config(int dis,enum dirction Direction_of_movement,int yaw_setting);
#endif

