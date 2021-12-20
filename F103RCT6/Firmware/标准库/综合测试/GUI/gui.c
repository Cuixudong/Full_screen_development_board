#include "guix.h"
#include "touch.h"
#include "text.h"	
#include "icos.h"							 
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

//�˴��������ⲿ����asc2_1206��asc2_1608;
//#include "font.h" 
extern const unsigned char asc2_1206[95][12];
extern const unsigned char asc2_1608[95][16];
extern const unsigned char asc2_2412[95][36];

extern uint8_t* asc2_2814;	//��ͨ����28*14���������
extern uint8_t* asc2_3618;	//��ͨ����36*18���������
extern uint8_t* asc2_5427;	//��ͨ����54*27���������
extern uint8_t* asc2_s6030;	//���������60*30���������

////////////////////////////GUIͨ���ַ�����//////////////////////////////
//ȷ��
uint8_t*const GUI_OK_CAPTION_TBL[GUI_LANGUAGE_NUM]=
{
	"ȷ��","�_��","OK",
};
//ѡ��
uint8_t*const GUI_OPTION_CAPTION_TBL[GUI_LANGUAGE_NUM]=
{
	"ѡ��","�x�","MENU",
};
//����
uint8_t*const GUI_BACK_CAPTION_TBL[GUI_LANGUAGE_NUM]=
{
	"����","����","BACK",
};
//ȡ�� 
uint8_t*const GUI_CANCEL_CAPTION_TBL[GUI_LANGUAGE_NUM]=
{
	"ȡ��","ȡ��","CANCEL",
};
//�˳�
uint8_t*const GUI_QUIT_CAPTION_TBL[GUI_LANGUAGE_NUM]=
{
	"�˳�","�˳�","QUIT",		    
};
///////////////////////////////////////////////////////////////////////////
	   
//����ӿ�
_in_obj in_obj=
{
 	gui_get_key,		//��ȡ��ֵ����
	0,					//����
	0,			
	0,					//������ֵ
	IN_TYPE_ERR,		//��������,Ĭ�Ͼ��Ǵ����״̬
};
_gui_phy gui_phy;		//gui�����ӿ�
//////////////////////////ͳһ��׼����//////////////////////////////
//���㺯��
//x0,y0:����
//color:��ɫ
void _gui_draw_point(uint16_t x0,uint16_t y0,uint16_t color)
{
	uint16_t tempcolor=POINT_COLOR;
	POINT_COLOR=color;
	LCD_DrawPoint(x0,y0);
	POINT_COLOR=tempcolor;
}

////////////////////////////////////////////////////////////////////
//gui��ʼ��
void gui_init(void)
{
	gui_phy.read_point=LCD_ReadPoint;
	gui_phy.draw_point=LCD_Fast_DrawPoint;//���ٻ���
	gui_phy.fill=LCD_Fill;		 
	gui_phy.colorfill=LCD_Color_Fill;		 
	gui_phy.back_color=BACK_COLOR;		 
	gui_phy.lcdwidth=lcddev.width;
	gui_phy.lcdheight=lcddev.height; 
	//����listbox/filelistbox����
	if(lcddev.width==240)
	{
		gui_phy.tbfsize=16;
		gui_phy.tbheight=20;
		gui_phy.listfsize=12;
		gui_phy.listheight=20;
	}else if(lcddev.width==320)	
	{
		gui_phy.tbfsize=16;
		gui_phy.tbheight=24;
		gui_phy.listfsize=16;
		gui_phy.listheight=24;
	}else if(lcddev.width==480)
	{
		gui_phy.tbfsize=24;
		gui_phy.tbheight=32;
		gui_phy.listfsize=24;
		gui_phy.listheight=32;
	}
}   
//��ȡ��ֵ����
void gui_get_key(void* obj,uint8_t type)
{
	_m_tp_dev * tp_dev;		 
	switch(type)
	{
		case IN_TYPE_TOUCH:
			in_obj.intype=IN_TYPE_TOUCH;
			tp_dev=(_m_tp_dev*)obj;
		    in_obj.x=tp_dev->x[0];		 			//�õ���������
 		    in_obj.y=tp_dev->y[0];
			if(tp_dev->sta&0X80)in_obj.ksta|=0X01;	//����������
			else in_obj.ksta&=~(0X01);				//�����ɿ��� 
			break;
		case IN_TYPE_KEY:
			in_obj.keyval=(uint32_t)obj;
			in_obj.intype=IN_TYPE_KEY;
			break;
		case IN_TYPE_JOYPAD:
			in_obj.intype=IN_TYPE_JOYPAD;
			//break;
		case IN_TYPE_MOUSE:
			in_obj.intype=IN_TYPE_MOUSE;
			//break;
		default:
			in_obj.intype=IN_TYPE_ERR;
			break;
		
	}	   
}
//��ɫת��
//rgb:32λ��ɫ
//����ֵ:16λɫ.
uint16_t gui_color_chg(uint32_t rgb)
{
	uint16_t r,g,b;
	r=rgb>>19;
	g=(rgb>>10)&0x3f;
	b=(rgb>>3)&0x1f;
	return ((r<<11)|(g<<5)|b);   
}
//��rgb332��ɫת��Ϊrgb565.
//rgb332:rgb332��ʽ����
//����ֵ:rgb565��ʽ����.
uint16_t gui_rgb332torgb565(uint16_t rgb332)
{
	uint16_t rgb565=0x18E7;
	rgb565|=(rgb332&0x03)<<3;
	rgb565|=(rgb332&0x1c)<<6;
	rgb565|=(rgb332&0xe0)<<8;
	return rgb565;
}
//m^n����
long long gui_pow(uint8_t m,uint8_t n)
{
	long long result=1;	 
	while(n--)result*=m;    
	return result;
}
//�������Ĳ�ľ���ֵ
uint32_t gui_disabs(uint32_t x1,uint32_t x2)
{
	return x1>x2 ? x1-x2:x2-x1;	    
}   
//��ָ���������alphablend
//x,y,width,height:��������
//color:alphablend����ɫ
//aval:͸����(0~32)
void gui_alphablend_area(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color,uint8_t aval)
{
	uint16_t i,j;
	uint16_t tempcolor;
	for(i=0;i<width;i++)
	{
		for(j=0;j<height;j++)
		{
			tempcolor=gui_phy.read_point(x+i,y+j);
			tempcolor=gui_alpha_blend565(tempcolor,color,aval);
			gui_phy.draw_point(x+i,y+j,tempcolor);
		}
	}
}

