#include "nes_main.h" 
#include "nes_ppu.h"
#include "nes_mapper.h"
#include "nes_apu.h"
#include "usart3.h"	
#include "malloc.h" 
#include "key.h"
#include "lcd.h"    
#include "ff.h"
#include "string.h"
#include "usart.h" 
#include "timer.h" 
#include "joypad.h"    	
#include "vs10xx.h"    	
#include "spi.h"      	
#include "audioplay.h"     	
#include "spb.h"     

//////////////////////////////////////////////////////////////////////////////////	 
//��������ֲ������ye781205��NESģ��������
//ALIENTEK STM32������
//NES������ ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/1
//�汾��V1.0  			  
////////////////////////////////////////////////////////////////////////////////// 	 
 

extern vu8 frame_cnt;	//֡������ 
int MapperNo;			//map���
int NES_scanline;		//nesɨ����
int VROM_1K_SIZE;
int VROM_8K_SIZE;
u32 NESrom_crc32;

uint8_t PADdata0;   			//�ֱ�1��ֵ [7:0]��7 ��6 ��5 ��4 Start3 Select2 B1 A0  
uint8_t PADdata1;   			//�ֱ�2��ֵ [7:0]��7 ��6 ��5 ��4 Start3 Select2 B1 A0  
uint8_t *NES_RAM;			//����1024�ֽڶ���
uint8_t *NES_SRAM;  
NES_header *RomHeader; 	//rom�ļ�ͷ
MAPPER *NES_Mapper;		 
MapperCommRes *MAPx;  


uint8_t* spr_ram;			//����RAM,256�ֽ�
ppu_data* ppu;			//ppuָ��
uint8_t* VROM_banks;
uint8_t* VROM_tiles;

apu_t *apu; 			//apuָ��
uint8_t *wave_buffers;


uint8_t *nesapusbuf[NES_APU_BUF_NUM];		//��Ƶ����֡
uint8_t* romfile;							//nes�ļ�ָ��,ָ������nes�ļ�����ʼ��ַ.
//////////////////////////////////////////////////////////////////////////////////////

 
//����ROM
//����ֵ:0,�ɹ�
//    1,�ڴ����
//    3,map����
uint8_t nes_load_rom(void)
{  
    uint8_t* p;  
	uint8_t i;
	uint8_t res=0;
	p=(uint8_t*)romfile;	
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
	uint8_t i;
	myfree(SRAMIN,NES_RAM);		
	myfree(SRAMIN,NES_SRAM);	
	myfree(SRAMIN,RomHeader);	
	myfree(SRAMIN,NES_Mapper);
	myfree(SRAMIN,spr_ram);		
	myfree(SRAMIN,ppu);	
	myfree(SRAMIN,apu);	
	myfree(SRAMIN,wave_buffers);
	for(i=0;i<NES_APU_BUF_NUM;i++)myfree(SRAMEX,nesapusbuf[i]);//�ͷ�APU BUFs 
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
	for(i=0;i<NES_APU_BUF_NUM;i++)nesapusbuf[i]=0; 
	VROM_banks=0;
	VROM_tiles=0; 
	MAP1=0;
	MAPx=0;
} 
//ΪNES���������ڴ�
//romsize:nes�ļ���С
//����ֵ:0,����ɹ�
//       1,����ʧ��
uint8_t nes_sram_malloc(u32 romsize)
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
	wave_buffers=mymalloc(SRAMIN,APU_PCMBUF_SIZE);
	for(i=0;i<NES_APU_BUF_NUM;i++)
	{
		nesapusbuf[i]=mymalloc(SRAMEX,APU_PCMBUF_SIZE+10);//�����ڴ�
	}
 	romfile=mymalloc(SRAMEX,romsize);			//������Ϸrom�ռ�,����nes�ļ���С 
	if(romfile==NULL)//�ڴ治��?�ͷ�������ռ���ڴ�,����������
	{
		spb_delete();//�ͷ�SPBռ�õ��ڴ�
		romfile=mymalloc(SRAMEX,romsize);//��������
	}
	if(i==64||!NES_RAM||!NES_SRAM||!RomHeader||!NES_Mapper||!spr_ram||!ppu||!apu||!wave_buffers||!nesapusbuf[NES_APU_BUF_NUM-1]||!romfile)
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
	memset(wave_buffers,0,APU_PCMBUF_SIZE);	//����
	for(i=0;i<NES_APU_BUF_NUM;i++)memset(nesapusbuf[i],0,APU_PCMBUF_SIZE+10);//���� 
	memset(romfile,0,romsize);				//���� 
	return 0;
} 

