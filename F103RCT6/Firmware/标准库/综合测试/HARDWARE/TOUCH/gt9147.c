#include "gt9147.h"
#include "touch.h"
#include "ctiic.h"
#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "string.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//4.3����ݴ�����-GT9147 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/10/28
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//GT9147���ò�����
//��һ���ֽ�Ϊ�汾��(0X60),���뱣֤�µİ汾�Ŵ��ڵ���GT9147�ڲ�
//flashԭ�а汾��,�Ż��������.
const uint8_t GT9147_CFG_TBL[]=
{ 
	0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
	0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
	0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
	0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
	0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
	0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
	0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
	0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
	0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
	0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
	0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,
};  
//����GT9147���ò���
//mode:0,���������浽flash
//     1,�������浽flash
uint8_t GT9147_Send_Cfg(uint8_t mode)
{
	uint8_t buf[2];
	uint8_t i=0;
	buf[0]=0;
	buf[1]=mode;	//�Ƿ�д�뵽GT9147 FLASH?  ���Ƿ���籣��
	for(i=0;i<sizeof(GT9147_CFG_TBL);i++)buf[0]+=GT9147_CFG_TBL[i];//����У���
    buf[0]=(~buf[0])+1;
	GT9147_WR_Reg(GT_CFGS_REG,(uint8_t*)GT9147_CFG_TBL,sizeof(GT9147_CFG_TBL));//���ͼĴ�������
	GT9147_WR_Reg(GT_CHECK_REG,buf,2);//д��У���,�����ø��±��
	return 0;
}  
//��GT9147д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t GT9147_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i;
	uint8_t ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//������
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}
//��GT9147����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void GT9147_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   //����д���� 	 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT_CMD_RD);   //���Ͷ�����		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
    CT_IIC_Stop();//����һ��ֹͣ����    
} 
//��ʼ��GT9147������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
uint8_t GT9147_Init(void)
{
	uint8_t temp[5]; 
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_2);						//���1
	GPIO_SetBits(GPIOC,GPIO_Pin_3);					//���1

 	CT_IIC_Init();      	//��ʼ����������I2C����  
	GT_RST=0;				//��λ
	delay_ms(10);
 	GT_RST=1;				//�ͷŸ�λ 
 	delay_ms(10);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;			//PC1�˿�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;		//��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);			//PC1��������
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);				//����	

 	delay_ms(100);
	GT9147_RD_Reg(GT_PID_REG,temp,4);//��ȡ��ƷID
	temp[4]=0;
	printf("CTP ID:%s\r\n",temp);	//��ӡID
	if(strcmp((char*)temp,"9147")==0)//ID==9147
	{
		temp[0]=0X02;			
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//��λGT9147
		GT9147_RD_Reg(GT_CFGS_REG,temp,1);//��ȡGT_CFGS_REG�Ĵ���
		if(temp[0]<0X60)//Ĭ�ϰ汾�Ƚϵ�,��Ҫ����flash����
		{
			printf("Default Ver:%d\r\n",temp[0]);
			GT9147_Send_Cfg(1);//���²���������
		}
		delay_ms(10);
		temp[0]=0X00;	 
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//������λ   
		return 0;
	} 
	return 1;
}
const uint16_t GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};
//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
uint8_t GT9147_Scan(uint8_t mode)
{
	uint8_t buf[4];
	uint8_t i=0;
	uint8_t res=0;
	uint8_t temp;
	static uint8_t t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
	t++;
	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
	{
		GT9147_RD_Reg(GT_GSTID_REG,&mode,1);//��ȡ�������״̬ 
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//������Ч?
				{
					GT9147_RD_Reg(GT9147_TPX_TBL[i],buf,4);	//��ȡXY����ֵ
					
					switch(tp_dev.touchtype & 0x07)
					{
						case L2R_U2D:
							tp_dev.x[i]=((uint16_t)(buf[1]&0X0F)<<8)+buf[0];
							tp_dev.y[i]=((uint16_t)(buf[3]&0X0F)<<8)+buf[2];
							break;
						case L2R_D2U:
							tp_dev.y[i]=lcddev.height-(((uint16_t)(buf[1]&0X0F)<<8)+buf[0]);
							tp_dev.x[i]=lcddev.width-(((uint16_t)(buf[3]&0X0F)<<8)+buf[2]);
							break;
						case R2L_U2D:
							tp_dev.x[i]=lcddev.width-(((uint16_t)(buf[1]&0X0F)<<8)+buf[0]);
							tp_dev.y[i]=((uint16_t)(buf[3]&0X0F)<<8)+buf[2];
							break;
						case D2U_R2L:
							tp_dev.x[i]=lcddev.width-(((uint16_t)(buf[3]&0X0F)<<8)+buf[2]);
							tp_dev.y[i]=lcddev.height-(((uint16_t)(buf[1]&0X0F)<<8)+buf[0]);
							break;
						case U2D_L2R:
							tp_dev.y[i]=((uint16_t)(buf[1]&0X0F)<<8)+buf[0];
							tp_dev.x[i]=((uint16_t)(buf[3]&0X0F)<<8)+buf[2];
							break;
						case U2D_R2L:
							tp_dev.y[i]=lcddev.height-(((uint16_t)(buf[1]&0X0F)<<8)+buf[0]);
							tp_dev.x[i]=((uint16_t)(buf[3]&0X0F)<<8)+buf[2];
							break;
						case D2U_L2R:
							tp_dev.y[i]=((uint16_t)(buf[1]&0X0F)<<8)+buf[0];
							tp_dev.x[i]=lcddev.width-(((uint16_t)(buf[3]&0X0F)<<8)+buf[2]);
							break;
						case R2L_D2U:
							tp_dev.x[i]=lcddev.width-(((uint16_t)(buf[1]&0X0F)<<8)+buf[0]);
							tp_dev.y[i]=lcddev.height-(((uint16_t)(buf[3]&0X0F)<<8)+buf[2]);
							break;
						default:
							break;
					}
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			}
			res=1;
			if(tp_dev.x[0]==0 && tp_dev.y[0]==0)mode=0;	//���������ݶ���0,����Դ˴�����
			t=0;		//����һ��,��������������10��,�Ӷ����������
		}
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT9147_WR_Reg(GT_GSTID_REG,&temp,1);//���־ 		
		}
	}
	if((mode&0X8F)==0X80)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);	//��ǰ����ɿ�
		}else						//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//�������Ч���	
		}	 
	} 	
	if(t>240)t=10;//���´�10��ʼ����
	return res;
}
