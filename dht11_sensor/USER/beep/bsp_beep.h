#ifndef __BEEP_H
#define	__BEEP_H

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/

#define BEEP1_PIN                 GPIO_Pin_10                 
#define BEEP1_GPIO_PORT           GPIOB                       
#define BEEP1_GPIO_CLK            RCC_AHB1Periph_GPIOB

/*******************************************************/

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 {p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//�����ת״̬

/* �������IO�ĺ� */
#define BEEP1_TOGGLE	digitalToggle(BEEP1_GPIO_PORT,BEEP1_PIN)
#define BEEP1_ON			digitalHi(BEEP1_GPIO_PORT,BEEP1_PIN)
#define BEEP1_OFF			digitalLo(BEEP1_GPIO_PORT,BEEP1_PIN)

void BEEP_Init(void); //��������ʼ��



#endif /* __LED_H */

