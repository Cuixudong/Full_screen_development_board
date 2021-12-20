#ifndef __DIGITAL_LED_H
#define __DIGITAL_LED_H

typedef struct
{
    unsigned char (*IF_DrawLine)(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye);		//IO初始化函数
    void (*Digital_Draw_Line)(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color);
} _Draw_Str;

extern  unsigned short DIGITAL_COLOR_FRONT;
extern  unsigned short DIGITAL_COLOR_FRONT_EMP;
extern unsigned short DIGITAL_COLOR_BACK;
extern _Draw_Str draw_str;
extern unsigned short DIGITAL_POINT_COLOR;

void Draw_Digital_num(unsigned short x,unsigned short y,unsigned char lw,unsigned short w,unsigned short h,unsigned char num,unsigned char fill);
/**

                   起始坐标
                   (x,y)___________________________________________
                       /                     A                     \      <-------------横线的宽度lw 值越小数码管越细长    ^
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
                      / \____________________G____________________/ \                                                  数码管高度h
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

                     <---------------数码管宽度w--------------------->

  例如显示数字1，则B，C段为显示的有效段，其余为无效段，mode参数的位5为1时则无效段是显示的不然就是显示成背景色和不显示一样，
  如果另其显示的同时位6也为1，那么显示的无效段就是填充成实心的，不然就是空心的只有边框
  主显示段也就是有效段是一直显示的，可以通过位7设置有效的这段是空心还是实心，为1是实心，否则空心

 *起始坐标XY，数码管段线宽，显示大小宽高，显示的数字
 *mode ：bit7 是否填充主显示段，bit6 是否填充副显示段，bit5 是否显示副显示段
 */
void Digital_Draw_num(unsigned short x,unsigned short y,unsigned char lw,unsigned short w,unsigned short h,unsigned char num,unsigned char mode);

#endif
