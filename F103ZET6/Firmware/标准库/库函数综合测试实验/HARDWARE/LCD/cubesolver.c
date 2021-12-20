#include "sys.h"
#include "delay.h"
#include "lcd.h"

struct rotate//各侧边的关联 即当前面的个侧边面块
{
    u8 *Up[3];
    u8 *Down[3];
    u8 *Left[3];
    u8 *Right[3];

};
u8 Red,Gre,Blu;
u8 Cube[6][9];//magic cube color
typedef struct//各侧边的关联 即当前面的个侧边面块
{
    u8 *Up[3];
    u8 *Down[3];
    u8 *Left[3];
    u8 *Right[3];
} rotate;
struct rotate Cube1[6];

u8 pause=0,flag=0;

/********************以上为TFT显示驱动 下面为还原算法**********************/
//15*15   左到右 上到下Cube[0-5][0-8]  bit2-0:color  bit3:change
void LCD_Cube_Paint(void)
{
    u8 horizontal,t1,t2;
    u16 vertical;
    u8 i,j;
    for(i=0; i<6; i++)
    {
        if(i==0)
        {
            horizontal=206;
            vertical=136;
        }
        else if(i<5)
        {
            horizontal=143;  // 1号 4号有错位 图形显示上
            vertical=(i-1)*63+10;
        }
        else
        {
            horizontal=80;
            vertical=136;
        }
        for(j=0; j<9; j++)
        {
            if(Cube[i][j]&0x08) //有改变才去重画
            {
                //颜色赋值
                switch(Cube[i][j]&0x07)
                {
                case 0:
                    Red=0xFF;
                    Gre=0xFF;
                    Blu=0xFF;
                    break; //White
                case 1:
                    Red=0;
                    Gre=0;
                    Blu=0xFF;
                    break;//Blue
                case 2:
                    Red=0xFF;
                    Gre=0x60;
                    Blu=0;
                    break;//Orange
                case 3:
                    Red=0;
                    Blu=0;
                    Gre=0xFF;
                    break;//Green
                case 4:
                    Red=0xFF;
                    Gre=0;
                    Blu=0;
                    break;//Red
                case 5:
                    Red=0xFF;
                    Gre=0xFF;
                    Blu=0;
                    break;//yellow
                default:
                    Red=0;
                    Gre=0;
                    Blu=0;
                }
                t2=vertical+j%3*21;
                t1=horizontal-j/3*21;
                LCD_Fill(t1-20,t2,t1-1,t2+20-1,(((Red>>3)<<11)|((Gre>>2)<<5)|Blu>>3));//各块分别填充的颜色
                Cube[i][j]&=0xF7; //clear flag
            }
        }
    }
    //LCD_Write_Data_End();
}

void init_Cube(void)
{
    u8 i,j;///////////// 初始显示
    for(i=0; i<6; i++) ///
        for(j=0; j<9; j++) ////
            Cube[i][j]=i+0x08;///各面填充颜色

    //6个面关联 struct rotate建立初期模型
    //white 0
    Cube1[0].Up[0]=Cube[1]+2;
    Cube1[0].Up[1]=Cube[1]+1;
    Cube1[0].Up[2]=Cube[1];
    Cube1[0].Down[0]=Cube[3];
    Cube1[0].Down[1]=Cube[3]+1;
    Cube1[0].Down[2]=Cube[3]+2;
    Cube1[0].Left[0]=Cube[2];
    Cube1[0].Left[1]=Cube[2]+1;
    Cube1[0].Left[2]=Cube[2]+2;
    Cube1[0].Right[0]=Cube[4]+2;
    Cube1[0].Right[1]=Cube[4]+1;
    Cube1[0].Right[2]=Cube[4];
    //Blue 1
    Cube1[1].Up[0]=Cube[0]+2;
    Cube1[1].Up[1]=Cube[0]+1;
    Cube1[1].Up[2]=Cube[0];
    Cube1[1].Down[0]=Cube[5]+8;
    Cube1[1].Down[1]=Cube[5]+7;
    Cube1[1].Down[2]=Cube[5]+6;
    Cube1[1].Left[0]=Cube[4]+2;
    Cube1[1].Left[1]=Cube[4]+5;
    Cube1[1].Left[2]=Cube[4]+8;
    Cube1[1].Right[0]=Cube[2];
    Cube1[1].Right[1]=Cube[2]+3;
    Cube1[1].Right[2]=Cube[2]+6;
    //Orange
    Cube1[2].Up[0]=Cube[0];
    Cube1[2].Up[1]=Cube[0]+3;
    Cube1[2].Up[2]=Cube[0]+6;
    Cube1[2].Down[0]=Cube[5]+6;
    Cube1[2].Down[1]=Cube[5]+3;
    Cube1[2].Down[2]=Cube[5]+0;
    Cube1[2].Left[0]=Cube[1]+2;
    Cube1[2].Left[1]=Cube[1]+5;
    Cube1[2].Left[2]=Cube[1]+8;
    Cube1[2].Right[0]=Cube[3];
    Cube1[2].Right[1]=Cube[3]+3;
    Cube1[2].Right[2]=Cube[3]+6;
    //Green
    Cube1[3].Up[0]=Cube[0]+6;
    Cube1[3].Up[1]=Cube[0]+7;
    Cube1[3].Up[2]=Cube[0]+8;
    Cube1[3].Down[0]=Cube[5];
    Cube1[3].Down[1]=Cube[5]+1;
    Cube1[3].Down[2]=Cube[5]+2;
    Cube1[3].Left[0]=Cube[2]+2;
    Cube1[3].Left[1]=Cube[2]+5;
    Cube1[3].Left[2]=Cube[2]+8;
    Cube1[3].Right[0]=Cube[4];
    Cube1[3].Right[1]=Cube[4]+3;
    Cube1[3].Right[2]=Cube[4]+6;
    //Red
    Cube1[4].Up[0]=Cube[0]+8;
    Cube1[4].Up[1]=Cube[0]+5;
    Cube1[4].Up[2]=Cube[0]+2;
    Cube1[4].Down[0]=Cube[5]+2;
    Cube1[4].Down[1]=Cube[5]+5;
    Cube1[4].Down[2]=Cube[5]+8;
    Cube1[4].Left[0]=Cube[3]+2;
    Cube1[4].Left[1]=Cube[3]+5;
    Cube1[4].Left[2]=Cube[3]+8;
    Cube1[4].Right[0]=Cube[1];
    Cube1[4].Right[1]=Cube[1]+3;
    Cube1[4].Right[2]=Cube[1]+6;
    //yellow
    Cube1[5].Up[0]=Cube[3]+6;
    Cube1[5].Up[1]=Cube[3]+7;
    Cube1[5].Up[2]=Cube[3]+8;
    Cube1[5].Down[0]=Cube[1]+8;
    Cube1[5].Down[1]=Cube[1]+7;
    Cube1[5].Down[2]=Cube[1]+6;
    Cube1[5].Left[0]=Cube[2]+8;
    Cube1[5].Left[1]=Cube[2]+7;
    Cube1[5].Left[2]=Cube[2]+6;
    Cube1[5].Right[0]=Cube[4]+6;
    Cube1[5].Right[1]=Cube[4]+7;
    Cube1[5].Right[2]=Cube[4]+8;

}

