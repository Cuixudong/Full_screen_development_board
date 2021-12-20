#include "nes_main.h" 
#include "nes_ppu.h"
#include "nes_mapper.h"
#include "nes_apu.h"

#include "malloc.h" 
#include "key.h"
#include "lcd.h" 
#include "audioplay.h"
#include "i2s.h" 
#include "usb_app.h"
#include "ff.h"
#include "string.h"
#include "usart.h"
#include "spb.h"
//////////////////////////////////////////////////////////////////////////////////	 
//��������ֲ������ye781205��NESģ��������
//ALIENTEK STM32F407������
//NES������ ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/1
//�汾��V1.0  			  
////////////////////////////////////////////////////////////////////////////////// 	 
 

u8 nes_frame_cnt;		//nes֡������ 
int MapperNo;			//map���
int NES_scanline;		//nesɨ����
int VROM_1K_SIZE;
int VROM_8K_SIZE;
u32 NESrom_crc32;

u8 PADdata0;   			//�ֱ�1��ֵ [7:0]��7 ��6 ��5 ��4 Start3 Select2 B1 A0  
u8 PADdata1;   			//�ֱ�2��ֵ [7:0]��7 ��6 ��5 ��4 Start3 Select2 B1 A0  
u8 *NES_RAM;			//����1024�ֽڶ���
u8 *NES_SRAM;  
NES_header *RomHeader; 	//rom�ļ�ͷ
MAPPER *NES_Mapper;		 
MapperCommRes *MAPx;  


u8* spr_ram;			//����RAM,256�ֽ�
ppu_data* ppu;			//ppuָ��
u8* VROM_banks;
u8* VROM_tiles;

apu_t *apu; 			//apuָ��
u16 *wave_buffers; 		
u16 *i2sbuf1; 			//��Ƶ����֡,ռ���ڴ��� 367*4 �ֽ�@22050Hz
u16 *i2sbuf2; 			//��Ƶ����֡,ռ���ڴ��� 367*4 �ֽ�@22050Hz

