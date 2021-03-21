#ifndef _BSP_KEY_H 
#define _BSP_KEY_H 

#include "stm32f4xx.h"

#define KEY_ON      1
#define KEY_OFF      0

void KEY_GPIO_Config(void);
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

/*引脚定义*/
/************************************************************/
/*按键 1*/
#define KEY1_PIN                  GPIO_Pin_4 
#define KEY1_GPIO_PORT            GPIOE                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOE

/*按键 2*/
#define KEY2_PIN                  GPIO_Pin_5 
#define KEY2_GPIO_PORT            GPIOE                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOE

/*按键 3*/
#define KEY3_PIN                  GPIO_Pin_6 
#define KEY3_GPIO_PORT            GPIOE                      
#define KEY3_GPIO_CLK             RCC_AHB1Periph_GPIOE

/*按键 4*/
#define KEY4_PIN                  GPIO_Pin_13 
#define KEY4_GPIO_PORT            GPIOC                      
#define KEY4_GPIO_CLK             RCC_AHB1Periph_GPIOC
/************************************************************/

void Delay(__IO uint32_t nCount);			//延时函数

void LED_water(void);				//流水灯

uint8_t KEY_Scan_down(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin); 		//按键长按扫描

uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);		//按键扫描



#endif  /* _BSP_KEY_H */