void uart_initx(u32 pclk2,u32 bound)
{  	 
	NVIC_InitTypeDef NVIC_InitStructure;
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬���� 
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
#if EN_USART1_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж� 
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
#endif
}

//Ƶ������
//PLL,��Ƶ��
void nes_clock_set(uint8_t PLL)
{
	u16 tPLL=PLL;
	uint8_t temp=0;	 
	RCC->CFGR&=0XFFFFFFFC;	//�޸�ʱ��Ƶ��Ϊ�ڲ�8M	   
	RCC->CR&=~0x01000000;  	//PLLOFF  
 	RCC->CFGR&=~(0XF<<18);	//���ԭ��������
 	PLL-=2;//����2����λ
	RCC->CFGR|=PLL<<18;   	//����PLLֵ 2~16
	RCC->CFGR|=1<<16;	  	//PLLSRC ON 
	FLASH->ACR|=0x12;	  	//FLASH 2����ʱ����
 	RCC->CR|=0x01000000;  	//PLLON
	while(!(RCC->CR>>25));	//�ȴ�PLL����
	RCC->CFGR|=0x02;		//PLL��Ϊϵͳʱ��	 
	while(temp!=0x02)    	//�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	{
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}
 	//˳��������ʱ�ʹ���
	delay_init(tPLL*8);			//��ʱ��ʼ��
	uart_initx(tPLL*8,115200); 	//����1��ʼ��  
	usart3_fast_init(tPLL*4,115200);//����3 APB2ʱ���Ǵ���1��2��
}  
extern vu8 nes_spped_para;		//NES��Ϸ����ʱ,����Դ�ֵ����,Ĭ��Ϊ0.

//��ʼnes��Ϸ
//pname:nes��Ϸ·��
//����ֵ:
//0,�����˳�
//1,�ڴ����
//2,�ļ�����
//3,��֧�ֵ�map
uint8_t nes_load(uint8_t* pname)
{
	FIL *file; 
	UINT br;
	uint8_t res=0;   
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
			nes_clock_set(16);					//128M
			TPAD_Init(16);
			nes_spped_para=1;					//SPI�ٶȼ���
			JOYPAD_Init();
			cpu6502_init();						//��ʼ��6502,����λ	  	 
			Mapper_Init();						//map��ʼ��
			PPU_reset();						//ppu��λ
			apu_init(); 						//apu��ʼ�� 
			nes_sound_open(0,APU_SAMPLE_RATE);	//��ʼ�������豸
			nes_emulate_frame();				//����NESģ������ѭ�� 
			nes_sound_close();					//�ر��������
			nes_clock_set(9);					//72M  
			TPAD_Init(6);
			nes_spped_para=0;					//SPI�ٶȻָ�
		}
	}
	f_close(file);
	myfree(SRAMIN,file);//�ͷ��ڴ�
	nes_sram_free();	//�ͷ��ڴ�
	return res;
} 
uint8_t nes_xoff=0;	//��ʾ��x�᷽���ƫ����(ʵ����ʾ���=256-2*nes_xoff)
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
	yoff=32 + 8;//����߶�(lcddev.height-lcdheight)/2;//��Ļ�߶� 
	LCD_Set_Window(xoff,yoff,lcdwidth,lcdheight);//��NESʼ������Ļ����������ʾ
	LCD_WriteRAM_Prepare();//д��LCD RAM��׼�� 	
}
extern void KEYBRD_FCPAD_Decode(uint8_t *fcbuf,uint8_t mode);
//��ȡ��Ϸ�ֱ�����
void nes_get_gamepadval(void)
{
	if(USART3_RX_STA & 0x08000)
	{
		//printf("usart3 data:%s\r\n",USART3_RX_BUF);
		if(USART3_RX_BUF[0] == 'A')
		{
			PADdata0 |= 0x10;
		}
		else
		{
			PADdata0 &= ~0x10;
		}
		if(USART3_RX_BUF[1] == 'B')
		{
			PADdata0 |= 0x20;
		}
		else
		{
			PADdata0 &= ~0x20;
		}
		if(USART3_RX_BUF[2] == 'C')
		{
			PADdata0 |= 0x40;
		}
		else
		{
			PADdata0 &= ~0x40;
		}
		if(USART3_RX_BUF[3] == 'D')
		{
			PADdata0 |= 0x80;
		}
		else
		{
			PADdata0 &= ~0x80;
		}
		
		if(USART3_RX_BUF[4] == 'E')
		{
			PADdata0 |= 0x01;
		}
		else
		{
			PADdata0 &= ~0x01;
		}
		if(USART3_RX_BUF[5] == 'F')
		{
			PADdata0 |= 0x02;
		}
		else
		{
			PADdata0 &= ~0x02;
		}
		if(USART3_RX_BUF[6] == 'G')
		{
			PADdata0 |= 0x04;
		}
		else
		{
			PADdata0 &= ~0x04;
		}
		if(USART3_RX_BUF[7] == 'H')
		{
			PADdata0 |= 0x08;
		}
		else
		{
			PADdata0 &= ~0x08;
		}
		USART3_RX_STA = 0;
	}
	else
	{
		PADdata0 = get_ctr_res();
	}
	//LCD_ShowNum(2,799-16,PADdata0,3,16);ȡ����ʾ����ֵ
	//PADdata0=JOYPAD_Read();	//��ȡ�ֱ�1��ֵ
	//PADdata1=0;				//û���ֱ�2,�ʲ�����. 
}

