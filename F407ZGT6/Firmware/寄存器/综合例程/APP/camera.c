#include "camera.h"
#include "common.h"
#include "calendar.h"
#include "audioplay.h"
#include "ov2640.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//APP-����� ����
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

vu8 hsync_int=0;						//֡�жϱ�־
vu8 jpeg_size;							//jpegͼƬ�ֱ���
vu8 ov2640_mode=OV2640_RGB565_MODE;		//����ģʽ:0,RGB565ģʽ;1,JPEGģʽ

#define jpeg_dma_bufsize	5*1024		//����JPEG DMA����ʱ���ݻ���jpeg_buf0/1�Ĵ�С(*4�ֽ�)
volatile u32 jpeg_data_len=0; 			//buf�е�JPEG��Ч���ݳ���(*4�ֽ�)
volatile u8 jpeg_data_ok=0;				//JPEG���ݲɼ���ɱ�־
//0,����û�вɼ���;
//1,���ݲɼ�����,���ǻ�û����;
//2,�����Ѿ����������,���Կ�ʼ��һ֡����

u32 *jpeg_buf0;							//JPEG���ݻ���buf,ͨ��malloc�����ڴ�
u32 *jpeg_buf1;							//JPEG���ݻ���buf,ͨ��malloc�����ڴ�
u32 *jpeg_data_buf;						//JPEG���ݻ���buf,ͨ��malloc�����ڴ�

///////////////////////////////////////////////////////////////////////////////////
//JPEG�ߴ�֧���б�
const u16 camera_jpeg_img_size_tbl[][2]=
{
    160,120,	//QQVGA
    176,144,	//QCIF
    320,240,	//QVGA
    400,240,	//WQVGA
    352,288,	//CIF
    640,480,	//VGA
    800,600,	//SVGA
    1024,768,	//XGA
    1280,800,	//WXGA
    1280,960,	//XVGA
    1440,900,	//WXGA+
    1280,1024,	//SXGA
    1600,1200,	//UXGA
};
//����ͷ��ʾ
u8*const camera_remind_tbl[4][GUI_LANGUAGE_NUM]=
{
    {"��ʼ��OV2640,���Ժ�...","��ʼ��OV2640,Ո����...","OV2640 Init,Please wait...",},
    {"δ��⵽OV2640,����...","δ�z�y��OV2640,Ո�z��...","No OV2640 find,Please check...",},
    {"����Ϊ:","�����:","SAVE AS:",},
    {"�ֱ���","�ֱ���","Resolution",},
};
//�s����ʾ
u8*const camera_scalemsg_tbl[2][GUI_LANGUAGE_NUM]=
{
    "1:1��ʾ(������)��","1:1�@ʾ(�o�s��)��","1:1 Display(No Scale)��",
    "ȫ�ߴ����ţ�","ȫ�ߴ�s�ţ�","Full Scale��",
};
u8*const camera_jpegimgsize_tbl[13]=	//JPEGͼƬ 13�ֳߴ�
{"QQVGA","QCIF","QVGA","WQVGA","CIF","VGA","SVGA","XGA","WXGA","XVGA","WXGA+","SXGA","UXGA"};
//���ճɹ���ʾ�����
u8*const camera_saveok_caption[GUI_LANGUAGE_NUM]=
{
    "���ճɹ���","���ճɹ���","Take Photo OK��",
};
//����ʧ����ʾ��Ϣ
u8*const camera_failmsg_tbl[3][GUI_LANGUAGE_NUM]=
{
    "�����ļ�ʧ��,����!","�����ļ�ʧ��,Ո�z��!","Creat File Failed,Please check!",
    "�ڴ治��!","�ȴ治��!","Out of memory!",
    "���ݴ���(ͼƬ�ߴ�̫��)!","�����e�`(�DƬ�ߴ�̫��)!","Data Error(Picture is too big)!",
};
//00������ѡ������
u8*const camera_l00fun_caption[GUI_LANGUAGE_NUM]=
{
    "�������","���C�O��","Camera Set",
};
//00������ѡ���
u8*const camera_l00fun_table[GUI_LANGUAGE_NUM][6]=
{
    {"��������","��Ч����","�ع�ȼ�","��������","ɫ������","�Աȶ�����",},
    {"�����O��","��Ч�O��","�ع�ȼ�","�����O��","ɫ���O��","���ȶ��O��",},
    {"Scene","Effects","Exposure","Brightness","Saturation","Contrast"},
};
//////////////////////////////////////////////////////////////////////////
//10������ѡ���
//����ģʽ
u8*const camera_l10fun_table[GUI_LANGUAGE_NUM][5]=
{
    {"�Զ�","����","����","�칫��","��ͥ",},
    {"�Ԅ�","����","���","�k����","��ͥ",},
    {"Auto","Sunny","Cloudy","Office","Home"},
};
//11������ѡ���
//��Ч����
u8*const camera_l11fun_table[GUI_LANGUAGE_NUM][7]=
{
    {"��ͨ","��Ƭ","�ڰ�","ƫ��ɫ","ƫ��ɫ","ƫ��ɫ","����"},
    {"��ͨ","ؓƬ","�ڰ�","ƫ�tɫ","ƫ�Gɫ","ƫ�{ɫ","�͹�"},
    {"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique",},
};
//12~15������ѡ���
//����-2~2��5��ֵ
u8*const camera_l125fun_table[GUI_LANGUAGE_NUM][5]=
{
    {"-2","-1","0","+1","+2",},
    {"-2","-1","0","+1","+2",},
    {"-2","-1","0","+1","+2",},
};
//////////////////////////////////////////////////////////////////////////

