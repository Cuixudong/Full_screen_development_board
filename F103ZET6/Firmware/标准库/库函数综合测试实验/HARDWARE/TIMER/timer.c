#include "timer.h"
#include "led.h"
#include "usart.h"
#include "ucos_ii.h"	//ucos ʹ��	 
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//��ʱ�� ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/10
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.1 20150110
//1,����TIM3_PWM_Init������
//2,����LED0_PWM_VAL�궨�壬����TIM3_CH2����
//V1.2 20150110
//1,����TIM5_Cap_Init����
//2,����TIM5_IRQHandler�жϷ�����
//V1.3 20150115
//1,����TIM1_PWM_Init����
//V1.4 20150118
//1,����TIM6_Int_Init������
//2,����TIM6_IRQHandler����
//V1.5 20150314
//1,����TIM7_Int_Init������
//2,����TIM7_IRQHandler����
//////////////////////////////////////////////////////////////////////////////////

vu8 frame_cnt;
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)
{
    OSIntEnter();
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)//����ж�
    {
        if(frame_cnt)printf("frame:%d\r\n",frame_cnt);//��ӡ֡��
        frame_cnt=0;
    }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
    OSIntExit();
}
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

    //��ʱ��TIM3��ʼ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx

}
//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5

    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO

    //��ʼ��TIM3
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM3 Channel2 PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}
//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM5_Cap_Init(u16 arr,u16 psc)
{
    TIM_ICInitTypeDef  TIM5_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����

    //��ʼ����ʱ��5 TIM5
    TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM5���벶�����
    TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM5, &TIM5_ICInitStructure);

    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�

    TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
//[5:0]:����ߵ�ƽ������Ĵ���
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
//��ʱ��5�жϷ������
void TIM5_IRQHandler(void)
{

    if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
    {
        if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//���
        {
            if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
            {
                if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
                {
                    TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
                    TIM5CH1_CAPTURE_VAL=0XFFFF;
                } else TIM5CH1_CAPTURE_STA++;
            }
        }
        if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
        {
            if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½���
            {
                TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
                TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
            } else  								//��δ��ʼ,��һ�β���������
            {
                TIM5CH1_CAPTURE_STA=0;			//���
                TIM5CH1_CAPTURE_VAL=0;
                TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
                TIM_SetCounter(TIM5,0);
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
            }
        }
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}
//TIM1 CH1 PWM�������
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʹ��TIMx����
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOA����ʱ��ʹ��


    //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO

    TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ������ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //CH1 PWM2ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //OC1 �͵�ƽ��Ч
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIMx

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1 Ԥװ��ʹ��

    TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��,�߼���ʱ�����뿪�����

    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx
}

extern void nes_vs10xx_feeddata(void);
//��ʱ��6�жϷ������
void TIM6_IRQHandler(void)
{
    OSIntEnter();
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
    {
        nes_vs10xx_feeddata();//�������
    }
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
    OSIntExit();
}
//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM6_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig( TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//ʹ�ܶ�ʱ��6���´����ж�

    TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx����

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}
//LCD ����PWM�����ʼ��
//��ʼ���������Ϊ:PWM����Ƶ��Ϊ80Khz
//ͨ��LCD_BLPWM_VAL����LCD��������.
//0,�;250,�.
void LCD_PWM_Init(void)
{
    //�˲������ֶ��޸�IO������
    RCC->APB2ENR|=1<<13; 	//TIM8ʱ��ʹ��
    RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��

    GPIOB->CRL&=0XFFFFFFF0;	//PB0���
    GPIOB->CRL|=0X0000000B;	//���ù������
    GPIOB->ODR|=1<<0;		//PB0����

    TIM8->ARR=100;			//�趨�������Զ���װֵΪ100.Ƶ��Ϊ100Hz
    TIM8->PSC=7200-1;		//Ԥ��Ƶ��7200

    TIM8->CCMR1|=7<<12; 	//CH2 PWM2ģʽ
    TIM8->CCMR1|=1<<11; 	//CH2Ԥװ��ʹ��

    TIM8->CCER|=1<<6;   	//OC2�������ʹ��
    TIM8->CCER|=1<<7;   	//OC2N�͵�ƽ��Ч
    TIM8->BDTR|=1<<15;   	//MOE�����ʹ��

    TIM8->CR1=0x0080;   	//ARPEʹ��
    TIM8->CR1|=0x01;    	//ʹ�ܶ�ʱ��8
}
extern vu16 USART3_RX_STA;
//��ʱ��7�жϷ������
void TIM7_IRQHandler(void)
{
    OSIntEnter();
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
    {
        USART3_RX_STA|=1<<15;	//��ǽ������
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
        TIM_Cmd(TIM7, DISABLE);  		//�رն�ʱ��7
    }
    OSIntExit();
}
//������ʱ��7�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM7_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��
    //��ʱ��TIM7��ʼ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM7�ж�,��������ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�1��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_Cmd(TIM7, ENABLE);  //ʹ��TIMx
}
