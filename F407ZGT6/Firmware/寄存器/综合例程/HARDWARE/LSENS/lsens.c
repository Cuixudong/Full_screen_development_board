#include "lsens.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LSENS(����������)��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//��ʼ������������
void Lsens_Init(void)
{
    RCC->AHB1ENR|=1<<5;    	//ʹ��PORTFʱ��
    GPIO_Set(GPIOF,PIN7,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PF7,ģ������,����
    Adc3_Init();
}
//��ȡLight Sens��ֵ
//0~100:0,�;100,����
u8 Lsens_Get_Val(void)
{
    u32 temp_val=0;
    u8 t;
    for(t=0; t<LSENS_READ_TIMES; t++)
    {
        temp_val+=Get_Adc3(LSENS_ADC_CHX);	//��ȡADCֵ
        delay_ms(5);
    }
    temp_val/=LSENS_READ_TIMES;//�õ�ƽ��ֵ
    if(temp_val>4000)temp_val=4000;
    return 100-(temp_val/40);
}