//六个旋转面 bit2-0  3个转向bit5-4 0undo 1 turn left  2 turn right  3turn back
//旋转当前面 会影响到各侧边块即 struct rotate
void Turn_Cube( u8 direction )
{
    u8 center;
    u8 temp,i;
    center=direction&0x07;
    if(center>5) return ;
    switch(direction&0x30)
    {
    case 0x10:
        //修改侧面
        for(i=0; i<3; i++)
        {
            temp= *Cube1[center].Left[i];
            *Cube1[center].Left[i]= *Cube1[center].Up[2-i] |0x08;
            *Cube1[center].Up[2-i]= *Cube1[center].Right[2-i] |0x08;
            *Cube1[center].Right[2-i]= *Cube1[center].Down[i] |0x08;
            *Cube1[center].Down[i]=temp |0x08;
        }
        temp=Cube[center][0];
        Cube[center][0]=Cube[center][2] |0x08;
        Cube[center][2]=Cube[center][8] |0x08;
        Cube[center][8]=Cube[center][6] |0x08;
        Cube[center][6]=temp |0x08;
        temp=Cube[center][1];
        Cube[center][1]=Cube[center][5] |0x08;
        Cube[center][5]=Cube[center][7] |0x08;
        Cube[center][7]=Cube[center][3] |0x08;
        Cube[center][3]=temp |0x08;
        break;
    case 0x20:
        //修改侧面
        for(i=0; i<3; i++)
        {
            temp= *Cube1[center].Left[i];
            *Cube1[center].Left[i]= *Cube1[center].Down[i] |0x08;
            *Cube1[center].Down[i]= *Cube1[center].Right[2-i] |0x08;
            *Cube1[center].Right[2-i]= *Cube1[center].Up[2-i] |0x08;
            *Cube1[center].Up[2-i]=temp |0x08;
        }
        temp=Cube[center][0];
        Cube[center][0]=Cube[center][6] |0x08;
        Cube[center][6]=Cube[center][8] |0x08;
        Cube[center][8]=Cube[center][2] |0x08;
        Cube[center][2]=temp |0x08;
        temp=Cube[center][1];
        Cube[center][1]=Cube[center][3] |0x08;
        Cube[center][3]=Cube[center][7] |0x08;
        Cube[center][7]=Cube[center][5] |0x08;
        Cube[center][5]=temp |0x08;
        break;
    case 0x30:
        //修改侧面
        for(i=0; i<3; i++)
        {
            temp= *Cube1[center].Left[i];
            *Cube1[center].Left[i]= *Cube1[center].Right[2-i] |0x08;
            *Cube1[center].Right[2-i]=temp |0x08;
            temp=*Cube1[center].Up[2-i];
            *Cube1[center].Up[2-i]= *Cube1[center].Down[i] |0x08;
            *Cube1[center].Down[i]=temp |0x08;
        }
        temp=Cube[center][0];
        Cube[center][0]=Cube[center][8] |0x08;
        Cube[center][8]=temp |0x08;
        temp=Cube[center][2];
        Cube[center][2]=Cube[center][6] |0x08;
        Cube[center][6]=temp |0x08;

        temp=Cube[center][1];
        Cube[center][1]=Cube[center][7] |0x08;
        Cube[center][7]=temp |0x08;
        temp=Cube[center][3];
        Cube[center][3]=Cube[center][5] |0x08;
        Cube[center][5]=temp |0x08;
        break;
    }

    LCD_Cube_Paint( );
    pause=1;
    //while(pause && flag)delay_us(100);///////////////暂停
}

u8 Check(u8 i)//判断算法是否出错 只写了前两个阶段
{
    //u8 temp,temp1;
    u8 end=i&0xF0;
    i &=0x0F;
    if(Cube[i][4]!=Cube[i][1] || Cube[i][4]!=Cube[i][3]||Cube[i][4]!=Cube[i][5]||Cube[i][4]!=Cube[i][7])
        return 0x11;//面上不对
    if(Cube[(Cube1[i].Up[1]-Cube[0])/9][4]!=*Cube1[i].Up[1])
        return 0x12;
    if(Cube[(Cube1[i].Down[1]-Cube[0])/9][4]!=*Cube1[i].Down[1])
        return 0x13;
    if(Cube[(Cube1[i].Left[1]-Cube[0])/9][4]!=*Cube1[i].Left[1])
        return 0x14;
    if(Cube[(Cube1[i].Right[1]-Cube[0])/9][4]!=*Cube1[i].Right[1])
        return 0x15;
    if(end==0x10)//第一阶段校验
        return 0;

    if(Cube[i][4]!=Cube[i][0] || Cube[i][4]!=Cube[i][2]||Cube[i][4]!=Cube[i][8]||Cube[i][4]!=Cube[i][6])
        return 0x21;//面上不对
    if(Cube[(Cube1[i].Up[1]-Cube[0])/9][4]!=*Cube1[i].Up[0] || Cube[(Cube1[i].Left[1]-Cube[0])/9][4]!=*Cube1[i].Left[0])//第一个角
        return 0x22;
    if(Cube[(Cube1[i].Up[1]-Cube[0])/9][4]!=*Cube1[i].Up[2] ||Cube[(Cube1[i].Right[1]-Cube[0])/9][4]!=*Cube1[i].Right[0])//第2个角
        return 0x23;
    if(Cube[(Cube1[i].Right[1]-Cube[0])/9][4]!=*Cube1[i].Right[2] ||Cube[(Cube1[i].Down[1]-Cube[0])/9][4]!=*Cube1[i].Down[2])//第3个角
        return 0x24;
    if(Cube[(Cube1[i].Down[1]-Cube[0])/9][4]!=*Cube1[i].Down[0] || Cube[(Cube1[i].Left[1]-Cube[0])/9][4]!=*Cube1[i].Left[2])//第4个角
        return 0x25;
    if(end==0x20)//第二阶段校验
        return 0;
    return 0;
}


