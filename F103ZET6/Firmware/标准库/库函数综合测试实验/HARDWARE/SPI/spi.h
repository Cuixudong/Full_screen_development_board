#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//SPI���� ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/15
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//����˵��
//20150120  V1.1
//����SPI1��ʼ����غ���������SPI1_Init��SPI1_SetSpeed��SPI1_ReadWriteByte��
//////////////////////////////////////////////////////////////////////////////////


void SPI2_Init(void);			 //��ʼ��SPI2��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI2�ٶ�
u8 SPI2_ReadWriteByte(u8 TxData);//SPI2���߶�дһ���ֽ�
void SPI1_Init(void);			 //��ʼ��SPI1��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�
#endif

