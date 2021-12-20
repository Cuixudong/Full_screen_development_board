#ifndef __GUIX_H
#define __GUIX_H 	
#include "sys.h"
#include "malloc.h"
#include "lcd.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//GUI-�ײ�ʵ�� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/2/18
//�汾��V1.2
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140218
//����gui_draw_bline����
//V1.2 20140801
//1,�޸�gui_show_ptchar��gui_show_ptfont����,֧��24*24���壨������#��*��֧�ָ�������壩
//2,�޸�gui_show_ptchar��gui_show_ptfont������offset����Ϊuint16_t. 
//////////////////////////////////////////////////////////////////////////////////


 
//�õ�ucos�ĵδ�ʱ��
typedef unsigned int   INT32U;	 
extern volatile  INT32U  OSTime;
//guiʱ�������,��Ҫ���ⲿʵ��
//gui��ʱ��,ÿ10ms����1��
#define GUI_TIMER_10MS	OSTime/2 	//ucos�ĵ���ʱ������Ϊ5ms 

#define GUI_VERSION		200			//gui�汾(������100��),100��ʾV1.00
//////////////////////////////////////////////////////////////////////////////////////////////
//GUI֧�ֵ�����������Ŀ
//ϵͳ����������
#define GUI_LANGUAGE_NUM	   	3			//����������
											//0,��������
											//1,��������
											//2,Ӣ��

extern uint8_t*const GUI_OK_CAPTION_TBL[GUI_LANGUAGE_NUM]; 			//ȷ�ϰ�ť
extern uint8_t*const GUI_OPTION_CAPTION_TBL[GUI_LANGUAGE_NUM];		//ѡ�ť
extern uint8_t*const GUI_BACK_CAPTION_TBL[GUI_LANGUAGE_NUM];		//ȡ����ť
extern uint8_t*const GUI_CANCEL_CAPTION_TBL[GUI_LANGUAGE_NUM];		//ȡ����ť
extern uint8_t*const GUI_QUIT_CAPTION_TBL[GUI_LANGUAGE_NUM];		//�˳���ť	 
////////////////////////////////////////////////////////////////////////////////////////////////////////
//gui��ɫ����
#define GUI_COLOR_BLACK 0X0000
#define GUI_COLOR_WHITE 0XFFFF


//�����¼�����
#define	IN_TYPE_TOUCH	0X00
#define IN_TYPE_KEY		0X01
#define IN_TYPE_JOYPAD  0X02
#define IN_TYPE_MOUSE	0X03
#define IN_TYPE_ERR	 	0XFF

//gui����ӿ�
__packed typedef struct 
{
	void (*get_key)(void*,uint8_t);	//��ȡ��ֵ����
	uint16_t x;						//����
	uint16_t y;			
	uint32_t keyval;					//������ֵ
	uint8_t  intype;					//��������
	uint8_t 	ksta;					//�����豸(����)��״̬ [7:1],����;[0],0,�ɿ�;1,����.
}_in_obj;
extern _in_obj in_obj;

//gui�ײ�ӿ�
//Ҳ�����ⲿ��Ҫʵ�ֵĺ���!
//����������Ҫ�ⲿ�ṩ4������
//1,���㺯��;
//2,���㺯��;
//3,��ɫ��亯��;
//4,��ɫ��亯��
__packed typedef struct 
{
	uint8_t language;							//GUI��ǰ����,ȡֵ��Χ0~GUI_LANGUAGE_NUM-1;
	uint16_t memdevflag;							//�洢�豸״̬;
											//bit7:0,�洢�豸7~0��λ״̬;0,����λ;1,��λ;
											//bit15:8,�洢�豸7~0ʹ��״̬;0,����ʹ����;1,����ʹ����
											//������,�洢�豸0��ʾ:SD��
											//              1��ʾ:SPI FLASH
											//              2��ʾ:U��
											//����,δ�õ�
	//���ĸ�����,�����listbox/filelistbox�ȿؼ��ľ���Ч��
	uint8_t tbfsize;								//filelistbox/listboxʱ,����/�ײ����������С
	uint8_t tbheight;							//filelistbox/listboxʱ,����/�ײ������߶�
	uint8_t listfsize;							//list�����С
	uint8_t listheight;							//list��Ŀ�߶�
	
	uint16_t back_color;							//����ɫ		   
	uint16_t(*read_point)(uint16_t,uint16_t);				//���㺯��
	void(*draw_point)(uint16_t,uint16_t,uint16_t);			//���㺯��
 	void(*fill)(uint16_t,uint16_t,uint16_t,uint16_t,uint16_t);		//��ɫ��亯�� 	  
 	void(*colorfill)(uint16_t,uint16_t,uint16_t,uint16_t,uint16_t*);	//��ɫ��亯�� 	 
	uint16_t lcdwidth;							//LCD�Ŀ��
	uint16_t lcdheight;							//LCD�ĸ߶�
}_gui_phy;
extern _gui_phy gui_phy;

