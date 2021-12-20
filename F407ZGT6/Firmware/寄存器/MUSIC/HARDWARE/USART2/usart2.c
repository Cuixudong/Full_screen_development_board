#include "sys.h"
#include "usart2.h"	  
//////////////////////////////////////////////////////////////////////////////////	   
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����2��ʼ�� 
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/5/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//��
////////////////////////////////////////////////////////////////////////////////// 	

//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������ 
void usart2_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV,OVER8����Ϊ0
	mantissa=temp;				 			//�õ���������
	fraction=(temp-mantissa)*16; 			//�õ�С������,OVER8����Ϊ0	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->AHB1ENR|=1<<0;   					//ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<17;  					//ʹ�ܴ���2ʱ�� 
	GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
 	GPIO_AF_Set(GPIOA,2,7);					//PA2,AF7
	GPIO_AF_Set(GPIOA,3,7);		 			//PA3,AF7  	   
	//����������
 	USART2->BRR=mantissa; 	// ����������	 
	USART2->CR1|=1<<3;  	//���ڷ���ʹ��  
	USART2->CR1|=1<<13;  	//����ʹ��
}






