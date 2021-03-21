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

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	TIMx_Configuration();
	LED_GPIO_Config();					//初始化LED 
	KEY_GPIO_Config();
	BEEP_Init();
	rtc_init();
	
 	while(DHT11_Init())	//DHT11初始化	
	{
		printf("DHT11 Error\n");
		delay_ms(200);
	}								   

	while(1)
	{	
		if(!KEY_Scan(KEY1_GPIO_PORT,KEY1_PIN))  //关闭串口数据发送
		{
			flag = 0;
		}
		if(!KEY_Scan(KEY2_GPIO_PORT,KEY2_PIN))	//打开串口数据发送
		{
			flag = 1;
		}
		if(!KEY_Scan(KEY3_GPIO_PORT,KEY3_PIN))  //关闭温湿度检测
		{
			alarm_flag = 0;
		}
		if(!KEY_Scan(KEY4_GPIO_PORT,KEY4_PIN))	//打开温湿度检测
		{
			alarm_flag = 1;
		}
		
	
		if(show_flag >= 200) 		
		{
			if(check_time() && flag)		//判断串口是否开始发送数据 flag 按钮控制开关  check_time() 判段时间是否到达八点
			{
				RTC_TimeAndDate_Show();	//发送系统时间到串口
				dht11_show();						//发送温湿度数到串口
			}
			else
			{
				printf("串口休息中！\r\n");	
			}
			show_flag = 0;
	  }
		
		if(dhtll_flag >= 200 && flag && alarm_flag && check_time())			
		{
			if(dhtll_hum_alarm())		//判断湿度是否超标
			{
				led1_open = 1;				//开启led3 
			}
			else
			{
				led1_open = 0;		//关闭led3 流水灯
			}
			
			if(dhtll_temp_alarm())			//判断湿度是否超标
			{
				led2_open = 1;			//开启led 1 闪烁 2短 1长
			}
			else
			{
				led2_open = 0;		//关闭led 1
			}
			dhtll_flag = 0;
		}
		
		if(led1_open && alarm_flag && flag)  	//led 3 闪烁 3短
		{
			led1_show();
		}
		else
		{
			LED3_OFF;
		}
		
		if(led2_open && alarm_flag && flag)  	//led 1 闪烁 2短 1长
		{
			led_show();
		}		
		else
		{
			LED1_OFF;
		}
	}
}






