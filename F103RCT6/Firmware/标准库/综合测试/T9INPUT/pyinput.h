#ifndef __PYINPUT_H
#define __PYINPUT_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ο������粢�����޸�
//ALIENTEK STM32������
//ƴ�����뷨 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/22
//�汾��V1.0			    
//������������ӿƼ����޹�˾  	 												    								  
//////////////////////////////////////////////////////////////////////////////////


//ƴ�������ƴ���Ķ�Ӧ��
typedef struct
{
  uint8_t *py_input;//������ַ���
  uint8_t *py;	   //��Ӧ��ƴ��
  uint8_t *pymb;	   //���
}py_index;

#define MAX_MATCH_PYMB 	10	//���ƥ����

//ƴ�����뷨
typedef struct
{
  uint8_t(*getpymb)(uint8_t *instr);			//�ַ���������ȡ����
  py_index *pymb[MAX_MATCH_PYMB];	//�����λ��
}pyinput;

extern pyinput t9;
uint8_t str_match(uint8_t*str1,uint8_t*str2);
uint8_t get_matched_pymb(uint8_t *strin,py_index **matchlist);
uint8_t get_pymb(uint8_t* str);
void test_py(uint8_t *inputstr);
#endif