//����㺯��
//x0,y0:����
//color:��ɫ
//��(x0,y0)Ϊ����,��һ��9����Ĵ��
void gui_draw_bigpoint(uint16_t x0,uint16_t y0,uint16_t color)
{
	uint16_t i,j;
	uint16_t x,y;				    
	if(x0>=1)x=x0-1;
	else x=x0;
	if(y0>=1)y=y0-1;
	else y=y0;
	for(i=y;i<y0+2;i++)
	{
		for(j=x;j<x0+2;j++)gui_phy.draw_point(j,i,color);
	}  						   
}
//��������
//x0,y0:��� x1,y1:�յ�
//color:��ɫ
void gui_draw_line(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x1-x0; //������������ 
	delta_y=y1-y0; 
	uRow=x0; 
	uCol=y0; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		gui_phy.draw_point(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 				 
}
//��һ������(����0)
//(x1,y1),(x2,y2):��������ֹ����
//size�������Ĵ�ϸ�̶�
//color����������ɫ
void gui_draw_bline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint8_t size,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return;
	if(size==0){gui_phy.draw_point(x1,y1,color);return;} 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		gui_fill_circle(uRow,uCol,size,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance){xerr-=distance;uRow+=incx;}  
		if(yerr>distance){yerr-=distance;uCol+=incy;}
	}  
} 

//��һ������(����1)
//x0,y0:��� x1,y1:�յ�
//size:�ߴ�ϸ,��֧��:0~2.
//color:��ɫ
void gui_draw_bline1(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint8_t size,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x1-x0; //������������ 
	delta_y=y1-y0; 
	uRow=x0; 
	uCol=y0; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		if(size==0)LCD_Fast_DrawPoint(uRow,uCol,color);//���� 
		if(size==1)
		{
			LCD_Fast_DrawPoint(uRow,uCol,color);//���� 
			LCD_Fast_DrawPoint(uRow+1,uCol,color);//���� 
			LCD_Fast_DrawPoint(uRow,uCol+1,color);//���� 
			LCD_Fast_DrawPoint(uRow+1,uCol+1,color);//���� 
		}
		if(size==2)
		{
			LCD_Fast_DrawPoint(uRow,uCol,color);//���� 
			LCD_Fast_DrawPoint(uRow+1,uCol,color);//���� 
			LCD_Fast_DrawPoint(uRow,uCol+1,color);//���� 
			LCD_Fast_DrawPoint(uRow+1,uCol+1,color);//���� 
			LCD_Fast_DrawPoint(uRow-1,uCol+1,color);//���� 
			LCD_Fast_DrawPoint(uRow+1,uCol-1,color);//����
			LCD_Fast_DrawPoint(uRow-1,uCol-1,color);//����  
			LCD_Fast_DrawPoint(uRow-1,uCol,color);//���� 
			LCD_Fast_DrawPoint(uRow,uCol-1,color);//����  
		}
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 				 
}
//����ֱ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_vline(uint16_t x0,uint16_t y0,uint16_t len,uint16_t color)
{
	if((len==0)||(x0>gui_phy.lcdwidth)||(y0>gui_phy.lcdheight))return;
	gui_phy.fill(x0,y0,x0,y0+len-1,color);	
}
//��ˮƽ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_hline(uint16_t x0,uint16_t y0,uint16_t len,uint16_t color)
{
	if((len==0)||(x0>gui_phy.lcdwidth)||(y0>gui_phy.lcdheight))return;
	gui_phy.fill(x0,y0,x0+len-1,y0,color);	
}
//���һ��ɫ��.
//x0,y0,width,height:���꼰���ߴ�
//ctbl:��ɫ��,�������ʱwidth,�������ʱ��СΪheight
//mode:���ģʽ(����:������,���ϵ������;����:���ϵ���,���������)
//[7:1]:����
//[bit0]:0,����;1,����
void gui_fill_colorblock(uint16_t x0,uint16_t y0,uint16_t width,uint16_t height,uint16_t* ctbl,uint8_t mode)
{
	uint16_t i;
	if(height==0||width==0)return;
	if(mode&0x01)//����
	{
		for(i=0;i<width;i++)
		{
			gui_draw_vline(x0+i,y0,height-1,ctbl[i]);	
		}
	}else
	{
		for(i=0;i<height;i++)
		{
			gui_draw_hline(x0,y0+i,width-1,ctbl[i]);	
		}
	}
}   

