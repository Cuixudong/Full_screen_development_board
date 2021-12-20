#include "i2s.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//I2S ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/24
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//******************************************************************************** 
//V1.1 20141220  
//����I2S2_SampleRate_Set����ODDλ���õ�bug 	
////////////////////////////////////////////////////////////////////////////////// 	
 

//I2S2��ʼ��
//std:I2S��׼,00,�����ֱ�׼;01,MSB�����׼(�Ҷ���);10,LSB�����׼(�����);11,PCM��׼
//mode:I2S����ģʽ,00,�ӻ�����;01,�ӻ�����;10,��������;11,��������
//cpol:0,ʱ�ӵ͵�ƽ��Ч;1,ʱ�Ӹߵ�ƽ��Ч
//datalen:���ݳ���,0,16λ��׼;1,16λ��չ(frame=32bit);2,24λ;3,32λ.
void I2S2_Init(u8 std,u8 mode,u8 cpol,u8 datalen)
{ 
	RCC->APB1ENR|=1<<14;	//ʹ��SPI2ʱ��
	RCC->APB1RSTR|=1<<14;	//��λSPI2
	RCC->APB1RSTR&=~(1<<14);//������λ  
	SPI2->I2SCFGR=0;		//ȫ������Ϊ0
	SPI2->I2SPR=0X02;		//��Ƶ�Ĵ���ΪĬ��ֵ
	SPI2->I2SCFGR|=1<<11;	//ѡ��:I2Sģʽ
	SPI2->I2SCFGR|=(u16)mode<<8;//I2S����ģʽ����
	SPI2->I2SCFGR|=std<<4;		//I2S��׼���� 
	SPI2->I2SCFGR|=cpol<<3;		//����ʱ�ӵ�ƽ����
	if(datalen)					//�Ǳ�׼16λ����
	{
		SPI2->I2SCFGR|=1<<0;	//Channel����Ϊ32λ 
		datalen-=1;		
	}else SPI2->I2SCFGR|=0<<0;	//Channel����Ϊ16λ  
	SPI2->I2SCFGR|=datalen<<1;	//I2S��׼���� 
	SPI2->CR2|=1<<1;			//SPI2 TX DMA����ʹ��.
	SPI2->I2SCFGR|=1<<10;		//SPI2 I2S ENʹ��.	
} 
//�����ʼ��㹫ʽ:Fs=I2SxCLK/[256*(2*I2SDIV+ODD)]
//I2SxCLK=(HSE/pllm)*PLLI2SN/PLLI2SR
//һ��HSE=8Mhz 
//pllm:��Sys_Clock_Set���õ�ʱ��ȷ����һ����8
//PLLI2SN:һ����192~432 
//PLLI2SR:2~7
//I2SDIV:2~255
//ODD:0/1
//I2S��Ƶϵ����@pllm=8,HSE=8Mhz,��vco����Ƶ��Ϊ1Mhz
//���ʽ:������/10,PLLI2SN,PLLI2SR,I2SDIV,ODD
const u16 I2S_PSC_TBL[][5]=
{
	{800 ,256,5,12,1},		//8Khz������
	{1102,429,4,19,0},		//11.025Khz������ 
	{1600,213,2,13,0},		//16Khz������
	{2205,429,4, 9,1},		//22.05Khz������
	{3200,213,2, 6,1},		//32Khz������
	{4410,271,2, 6,0},		//44.1Khz������
	{4800,258,3, 3,1},		//48Khz������
	{8820,316,2, 3,1},		//88.2Khz������
	{9600,344,2, 3,1},  	//96Khz������
	{17640,361,2,2,0},  	//176.4Khz������ 
	{19200,393,2,2,0},  	//192Khz������
};  
//����IIS�Ĳ�����(@MCKEN)
//samplerate:������,��λ:Hz
//����ֵ:0,���óɹ�;1,�޷�����.
u8 I2S2_SampleRate_Set(u32 samplerate)
{ 
	u8 i=0; 
	u32 tempreg=0;
	samplerate/=10;//��С10��   
	for(i=0;i<(sizeof(I2S_PSC_TBL)/10);i++)//�����Ĳ������Ƿ����֧��
	{
		if(samplerate==I2S_PSC_TBL[i][0])break;
	}
	RCC->CR&=~(1<<26);						//�ȹر�PLLI2S
	if(i==(sizeof(I2S_PSC_TBL)/10))return 1;//�ѱ���Ҳ�Ҳ���
	tempreg|=(u32)I2S_PSC_TBL[i][1]<<6;		//����PLLI2SN
	tempreg|=(u32)I2S_PSC_TBL[i][2]<<28;	//����PLLI2SR
	RCC->PLLI2SCFGR=tempreg;		//����I2SxCLK��Ƶ��(x=2) 
	RCC->CR|=1<<26;					//����I2Sʱ��
	while((RCC->CR&1<<27)==0);		//�ȴ�I2Sʱ�ӿ����ɹ�. 
	tempreg=I2S_PSC_TBL[i][3]<<0;	//����I2SDIV
	tempreg|=I2S_PSC_TBL[i][4]<<8;	//����ODDλ
	tempreg|=1<<9;					//ʹ��MCKOEλ,���MCK
	SPI2->I2SPR=tempreg;			//����I2SPR�Ĵ��� 
	return 0;
}  
//I2S2 TX DMA����
//����Ϊ˫����ģʽ,������DMA��������ж�
//buf0:M0AR��ַ.
//buf1:M1AR��ַ.
//num:ÿ�δ���������
void I2S2_TX_DMA_Init(u8* buf0,u8 *buf1,u16 num)
{  
	RCC->AHB1ENR|=1<<21;		//DMA1ʱ��ʹ��   
	while(DMA1_Stream4->CR&0X01);//�ȴ�DMA1_Stream4������ 
	DMA1->HIFCR|=0X3D<<6*0;		//���ͨ��4�������жϱ�־
	DMA1_Stream4->FCR=0X0000021;//����ΪĬ��ֵ	
	
	DMA1_Stream4->PAR=(u32)&SPI2->DR;		//�����ַΪ:SPI2->DR
	DMA1_Stream4->M0AR=(u32)buf0;//�ڴ�1��ַ
	DMA1_Stream4->M1AR=(u32)buf1;//�ڴ�2��ַ
	DMA1_Stream4->NDTR=num;		//��ʱ���ó���Ϊ1
	DMA1_Stream4->CR=0;			//��ȫ����λCR�Ĵ���ֵ  
	DMA1_Stream4->CR|=1<<6;		//�洢��������ģʽ 
	DMA1_Stream4->CR|=1<<8;		//ѭ��ģʽ
	DMA1_Stream4->CR|=0<<9;		//���������ģʽ
	DMA1_Stream4->CR|=1<<10;	//�洢������ģʽ
	DMA1_Stream4->CR|=1<<11;	//�������ݳ���:16λ
	DMA1_Stream4->CR|=1<<13;	//�洢�����ݳ���:16λ
	DMA1_Stream4->CR|=2<<16;	//�����ȼ�
	DMA1_Stream4->CR|=1<<18;	//˫����ģʽ
	DMA1_Stream4->CR|=0<<21;	//����ͻ�����δ���
	DMA1_Stream4->CR|=0<<23;	//�洢��ͻ�����δ���
	DMA1_Stream4->CR|=0<<25;	//ѡ��ͨ��0 SPI2_TXͨ�� 

	DMA1_Stream4->FCR&=~(1<<2);	//��ʹ��FIFOģʽ
	DMA1_Stream4->FCR&=~(3<<0);	//��FIFO ����
	
	DMA1_Stream4->CR|=1<<4;		//������������ж�
	MY_NVIC_Init(0,0,DMA1_Stream4_IRQn,2);	//��ռ1�������ȼ�0����2  
}  
//I2S DMA�ص�����ָ��
void (*i2s_tx_callback)(void);	//TX�ص����� 
//DMA1_Stream4�жϷ�����
void DMA1_Stream4_IRQHandler(void)
{      
	if(DMA1->HISR&(1<<5))	//DMA1_Steam4,������ɱ�־
	{ 
		DMA1->HIFCR|=1<<5;	//�����������ж�
      	i2s_tx_callback();	//ִ�лص�����,��ȡ���ݵȲ����������洦��  
	}   											 
}  
//I2S��ʼ����
void I2S_Play_Start(void)
{   	  
	DMA1_Stream4->CR|=1<<0;		//����DMA TX����  		
}
//�ر�I2S����
void I2S_Play_Stop(void)
{   	 
	DMA1_Stream4->CR&=~(1<<0);	//��������	 	 
} 







