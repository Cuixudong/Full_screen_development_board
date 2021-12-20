#include "tpad.h"
#include "delay.h"		    
#include "usart.h"

#define TPAD_ARR_MAX_VAL 	0XFFFF	//����ARRֵ
volatile uint16_t tpad_default_val=0;//���ص�ʱ��(û���ְ���),��������Ҫ��ʱ��

//��ʼ����������
//��ÿ��ص�ʱ����������ȡֵ.
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ��
uint8_t TPAD_Init(uint8_t psc)
{
	uint16_t buf[10];
	uint16_t temp;
	uint8_t j,i;
	TIM2_CH1_Cap_Init(TPAD_ARR_MAX_VAL,psc-1);//��1Mhz��Ƶ�ʼ��� 
	for(i=0;i<10;i++)//������ȡ10��
	{
		buf[i]=TPAD_Get_Val();
		delay_ms(10);	    
	}
	for(i=0;i<9;i++)//����
	{
		for(j=i+1;j<10;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	temp=0;
	for(i=2;i<8;i++)temp+=buf[i];//ȡ�м��6�����ݽ���ƽ��
	tpad_default_val=temp/6;
	printf("tpad_default_val:%d\r\n",tpad_default_val);	
	if(tpad_default_val>TPAD_ARR_MAX_VAL/2)return 1;//��ʼ����������TPAD_ARR_MAX_VAL/2����ֵ,������!
	return 0;		     	    					   
}
//��λһ��
void TPAD_Reset(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
	//����GPIOA.0Ϊ����ʹ��
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PA0 �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA.0���0,�ŵ�

	delay_ms(5);

	TIM_SetCounter(TIM2,0);		//��0
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־
	//����GPIOA.0Ϊ��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	 //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//�õ���ʱ������ֵ
//�����ʱ,��ֱ�ӷ��ض�ʱ���ļ���ֵ.
uint16_t TPAD_Get_Val(void)
{				   
	TPAD_Reset();
	while(TIM_GetFlagStatus(TIM2, TIM_IT_CC1) == RESET)//�ȴ�����������
	{
		if(TIM_GetCounter(TIM2)>TPAD_ARR_MAX_VAL-500)
			return TIM_GetCounter(TIM2);//��ʱ��,ֱ�ӷ���CNT��ֵ
	};	
	return TIM_GetCapture1(TIM2);	  
} 	 
//��ȡn��,ȡ���ֵ
//n��������ȡ�Ĵ���
//����ֵ��n�ζ������������������ֵ
uint16_t TPAD_Get_MaxVal(uint8_t n)
{
	uint16_t temp=0;
	uint16_t res=0;
	while(n--)
	{
		temp=TPAD_Get_Val();//�õ�һ��ֵ
		if(temp>res)res=temp;
	};
	return res;
}  
//ɨ�败������
//mode:0,��֧����������(����һ�α����ɿ����ܰ���һ��);1,֧����������(����һֱ����)
//����ֵ:0,û�а���;1,�а���;										  
#define TPAD_GATE_VAL 	100	//����������ֵ,Ҳ���Ǳ������tpad_default_val+TPAD_GATE_VAL,����Ϊ����Ч����.
uint8_t TPAD_Scan(uint8_t mode)
{
	static uint8_t keyen=0;	//0,���Կ�ʼ���;>0,�����ܿ�ʼ���	 
	uint8_t res=0;
	uint8_t sample=3;		//Ĭ�ϲ�������Ϊ3��	 
	uint16_t rval;
	if(mode)
	{
		sample=6;		//֧��������ʱ�����ò�������Ϊ6��
		keyen=0;		//֧������	  
	}
	rval=TPAD_Get_MaxVal(sample); 
	if(rval>(tpad_default_val+TPAD_GATE_VAL))//����tpad_default_val+TPAD_GATE_VAL,��Ч
	{							 
		if(keyen==0)res=1;		//keyen==0,��Ч 
		//printf("r:%d\r\n",rval);
		keyen=3;				//����Ҫ�ٹ�3��֮����ܰ�����Ч   
	} 
	if(keyen)keyen--;		   							   		     	    					   
	return res;
}	
//��ʱ��2ͨ��2���벶������
void TIM2_CH1_Cap_Init(uint16_t arr,uint16_t psc)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
   	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM2_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 //ʹ��TIM2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	//����GPIOA.0Ϊ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PA0�˿�����
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
   	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	 //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	 //����Ϊ��������
	
	//��ʼ����ʱ��2 TIM2
    TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM2���벶�����
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ
    TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);

    TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��
}
