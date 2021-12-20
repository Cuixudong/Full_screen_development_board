#ifndef __DIGITAL_LED_H
#define __DIGITAL_LED_H

typedef struct
{
    unsigned char (*IF_DrawLine)(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye);		//IO��ʼ������
    void (*Digital_Draw_Line)(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color);
} _Draw_Str;

extern  unsigned short DIGITAL_COLOR_FRONT;
extern  unsigned short DIGITAL_COLOR_FRONT_EMP;
extern unsigned short DIGITAL_COLOR_BACK;
extern _Draw_Str draw_str;
extern unsigned short DIGITAL_POINT_COLOR;

void Draw_Digital_num(unsigned short x,unsigned short y,unsigned char lw,unsigned short w,unsigned short h,unsigned char num,unsigned char fill);
/**

                   ��ʼ����
                   (x,y)___________________________________________
                       /                     A                     \      <-------------���ߵĿ��lw ֵԽС�����Խϸ��    ^
                      /\___________________________________________/\                                                      |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     | F|                                         |  |                                                     |
                     |  |                                         | B|                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |_________________________________________|  |                                                     |
                      \ /                                         \ /                                                      |
                      / \____________________G____________________/ \                                                  ����ܸ߶�h
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     | E|                                         | C|                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |_________________________________________|  |                                                     |
                      \/                                           \/                                                      |
                       \_____________________D_____________________/                                                       |

                     <---------------����ܿ��w--------------------->

  ������ʾ����1����B��C��Ϊ��ʾ����Ч�Σ�����Ϊ��Ч�Σ�mode������λ5Ϊ1ʱ����Ч������ʾ�Ĳ�Ȼ������ʾ�ɱ���ɫ�Ͳ���ʾһ����
  ���������ʾ��ͬʱλ6ҲΪ1����ô��ʾ����Ч�ξ�������ʵ�ĵģ���Ȼ���ǿ��ĵ�ֻ�б߿�
  ����ʾ��Ҳ������Ч����һֱ��ʾ�ģ�����ͨ��λ7������Ч������ǿ��Ļ���ʵ�ģ�Ϊ1��ʵ�ģ��������

 *��ʼ����XY������ܶ��߿���ʾ��С��ߣ���ʾ������
 *mode ��bit7 �Ƿ��������ʾ�Σ�bit6 �Ƿ���丱��ʾ�Σ�bit5 �Ƿ���ʾ����ʾ��
 */
void Digital_Draw_num(unsigned short x,unsigned short y,unsigned char lw,unsigned short w,unsigned short h,unsigned char num,unsigned char mode);

#endif
