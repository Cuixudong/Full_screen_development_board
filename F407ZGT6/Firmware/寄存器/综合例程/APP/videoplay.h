#ifndef __VIDEOPLAY_H
#define __VIDEOPLAY_H
#include <stm32f4xx.h>
#include "avi.h"
#include "ff.h"
#include "includes.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//APP-��Ƶ������ ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//*******************************************************************************
//�޸���Ϣ
//��
//////////////////////////////////////////////////////////////////////////////////

#define AVI_AUDIO_BUF_SIZE    1024*5		//����avi����ʱ,��Ƶbuf��С.
#define AVI_VIDEO_BUF_SIZE    1024*60		//����avi����ʱ,��Ƶbuf��С.

//��Ƶ���ſ�����
typedef __packed struct
{
    u8 *path;			//��ǰ�ļ���·��
    u8 *name;			//��ǰ��������
    vu8 status;			//bit0:0,��ͣ����;1,��������
    //bit1:0,���/������;1,��������
    //����,����

    u16 curindex;		//��ǰ���ŵ���Ƶ�ļ�����
    u16 mfilenum;		//��Ƶ�ļ���Ŀ
    u16 *mfindextbl;	//��Ƶ�ļ�������

    FIL *file;			//��Ƶ�ļ�ָ��
    vu8 i2splaybuf;		//�������ŵ���Ƶ֡������
    u8* i2sbuf[4]; 		//��Ƶ����֡,��4֡,4*AVI_AUDIO_BUF_SIZE
} __videodev;
extern __videodev videodev;//��Ƶ���ſ�����



void video_time_show(u16 sx,u16 sy,u16 sec);
void video_load_ui(void);
void video_show_vol(u8 pctx);
void video_info_upd(__videodev *videodevx,_progressbar_obj* videoprgbx,_progressbar_obj* volprgbx,AVI_INFO *aviinfo,u8 flag);
u8 video_play(void);
u8 video_play_mjpeg(void);

u8 video_seek(__videodev *videodevx,AVI_INFO *aviinfo,u8 *mbuf,u32 dstpos);

#endif











