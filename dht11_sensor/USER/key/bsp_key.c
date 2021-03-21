#include "./key/bsp_key.h"
#include "./led/bsp_led.h"   


u16 num = 0;
extern u16 key_flag;
 /**
  * @brief  ��ʼ��KEY����I/O
  * @param  ��
  * @retval ��
  */
void KEY_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd ( KEY1_GPIO_CLK|
	                         KEY2_GPIO_CLK|
	                         KEY3_GPIO_CLK|
													 KEY4_GPIO_CLK, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = KEY1_PIN|KEY2_PIN|KEY3_PIN;	

		/*��������ģʽΪ����ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*������������Ϊ2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin = KEY4_PIN;
		
		GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);	

}

 /**
  * @brief  ���ΰ���ɨ��
  * @param  GPIO_TypeDef *GPIOx ���˿ںš�  uint16_t GPIO_Pin ��ָ���˿�λ��
  * @retval ���ض˿�״̬
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
  * @brief  ��������ɨ��
  * @param  GPIO_TypeDef *GPIOx ���˿ںš�  uint16_t GPIO_Pin ��ָ���˿�λ��
  * @retval ���ض˿�״̬
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
  * @brief  ��ʱ
  * @param  __IO uint32_t nCount ��ָ����ʱѭ���Ĵ�����
  * @retval ��
  */
void Delay(__IO uint32_t nCount)	
{
	for(; nCount != 0; nCount--);
}