//����JPEG����
//���ɼ���һ֡JPEG���ݺ�,���ô˺���,�л�JPEG BUF.��ʼ��һ֡�ɼ�.
void jpeg_data_process(void)
{
    u16 i;
    u16 rlen;//ʣ�����ݳ���
    u32 *pbuf;
    if(ov2640_mode==OV2640_JPEG_MODE)//ֻ����JPEG��ʽ��,����Ҫ������.
    {
        if(jpeg_data_ok==0)	//jpeg���ݻ�δ�ɼ���?
        {
            DMA2_Stream1->CR&=~(1<<0);		//ֹͣ��ǰ����
            while(DMA2_Stream1->CR&0X01);	//�ȴ�DMA2_Stream1������
            rlen=jpeg_dma_bufsize-DMA2_Stream1->NDTR;//�õ�ʣ�����ݳ���
            pbuf=jpeg_data_buf+jpeg_data_len;//ƫ�Ƶ���Ч����ĩβ,�������
            if(DMA2_Stream1->CR&(1<<19))for(i=0; i<rlen; i++)pbuf[i]=jpeg_buf1[i]; //��ȡbuf1�����ʣ������
            else for(i=0; i<rlen; i++)pbuf[i]=jpeg_buf0[i]; //��ȡbuf0�����ʣ������
            jpeg_data_len+=rlen;			//����ʣ�೤��
            jpeg_data_ok=1; 				//���JPEG���ݲɼ��갴��,�ȴ�������������
        }
        if(jpeg_data_ok==2)	//��һ�ε�jpeg�����Ѿ���������
        {
            DMA2_Stream1->NDTR=jpeg_dma_bufsize;//���䳤��Ϊjpeg_buf_size*4�ֽ�
            DMA2_Stream1->CR|=1<<0;			//���´���
            jpeg_data_ok=0;					//�������δ�ɼ�
            jpeg_data_len=0;				//�������¿�ʼ
        }
    } else
    {
        LCD_SetCursor(0,0);
        LCD_WriteRAM_Prepare();		//��ʼд��GRAM
        hsync_int=1;
    }
}
//jpeg���ݽ��ջص�����
void jpeg_dcmi_rx_callback(void)
{
    u16 i;
    u32 *pbuf;
    pbuf=jpeg_data_buf+jpeg_data_len;//ƫ�Ƶ���Ч����ĩβ
    if(DMA2_Stream1->CR&(1<<19))//buf0����,��������buf1
    {
        for(i=0; i<jpeg_dma_bufsize; i++)pbuf[i]=jpeg_buf0[i]; //��ȡbuf0���������
        jpeg_data_len+=jpeg_dma_bufsize;//ƫ��
    } else //buf1����,��������buf0
    {
        for(i=0; i<jpeg_dma_bufsize; i++)pbuf[i]=jpeg_buf1[i]; //��ȡbuf1���������
        jpeg_data_len+=jpeg_dma_bufsize;//ƫ��
    }
}
//�л�ΪOV2640ģʽ
void sw_ov2640_mode(void)
{
    OV2640_PWDN=0;//OV2640 Power Up
    //GPIOC6/8/9/11�л�Ϊ DCMI�ӿ�
    GPIO_AF_Set(GPIOC,6,13);	//PC6,AF13
    GPIO_AF_Set(GPIOC,8,13);	//PC8,AF13  DCMI_D2
    GPIO_AF_Set(GPIOC,9,13);	//PC9,AF13  DCMI_D3
    GPIO_AF_Set(GPIOC,11,13);	//PC11,AF13 DCMI_D4
}
//�л�ΪSD��ģʽ
void sw_sdcard_mode(void)
{
    OV2640_PWDN=1;//OV2640 Power Down
    //GPIOC6/8/9/11�л�Ϊ SDIO�ӿ�
    GPIO_AF_Set(GPIOC,6,5);		//PC6,AF5
    GPIO_AF_Set(GPIOC,8,12);	//PC8,AF12
    GPIO_AF_Set(GPIOC,9,12);	//PC9,AF12
    GPIO_AF_Set(GPIOC,11,12);	//PC11,AF12
}
//�õ��ļ���,��������ʱ������
//mode:0,����.bmp�ļ�;1,����.jpg�ļ�.
//bmp��ϳ�:����"0:PHOTO/PIC20120321210633.bmp"/"2:PHOTO/PIC20120321210633.bmp"���ļ���
//jpg��ϳ�:����"0:PHOTO/PIC20120321210633.jpg"/"2:PHOTO/PIC20120321210633.jpg"���ļ���
void camera_new_pathname(u8 *pname,u8 mode)
{
    calendar_get_time(&calendar);
    calendar_get_date(&calendar);
    if(mode==0)
    {
        if(gui_phy.memdevflag&(1<<0))sprintf((char*)pname,"0:PHOTO/PIC%04d%02d%02d%02d%02d%02d.bmp",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);		//��ѡ������SD��
        else if(gui_phy.memdevflag&(1<<2))sprintf((char*)pname,"2:PHOTO/PIC%04d%02d%02d%02d%02d%02d.bmp",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);	//SD��������,�򱣴���U��
    } else
    {
        if(gui_phy.memdevflag&(1<<0))sprintf((char*)pname,"0:PHOTO/PIC%04d%02d%02d%02d%02d%02d.jpg",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);		//��ѡ������SD��
        else if(gui_phy.memdevflag&(1<<2))sprintf((char*)pname,"2:PHOTO/PIC%04d%02d%02d%02d%02d%02d.jpg",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);	//SD��������,�򱣴���U��
    }
}
//OV2640����jpgͼƬ
//����ֵ:0,�ɹ�
//    ����,�������
u8 ov2640_jpg_photo(u8 *pname)
{
    FIL* f_jpg;
    u8 res;
    u32 bwr;
    u16 i;
    u8* pbuf;
    f_jpg=(FIL *)gui_memin_malloc(sizeof(FIL));		//����FIL�ֽڵ��ڴ�����
    jpeg_buf0=gui_memin_malloc(jpeg_dma_bufsize*4);	//Ϊjpeg dma���������ڴ�
    jpeg_buf1=gui_memin_malloc(jpeg_dma_bufsize*4);	//Ϊjpeg dma���������ڴ�
    jpeg_data_buf=gui_memex_malloc(210*1024);		//Ϊjpeg�ļ������ڴ�(���210KB)
    if(!f_jpg||!jpeg_buf0||!jpeg_buf1||!jpeg_data_buf)//�ڴ�����ʧ��.
    {
        gui_memin_free(f_jpg);
        gui_memin_free(jpeg_buf0);
        gui_memin_free(jpeg_buf1);
        gui_memex_free(jpeg_data_buf);
        return 0XFF;
    }
    ov2640_mode=OV2640_JPEG_MODE;				//����ΪJPEGģʽ
    sw_ov2640_mode();		//�л�ΪOV2640ģʽ
    dcmi_rx_callback=jpeg_dcmi_rx_callback;//dcmi dma���ջص�����
    DCMI_DMA_Init((u32)jpeg_buf0,(u32)jpeg_buf1,jpeg_dma_bufsize,2,1);;//DCMI DMA����(˫����ģʽ)
    OV2640_JPEG_Mode();		//�л�ΪJPEGģʽ
    OV2640_ImageWin_Set(0,0,1600,1200);
    OV2640_OutSize_Set(camera_jpeg_img_size_tbl[jpeg_size][0],camera_jpeg_img_size_tbl[jpeg_size][1]);//��������ߴ�
    DCMI_Start(); 			//��������
    while(jpeg_data_ok!=1);	//�ȴ���һ֡ͼƬ�ɼ���
    jpeg_data_ok=2;			//���Ա�֡ͼƬ,������һ֡�ɼ�
    while(jpeg_data_ok!=1);	//�ȴ��ڶ�֡ͼƬ�ɼ���
    jpeg_data_ok=2;			//���Ա�֡ͼƬ,������һ֡�ɼ�
    while(jpeg_data_ok!=1);	//�ȴ�����֡ͼƬ�ɼ���,����֡,�ű��浽SD��ȥ.
    DCMI_Stop(); 			//ֹͣDMA����
    ov2640_mode=OV2640_RGB565_MODE;//�л�ΪRGB565ģʽ
    sw_sdcard_mode();		//�л�ΪSD��ģʽ
    res=f_open(f_jpg,(const TCHAR*)pname,FA_WRITE|FA_CREATE_NEW);//ģʽ0,���߳��Դ�ʧ��,�򴴽����ļ�
    if(res==0)
    {
        printf("jpeg data size:%d\r\n",jpeg_data_len*4);//���ڴ�ӡJPEG�ļ���С
        pbuf=(u8*)jpeg_data_buf;
        for(i=0; i<jpeg_data_len*4; i++) //����0XFF,0XD8
        {
            if((pbuf[i]==0XFF)&&(pbuf[i+1]==0XD8))break;
        }
        if(i==jpeg_data_len*4)res=0XFD;//û�ҵ�0XFF,0XD8
        else//�ҵ���
        {
            pbuf+=i;//ƫ�Ƶ�0XFF,0XD8��
            res=f_write(f_jpg,pbuf,jpeg_data_len*4-i,&bwr);
            if(bwr!=(jpeg_data_len*4-i))res=0XFE;
        }
    }
    jpeg_data_len=0;
    f_close(f_jpg);
    sw_ov2640_mode();		//�л�ΪOV2640ģʽ
    OV2640_RGB565_Mode();	//RGB565ģʽ
    DCMI_DMA_Init((u32)&LCD->LCD_RAM,0,1,1,0);//DCMI DMA����
    gui_memin_free(f_jpg);
    gui_memin_free(jpeg_buf0);
    gui_memin_free(jpeg_buf1);
    gui_memex_free(jpeg_data_buf);
    return res;
}

