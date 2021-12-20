#include "videoplay.h"
#include "audioplay.h"
#include "settings.h"
#include "ucos_ii.h"
#include "wm8978.h"
#include "i2s.h"
#include "wavplay.h"
#include "mjpeg.h"
#include "timer.h"
#include "avi.h"
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

__videodev videodev;		//��Ƶ���ſ�����


extern vu8 framecnt;		//ͳһ��֡������
extern vu8 framecntout;		//ͳһ��֡�������������
vu8 aviframeup;				//��Ƶ����ʱ϶���Ʊ���,������1��ʱ��,���Ը�����һ֡��Ƶ

//��Ƶ����I2S DMA����ص�����
void audio_i2s_dma_callback(void)
{
    videodev.i2splaybuf++;
    if(videodev.i2splaybuf>3)videodev.i2splaybuf=0;
    if(DMA1_Stream4->CR&(1<<19))
    {
        DMA1_Stream4->M0AR=(u32)videodev.i2sbuf[videodev.i2splaybuf];//ָ����һ��buf
    }
    else
    {
        DMA1_Stream4->M1AR=(u32)videodev.i2sbuf[videodev.i2splaybuf];//ָ����һ��buf
    }
}
/////////////////////////////////////////////////////////////////////////
//��ʾaudio����ʱ��
//sx,sy:��ʼ����
//sec:ʱ��
void video_time_show(u16 sx,u16 sy,u16 sec)
{
    u16 min;
    u8 *buf;
    buf=gui_memin_malloc(100);
    if(buf==0)return;
    min=sec/60;//�õ�������
    sec=sec%60;//�õ�������
    sprintf((char*)buf,"%03d:%02d",min,sec);
    gui_fill_rectangle(sx,sy,36,12,AUDIO_MAIN_BKCOLOR);	//����ɫ
    gui_show_string(buf,sx,sy,36,12,12,AUDIO_INFO_COLOR);
    gui_memin_free(buf);
}
//video����������
void video_load_ui(void)
{
    u8 vui_tpbar_height=0;	//�����������߶�
    u8 vui_msgbar_height=0;	//��Ϣ���߶�
    u8 vui_prgbar_height=0;	//����������߶�
    u8 vui_btnbar_height=0;	//�ײ���ť���߶�
    u8 pixpitch=0;
    u8 toffy=0;
    if(lcddev.width==240)
    {
        vui_tpbar_height=20;
        vui_msgbar_height=46;
        vui_prgbar_height=30;
        vui_btnbar_height=60;
        pixpitch=6;
    } else if(lcddev.width==320)
    {
        vui_tpbar_height=24;
        vui_msgbar_height=50;
        vui_prgbar_height=30;
        vui_btnbar_height=80;
        pixpitch=20;
    } else if(lcddev.width==480)
    {
        vui_tpbar_height=30;
        vui_msgbar_height=60;
        vui_prgbar_height=40;
        vui_btnbar_height=120;
        pixpitch=30;
    }
    gui_fill_rectangle(0,0,lcddev.width,vui_tpbar_height,AUDIO_TITLE_BKCOLOR);	//����������ɫ
    gui_show_strmid(0,0,lcddev.width,vui_tpbar_height,AUDIO_TITLE_COLOR,16,(u8*)APP_MFUNS_CAPTION_TBL[3][gui_phy.language]);	//��ʾ����
    gui_fill_rectangle(0,vui_tpbar_height,lcddev.width,vui_msgbar_height,AUDIO_MAIN_BKCOLOR);									//�����Ϣ������ɫ
    toffy=(vui_msgbar_height-44)/2;
    minibmp_decode((u8*)APP_VOL_PIC,pixpitch+2,vui_tpbar_height+20+toffy-2,16,16,0,0);				//��������ͼ��
    gui_show_string("00%",pixpitch+20,vui_tpbar_height+20+toffy+12,66,12,12,AUDIO_INFO_COLOR); 		//��ʾ����
    gui_fill_rectangle(0,lcddev.height-vui_btnbar_height-vui_prgbar_height,lcddev.width,vui_prgbar_height,AUDIO_MAIN_BKCOLOR);	//��������������ɫ
    gui_fill_rectangle(0,lcddev.height-vui_btnbar_height,lcddev.width,vui_btnbar_height,AUDIO_BTN_BKCOLOR);						//��䰴ť������ɫ
    gui_fill_rectangle(0,vui_tpbar_height+vui_msgbar_height,lcddev.width,lcddev.height-vui_tpbar_height-vui_msgbar_height-vui_prgbar_height-vui_btnbar_height,BLACK);//����ɫ
}
//��ʾ�����ٷֱ�
//pctx:�ٷֱ�ֵ
void video_show_vol(u8 pctx)
{
    u16 sx,sy;
    if(lcddev.width==240)
    {
        sx=6+20;
        sy=20+20+1+12;
    } else if(lcddev.width==320)
    {
        sx=20+20;
        sy=24+20+3+12;
    } else if(lcddev.width==480)
    {
        sx=30+20;
        sy=30+20+8+12;
    }
    gui_phy.back_color=AUDIO_MAIN_BKCOLOR;//���ñ���ɫΪ��ɫ
    gui_fill_rectangle(sx,sy,24,12,AUDIO_MAIN_BKCOLOR);//��䱳��ɫ
    if(pctx==100)
    {
        gui_show_num(sx,sy,3,AUDIO_INFO_COLOR,12,pctx,0x80);//��ʾ�����ٷֱ�
        gui_show_ptchar(sx+18,sy,sx+18+6,sy+12,0,AUDIO_INFO_COLOR,12,'%',0);	//��ʾ�ٷֺ�
    } else
    {
        gui_show_num(sx,sy,2,AUDIO_INFO_COLOR,12,pctx,0x80);//��ʾ�����ٷֱ�
        gui_show_ptchar(sx+12,sy,sx+12+6,sy+12,0,AUDIO_INFO_COLOR,12,'%',0);	//��ʾ�ٷֺ�
    }
}
//videodevx:audio������
//videoprgbx:������
//aviinfo:��Ƶ��Ϣ
void video_info_upd(__videodev *videodevx,_progressbar_obj* videoprgbx,_progressbar_obj* volprgbx,AVI_INFO *aviinfo,u8 flag)
{
    static u32 oldsec;
    u8 vui_tpbar_height;	//�����������߶�
    u8 vui_msgbar_height;	//��Ϣ���߶�
    u8 pixpitch;
    u8 toffy;
    u16 tempx;
    u8 *buf;
    float ftemp;
    u32 totsec=0;		//video�ļ���ʱ��
    u32 cursec; 		//��ǰ����ʱ��
    if(lcddev.width==240)
    {
        vui_tpbar_height=20;
        vui_msgbar_height=46;
        pixpitch=6;
    } else if(lcddev.width==320)
    {
        vui_tpbar_height=24;
        vui_msgbar_height=50;
        pixpitch=20;
    } else if(lcddev.width==480)
    {
        vui_tpbar_height=30;
        vui_msgbar_height=60;
        pixpitch=30;
    }
    toffy=(vui_msgbar_height-44)/2;
    if(flag==1)//��Ҫ�������ֵ���Ϣ
    {
        buf=gui_memin_malloc(100);	//����100�ֽ��ڴ�
        if(buf==NULL)return;		//game over
        gui_fill_rectangle(0,vui_tpbar_height+3,lcddev.width,14,AUDIO_MAIN_BKCOLOR);//���¸������һ��,���֮ǰ����ʾ
        gui_show_ptstrwhiterim(4,vui_tpbar_height+4,lcddev.width-4,lcddev.height,0,0X0000,0XFFFF,12,videodevx->name);	//��ʾ�µ�����
        gui_phy.back_color=AUDIO_MAIN_BKCOLOR;//���ñ���ɫΪ��ɫ
        //��ʾ�����ٷֱ�
        audio_show_vol((volprgbx->curpos*100)/volprgbx->totallen);//��ʾ�����ٷֱ�
        //��ʾ��Ŀ���
        sprintf((char*)buf,"%03d/%03d",videodevx->curindex+1,videodevx->mfilenum);
        gui_fill_rectangle(pixpitch+20+volprgbx->width-42,vui_tpbar_height+20+toffy+12,42,12,AUDIO_MAIN_BKCOLOR);	//���֮ǰ����ʾ
        gui_show_string(buf,pixpitch+20+volprgbx->width-42,vui_tpbar_height+20+toffy+12,42,12,12,AUDIO_INFO_COLOR);
        //��ʾxxxKhz
        tempx=pixpitch*2+20+volprgbx->width;//��ʼx����
        gui_fill_rectangle(tempx,vui_tpbar_height+20+toffy,54,12,AUDIO_MAIN_BKCOLOR);		//���֮ǰ����ʾ
        ftemp=(float)aviinfo->SampleRate/1000;//xx.xxxKhz
        sprintf((char*)buf,"%2.3fKhz",ftemp);
        gui_show_string(buf,tempx,vui_tpbar_height+20+toffy,54,12,12,AUDIO_INFO_COLOR);
        //��ʾ�ֱ���
        tempx=pixpitch*2+20+volprgbx->width;//��ʼx����
        gui_fill_rectangle(tempx,vui_tpbar_height+20+toffy+12,66,12,AUDIO_MAIN_BKCOLOR);	//���֮ǰ����ʾ
        sprintf((char*)buf,"Pix:%dX%d",aviinfo->Width,aviinfo->Height);
        gui_show_string(buf,tempx,vui_tpbar_height+20+toffy+12,66,12,12,AUDIO_INFO_COLOR);	//��ʾ�ֱ���
        //��������
        oldsec=0;
        videoprgbx->totallen=videodevx->file->fsize;	//�����ܳ���
        videoprgbx->curpos=0;
        gui_memin_free(buf);//�ͷ��ڴ�
    }
    totsec=(aviinfo->SecPerFrame/1000)*aviinfo->TotalFrame;	//�����ܳ���(��λ:ms)
    totsec/=1000;		//������.
    cursec=((double)videodevx->file->fptr/videodevx->file->fsize)*totsec;//��ǰ���ŵ���������?
    videoprgbx->curpos=f_tell(videodevx->file);	//�õ���ǰ�Ĳ���λ��
    progressbar_draw_progressbar(videoprgbx);	//���½�����λ��
    if(oldsec!=cursec)
    {
        oldsec=cursec;
        //��ʾ֡��
        buf=gui_memin_malloc(100);	//����100�ֽ��ڴ�
        if(buf==NULL)return;
        tempx=pixpitch*2+20+volprgbx->width+60;//��ʼx����
        gui_fill_rectangle(tempx,vui_tpbar_height+20+toffy,30,12,AUDIO_MAIN_BKCOLOR);		//���֮ǰ����ʾ
        sprintf((char*)buf,"%02dfps",framecntout);
        gui_show_string(buf,tempx,vui_tpbar_height+20+toffy,30,12,12,AUDIO_INFO_COLOR);
        gui_memin_free(buf);//�ͷ��ڴ�
        //��ʾʱ��
        if(lcddev.width==240)
        {
            video_time_show(2,lcddev.height-48-12-12-9,cursec);			//��ʾ����ʱ��
            video_time_show(40+160+3,lcddev.height-48-12-12-9,totsec);	//��ʾ��ʱ��
        } else if(lcddev.width==320)
        {
            video_time_show(4,lcddev.height-60-20-12-9,cursec);		//��ʾ����ʱ��
            video_time_show(45+230+5,lcddev.height-60-20-12-9,totsec);	//��ʾ��ʱ��
        } else if(lcddev.width==480)
        {
            video_time_show(24,lcddev.height-80-40-12-14,cursec);		//��ʾ����ʱ��
            video_time_show(70+340+10,lcddev.height-80-40-12-14,totsec);//��ʾ��ʱ��
        }
    }
}
//��Ƶ������ʾ��
u8*const video_msg_tbl[3][GUI_LANGUAGE_NUM]=
{
    {"��ȡ�ļ�����!!","�xȡ�ļ��e�`!!","File Read Error!",},
    {"�ڴ治��!!","�ȴ治��!!","Out of memory!",},
    {"�ֱ��ʲ�֧��","�ֱ��ʲ�֧��","Image Size Error!",},
};
//��Ƶ����
u8 video_play(void)
{
    u8 rval=0;			//����ֵ
    u8 *pname=0;
    u16 i;
    u8 key;

    _btn_obj* rbtn;		//���ذ�ť�ؼ�
    _filelistbox_obj * flistbox;
    _filelistbox_list * filelistx; 	//�ļ�
    memset(&videodev,0,sizeof(__videodev));//videodev�ṹ������.
    app_filebrower((u8*)APP_MFUNS_CAPTION_TBL[3][gui_phy.language],0X07);//ѡ��Ŀ���ļ�,���õ�Ŀ������

    flistbox=filelistbox_creat(0,gui_phy.tbheight,lcddev.width,lcddev.height-gui_phy.tbheight*2,1,gui_phy.listfsize);//����һ��filelistbox
    if(flistbox==NULL)rval=1;							//�����ڴ�ʧ��.
    else
    {
        flistbox->fliter=FLBOX_FLT_VIDEO;		//ͼƬ�ļ�
        filelistbox_add_disk(flistbox);			//��Ӵ���·��
        filelistbox_draw_listbox(flistbox);
    }
    rbtn=btn_creat(lcddev.width-2*gui_phy.tbfsize-8-1,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
    if(rbtn==NULL)rval=1;	//û���㹻�ڴ湻����
    else
    {
        rbtn->caption=(u8*)GUI_BACK_CAPTION_TBL[gui_phy.language];	//����
        rbtn->font=gui_phy.tbfsize;//�����µ������С
        rbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
        rbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
        btn_draw(rbtn);//����ť
    }
    while(rval==0)//��ѭ��
    {
        tp_dev.scan(0);    							//ɨ�败����
        in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);		//�õ�������ֵ
        delay_ms(5);
        if(system_task_return)break;				//TPAD����
        filelistbox_check(flistbox,&in_obj);		//ɨ���ļ�

        if(flistbox->dbclick==0X81)					//˫���ļ���
        {
            gui_memin_free(videodev.path);			//�ͷ��ڴ�
            gui_memex_free(videodev.mfindextbl);	//�ͷ��ڴ�
            videodev.path=(u8*)gui_memin_malloc(strlen((const char*)flistbox->path)+1);//Ϊ�µ�·�������ڴ�
            if(videodev.path==NULL) {
                rval=1;    //�ڴ����ʧ��
                break;
            }
            videodev.path[0]='\0';					//���ʼ���������.
            strcpy((char *)videodev.path,(char *)flistbox->path);
            videodev.mfindextbl=(u16*)gui_memex_malloc(flistbox->filecnt*2);//Ϊ�µ�tbl�����ڴ�
            if(videodev.mfindextbl==NULL) {
                rval=1;    //�ڴ����ʧ��
                break;
            }
            for(i=0; i<flistbox->filecnt; i++)videodev.mfindextbl[i]=flistbox->findextbl[i]; //����
            videodev.mfilenum=flistbox->filecnt;		//��¼�ļ�����
            videodev.curindex=flistbox->selindex-flistbox->foldercnt;//��ǰӦ�ò��ŵ��ļ�����
            printf("play:%d/%d\r\n",videodev.curindex,videodev.mfilenum);
            rval=video_play_mjpeg();
            if(rval==0XFF)break;
            else
            {
                if(rval)//���ڴ���
                {
                    if(rval<20)window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)video_msg_tbl[0][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);	//�ļ���ȡ����
                    if(rval==0X21)window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)video_msg_tbl[1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//�ڴ����
                    if(rval==0X22)window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)video_msg_tbl[2][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//�ֱ��ʴ���
                    delay_ms(2000);
                    rval=0;
                }
                flistbox->dbclick=0;	//���÷��ļ����״̬
                app_filebrower((u8*)APP_MFUNS_CAPTION_TBL[3][gui_phy.language],0X07);//ѡ��Ŀ���ļ�,���õ�Ŀ������
                btn_draw(rbtn);			//����ť
                flistbox->selindex=flistbox->foldercnt+videodev.curindex;//ѡ����ĿΪ��ǰ���ڲ��ŵ���Ŀ
                filelistbox_rebuild_filelist(flistbox);//�ؽ�flistbox
                system_task_return=0;	//�������˳���Ƶ����
            }
        }
        key=btn_check(rbtn,&in_obj);
        if(key&&((rbtn->sta&0X80)==0))
        {
            if(flistbox->dbclick!=0X81)//���ļ������ʱ���˷��ذ�ť,�򷵻���һ��Ŀ¼
            {
                filelistx=filelist_search(flistbox->list,flistbox->selindex);//�õ���ʱѡ�е�list����Ϣ
                if(filelistx->type==FICO_DISK)//�Ѿ�������������,���˳���Ƶ���
                {
                    break;
                } else filelistbox_back(flistbox);//�˻���һ��Ŀ¼
            }
        }
    }
    filelistbox_delete(flistbox);		//ɾ��filelist
    btn_delete(rbtn);					//ɾ����ť
    gui_memin_free(pname);				//�ͷ��ڴ�
    gui_memin_free(videodev.path);		//�ͷ��ڴ�
    gui_memex_free(videodev.mfindextbl);//�ͷ��ڴ�
    return rval;
}


