

#include "./BSP/GPIO/gpio.h"
#include "./SYSTEM/delay/delay.h"
#include "adc.h"
/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void gpio_init(void)
{
	  
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO配置参数存储变量 */
		/*循迹初始化*/
    L3_GPIO_CLK_ENABLE();
	  L2_GPIO_CLK_ENABLE();
		L1_GPIO_CLK_ENABLE();
		M_GPIO_CLK_ENABLE();
		R1_GPIO_CLK_ENABLE();
	  R2_GPIO_CLK_ENABLE();
		R3_GPIO_CLK_ENABLE();
	
    gpio_init_struct.Pin = L3_GPIO_PIN | L2_GPIO_PIN |L1_GPIO_PIN |M_GPIO_PIN |R1_GPIO_PIN |R2_GPIO_PIN |R3_GPIO_PIN;                       /* KEY0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_NOPULL;                        /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(GPIOD, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */

		
		LIGHT_GPIO_CLK_ENABLE();
		gpio_init_struct.Pin = LIGHT_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LIGHT_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

    gpio_init_struct.Pin = LIGHT_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(LIGHT_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */
    
		LIGHT(0);
		
		BEEP_GPIO_CLK_ENABLE();
		gpio_init_struct.Pin = BEEP_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(BEEP_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

    gpio_init_struct.Pin = BEEP_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(BEEP_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */
    
		BEEP(1);

}




















