#ifndef _BSP_KEY_H 
#define _BSP_KEY_H 

#include "stm32f4xx.h"

#define KEY_ON      1
#define KEY_OFF      0

void KEY_GPIO_Config(void);
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

/*���Ŷ���*/
/************************************************************/
/*���� 1*/
#define KEY1_PIN                  GPIO_Pin_4 
#define KEY1_GPIO_PORT            GPIOE                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOE

/*���� 2*/
#define KEY2_PIN                  GPIO_Pin_5 
#define KEY2_GPIO_PORT            GPIOE                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOE

/*���� 3*/
#define KEY3_PIN                  GPIO_Pin_6 
#define KEY3_GPIO_PORT            GPIOE                      
#define KEY3_GPIO_CLK             RCC_AHB1Periph_GPIOE

/*���� 4*/
#define KEY4_PIN                  GPIO_Pin_13 
#define KEY4_GPIO_PORT            GPIOC                      
#define KEY4_GPIO_CLK             RCC_AHB1Periph_GPIOC
/************************************************************/

void Delay(__IO uint32_t nCount);			//��ʱ����

void LED_water(void);				//��ˮ��

uint8_t KEY_Scan_down(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin); 		//��������ɨ��

uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);		//����ɨ��



#endif  /* _BSP_KEY_H */


