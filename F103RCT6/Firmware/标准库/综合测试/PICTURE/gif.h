#ifndef __GIF_H__
#define __GIF_H__
#include "sys.h"    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ͼƬ���� ��������-gif���벿��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//����˵�� 
//��
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////�û�������//////////////////////////////////
#define GIF_USE_MALLOC		1 	//�����Ƿ�ʹ��malloc,��������ѡ��ʹ��malloc	     
//////////////////////////////////////////////END/////////////////////////////////////


#define LCD_MAX_LOG_COLORS  256 
#define MAX_NUM_LWZ_BITS 	12


#define GIF_INTRO_TERMINATOR ';'	//0X3B   GIF�ļ�������
#define GIF_INTRO_EXTENSION  '!'    //0X21
#define GIF_INTRO_IMAGE      ','	//0X2C

#define GIF_COMMENT     	0xFE
#define GIF_APPLICATION 	0xFF
#define GIF_PLAINTEXT   	0x01
#define GIF_GRAPHICCTL  	0xF9

typedef struct
{
	uint8_t    aBuffer[258];                     // Input buffer for data block 
	short aCode  [(1 << MAX_NUM_LWZ_BITS)]; // This array stores the LZW codes for the compressed strings 
	uint8_t    aPrefix[(1 << MAX_NUM_LWZ_BITS)]; // Prefix character of the LZW code.
	uint8_t    aDecompBuffer[3000];              // Decompression buffer. The higher the compression, the more bytes are needed in the buffer.
	uint8_t *  sp;                               // Pointer into the decompression buffer 
	int   CurBit;
	int   LastBit;
	int   GetDone;
	int   LastByte;
	int   ReturnClear;
	int   CodeSize;
	int   SetCodeSize;
	int   MaxCode;
	int   MaxCodeSize;
	int   ClearCode;
	int   EndCode;
	int   FirstCode;
	int   OldCode;
}LZW_INFO;

//�߼���Ļ������
__packed typedef struct
{
	uint16_t width;		//GIF���
	uint16_t height;		//GIF�߶�
	uint8_t flag;		//��ʶ��  1:3:1:3=ȫ����ɫ���־(1):��ɫ���(3):�����־(1):ȫ����ɫ���С(3)
	uint8_t bkcindex;	//����ɫ��ȫ����ɫ���е�����(��������ȫ����ɫ��ʱ��Ч)
	uint8_t pixratio;	//���ؿ�߱�
}LogicalScreenDescriptor;


//ͼ��������
__packed typedef struct
{
	uint16_t xoff;		//x����ƫ��
	uint16_t yoff;		//y����ƫ��
	uint16_t width;		//���
	uint16_t height;		//�߶�
	uint8_t flag;		//��ʶ��  1:1:1:2:3=�ֲ���ɫ���־(1):��֯��־(1):����(2):�ֲ���ɫ���С(3)
}ImageScreenDescriptor;

//ͼ������
__packed typedef struct
{
	LogicalScreenDescriptor gifLSD;	//�߼���Ļ������
	ImageScreenDescriptor gifISD;	//ͼ��������
	uint16_t colortbl[256];				//��ǰʹ����ɫ��
	uint16_t bkpcolortbl[256];			//������ɫ��.�����ھֲ���ɫ��ʱʹ��
	uint16_t numcolors;					//��ɫ���С
	uint16_t delay;					    //�ӳ�ʱ��
	LZW_INFO *lzw;					//LZW��Ϣ
}gif89a;

extern uint8_t gifdecoding;	//GIF���ڽ�����.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t gif_check_head(FIL *file);														    //���GIFͷ
uint16_t gif_getrgb565(uint8_t *ctb);																//��RGB888תΪRGB565
uint8_t gif_readcolortbl(FIL *file,gif89a * gif,uint16_t num);									//��ȡ��ɫ��
uint8_t gif_getinfo(FIL *file,gif89a * gif);												    //�õ��߼���Ļ����,ͼ��ߴ��
void gif_savegctbl(gif89a* gif);														//����ȫ����ɫ��
void gif_recovergctbl(gif89a* gif);														//�ָ�ȫ����ɫ��
void gif_initlzw(gif89a* gif,uint8_t codesize);												//��ʼ��LZW��ز���
uint16_t gif_getdatablock(FIL *gfile,uint8_t *buf,uint16_t maxnum);								   	//��ȡһ�����ݿ�
uint8_t gif_readextension(FIL *gfile,gif89a* gif, int *pTransIndex,uint8_t *pDisposal);		   	//��ȡ��չ����
int gif_getnextcode(FIL *gfile,gif89a* gif);										   	//��LZW�����еõ���һ��LZW��,ÿ�������12λ
int gif_getnextbyte(FIL *gfile,gif89a* gif);											//�õ�LZW����һ����
uint8_t gif_dispimage(FIL *gfile,gif89a* gif,uint16_t x0,uint16_t y0,int Transparency, uint8_t Disposal);	//��ʾͼƬ
void gif_clear2bkcolor(uint16_t x,uint16_t y,gif89a* gif,ImageScreenDescriptor pimge);		   	//�ָ��ɱ���ɫ
uint8_t gif_drawimage(FIL *gfile,gif89a* gif,uint16_t x0,uint16_t y0);									//��GIFͼ���һ֡

uint8_t gif_decode(const uint8_t *filename,uint16_t x,uint16_t y,uint16_t width,uint16_t height);//��ָ���������һ��GIF�ļ�.
void gif_quit(void);									//�˳���ǰ����.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
