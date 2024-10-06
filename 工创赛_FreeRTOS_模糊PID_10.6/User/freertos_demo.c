#include "pwm.h"
#include "pid.h"  
#include "./BSP/MOTO/moto.h"
#include "oled.h"
#include "./BSP/KEY/key.h"
#include "freertos_demo.h"
#include "./SYSTEM/DELAY/delay.h"
#include "./SYSTEM/USART/usart.h"
#include "./BSP/GPIO/gpio.h"
#include "./BSP/TIMER/btim.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
 #include "./BSP/LED/led.h"
 #include "./BSP/NRF24L01/nrf24l01.h"
  #include "./BSP/FuzzyPid/fuzzypid.h"
/******************************************************************************************************/
/*LCD & HWT101*****************************************************************************************************/
#include "./BSP/HWT101/HWT101.h"
#include "./BSP/Software_LCD3.5/lcd.h"
#include "./BSP/Software_LCD3.5/test.h"
#include "./BSP/Software_LCD3.5/spi.h"

/******************************************************************************************************/
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO 1                   /* �������ȼ� */
#define START_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            StartTask_Handler;  /* ������ */
void start_task(void *pvParameters);        /* ������ */

/* TASK1 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK1_PRIO      2                   /* �������ȼ� */
#define TASK1_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task1Task_Handler;  /* ������ */
void task1(void *pvParameters);             /* ������ */

/* MOTO ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define MOTO_TASK_PRIO      2                  /* �������ȼ� */
#define MOTO_TASK_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            MOTOTaskTask_Handler;  /* ������ */
void MOTO_task(void *pvParameters);             /* ������ */


/* TASK2 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define OLED_TASK_PRIO      2                  /* �������ȼ� */
#define OLED_TASK_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            OLEDTaskTask_Handler;  /* ������ */
void oled_task(void *pvParameters);             /* ������ */

/* key_task ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define MAIN_TASK_PRIO      4                   /* �������ȼ� */
#define MAIN_STK_SIZE  1024                 /* �����ջ��С */
TaskHandle_t            MAINTask_Handler;  /* ������ */
void main_task(void *pvParameters);             /* ������ */

/*****************************���������񴴽���Ҫ��һЩ������ �������ȼ� ��ջ��С ����������**************************************************/

/**
 * @brief       FreeRTOS��ں���,��������һ����ʼ����
 * @param       ��
 * @retval      ��
 */
void freertos_demo(void)
{
//    lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
//    lcd_show_string(10, 47, 220, 24, 24, "Interrupt", RED);
//    lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
    xTaskCreate((TaskFunction_t )start_task,            /* ������ */
                (const char*    )"start_task",          /* �������� */
                (uint16_t       )START_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )START_TASK_PRIO,       /* �������ȼ� */
                (TaskHandle_t*  )&StartTask_Handler);   /* ������ */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��//������������1��2�ȣ��ÿ�ʼ���񴴽���Ҫ������
 */

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* �����ٽ��� */
    /* ��ʼ��TIM3��TIM5 */
      btim_tim7_int_init(8400-1, 100-1);
			btim_tim6_int_init(8400-1, 1000-1);
			//MX_TIM6_Init();
			//HAL_TIM_Base_Start_IT(&g_tim6_handle); //������ʱ��6 �ж�
    /* ��������1 */
    xTaskCreate((TaskFunction_t )task1,
                (const char*    )"task1",
                (uint16_t       )TASK1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK1_PRIO,
                (TaskHandle_t*  )&Task1Task_Handler);
		/* ��������2 */				
    xTaskCreate((TaskFunction_t )oled_task,
               (const char*    )"oled_task",
               (uint16_t       )OLED_TASK_STK_SIZE,
               (void*          )NULL,
               (UBaseType_t    )OLED_TASK_PRIO,
               (TaskHandle_t*  )&OLEDTaskTask_Handler);
		/* ��������3 */				
    xTaskCreate((TaskFunction_t )main_task,
               (const char*    )"main_task",
               (uint16_t       )MAIN_STK_SIZE,
               (void*          )NULL,
               (UBaseType_t    )MAIN_TASK_PRIO,
               (TaskHandle_t*  )&MAINTask_Handler);
		/* ��������������� */				
    xTaskCreate((TaskFunction_t )MOTO_task,
               (const char*    )"MOTO_task",
               (uint16_t       )MOTO_TASK_STK_SIZE,
               (void*          )NULL,
               (UBaseType_t    )MOTO_TASK_PRIO,
               (TaskHandle_t*  )&MOTOTaskTask_Handler);
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
}

/**
 * @brief       task1
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 * @work        LED0����ָʾ����ʾ�����������������
 */
int time;
void task1(void *pvParameters)
{
    //uint32_t task1_num = 0;
    
	while(1)
	{
		
		//printf("YAW: %f\r\n",HWT101_yaw);
		LED0(0);
		vTaskDelay(500);
		LED0(1);
		vTaskDelay(500);
	}

}

/**
 * @brief       oled_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 * @work        ˢ��OLED
 */

void oled_task(void *pvParameters)
{
	while(1){
		OLED_Show();
   //LCD_Dynamic_Show();  //LCD��ʾ
   vTaskDelay(100);
	}
}

/**
 * @brief       main_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 * @work        ������-���߳�
 */

int fuzzypid_clearflag = 0;//�ò���

void main_task(void *pvParameters)
{
	uint8_t key;
	pidmode=frees;
	//while(nrf24l01_check());
	
	while(1)
	{
		key = key_scan(0);
		if(key == 3) {
			pidmode = fuzzyspd_pid;
						Moto_Config(600,left,0);
            Moto_Config(5000,front,0);
            vTaskDelay(1000);
            Moto_Config(5000,front,0);
            vTaskDelay(1000);
            Moto_Config(300,left,0);
            Moto_Config(3000,back,0);
            turn90(L);
            Moto_Config(11500,front,90);
            turn90(L);
            vTaskDelay(1000);
            turn90(R);
            Moto_Config(5300,right,90);
            Moto_Config(6000,back,90);
            vTaskDelay(1000);
            Moto_Config(5800,back,90);
            turn90(R);
            Moto_Config(3000,back,0);
            vTaskDelay(1000);
            Moto_Config(300,left,0);
            Moto_Config(3000,back,0);
            turn90(L);
            Moto_Config(11500,front,90);
            turn90(L);
            vTaskDelay(1000);
            turn90(R);
            Moto_Config(5500,right,90);
            Moto_Config(6000,back,90);
            vTaskDelay(1000);
            Moto_Config(12000,left,90);
            Moto_Config(5500,back,90);
//			tarA = 6000;
//			tarB = -6000;
//			tarC = -6000;
//			tarD = 6000;
//			moto_wait();
//			tarA = 3000;
//			tarB = 3000;
//			tarC = 3000;
//			tarD = 3000;
//			moto_wait();
//			yaw_assisted = 0;
//			tarA = -2200;
//			tarB = 2200;
//			tarC = -2200;
//			tarD = 2200;
//			moto_wait();
//			yaw_assisted = 1;
//			yaw_set_value = 90;
//			tarA = 3000;
//			tarB = 3000;
//			tarC = 3000;
//			tarD = 3000;
//			moto_wait();
		}
		else if(key == 2) 
		{
			fuzzypid_clearerr();
		}
	
		vTaskDelay(10);
	}
	
	
}

void MOTO_task(void *pvParameters)
{
while(1)
{
	vTaskDelay(10);
}

}

