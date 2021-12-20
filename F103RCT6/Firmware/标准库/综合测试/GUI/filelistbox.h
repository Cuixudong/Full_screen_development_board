#ifndef __FILELISTBOX_H
#define __FILELISTBOX_H 
#include "guix.h"  	 			  
#include "scrollbar.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//GUI-�ļ��б�� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2012/10/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************
//����˵�� 
//V1.1 20140715
//1,�޸Ĺ�����������,ʹ�ø�����
//2,ȥ��FLBOX_PATH_HEIGHT�Ⱥ궨��,���ñ�����ʽ����(��gui_phy�ṹ����������)
//////////////////////////////////////////////////////////////////////////////////

//�ļ�ͼ�궨��
#define FICO_DISK				0  			//����
#define FICO_FOLDER		 		1			//�ļ���
#define FICO_UNKNOW				2			//δ֪�ļ�
#define FICO_BIN				3			//BIN�ļ�
#define FICO_LRC				4			//LRC�ļ�
#define FICO_NES				5			//NES�ļ�
#define FICO_TEXT				6			//�ı��ļ�
#define FICO_MUSIC				7			//�����ļ�
#define FICO_PICTURE			8			//ͼƬ�ļ�
#define FICO_VIDEO				9			//��Ƶ�ļ�

//�ļ���������λ���ܶ���
#define FLBOX_FLT_BIN 			1<<0		//BIN�ļ�
#define FLBOX_FLT_LRC	 		1<<1		//LRC�ļ�
#define FLBOX_FLT_NES	 		1<<2		//NES�ļ�
#define FLBOX_FLT_TEXT	 		1<<3		//�ı��ļ�
#define FLBOX_FLT_MUSIC	 		1<<4		//�����ļ�
#define FLBOX_FLT_PICTURE 		1<<5		//ͼƬ�ļ�
#define FLBOX_FLT_VIDEO			1<<6		//��Ƶ�ļ�
#define FLBOX_FLT_UNKNOW		1<<15		//�޷�ʶ���һ���ļ�

//////filelistbox�ϵķ��ŵ�Ĭ����ɫ 
#define FLBOX_DFT_LBKCOLOR		0XFFFF		//�ڲ�����ɫ
#define FLBOX_DFT_LSELCOLOR		0XFFFF		//ѡ��list���������ɫ
#define FLBOX_DFT_LSELBKCOLOR	0X001F		//0X07E0		//ѡ��list��ı���ɫ
#define FLBOX_DFT_LNCOLOR		0X0000		//δѡ�е�list������ɫ
#define FLBOX_DFT_RIMCOLOR		0XF800		//�߿���ɫ
#define FLBOX_DFT_PTHINFBKCOLOR	0XCE7E		//·��/��Ϣ���ı�����ɫ


//filelistbox�ļ��洢��ȶ���,���������������,�����ټ�����һ����ѡ��Ŀ��λ��.
#define FLBOX_PATH_DEPTH		0X0A		//�ļ�·�����
//filelistbox�����ļ�����������Ŀ���ļ�������Ŀ
#define FLBOX_MAX_DFFILE 		2000		//ʹ��12*12������ 2K��,�������ļ��е�ʱ��,��Ҫռ��2K*2���ڴ�

//�̶���߶ȶ���
#define FLBOX_SCB_WIDTH 		0X0E		//���������Ϊ15������ 
//filelist�ṹ��.����ṹ
__packed typedef struct 
{
	void * prevlist;
	void * nextlist;
	uint8_t type;		//�ļ�����
	uint8_t *name;		//�ļ�����
}_filelistbox_list;

