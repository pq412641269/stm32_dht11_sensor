#include "dht11.h"
#include "delay.h"
#include "stdio.h"
//////////////////////////////////////////////////////////////////////////////////	 
								  
//////////////////////////////////////////////////////////////////////////////////
    
//复位DHT11
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT
  DHT11_DQ_OUT=0; 	//拉低DQ
  delay_ms(20);    	//拉低至少18ms
  DHT11_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     	//主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT11_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOG时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	DHT11_Rst();
	return DHT11_Check();
}


/**
  * @brief  打印温湿度值
  * @param  无
  * @retval 无
  */
u8 temperature;  	    
u8 humidity; 

void dht11_show(void)
{
	DHT11_Read_Data(&temperature,&humidity);//读取温湿度值	
	printf("		温湿度数据\r\n");	
	printf("----------------------------------------------\r\n");	
	printf("\r\n");
	printf("温度:%d °C ( 正常范围 : 5 °C ~ 25 °C )\r\n",temperature); 
	printf("\r\n");	
	printf("湿度:%d %%rh ( 正常范围 : 20%% rh ~ 80%% rh )\r\n",humidity);
	printf("\r\n");
	printf("----------------------------------------------\r\n");
	printf("\r\n");
}


/**
  * @brief  判断温度是否异常
  * @param  无
  * @retval 正常返回0 异常返回1
  */

u8 dhtll_temp_alarm(void)
{
	DHT11_Read_Data(&temperature,&humidity);
	if(temperature > 25 || temperature < 5)
	{
		printf("		温度度数据异常!\r\n");
		printf("----------------------------------------------\r\n");
		printf("\r\n");
		printf("温度超标:%d °C ( 正常范围 : 5 °C ~ 25 °C )\r\n",temperature);
		printf("\r\n");
		printf("----------------------------------------------\r\n");
		printf("\r\n");
		return 1;
	}

	return 0;
}


/**
  * @brief  判断湿度是否异常
  * @param  无
  * @retval 正常返回0 异常返回1
  */

u8 dhtll_hum_alarm(void)
{
	DHT11_Read_Data(&temperature,&humidity);
	if(humidity > 80 || humidity < 20)
	{
		printf("		湿度数据异常!\r\n");
		printf("----------------------------------------------\r\n");
		printf("\r\n");
		printf("湿度超标:%d %% rh ( 正常范围 : 20%% rh ~ 80%% rh )\r\n",humidity);
		printf("\r\n");
		printf("----------------------------------------------\r\n");
		printf("\r\n");
		return 1;
	}
	return 0;
}




















