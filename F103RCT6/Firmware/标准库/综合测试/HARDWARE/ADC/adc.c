 #include "adc.h"
 #include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 2;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

	ADC_TempSensorVrefintCmd(ENABLE); //�����ڲ��¶ȴ�����

	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
uint16_t Get_Adc(uint8_t ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
}

int Get_Temp(void)
{				 
	uint16_t temp_val=0;
	uint8_t t;
	float temperate;   
	for(t=0;t<20;t++)//��20��,ȡƽ��ֵ
	{
		temp_val+=Get_Adc(ADC_CH_TEMP);
		delay_ms(1);
	}
	temp_val/=20;
	temperate=(float)temp_val*(3.3/4096);//�õ��¶ȴ������ĵ�ѹֵ
	temperate=(1.43-temperate)/0.0043+25;//�������ǰ�¶�ֵ	 
	temperate*=10;//����ʮ��,ʹ��С�����һλ
	return (int)temperate;	 
}

void Get_Battery_Message(float * vol,uint8_t * percent)
{
	uint32_t ADCConvertedValue;
	uint16_t temp_val[2];
	float battery=0;
	{
		ADCConvertedValue = Get_Adc_Average(ADC_CH1,10);
		temp_val[0] = (uint16_t)(ADCConvertedValue*6.63/4.096)/1000;//�����ѹ������ֵ��������Ӧ����3.3���ѹ6.6��ʵ��7.897�ȽϽӽ���ʵ��ѹ
		temp_val[1] = (uint16_t)(ADCConvertedValue*6.63/4.096)%1000;

		battery = ((temp_val[0] + temp_val[1] * 0.001 - 3.25) * 100 / (4.15 - 3.25));
		if(battery >= 100)
		{
			battery = 100;
		}
		else if(battery <= 0)
		{
			battery = 0;
		}
		* vol = temp_val[0] * 1 + temp_val[1] * 0.001;
		* percent = (uint8_t)battery;
	}
}
