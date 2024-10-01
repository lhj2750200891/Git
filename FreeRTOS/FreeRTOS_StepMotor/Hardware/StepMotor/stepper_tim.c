#include "stepper_tim.h"

/******************************************************************************************/
/* 定时器配置句柄 定义 */

/* 高级定时器PWM */
TIM_HandleTypeDef TIM8_Handle;           /* 定时器x句柄 */
TIM_OC_InitTypeDef TIM8_OC_Handle;   /* 定时器输出句柄 */ 
uint8_t Step_Run_Flag;   //步进电机运动标志
/******************************************************************************************/

/**
 * @brief       高级定时器TIMX PWM 初始化函数
 * @note
 *              高级定时器的时钟来自APB2, 而PCLK2 = 168Mhz, 我们设置PPRE2不分频, 因此
 *              高级定时器时钟 = 168Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void atim_timx_oc_chy_init(uint16_t arr, uint16_t psc)
{
    ATIM_TIMX_PWM_CHY_CLK_ENABLE();                             /* TIMX 时钟使能 */

    TIM8_Handle.Instance = ATIM_TIMX_PWM;                    /* 定时器x */
    TIM8_Handle.Init.Prescaler = psc;                        /* 定时器分频 */
    TIM8_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;       /* 向上计数模式 */
    TIM8_Handle.Init.Period = arr;                           /* 自动重装载值 */
    TIM8_Handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;   /* 分频因子 */
    TIM8_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /*使能TIMx_ARR进行缓冲*/
    TIM8_Handle.Init.RepetitionCounter = 0;                  /* 开始时不计数*/
    HAL_TIM_PWM_Init(&TIM8_Handle);                          /* 初始化PWM */
    
    TIM8_OC_Handle.OCMode = TIM_OCMODE_PWM1;             /* 模式选择PWM1 */
    TIM8_OC_Handle.Pulse = arr/2;
    TIM8_OC_Handle.OCPolarity = TIM_OCPOLARITY_HIGH;     /* 输出比较极性为高 */
    TIM8_OC_Handle.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    TIM8_OC_Handle.OCFastMode = TIM_OCFAST_DISABLE;
    TIM8_OC_Handle.OCIdleState = TIM_OCIDLESTATE_RESET;
    TIM8_OC_Handle.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH1); /* 配置TIMx通道y */
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH2); /* 配置TIMx通道y */   
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH3); /* 配置TIMx通道y */
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH4); /* 配置TIMx通道y */
   
}


/**
 * @brief       定时器底层驱动，时钟使能，引脚配置
                此函数会被HAL_TIM_PWM_Init()调用
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == ATIM_TIMX_PWM)
    {
        GPIO_InitTypeDef gpio_init_struct;
        ATIM_TIMX_PWM_CHY_CLK_ENABLE();                             /* 开启通道y的GPIO时钟 */
        ATIM_TIM8_PWM_CH1_GPIO_CLK_ENABLE();                        /* IO时钟使能 */
        ATIM_TIM8_PWM_CH2_GPIO_CLK_ENABLE();                        /* IO时钟使能 */
        ATIM_TIM8_PWM_CH3_GPIO_CLK_ENABLE();                        /* IO时钟使能 */
        ATIM_TIM8_PWM_CH4_GPIO_CLK_ENABLE();                        /* IO时钟使能 */

        gpio_init_struct.Pin = ATIM_TIM8_PWM_CH1_GPIO_PIN;          /* 通道y的GPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                    /* 复用推挽输出 */
        gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
        gpio_init_struct.Alternate = ATIM_TIMX_PWM_CHY_GPIO_AF;     /* 端口复用 */
        HAL_GPIO_Init(ATIM_TIM8_PWM_CH1_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIM8_PWM_CH2_GPIO_PIN;          /* 通道x的GPIO口 */
        HAL_GPIO_Init(ATIM_TIM8_PWM_CH2_GPIO_PORT, &gpio_init_struct);
       
        gpio_init_struct.Pin = ATIM_TIM8_PWM_CH3_GPIO_PIN;         
        HAL_GPIO_Init(ATIM_TIM8_PWM_CH3_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIM8_PWM_CH4_GPIO_PIN;          
        HAL_GPIO_Init(ATIM_TIM8_PWM_CH4_GPIO_PORT, &gpio_init_struct);
				
        HAL_NVIC_SetPriority(ATIM_TIMX_UP_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(ATIM_TIMX_UP_IRQn);				
    }
}

/**
 * @brief       高级定时器共用中断服务函数
 * @param       无
 * @retval      无
 */
void ATIM_TIMX_UP_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM8_Handle);            /* 定时器共用处理函数 */
}
