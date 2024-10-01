#include "stepper_tim.h"

/******************************************************************************************/
/* ��ʱ�����þ�� ���� */

/* �߼���ʱ��PWM */
TIM_HandleTypeDef TIM8_Handle;           /* ��ʱ��x��� */
TIM_OC_InitTypeDef TIM8_OC_Handle;   /* ��ʱ�������� */ 
uint8_t Step_Run_Flag;   //��������˶���־
/******************************************************************************************/

/**
 * @brief       �߼���ʱ��TIMX PWM ��ʼ������
 * @note
 *              �߼���ʱ����ʱ������APB2, ��PCLK2 = 168Mhz, ��������PPRE2����Ƶ, ���
 *              �߼���ʱ��ʱ�� = 168Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void atim_timx_oc_chy_init(uint16_t arr, uint16_t psc)
{
    ATIM_TIMX_PWM_CHY_CLK_ENABLE();                             /* TIMX ʱ��ʹ�� */

    TIM8_Handle.Instance = ATIM_TIMX_PWM;                    /* ��ʱ��x */
    TIM8_Handle.Init.Prescaler = psc;                        /* ��ʱ����Ƶ */
    TIM8_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;       /* ���ϼ���ģʽ */
    TIM8_Handle.Init.Period = arr;                           /* �Զ���װ��ֵ */
    TIM8_Handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;   /* ��Ƶ���� */
    TIM8_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /*ʹ��TIMx_ARR���л���*/
    TIM8_Handle.Init.RepetitionCounter = 0;                  /* ��ʼʱ������*/
    HAL_TIM_PWM_Init(&TIM8_Handle);                          /* ��ʼ��PWM */
    
    TIM8_OC_Handle.OCMode = TIM_OCMODE_PWM1;             /* ģʽѡ��PWM1 */
    TIM8_OC_Handle.Pulse = arr/2;
    TIM8_OC_Handle.OCPolarity = TIM_OCPOLARITY_HIGH;     /* ����Ƚϼ���Ϊ�� */
    TIM8_OC_Handle.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    TIM8_OC_Handle.OCFastMode = TIM_OCFAST_DISABLE;
    TIM8_OC_Handle.OCIdleState = TIM_OCIDLESTATE_RESET;
    TIM8_OC_Handle.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH1); /* ����TIMxͨ��y */
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH2); /* ����TIMxͨ��y */   
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH3); /* ����TIMxͨ��y */
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handle, &TIM8_OC_Handle, ATIM_TIM8_PWM_CH4); /* ����TIMxͨ��y */
   
}


/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
                �˺����ᱻHAL_TIM_PWM_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == ATIM_TIMX_PWM)
    {
        GPIO_InitTypeDef gpio_init_struct;
        ATIM_TIMX_PWM_CHY_CLK_ENABLE();                             /* ����ͨ��y��GPIOʱ�� */
        ATIM_TIM8_PWM_CH1_GPIO_CLK_ENABLE();                        /* IOʱ��ʹ�� */
        ATIM_TIM8_PWM_CH2_GPIO_CLK_ENABLE();                        /* IOʱ��ʹ�� */
        ATIM_TIM8_PWM_CH3_GPIO_CLK_ENABLE();                        /* IOʱ��ʹ�� */
        ATIM_TIM8_PWM_CH4_GPIO_CLK_ENABLE();                        /* IOʱ��ʹ�� */

        gpio_init_struct.Pin = ATIM_TIM8_PWM_CH1_GPIO_PIN;          /* ͨ��y��GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                    /* ����������� */
        gpio_init_struct.Pull = GPIO_PULLUP;                        /* ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
        gpio_init_struct.Alternate = ATIM_TIMX_PWM_CHY_GPIO_AF;     /* �˿ڸ��� */
        HAL_GPIO_Init(ATIM_TIM8_PWM_CH1_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIM8_PWM_CH2_GPIO_PIN;          /* ͨ��x��GPIO�� */
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
 * @brief       �߼���ʱ�������жϷ�����
 * @param       ��
 * @retval      ��
 */
void ATIM_TIMX_UP_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM8_Handle);            /* ��ʱ�����ô����� */
}
