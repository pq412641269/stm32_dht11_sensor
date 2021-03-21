/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ledӦ�ú����ӿ�
  */
  
#include "./led/bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|
	                           LED2_GPIO_CLK|
	                           LED3_GPIO_CLK, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = LED1_PIN;	

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*������������Ϊ2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = LED3_PIN;	
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	
		
		/*�ر�RGB��*/
		LED_RGBOFF;		
}





/*********************************************END OF FILE**********************/
 /**
  * @brief  ����LED
  * @param  ��
  * @retval ��
  */
extern u16 led_flag;

void led_show(void)
{
	if(led_flag == 0)
	{
		LED1_ON
	}
	if(led_flag == 25)
	{
		LED1_OFF
	}
	if(led_flag == 50)
	{
		LED1_ON
	}
	if(led_flag == 75)
	{
		LED1_OFF
	}
	if(led_flag == 100)
	{
		LED1_ON
	}
	if(led_flag == 200)
	{
		LED1_OFF
	}
	if(led_flag > 300)
	{
		led_flag = 0;
	}
}



/**
  * @brief  ����LED
  * @param  ��
  * @retval ��
  */

extern u16 led1_flag;

void led1_show(void)
{
	if(led1_flag == 0)
	{
		LED3_ON
	}
	if(led1_flag == 25)
	{
		LED3_OFF
	}
	if(led1_flag == 50)
	{
		LED3_ON
	}
	if(led1_flag == 75)
	{
		LED3_OFF
	}
	if(led1_flag == 100)
	{
		LED3_ON
	}
	if(led1_flag == 125)
	{
		LED3_OFF
	}
	if(led1_flag > 150)
	{
		led1_flag = 0;
	}
}



