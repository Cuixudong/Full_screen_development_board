#ifndef __EXFUNS_H
#define __EXFUNS_H 			   
#include <stm32f10x.h>
#include "ff.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//FATFS ��չ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/18
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1�޸�˵�� 20140318
//����exf_copy��exf_get_src_dname��exf_fdsize��exf_fdcopy�Ⱥ���
//////////////////////////////////////////////////////////////////////////////////	 

extern FATFS *fs[2];  
extern FIL *file;	 
extern FIL *ftemp;	 
extern UINT br,bw;
extern FILINFO fileinfo;
extern DIR dir;
extern uint8_t *fatbuf;//SD�����ݻ�����


//f_typetell���ص����Ͷ���
//���ݱ�FILE_TYPE_TBL���.��exfuns.c���涨��
#define T_BIN		0X00	//bin�ļ�
#define T_LRC		0X10	//lrc�ļ�
#define T_NES		0X20	//nes�ļ�
#define T_TEXT		0X30	//.txt�ļ�
#define T_C			0X31	//.c�ļ�
#define T_H			0X32    //.h�ļ�
#define T_FLAC		0X4C	//flac�ļ�
#define T_BMP		0X50	//bmp�ļ�
#define T_JPG		0X51	//jpg�ļ�
#define T_JPEG		0X52	//jpeg�ļ�		 
#define T_GIF		0X53	//gif�ļ�  

 
uint8_t exfuns_init(void);							//�����ڴ�
uint8_t f_typetell(uint8_t *fname);						//ʶ���ļ�����
uint8_t exf_getfree(uint8_t *drv,uint32_t *total,uint32_t *free);	//�õ�������������ʣ������
uint32_t exf_fdsize(uint8_t *fdname);						//�õ��ļ��д�С			 																		   
uint8_t exf_copy(uint8_t(*fcpymsg)(uint8_t*pname,uint8_t pct,uint8_t mode),uint8_t *psrc,uint8_t *pdst,uint32_t totsize,uint32_t cpdsize,uint8_t fwmode);
uint8_t* exf_get_src_dname(uint8_t* dpfn);
uint32_t exf_fdsize(uint8_t *fdname);
uint8_t exf_fdcopy(uint8_t(*fcpymsg)(uint8_t*pname,uint8_t pct,uint8_t mode),uint8_t *psrc,uint8_t *pdst,uint32_t *totsize,uint32_t *cpdsize,uint8_t fwmode);
#endif