//��һ����ɫƽ�����ɵ�����һ����ɫ
//srgb,ergb:��ʼ��ɫ����ֹ��ɫ.
//cbuf:��ɫ������(��len)
//len:���ɼ���(�����������ɫֵ����)
void gui_smooth_color(uint32_t srgb,uint32_t ergb,uint16_t*cbuf,uint16_t len)
{
	uint8_t sr,sg,sb;
	short dr,dg,db;
	uint16_t r,g,b;	  
	uint16_t i=0;
 	sr=srgb>>16;
	sg=(srgb>>8)&0XFF;
	sb=srgb&0XFF;
	dr=(ergb>>16)-sr;
	dg=((ergb>>8)&0XFF)-sg;
	db=(ergb&0XFF)-sb;
 	for(i=0;i<len;i++)
	{
	 	r=sr+(dr*i)/len;
 	 	g=sg+(dg*i)/len;
	 	b=sb+(db*i)/len;
		r>>=3;
		g>>=2;
		b>>=3;
	    cbuf[i]=((r<<11)|(g<<5)|b);		   
	}
}
//��һ��ƽ�����ɵĲ�ɫ����(����)
//x,y,width,height:���ε�����ߴ�
//srgb,ergb:��ʼ����ֹ����ɫ
void gui_draw_smooth_rectangle(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint32_t srgb,uint32_t ergb)
{
	uint16_t i,j;
	uint16_t *colortbl=NULL;
	colortbl=(uint16_t*)gui_memin_malloc(width*2);//�����ڴ�
	if(colortbl==NULL)return ;//�ڴ�����ʧ��
	gui_smooth_color(srgb,ergb,colortbl,width);//�����ɫ��
 	for(i=0;i<width;i++)
	{	 
		for(j=0;j<height;j++)
		{
			gui_phy.draw_point(x+i,y+j,colortbl[i]);//����
		}
	}
	gui_memin_free(colortbl);
}
//������
//x0,y0:���ε����Ͻ�����
//width,height:���εĳߴ�
//color:��ɫ
void gui_draw_rectangle(uint16_t x0,uint16_t y0,uint16_t width,uint16_t height,uint16_t color)
{
	gui_draw_hline(x0,y0,width,color);
	gui_draw_hline(x0,y0+height-1,width,color);
	gui_draw_vline(x0,y0,height,color);
	gui_draw_vline(x0+width-1,y0,height,color);
}
//��Բ�Ǿ���/���Բ�Ǿ���
//x,y,width,height:Բ�Ǿ��ε�λ�úͳߴ�
//r:Բ�ǵİ뾶.
//mode:0,�����ο�;1,������.
//upcolor:�ϰ벿����ɫ
//downcolor:�°벿����ɫ
void gui_draw_arcrectangle(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t r,uint8_t mode,uint16_t upcolor,uint16_t downcolor)
{
	uint16_t btnxh=0;
	if(height%2)btnxh=height+1;//��ż������
	else btnxh=height;
	if(mode)//���
	{
 		gui_fill_rectangle(x+r,y,width-2*r,btnxh/2,upcolor);			//����
  		gui_fill_rectangle(x+r,y+btnxh/2,width-2*r,btnxh/2,downcolor);	//����
		gui_fill_rectangle(x,y+r,r,btnxh/2-r,upcolor);					//����
		gui_fill_rectangle(x,y+btnxh/2,r,btnxh/2-r,downcolor);			//����
		gui_fill_rectangle(x+width-r,y+r,r,btnxh/2-r,upcolor);			//����
		gui_fill_rectangle(x+width-r,y+btnxh/2,r,btnxh/2-r,downcolor);	//����
	}else
	{
		gui_draw_hline (x+r,y,width-2*r,upcolor);					//��		   
		gui_draw_hline (x+r,y+btnxh-1,width-2*r,downcolor);			//��		   
		gui_draw_vline (x,y+r,btnxh/2-r,upcolor);					//����		   
		gui_draw_vline (x,y+btnxh/2,btnxh/2-r,downcolor);			//����		   
		gui_draw_vline (x+width-1,y+r,btnxh/2-r,upcolor);			//����
		gui_draw_vline (x+width-1,y+btnxh/2,btnxh/2-r,downcolor);	//����				   
	}
	gui_draw_arc(x,y,x+r,y+r,x+r,y+r,r,upcolor,mode);//����	
	gui_draw_arc(x,y+btnxh-r,x+r,y+btnxh-1,x+r,y+btnxh-r-1,r,downcolor,mode);//����	
	gui_draw_arc(x+width-r,y,x+width,y+r,x+width-r-1,y+r,r,upcolor,mode);	 //����
	gui_draw_arc(x+width-r,y+btnxh-r,x+width,y+btnxh-1,x+width-r-1,y+btnxh-r-1,r,downcolor,mode);//����
}
//��ico
//x0,y0:���ε����Ͻ�����
//size:icoͼƬ�ߴ�(16/20/28)
//index:icos���
void gui_draw_icos(uint16_t x,uint16_t y,uint8_t size,uint8_t index)
{       
	uint16_t *colorbuf;
	uint16_t i=0;
	uint16_t icosize;
	uint8_t* pico;
	icosize=size*size;
	colorbuf=gui_memin_malloc(2*icosize);//�����ڴ�
	if(colorbuf==NULL)return ; 
	if(size==16)pico=(uint8_t*)icostbl_16[index];
	else if(size==20)pico=(uint8_t*)icostbl_20[index];
	else if(size==28)pico=(uint8_t*)icostbl_28[index];
	if(colorbuf)
	{
		for(i=0;i<icosize;i++)colorbuf[i]=gui_rgb332torgb565(pico[i]);//RGB332ת��ΪRGB565;
 		gui_phy.colorfill(x,y,x+size-1,y+size-1,colorbuf);//����ICOS
 	} 
	gui_memin_free(colorbuf);//�ͷ��ڴ�  	 
	  	   
} 
//������͸����ICO,����16*16��С��.
//x0,y0:���ε����Ͻ�����
//size:icoͼƬ�ߴ�(16/20/28)
//index:icos���
void gui_draw_icosalpha(uint16_t x,uint16_t y,uint8_t size,uint8_t index)
{          
	uint16_t i,j;
	uint8_t *pico;
	uint16_t color;
	uint8_t alphabend;
	if(size==16)pico=(uint8_t*)pathico_16[index];
	else if(size==20)pico=(uint8_t*)pathico_20[index];
	else if(size==28)pico=(uint8_t*)pathico_28[index];	
	for(i=y;i<y+size;i++)
	{
		for(j=x;j<x+size;j++)
		{
			color=(*pico++)>>3;		   		 	//B
			color+=((uint16_t)(*pico++)<<3)&0X07E0;	//G
			color+=(((uint16_t)*pico++)<<8)&0XF800;	//R
			alphabend=*pico++;					//ALPHAͨ��
			if(alphabend==0)//ֻ��͸������ɫ���л�ͼ
			{
				if(color)gui_phy.draw_point(j,i,color);
 			}
		}
 	}   
}
//������
//x0,y0:���ε����Ͻ�����
//width,height:���εĳߴ�
//color:��ɫ
void gui_fill_rectangle(uint16_t x0,uint16_t y0,uint16_t width,uint16_t height,uint16_t color)
{	  							   
	if(width==0||height==0)return;//�Ƿ�.	 
	gui_phy.fill(x0,y0,x0+width-1,y0+height-1,color);	   	   
}
//��ʵ��Բ
//x0,y0:����
//r�뾶
//color:��ɫ
void gui_fill_circle(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color)
{											  
	uint32_t i;
	uint32_t imax = ((uint32_t)r*707)/1000+1;
	uint32_t sqmax = (uint32_t)r*(uint32_t)r+(uint32_t)r/2;
	uint32_t x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax) 
		{
			// draw lines from outside  
			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}
