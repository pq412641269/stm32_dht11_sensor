#ifndef __BEEP_H
#define	__BEEP_H

#include "stm32f4xx.h"

//引脚定义
/*******************************************************/

#define BEEP1_PIN                 GPIO_Pin_10                 
#define BEEP1_GPIO_PORT           GPIOB                       
#define BEEP1_GPIO_CLK            RCC_AHB1Periph_GPIOB

/*******************************************************/

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define BEEP1_TOGGLE	digitalToggle(BEEP1_GPIO_PORT,BEEP1_PIN)
#define BEEP1_ON			digitalHi(BEEP1_GPIO_PORT,BEEP1_PIN)
#define BEEP1_OFF			digitalLo(BEEP1_GPIO_PORT,BEEP1_PIN)

void BEEP_Init(void); //蜂鸣器初始化



#endif /* __LED_H */