_btn_obj * tbtn_game[8];		//�ܹ�8����ť

static uint8_t game_btn_check(_btn_obj * btnx,void * in_key)
{
	_in_obj *key=(_in_obj*)in_key;
	uint8_t btnok=0;
	if((btnx->sta&0X03)==BTN_INACTIVE)return 0;//��Ч״̬�İ���,ֱ�Ӳ����
	switch(key->intype)
	{
		case IN_TYPE_TOUCH:	//������������
			if(btnx->top<key->y&&key->y<(btnx->top+btnx->height)&&btnx->left<key->x&&key->x<(btnx->left+btnx->width))//�ڰ����ڲ�
			{
				btnx->sta&=~(0X03);
				btnx->sta|=BTN_PRESS;//����
				//btn_draw(btnx);//����ť  �����ػ水ť������Ӱ��֡��
				btnok=1;
			}else 
			{
				btnx->sta&=~(0X03);
				btnx->sta|=BTN_RELEASE;	//�ɿ�
				//btn_draw(btnx);			//����ť
			}
			break;
		default:
			break;
	}
	return btnok;
}

void delete_ctr_ui(void)
{
	uint8_t i;
	for(i=0;i<8;i++)
	btn_delete(tbtn_game[i]);//ɾ����ť
}
uint8_t get_ctr_res(void)
{
	uint8_t res = 0,i,val = 0;
	tp_dev.scan(0);    
	in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ
	for(i=0;i<8;i++)
	{
		res=game_btn_check(tbtn_game[i],&in_obj);//ȷ�ϰ�ť���
		if(res)
		{
			if((tbtn_game[i]->sta&0X80)==0)//����Ч����
			{
				switch(i)
				{
					case 0:
						val |= 1 << 2;
						break;
					case 1:
						val |= 1 << 3;
						break;
					case 2:
						val |= 1 << 6;
						break;
					case 3:
						val |= 1 << 7;
						break;
					case 4:
						val |= 1 << 4;
						break;
					case 5:
						val |= 1 << 5;
						break;
					case 6:
						val |= 1 << 0;
						break;
					case 7:
						val |= 1 << 1;
						break;
				}
			}
		}
	}
	return val;
}
void load_ctr_ui(void)
{
	u16 button_w,button_h,W,H;
	
	uint8_t rval=0;
	uint8_t i;
	
	if(lcddev.width == 480)
	{
		button_w = 60;
		button_h = 40;
	}
	else
	{
		button_w = 30;
		button_h = 18;
	}
	
	W = (lcddev.width - button_w * 6) / (6 + 1);//�����϶���
	H = (lcddev.height  - 552 - button_h * 3) / (3 + 1);//�����϶���
	
 	tbtn_game[0]=btn_creat(button_w * 1 + W * 2, 552 + button_h * 0 + H * 1,button_w,button_h,0,0x02);	//������ť
	tbtn_game[1]=btn_creat(button_w * 1 + W * 2, 552 + button_h * 2 + H * 3,button_w,button_h,1,0x02);	//������ť
	tbtn_game[2]=btn_creat(button_w * 0 + W * 1, 552 + button_h * 1 + H * 2,button_w,button_h,2,0x02);	//������ť
	tbtn_game[3]=btn_creat(button_w * 2 + W * 3, 552 + button_h * 1 + H * 2,button_w,button_h,3,0x02);	//������ť
	tbtn_game[4]=btn_creat(button_w * 4 + W * 5, 552 + button_h * 0 + H * 1,button_w,button_h,4,0x02);	//������ť
	tbtn_game[5]=btn_creat(button_w * 4 + W * 5, 552 + button_h * 2 + H * 3,button_w,button_h,5,0x02);	//������ť
	tbtn_game[6]=btn_creat(button_w * 3 + W * 4, 552 + button_h * 1 + H * 2,button_w,button_h,6,0x02);	//������ť
	tbtn_game[7]=btn_creat(button_w * 5 + W * 6, 552 + button_h * 1 + H * 2,button_w,button_h,7,0x02);	//������ť
	for(i=0;i<8;i++)
	{
		if(tbtn_game[i]==NULL)
		{
			rval=1;
			break;
		}
		
		tbtn_game[i]->bcfucolor=BLACK;//�ɿ�ʱΪ��ɫ
		tbtn_game[i]->bcfdcolor=WHITE;//����ʱΪ��ɫ			
		tbtn_game[i]->bkctbl[0]=0X453A;//�߿���ɫ
		tbtn_game[i]->bkctbl[1]=0X5DDC;//��һ�е���ɫ				
		tbtn_game[i]->bkctbl[2]=0X5DDC;//�ϰ벿����ɫ
		tbtn_game[i]->bkctbl[3]=0X453A;//�°벿����ɫ

		if(i==0)tbtn_game[i]->caption="Select";
		if(i==1)tbtn_game[i]->caption="Start";	
		if(i==2)tbtn_game[i]->caption="Left";
		if(i==3)tbtn_game[i]->caption="Right";
		if(i==4)tbtn_game[i]->caption="Up";
		if(i==5)tbtn_game[i]->caption="Down";
		if(i==6)tbtn_game[i]->caption="A";
		if(i==7)tbtn_game[i]->caption="B";
	}
	if(rval==0)//�޴���
	{
		for(i=0;i<8;i++)btn_draw(tbtn_game[i]);	//����ť
 	}
}

