#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
   	   		   
//IO��������
#define SDA_IN()  {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=8<<16;}
#define SDA_OUT() {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=3<<16;}

//IO��������	 
#define IIC_SCL    PCout(11) //SCL
#define IIC_SDA    PCout(12) //SDA	 
#define READ_SDA   PCin(12)  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