//以某一面还原魔方 数字化立体
unsigned char Cube_Restore(u8 face)
{

    u8 Area= face&0x07,order;
    u8 Color_D[6];//self,Up,Right,Down,Left,Opposite;  0-5
    //bit 2~0 color bit 5-3 Area  bit7-6:以顶面为准（Area朝上），各侧面以Cube方式存储时相对正向（从上一行至下依次0-2、3-5、6-8）顺时旋转 90*n
    //对面则是相对Area旋转的角度 90*n
    u8 location;//块具体位置 相对标准位置 bit6-4 面 0-正面（Area 从上往下看） 1上 2右 3下 4左 5-底
    //bit1-0 0-3的标准位置（顺时针数  上 右 下 左）  bit7 0偶（0 2 8 6） 1奇数（1 5 7 3块） 如：0x81-->正面 第5块
    u8 i,j,temp,temp1,m,n;

    u8 target_C1,target_C2;//目标颜色1 2（左边和右边的）
    u8 Area_Operate,Area_Real,Area_Calc;
    u8 compare1[3],compare2[3],index_temp,data_temp;//用于三种颜色对比 从大到小排列

    u8 Area_index[4]= {1,5+0x20,7+0x80,3+0x60}; //顺时针0 2 8 6或 1 5 7 3 高四位记偶数的
    u8 state=0;//步骤3用到的状态标志	 bit0-3 1-4棱是否对好 1对好 0否
    u8 *seamed_edge_p1[4],*seamed_edge_p2[4],seamed_edge_Color[4];//从上往下看 中间层第1个棱边（顺时针数 1-4）左边为seamed_edge_p1[0]，右边为seamed_edge_p2[0]
    //seamed_edge_Color存储此棱边两面的颜色，高四位为左边的颜色，低四位为右边的

    flag=1;

    //分析各面颜色
    Color_D[0]=Cube[Area][4]+(Area<<3);//self
    switch(Area)
    {
    case 0:
        Color_D[1]=Cube[1][4]+0x08;
        Color_D[3]=Cube[3][4]+0x18;
        Color_D[4]=Cube[2][4]+0x10;
        Color_D[2]=Cube[4][4]+0x20;
        Color_D[5]=Cube[5][4]+0xA8;
        break;
    case 1:
        Color_D[1]=Cube[0][4];
        Color_D[3]=Cube[5][4]+0xA8;
        Color_D[4]=Cube[4][4]+0xE0;
        Color_D[2]=Cube[2][4]+0x50;
        Color_D[5]=Cube[3][4]+0x18;
        break;
    case 2:
        Color_D[1]=Cube[0][4]+0x40;
        Color_D[3]=Cube[5][4]+0x68;
        Color_D[4]=Cube[1][4]+0xC8;
        Color_D[2]=Cube[3][4]+0x58;
        Color_D[5]=Cube[4][4]+0x20;
        break;
    case 3:
        Color_D[1]=Cube[0][4]+0x80;
        Color_D[3]=Cube[5][4]+0x28;
        Color_D[4]=Cube[2][4]+0xD0;
        Color_D[2]=Cube[4][4]+0x60;
        Color_D[5]=Cube[1][4]+0x08;
        break;
    case 4:
        Color_D[1]=Cube[0][4]+0xC0;
        Color_D[3]=Cube[5][4]+0xE8;
        Color_D[4]=Cube[3][4]+0xD8;
        Color_D[2]=Cube[1][4]+0x48;
        Color_D[5]=Cube[2][4]+0x10;
        break;
    case 5:
        Color_D[1]=Cube[3][4]+0x98;
        Color_D[3]=Cube[1][4]+0x88;
        Color_D[4]=Cube[2][4]+0x90;
        Color_D[2]=Cube[4][4]+0xA0;
        Color_D[5]=Cube[0][4]+0x80;
        break;
    }


    //先还原某一面的十字  cross 上 右 下 左四棱

    order=1;
    do {
        switch(order)//
        {
        case 1:
            temp=Cube[Area][1];
            temp1=*Cube1[Area].Up[1];
            break;
        case 2:
            temp=Cube[Area][5];
            temp1=*Cube1[Area].Right[1];
            break;
        case 3:
            temp=Cube[Area][7];
            temp1=*Cube1[Area].Down[1];
            break;
        case 4:
            temp=Cube[Area][3];
            temp1=*Cube1[Area].Left[1];
            break;
        }
        if(temp==Cube[Area][4] && temp1 == (Color_D[order]&0x07))//已在正确位置
        {}
        else//先搜索到那块
        {
            for(i=0,location=4; i<6; i++) //Color_Up Cube[Area][4]
            {
                temp=((Color_D[i]&0x38)>>3);//扫描第几面
                if(Cube[temp][1]==(Color_D[order]&0x07) && *Cube1[temp].Up[1]==Cube[Area][4]) {
                    location=0;
                    break;
                }
                if(Cube[temp][3]==(Color_D[order]&0x07) && *Cube1[temp].Left[1]==Cube[Area][4]) {
                    location=3;
                    break;
                }
                if(Cube[temp][5]==(Color_D[order]&0x07) && *Cube1[temp].Right[1]==Cube[Area][4]) {
                    location=1;
                    break;
                }
                if(Cube[temp][7]==(Color_D[order]&0x07) && *Cube1[temp].Down[1]==Cube[Area][4]) {
                    location=2;
                    break;
                }
            }
            if(location!=4)location=(i<<4)+0x80+((location+((Color_D[i]&0xC0)>>6)) & 0xF3);

            //可能在三种情况 目标色块在： 侧面 底面 本面
            if((location&0x70)==0 || (location&0x70)==0x50)//在本面或底面
            {
                //若在本面则化为底面情况
                if((location&0x70)==0)
                {
                    temp=(Color_D[1+(location&0x03)]>>3)&0x07;
                    Turn_Cube(0x30+ temp);//此块属于哪个侧面 就转哪个面
                    //printf ( "Step%d %X\n",order,0x30+ temp);///////////////
                    temp=(location&0x03)+1;
                    if(temp!=1)location =0xD0+5-temp;//注意底面与正上面反的
                    else  location=0xD0;
                }
                //Up那个时：先将此块在底面旋转到相对正面的左侧或右侧
                if((order&0x01)!=(location&0x01))
                {
                    Turn_Cube(0x20+ ((Color_D[5]>>3)&0x07));//底面右转90
                    //printf ( "Step%d %X\n",order,0x20+ ((Color_D[5]>>3)&0x07));///////////////
                    location=((location+1)&0xF3);
                }
                //判断此块属于哪个侧面 1-4  location&0x03：0--1面 3->2面 2->3面 1->4面
                temp1=location&0x03;
                //printf ( " L: %X T1 %X\n",location,temp1);///////////////
                if(temp1==0)
                {
                    temp=1;
                }
                else {
                    temp=5-temp1;
                }
                temp1=(Color_D[temp]>>3)&0x07;//要旋转的侧面
                //如果要转的面在校正目标处右侧则逆时针转90，反之顺时针90

                if(order==1 && temp==4)
                {
                    temp=0x20;
                }
                else if(order==4 && temp==1)
                {
                    temp=0x10;
                }
                else
                {
                    temp=temp>order?0x10:0x20;
                }
                Turn_Cube(temp+temp1);//将目标块转到中间层
                //printf ( "Step%d %X\n",order,temp+temp1);///////////////
                if(temp==0x10)temp=0x20;
                else temp=0x10;
                Turn_Cube( ((Color_D[order]>>3)&0x07) +temp);//将目标快转到位
                //printf ( "Step%d %X\n",order,((Color_D[order]>>3)&0x07) +temp);///////////////
                Turn_Cube(temp+temp1);//将转过的侧面转回去
                //printf ( "Step%d %X\n",order,temp+temp1);///////////////
            }

            else //在侧面
            {
                //先将此处转到底面  0-180  1-90 2-0  3-270
                i=location&0x03;
                temp=0;

                temp1=(location>>4)&0x07;//在第几个面 标准相对的

                if(temp1==order)
                {
                    if(i==2)temp=0x30;
                    else if(i==1)temp=0x10;
                    else if(i==3)temp=0x20;


                    Turn_Cube( ((Color_D[temp1]>>3)&0x07) +temp);
                }
                else
                {
                    if(i==0)temp=0x30;
                    else if(i==1)temp=0x20;
                    else if(i==3)temp=0x10;
                    Turn_Cube( ((Color_D[temp1]>>3)&0x07) +temp);//将目标块转到底
                    i=0;
                    if(temp==0x10)
                    {
                        i=0x20;
                    }
                    if(temp==0x20)
                        i=0x10;
                    temp=0;
                    if(temp1>order)
                    {
                        switch(temp1-order)
                        {
                        case 3:
                            temp=0x10;
                            break;
                        case 2:
                            temp=0x30;
                            break;
                        case 1:
                            temp=0x20;
                            break;
                        }
                    }
                    else
                    {
                        switch(order-temp1)
                        {
                        case 3:
                            temp=0x20;
                            break;
                        case 2:
                            temp=0x30;
                            break;
                        case 1:
                            temp=0x10;
                            break;
                        }
                    }
                    Turn_Cube(((Color_D[5]>>3)&0x07) +temp);//将目标块转到order侧的底
                    if(i)Turn_Cube(((Color_D[temp1]>>3)&0x07) +i);//复原动过的地方
                    Turn_Cube(((Color_D[order]>>3)&0x07) +0x30);//转到目标位置
                }
            }
        }
        order++;
        LCD_Cube_Paint();//显示一次
    } while(order<5);
    //第一阶段完成
    //校验第一阶段
    temp=Check(Area+0x10);
    if(temp)return temp;
    else  printf ( "Mission 1 Finish\n");////////

    //return 0;////////

    //	pause=1;////////////////
    //	while(pause && flag)delay_us(100);///////////////暂停


    //顶面的四角
    //先判断是否位置对  正面的0 2 6 8 四个  location 0x00-0x03

    order=1;//1-4
    //以顶面为主 分别判断四个角
    do {
        switch(order)//分别提取四个角颜色
        {
        case 1:
            temp=*Cube1[Area].Left[0];
            temp1=*Cube1[Area].Up[0];
            target_C1=Color_D[4]&0x07;
            target_C2=Color_D[1]&0x07;
            j=Cube[Area][0];
            break;
        case 2:
            temp=*Cube1[Area].Up[2];
            temp1=*Cube1[Area].Right[0];
            target_C1=Color_D[1]&0x07;
            target_C2=Color_D[2]&0x07;
            j=Cube[Area][2];
            break;
        case 3:
            temp=*Cube1[Area].Right[2];
            temp1=*Cube1[Area].Down[2];
            target_C1=Color_D[2]&0x07;
            target_C2=Color_D[3]&0x07;
            j=Cube[Area][8];
            break;
        case 4:
            temp=*Cube1[Area].Down[0];
            temp1=*Cube1[Area].Left[2];
            target_C1=Color_D[3]&0x07;
            target_C2=Color_D[4]&0x07;
            j=Cube[Area][6];
            break;
        }

        if(temp==target_C1 && temp1==target_C2 && j==Cube[Area][4])
        {


        }
        else //颜色不对则要调整
        {
            //先找到目标块(Color[0]的颜色块所在的位置)
            location=0xFF;
            i=0;//
            //先在底层找  0 2 8 6（底面） 左上  右上  右下  左下
            Area_Real=(Color_D[5]>>3)&0x07;//底面实际的面
Again1:
            while((++i)<5)
            {
                switch(i)//提取角块三色
                {
                case 1:
                    temp=*Cube1[Area_Real].Left[0];
                    temp1=*Cube1[Area_Real].Up[0];
                    j=Cube[Area_Real][0];
                    break;
                case 2:
                    temp=*Cube1[Area_Real].Up[2];
                    temp1=*Cube1[Area_Real].Right[0];
                    j=Cube[Area_Real][2];
                    break;
                case 3:
                    temp=*Cube1[Area_Real].Right[2];
                    temp1=*Cube1[Area_Real].Down[2];
                    j=Cube[Area_Real][8];
                    break;
                case 4:
                    temp=*Cube1[Area_Real].Down[0];
                    temp1=*Cube1[Area_Real].Left[2];
                    j=Cube[Area_Real][6];
                    break;
                }
                //判断temp temp1 j    target_C1 target_C2 Cube[Area][4]
                compare1[0]=temp+0x10;
                compare1[1]=temp1+0x20;
                compare1[2]=j+0x30;
                compare2[0]=target_C1+0x10;
                compare2[1]=target_C2+0x20;
                compare2[2]=Cube[Area][4]+0x30;
                index_temp=2;
                //冒泡排序
                for(m=0; m<2; m++)
                    for(n=m+1; n<3; n++)
                    {
                        if((compare1[m]&0x0F)<(compare1[n]&0x0F)) {
                            data_temp=compare1[m];
                            compare1[m]=compare1[n];
                            compare1[n]=data_temp;
                        }
                        if((compare2[m]&0x0F)<(compare2[n]&0x0F))
                        {   data_temp=compare2[m];
                            compare2[m]=compare2[n];
                            compare2[n]=data_temp;
                            if(m==index_temp)index_temp=n;
                            if(n==index_temp)index_temp=m;//存储下标
                        }
                    }
                if((compare1[0]&0x0F)!=(compare2[0]&0x0F) || (compare1[1]&0x0F)!=(compare2[1]&0x0F) || (compare1[2]&0x0F)!=(compare2[2]&0x0F))
                    continue;
                //分析目标块Cube[Area][4] 在侧面哪或底面哪
                m=(compare1[index_temp]>>4);//
                if(Area_Real==((Color_D[5]>>3)&0x07))//在底面
                {
                    //先把i换成相对标准面的1-4
                    //判断底面旋转了多少度
                    n=(Color_D[5]>>6);
                    if(n!=0)
                    {
                        n=i+n;
                        if(n>4)n&=0x03;
                    }
                    else n=i;
                    if(m==3)location=0x50+n-1;//识别错误 应该是相对标准面的 0-3！！！
                    else
                    {   location=m+1;
                        if(m==1) {
                            switch(n)
                            {
                            case 1:
                                location+=0x20;
                                break;
                            case 2:
                                location+=0x10;
                                break;
                            case 3:
                                location+=0x40;
                                break;
                            case 4:
                                location+=0x30;
                                break;
                            }
                        }
                        else
                        {
                            switch(n)
                            {
                            case 1:
                                location+=0x10;
                                break;
                            case 2:
                                location+=0x40;
                                break;
                            case 3:
                                location+=0x30;
                                break;
                            case 4:
                                location+=0x20;
                                break;
                            }
                        }

                    }
                }
                else//在上层面找
                {
                    if(m==3)location=i-1;
                    else
                    {
                        location=m-1;
                        location+=((i+m-2)<<4);
                        if((location&0xF0)==0)location |=0x40;//第四面特殊

                    }

                }
                //		i++;
            }
            if(location==0xFF && Area_Real==((Color_D[5]>>3)&0x07)) {
                Area_Real=Area;
                i=0;
                goto Again1;
            }

            if(location==0xFF)return 0x21;//第二阶段错误1

            //if(order==4){printf ( "Lo %X",location);return 0;}//////////////////

#ifdef DEBUG2
            printf ( "Pause:order %X Find  Location %X",order,location);///////
            pause=1;
            while(pause && flag)delay_us(100);//////表示暂停  发送’A’字符继续  方便调试(下同)
            printf ( " >\n");
#endif
            //找到所在位置
            //能见目标颜色情况、不能见情况
            //若在顶层换到底边去
            //1.在表面则 侧面L 底面L 侧面R （化为可见状态）
            //2.在侧上层
            if((location&0xF0)==0)
            {
                Area_Operate=(Color_D[(location&0x03)+1]>>3)&0x07;//顺时针旋转此面
                temp=(Color_D[5]>>3)&0x07;//底面实际
                Turn_Cube(Area_Operate+0x20);//将目标块转到的底层

                Turn_Cube(temp+0x20);//底面顺时转90度
                Turn_Cube(Area_Operate+0x10);//将目标块转到的上层
                location=(((location&0x03)+3)<<4) +3;  //在操作面的对面
                if((location&0xF0)>0x40)
                    location &=0x3F;//抹掉最大 使其为1-4面
            }
            else if((location&0xF0)!=0x50 && (location&0x03)<2)//0 1在上层 2 3下层！！！
            {
                temp=(location>>4);
                if(location&0x01)//奇数  操作其减1的面逆时针转 底面再顺时针转90  操作面再顺时转回去  最后在操作面的加1面2（原来的面）
                {
                    if(temp==1)Area_Operate=(Color_D[4]>>3)&0x07;
                    else Area_Operate=(Color_D[temp-1]>>3)&0x07;
                    temp1=0x10;
                    location+=1;
                }
                else  //0 操作其加1的面顺时针转90 底面再逆时针转90  操作面再逆时转回去 最后在操作面的减1面3（原来的面）
                {
                    if(temp==4)Area_Operate=(Color_D[1]>>3)&0x07;
                    else Area_Operate=(Color_D[temp+1]>>3)&0x07;
                    temp1=0x20;
                    location+=3;
                }

                //  printf ( "A_Op1  %X %X\n",Area_Operate+temp1,location);//////////
                //  pause=1;////////////////
                //	while(pause && flag)delay_us(100);///////////////暂停

                Turn_Cube(Area_Operate+temp1);//将目标块转到的下层
                if(temp1==0x10)temp1=0x20;
                else temp1=0x10;
                Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再   转90

                Turn_Cube(Area_Operate+temp1);//操作面再逆时转回去

            }
            else if((location&0xF0)==0x50)//若不可见此目标块  即在底面
            {
                //先将此块转到其目标位正下方！！！
                //	printf ( "Lo undo  %X Pause \n",location);//////////

                //	pause=1;printf ( "   Pause\n");////////////////
                //	while(pause && flag)delay_us(100);///////////////暂停

                //order1-location&0x03(1) 2-0 3-3 4-2
                temp=location&0x03;
                if((temp&0x01)==0)temp+=2;//计算出位置
                //计算底面相对旋转角度90*n
                if(temp!=order)
                {
                    if(((temp^order)&0x01)==0) {
                        temp1=0x30;   //底面要转180度
                    }
                    else
                    {
                        if(temp>order)
                        {
                            if(temp==4&&order==1)temp1=0x10;
                            else temp1=0x20;
                        }
                        else
                        {
                            if(temp==1&&order==4)temp1=0x20;
                            else temp1=0x10;
                        }
                    }

                    Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再  转90
                    //	printf ( "Lo undo  %X order %X temp1%X\n",location,order,temp1);//////////

                    if(temp1==0x10) {
                        if(location&0x03)temp=location-1;    /////////可以不加
                        else temp=location+3;
                    }
                    else if(temp1==0x20) {
                        temp=location+1;
                        temp &=0xF3;
                    }
                    else {
                        temp=location+2;    //////////可以不加
                        temp &=0xF3;
                    }

                    location=0x50+order;
                    if((order&0x01)==0)location-=2;

                    if(temp!=location)return 0x22;///错误2
                }

                //location bit1-0: 0-operate Area1 1-operate Area4 2-operate Area3 3-operate Area2
                //	printf ( "Lo unsee  %X order %X\n",location,order);//////////
                switch(location&0x03)
                {
                case 0:
                    Area_Operate=(Color_D[1]>>3)&0x07;
                    location=0x33;
                    break;
                case 1:
                    Area_Operate=(Color_D[4]>>3)&0x07;
                    location=0x23;
                    break;
                case 2:
                    Area_Operate=(Color_D[3]>>3)&0x07;
                    location=0x13;
                    break;
                case 3:
                    Area_Operate=(Color_D[2]>>3)&0x07;
                    location=0x43;
                    break;
                }
                temp1=0x10;//逆时针转

                //	printf ( "PR Ar   %X\n",Area_Operate+temp1);//////////
                //	pause=1;printf ( "   Pause\n");////////////////
                //	while(pause && flag)delay_us(100);///////////////暂停

                Turn_Cube(Area_Operate+temp1);//将目标块转到后侧

                temp1=temp1^0x30;//5-4位取反
                Turn_Cube(((Color_D[5]>>3)&0x07)+0x20);//底面再顺时针转90

                //	printf ( "Ar   %X\n",Area_Operate+temp1);//////////
                //	pause=1;////////////////
                //	while(pause && flag)delay_us(100);///////////////暂

                Turn_Cube(Area_Operate+temp1);//操作面再逆时转回去
            }
            //底层处理
            //先将此目标块放在正确位置正下方
            //计算此块属于哪个柱子下
            if((location&0x03)==2)temp=(location>>4);
            else {
                temp=(location>>4)+1;
                if(temp==5)temp=1;
            }
            //计算与order相差多少度
            if(temp!=order)
            {
                if(temp<order)
                {
                    switch(order-temp)
                    {
                    case 1:
                        temp1=0x10;
                        break;
                    case 2:
                        temp1=0x30;
                        break;
                    case 3:
                        temp1=0x20;
                        break;
                    }
                }
                else
                {   switch(temp-order)
                    {
                    case 1:
                        temp1=0x20;
                        break;
                    case 2:
                        temp1=0x30;
                        break;
                    case 3:
                        temp1=0x10;
                        break;
                    }
                }
                //printf ( "Area_Op  %X\n",temp1);//////////
                //	if(order==3){printf ( "order %d Lo %X %X",order,location,((Color_D[5]>>3)&0x07)+temp1);}//////////////////
                //	 pause=1;////////////////
                //	while(pause && flag)delay_us(100);///////////////暂停

                Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再 转90*n	！！！

                if(temp1==0x10)//面加1
                {
                    if((location&0xF0)==0x40)location=0x10+(location&0x03);
                    else location+=0x10;
                }
                else if(temp1==0x20)//面减1
                {
                    if((location&0x70)==0x10)location=0x40+(location&0x03);
                    else location-=0x10;
                }
                else //面加2
                {
                    location+=0x20;
                    if((location&0x70)>0x40)location &=0x3F;//抹掉最大 使其为1-4面
                }
            }


            //已在柱子下方了
            if((location&0x03)==2)
            {
                temp1=0x20;
            }
            else
            {
                temp1=0x10;//逆时针转
            }

            Area_Operate=(Color_D[location>>4]>>3)&0x07;
            Turn_Cube(Area_Operate+temp1);//操作面 转

            Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再按temp1转90
            temp1 =temp1^0x30;


            Turn_Cube(Area_Operate+temp1);//操作面再逆时转回去
            //printf ( "Area_Op  %X\n",Area_Operate+temp1);//////////
#ifdef DEBUG2
            pause=1;
            printf ( "  Order %X Pause",order);////////////////
            while(pause && flag)delay_us(100);///////////////暂停
            printf ( " >\n");
#endif
            //return 0;
        }
        order++;
        LCD_Cube_Paint();//显示一次
        //每次校验下

    } while(order<5);

    temp=Check(Area+0x20);
    if(temp)return temp;
    else  printf ( "Mission 2 Finish\n");////////

    //中间层处理 四个
    //order=1;
    //do{
    // 	//若order 为1 则左侧左中颜色为实际块的3-(Color_D[4]>>6)  3为顺时针0-3计数（0-原序号1块 1-5 2-7 3-3）
    //	//(Color_D[4]>>6)= 0-3 即0 90 180 270度  则块分别为3 2 1 0（3的块转多少度后）
    //	//同理 上侧右中 实际块：1-(Color_D[1]>>6)+4 （但有负数 所以+4 最后bit2置0)，0°-1 90°-0 180°-3 270°-2
    //	//分别提取四个棱颜色 从正面往下看顺时针1-4  temp temp1为实际颜色 target_C1 target_C2为目标颜色（左为1 右为2）

    //	m=order-1;if(m==0)m=4;
    //	temp=Cube[(Color_D[m]>>3)&0x07][Area_index[3-(Color_D[m]>>6)]&0x0F];
    //	temp1= Cube[(Color_D[order]>>3)&0x07][Area_index[(5-(Color_D[order]>>6))&0x03]&0x0F];
    //	target_C1=Color_D[m]&0x07;target_C2=Color_D[order]&0x07;
    //
    //	if(temp==target_C1 && temp1==target_C2)//目标颜色对的
    //	{}
    //	else
    //	{
    //	 //不对则要找到那块在哪

    //	}
    // LCD_Cube_Paint();//显示一次
    // //每次校验下
    // m=order-1;if(m==0)m=4;
    //	temp=Cube[(Color_D[m]>>3)&0x07][Area_index[3-(Color_D[m]>>6)]&0x0F];
    //	temp1= Cube[(Color_D[order]>>3)&0x07][Area_index[(5-(Color_D[order]>>6))&0x03]&0x0F];
    // if(temp!=target_C1 || temp1!=target_C2)return 0x33;//错误3
    //
    //  order++;
    //}while(order<5);

    //先在底层找没有底层颜色的棱 再将其放到标准位置，底层找不到说明中间棱的位置或颜色没对好，再将其调换到底层再处理
    //再检查中间层四棱是否都还原，否则继续循环查找

    //u8 *seamed_edge_p1[4],*seamed_edge_p2[4],seamed_edge_Color[4];//从上往下看 中间层第1个棱边（顺时针数 1-4）左边为seamed_edge_p1[0]，右边为seamed_edge_p2[0]
    //seamed_edge_Color存储此棱边两面的目标颜色，高四位为左边的颜色，低四位为右边的
    state=0;////////初始化
    //先将信息准备好
    for(n=1; n<5; n++)
    {
        m=n-1;
        if(m==0)m=4;
        seamed_edge_p1[n-1]=&Cube[(Color_D[m]>>3)&0x07][Area_index[3-(Color_D[m]>>6)]&0x0F];
        seamed_edge_p2[n-1]=&Cube[(Color_D[n]>>3)&0x07][Area_index[(5-(Color_D[n]>>6))&0x03]&0x0F];
        //seamed_edge_Color[n-1]=Color_D[m]&0x07;
        seamed_edge_Color[n-1]=((Color_D[m]&0x07)<<4)+(Color_D[n]&0x07);
    }
    //初次扫描四个中间棱边是否有归位的
    for(i=0; i<4; i++)
    {
        if(*seamed_edge_p1[i]==(seamed_edge_Color[i]>>4) && *seamed_edge_p2[i]==(seamed_edge_Color[i]&0x0F))
            state |=(1<<i);
    }
    while((state&0x0F)!=0x0F)
    {
        temp=Color_D[5]&0x07;//底层面颜色

        for(i=0; i<4; i++) //在底面 0 -3 找符合要求的棱块  0块处对应实际的0（转过n=0度时）  3（90°） 2（180°） 1（270°）  0+4-n
        {
            temp1=Area_index[(i+4-(Color_D[5]>>6))&0x03]&0x0F;
            target_C1=Cube[(Color_D[5]>>3)&0x07][temp1];//表面棱块的颜色

            switch(temp1)//找到侧边色
            {
            case 1:
                target_C2=*Cube1[(Color_D[5]>>3)&0x07].Up[1];
                break;
            case 5:
                target_C2=*Cube1[(Color_D[5]>>3)&0x07].Right[1];
                break;
            case 7:
                target_C2=*Cube1[(Color_D[5]>>3)&0x07].Down[1];
                break;
            case 3:
                target_C2=*Cube1[(Color_D[5]>>3)&0x07].Left[1];
                break;
            }
            if(temp!=target_C1 && temp!=target_C2) {
                break;
            }
        }
        if(i!=4)//找到没有底层颜色的棱
        {
            //先将此块侧边颜色与侧面中心颜色对齐（底面转n*90度）
            n=5-i;//target_C2在底面此块相对标准位置 1-4
            if(n==5)n=1;
            //target_C2颜色应在那个面（相对标准的面）
            for(m=1; m<5; m++)
            {
                if(target_C2==(Color_D[m]&0x07))break;
            }
            if(m==5)return 0x31;//错误1
            //计算底面要旋转n*90
            if(m!=n) {
                i=m>n?(m-n):(n-m+0x10);//m>n 则要底面逆时针转i*90 反之顺时针转
                if((i&0x03)==2)temp1=0x30;
                else
                {
                    temp1=0x10+(i&0x10);
                    if((i&0x03)==3)temp1 ^=0x30;//反向取反
                }

                Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再按temp1转90
            }

            location=0x82+(m<<4);
#ifdef DEBUG3
            pause=1;
            printf ( "under %X",location);
            while(pause && flag)delay_us(100);///////////////暂停
            printf ( " >\n");
#endif

            //已转至标准位置
            //查找target_C1颜色在 location此面的左侧还是右侧：若是左侧则location面逆时针转90 反之则顺时针转90
            //Area_Operate=(Color_D[(location>>4)&0x07]>>3)&0x07;
            Area_Operate=(Color_D[m]>>3)&0x07;
            temp=m-1;//左边的
            //temp1=m+1;//右边的
            if(temp==0)temp=4;
            //if(temp1==5)temp1=1;

            if((Color_D[temp]&0x07)==target_C1)//左边的与其颜色一样  location面逆时针转90
            {
                temp1=0x10;
                temp=m-1;
            }
            else
            {
                temp1=0x20;
                temp=m&0x03;
            }
            for(i=0; i<5; i++)
            {
                if(i&0x01) Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再按temp1转90
                else Turn_Cube(Area_Operate+temp1);//操作Area_Operate 再按temp1转90
            }
            temp1 ^=0x30;
            for(i=0; i<4; i++)
            {
                if(i&0x01)Turn_Cube(Area_Operate+temp1);//操作Area_Operate 再按temp1转90
                else Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再按temp1转90
            }
            state|=(1<<temp);
        }
        else
        {
            //找不到则是还有不对位置的或不对色的棱块在中间层，将其移动到底层去（与底层任意一个交换位置）
#ifdef DEBUG3
            printf ( "No find Area5!\n");
#endif

            for(i=0; i<4; i++)
            {
                if(state&(1<<i))continue;//此棱已正确
                if(*seamed_edge_p1[i]==(seamed_edge_Color[i]>>4) && *seamed_edge_p2[i]==(seamed_edge_Color[i]&0x0F))
                    state |=(1<<i);
                else//遇到棱不对的
                {
                    break;//将其转到底层  即与一块底层的交换
                }
            }
            //统一将 i+1面的底棱与其交换  i+1面逆时针转
            Area_Operate=(Color_D[i+1]>>3)&0x07;
            temp1=0x10;
            for(i=0; i<5; i++)
            {
                if(i&0x01) Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再按temp1转90
                else Turn_Cube(Area_Operate+temp1);//操作Area_Operate 再按temp1转90
            }
            temp1 ^=0x30;
            for(i=0; i<4; i++)
            {
                if(i&0x01)Turn_Cube(Area_Operate+temp1);//操作Area_Operate 再按temp1转90
                else Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//底面再按temp1转90
            }

        }

#ifdef DEBUG3
        pause=1;
        printf ( "|| State  %X Pause",state);////////////////
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif

        LCD_Cube_Paint();////显示一次 清除标志位
    }

    //进行一次校准
    temp=Check(Area+0x20);
    if(temp)return temp;
    for(i=0; i<4; i++)
    {
        if(*seamed_edge_p1[i]==(seamed_edge_Color[i]>>4) && *seamed_edge_p2[i]==(seamed_edge_Color[i]&0x0F))
            state |=(1<<i);
    }
    if(state!=0x0F) return 0x31;
    printf ( "Mission 3 Finish\n");////////

    //进行第四阶段
    //底层十字架 只看底面的颜色
    //有三种情况：1 四棱都不在底面 2有两个不在（相对的2个） 3相邻的两个   4：有无单独一个不在底面的？
    Area_Real=(Color_D[5]>>3)&0x07;//底面实际面
    do {
        for(i=0,n=0,state=0; i<4; i++)
        {
            //(i+4-(Color_D[5]>>6))&0x03  ---->相对面的（0-3）转为实际底面的（0-3）
            if(Cube[Area_Real][Area_index[(i+4-(Color_D[5]>>6))&0x03]&0x0F]==Cube[Area_Real][4])
                n++;//有几个在底面
            else state|=(1<<i);
        }
        if(state!=0)//有不在底面的
        {

            if(n==0)//四个都不在  可先将其转化为两个相邻不在的
            {
                //转第1面  第二面及底面
                temp1=0x20;
                i=(Color_D[1]>>3)&0x07;
                j=(Color_D[2]>>3)&0x07;
                Turn_Cube(i+temp1);//第一面
                Turn_Cube(j+temp1);//2面
                Turn_Cube(Area_Real+temp1);//底面
                temp1 ^=0x30;
                Turn_Cube(j+temp1);//2面
                Turn_Cube(Area_Real+temp1);//底面
                Turn_Cube(i+temp1);//第一面
            }
            else if(n==2)
            {

                if(state==0x05 || state==0x0A)//对棱不同色
                {
                    if(state==0x05)temp=1;
                    else temp=2;//开始旋转的面
                    temp1=0x20;

                    i=(Color_D[temp]>>3)&0x07;
                    j=(Color_D[temp+1]>>3)&0x07;
#ifdef DEBUG4
                    printf ( " 2 Areas not DUI State %X i:%X j:%X ",state,i,j);
                    pause=1;
                    while(pause && flag)delay_us(100);///////////////暂停
                    printf ( " >\n");
#endif
                    Turn_Cube(i+temp1);//第一面
                    Turn_Cube(j+temp1);//2面
                    Turn_Cube(Area_Real+temp1);//底面
                    temp1 ^=0x30;
                    Turn_Cube(j+temp1);//2面
                    Turn_Cube(Area_Real+temp1);//底面
                    Turn_Cube(i+temp1);//第一面
                }
                else//相邻两个颜色不对的
                {
                    //state bit0-3: bit0/3 为1时 应转2所在的面（底面0-3四个棱边）
                    //bit0/1=1:turn Area3  bit1/2 为1时 应转0所在的面 bit2/3 =1 turn Area1
                    temp=state+(state<<4);
                    //寻找temp里的110二进制位所在位置
                    for(i=0; i<4; i++)
                    {
                        if((temp&(0x07<<i))==(0x06<<i))
                            break;
                    }
                    if(i==4)return 0x41;//错误1

#ifdef DEBUG4
                    printf ( "i= %X \n",i);
#endif

                    //0-Area1 1-Area4 2-Area3 3-Area2
                    temp=5-i;
                    if(temp==5)temp=1;//转化为从上往下看的侧面
                    //将底面“看到”的面转为顶层的相对标准面  因为初始位置它可能相对标准面旋转过的（由cube二维数组决定）
                    temp=((temp+1)&0x03)+1;//  DOC文档图形显示错误 操作面选择旋转180
                    i=(Color_D[temp]>>3)&0x07;//第一个面
                    j=temp+1;
                    if(j==5)j=1;//只有1-4的侧面
                    j=(Color_D[j]>>3)&0x07;//第一个面+1面
                    temp1=0x20;//顺时针转

#ifdef DEBUG4
                    printf ( " 2 Areas not LIN State %X i:%X j:%X ",state,i,j);
                    pause=1;
                    while(pause && flag)delay_us(100);///////////////暂停
                    printf ( " >\n");
#endif

                    //第一个面顺时针 底顺 第一个面+1面顺时针  底逆时针  第一个面+1面逆时针 第一个面逆时针
                    Turn_Cube(i+temp1);
                    Turn_Cube(Area_Real+temp1);
                    Turn_Cube(j+temp1);

                    temp1 ^=0x30;
                    Turn_Cube(Area_Real+temp1);
                    Turn_Cube(j+temp1);
                    Turn_Cube(i+temp1);
                    //上面的处理方法一样也可以，下面的也行，不过下面的要多个步骤
                    /*Turn_Cube(i+temp1);//第一面
                    Turn_Cube(j+temp1);//2面
                    Turn_Cube(Area_Real+temp1);//底面
                    temp1 ^=0x30;
                    Turn_Cube(j+temp1);//2面
                    Turn_Cube(Area_Real+temp1);//底面
                    Turn_Cube(i+temp1);//第一面*/
                }
            }

            LCD_Cube_Paint();////显示一次 清除标志位
        }
#ifdef DEBUG4
        pause=1;
        printf ( "|| State  %X n=%XPause",state,n);////////////////
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif

    } while(state!=0);

    //if(state!=0x0F) return 0x31;//暂时不校验
    printf ( "Mission 4 Finish\n");////////

    //底层颜色处理
    //处理底层四角的7种情况

    //Area_Real依旧是底层的面 不要改变它

    //先将四角 左右两块的具体位置存入到数组
    //*seamed_edge_p1[4],*seamed_edge_p2[4],前者为左侧，后者为右侧  以标准相对位置的0-3
    //读取底层四角块侧面颜色 i=1 2面2(L) 1面3(R) i=2 Area1_2(L) Area4_3(R) i=3 Area4_2(L) Area3_3(R) i=4 Area3_2(L) Area2_3(R)
    for(i=1; i<5; i++)
    {
        m=i<3?3-i:7-i;
        n=(i&0x01)?i:6-i;
        seamed_edge_p1[i-1]=&Cube[(Color_D[m]>>3)&0x07][Area_index[(6-(Color_D[m]>>6))&0x03]>>4];// 顺时针2
        seamed_edge_p2[i-1]=&Cube[(Color_D[n]>>3)&0x07][Area_index[3-(Color_D[n]>>6)]>>4]; //顺时针3
    }


    do {
        //扫描底面四角颜色 从0 - 2 - 8 - 6（0-3相对标准位置）
        for(i=0,n=0,state=0; i<4; i++)
        {
            temp=Area_index[(i+4-(Color_D[5]>>6))&0x03]>>4;
            if(Cube[Area_Real][temp]==Cube[Area_Real][4])
                n++;//有几个在底面
            else
            {
                state|=(0x10<<i);
                //并找出底色块在此角左侧还是右侧（左侧为0 右侧为1 分别置数到bit 0-3位）
                if(*seamed_edge_p2[i]==Cube[Area_Real][4]) state|=(0x01<<i);
                else if(*seamed_edge_p1[i]!=Cube[Area_Real][4])//不在右侧块也不在左侧块  说明出错了
                {
                    return 0x51;//第五步错误1
                }
            }
        }//扫描结束
        if(state==0)break;//满足条件不再处理

        //分 只有 0 1 2 三种情况处理

        if(n==0)//两种情况
        {
            temp=state&0x0F;
            temp=temp+(temp<<4);
            //寻找temp里的0101或0011二进制位所在位置
            for(i=0,Area_Operate=0; i<4; i++)
            {
                if((temp&(0x0F<<i))==(0x05<<i))// i=0-->i=4 即先逆时针旋转第i面  scene 3
                {
                    Area_Operate=i+0x30;
                    break;
                }
                else if((temp&(0x0F<<i))==(0x03<<i))// i=0-->i=4 即先逆时针旋转第i面  scene 6
                {
                    Area_Operate=i+0x60;
                    break;
                }
            }
            if(i==0)i=4;
            else if(i==4)return 0x53;//遇到不满足条件的


            //进行旋转
            //Turn_Cube(Area_Operate+0x10);//操作Area_Operate 再按逆时针转90
            //Turn_Cube(Area_Real+0x30);//底面再转180
            //Turn_Cube(Area_Operate+0x20);//操作Area_Operate 再按顺时针转90
            //Turn_Cube(Area_Real+0x20);//底面再转顺时针转90
            //Turn_Cube(Area_Operate+0x10);//操作Area_Operate 再按逆时针转90
            //Turn_Cube(Area_Real+0x20);//底面再转顺时针转90
            //Turn_Cube(Area_Operate+0x20);//操作Area_Operate 再按顺时针转90
        }
        else if(n==1)//两种情况
        {
            //找到state高四位为0的那位
            for(i=0; i<4; i++)
            {
                if((state&(0x10<<i))==0)break;
            }
            if(i==0)i=4;
            else if(i==4)return 0x54;//遇到不满足条件的

            //if((i&0x01)==0)i=6-i;// 2 4面互换
            //Area_Operate=(Color_D[i]>>3)&0x07;//需要操作的面  注意底面 的2与4面是正面看来的 4与2面

        }
        else if(n==2)//3种情况
        {
            //寻找state里高四位为1且对应第四位的那个为0
            temp=state | ((~(state>>4))&0x0F);
            for(i=0,Area_Operate=0; i<4; i++)
            {
                if((temp&(0x11<<i))==(0x10<<i))break;
            }
            if(i==0)i=4;
            else if(i==4)return 0x55;//遇到不满足条件的

            //if((i&0x01)==0)i=6-i;// 2 4面互换
        }
        else return 0x52;//第五步错误2  遇到非法情况！

        if((i&0x01)==0)i=6-i;// 2 4面互换
        //i=((i+3-(Color_D[5]>>6))&0x03)+1;//注意此时相当于底层将面值逆时针旋转 n*90  此处不需要了  开始寻找时已将其化为标准相对面
        Area_Operate=(Color_D[i]>>3)&0x07;//需要操作的面 注意底面 的2与4面是正面看来的 4与2面
#ifdef DEBUG5
        pause=1;
        printf ( "|| n=%X A=%X state=%X Pause",n,Area_Operate,state);////////////////
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif
        Turn_Cube(Area_Operate+0x10);//操作Area_Operate 再按逆时针转90
        Turn_Cube(Area_Real+0x30);//底面再转180
        Turn_Cube(Area_Operate+0x20);//操作Area_Operate 再按顺时针转90
        Turn_Cube(Area_Real+0x20);//底面再转顺时针转90
        Turn_Cube(Area_Operate+0x10);//操作Area_Operate 再按逆时针转90
        Turn_Cube(Area_Real+0x20);//底面再转顺时针转90
        Turn_Cube(Area_Operate+0x20);//操作Area_Operate 再按顺时针转90
#ifdef DEBUG5
        pause=1;
        printf ( "|| State  %X Pause",state);////////////////
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif
        LCD_Cube_Paint();////显示一次 清除标志位
    } while(state!=0);//当四角底面都是底面色  state高四位全为0

    printf ( "Mission 5 Finish\n");////////

    //还原底层角位置
    //依旧利用Mission 5的*seamed_edge_p1[4],*seamed_edge_p2[4],前者为左侧，后者为右侧  以标准相对位置的0-3
    //必然有一个角块位置是对的，若不对说明底层需要转
    //四角块侧面颜色 i=1 2面2(L) 1面3(R) i=2 Area1_2(L) Area4_3(R) i=3 Area4_2(L) Area3_3(R) i=4 Area3_2(L) Area2_3(R)


    //记录四侧面颜色
    seamed_edge_Color[0]=Cube[(Color_D[2]>>3)&0x07][4];
    seamed_edge_Color[1]=Cube[(Color_D[1]>>3)&0x07][4];
    seamed_edge_Color[2]=Cube[(Color_D[4]>>3)&0x07][4];
    seamed_edge_Color[3]=Cube[(Color_D[3]>>3)&0x07][4];


    do {
        Area_Operate=0;
        for(i=0,location=0,state=0,temp1=0; i<4; i++) //将各块需转的信息存入到location
        {
            location >>=2;//bit1-0记录角块1是否需要旋转（0不用 1逆时转90 2顺时90 3转180°） 高位依次类推
            if(i==3)j=0;
            else j=i+1;
            if(*seamed_edge_p1[i]!=seamed_edge_Color[i] || *seamed_edge_p2[i] !=seamed_edge_Color[j])//位置不对
            {
                state++;
                for(m=0; m<4; m++) //寻找此角属于哪个地方 即需要转多少度
                {
                    if(m==3)n=0;
                    else n=m+1;
                    if(*seamed_edge_p1[i]==seamed_edge_Color[m] && *seamed_edge_p2[i] ==seamed_edge_Color[n])//在哪个角
                        break;
                }
                if(m==4)return 0x61;//错误1 找不到
                //m>i 则它需要顺时针转  反之则逆时针
                temp=m>i?m-i:(i-m+0x80);//0x80代表此块需要 逆时针 转 90*（temp&0x0F）度才能归位
                if((temp&0x03)==2) {
                    location|=0xC0;
                    temp1++;
                }
                else
                {
                    if(temp&0x80)location |=0x40;//逆时针转
                    else location |=0x80;//顺时针转
                    if((temp&0x03)==3)location ^=0xC0;//转270度即为反向转90
                }

            }
            else Area_Operate=i;//for state=3
        }
#ifdef DEBUG6
        pause=1;
        printf ( "|| Loca %X state=%X Area_O=%X temp1 %X",location,state,Area_Operate,temp1);
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif
        if(state!=0)
        {
            if(state==3)//有三个不对则有两种情况
            {
                //对的角块所在位置与要操作面的关系：0-3  1-2  2-1 3-4
                Area_Operate=3-Area_Operate;
                if(Area_Operate==0)Area_Operate=4;
                //判断三角市顺时还是逆时针转
                for(i=0,j=location; i<4; i++,j>>=2)
                {
                    if((j&0x03)==0x02)//即是顺时针的圈
                    {   Area_Operate+=0x21;
                        if(Area_Operate==0x25)Area_Operate=0x21;
                        break;
                    }
                    else if((j&0x03)==0x01)//即是逆时针的圈
                    {
                        Area_Operate+=0x10;
                        break;
                    }
                }
                if(i!=4)Area_Operate=0x80+Area_Operate;//操作面
            }
            else if(state==4)
            {
                //若四个角不对的情况有2种(及2种直接可以复原的)：两两间互换(对角交换的话 可以在此直接完成)、8字形交换-> 转90度变3个不同的情况 (或3、口字形顺逆时换 此时转90度及复原)
                if(temp1==4)//即转180即可
                    Turn_Cube(Area_Real+0x30);//底面再转180
                else if(temp1==2)//8字形
                {
                    Turn_Cube(Area_Real+0x20);//底面再转顺时针转90
                }
                else//没有要转180°的      口字形顺逆时换、水平或竖直两两间互换
                {
                    if(location==0xAA)//口字形顺逆时换
                    {
                        Turn_Cube(Area_Real+0x20);   //底面再转顺时针转90
                    }
                    else if(location==0x55)//口字形顺逆时换
                    {
                        Turn_Cube(Area_Real+0x10);//底面再转逆时针转90
                    }
                    else //随便挑选一个方向拧一次三者交换的公式   两两间互换
                    {
                        //2+0x30 1+0x30 2+0x20 3+0x20 2+0x10 1+0x30 2+0x20 3+0x10 2+0x20（1  3是从底面往上看的 与实际相对标准面不同 2 - 4交换即可）
                        //找到要两两交换的同一侧 如0<-->1  2<-->3  找到01的那个侧面
                        Turn_Cube(Area_Real+0x10);//5'   需添加此
                        for(i=0; i<8; i+=2)
                        {
                            if((location&(0x03<<i))==(0x02<<i))
                                break;
                        }
#ifdef DEBUG6
                        printf ( "! i=%X Loca=%X\n",i,location);

#endif
                        //对的角块所在位置与要操作面的关系：0-1  1-4  2-3 3-2
                        Area_Operate=5-(i>>1);
                        if(Area_Operate==5)Area_Operate=1;
                        Area_Operate+=0xB0;//操作
                    }
                }
#ifdef DEBUG6
                printf ( "state=4; Area_Operate=%X\n",Area_Operate);

#endif

            }
            else //除以上外只有2个不对情况了
            {
                // 0-3 四个角位置 01对 23需调换(底面转90度变1个是正确的) 02对 13需调换(此时不按公式转，要转底面90 把其弄成4个不同的状态)
                Turn_Cube(Area_Real+0x20);//底面再转顺时针转90
            }

            if(Area_Operate&0x80)//有需要操作
            {
#ifdef DEBUG6
                printf ( " Area_Operate=%X  lo=%X\n",Area_Operate,location);

#endif
                i=Area_Operate&0x70;//判断是属于哪种方式
                Area_Operate&=0x0F;
                temp= Area_Operate;
                m=(Area_Operate+1);//加1面
                if(m>4)m=1;
                n=Area_Operate-1;//减一面
                if(n==0)n=4;
                Area_Operate=(Color_D[temp]>>3)&0x07; //算出实际操作面

                m=(Color_D[m]>>3)&0x07;//算出实际操作面

                n=(Color_D[n]>>3)&0x07;//算出实际操作面

#ifdef DEBUG6
                pause=1;
                printf ( "|| n= %X Ar=%X m=%X",n,Area_Operate,m);
                while(pause && flag)delay_us(100);///////////////暂停
                printf ( " >\n");
#endif
                //操作面旋转
                if(i==0x10)//是逆时针的圈
                {   Turn_Cube(Area_Operate+0x30);//当前面再转180
                    Turn_Cube(m+0x30);//+1面再180
                    Turn_Cube(Area_Operate+0x20);//当前面再转顺时针转90
                    Turn_Cube(n+0x20);//-1面再转顺时针转90
                    Turn_Cube(Area_Operate+0x10);//当前面再转逆时针转90
                    Turn_Cube(m+0x30);//+1面再转180
                    Turn_Cube(Area_Operate+0x20);//当前面再转顺时针转90
                    Turn_Cube(n+0x10);//-1面再转逆时针转90
                    Turn_Cube(Area_Operate+0x20);//当前面再转顺时针转90

                }
                else if(i==0x20)//是顺时针的圈
                {   Turn_Cube(Area_Operate+0x30);//R2
                    Turn_Cube(n+0x30);//D2 R-1
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(m+0x10);//U' R+1
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(n+0x30);//D2 R-1
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(m+0x20);//U  R+1
                    Turn_Cube(Area_Operate+0x10);//R'
                }
                else if(i==0x30) //两两间互换 两边之间
                {
#ifdef DEBUG6
                    pause=1;
                    printf ( "|| i=0x30 Ar=%X m=%X",Area_Operate,m);
                    while(pause && flag)delay_us(100);///////////////暂停
                    printf ( " >\n");
#endif
                    //Turn_Cube(Area_Real+0x10);//5'   需添加此
                    //以下为相邻两个面（m与Area_Operate）的棱边交换及这两个相邻面所形成的对角交换
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x20);//5
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x10);//5'
                    Turn_Cube(m+0x10);//m'
                    Turn_Cube(Area+0x20);//0
                    Turn_Cube(m+0x10);//m'
                    Turn_Cube(Area+0x10);//0'
                    Turn_Cube(m+0x30);//m2
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(m+0x10);//m'
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(m+0x20);//m
                    Turn_Cube(Area_Operate+0x20);//R

#ifdef DEBUG6
                    pause=1;
                    printf ( "|| END turn");
                    while(pause && flag)delay_us(100);///////////////暂停
                    printf ( " >\n");
#endif
                }
            }
            LCD_Cube_Paint();////显示一次 清除标志位
        }