//����ͷ����
//������Ƭ�ļ�,��������SD��PHOTO�ļ�����.
u8 camera_play(void)
{
    u8 rval=0;
    u8 res;
    u8 *caption=0;
    u8 *pname;
    u8 selx=0;
    u8 l00sel=0,l10sel=0,l11sel=0;//Ĭ��ѡ����
    u8 l2345sel[4];
    u8 *psn;
    u8 key;
    u8 scale=1;				//Ĭ����ȫ�ߴ�����
    u8 tcnt=0;
    vu16 tpad_temp_val=tpad_default_val;

    if(audiodev.status&(1<<7))		//��ǰ�ڷŸ�??����ֹͣ
    {
        audio_stop_req(&audiodev);	//ֹͣ��Ƶ����
        audio_task_delete();		//ɾ�����ֲ�������.
    }
    //��ʾ��ʼ���OV2640
    window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)camera_remind_tbl[0][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
    if(gui_phy.memdevflag&(1<<0))f_mkdir("0:PHOTO");//ǿ�ƴ����ļ���,���������
    if(gui_phy.memdevflag&(1<<2))f_mkdir("2:PHOTO");//ǿ�ƴ����ļ���,���������
    if(OV2640_Init())//��ʼ��ov2640
    {
        window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)camera_remind_tbl[1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
        delay_ms(500);
        rval=1;
    }
    pname=gui_memin_malloc(40);	//����40���ֽ��ڴ�,���ڴ���ļ���
    psn=gui_memin_malloc(50);	//����50���ֽ��ڴ�,���ڴ�����ƣ�������Ϊ:0:PHOTO/PIC20120321210633.bmp"������ʾ��
    if(!pname||!psn)rval=1;//����ʧ��
    if(rval==0)//OV2640����
    {
        OV2640_RGB565_Mode();	//RGB565ģʽ

        l2345sel[0]=2;//�ع�����2,ʵ��ֵ0
        l2345sel[1]=2;//����Ĭ��Ϊ2,ʵ��ֵ0
        l2345sel[2]=2;//ɫ��Ĭ��Ϊ2,ʵ��ֵ0
        l2345sel[3]=2;//�Աȶ�Ĭ��Ϊ2,ʵ��ֵ0

        OV2640_Auto_Exposure(l2345sel[0]);   	//�Զ��ع�����
        OV2640_Brightness(l2345sel[1]);	   		//��������
        OV2640_Color_Saturation(l2345sel[2]);	//ɫ������
        OV2640_Contrast(l2345sel[3]);			//�Աȶ�����

        DCMI_Init();			//DCMI����
        DCMI_DMA_Init((u32)&LCD->LCD_RAM,0,1,1,0);//DCMI DMA����
        OV2640_OutSize_Set(lcddev.width,lcddev.height);//��������ͷ����ߴ�ΪLCD�ĳߴ��С
        DCMI_Start(); 			//��������
        delay_ms(200);
        //��Ϊ����ͷHREF��PCLK��TPAD����ż����м�,��������ͷ��,���нϴ�Ӱ��,�����³�ʼ��TPAD
        OSTaskSuspend(3); 		//����watch_task
        TPAD_Init(16);			//���³�ʼ��TPAD
        OSTaskResume(3);		//�ָ�watch_task
        delay_ms(200);
        system_task_return=0;	//���TPAD
        jpeg_size=12;			//JPEG����,Ĭ������Ϊ1600*1200�ֱ���(UXGA)
        while(1)
        {
            tp_dev.scan(0);
            if(tp_dev.sta&TP_PRES_DOWN)
            {
                DCMI_Stop();
                sw_sdcard_mode();	//�л�ΪSD��ģʽ
                caption=(u8*)camera_l00fun_caption[gui_phy.language];
                res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*6)/2,160,72+32*6,(u8**)camera_l00fun_table[gui_phy.language],6,(u8*)&l00sel,0X90,caption);//��ѡ
                sw_ov2640_mode();	//�л�ΪOV2640ģʽ
                if(res==0)
                {
                    DCMI_Start();
                    delay_ms(200);
                    DCMI_Stop();
                    sw_sdcard_mode();	//�л�ΪSD��ģʽ
                    caption=(u8*)camera_l00fun_table[gui_phy.language][l00sel];
                    switch(l00sel)
                    {
                    case 0://��������
                        res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*5)/2,160,72+32*5,(u8**)camera_l10fun_table[gui_phy.language],5,(u8*)&l10sel,0X90,caption);//��ѡ
                        sw_ov2640_mode();//�л�ΪOV2640ģʽ
                        if(res==0)
                        {
                            OV2640_Light_Mode(l10sel);
                        }
                        break;
                    case 1://��Ч����
                        res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*7)/2,160,72+32*7,(u8**)camera_l11fun_table[gui_phy.language],7,(u8*)&l11sel,0X90,caption);//��ѡ
                        sw_ov2640_mode();//�л�ΪOV2640ģʽ
                        if(res==0)
                        {
                            OV2640_Special_Effects(l11sel);
                        }
                        break;
                    case 2://�ع�����
                    case 3://��������
                    case 4://ɫ������
                    case 5://�Աȶ�����
                        selx=l2345sel[l00sel-2];//�õ�֮ǰ��ѡ��
                        res=app_items_sel((lcddev.width-160)/2,(lcddev.height-72-32*5)/2,160,72+32*5,(u8**)camera_l125fun_table[gui_phy.language],5,(u8*)&selx,0X90,caption);//��ѡ
                        sw_ov2640_mode();//�л�ΪOV2640ģʽ
                        if(res==0)
                        {
                            l2345sel[l00sel-2]=selx;//��¼��ֵ
                            if(l00sel==2)OV2640_Auto_Exposure(selx);   	//�Զ��ع�����
                            if(l00sel==3)OV2640_Brightness(selx);	   	//��������
                            if(l00sel==4)OV2640_Color_Saturation(selx);	//ɫ������
                            if(l00sel==5)OV2640_Contrast(selx);			//�Աȶ�����
                        }
                        break;
                    }
                }
                DCMI_Start();
            }
            if(system_task_return)break;//TPAD����
            key=KEY_Scan(0);//����ɨ��
            if(key)
            {
                DCMI_Stop();
                while(KEY_Scan(1));//�ȴ������ɿ�
                tcnt=0;
                switch(key)
                {
                case KEY0_PRES:	//KEY0����,JPEG����
                case KEY2_PRES:	//KEY2����,BMP����
                    LED1=0;		//DS1��,��ʾ������
                    sw_sdcard_mode();	//�л�ΪSD��ģʽ
                    if(key==KEY0_PRES)	//JPEG����
                    {
                        camera_new_pathname(pname,OV2640_JPEG_MODE);//�õ�jpg�ļ���
                        res=ov2640_jpg_photo(pname);
                    } else//BMP����
                    {
                        camera_new_pathname(pname,OV2640_RGB565_MODE);//�õ�bmp�ļ���
                        res=bmp_encode(pname,0,0,lcddev.width,lcddev.height,0);//bmp����
                    }
                    if(res)//����ʧ����
                    {
                        if(res==0XFF)window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)camera_failmsg_tbl[1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//�ڴ����
                        else if(res==0XFD)window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)camera_failmsg_tbl[2][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//���ݴ���
                        else window_msg_box((lcddev.width-200)/2,(lcddev.height-100)/2,200,100,(u8*)camera_failmsg_tbl[0][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);//��ʾSD���Ƿ����
                    } else
                    {
                        strcpy((char*)psn,(const char *)camera_remind_tbl[2][gui_phy.language]);
                        strcat((char*)psn,(const char *)pname);
                        window_msg_box((lcddev.width-180)/2,(lcddev.height-80)/2,180,80,psn,(u8*)camera_saveok_caption[gui_phy.language],12,0,0,0);
                        BEEP=1;	//�������̽У���ʾ�������
                        delay_ms(100);
                    }
                    sw_ov2640_mode();	//�л�ΪOV2640ģʽ
                    LED1=1;				//DS1��,��ʾ�������
                    BEEP=0;				//�������̽�
                    delay_ms(2000);
                    if(scale==0)
                    {
                        OV2640_ImageWin_Set((1600-lcddev.width)/2,(1200-lcddev.height)/2,lcddev.width,lcddev.height);//1:1��ʵ�ߴ�
                        OV2640_OutSize_Set(lcddev.width,lcddev.height);
                    } else
                    {
                        OV2640_ImageWin_Set(0,0,1600,1200);	//ȫ�ߴ�����
                    }
                    OV2640_OutSize_Set(lcddev.width,lcddev.height);
                    system_task_return=0;//���TPAD
                    break;
                case KEY1_PRES:	//KEY1����,����/1:1��ʾ(������)
                    scale=!scale;
                    if(scale==0)OV2640_ImageWin_Set((1600-lcddev.width)/2,(1200-lcddev.height)/2,lcddev.width,lcddev.height);//1:1��ʵ�ߴ�
                    else OV2640_ImageWin_Set(0,0,1600,1200);				//ȫ�ߴ�����
                    OV2640_OutSize_Set(lcddev.width,lcddev.height);
                    window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)camera_scalemsg_tbl[scale][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
                    while(KEY_Scan(1)==0&&tcnt<80)//�ȴ�800ms,���û�а������µĻ�.
                    {
                        delay_ms(10);
                        tcnt++;
                    }
                    break;
                case WKUP_PRES://�ֱ�������
                    jpeg_size++;
                    if(jpeg_size>12)jpeg_size=0;
                    sprintf((char*)psn,"%s:%dX%d(%s)",camera_remind_tbl[3][gui_phy.language],camera_jpeg_img_size_tbl[jpeg_size][0],camera_jpeg_img_size_tbl[jpeg_size][1],camera_jpegimgsize_tbl[jpeg_size]);
                    window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,psn,(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
                    while(KEY_Scan(1)==0&&tcnt<80)//�ȴ�800ms,���û�а������µĻ�.
                    {
                        delay_ms(10);
                        tcnt++;
                    }
                    break;

                }
                sw_ov2640_mode();//�л�ΪOV2640ģʽ
                DCMI_Start();
            }
            if(hsync_int)//�ող���֡�ж�,������ʱ
            {
                delay_ms(10);
                hsync_int=0;
            }
        }
    }
    DCMI_Stop();		//ֹͣ����ͷ����
    sw_sdcard_mode();	//�л�ΪSD��ģʽ
    gui_memin_free(pname);
    gui_memin_free(psn);
    TPAD_Init(8);		//���³�ʼ��TPAD
    tpad_default_val=tpad_temp_val;//�ָ�ԭ����ֵ
    return 0;
}















