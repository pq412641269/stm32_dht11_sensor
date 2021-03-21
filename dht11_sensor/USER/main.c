#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "dht11.h"
#include "./led/bsp_led.h"  
#include "./BASICTIM/bsp_basic_tim.h" 
#include "./RTC/bsp_rtc.h"
#include "./key/bsp_key.h"
#include "./beep/bsp_beep.h" 


int main(void)
{ 
	u8 flag = 1;
	u8 alarm_flag = 1; 
	extern u16 show_flag;
	extern u16 dhtll_flag;
	extern u16 beep_flag;
	u8 led1_open = 0;
	u8 led2_open = 0;

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	TIMx_Configuration();
	LED_GPIO_Config();					//��ʼ��LED 
	KEY_GPIO_Config();
	BEEP_Init();
	rtc_init();
	
 	while(DHT11_Init())	//DHT11��ʼ��	
	{
		printf("DHT11 Error\n");
		delay_ms(200);
	}								   

	while(1)
	{	
		if(!KEY_Scan(KEY1_GPIO_PORT,KEY1_PIN))  //�رմ������ݷ���
		{
			flag = 0;
		}
		if(!KEY_Scan(KEY2_GPIO_PORT,KEY2_PIN))	//�򿪴������ݷ���
		{
			flag = 1;
		}
		if(!KEY_Scan(KEY3_GPIO_PORT,KEY3_PIN))  //�ر���ʪ�ȼ��
		{
			alarm_flag = 0;
		}
		if(!KEY_Scan(KEY4_GPIO_PORT,KEY4_PIN))	//����ʪ�ȼ��
		{
			alarm_flag = 1;
		}
		
	
		if(show_flag >= 200) 		
		{
			if(check_time() && flag)		//�жϴ����Ƿ�ʼ�������� flag ��ť���ƿ���  check_time() �ж�ʱ���Ƿ񵽴�˵�
			{
				RTC_TimeAndDate_Show();	//����ϵͳʱ�䵽����
				dht11_show();						//������ʪ����������
			}
			else
			{
				printf("������Ϣ�У�\r\n");	
			}
			show_flag = 0;
	  }
		
		if(dhtll_flag >= 200 && flag && alarm_flag && check_time())			
		{
			if(dhtll_hum_alarm())		//�ж�ʪ���Ƿ񳬱�
			{
				led1_open = 1;				//����led3 
			}
			else
			{
				led1_open = 0;		//�ر�led3 ��ˮ��
			}
			
			if(dhtll_temp_alarm())			//�ж�ʪ���Ƿ񳬱�
			{
				led2_open = 1;			//����led 1 ��˸ 2�� 1��
			}
			else
			{
				led2_open = 0;		//�ر�led 1
			}
			dhtll_flag = 0;
		}
		
		if(led1_open && alarm_flag && flag)  	//led 3 ��˸ 3��
		{
			led1_show();
		}
		else
		{
			LED3_OFF;
		}
		
		if(led2_open && alarm_flag && flag)  	//led 1 ��˸ 2�� 1��
		{
			led_show();
		}		
		else
		{
			LED1_OFF;
		}
	}
}






