#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
									  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
#define DHT11_IO_IN()  {GPIOA->MODER&=~(3<<(3*2));GPIOA->MODER|=0<<3*2;}	//PA3����ģʽ
#define DHT11_IO_OUT() {GPIOA->MODER&=~(3<<(3*2));GPIOA->MODER|=1<<3*2;} 	//PA3���ģʽ 
////IO��������											   
#define	DHT11_DQ_OUT PAout(3) //���ݶ˿�	PA3 
#define	DHT11_DQ_IN  PAin(3)  //���ݶ˿�	PA3

u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11   
void dht11_show(void);//��ӡ��ʪ����Ϣ
u8 dhtll_hum_alarm(void);//���ʪ���Ƿ񳬱�
u8 dhtll_temp_alarm(void);//����¶��Ƿ񳬱�
#endif