uint16_t gui_alpha_blend565(uint16_t src,uint16_t dst,uint8_t alpha);						//alpha blending
uint16_t gui_color_chg(uint32_t rgb);												//��ɫת��.��32λɫתΪ16λɫ
uint16_t gui_rgb332torgb565(uint16_t rgb332);										//��rgb332תΪrgb565
long long gui_pow(uint8_t m,uint8_t n);											//�õ�m^n
uint8_t* gui_path_name(uint8_t *pname,uint8_t* path,uint8_t *name);

void gui_memset(void *p,uint8_t c,uint32_t len);
void *gui_memin_malloc(uint32_t size);
void gui_memin_free(void* ptr);
void *gui_memex_malloc(uint32_t size);			
void gui_memex_free(void* ptr);		 
void *gui_memin_realloc(void *ptr,uint32_t size);

void gui_init(void);
void gui_get_key(void* obj,uint8_t type);									 
uint32_t gui_disabs(uint32_t x1,uint32_t x2);											//��ľ���ֵ
void gui_alphablend_area(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color,uint8_t aval);
void gui_draw_bigpoint(uint16_t x0,uint16_t y0,uint16_t color);						//�����
void gui_draw_line(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color);				//��������
void gui_draw_bline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint8_t size,uint16_t color);	//��һ������
void gui_draw_bline1(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint8_t size,uint16_t color);	//��һ������,����1
void gui_draw_rectangle(uint16_t x0,uint16_t y0,uint16_t width,uint16_t height,uint16_t color);	//������
void gui_draw_arcrectangle(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t r,uint8_t mode,uint16_t upcolor,uint16_t downcolor);//��Բ�Ǿ���
void gui_draw_vline(uint16_t x0,uint16_t y0,uint16_t len,uint16_t color);								//����ֱ��
void gui_draw_hline(uint16_t x0,uint16_t y0,uint16_t len,uint16_t color);								//��ˮƽ��
void gui_fill_colorblock(uint16_t x0,uint16_t y0,uint16_t width,uint16_t height,uint16_t* ctbl,uint8_t mode);		//�����ɫ��
void gui_smooth_color(uint32_t srgb,uint32_t ergb,uint16_t*cbuf,uint16_t len);							//��ɫƽ������
void gui_draw_smooth_rectangle(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint32_t srgb,uint32_t ergb);	//����ɫƽ�����ɵľ���/����
void gui_fill_rectangle(uint16_t x0,uint16_t y0,uint16_t width,uint16_t height,uint16_t color);				//�������
void gui_fill_circle(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color);
void gui_draw_ellipse(uint16_t x0, uint16_t y0, uint16_t rx, uint16_t ry,uint16_t color);
void gui_fill_ellipse(uint16_t x0,uint16_t y0,uint16_t rx,uint16_t ry,uint16_t color);
void gui_draw_argrec(uint16_t x0,uint16_t y0,uint16_t width,uint16_t height,uint16_t color);
void gui_show_strmid(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color,uint8_t size,uint8_t *str);
void gui_show_ptchar(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint16_t size,uint8_t chr,uint8_t mode);
void gui_show_ptfont(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint16_t size,uint8_t* chr,uint8_t mode);
void gui_show_ptstr(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint8_t size,uint8_t *str,uint8_t mode);
void gui_show_ptstrwhiterim(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint16_t rimcolor,uint8_t size,uint8_t *str);//��Ч��ʾ�ַ���
void gui_draw_icos(uint16_t x,uint16_t y,uint8_t size,uint8_t index);
void gui_draw_icosalpha(uint16_t x,uint16_t y,uint8_t size,uint8_t index);
void gui_show_num(uint16_t x,uint16_t y,uint8_t len,uint16_t color,uint8_t size,long long num,uint8_t mode);
uint8_t* gui_num2str(uint8_t*str,uint32_t num);//������תΪ�ַ���
void gui_draw_arc(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t rx,uint16_t ry,uint16_t r,uint16_t color,uint8_t mode);

uint32_t gui_get_stringline(uint8_t*str,uint16_t linelenth,uint8_t font);
void gui_show_string(uint8_t*str,uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t font,uint16_t fcolor);
uint16_t gui_string_forwardgbk_count(uint8_t *str,uint16_t pos);


#endif



























