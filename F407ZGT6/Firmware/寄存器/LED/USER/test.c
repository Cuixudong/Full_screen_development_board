#include "sys.h"
#include "delay.h" 
#include "led.h"
//ALIENTEK ̽����STM32F407������ ʵ��1
//�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
  
int main(void)
{ 
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz
	delay_init(168);		//��ʼ����ʱ����
	LED_Init();				//��ʼ��LEDʱ��  
	while(1)
	{
		LED0=0;				//DS0��
		LED1=1;				//DS1��
		delay_ms(500);
		LED0=1;				//DS0��
		LED1=0;				//DS1��
		delay_ms(500);
	}
}

















