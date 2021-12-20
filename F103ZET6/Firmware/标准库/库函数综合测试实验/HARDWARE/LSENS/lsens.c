#include "lsens.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//LSENS(����������)��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
//��ʼ��ADC3
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��6
void  Adc3_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3	, ENABLE );	  //ʹ��ADC3ͨ��ʱ��
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);//ADC��λ
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);//��λ����
    ADC_DeInit(ADC3);  //��λADC3,������ ADC3��ȫ���Ĵ�������Ϊȱʡֵ
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ: ����ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC3, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
    ADC_Cmd(ADC3, ENABLE);	//ʹ��ָ����ADC3
    ADC_ResetCalibration(ADC3);	//ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC3));	//�ȴ���λУ׼����
    ADC_StartCalibration(ADC3);	 //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC3));	 //�ȴ�У׼����
}
//���ADC3ĳ��ͨ����ֵ
//ch:ͨ��ֵ 0~16
//����ֵ:ת�����
u16 Get_Adc3(u8 ch)
{
    //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
    ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC3,ADCͨ��,����ʱ��Ϊ239.5����
    ADC_SoftwareStartConvCmd(ADC3, ENABLE);		//ʹ��ָ����ADC3�����ת����������
    while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������
    return ADC_GetConversionValue(ADC3);	//�������һ��ADC3�������ת�����
}

//��ʼ������������
void Lsens_Init(void)
{
//  GPIO_InitTypeDef GPIO_InitStructure;
//
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//ʹ��PORTFʱ��
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PF8 anolog����
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
//  GPIO_Init(GPIOF, &GPIO_InitStructure);
//  Adc3_Init();
}
//��ȡLight Sens��ֵ
//0~100:0,�;100,����
u8 Lsens_Get_Val(void)
{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<LSENS_READ_TIMES;t++)
//	{
//		temp_val+=Get_Adc3(LSENS_ADC_CHX);	//��ȡADCֵ
//		delay_ms(5);
//	}
//	temp_val/=LSENS_READ_TIMES;//�õ�ƽ��ֵ
//	if(temp_val>4000)temp_val=4000;
//	return (u8)(100-(temp_val/40));
    return 70;
}