//����mjpeg�ļ�
//����ֵ:
//0,�������Ž���,�����ļ����״̬.
//0XFF,���˳���ť��,ֱ�ӽ�����Ƶ����
//����,�������
u8 video_play_mjpeg(void)
{
    u8 *pname=0;		//��·��������
    u8* framebuf=0;		//��Ƶ����buf
    u8* pbuf=0;			//bufָ��
    DIR videodir;		//videoĿ¼
    FILINFO videoinfo;	//video�ļ���Ϣ
    _progressbar_obj* videoprgb=0,*volprgb=0;
    _btn_obj* tbtn[5];
    u16 lastvolpos;
    u8 i;
    u8 tcnt=0;

    u8  res=0;
    u16 offset=0;
    u32	nr;
    u8 i2ssavebuf;
    u16 videoheight;	//��Ƶ��ʾ����߶�
    u16 yoff;
    u8 key=0;

    for(i=0; i<5; i++)tbtn[i]=0;
    if(audiodev.status&(1<<7))//��ǰ�ڷŸ�??
    {
        audio_stop_req(&audiodev);	//ֹͣ��Ƶ����
        audio_task_delete();		//ɾ�����ֲ�������.
    }
    app_wm8978_volset(wm8978set.mvol);
    WM8978_ADDA_Cfg(1,0);	//����DAC
    WM8978_Input_Cfg(0,0,0);//�ر�����ͨ��
    WM8978_Output_Cfg(1,0);	//����DAC���
    videoinfo.lfsize=_MAX_LFN*2+1;								//���ļ�����󳤶�
    framebuf=gui_memin_malloc(AVI_VIDEO_BUF_SIZE);				//������Ƶbuf
    videoinfo.lfname=gui_memin_malloc(videoinfo.lfsize);		//Ϊ���ļ������������ڴ�
    videodev.i2sbuf[0]=gui_memin_malloc(AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ�
    videodev.i2sbuf[1]=gui_memin_malloc(AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ�
    videodev.i2sbuf[2]=gui_memin_malloc(AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ�
    videodev.i2sbuf[3]=gui_memin_malloc(AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ�
    videodev.file=(FIL*)gui_memin_malloc(sizeof(FIL)); 			//����videodev.file�ڴ�
    if(!videodev.i2sbuf[3]||!framebuf||!videodev.file||!videoinfo.lfname)
    {
        res=0X21;
    } else
    {
        memset(videodev.i2sbuf[0],0,AVI_AUDIO_BUF_SIZE);
        memset(videodev.i2sbuf[1],0,AVI_AUDIO_BUF_SIZE);
        memset(videodev.i2sbuf[2],0,AVI_AUDIO_BUF_SIZE);
        memset(videodev.i2sbuf[3],0,AVI_AUDIO_BUF_SIZE);
        if(lcddev.width==240)
        {
            videoprgb=progressbar_creat(40,lcddev.height-48-12-10-11,160,12,0X20);//video���Ž�����
            if(videoprgb==NULL)res=0X21;
            volprgb=progressbar_creat(6+20,20+20+1+1,110,10,0X20);	//������С������
            if(volprgb==NULL)res=0X21;
            volprgb->totallen=63;
            videoheight=164;
            yoff=66;
        } else if(lcddev.width==320)
        {
            videoprgb=progressbar_creat(45,lcddev.height-60-20-10-11,230,12,0X20);//video���Ž�����
            if(videoprgb==NULL)res=0X21;
            volprgb=progressbar_creat(20+20,24+20+3+1,150,10,0X20);	//������С������
            if(volprgb==NULL)res=0X21;
            volprgb->totallen=63;	//�����ܳ���,��Ƶ��100~250.ƫ��Ϊ100.
            videoheight=296;
            yoff=74;
        } else if(lcddev.width==480)
        {
            videoprgb=progressbar_creat(70,lcddev.height-80-40-10-16,340,12,0X20);//video���Ž�����
            if(videoprgb==NULL)res=0X21;
            volprgb=progressbar_creat(30+20,30+20+8+1,280,10,0X20);	//������С������
            if(volprgb==NULL)res=0X21;
            volprgb->totallen=63;	//�����ܳ���,��Ƶ��100~250.ƫ��Ϊ100.
            videoheight=550;
            yoff=90;
        }
        if(wm8978set.mvol<=63)volprgb->curpos=wm8978set.mvol;
        else//���������
        {
            wm8978set.mvol=0;
            volprgb->curpos=0;
        }
        lastvolpos=volprgb->curpos;//�趨�����λ��
        for(i=0; i<5; i++) //ѭ������5����ť
        {
            if(lcddev.width==240)tbtn[i]=btn_creat(0+i*48,lcddev.height-48-6,48,48,0,1);			//����ͼƬ��ť
            else if(lcddev.width==320)tbtn[i]=btn_creat(2+i*(60+4),lcddev.height-60-10,60,60,0,1);	//����ͼƬ��ť
            else if(lcddev.width==480)tbtn[i]=btn_creat(8+i*(80+16),lcddev.height-80-20,80,80,0,1);	//����ͼƬ��ť
            if(tbtn[i]==NULL) {
                res=0X21;    //����ʧ��.
                break;
            }
            tbtn[i]->bcfdcolor=0X2CFF;				//����ʱ�ı���ɫ
            tbtn[i]->bcfucolor=AUDIO_BTN_BKCOLOR;	//�ɿ�ʱ����ɫ
            tbtn[i]->picbtnpathu=(u8*)AUDIO_BTN_PIC_TBL[0][i];
            tbtn[i]->picbtnpathd=(u8*)AUDIO_BTN_PIC_TBL[1][i];
            tbtn[i]->sta=0;
        }
        if(res==0)
        {
            res=f_opendir(&videodir,(const TCHAR*)videodev.path);//��ѡ�е�Ŀ¼
        }
    }
    if(res==0)
    {
        videoprgb->inbkcolora=0x738E;			//Ĭ��ɫ
        videoprgb->inbkcolorb=AUDIO_INFO_COLOR;	//Ĭ��ɫ
        videoprgb->infcolora=0X75D;				//Ĭ��ɫ
        videoprgb->infcolorb=0X596;				//Ĭ��ɫ
        volprgb->inbkcolora=AUDIO_INFO_COLOR;	//Ĭ��ɫ
        volprgb->inbkcolorb=AUDIO_INFO_COLOR;	//Ĭ��ɫ
        volprgb->infcolora=0X75D;				//Ĭ��ɫ
        volprgb->infcolorb=0X596;				//Ĭ��ɫ
        video_load_ui();						//����������
        for(i=0; i<5; i++)btn_draw(tbtn[i]);		//����ť
        tbtn[2]->picbtnpathu=(u8*)AUDIO_PLAYR_PIC;//����һ��֮���Ϊ�����ɿ�״̬
        progressbar_draw_progressbar(videoprgb);//��������
        progressbar_draw_progressbar(volprgb);	//��������
    }
    while(res==0)
    {
        ff_enter(videodir.fs);//����fatfs,��ֹ�����.
        dir_sdi(&videodir,videodev.mfindextbl[videodev.curindex]);
        ff_leave(videodir.fs);//�˳�fatfs,��������os��
        res=f_readdir(&videodir,&videoinfo);//��ȡ�ļ���Ϣ
        if(res)break;//��ʧ��
        videodev.name=(u8*)(*videoinfo.lfname?videoinfo.lfname:videoinfo.fname);
        pname=gui_memin_malloc(strlen((const char*)videodev.name)+strlen((const char*)videodev.path)+2);//�����ڴ�
        if(pname==NULL) {
            res=0X21;    //����ʧ��
            break;
        }
        pname=gui_path_name(pname,videodev.path,videodev.name);	//�ļ�������·��
        res=f_open(videodev.file,(char *)pname,FA_READ);
        gui_memin_free(pname);			//�ͷ��ڴ�
        if(res==0)
        {
            pbuf=framebuf;
            res=f_read(videodev.file,pbuf,AVI_VIDEO_BUF_SIZE,&nr);//��ʼ��ȡ
            if(res)//�ļ�ϵͳ����,ֱ���˳����ٲ���
            {
                break;
            }
            //��ʼavi����
            res=avi_init(pbuf,AVI_VIDEO_BUF_SIZE);	//avi����
            if(res)//һ������,�����Լ�������
            {
                printf("avi err:%d\r\n",res);
                break;
            }
            if(avix.Height>videoheight||avix.Width>lcddev.width)//ͼƬ�ߴ�������,ֱ���˳����ٲ���
            {
                res=0X22;
                printf("avi size error\r\n");
                break;
            }
            TIM6_Int_Init(avix.SecPerFrame/100-1,8400-1);	//10Khz����Ƶ��,��1��100us,������Ƶ֡�������
            TIM3_Int_Init(10000-1,8400-1);					//10Khz����,1�����ж�һ��,����֡����
            offset=avi_srarch_id(pbuf,AVI_VIDEO_BUF_SIZE,"movi");//Ѱ��movi ID
            avi_get_streaminfo(pbuf+offset+4);			//��ȡ����Ϣ
            f_lseek(videodev.file,offset+12);			//������־ID,����ַƫ�Ƶ������ݿ�ʼ��
            res=mjpegdec_init((lcddev.width-avix.Width)/2,yoff+(videoheight-avix.Height)/2);//JPG�����ʼ��
            if(avix.SampleRate)							//����Ƶ��Ϣ,�ų�ʼ��
            {
                WM8978_I2S_Cfg(2,0);	//�����ֱ�׼,16λ���ݳ���
                I2S2_Init(0,2,0,0);		//�����ֱ�׼,��������,ʱ�ӵ͵�ƽ��Ч,16λ֡����
                I2S2_SampleRate_Set(avix.SampleRate);	//���ò�����
                I2S2_TX_DMA_Init(videodev.i2sbuf[1],videodev.i2sbuf[2],avix.AudioBufSize/2); //����DMA
                i2s_tx_callback=audio_i2s_dma_callback;	//�ص�����ָ��I2S_DMA_Callback
                videodev.i2splaybuf=0;
                i2ssavebuf=0;
                I2S_Play_Start(); //����I2S����
            }
            gui_fill_rectangle(0,yoff,lcddev.width,videoheight,BLACK);	//�����Ƶ����
            video_info_upd(&videodev,videoprgb,volprgb,&avix,1);		//����������Ϣ
            tcnt=0;
            key=0;
            videodev.status=3;//����ͣ,�ǿ������
            while(key==0)//����ѭ��
            {
                if(videodev.status&(1<<0)&&videodev.status&(1<<1))
                {
                    if(avix.StreamID==AVI_VIDS_FLAG)//��Ƶ��
                    {
                        pbuf=framebuf;
                        f_read(videodev.file,pbuf,avix.StreamSize+8,&nr);//������֡+��һ������ID��Ϣ
                        res=mjpegdec_decode(pbuf,avix.StreamSize);
                        if(res)
                        {
                            printf("decode error!\r\n");
                        }
                        while(aviframeup==0)delay_ms(1000/OS_TICKS_PER_SEC);//�ȴ�ʱ�䵽��(��TIM6���ж���������Ϊ1)
                        aviframeup=0;	//��־����
                        framecnt++;
                    } else 	//��Ƶ��
                    {
                        //video_time_show(videodev.file,&avix); 	//��ʾ��ǰ����ʱ��
                        i2ssavebuf++;
                        if(i2ssavebuf>3)i2ssavebuf=0;
                        do
                        {
                            nr=videodev.i2splaybuf;
                            if(nr)nr--;
                            else nr=3;
                        } while(i2ssavebuf==nr);//��ײ�ȴ�.
                        f_read(videodev.file,videodev.i2sbuf[i2ssavebuf],avix.StreamSize+8,&nr);//���videodev.i2sbuf
                        pbuf=videodev.i2sbuf[i2ssavebuf];
                    }
                } else	//��ͣ״̬
                {
                    delay_ms(1000/OS_TICKS_PER_SEC);
                }

                tp_dev.scan(0);
                in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ
                for(i=0; i<5; i++)
                {
                    res=btn_check(tbtn[i],&in_obj);
                    if((res&&((tbtn[i]->sta&(1<<7))==0)&&(tbtn[i]->sta&(1<<6)))||system_task_return)//�а����������ɿ�,����TP�ɿ��˻���TPAD����
                    {
                        if(system_task_return) {
                            key=0XFF;
                            break;
                        };//TPAD���أ�����Ŀ¼
                        switch(i)
                        {
                        case 0://file list
                            key=0xff;
                            break;
                        case 1://��һ����Ƶ
                            if(systemset.videomode!=1)//���������
                            {
                                if(videodev.curindex)videodev.curindex--;
                                else videodev.curindex=videodev.mfilenum-1;
                            } else	//�������
                            {
                                videodev.curindex=app_get_rand(videodev.mfilenum);//�õ���һ�׸���������
                            }
                            key=1;
                            break;
                        case 3://��һ����Ƶ
                            if(systemset.videomode!=1)//���������
                            {
                                if(videodev.curindex<(videodev.mfilenum-1))videodev.curindex++;
                                else videodev.curindex=0;
                            } else	//�������
                            {
                                videodev.curindex=app_get_rand(videodev.mfilenum);//�õ���һ�׸���������
                            }
                            key=3;
                            break;
                        case 2://����/��ͣ
                            if(videodev.status&(1<<0))//����ͣ
                            {
                                videodev.status&=~(1<<0);	//�����ͣ
                                I2S_Play_Stop();			//�ر���Ƶ
                                tbtn[2]->picbtnpathd=(u8*)AUDIO_PLAYP_PIC;
                                tbtn[2]->picbtnpathu=(u8*)AUDIO_PAUSER_PIC;
                            } else//��ͣ״̬
                            {
                                videodev.status|=1<<0;		//ȡ����ͣ
                                I2S_Play_Start();			//����DMA����
                                tbtn[2]->picbtnpathd=(u8*)AUDIO_PAUSEP_PIC;
                                tbtn[2]->picbtnpathu=(u8*)AUDIO_PLAYR_PIC;
                            }
                            break;
                        case 4://ֹͣ����,ֱ���˳���������
                            key=4;
                            break;
                        }
                    }
                }
                res=progressbar_check(volprgb,&in_obj);//�������������
                if(res&&lastvolpos!=volprgb->curpos)//��������,��λ�ñ仯��.ִ����������
                {
                    lastvolpos=volprgb->curpos;
                    if(volprgb->curpos)wm8978set.mvol=volprgb->curpos;//��������
                    else wm8978set.mvol=0;
                    app_wm8978_volset(wm8978set.mvol);
                    audio_show_vol((volprgb->curpos*100)/volprgb->totallen);	//��ʾ�����ٷֱ�
                }
                res=progressbar_check(videoprgb,&in_obj);
                if(res)//��������,�����ɿ���,ִ�п������
                {
                    videodev.status&=~(1<<1);//��־����������״̬
                    if(videodev.status&1<<0)I2S_Play_Stop();//����ͣʱ,��ʼ�������,�ر���Ƶ
                    video_seek(&videodev,&avix,framebuf,videoprgb->curpos);
                    pbuf=framebuf;
                    video_info_upd(&videodev,videoprgb,volprgb,&avix,0);//������ʾ��Ϣ,ÿ100msִ��һ��
                } else if((videodev.status&(1<<1))==0)//���ڿ��/����״̬?
                {
                    if(videodev.status&1<<0)I2S_Play_Start();//����ͣ״̬,������˽���,����Ƶ
                    videodev.status|=1<<1;	//ȡ���������״̬
                }
                if(videodev.status&(1<<0)&&videodev.status&(1<<1))//����ͣ״̬�Ϳ������״̬
                {
                    if(avi_get_streaminfo(pbuf+avix.StreamSize))//��ȡ��һ֡ ����־,�������,�����ǵ�Ӱ������
                    {
                        printf("frame error \r\n");
                        break;
                    }
                }
                if((tcnt%20)==0)video_info_upd(&videodev,videoprgb,volprgb,&avix,0);//������ʾ��Ϣ,ÿ100msִ��һ��
            }
            I2S_Play_Stop();	//�ر���Ƶ
            TIM6->CR1&=~(1<<0); //�رն�ʱ��6
            TIM3->CR1&=~(1<<0); //�رն�ʱ��3
            mjpegdec_free();	//�ͷ��ڴ�
            f_close(videodev.file);
            if(key==0)
            {
                if(systemset.videomode==0)//˳�򲥷�
                {
                    if(videodev.curindex<(videodev.mfilenum-1))videodev.curindex++;
                    else videodev.curindex=0;
                } else if(systemset.videomode==1)//�������
                {
                    videodev.curindex=app_get_rand(videodev.mfilenum);//�õ���һ�׸���������
                } else videodev.curindex=videodev.curindex;//����ѭ��
            } else if(key==0XFF) {
                res=0;
                break;
            }
            else if(key==4) {
                res=0XFF;
                break;
            }
        }
    }
    gui_memin_free(videoinfo.lfname);
    gui_memin_free(videodev.i2sbuf[0]);
    gui_memin_free(videodev.i2sbuf[1]);
    gui_memin_free(videodev.i2sbuf[2]);
    gui_memin_free(videodev.i2sbuf[3]);
    gui_memin_free(framebuf);
    gui_memin_free(videodev.file);
    for(i=0; i<5; i++)if(tbtn[i])btn_delete(tbtn[i]); //ɾ����ť
    if(videoprgb)progressbar_delete(videoprgb);
    if(volprgb)progressbar_delete(volprgb);
    WM8978_ADDA_Cfg(0,0);				//�ر�DAC&ADC
    WM8978_Input_Cfg(0,0,0);			//�ر�����ͨ��
    WM8978_Output_Cfg(0,0);				//�ر�DAC���
    app_wm8978_volset(0);				//�ر�WM8978�������
    return res;
}
//avi�ļ�����
u8 video_seek(__videodev *videodevx,AVI_INFO *aviinfo,u8 *mbuf,u32 dstpos)
{
    u32 fpos=dstpos;
    u8 *pbuf;
    u16 offset;
    u32 br;

    f_lseek(videodevx->file,fpos);///ƫ�Ƶ�Ŀ��λ��
    f_read(videodevx->file,mbuf,AVI_VIDEO_BUF_SIZE,&br);	//������֡+��һ������ID��Ϣ
    pbuf=mbuf;
    if(fpos==0) //��0��ʼ,����Ѱ��movi ID
    {
        offset=avi_srarch_id(pbuf,AVI_VIDEO_BUF_SIZE,"movi");
    } else offset=0;
    offset+=avi_srarch_id(pbuf+offset,AVI_VIDEO_BUF_SIZE,aviinfo->VideoFLAG);	//Ѱ����Ƶ֡
    avi_get_streaminfo(pbuf+offset);			//��ȡ����Ϣ
    f_lseek(videodevx->file,fpos+offset+8);		//������־ID,����ַƫ�Ƶ������ݿ�ʼ��
    if(aviinfo->StreamID==AVI_VIDS_FLAG)
    {
        f_read(videodevx->file,mbuf,aviinfo->StreamSize+8,&br);	//������֡
        mjpegdec_decode(mbuf,aviinfo->StreamSize); 		//��ʾ��Ƶ֡
    }
    return 0;
}






