//�������ڻ���
//(sx,sy),(ex,ey):�趨����ʾ��Χ
//(x,y):������
//color:��ɫ
void gui_draw_expoint(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t x,uint16_t y,uint16_t color)	    
{
	uint16_t tempcolor;
	if(x<=ex&&x>=sx&&y<=ey&&y>=sy)
	{
		tempcolor=POINT_COLOR;
		POINT_COLOR=color;
		LCD_DrawPoint(x,y);	    
		POINT_COLOR=tempcolor;
	}
}
//��8��(Bresenham�㷨)		  
//(sx,sy),(ex,ey):�趨����ʾ��Χ
//(rx,ry,a,b):����
//color:��ɫ
void gui_draw_circle8(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t rx,uint16_t ry,int a,int b,uint16_t color)
{
	gui_draw_expoint(sx,sy,ex,ey,rx+a,ry-b,color);              
	gui_draw_expoint(sx,sy,ex,ey,rx+b,ry-a,color);                       
	gui_draw_expoint(sx,sy,ex,ey,rx+b,ry+a,color);                           
	gui_draw_expoint(sx,sy,ex,ey,rx+a,ry+b,color);             
	gui_draw_expoint(sx,sy,ex,ey,rx-a,ry+b,color);                  
	gui_draw_expoint(sx,sy,ex,ey,rx-b,ry+a,color);               
	gui_draw_expoint(sx,sy,ex,ey,rx-b,ry-a,color);                      
	gui_draw_expoint(sx,sy,ex,ey,rx-a,ry-b,color);                  
}	    
//��ָ��λ�û�һ��ָ����С��Բ
//(rx,ry):Բ��
//(sx,sy),(ex,ey):�趨����ʾ��Χ
//r    :�뾶
//color:��ɫ
//mode :0,�����;1,���
void gui_draw_arc(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t rx,uint16_t ry,uint16_t r,uint16_t color,uint8_t mode)
{
	int a,b,c;
	int di;	  
	a=0;b=r;	  
	di=3-(r<<1);	//�ж��¸���λ�õı�־
	while(a<=b)
	{
		if(mode)for(c=a;c<=b;c++)gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,c,color);//��ʵ��Բ
 		else gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,b,color);					   //������Բ
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 							  
	}
}
//����Բ
//x0,y0:����
//rx:x����뾶
//ry:y����뾶
//color:��Բ����ɫ
void gui_draw_ellipse(uint16_t x0, uint16_t y0, uint16_t rx, uint16_t ry,uint16_t color) 
{
	uint32_t OutConst, Sum, SumY;
	uint16_t x,y;
	uint16_t xOld;
	uint32_t _rx = rx;
	uint32_t _ry = ry;
	if(rx>x0||ry>y0)return;//�Ƿ�.
	OutConst = _rx*_rx*_ry*_ry+(_rx*_rx*_ry>>1);  // Constant as explaint above 
	// To compensate for rounding  
	xOld = x = rx;
	for (y=0; y<=ry; y++) 
	{
		if (y==ry)x=0; 
		else 
		{
			SumY =((uint32_t)(rx*rx))*((uint32_t)(y*y)); // Does not change in loop  
			while(Sum = SumY + ((uint32_t)(ry*ry))*((uint32_t)(x*x)),(x>0) && (Sum>OutConst)) x--;
		}
		// Since we draw lines, we can not draw on the first iteration		    
		if (y) 
		{
			gui_draw_line(x0-xOld,y0-y+1,x0-x,y0-y,color);
			gui_draw_line(x0-xOld,y0+y-1,x0-x,y0+y,color);
			gui_draw_line(x0+xOld,y0-y+1,x0+x,y0-y,color);
			gui_draw_line(x0+xOld,y0+y-1,x0+x,y0+y,color);
		}
		xOld = x;
	}
}
//�����Բ
//x0,y0:����
//rx:x����뾶
//ry:y����뾶
//color:��Բ����ɫ
void gui_fill_ellipse(uint16_t x0,uint16_t y0,uint16_t rx,uint16_t ry,uint16_t color) 
{
	uint32_t OutConst, Sum, SumY;
	uint16_t x,y;
	uint32_t _rx = rx;
	uint32_t _ry = ry;
	OutConst = _rx*_rx*_ry*_ry+(_rx*_rx*_ry>>1);  // Constant as explaint above  
	// To compensate for rounding 
	x = rx;
	for (y=0; y<=ry; y++) 
	{
		SumY =((uint32_t)(rx*rx))*((uint32_t)(y*y)); // Does not change in loop  
		while (Sum = SumY + ((uint32_t)(ry*ry))*((uint32_t)(x*x)),(x>0) && (Sum>OutConst))x--;    
		gui_draw_hline(x0-x,y0+y,2*x,color);
		if(y)gui_draw_hline(x0-x,y0-y,2*x,color);    
	}
}
//����ALPHA BLENDING�㷨.
//src:Դ��ɫ
//dst:Ŀ����ɫ
//alpha:͸���̶�(0~32)
//����ֵ:��Ϻ����ɫ.
uint16_t gui_alpha_blend565(uint16_t src,uint16_t dst,uint8_t alpha)
{
	uint32_t src2;
	uint32_t dst2;	 
	//Convert to 32bit |-----GGGGGG-----RRRRR------BBBBB|
	src2=((src<<16)|src)&0x07E0F81F;
	dst2=((dst<<16)|dst)&0x07E0F81F;   
	//Perform blending R:G:B with alpha in range 0..32
	//Note that the reason that alpha may not exceed 32 is that there are only
	//5bits of space between each R:G:B value, any higher value will overflow
	//into the next component and deliver ugly result.
	dst2=((((dst2-src2)*alpha)>>5)+src2)&0x07E0F81F;
	return (dst2>>16)|dst2;  
}  	  
/////////////////////////////////////////////////////////////////////////////////////////////
 
