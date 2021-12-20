#include "timer.h"
#include "led.h"
#include "usart.h"
#include "includes.h"	 	//ucos ʹ��	  
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.6
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//V1.1 20140504
//����TIM14_PWM_Init����,����PWM���
//V1.2 20140504
//����TIM5_CH1_Cap_Init����,�������벶��
//V1.3 20140506
//����TIM9_CH2_PWM_Init����,����PWM DACʵ��
//V1.4 20140723
//����TIM6_Int_Init����
//V1.5 20140726
//����TIM12_CH2_PWM_Init����
//V1.6 20140807
//����TIM7_Int_Init����
//////////////////////////////////////////////////////////////////////////////////

extern u8 ov_frame;
extern volatile u16 jpeg_data_len;
extern void usbapp_pulling(void);

vu8 framecnt;		//ͳһ��֡������
vu8 framecntout;	//ͳһ��֡�������������
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)
{
    OSIntEnter();
    if(TIM3->SR&0X0001)//����ж�
    {
        if(OSRunning!=TRUE)//OS��û����,��TIM3���ж�,10msһ��,��ɨ��USB
        {
            usbapp_pulling();
        }
        framecntout=framecnt;
        //printf("frame:%d\r\n",framecntout);//��ӡ֡��
        framecnt=0;
    }
    TIM3->SR&=~(1<<0);//����жϱ�־λ
    OSIntExit();
}
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ42M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��
    TIM3->ARR=arr;  	//�趨�������Զ���װֵ
    TIM3->PSC=psc;  	//Ԥ��Ƶ��
    TIM3->DIER|=1<<0;   //��������ж�
    TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
    MY_NVIC_Init(2,0,TIM3_IRQn,2);	//��ռ2�������ȼ�0����2
}