//nesģ������ѭ��
void nes_emulate_frame(void)
{
	uint8_t nes_frame;
	TIM3_Int_Init(10000-1,12800-1);//����TIM3 ,1s�ж�һ��
	load_ctr_ui();
	nes_set_window();//���ô���
	system_task_return=0;
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
		//LCD_Set_Window(0,0,lcddev.width,lcddev.height);//�ָ���Ļ�������ڸ�����Ļ����״̬
		nes_get_gamepadval();	//ÿ3֡��ѯһ��USB
		//nes_set_window();//��Ϊ�����Ļ����ʱ������˰�ť״̬������Ҫ�������ô���
		apu_soundoutput();		//�����Ϸ����	 
		frame_cnt++; 	
		nes_frame++;
		if(nes_frame>NES_SKIP_FRAME)
		{
			nes_frame=0;//��֡  
			if(lcddev.id==0X1963)nes_set_window();//���贰��
		}
		if(system_task_return)
		{
			system_task_return=0;
			break;
 		}
	}
	LCD_Set_Window(0,0,lcddev.width,lcddev.height);//�ָ���Ļ����
	delete_ctr_ui();
	TIM3->CR1&=~(1<<0);//�رն�ʱ��3
}
//��6502.s���汻����
void debug_6502(u16 reg0,uint8_t reg1)
{
	printf("6502 error:%x,%d\r\n",reg0,reg1);
}
////////////////////////////////////////////////////////////////////////////////// 	 
//nes,��Ƶ���֧�ֲ���
vu16 nesbufpos=0;
vu8 nesplaybuf=0;		//�������ŵ���Ƶ֡������
vu8 nessavebuf=0;		//��ǰ���浽����Ƶ������ 

