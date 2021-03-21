#include "./key/bsp_key.h"
#include "./led/bsp_led.h"   


u16 num = 0;
extern u16 key_flag;
 /**
  * @brief  初始化KEY控制I/O
  * @param  无
  * @retval 无
  */
void KEY_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd ( KEY1_GPIO_CLK|
	                         KEY2_GPIO_CLK|
	                         KEY3_GPIO_CLK|
													 KEY4_GPIO_CLK, ENABLE); 

	/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = KEY1_PIN|KEY2_PIN|KEY3_PIN;	

		/*设置引脚模式为输入模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin = KEY4_PIN;
		
		GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);	

}

 /**
  * @brief  单次按键扫描
  * @param  GPIO_TypeDef *GPIOx ：端口号。  uint16_t GPIO_Pin ：指定端口位。
  * @retval 返回端口状态
  */
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if(key_flag >= 10)
	{
		uint8_t val;
		val = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
		if(val == 0)
		{
			num++;
			if(num == 2)
			{
				num = 0;
				key_flag = 0;
				val = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
				if(val == 1)
				{
					return 1;
				}
				else if(val == 0)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

/**
  * @brief  长按按键扫描
  * @param  GPIO_TypeDef *GPIOx ：端口号。  uint16_t GPIO_Pin ：指定端口位。
  * @retval 返回端口状态
  */
uint8_t KEY_Scan_down(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	uint8_t val;
	val = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	if(val == 1)
	{
		return 1;
	} 
	else if(val == 0)
	{
		Delay(10000000);
		val = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
		if(val == 1)
			return 1;
		else if(val == 0)
			return 0;
	}
  return 1;
}




/**
  * @brief  延时
  * @param  __IO uint32_t nCount ：指定延时循环的次数。
  * @retval 无
  */
void Delay(__IO uint32_t nCount)	
{
	for(; nCount != 0; nCount--);
}