u8* romfile;			//nes�ļ�ָ��,ָ������nes�ļ�����ʼ��ַ.
//////////////////////////////////////////////////////////////////////////////////////

 
//����ROM
//����ֵ:0,�ɹ�
//    1,�ڴ����
//    3,map����
u8 nes_load_rom(void)
{  
    u8* p;  
	u8 i;
	u8 res=0;
	p=(u8*)romfile;	
	if(strncmp((char*)p,"NES",3)==0)
	{  
		RomHeader->ctrl_z=p[3];
		RomHeader->num_16k_rom_banks=p[4];
		RomHeader->num_8k_vrom_banks=p[5];
		RomHeader->flags_1=p[6];
		RomHeader->flags_2=p[7]; 
		if(RomHeader->flags_1&0x04)p+=512;		//��512�ֽڵ�trainer:
		if(RomHeader->num_8k_vrom_banks>0)		//����VROM,����Ԥ����
		{		
			VROM_banks=p+16+(RomHeader->num_16k_rom_banks*0x4000);
#if	NES_RAM_SPEED==1	//1:�ڴ�ռ��С 0:�ٶȿ�	 
			VROM_tiles=VROM_banks;	 
#else  
			VROM_tiles=mymalloc(SRAMEX,RomHeader->num_8k_vrom_banks*8*1024);//�������������1MB�ڴ�!!!
			if(VROM_tiles==0)VROM_tiles=VROM_banks;//�ڴ治���õ������,����VROM_titles��VROM_banks�����ڴ�			
			compile(RomHeader->num_8k_vrom_banks*8*1024/16,VROM_banks,VROM_tiles);  
#endif	
		}else 
		{
			VROM_banks=mymalloc(SRAMIN,8*1024);
			VROM_tiles=mymalloc(SRAMEX,8*1024);
			if(!VROM_banks||!VROM_tiles)res=1;
		}  	
		VROM_1K_SIZE = RomHeader->num_8k_vrom_banks * 8;
		VROM_8K_SIZE = RomHeader->num_8k_vrom_banks;  
		MapperNo=(RomHeader->flags_1>>4)|(RomHeader->flags_2&0xf0);
		if(RomHeader->flags_2 & 0x0E)MapperNo=RomHeader->flags_1>>4;//���Ը���λ�����ͷ����������� 
		printf("use map:%d\r\n",MapperNo);
		for(i=0;i<255;i++)  // ����֧�ֵ�Mapper��
		{		
			if (MapTab[i]==MapperNo)break;		
			if (MapTab[i]==-1)res=3; 
		} 
		if(res==0)
		{
			switch(MapperNo)
			{
				case 1:  
					MAP1=mymalloc(SRAMIN,sizeof(Mapper1Res)); 
					if(!MAP1)res=1;
					break;
				case 4:  
				case 6: 
				case 16:
				case 17:
				case 18:
				case 19:
				case 21: 
				case 23:
				case 24:
				case 25:
				case 64:
				case 65:
				case 67:
				case 69:
				case 85:
				case 189:
					MAPx=mymalloc(SRAMIN,sizeof(MapperCommRes)); 
					if(!MAPx)res=1;
					break;  
				default:
					break;
			}
		}
	} 
	return res;	//����ִ�н��
} 
//�ͷ��ڴ� 
void nes_sram_free(void)
{ 
	myfree(SRAMIN,NES_RAM);		
	myfree(SRAMIN,NES_SRAM);	
	myfree(SRAMIN,RomHeader);	
	myfree(SRAMIN,NES_Mapper);
	myfree(SRAMIN,spr_ram);		
	myfree(SRAMIN,ppu);	
	myfree(SRAMIN,apu);	
	myfree(SRAMIN,wave_buffers);	
	myfree(SRAMIN,i2sbuf1);	
	myfree(SRAMIN,i2sbuf2);	 
	myfree(SRAMEX,romfile);	  
	if((VROM_tiles!=VROM_banks)&&VROM_banks&&VROM_tiles)//����ֱ�ΪVROM_banks��VROM_tiles�������ڴ�,���ͷ�
	{
		myfree(SRAMIN,VROM_banks);
		myfree(SRAMEX,VROM_tiles);		 
	}
	switch (MapperNo)//�ͷ�map�ڴ�
	{
		case 1: 			//�ͷ��ڴ�
			myfree(SRAMIN,MAP1);
			break;	 	
		case 4: 
		case 6: 
		case 16:
		case 17:
		case 18:
		case 19:
		case 21:
		case 23:
		case 24:
		case 25:
		case 64:
		case 65:
		case 67:
		case 69:
		case 85:
		case 189:
			myfree(SRAMIN,MAPx);break;	 		//�ͷ��ڴ� 
		default:break; 
	}
	NES_RAM=0;	
	NES_SRAM=0;
	RomHeader=0;
	NES_Mapper=0;
	spr_ram=0;
	ppu=0;
	apu=0;
	wave_buffers=0;
	i2sbuf1=0;
	i2sbuf2=0;
	romfile=0; 
	VROM_banks=0;
	VROM_tiles=0; 
	MAP1=0;
	MAPx=0;
} 
//ΪNES���������ڴ�
//romsize:nes�ļ���С
//����ֵ:0,����ɹ�
//       1,����ʧ��
u8 nes_sram_malloc(u32 romsize)
{
	u16 i=0;
	for(i=0;i<64;i++)//ΪNES_RAM,����1024������ڴ�
	{
		NES_SRAM=mymalloc(SRAMIN,i*32);
		NES_RAM=mymalloc(SRAMIN,0X800);	//����2K�ֽ�,����1024�ֽڶ���
		if((u32)NES_RAM%1024)			//����1024�ֽڶ���
		{
			myfree(SRAMIN,NES_RAM);		//�ͷ��ڴ�,Ȼ�����³��Է���
			myfree(SRAMIN,NES_SRAM); 
		}else 
		{
			myfree(SRAMIN,NES_SRAM); 	//�ͷ��ڴ�
			break;
		}
	}	 
 	NES_SRAM=mymalloc(SRAMIN,0X2000);
	RomHeader=mymalloc(SRAMIN,sizeof(NES_header));
	NES_Mapper=mymalloc(SRAMIN,sizeof(MAPPER));
	spr_ram=mymalloc(SRAMIN,0X100);		
	ppu=mymalloc(SRAMIN,sizeof(ppu_data));  
	apu=mymalloc(SRAMIN,sizeof(apu_t));		//sizeof(apu_t)=  12588
	wave_buffers=mymalloc(SRAMIN,APU_PCMBUF_SIZE*2);
	i2sbuf1=mymalloc(SRAMIN,APU_PCMBUF_SIZE*4+10);
	i2sbuf2=mymalloc(SRAMIN,APU_PCMBUF_SIZE*4+10);
 	romfile=mymalloc(SRAMEX,romsize);			//������Ϸrom�ռ�,����nes�ļ���С 
	if(romfile==NULL)//�ڴ治��?�ͷ�������ռ���ڴ�,����������
	{
		spb_delete();//�ͷ�SPBռ�õ��ڴ�
		romfile=mymalloc(SRAMEX,romsize);//��������
	}
	if(i==64||!NES_RAM||!NES_SRAM||!RomHeader||!NES_Mapper||!spr_ram||!ppu||!apu||!wave_buffers||!i2sbuf1||!i2sbuf2||!romfile)
	{
		nes_sram_free();
		return 1;
	}
	memset(NES_SRAM,0,0X2000);				//����
	memset(RomHeader,0,sizeof(NES_header));	//����
	memset(NES_Mapper,0,sizeof(MAPPER));	//����
	memset(spr_ram,0,0X100);				//����
	memset(ppu,0,sizeof(ppu_data));			//����
	memset(apu,0,sizeof(apu_t));			//����
	memset(wave_buffers,0,APU_PCMBUF_SIZE*2);//����
	memset(i2sbuf1,0,APU_PCMBUF_SIZE*4+10);	//����
	memset(i2sbuf2,0,APU_PCMBUF_SIZE*4+10);	//����
	memset(romfile,0,romsize);				//���� 
	return 0;
} 
//��ʼnes��Ϸ
//pname:nes��Ϸ·��
//����ֵ:
//0,�����˳�
//1,�ڴ����
//2,�ļ�����
//3,��֧�ֵ�map
u8 nes_load(u8* pname)
{
	FIL *file; 
	UINT br;
	u8 res=0;  
	if(audiodev.status&(1<<7))//��ǰ�ڷŸ�??
	{
		audio_stop_req(&audiodev);	//ֹͣ��Ƶ����
		audio_task_delete();		//ɾ�����ֲ�������.
	}  
	app_wm8978_volset(wm8978set.mvol);	 
	WM8978_ADDA_Cfg(1,0);	//����DAC
	WM8978_Input_Cfg(0,0,0);//�ر�����ͨ��
	WM8978_Output_Cfg(1,0);	//����DAC���
	
	file=mymalloc(SRAMIN,sizeof(FIL));  
	if(file==0)return 1;						//�ڴ�����ʧ��.  
	res=f_open(file,(char*)pname,FA_READ);
	if(res!=FR_OK)	//���ļ�ʧ��
	{
		myfree(SRAMIN,file);
		return 2;
	}	 
	res=nes_sram_malloc(file->fsize);			//�����ڴ� 
	if(res==0)
	{
		f_read(file,romfile,file->fsize,&br);	//��ȡnes�ļ�
		NESrom_crc32=get_crc32(romfile+16, file->fsize-16);//��ȡCRC32��ֵ	
		res=nes_load_rom();						//����ROM
		if(res==0) 					
		{   
			cpu6502_init();						//��ʼ��6502,����λ	 
			Mapper_Init();						//map��ʼ�� 	 
			PPU_reset();						//ppu��λ
			apu_init(); 						//apu��ʼ�� 
			nes_sound_open(0,APU_SAMPLE_RATE);	//��ʼ�������豸
			nes_emulate_frame();				//����NESģ������ѭ�� 
			nes_sound_close();					//�ر��������
		}
	}
	f_close(file);
	myfree(SRAMIN,file);//�ͷ��ڴ�
	nes_sram_free();	//�ͷ��ڴ�
	return res;
}  
u8 nes_xoff=0;	//��ʾ��x�᷽���ƫ����(ʵ����ʾ���=256-2*nes_xoff)
//������Ϸ��ʾ����
void nes_set_window(void)
{	
	u16 xoff=0,yoff=0; 
	u16 lcdwidth,lcdheight;
	if(lcddev.width==240)
	{
		lcdwidth=240;
		lcdheight=240;
		nes_xoff=(256-lcddev.width)/2;	//�õ�x�᷽���ƫ����
 		xoff=0; 
	}else if(lcddev.width==320) 
	{
		lcdwidth=256;
		lcdheight=240; 
		nes_xoff=0;
		xoff=(lcddev.width-256)/2;
	}else if(lcddev.width==480)
	{
		lcdwidth=480;
		lcdheight=480; 
		nes_xoff=(256-(lcddev.width/2))/2;//�õ�x�᷽���ƫ����
 		xoff=0;  
	}	
	yoff=(lcddev.height-lcdheight-gui_phy.tbheight)/2+gui_phy.tbheight;//��Ļ�߶� 
	LCD_Set_Window(xoff,yoff,lcdwidth,lcdheight);//��NESʼ������Ļ����������ʾ
	LCD_SetCursor(xoff,yoff);
	LCD_WriteRAM_Prepare();//д��LCD RAM��׼��  
}
extern void KEYBRD_FCPAD_Decode(uint8_t *fcbuf,uint8_t mode);
//��ȡ��Ϸ�ֱ�����
void nes_get_gamepadval(void)
{  
	u8 *pt;
	while((usbx.bDeviceState&0XC0)==0X40)//USB�豸������,���ǻ�û���ӳɹ�,�Ͳ�ѯ.
	{
		usbapp_pulling();	//��ѯ����USB����
	}
	usbapp_pulling();		//��ѯ����USB����
	if(usbx.hdevclass==4)	//USB��Ϸ�ֱ�
	{	
		PADdata0=fcpad.ctrlval;
		PADdata1=0;
	}else if(usbx.hdevclass==3)//USB����ģ���ֱ�
	{
		KEYBRD_FCPAD_Decode(pt,0);
		PADdata0=fcpad.ctrlval;
		PADdata1=fcpad1.ctrlval; 
	}	
}    
//nesģ������ѭ��
void nes_emulate_frame(void)
{  
	u8 nes_frame;
	TIM3_Int_Init(10000-1,8400-1);//����TIM3 ,1s�ж�һ��	
	nes_set_window();//���ô���
	while(1)
	{	
		// LINES 0-239
		PPU_start_frame();
		for(NES_scanline = 0; NES_scanline< 240; NES_scanline++)
		{
			run6502(113*256);
			NES_Mapper->HSync(NES_scanline);
			//ɨ��һ��		  
			if(nes_frame==0)scanline_draw(NES_scanline);
			else do_scanline_and_dont_draw(NES_scanline); 
		}  
		NES_scanline=240;
		run6502(113*256);//����1��
		NES_Mapper->HSync(NES_scanline); 
		start_vblank(); 
		if(NMI_enabled()) 
		{
			cpunmi=1;
			run6502(7*256);//�����ж�
		}
		NES_Mapper->VSync();
		// LINES 242-261    
		for(NES_scanline=241;NES_scanline<262;NES_scanline++)
		{
			run6502(113*256);	  
			NES_Mapper->HSync(NES_scanline);		  
		}	   
		end_vblank(); 
		nes_get_gamepadval();//ÿ3֡��ѯһ��USB
		apu_soundoutput();//�����Ϸ����	 
		nes_frame_cnt++; 	
		nes_frame++;
		if(nes_frame>NES_SKIP_FRAME)nes_frame=0;//��֡ 
		if(system_task_return)break;//TPAD����  
		if(spbdev.spbheight==0&&spbdev.spbwidth==0)//�����������¼���Ҫ�������ô���
		{
			nes_set_window();
		}
	}
	LCD_Set_Window(0,0,lcddev.width,lcddev.height);//�ָ���Ļ����
	TIM3->CR1&=~(1<<0);//�رն�ʱ��3
}
//��6502.s���汻����
void debug_6502(u16 reg0,u8 reg1)
{
	printf("6502 error:%x,%d\r\n",reg0,reg1);
}
////////////////////////////////////////////////////////////////////////////////// 	 
//nes,��Ƶ���֧�ֲ���
vu8 nestransferend=0;	//i2s������ɱ�־
vu8 neswitchbuf=0;		//i2sbufxָʾ��־
//I2S��Ƶ���Żص�����
void nes_i2s_dma_tx_callback(void)
{  
	if(DMA1_Stream4->CR&(1<<19))neswitchbuf=0; 
	else neswitchbuf=1;  
	nestransferend=1;
}
//NES����Ƶ���
int nes_sound_open(int samples_per_sync,int sample_rate) 
{
	printf("sound open:%d\r\n",sample_rate);
	WM8978_ADDA_Cfg(1,0);	//����DAC
	WM8978_Input_Cfg(0,0,0);//�ر�����ͨ��
	WM8978_Output_Cfg(1,0);	//����DAC���  
	WM8978_I2S_Cfg(2,0);	//�����ֱ�׼,16λ���ݳ���
	app_wm8978_volset(wm8978set.mvol);
	I2S2_Init(0,2,0,1);		//�����ֱ�׼,��������,ʱ�ӵ͵�ƽ��Ч,16λ��չ֡����
	I2S2_SampleRate_Set(sample_rate);		//���ò�����
	I2S2_TX_DMA_Init((u8*)i2sbuf1,(u8*)i2sbuf2,2*APU_PCMBUF_SIZE);//DMA���� 
 	i2s_tx_callback=nes_i2s_dma_tx_callback;//�ص�����ָwav_i2s_dma_callback
	I2S_Play_Start();						//����DMA    
	return 1;
}
//NES�ر���Ƶ���
void nes_sound_close(void) 
{ 
	I2S_Play_Stop();
	app_wm8978_volset(0);				//�ر�WM8978�������
} 
//NES��Ƶ�����I2S����
void nes_apu_fill_buffer(int samples,u16* wavebuf)
{	
 	int i;	 
	while(!nestransferend)//�ȴ���Ƶ�������
	{
		delay_ms(5);
	}
	nestransferend=0;
    if(neswitchbuf==0)
	{
		for(i=0;i<APU_PCMBUF_SIZE;i++)
		{
			i2sbuf1[2*i]=wavebuf[i];
			i2sbuf1[2*i+1]=wavebuf[i];
		}
	}else 
	{
		for(i=0;i<APU_PCMBUF_SIZE;i++)
		{
			i2sbuf2[2*i]=wavebuf[i];
			i2sbuf2[2*i+1]=wavebuf[i];
		}
	}
} 



