//TIM14 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM14_PWM_Init(u32 arr,u32 psc)
{
    //�˲������ֶ��޸�IO������
    RCC->APB1ENR|=1<<8; 	//TIM14ʱ��ʹ��
    RCC->AHB1ENR|=1<<5;   	//ʹ��PORTFʱ��
    GPIO_Set(GPIOF,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
    GPIO_AF_Set(GPIOF,9,9);	//PF9,AF9

    TIM14->ARR=arr;			//�趨�������Զ���װֵ
    TIM14->PSC=psc;			//Ԥ��Ƶ������Ƶ
    TIM14->CCMR1|=6<<4;  	//CH1 PWM1ģʽ
    TIM14->CCMR2|=1<<3; 	//CH1 Ԥװ��ʹ��
    TIM14->CCER|=1<<0;   	//OC1 ���ʹ��
    TIM14->CCER|=1<<1;   	//OC1 �͵�ƽ��Ч
    TIM14->CR1|=1<<7;   	//ARPEʹ��
    TIM14->CR1|=1<<0;    	//ʹ�ܶ�ʱ��14
}

//��ʱ��2ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
    RCC->APB1ENR|=1<<3;   	//TIM5 ʱ��ʹ��
    RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��
    GPIO_Set(GPIOA,PIN0,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,����
    GPIO_AF_Set(GPIOA,0,2);	//PA0,AF2

    TIM5->ARR=arr;  		//�趨�������Զ���װֵ
    TIM5->PSC=psc;  		//Ԥ��Ƶ��

    TIM5->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
    TIM5->CCMR1|=0<<4; 		//IC1F=0000 ���������˲��� ���˲�
    TIM5->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ

    TIM5->CCER|=0<<1; 		//CC1P=0	�����ز���
    TIM5->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����

    TIM5->EGR=1<<0;			//������Ʋ��������¼�,ʹд��PSC��ֵ������Ч,���򽫻�Ҫ�ȵ���ʱ������Ż���Ч!
    TIM5->DIER|=1<<1;   	//������1�ж�
    TIM5->DIER|=1<<0;   	//��������ж�
    TIM5->CR1|=0x01;    	//ʹ�ܶ�ʱ��2
    MY_NVIC_Init(2,0,TIM5_IRQn,2);//��ռ2�������ȼ�0����2
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������
void TIM5_IRQHandler(void)
{
    u16 tsr;
    tsr=TIM5->SR;
    if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
    {
        if(tsr&0X01)//���
        {
            if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
            {
                if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
                {
                    TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
                    TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
                } else TIM5CH1_CAPTURE_STA++;
            }
        }
        if(tsr&0x02)//����1���������¼�
        {
            if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½���
            {
                TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
                TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
                TIM5->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
            } else  								//��δ��ʼ,��һ�β���������
            {
                TIM5CH1_CAPTURE_STA=0;			//���
                TIM5CH1_CAPTURE_VAL=0;
                TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
                TIM5->CR1&=~(1<<0)		;    	//ʹ�ܶ�ʱ��2
                TIM5->CNT=0;					//���������
                TIM5->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز���
                TIM5->CR1|=0x01;    			//ʹ�ܶ�ʱ��2
            }
        }
    }
    TIM5->SR=0;//����жϱ�־λ
}
//TIM9 CH2 PWM�������
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM9_CH2_PWM_Init(u16 arr,u16 psc)
{
    RCC->APB2ENR|=1<<16;   	//TIM9 ʱ��ʹ��
    RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��
    GPIO_Set(GPIOA,PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//PA3,���ù���,����
    GPIO_AF_Set(GPIOA,3,3);	//PA3,AF3
    TIM9->ARR=arr;  		//�趨�������Զ���װֵ
    TIM9->PSC=psc;  		//Ԥ��Ƶ��
    TIM9->CCMR1|=6<<12;  	//CH2 PWM1ģʽ
    TIM9->CCMR1|=1<<11; 	//CH2 Ԥװ��ʹ��
    TIM9->CCER|=1<<4;   	//OC2 ���ʹ��
    TIM9->CR1|=1<<7;   		//ARPEʹ��
    TIM9->CR1|=1<<0;    	//ʹ�ܶ�ʱ��9
}
extern vu8 aviframeup;
//��ʱ��6�жϷ������
void TIM6_DAC_IRQHandler(void)
{
    OSIntEnter();
    if(TIM6->SR&0X0001)//����ж�
    {
        aviframeup=1;
    }
    TIM6->SR&=~(1<<0);//����жϱ�־λ
    OSIntExit();
}
//ͨ�ö�ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ42M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
void TIM6_Int_Init(u16 arr,u16 psc)
{
    RCC->APB1ENR|=1<<4;	//TIM6ʱ��ʹ��
    TIM6->ARR=arr;  	//�趨�������Զ���װֵ
    TIM6->PSC=psc;  	//Ԥ��Ƶ��
    TIM6->CNT=0;  		//����������
    TIM6->DIER|=1<<0;   //��������ж�
    TIM6->CR1|=0x01;    //ʹ�ܶ�ʱ��6
    MY_NVIC_Init(1,3,TIM6_DAC_IRQn,2);	//��ռ1�������ȼ�3����2
}
extern vu16 USART3_RX_STA;
//��ʱ��7�жϷ������
void TIM7_IRQHandler(void)
{
    OSIntEnter();
    if(TIM7->SR&0X01)//�Ǹ����ж�
    {
        USART3_RX_STA|=1<<15;	//��ǽ������
        TIM7->SR&=~(1<<0);		//����жϱ�־λ
        TIM7->CR1&=~(1<<0);		//�رն�ʱ��7
    }
    OSIntExit();
}
//ͨ�ö�ʱ��7�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ42M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
void TIM7_Int_Init(u16 arr,u16 psc)
{
    RCC->APB1ENR|=1<<5;	//TIM7ʱ��ʹ��
    TIM7->ARR=arr;  	//�趨�������Զ���װֵ
    TIM7->PSC=psc;  	//Ԥ��Ƶ��
    TIM7->CNT=0;  		//����������
    TIM7->DIER|=1<<0;   //��������ж�
    TIM7->CR1|=0x01;    //ʹ�ܶ�ʱ��7
    MY_NVIC_Init(0,1,TIM7_IRQn,2);	//��ռ0�������ȼ�1����2
}
//TIM12 CH2 PWM�������
//PWM�����ʼ��,����LCD �������
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM12_CH2_PWM_Init(u16 arr,u16 psc)
{
    RCC->APB1ENR|=1<<6;   	//TIM12 ʱ��ʹ��
    RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��
    GPIO_Set(GPIOB,PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//PB15,���ù���,����
    GPIO_AF_Set(GPIOB,15,9);//PB15,AF9
    TIM12->ARR=arr;  		//�趨�������Զ���װֵ
    TIM12->PSC=psc;  		//Ԥ��Ƶ��
    TIM12->CCMR1|=6<<12;  	//CH2 PWM1ģʽ
    TIM12->CCMR1|=1<<11; 	//CH2 Ԥװ��ʹ��
    TIM12->CCER|=1<<4;   	//OC2 ���ʹ��
    TIM12->CR1|=1<<7;   	//ARPEʹ��
    TIM12->CR1|=1<<0;    	//ʹ�ܶ�ʱ��12
}










