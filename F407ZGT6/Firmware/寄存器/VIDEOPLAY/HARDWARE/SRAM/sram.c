#include "sram.h"	  
#include "usart.h"	     
#include "XMRAM.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿSRAM ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/14
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//********************************************************************************
//V1.1 20140729
//1,�޸�FSMC_SRAM_Init����,��ֹ��λ���ʼ������SRAM����.
////////////////////////////////////////////////////////////////////////////////// 	 

//ʹ��NOR/SRAM�� Bank1.sector3,��ַλHADDR[27,26]=10 
//��XM8A51216,��ַ�߷�ΧΪA0~A18

#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))	
 					   
//��ʼ���ⲿSRAM
void FSMC_SRAM_Init(void)
{
	XmRamInit();                //��ʼ��XMRAM 20191024
	delay_us(100);
	
	RCC->AHB1ENR|=0XF<<3;    	//ʹ��PD,PE,PF,PGʱ��  
	RCC->AHB3ENR|=1<<0;     	//ʹ��FSMCʱ��  
	 
 	GPIO_AF_Set(GPIOG,10,12);	//PG10,AF12(CS�ŵ���ǰ��,��ֹ��λ��CS�Ƿ����,�ƻ�ԭ������) 
	
	GPIO_Set(GPIOD,(3<<0)|(3<<4)|(0XFF<<8),GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PD0,1,4,5,8~15 AF OUT
 	GPIO_Set(GPIOE,(3<<0)|(0X1FF<<7),GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);			//PE0,1,7~15,AF OUT
	GPIO_Set(GPIOF,(0X3F<<0)|(0XF<<12),GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); 	 	//PF0~5,12~15
	GPIO_Set(GPIOG,(0X3F<<0)|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	 		//PG0~5,10
 
	
	GPIO_AF_Set(GPIOD,0,12);	//PD0,AF12
 	GPIO_AF_Set(GPIOD,1,12);	//PD1,AF12
 	GPIO_AF_Set(GPIOD,4,12);	//PD4,AF12
 	GPIO_AF_Set(GPIOD,5,12);	//PD5,AF12 
 	GPIO_AF_Set(GPIOD,8,12);	//PD8,AF12
 	GPIO_AF_Set(GPIOD,9,12);	//PD9,AF12
 	GPIO_AF_Set(GPIOD,10,12);	//PD10,AF12 
 	GPIO_AF_Set(GPIOD,11,12);	//PD11,AF12 
 	GPIO_AF_Set(GPIOD,12,12);	//PD12,AF12 
 	GPIO_AF_Set(GPIOD,13,12);	//PD13,AF12 
 	GPIO_AF_Set(GPIOD,14,12);	//PD14,AF12
 	GPIO_AF_Set(GPIOD,15,12);	//PD15,AF12
	
 	GPIO_AF_Set(GPIOE,0,12);	//PE0,AF12
 	GPIO_AF_Set(GPIOE,1,12);	//PE1,AF12
 	GPIO_AF_Set(GPIOE,7,12);	//PE7,AF12
 	GPIO_AF_Set(GPIOE,8,12);	//PE8,AF12
 	GPIO_AF_Set(GPIOE,9,12);	//PE9,AF12
 	GPIO_AF_Set(GPIOE,10,12);	//PE10,AF12
 	GPIO_AF_Set(GPIOE,11,12);	//PE11,AF12
 	GPIO_AF_Set(GPIOE,12,12);	//PE12,AF12
 	GPIO_AF_Set(GPIOE,13,12);	//PE13,AF12
 	GPIO_AF_Set(GPIOE,14,12);	//PE14,AF12
 	GPIO_AF_Set(GPIOE,15,12);	//PE15,AF12
	
 	GPIO_AF_Set(GPIOF,0,12);	//PF0,AF12
 	GPIO_AF_Set(GPIOF,1,12);	//PF1,AF12
 	GPIO_AF_Set(GPIOF,2,12);	//PF2,AF12
 	GPIO_AF_Set(GPIOF,3,12);	//PF3,AF12
 	GPIO_AF_Set(GPIOF,4,12);	//PF4,AF12
 	GPIO_AF_Set(GPIOF,5,12);	//PF5,AF12
 	GPIO_AF_Set(GPIOF,12,12);	//PF12,AF12
 	GPIO_AF_Set(GPIOF,13,12);	//PF13,AF12
 	GPIO_AF_Set(GPIOF,14,12);	//PF14,AF12
 	GPIO_AF_Set(GPIOF,15,12);	//PF15,AF12
	
 	GPIO_AF_Set(GPIOG,0,12);	//PG0,AF12
 	GPIO_AF_Set(GPIOG,1,12);	//PG1,AF12
 	GPIO_AF_Set(GPIOG,2,12);	//PG2,AF12
 	GPIO_AF_Set(GPIOG,3,12);	//PG3,AF12
 	GPIO_AF_Set(GPIOG,4,12);	//PG4,AF12
 	GPIO_AF_Set(GPIOG,5,12);	//PG5,AF12 	
	
	//�Ĵ�������
	//bank1��NE1~4,ÿһ����һ��BCR+TCR�������ܹ��˸��Ĵ�����
	//��������ʹ��NE3 ��Ҳ�Ͷ�ӦBTCR[4],[5]��				    
	FSMC_Bank1->BTCR[4]=0X00000000;
	FSMC_Bank1->BTCR[5]=0X00000000;
	FSMC_Bank1E->BWTR[4]=0X00000000;
	//����BCR�Ĵ���	ʹ���첽ģʽ,ģʽA(��д����һ��ʱ��Ĵ���)
	//BTCR[ż��]:BCR�Ĵ���;BTCR[����]:BTR�Ĵ���
	FSMC_Bank1->BTCR[4]|=1<<12;//�洢��дʹ��
	FSMC_Bank1->BTCR[4]|=1<<4; //�洢�����ݿ��Ϊ16bit 	    
	//����BTR�Ĵ���			��HCLK=168M, 1��HCLK=6ns			    
	FSMC_Bank1->BTCR[5]|=3<<8; //���ݱ���ʱ�䣨DATAST��Ϊ3��HCLK 6*3=18ns	 	 
	FSMC_Bank1->BTCR[5]|=0<<4; //��ַ����ʱ�䣨ADDHLD��δ�õ�	  	 
	FSMC_Bank1->BTCR[5]|=2<<0; //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 12ns	 	

	//����дʱ��Ĵ���  
	FSMC_Bank1E->BWTR[4]=0x0FFFFFFF;//Ĭ��ֵ
	//ʹ��BANK1����3
	FSMC_Bank1->BTCR[4]|=1<<0; 	
} 														  
//��ָ����ַ(WriteAddr+Bank1_SRAM3_ADDR)��ʼ,����д��n���ֽ�.
//pBuffer:�ֽ�ָ��
//WriteAddr:Ҫд��ĵ�ַ
//n:Ҫд����ֽ���
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)  
	{										    
		*(vu8*)(Bank1_SRAM3_ADDR+WriteAddr)=*pBuffer;	  
		WriteAddr++;
		pBuffer++;
	}   
}																			    
//��ָ����ַ((WriteAddr+Bank1_SRAM3_ADDR))��ʼ,��������n���ֽ�.
//pBuffer:�ֽ�ָ��
//ReadAddr:Ҫ��������ʼ��ַ
//n:Ҫд����ֽ���
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)  
	{											    
		*pBuffer++=*(vu8*)(Bank1_SRAM3_ADDR+ReadAddr);    
		ReadAddr++;
	}  
} 
////////////////////////////////////////////////////////////////////////////////////////
//���Ժ���
//��ָ����ַд��1���ֽ�
//addr:��ַ(0~SRAM��С)
//data:Ҫд�������
void fsmc_sram_test_write(u32 addr,u8 data)
{			   
	FSMC_SRAM_WriteBuffer(&data,addr,1);//д��1���ֽ�
}
//��ȡ1���ֽ�
//addr:Ҫ��ȡ�ĵ�ַ(0~SRAM��С)
//����ֵ:��ȡ��������
u8 fsmc_sram_test_read(u32 addr)
{
	u8 data;
	FSMC_SRAM_ReadBuffer(&data,addr,1);
	return data;
}