//filelistbox�ṹ�嶨��		  
__packed typedef struct 
{
	uint16_t top; 				  		//filelistbox��������
	uint16_t left;                       //filelistbox�������
	uint16_t width; 				  		//���
	uint16_t height;						//�߶� ����Ϊ12/16�ı���,����б߿�,�ڱ��������ϼ�2

	uint8_t type;						//���ͱ����
									//[bit7]:1,��Ҫ������������(������totalitems>itemsperpage);0,����Ҫ������.(��λ������Զ�����)
									//[bit6:0]:�ļ�����					 
								
	uint8_t sta;							//filelistbox״̬,[bit7]:������־;[bit6]:�����Ч�ı�־;[bit5:0]:��һ�ΰ��µı��.	 
	uint8_t id;							//filelistbox ��id
	uint8_t dbclick;					   	//˫��,
									//[7]:0,û��˫��.1,��˫��.
									//[0]:0,��Ŀ���ļ�(���ļ���/����).1,Ŀ���ļ�(���ļ���/����)

	uint8_t font;						//�������� 12/16
	uint16_t selindex;					//ѡ�е����� 0<selindex<foldercnt+filecnt;

	uint16_t foldercnt;					//�ļ�����Ŀ
	uint16_t filecnt;					//�ļ���Ŀ
	
	uint8_t icosize;						//icoͼ���С 16/20/28��
 
	uint16_t lbkcolor;					//�ڲ�������ɫ
 	uint16_t lnselcolor; 				//list name ѡ�к����ɫ
  	uint16_t lnselbkcolor; 				//list name ѡ�к�ı�����ɫ
	uint16_t lncolor; 					//list name δѡ�е���ɫ
	uint16_t rimcolor;					//�߿���ɫ
	uint16_t pthinfbkcolor;			    //·��/��Ϣ���ı�����ɫ

	uint8_t* path;						//��Ŀ¼·��
	//uint8_t  seltblindex;				//��ǰ��Ŀ¼����
	uint16_t seltbl[FLBOX_PATH_DEPTH];	//ѡ�е���Ŀ�б�,FLBOX_PATH_DEPTHΪ���
	uint16_t fliter;						//�ļ�������,�������
									//ˢѡ�������Ķ���
	uint16_t fliterex;					//�ļ���չ�Ĺ�����
									//����ѡ����������С��,���֧��16�ֲ�ͬ���ļ�.Ĭ��0XFFFF,������С�����ˢѡ.

	uint8_t memdevflag;					//������λ״̬(�����Ա�ʾ8������)
									//bit7:0,�洢�豸7~0��λ״̬;0,����λ;1,��λ;
									//������,�洢�豸0��ʾ:SD��
									//              1��ʾ:SPI FLASH
									//              2��ʾ:U��
//////////////////////
	uint8_t *fname;						//��ǰѡ�е�index������
	uint16_t namelen;					//name��ռ�ĵ���.
	uint16_t curnamepos;					//��ǰ��ƫ��
	uint32_t oldtime;					//��һ�θ���ʱ�� 

    //����ֻ��Ŀ���ļ����(�����ļ���)
 	uint16_t *findextbl;    				//Ŀ���ļ���������	

	_scrollbar_obj * scbv;			//��ֱ������
	_filelistbox_list *list; 		//����	    
}_filelistbox_obj;


_filelistbox_obj * filelistbox_creat(uint16_t left,uint16_t top,uint16_t width,uint16_t height,uint8_t type,uint8_t font);//����filelistbox
_filelistbox_list * filelist_search(_filelistbox_list *filelistx,uint16_t index);		//���ұ��Ϊindex��list,��ȡ����ϸ��Ϣ
void filelist_delete(_filelistbox_obj * filelistbox);						//ɾ��filelist����
void filelistbox_delete(_filelistbox_obj *filelistbox_del);	 				//ɾ��filelistbox
uint8_t filelistbox_rebuild_filelist(_filelistbox_obj * filelistbox);			//�ؽ�filelistbox
uint8_t filelistbox_check(_filelistbox_obj * filelistbox,void * in_key);			//���filelistbox�İ���״̬
uint8_t filelistbox_addlist(_filelistbox_obj * filelistbox,uint8_t *name,uint8_t type);	//����һ��filelist
void filelistbox_draw_list(_filelistbox_obj *filelistbox);					//��filelist
void filelistbox_draw_listbox(_filelistbox_obj *filelistbox);				//��filelistbox
void filelistbox_show_path(_filelistbox_obj *filelistbox); 					//��ʾ·��
void filelistbox_show_info(_filelistbox_obj *filelistbox);
uint8_t   filelistbox_scan_filelist(_filelistbox_obj *filelistbox);
void filelistbox_add_disk(_filelistbox_obj *filelistbox);
void filelistbox_check_filelist(_filelistbox_obj *filelistbox);
void filelistbox_back(_filelistbox_obj *filelistbox);
void filelistbox_2click_hook(_filelistbox_obj *filelistbox);				//˫�����Ӻ���
#endif





