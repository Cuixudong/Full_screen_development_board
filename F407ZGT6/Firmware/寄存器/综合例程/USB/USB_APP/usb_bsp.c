#include "usb_bsp.h" 
#include "sys.h"  
#include "delay.h" 
#include "usart.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//USB-BSP ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   

//USB������Դ���ƿ�
#define USB_HOST_PWRCTRL 	PAout(15)	//PA15


  
//USB OTG �ײ�IO��ʼ��
//pdev:USB OTG�ں˽ṹ��ָ��
void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev)
{
	RCC->AHB1ENR|=1<<0;    		//ʹ��PORTAʱ��	    
 	RCC->AHB2ENR|=1<<7;    		//ʹ��USB OTGʱ��	    
	GPIO_Set(GPIOA,3<<11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_NONE);	//PA11/12���ù������	
	GPIO_Set(GPIOA,PIN15,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_NONE);	//PA15�������	
  	USB_HOST_PWRCTRL=1;			//����USB HOST��Դ����
  	GPIO_AF_Set(GPIOA,11,10);	//PA11,AF10(USB)
 	GPIO_AF_Set(GPIOA,12,10);	//PA12,AF10(USB)
}
//USB OTG �ж�����,����USB FS�ж�
//pdev:USB OTG�ں˽ṹ��ָ��
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{
  	MY_NVIC_Init(0,3,OTG_FS_IRQn,2);	//���ȼ�����Ϊ��ռ0,�����ȼ�3����2	 
}
//USB OTG �ж�����,����USB FS�ж�
//pdev:USB OTG�ں˽ṹ��ָ��
void USB_OTG_BSP_DisableInterrupt(void)
{ 
}
//USB OTG �˿ڹ�������(������δ�õ�)
//pdev:USB OTG�ں˽ṹ��ָ��
//state:0,�ϵ�;1,�ϵ�
void USB_OTG_BSP_DriveVBUS(USB_OTG_CORE_HANDLE *pdev, uint8_t state)
{ 
}
//USB_OTG �˿ڹ���IO����(������δ�õ�)
//pdev:USB OTG�ں˽ṹ��ָ��
void  USB_OTG_BSP_ConfigVBUS(USB_OTG_CORE_HANDLE *pdev)
{ 
} 
//USB_OTG us����ʱ����
//�����̲���SYSTEM�ļ��е�delay.c�����delay_us����ʵ��
//�ٷ����̲��õ��Ƕ�ʱ��2��ʵ�ֵ�.
//usec:Ҫ��ʱ��us��.
void USB_OTG_BSP_uDelay (const uint32_t usec)
{ 
   	delay_us(usec);
}
//USB_OTG ms����ʱ����
//�����̲���SYSTEM�ļ��е�delay.c�����delay_ms����ʵ��
//�ٷ����̲��õ��Ƕ�ʱ��2��ʵ�ֵ�.
//msec:Ҫ��ʱ��ms��.
void USB_OTG_BSP_mDelay (const uint32_t msec)
{  
	delay_ms(msec);
}
   




