#include "RTOS.h"
#include "main.h"

/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

/* TASK1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO      2                  /* 任务优先级 */
#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void task1(void *pvParameters);             /* 任务函数 */

#define TASK2_PRIO      3                  /* 任务优先级 */
#define TASK2_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task2Task_Handler;  /* 任务句柄 */
void task2(void *pvParameters);             /* 任务函数 */

#define TASK3_PRIO      4                  /* 任务优先级 */
#define TASK3_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task3Task_Handler;  /* 任务句柄 */
void task3(void *pvParameters);             /* 任务函数 */

#define TASK4_PRIO      5                  /* 任务优先级 */
#define TASK4_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task4Task_Handler;  /* 任务句柄 */
void task4(void *pvParameters);             /* 任务函数 */
/*****************************以上是任务创建需要的一些任务句柄 任务优先级 堆栈大小 创建任务函数**************************************************/

/**
 * @brief       FreeRTOS入口函数,用来创建一个开始任务
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */   //动态创建
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();   //开启任务调度器
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无//用来创建任务1和2等，用开始任务创建需要的任务
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 <==> 关闭中断 */   //目的是防止在任务没有完全创建完成时，低优先级的任务先执行
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t )task1,
                (const char*    )"task1",
                (uint16_t       )TASK1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK1_PRIO,
                (TaskHandle_t*  )&Task1Task_Handler);
								
		/* 创建任务2 */				
    xTaskCreate((TaskFunction_t )task2,
                (const char*    )"task2",
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler);

		/* 创建任务3 */				
    xTaskCreate((TaskFunction_t )task3,
                (const char*    )"task3",
                (uint16_t       )TASK3_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK3_PRIO,
                (TaskHandle_t*  )&Task3Task_Handler);

		/* 创建任务4 */				
    xTaskCreate((TaskFunction_t )task4,
                (const char*    )"task4",
                (uint16_t       )TASK4_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK4_PRIO,
                (TaskHandle_t*  )&Task4Task_Handler);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////								
//    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
			vTaskDelete(NULL); /* 删除任务自身 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

/**
 * @brief       task1
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void task1(void *pvParameters)
{   
	while(1)
	{
		HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
		printf("task1:Executing\r\n");
		vTaskDelay(500);
	}
}

/**
 * @brief       task2
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */

void task2(void *pvParameters)
{
	while(1)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		printf("task2:Executing\r\n");
		vTaskDelay(1000);
	}
}

void task3(void *pvParameters)
{
	while(1)
	{
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin); 
		printf("task3:Executing\r\n");
		vTaskDelay(1500);
	}
}

void task4(void *pvParameters)
{
	uint16_t keynum;
	printf("Task4 Start\r\n");
	while(1)
	{ 
		keynum = key_scan(0);
		if(keynum == 1)
		{
			if(Task1Task_Handler != NULL)   //依次删除任务，按键按下一次删除一个任务
			{
				vTaskDelete(Task1Task_Handler);
				printf("Task1 ==> Deleted \r\n");
				Task1Task_Handler = NULL;
			}
			else if(Task2Task_Handler != NULL)
			{
				vTaskDelete(Task2Task_Handler);
				printf("Task2 ==> Deleted \r\n");
				Task2Task_Handler = NULL;
			}
			else if(Task3Task_Handler != NULL)
			{
				vTaskDelete(Task3Task_Handler);
				printf("Task3 ==> Deleted \r\n");
				Task3Task_Handler = NULL;
			}
		}
		vTaskDelay(10);
	}
}

