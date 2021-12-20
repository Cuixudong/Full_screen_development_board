#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//SPI ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ
//SPI�ڳ�ʼ��
//�������Ƕ�SPI1�ĳ�ʼ��
void SPI1_Init(void)
{
    u16 tempreg=0;
    RCC->AHB1ENR|=1<<0;    	//ʹ��PORTAʱ��
    RCC->APB2ENR|=1<<12;   	//SPI1ʱ��ʹ��
    GPIO_Set(GPIOA,PIN5|PIN6|PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);
    GPIO_AF_Set(GPIOA,5,5);
    GPIO_AF_Set(GPIOA,6,5);
    GPIO_AF_Set(GPIOA,7,5);

    //����ֻ���SPI�ڳ�ʼ��
    RCC->APB2RSTR|=1<<12;	//��λSPI1
    RCC->APB2RSTR&=~(1<<12);//ֹͣ��λSPI1
    tempreg|=0<<10;			//ȫ˫��ģʽ
    tempreg|=1<<9;			//���nss����
    tempreg|=1<<8;
    tempreg|=1<<2;			//SPI����
    tempreg|=0<<11;			//8λ���ݸ�ʽ
    tempreg|=1<<1;			//����ģʽ��SCKΪ1 CPOL=1
    tempreg|=1<<0;			//���ݲ����ӵ�2��ʱ����ؿ�ʼ,CPHA=1
    //��SPI1����APB2������.ʱ��Ƶ�����Ϊ84MhzƵ��.
    tempreg|=7<<3;			//Fsck=Fpclk1/256
    tempreg|=0<<7;			//MSB First
    tempreg|=1<<6;			//SPI����
    SPI1->CR1=tempreg; 		//����CR1
    SPI1->I2SCFGR&=~(1<<11);//ѡ��SPIģʽ
    SPI1_ReadWriteByte(0xff);//��������
}
//SPI1�ٶ����ú���
//SpeedSet:0~7
//SPI�ٶ�=fAPB2/2^(SpeedSet+1)
//fAPB2ʱ��һ��Ϊ84Mhz
void SPI1_SetSpeed(u8 SpeedSet)
{
    SpeedSet&=0X07;			//���Ʒ�Χ
    SPI1->CR1&=0XFFC7;
    SPI1->CR1|=SpeedSet<<3;	//����SPI1�ٶ�
    SPI1->CR1|=1<<6; 		//SPI�豸ʹ��
}
//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{
    while((SPI1->SR&1<<1)==0);		//�ȴ���������
    SPI1->DR=TxData;	 	  		//����һ��byte
    while((SPI1->SR&1<<0)==0);		//�ȴ�������һ��byte
    return SPI1->DR;          		//�����յ�������
}








