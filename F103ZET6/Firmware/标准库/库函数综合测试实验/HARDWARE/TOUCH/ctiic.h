#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//4.3��/7����ݴ���������-IICͨ�Ų���
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//IO��������
#define CT_SDA_IN()  {GPIOC->CRL&=0XFFF0FFFF;GPIOC->CRL|=8<<(4*4);}
#define CT_SDA_OUT() {GPIOC->CRL&=0XFFF0FFFF;GPIOC->CRL|=3<<(4*4);}

//IO��������
#define CT_IIC_SCL    PCout(5) 			//SCL C5 T_SCK    
#define CT_IIC_SDA    PCout(4) 			//SDA C4
#define CT_READ_SDA   PCin(4)  			//����SDA 

//IIC���в�������
void CT_IIC_Init(void);                	//��ʼ��IIC��IO��
void CT_IIC_Start(void);				//����IIC��ʼ�ź�
void CT_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CT_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 CT_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CT_IIC_Ack(void);					//IIC����ACK�ź�
void CT_IIC_NAck(void);					//IIC������ACK�ź�

#endif







