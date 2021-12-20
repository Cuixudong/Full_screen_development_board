#ifndef __NES_MAIN_H
#define __NES_MAIN_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序移植自网友ye781205的NES模拟器工程
//ALIENTEK STM32开发板
//NES主函数 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/7/1
//版本：V1.0  			  
////////////////////////////////////////////////////////////////////////////////// 	 
 
#define NES_SKIP_FRAME 	2		//定义模拟器跳帧数,默认跳2帧
 
 
#define INLINE 	static inline
#define int8 	char
#define int16 	short
#define int32 	int
#define uint8 	unsigned char
#define uint16 	unsigned short
#define uint32 	unsigned int
#define boolean uint8 



//nes信息头结构体
typedef struct
{
	unsigned char id[3]; // 'NES'
	unsigned char ctrl_z; // control-z
	unsigned char num_16k_rom_banks;
	unsigned char num_8k_vrom_banks;
	unsigned char flags_1;
	unsigned char flags_2;
	unsigned char reserved[8];
}NES_header;   
 
extern int MapperNo;			//map编号
extern int NES_scanline;		//扫描线
extern NES_header *RomHeader;	//rom文件头 
extern int VROM_1K_SIZE;
extern int VROM_8K_SIZE; 
extern uint8_t cpunmi;  				//cpu中断标志  在 6502.s里面
extern uint8_t cpuirq;			
extern uint8_t PADdata;   			//手柄1键值 
extern uint8_t PADdata1;   			//手柄1键值 
extern uint8_t lianan_biao;			//连按标志 
#define  CPU_NMI  cpunmi=1;
#define  CPU_IRQ  cpuirq=1;
#define  NES_RAM_SPEED	0 	 	//1:内存占用小  0:速度快


void cpu6502_init(void);		//在 cart.s
void run6502(u32); 		   		//在 6502.s 
uint8_t nes_load_rom(void);
void nes_sram_free(void);
uint8_t nes_sram_malloc(u32 romsize);
uint8_t nes_load(uint8_t* pname);
void nes_set_window(void);
void nes_get_gamepadval(void);
void nes_emulate_frame(void);
void debug_6502(u16 reg0,uint8_t reg1);

void nes_i2s_dma_tx_callback(void);
int nes_sound_open(int samples_per_sync,int sample_rate);
void nes_sound_close(void);
void nes_apu_fill_buffer(int samples,uint8_t* wavebuf); 

extern u32 get_crc32(uint8_t* buf, u32 len);

void delete_ctr_ui(void);
uint8_t get_ctr_res(void);
void load_ctr_ui(void);
	
#endif
