#include "nesplay.h"
#include "nes_main.h"
#include "usb_app.h"
#include "spb.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//APP-NESģ���� ����
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

u8 *rom_file;
u8*const nes_caption_tbl[GUI_LANGUAGE_NUM]= {"NESģ����","NESģ�M��","NES Emulator",};
u8*const nes_remindmsg_tbl[4][GUI_LANGUAGE_NUM]=
{
    {"���Ȱε�U��...","Ո�Ȱε�U�P...","Please pull U disk first...",},
    {"�����USB�ֱ�/����!","Ո����USB�ֱ�/�I�P!","Please plug USB gamepad/keyboard!",},
    {"��⵽����!","�z�y���I�P!","Keyboard detected!",},
    {"��⵽��Ϸ�ֱ�!","�z�y���[���ֱ�!","Gamepad detected!",},
};
//������ʾ
u8*const nes_errormsg_tbl[3][GUI_LANGUAGE_NUM]=
{
    {"�ڴ治��!","�ȴ治��!","Out of memory!",},
    {"�ļ���ȡ����!","�ļ��xȡ�e�`!","Read file error!",},
    {"MAP��֧��!","MAP��֧��!","Not supported MAP!",},
};

//������Ϸ����
void nes_load_ui(void)
{
    app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X05);//��ʾ����
    gui_fill_rectangle(0,20,lcddev.width,lcddev.height-20,BLACK);//����ɫ
}
//NES��Ϸ
u8 nes_play(void)
{
    DIR nesdir;		//nesdirר��
    FILINFO nesinfo;
    u8 res;
    u8 rval=0;			//����ֵ
    u8 *pname=0;
    u8 *fn;
    u8 remindflag=0;

    _btn_obj* rbtn;		//���ذ�ť�ؼ�
    _filelistbox_obj * flistbox;
    _filelistbox_list * filelistx; 	//�ļ�

    //���U����λ,��ʾҪ�ε�U��
    if(gui_phy.memdevflag&(1<<2))
    {
        window_msg_box((lcddev.width-220)/2,(lcddev.height-100)/2,220,100,(u8*)nes_remindmsg_tbl[0][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
        while(gui_phy.memdevflag&(1<<2))
        {
            delay_ms(5);//��ѭ���ȴ�U�̱��γ�
        }
    }
    usbapp_mode_set(USBH_HID_MODE);	//����USBΪHIDģʽ
    LCD_Clear(BLACK);
    //��ʾ�����ֱ�/����
    window_msg_box((lcddev.width-220)/2,(lcddev.height-100)/2,220,100,(u8*)nes_remindmsg_tbl[1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
    delay_ms(1000);
    app_filebrower((u8*)APP_MFUNS_CAPTION_TBL[6][gui_phy.language],0X07);	//ѡ��Ŀ���ļ�,���õ�Ŀ������
    flistbox=filelistbox_creat(0,gui_phy.tbheight,lcddev.width,lcddev.height-gui_phy.tbheight*2,1,gui_phy.listfsize);//����һ��filelistbox
    if(flistbox==NULL)rval=1;							//�����ڴ�ʧ��.
    else
    {
        flistbox->fliter=FLBOX_FLT_NES;	//�����ı��ļ�
        filelistbox_add_disk(flistbox);	//��Ӵ���·��
        filelistbox_draw_listbox(flistbox);
    }
    //Ϊ���ļ������뻺����
    nesinfo.lfsize=_MAX_LFN*2+1;
    nesinfo.lfname=gui_memin_malloc(nesinfo.lfsize);
    if(nesinfo.lfname==NULL)rval=1;//�����ڴ�ʧ��
    else gui_memset((u8*)nesinfo.lfname,0,nesinfo.lfsize);
    rbtn=btn_creat(lcddev.width-2*gui_phy.tbfsize-8-1,lcddev.height-gui_phy.tbheight,2*gui_phy.tbfsize+8,gui_phy.tbheight-1,0,0x03);//�������ְ�ť
    if(rbtn==NULL)rval=1;	//û���㹻�ڴ湻����
    else
    {
        rbtn->caption=(u8*)GUI_BACK_CAPTION_TBL[gui_phy.language];//����
        rbtn->font=gui_phy.tbfsize;//�����µ������С
        rbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
        rbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
        btn_draw(rbtn);//����ť
    }
    while(rval==0)
    {
        tp_dev.scan(0);
        in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ
        delay_ms(5);
        if(system_task_return)break;	  		//TPAD����
        filelistbox_check(flistbox,&in_obj);	//ɨ���ļ�
        res=btn_check(rbtn,&in_obj);
        if(res)
        {
            if(((rbtn->sta&0X80)==0))//��ť״̬�ı���
            {
                if(flistbox->dbclick!=0X81)
                {
                    filelistx=filelist_search(flistbox->list,flistbox->selindex);//�õ���ʱѡ�е�list����Ϣ
                    if(filelistx->type==FICO_DISK)//�Ѿ�������������
                    {
                        break;
                    } else filelistbox_back(flistbox);//�˻���һ��Ŀ¼
                }
            }
        }
        if(flistbox->dbclick==0X81)//˫���ļ���
        {
            rval=f_opendir(&nesdir,(const TCHAR*)flistbox->path); //��ѡ�е�Ŀ¼
            if(rval)break;
            dir_sdi(&nesdir,flistbox->findextbl[flistbox->selindex-flistbox->foldercnt]);
            rval=f_readdir(&nesdir,&nesinfo);//��ȡ�ļ���Ϣ
            if(rval)break;//�򿪳ɹ�
            fn=(u8*)(*nesinfo.lfname?nesinfo.lfname:nesinfo.fname);
            pname=gui_memin_malloc(strlen((const char*)fn)+strlen((const char*)flistbox->path)+2);//�����ڴ�
            if(pname==NULL)rval=1;//����ʧ��
            else
            {
                pname=gui_path_name(pname,flistbox->path,fn);//�ļ�������·��
                LCD_Clear(BLACK);
                app_filebrower(fn,0X05);//��ʾ��ǰ���������Ϸ����
                res=nes_load(pname);	//��ʼnes��Ϸ
                if(res)
                {
                    window_msg_box((lcddev.width-220)/2,(lcddev.height-100)/2,220,100,(u8*)nes_errormsg_tbl[res-1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
                    delay_ms(1200);
                }
                system_task_return=0;	//�˳���־����
            }
            flistbox->dbclick=0;	//���÷��ļ����״̬
            gui_memin_free(pname);	//�ͷ��ڴ�
            pname=NULL;
            app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X07);//ѡ��Ŀ���ļ�,���õ�Ŀ������
            btn_draw(rbtn);//����ť
            delay_ms(100);
            filelistbox_rebuild_filelist(flistbox);//�ؽ�flistbox
            system_task_return=0;//�ո��˳����������Ϸ,�������˳����ѭ��
        }
        while((usbx.bDeviceState&0XC0)==0X40)//USB�豸������,���ǻ�û���ӳɹ�,�Ͳ�ѯ.
        {
            usbapp_pulling();	//��ѯ����USB����
        }
        usbapp_pulling();		//��ѯ����USB����
        if(remindflag==0)
        {
            if(usbx.hdevclass==3||usbx.hdevclass==4)
            {
                window_msg_box((lcddev.width-220)/2,(lcddev.height-100)/2,220,100,(u8*)nes_remindmsg_tbl[usbx.hdevclass-1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
                delay_ms(800);
                filelistbox_rebuild_filelist(flistbox);//�ؽ�flistbox
                remindflag=1;
            }
        }
        if(usbx.bDeviceState==0)remindflag=0;
    }
    filelistbox_delete(flistbox);	//ɾ��filelist
    btn_delete(rbtn);				//ɾ����ť
    gui_memin_free(pname);			//�ͷ��ڴ�
    gui_memin_free(nesinfo.lfname);
    usbapp_mode_set(USBH_MSC_MODE);	//�ָ�USBΪUSBH MSCģʽ
    return rval;
}






