//���м�λ����ʾһ���ַ���
//x,y,width,height:��ʾ��������.
//color:������ɫ.
//size:���ִ�С
//str:�ַ���
void gui_show_strmid(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color,uint8_t size,uint8_t *str)
{
	uint16_t xoff=0,yoff=0;
	uint16_t strlenth;
	uint16_t strwidth;
	if(str==NULL)return;
   	strlenth=strlen((const char*)str);	//�õ��ַ�������
	strwidth=strlenth*size/2;		//�ַ�����ʾռ�ÿ��
	if(height>size)yoff=(height-size)/2;
	if(strwidth<=width)//�ַ���û�������
 	{
		xoff=(width-strwidth)/2;	  
	}
	gui_show_ptstr(x+xoff,y+yoff,x+width-1,y+height-1,0,color,size,str,1);  
}

//��ָ����ַ��ʼ��ʾһ��ASCII�ַ�
//x,y:��ʾ��ʼ����.
//xend,yend:x,y ������յ�����
//offset:��ʼ��ʾ��ƫ��
//color:������ɫ.
//size:���ִ�С
//chr:�ַ�
//mode:0,�ǵ�����ʾ;1,������ʾ.2,������(ֻ�����ڵ���ģʽ)
void gui_show_ptchar(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint16_t size,uint8_t chr,uint8_t mode)
{
    uint8_t temp;
    uint8_t t1,t;
	uint16_t tempoff;
	uint16_t y0=y;		
	uint16_t csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���				     
	if(chr>' ')chr=chr-' ';//�õ�ƫ�ƺ��ֵ
	else chr=0;//С�ڿո��һ���ÿո����,����TAB��(��ֵΪ9)
	for(t=0;t<csize;t++)
	{   
		switch(size)
		{
			case 12:
				temp=asc2_1206[chr][t]; 	//����1206����
				break;
			case 16:
				temp=asc2_1608[chr][t];		//����1608����
				break;
			case 24:
				temp=asc2_2412[chr][t];		//����2412����
				break;
			case 28:
				if(asc2_2814==NULL)return;		//�Ƿ�������
				temp=asc2_2814[chr*csize+t];	//����2814����
				break;
			case 36:
				if(asc2_3618==NULL)return;		//�Ƿ�������
				temp=asc2_3618[chr*csize+t];	//����3618����
				break;
			case 54:
				if(asc2_5427==NULL)return;		//�Ƿ�������
				temp=asc2_5427[chr*csize+t];	//����5427����
				break;
			case 60:
				if(asc2_s6030==NULL)return;		//�Ƿ�������
				temp=asc2_s6030[chr*csize+t];	//����6030����
				break;
			default://��֧�ֵ�����
				return;
		} 
		tempoff=offset;
		if(x>xend)return;	//�������� 	
		if(tempoff==0)	//ƫ�Ƶ�ַ���� 
		{			
			for(t1=0;t1<8;t1++)
			{		    
				if(y<=yend)
				{
					if(temp&0x80)
					{ 
						if(mode==0x02)gui_draw_bigpoint(x,y,color);	 
						else gui_phy.draw_point(x,y,color);
					}else if(mode==0)gui_phy.draw_point(x,y,gui_phy.back_color); 
				}
				temp<<=1;
				y++;
				if((y-y0)==size)
				{
					y=y0;
					x++;
					break;
				}
			}
		}else
		{
				y+=8;
				if((y-y0)>=size)//����һ���ֵĸ߶���
				{
					y=y0;		//y�������
 					tempoff--;   
				}
		}	 
	}						     
}
//��ʾlen������
//x,y :�������	 
//len :���ֵ�λ��
//color:��ɫ
//size:�����С
//num:��ֵ(0~2^64);
//mode:ģʽ.
//[7]:0,�����;1,���0.
//[3:0]:0,�ǵ�����ʾ;1,������ʾ.2,������(ֻ�����ڵ���ģʽ)
void gui_show_num(uint16_t x,uint16_t y,uint8_t len,uint16_t color,uint8_t size,long long num,uint8_t mode)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/gui_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)gui_show_ptchar(x+(size/2)*t,y,gui_phy.lcdwidth,gui_phy.lcdheight,0,color,size,'0',mode&0xf);//���0
				else gui_show_ptchar(x+(size/2)*t,y,gui_phy.lcdwidth,gui_phy.lcdheight,0,color,size,' ',mode&0xf);
 				continue;
			}else enshow=1; 
		 	 
		}
		gui_show_ptchar(x+(size/2)*t,y,gui_phy.lcdwidth,gui_phy.lcdheight,0,color,size,temp+'0',mode&0xf);
	}
}
//������תΪ�ַ���
//str:�ַ�����ŵ�ַ.
//num:���� 
uint8_t* gui_num2str(uint8_t*str,uint32_t num)
{
	uint8_t t,temp;
	uint8_t enrec=0;						   
	for(t=0;t<10;t++)
	{
		temp=(num/gui_pow(10,10-t-1))%10;
		if(enrec==0&&t<9)
		{
			if(temp==0)continue;//������Ҫ��¼
			else enrec=1; 		//��Ҫ��¼��.
		}
		*str=temp+'0';
		str++;
	}
	*str='\0';//���������.
	return str;
}


