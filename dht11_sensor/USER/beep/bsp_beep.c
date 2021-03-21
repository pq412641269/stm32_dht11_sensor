#include "./beep/bsp_beep.h"   



/**
  * @brief  蜂鸣器初始化
  * @param  无
  * @retval 无
  */
void BEEP_Init(void)
{    	 
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd (BEEP1_GPIO_CLK, ENABLE); 
		
		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = BEEP1_PIN;	

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

		/*设置引脚速率为2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(BEEP1_GPIO_PORT, &GPIO_InitStructure);	

}


