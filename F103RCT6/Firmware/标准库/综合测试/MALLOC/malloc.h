#ifndef __MALLOC_H
#define __MALLOC_H
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32������
//�ڴ���� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////


 
#ifndef NULL
#define NULL 0
#endif

//�ڴ�����趨.
#define MEM_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM_MAX_SIZE			35*1024  						//�������ڴ� 35K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//�ڴ���С
 
		 
//�ڴ���������
struct _m_mallco_dev
{
	void (*init)(void);				//��ʼ��
	uint8_t (*perused)(void);		  	//�ڴ�ʹ����
	uint8_t 	*membase;					//�ڴ�� 
	uint16_t *memmap; 					//�ڴ����״̬��
	uint8_t  memrdy; 					//�ڴ�����Ƿ����
};
extern struct _m_mallco_dev mallco_dev;	//��mallco.c���涨��

void mymemset(void *s,uint8_t c,uint32_t count);	//�����ڴ�
void mymemcpy(void *des,void *src,uint32_t n);//�����ڴ�     
void mem_init(void);					 //�ڴ�����ʼ������(��/�ڲ�����)
uint32_t mem_malloc(uint32_t size);		 		//�ڴ����(�ڲ�����)
uint8_t mem_free(uint32_t offset);		 		//�ڴ��ͷ�(�ڲ�����)
uint8_t mem_perused(void);					//���ڴ�ʹ����(��/�ڲ�����) 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void myfree(void *ptr);  				//�ڴ��ͷ�(�ⲿ����)
void *mymalloc(uint32_t size);				//�ڴ����(�ⲿ����)
void *myrealloc(void *ptr,uint32_t size);	//���·����ڴ�(�ⲿ����)
#endif