//��ָ����ַ��ʼ��ʾһ������
//x,y:��ʾ��ʼ����.
//xend,yend:x,y ������յ�����
//offset:��ʼ��ʾ��ƫ��
//color:������ɫ.
//size:���ִ�С
//chr:��������(���ֽ���ǰ,���ֽ��ں�)
//mode:0,�ǵ�����ʾ;1,������ʾ,2,������(ֻ�����ڵ���ģʽ)
void gui_show_ptfont(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint16_t size,uint8_t* chr,uint8_t mode)
{	 
    uint8_t temp;
    uint8_t t1,t;
	uint16_t tempoff;
	uint16_t y0=y;	
	uint8_t dzk[72];//24*24����,���Ҫ72���ֽ���Ϊ����洢
	uint8_t csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
 	if(size!=12&&size!=16&&size!=24)return;	//��֧�ֵ�size/�ڴ����ʧ��
	Get_HzMat(chr,dzk,size);		//�õ���Ӧ��С�ĵ�������
	tempoff=offset;
	for(t=0;t<csize;t++)
	{   	
		if(x>xend)break;//�����յ�����											   
		temp=dzk[t];	//�õ���������                         
		if(tempoff==0)	//ƫ�Ƶ�ַ���� 
		{			
			for(t1=0;t1<8;t1++)
			{		    
				if(y<=yend)
				{
					if(temp&0x80)
					{ 
						if(mode==0x02)gui_draw_bigpoint(x,y,color);	 
						else gui_phy.draw_point(x,y,color);
					}else if(mode==0)gui_phy.draw_point(x,y,gui_phy.back_color); 
				}
				temp<<=1;
				y++;
				if((y-y0)==size)
				{
					y=y0;
					x++;
					break;
				}
			}
		}else
		{
				y+=8;
				if((y-y0)>=size)//����һ���ֵĸ߶���
				{
					y=y0;		//y�������
 					tempoff--;   
				}
		}	
	}
}   
//��ָ��λ�ÿ�ʼ,��ʾָ�����ȷ�Χ���ַ���.
//x,y:��ʾ��ʼ����.
//xend:x�������ֹ����
//offset:��ʼ��ʾ��ƫ��
//color:������ɫ.
//size:���ִ�С
//str:�ַ���
//mode:0,�ǵ�����ʾ;1,������ʾ,2,������(ֻ�����ڵ���ģʽ)
void gui_show_ptstr(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint8_t size,uint8_t *str,uint8_t mode)
{
 	uint8_t bHz=0;     	//�ַ���������  
	uint8_t EnDisp=0;  	//ʹ����ʾ	    				    				  	  
    while(*str!=0)	//����δ����
    { 
        if(!bHz)
        {
	        if(*str>0x80)bHz=1;	//���� 
	        else              	//�ַ�
	        {      	   
				if(EnDisp==0)	//��δʹ����ʾ
				{
					if(offset>=size/2)	//������һ���ַ�
					{
						offset-=size/2;	//����һ���ַ���ƫ��
					}else				//δ����һ���ַ���ƫ��
					{
						offset=offset%(size/2);	//�õ��ַ�ƫ����
						EnDisp=1;				//���Կ�ʼ��ʾ��
					}
				}
				if(EnDisp==1)	//ʹ����ʾ
				{
	 				gui_show_ptchar(x,y,xend,yend,offset,color,size,*str,mode);//��ʾһ���ַ�	 
			        if((xend-x)>size/2)x+=size/2;	//�ַ�,Ϊȫ�ֵ�һ��
					else x+=xend-x;					//δ��ȫ��ʾ
					if(offset)
					{
						x-=offset;
						offset=0;//���ƫ�� 
			        } 
				}
				if(x>=xend)return;//������,�˳� 
				str++; 
	        }
        }else//���� 
        {     
            bHz=0;//�к��ֿ� 
			if(EnDisp==0)//��δʹ��
			{
				if(offset>=size)//������һ����
				{
					offset-=size;//����
				}else
				{
					offset=offset%(size);//�õ��ַ�ƫ��
					EnDisp=1;//���Կ�ʼ��ʾ��
				}
			}	 	   
			if(EnDisp)
			{
 				gui_show_ptfont(x,y,xend,yend,offset,color,size,str,mode); //��ʾ�������,������ʾ 	 
				if((xend-x)>size)x+=size; //�ַ�,Ϊȫ�ֵ�һ��
				else x+=xend-x;//δ��ȫ��ʾ				
				if(offset)
				{
					x-=offset;
					offset=0;//���ƫ�� 
		        }   
			}  
			if(x>=xend)return;//������,�˳�  
	        str+=2;  
        }						 
    }    
}
//��ָ��λ�ÿ�ʼ,��ʾָ�����ȷ�Χ���ַ���.(������Ч��ʾ)
//x,y:��ʾ��ʼ����.
//width:�����ʾ���
//offset:��ʼ��ʾ��ƫ��
//color:������ɫ.
//rimcolor:���ֱߵ���ɫ
//size:���ִ�С
//str:�ַ���
void gui_show_ptstrwhiterim(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t offset,uint16_t color,uint16_t rimcolor,uint8_t size,uint8_t *str)
{
	gui_show_ptstr(x,y,xend,yend,offset,rimcolor,size,str,2);	//�Ȼ���(�ô�ŵ㻭)
	gui_show_ptstr(x,y,xend,yend,offset,color,size,str,1);		//����(��С�㻭)
}

