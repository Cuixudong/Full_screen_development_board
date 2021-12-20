#include "sys.h"
#include "dcmi.h"
#include "lcd.h"
#include "led.h"
#include "ov2640.h"
#include "ucos_ii.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//DCMI ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/14
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//V1.1 20140516
//�޸�DCMI_DMA_Init������֧��˫����ģʽ
//////////////////////////////////////////////////////////////////////////////////

extern void jpeg_data_process(void);	//JPEG���ݴ�����
//DCMI�жϷ�����
void DCMI_IRQHandler(void)
{
    OSIntEnter();
    if(DCMI->MISR&0X01)//����һ֡ͼ��
    {
        jpeg_data_process(); //jpeg���ݴ���
        DCMI->ICR|=1<<0;	//���֡�ж�
    }
    OSIntExit();

}
//DCMI DMA����
//mem0addr:�洢����ַ0  ��Ҫ�洢����ͷ���ݵ��ڴ��ַ(Ҳ�����������ַ)
//mem1addr:�洢����ַ1  ��ֻʹ��mem0addr��ʱ��,��ֵ����Ϊ0
//memsize:�洢������    0~65535
//memblen:�洢��λ��    0,8λ,1,16λ,2,32λ
//meminc:�洢��������ʽ,0,������;1,����
void DCMI_DMA_Init(u32 mem0addr,u32 mem1addr,u16 memsize,u8 memblen,u8 meminc)
{
    RCC->AHB1ENR|=1<<22;		//DMA2ʱ��ʹ��
    while(DMA2_Stream1->CR&0X01);//�ȴ�DMA2_Stream1������
    DMA2->LIFCR|=0X3D<<6*1;		//���ͨ��1�������жϱ�־
    DMA2_Stream1->FCR=0X0000021;//����ΪĬ��ֵ

    DMA2_Stream1->PAR=(u32)&DCMI->DR;//�����ַΪ:DCMI->DR
    DMA2_Stream1->M0AR=mem0addr;	//mem0addr��ΪĿ���ַ0
    DMA2_Stream1->M1AR=mem1addr;	//mem1addr��ΪĿ���ַ1
    DMA2_Stream1->NDTR=memsize;		//���䳤��Ϊmemsize
    DMA2_Stream1->CR=0;				//��ȫ����λCR�Ĵ���ֵ
    DMA2_Stream1->CR|=0<<6;			//���赽�洢��ģʽ
    DMA2_Stream1->CR|=1<<8;			//ѭ��ģʽ
    DMA2_Stream1->CR|=0<<9;			//���������ģʽ
    DMA2_Stream1->CR|=meminc<<10;	//�洢������ģʽ
    DMA2_Stream1->CR|=2<<11;		//�������ݳ���:32λ
    DMA2_Stream1->CR|=memblen<<13;	//�洢��λ��,8/16/32bit
    DMA2_Stream1->CR|=2<<16;	//�����ȼ�
    DMA2_Stream1->CR|=0<<21;	//����ͻ�����δ���
    DMA2_Stream1->CR|=0<<23;	//�洢��ͻ�����δ���
    DMA2_Stream1->CR|=1<<25;	//ͨ��1 DCMIͨ��
    if(mem1addr)//˫�����ʱ��,����Ҫ����
    {
        DMA2_Stream1->CR|=1<<18;				//˫����ģʽ
        DMA2_Stream1->CR|=1<<4;					//������������ж�
        MY_NVIC_Init(0,0,DMA2_Stream1_IRQn,2);	//��ռ1�������ȼ�3����2
    }
}
void (*dcmi_rx_callback)(void);//DCMI DMA���ջص�����
//DMA2_Stream1�жϷ�����(��˫����ģʽ���õ�)
void DMA2_Stream1_IRQHandler(void)
{
    OSIntEnter();
    if(DMA2->LISR&(1<<11))	//DMA2_Steam1,������ɱ�־
    {
        DMA2->LIFCR|=1<<11;	//�����������ж�
        dcmi_rx_callback();	//ִ������ͷ���ջص�����,��ȡ���ݵȲ����������洦��
    }
    OSIntExit();
}
//DCMI��ʼ��
void DCMI_Init(void)
{
    //����IO
    RCC->AHB1ENR|=1<<0;		//ʹ������PORTAʱ��
    RCC->AHB1ENR|=1<<1;		//ʹ������PORTBʱ��
    RCC->AHB1ENR|=1<<2;		//ʹ������PORTCʱ��
    RCC->AHB1ENR|=1<<4;		//ʹ������PORTEʱ��
    RCC->AHB2ENR|=1<<0;		//��DCMIʱ��

    GPIO_Set(GPIOA,PIN4|PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PA4/6   ���ù������
    GPIO_Set(GPIOB,PIN6|PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PB6/7   ���ù������
    GPIO_Set(GPIOC,PIN6|PIN7|PIN8|PIN9|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//PC6/7/8/9/11 ���ù������
    GPIO_Set(GPIOE,PIN5|PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PE5/6  ���ù������

    GPIO_AF_Set(GPIOA,4,13);	//PA4,AF13  DCMI_HSYNC
    GPIO_AF_Set(GPIOA,6,13);	//PA6,AF13  DCMI_PCLK
    GPIO_AF_Set(GPIOB,7,13);	//PB7,AF13  DCMI_VSYNC
    GPIO_AF_Set(GPIOC,6,13);	//PC6,AF13  DCMI_D0
    GPIO_AF_Set(GPIOC,7,13);	//PC7,AF13  DCMI_D1
    GPIO_AF_Set(GPIOC,8,13);	//PC8,AF13  DCMI_D2
    GPIO_AF_Set(GPIOC,9,13);	//PC9,AF13  DCMI_D3
    GPIO_AF_Set(GPIOC,11,13);	//PC11,AF13 DCMI_D4
    GPIO_AF_Set(GPIOB,6,13);	//PB6,AF13  DCMI_D5
    GPIO_AF_Set(GPIOE,5,13);	//PE5,AF13  DCMI_D6
    GPIO_AF_Set(GPIOE,6,13);	//PE6,AF13  DCMI_D7
    //���ԭ��������
    DCMI->CR=0x0;
    DCMI->IER=0x0;
    DCMI->ICR=0x1F;
    DCMI->ESCR=0x0;
    DCMI->ESUR=0x0;
    DCMI->CWSTRTR=0x0;
    DCMI->CWSIZER=0x0;

    DCMI->CR|=0<<1;		//����ģʽ
    DCMI->CR|=0<<2;		//ȫ֡����
    DCMI->CR|=0<<4;		//Ӳ��ͬ��HSYNC,VSYNC
    DCMI->CR|=1<<5;		//PCLK ��������Ч
    DCMI->CR|=0<<6;		//HSYNC �͵�ƽ��Ч
    DCMI->CR|=0<<7;		//VSYNC �͵�ƽ��Ч
    DCMI->CR|=0<<8;		//�������е�֡
    DCMI->CR|=0<<10; 	//8λ���ݸ�ʽ
    DCMI->IER|=1<<0; 	//����֡�ж�
    DCMI->CR|=1<<14; 	//DCMIʹ��
    MY_NVIC_Init(0,0,DCMI_IRQn,2);	//��ռ1�������ȼ�2����2
}
//DCMI,��������
void DCMI_Start(void)
{
    LCD_SetCursor(0,0);
    LCD_WriteRAM_Prepare();		//��ʼд��GRAM
    DMA2_Stream1->CR|=1<<0;		//����DMA2,Stream1
    DCMI->CR|=1<<0; 			//DCMI����ʹ��
}
//DCMI,�رմ���
void DCMI_Stop(void)
{
    u32 i=0;
    DCMI->CR&=~(1<<0); 			//DCMI����ر�
    while(DCMI->CR&0X01)		//�ȴ��������
    {
        i++;
        if(i>0X7FFFFF)break;
    }
    DMA2_Stream1->CR&=~(1<<0);	//�ر�DMA2,Stream1
}
////////////////////////////////////////////////////////////////////////////////
//������������,��usmart����,���ڵ��Դ���

//DCMI������ʾ����
//sx,sy;LCD����ʼ����
//width,height:LCD��ʾ��Χ.
void DCMI_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{
    DCMI_Stop();
    LCD_Clear(WHITE);
    LCD_Set_Window(sx,sy,width,height);
    OV2640_OutSize_Set(width,height);
    LCD_SetCursor(0,0);
    LCD_WriteRAM_Prepare();		//��ʼд��GRAM
    DMA2_Stream1->CR|=1<<0;		//����DMA2,Stream1
    DCMI->CR|=1<<0; 			//DCMI����ʹ��
}

//ͨ��usmart����,����������.
//pclk/hsync/vsync:�����źŵ����޵�ƽ����
void DCMI_CR_Set(u8 pclk,u8 hsync,u8 vsync)
{
    DCMI->CR=0;
    DCMI->CR|=pclk<<5;		//PCLK ��Ч��������
    DCMI->CR|=hsync<<6;		//HSYNC ��Ч��ƽ����
    DCMI->CR|=vsync<<7;		//VSYNC ��Ч��ƽ����
    DCMI->CR|=1<<14; 		//DCMIʹ��
    DCMI->CR|=1<<0; 		//DCMI����ʹ��
}








