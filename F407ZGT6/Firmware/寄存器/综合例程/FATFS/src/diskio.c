/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "sdio_sdcard.h"
#include "w25qxx.h"
#include "malloc.h"		 
#include "guix.h"
#include "ucos_ii.h"
#include "usbh_usr.h"
#include "calendar.h" 	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//FATFS�ײ�(diskio) ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


#define SD_CARD	 0  		//SD��,���Ϊ0
#define EX_FLASH 1			//�ⲿflash,���Ϊ1
#define USB_DISK 2			//U��,���Ϊ2

#define FLASH_SECTOR_SIZE 	512		//W25Q128������СΪ512�ֽ�
#define FLASH_SECTOR_NUM    2048*12	//W25Q128����FATFS�������������,ǰ12M�ֽڸ�FATFSռ��
//����W25Q128
//ǰ12M�ֽڸ�fatfs��,12M�ֽں�,���ڴ���ֿ�,�ֿ�ռ��3.09M.	15.10M�ֽ��Ժ�,���ͻ��Լ���	 			    
u16 FLASH_SECTOR_COUNT;				//W25Q128��������
#define FLASH_BLOCK_SIZE   	8  		//ÿ��BLOCK��8������


//��ʼ������
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	u8 res=0;	 
 	switch(pdrv)
	{
		case SD_CARD:		//SD��
			res=SD_Init();	//SD_Init()  
  			break;
		case EX_FLASH:		//�ⲿflash
			W25QXX_Init();
			FLASH_SECTOR_COUNT=FLASH_SECTOR_NUM;//W25Q1218,ǰ12M�ֽڸ�FATFSռ�� 
 			break;
		case USB_DISK:		//U��  
	  		res=!USBH_UDISK_Status();//U�����ӳɹ�,�򷵻�1.���򷵻�0	
			break;
		default:
			res=1; 
	}		 
	if(res)return  STA_NOINIT;
	else return 0; //��ʼ���ɹ�
}  

//��ô���״̬
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{ 
	return 0;
} 

//������
//drv:���̱��0~9
//*buff:���ݽ��ջ����׵�ַ
//sector:������ַ
//count:��Ҫ��ȡ��������
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	u8 res=0;  
	u8 tcnt=0;
    if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������	 
	switch(pdrv)
	{
		case SD_CARD://SD�� 
			res=SD_ReadDisk(buff,sector,count);	 
			while(res&&tcnt<10)//������
			{
				tcnt++; 
				res=SD_Init();	//���³�ʼ��SD��
				res=SD_ReadDisk(buff,sector,count); 
				//printf("sd rd error:%d\r\n",res);
			}
			break;
		case EX_FLASH://�ⲿflash
			for(;count>0;count--)
			{
				W25QXX_Read(buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
				sector++;
				buff+=FLASH_SECTOR_SIZE;
			}
			res=0;
			break;
		case USB_DISK://U��    
			res=USBH_UDISK_Read(buff,sector,count);  								    
			break;
		default:
			res=1; 
	} 
   //������ֵ,������ֵת��ff.c�ķ���ֵ
    if(res==0x00)return RES_OK;	 
    else return RES_ERROR;	   
}

//д����
//drv:���̱��0~9
//*buff:���������׵�ַ
//sector:������ַ
//count:��Ҫд���������
#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	u8 res=0;   
 	u8 tcnt=0;
   if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������	 
 	switch(pdrv)
	{
		case SD_CARD://SD��
			res=SD_WriteDisk((u8*)buff,sector,count);
			while(res&&tcnt<10)//������
			{
				tcnt++;
				res=SD_Init();	//���³�ʼ��SD��
				res=SD_WriteDisk((u8*)buff,sector,count);	 
				//printf("sd wr error:%d\r\n",res);
			}
			break;
		case EX_FLASH://�ⲿflash
			for(;count>0;count--)
			{		 
				W25QXX_Write((u8*)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
				sector++;
				buff+=FLASH_SECTOR_SIZE;
			}
			res=0;
			break;
		case USB_DISK://U�� 
			res=USBH_UDISK_Write((u8*)buff,sector,count); 
			break;
		default:
			res=1; 
	}  
   //������ֵ,������ֵת��ff.c�ķ���ֵ
    if(res==0x00)return RES_OK;	 
    else return RES_ERROR;	
}
#endif


//����������Ļ��
 //drv:���̱��0~9
 //ctrl:���ƴ���
 //*buff:����/���ջ�����ָ��
#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;						  			     
	if(pdrv==SD_CARD)//SD��
	{
	    switch(cmd)
	    {
		    case CTRL_SYNC:
				res = RES_OK; 
		        break;	 
		    case GET_SECTOR_SIZE:
				*(DWORD*)buff = 512; 
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
				*(WORD*)buff = SDCardInfo.CardBlockSize;
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff = SDCardInfo.CardCapacity/512;
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }
	}else if(pdrv==EX_FLASH)	//�ⲿFLASH  
	{
	    switch(cmd)
	    {
		    case CTRL_SYNC:
				res = RES_OK; 
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff = FLASH_SECTOR_SIZE;
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff = FLASH_BLOCK_SIZE;
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff = FLASH_SECTOR_COUNT;
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }
	}else if(pdrv==USB_DISK)	//U��
	{
	    switch(cmd)
	    {
		    case CTRL_SYNC:
				res = RES_OK; 
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff=512;
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff=512;
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff=USBH_MSC_Param.MSCapacity;
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }		
	}else res=RES_ERROR;//�����Ĳ�֧��
    return res;
}
#endif 
vu8 cnt0=0;
vu8 cnt1=0;
OS_CPU_SR cpu_sr=0; 
//�����ٽ���
void ff_enter(FATFS *fs)
{   
	if(fs->drv!=2)
	{
		OS_ENTER_CRITICAL();	//�����ٽ���(�޷����жϴ��)     
		cnt0++;
	}else
	{  
		OSSchedLock();			//��ֹucos����
		cnt1++;
	}
}
//�˳��ٽ���
void ff_leave(FATFS* fs)
{ 
	if(cnt0)
	{
		cnt0--; 
		OS_EXIT_CRITICAL();	//�˳��ٽ���(���Ա��жϴ��) 
	}
	if(cnt1)
	{ 
		cnt1--;
		OSSchedUnlock();	//����ucos���� 	
	}
}  
//���ʱ��
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{	
	u32 time=0;
	calendar_get_date(&calendar);
	calendar_get_time(&calendar);
	if(calendar.w_year<1980)calendar.w_year=1980;
	time=(calendar.w_year-1980)<<25;//���
	time|=(calendar.w_month)<<21;	//�·�
	time|=(calendar.w_date)<<16;	//����
	time|=(calendar.hour)<<11;		//ʱ
	time|=(calendar.min)<<5;		//��
	time|=(calendar.sec/2);			//��	
	return time;
}			 
//��̬�����ڴ�
void *ff_memalloc (UINT size)			
{
	return (void*)mymalloc(SRAMIN,size);
}
//�ͷ��ڴ�
void ff_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}




