//��name���뵽path����.�Զ����\�ͽ�����.����Ҫȷ��pname���ڴ�ռ��㹻,������ܵ�������.
//pname:��·�����ļ���.path���ڴ��С����Ϊ:strlen(path)+strlen(name)+2!
//path:·��
//name:����
//����ֵ:��·�����ļ���
uint8_t* gui_path_name(uint8_t *pname,uint8_t* path,uint8_t *name)
{
	const uint8_t chgchar[2]={0X5C,0X00};//ת��� ��Ч"\"    
	strcpy((char *)pname,(const char*)path);	//����path��pname����
	strcat((char*)pname,(const char*)chgchar);	//���ת���
	strcat((char*)pname,(const char*)name);		//�������������
	return pname;
}
/////////////////////////////////////////////////////////////////////////////////////////
//�õ��ַ�����ռ������
//str:�ַ���ָ��;
//linelenth:ÿ�еĳ���
//font:�����С
//����ֵ:�ַ�����ռ������
uint32_t gui_get_stringline(uint8_t*str,uint16_t linelenth,uint8_t font)
{
	uint16_t xpos=0;
	uint32_t	lincnt=1;//���پ���1��.
	if(linelenth<font/2)return 0XFFFFFFFF;//�޷�ͳ�����
	while(*str!='\0'&&lincnt!=0xffffffff)
	{										   
		if((*str==0x0D&&(*(str+1)==0X0A))||(*str==0X0A))//�ǻس�/���з�
		{ 
			if(*str==0X0D)str+=2;
			else str+=1;
			lincnt++;//������1
			xpos=0;
		}else if(*str>=0X81&&(*(str+1)>=0X40))//��gbk����
		{
			xpos+=font;
			str+=2;
			if(xpos>linelenth)//�Ѿ����ڱ���֮��
			{
				xpos=font;
				lincnt++;//������1
			}
		}else//���ַ�
		{
			xpos+=font/2;
			str+=1;
			if(xpos>linelenth)//�Ѿ����ڱ���֮��
			{
				xpos=font/2;
				lincnt++;//������1
			}				
		}	
	}
	return lincnt;
}
//���趨��������ʾ�ַ���,�������������ʾ
//str:�ַ���ָ��;
//x,y,width,height:��ʾ����
//font:�����С
//fcolor:������ɫ,�Ե��ӷ�ʽд��.
void gui_show_string(uint8_t*str,uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t font,uint16_t fcolor)
{
	uint16_t xpos=x;
	uint16_t ypos=y;
	uint16_t endx=x+width-1;
	uint16_t endy=y+height-1;
 	if(width<font/2)return ;//�޷���ʾ���
	while(*str!='\0')//δ����
	{		
		if((*str==0x0D&&(*(str+1)==0X0A))||(*str==0X0A))//�ǻس�/���з�
		{ 
			if(*str==0X0D)str+=2;
			else str+=1;
 			xpos=x;
			ypos+=font;//y����16
		}else if(*str>=0X81&&(*(str+1)>=0X40))//��gbk����
		{
			if((xpos+font)>(endx+1))//�Ѿ����ڱ���֮��
			{
				xpos=x;
				ypos+=font;
 			}
			gui_show_ptfont(xpos,ypos,endx,endy,0,fcolor,font,str,1);
			xpos+=font;//ƫ��
			str+=2;

		}else//���ַ�
		{
			if((xpos+font/2)>(endx+1))
			{
				xpos=x;
				ypos+=font;
			}	
			gui_show_ptchar(xpos,ypos,endx,endy,0,fcolor,font,*str,1);		   
			xpos+=font/2;
			str+=1;	 			
		}
		if(ypos>endy)break;//��������ʾ������.	
	}	  
}	
//�ɴ˴���ʼ��ǰѰ��gbk��(������0x80���ֽ�)�ĸ���
//str:�ַ���
//pos:��ʼ���ҵĵ�ַ
//����ֵ:gbk�������
uint16_t gui_string_forwardgbk_count(uint8_t *str,uint16_t pos)
{		   
	uint16_t t=0;
	while(str[pos]>0x80)
	{
		t++;
		if(pos==0)break;
		pos--;
	}
	return t;
}
/////////////////////////////////////////////////////////////////////////////////////////
//�ڴ渴�ƺ���(��Ϊ��ϵͳmemset�����ᵼ��Ī��������,��ȫ�������������)
//*p:�ڴ��׵�ַ
//c:Ҫͳһ���õ�ֵ
//len:���ó���
void gui_memset(void *p,uint8_t c,uint32_t len)
{
	uint8_t *pt=(uint8_t*)p;
	while(len)
	{
		*pt=c;
		pt++;
		len--;		
	}
}
//�ڲ��ڴ���� 
//size:Ҫ������ڴ��С(uint8_tΪ��λ)
//����ֵ:NULL:����ʧ��;����,�ڴ��ַ
void *gui_memin_malloc(uint32_t size)			
{
	return (void*)mymalloc(size);
}
//�ڲ��ڴ��ͷ�
void gui_memin_free(void* ptr)		 
{
	if(ptr)myfree(ptr);
} 
//�ⲿ�ڴ����(Mini��û����SRAM,���� �������ڲ��ڴ�)
//size:Ҫ������ڴ��С(uint8_tΪ��λ)
//����ֵ:NULL:����ʧ��;����,�ڴ��ַ
void *gui_memex_malloc(uint32_t size)			
{ 
	return (void*)mymalloc(size);
}  
//�ⲿ�ڴ��ͷ�
void gui_memex_free(void* ptr)		 
{ 
	if(ptr)myfree(ptr);
}
//copy ptr��ǰsize���ֽڵ��µ�ַ,�������µ�ֵַ
//ptr:Ҫcopy��Դ��ַ
//size:�µ�ַ�ڴ�Ĵ�С
//����ֵ:Ŀ�ĵ�ַ
void *gui_memin_realloc(void *ptr,uint32_t size)
{
	return myrealloc(ptr,size);  
}		 
