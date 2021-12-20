#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32开发板
//STM32 FLASH 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/12
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////	
//********************************************************************************
//V1.1修改说明
//修正了STMFLASH_Write函数地址偏移的一个bug.
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
//用户根据自己的需要设置
#define STM32_FLASH_SIZE 	256 	 			//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 	1              		//使能FLASH写入(0，不是能;1，使能)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 			//STM32 FLASH的起始地址
//FLASH解锁键值
#define FLASH_KEY1               0X45670123
#define FLASH_KEY2               0XCDEF89AB
void STMFLASH_Unlock(void);					  	//FLASH解锁
void STMFLASH_Lock(void);					  	//FLASH上锁
uint8_t STMFLASH_GetStatus(void);				  	//获得状态
uint8_t STMFLASH_WaitDone(uint16_t time);				  	//等待操作结束
uint8_t STMFLASH_ErasePage(uint32_t paddr);			  	//擦除页
uint8_t STMFLASH_WriteHalfWord(uint32_t faddr, uint16_t dat);	//写入半字
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  	//读出半字  
void STMFLASH_WriteLenByte(uint32_t WriteAddr,uint32_t DataToWrite,uint16_t Len);	//指定地址开始写入指定长度的数据
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr,uint16_t Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead);   		//从指定地址开始读出指定长度的数据

//测试写入
void Test_Write(uint32_t WriteAddr,uint16_t WriteData);								   
#endif

