//��Ƶ���Żص�����
void nes_vs10xx_feeddata(void)
{  
	uint8_t n;
	uint8_t nbytes;
	uint8_t *p; 
	if(nesplaybuf==nessavebuf)return;//��û���յ��µ���Ƶ����
	if(VS_DQ!=0)//���Է������ݸ�VS10XX
	{		 
		p=nesapusbuf[nesplaybuf]+nesbufpos; 
		nesbufpos+=32; 
		if(nesbufpos>APU_PCMBUF_SIZE)
		{
			nesplaybuf++;
			if(nesplaybuf>(NES_APU_BUF_NUM-1))nesplaybuf=0; 	
			nbytes=APU_PCMBUF_SIZE+32-nesbufpos;
			nesbufpos=0; 
		}else nbytes=32;
		for(n=0;n<nbytes;n++)
		{
			if(p[n]!=0)break;	//�ж��ǲ���ʣ�����е����ݶ�Ϊ0? 
		}
		if(n==nbytes)return;	//����0,��ֱ�Ӳ�д��VS1053��,��������������. 
		VS_XDCS=0;  
		for(n=0;n<nbytes;n++)
		{
			SPI1_ReadWriteByte(p[n]);	 			
		}
		VS_XDCS=1;     				   
	} 
}
//NESģ����������VS1053���,ģ��WAV�����wavͷ����.
const uint8_t nes_wav_head[]=
{
0X52,0X49,0X46,0X46,0XFF,0XFF,0XFF,0XFF,0X57,0X41,0X56,0X45,0X66,0X6D,0X74,0X20,
0X10,0X00,0X00,0X00,0X01,0X00,0X01,0X00,0X11,0X2B,0X00,0X00,0X11,0X2B,0X00,0X00,
0X01,0X00,0X08,0X00,0X64,0X61,0X74,0X61,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};
//NES����Ƶ���
int nes_sound_open(int samples_per_sync,int sample_rate) 
{
	uint8_t *p;
	uint8_t i; 
	p=mymalloc(SRAMIN,100);	//����100�ֽ��ڴ�
	if(p==NULL)return 1;	//�ڴ�����ʧ��,ֱ���˳�
	printf("sound open:%d\r\n",sample_rate);
	for(i=0;i<sizeof(nes_wav_head);i++)//����nes_wav_head����
	{
		p[i]=nes_wav_head[i];
	}
	if(lcddev.width==480)	//��480*480��Ļ
	{
		sample_rate=8000;	//����8Khz,Լԭ���ٶȵ�0.75��
	}
	p[24]=sample_rate&0XFF;			//���ò�����
	p[25]=(sample_rate>>8)&0XFF;
	p[28]=sample_rate&0XFF;			//�����ֽ�����(8λģʽ,���ڲ�����)
	p[29]=(sample_rate>>8)&0XFF; 
	nesplaybuf=0;
	nessavebuf=0;	
	VS_HD_Reset();		   			//Ӳ��λ
	VS_Soft_Reset();  				//��λ 
	VS_Set_All();					//���������Ȳ��� 			 
	VS_Reset_DecodeTime();			//��λ����ʱ�� 	  	 
	while(VS_Send_MusicData(p));	//����wav head
	while(VS_Send_MusicData(p+32));	//����wav head
	TIM6_Int_Init(100-1,1280-1);	//1ms�ж�һ��
	myfree(SRAMIN,p);				//�ͷ��ڴ�
	return 1;
}
//NES�ر���Ƶ���
void nes_sound_close(void) 
{ 
	TIM6->CR1&=~(1<<0);				//�رն�ʱ��6
	VS_SPK_Set(0);					//�ر�������� 
	VS_Set_Vol(0);					//��������Ϊ0 	
} 
//NES��Ƶ�����VS1053����
void nes_apu_fill_buffer(int samples,uint8_t* wavebuf)
{	 
 	u16	i;	
	uint8_t tbuf;
	for(i=0;i<APU_PCMBUF_SIZE;i++)
	{
		nesapusbuf[nessavebuf][i]=wavebuf[i]; 
	}
	tbuf=nessavebuf;
	tbuf++;
	if(tbuf>(NES_APU_BUF_NUM-1))tbuf=0;
	while(tbuf==nesplaybuf)//������ݸ�����Ƶ���ŵ�λ����,�ȴ�.
	{ 
		delay_ms(5);
	}
	nessavebuf=tbuf; 
}	



