#ifdef DEBUG6
        pause=1;
        printf ( "State %X",state);
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif
    } while(state!=0);//}while(state!=0);

    printf ( "Mission 6 Finish\n");////////

    ////还原底层棱边位置
    // 4棱边都不对、3个不对（两个不对的话要转换了：顺或逆时针转90度即可 变为四个不对的平行交换 或变成3个不对的）

    //记录四条棱边侧面颜色
    //记录四侧面颜色
    seamed_edge_Color[0]=Cube[(Color_D[1]>>3)&0x07][4];
    seamed_edge_Color[1]=Cube[(Color_D[4]>>3)&0x07][4];
    seamed_edge_Color[2]=Cube[(Color_D[3]>>3)&0x07][4];
    seamed_edge_Color[3]=Cube[(Color_D[2]>>3)&0x07][4];
    //先将信息准备好  即相对面的1-4棱边地址存入seamed_edge_p2
    for(i=1; i<5; i++)
    {
        n=(i&0x01)?i:6-i;
        seamed_edge_p2[i-1]=&Cube[(Color_D[n]>>3)&0x07][Area_index[(6-(Color_D[n]>>6))&0x03]&0x0F];//顺时针2
    }

    do
    {
        location=0;//location bit1-0表示0位置的棱块需要移动多少度 n*90 其余一样

        //注意底面与正面相对位置是旋转了  具体在Color_D高两位
        //(i+(Color_D[5]>>6))&0x03---->实际底面的i（0-3）转为相对面的（0-3）  下面算法处不需要这样了

        for(i=0,temp=0,state=0,j=0xFF; i<4; i++)
        {
            if(seamed_edge_Color[i]!=*seamed_edge_p2[i])
            {   state|=(0x01<<i);
                temp++;
                //查找它应在什么地方
                for(m=0; m<4; m++)
                {
                    if(seamed_edge_Color[m]==*seamed_edge_p2[i])break;
                }
                if(m==4)return 0x71+i;

                m=m>i?m-i:4-i+m;//  此处：4-（i-m）
                location+=(m<<(i<<1));
            }
            else j=i;//for temp=3  记录对的棱在哪个面

        }


#ifdef DEBUG7
        /*printf ( "DI:%X Color0:%X--%X\n",Area_Real,seamed_edge_Color[0],*seamed_edge_p2[0]);
        printf ( "Color1:%X--%X \n",seamed_edge_Color[1],*seamed_edge_p2[1]);
        printf ( "Color2:%X--%X \n",seamed_edge_Color[2],*seamed_edge_p2[2]);
        printf ( "Color3:%X--%X \n",seamed_edge_Color[3],*seamed_edge_p2[3]);*/

        pause=1;
        printf ( "|| Start:state:%X Lo:%X temp:%X j %X",state,location,temp,j);
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif

        //对检查结果进行处理
        if(temp!=0)
        {
            if(temp==4)
            {
                if(location==0xAA)//十字交换的  M'2 U' M'2 U2 M'2 U' M'2
                {
                    Area_Operate=0x02;//从任意面开始都行
                    //m= Area_Operate+2;
                    //if(m>4)m &=0x03;//Area_Operate对面
                    m=(Color_D[4]>>3)&0x07;
                    Area_Operate=(Color_D[2]>>3)&0x07;

                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);
                    Turn_Cube(Area+0x10);//0面'
                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);
                    Turn_Cube(Area_Real+0x30);//5_2
                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);
                    Turn_Cube(Area+0x10);//0'
                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);

                }
                else if((location&0x0F)==(location>>4))//平行的交换  寻找1101 二进制里 (U R' U')(R U' R)(U R U')(R' U R U)(R2 U')(R' U)
                {

                    for(i=0; i<5; i+=2)
                    {
                        if((location&(0x0F<<i))==(0x0D<<i))
                        {
                            break;
                        }
                    }
                    if(i==6)return 0x77;//找不到！
                    i>>=1; //i=0 - 2
                    Area_Operate=i+1;////0即第1面
                    Area_Operate=(Color_D[Area_Operate]>>3)&0x07;//转为实际面

                    Turn_Cube(Area_Real+0x20);//U
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x20);//U
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x20);  //U
                    Turn_Cube(Area_Operate+0x20); //R
                    Turn_Cube(Area_Real+0x20); //U
                    Turn_Cube(Area_Operate+0x30); //R2
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x20); //U

                }
                else return 0x76;//遇到不可料的情况
            }
            else if(temp==3)
            {
                Area_Operate=4-j;//对应底面顺时针+1的面 0->4  1->3 2->2 3->1
                Area_Operate=(Color_D[Area_Operate]>>3)&0x07;//转为实际面
                //判断三角是顺时还是逆时针转
                for(i=0,j=location,temp1=0; i<4; i++,j>>=2)
                {
                    if((j&0x03)==0x01)//即是顺时针的圈   (R2 U)(R U R' U')(R' U')(R' U R')
                    {
                        temp1=0x20;
                        break;
                    }
                    else if((j&0x03)==0x03)//即是逆时针的圈  (R U' R) (U R U R) (U' R' U’R2)
                    {
                        temp1=0x10;
                        break;
                    }
                }
                if(temp1==0)return 0x78;////

                if(temp1==0x20)//	//针对顺时三角
                {
                    Turn_Cube(Area_Operate+0x30);//R2
                    Turn_Cube(Area_Real+0x20);//U
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x20);//U
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x20);//U
                    Turn_Cube(Area_Operate+0x10);//R'
                }
                else //针对逆时三角
                {
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x20);//U
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x20);//U
                    Turn_Cube(Area_Operate+0x20);//R
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x10);//R'
                    Turn_Cube(Area_Real+0x10);//U'
                    Turn_Cube(Area_Operate+0x30);//R2
                }
            }
            else  //只剩2个不对的   只能说明安装错误
            {
                return 0x75;// 此处是不可达到的
                //Turn_Cube(Area_Real+0x20);//底面再转顺时针转90
            }

            //旋转测试
            //m= Area_Operate+2;
            //if(m>4)m &=0x03;//Area_Operate对面
            //m=(Color_D[m]>>3)&0x07;


#ifdef DEBUG7
            pause=1;
            printf ( "|| temp1 %X  OP %X Lo %X",temp1,Area_Operate,location);
            while(pause && flag)delay_us(100);///////////////暂停
            printf ( " >\n");
#endif

            LCD_Cube_Paint();////显示一次 清除标志位
        }

#ifdef DEBUG7
        pause=1;
        printf ("|| State %X temp %X ",state,temp);
        while(pause && flag)delay_us(100);///////////////暂停
        printf ( " >\n");
#endif
    } while(state!=0);

    printf ( "|| End Pause\n");//表示暂停  发送’A’字符继续
    pause=1;////////////////
    while(pause && flag)
        delay_us(100);///////////////暂停
    printf ( " >\n");
    //USART_RX_STA=0;
    flag=0;
    return 0;

}

