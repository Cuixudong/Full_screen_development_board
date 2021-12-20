#include "sys.h"
#include "delay.h"
#include "lcd.h"

struct rotate//����ߵĹ��� ����ǰ��ĸ�������
{
    u8 *Up[3];
    u8 *Down[3];
    u8 *Left[3];
    u8 *Right[3];

};
u8 Red,Gre,Blu;
u8 Cube[6][9];//magic cube color
typedef struct//����ߵĹ��� ����ǰ��ĸ�������
{
    u8 *Up[3];
    u8 *Down[3];
    u8 *Left[3];
    u8 *Right[3];
} rotate;
struct rotate Cube1[6];

u8 pause=0,flag=0;

/********************����ΪTFT��ʾ���� ����Ϊ��ԭ�㷨**********************/
//15*15   ���� �ϵ���Cube[0-5][0-8]  bit2-0:color  bit3:change
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
            horizontal=143;  // 1�� 4���д�λ ͼ����ʾ��
            vertical=(i-1)*63+10;
        }
        else
        {
            horizontal=80;
            vertical=136;
        }
        for(j=0; j<9; j++)
        {
            if(Cube[i][j]&0x08) //�иı��ȥ�ػ�
            {
                //��ɫ��ֵ
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
                LCD_Fill(t1-20,t2,t1-1,t2+20-1,(((Red>>3)<<11)|((Gre>>2)<<5)|Blu>>3));//����ֱ�������ɫ
                Cube[i][j]&=0xF7; //clear flag
            }
        }
    }
    //LCD_Write_Data_End();
}

void init_Cube(void)
{
    u8 i,j;///////////// ��ʼ��ʾ
    for(i=0; i<6; i++) ///
        for(j=0; j<9; j++) ////
            Cube[i][j]=i+0x08;///���������ɫ

    //6������� struct rotate��������ģ��
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

//������ת�� bit2-0  3��ת��bit5-4 0undo 1 turn left  2 turn right  3turn back
//��ת��ǰ�� ��Ӱ�쵽����߿鼴 struct rotate
void Turn_Cube( u8 direction )
{
    u8 center;
    u8 temp,i;
    center=direction&0x07;
    if(center>5) return ;
    switch(direction&0x30)
    {
    case 0x10:
        //�޸Ĳ���
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
        //�޸Ĳ���
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
        //�޸Ĳ���
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
    //while(pause && flag)delay_us(100);///////////////��ͣ
}

u8 Check(u8 i)//�ж��㷨�Ƿ���� ֻд��ǰ�����׶�
{
    //u8 temp,temp1;
    u8 end=i&0xF0;
    i &=0x0F;
    if(Cube[i][4]!=Cube[i][1] || Cube[i][4]!=Cube[i][3]||Cube[i][4]!=Cube[i][5]||Cube[i][4]!=Cube[i][7])
        return 0x11;//���ϲ���
    if(Cube[(Cube1[i].Up[1]-Cube[0])/9][4]!=*Cube1[i].Up[1])
        return 0x12;
    if(Cube[(Cube1[i].Down[1]-Cube[0])/9][4]!=*Cube1[i].Down[1])
        return 0x13;
    if(Cube[(Cube1[i].Left[1]-Cube[0])/9][4]!=*Cube1[i].Left[1])
        return 0x14;
    if(Cube[(Cube1[i].Right[1]-Cube[0])/9][4]!=*Cube1[i].Right[1])
        return 0x15;
    if(end==0x10)//��һ�׶�У��
        return 0;

    if(Cube[i][4]!=Cube[i][0] || Cube[i][4]!=Cube[i][2]||Cube[i][4]!=Cube[i][8]||Cube[i][4]!=Cube[i][6])
        return 0x21;//���ϲ���
    if(Cube[(Cube1[i].Up[1]-Cube[0])/9][4]!=*Cube1[i].Up[0] || Cube[(Cube1[i].Left[1]-Cube[0])/9][4]!=*Cube1[i].Left[0])//��һ����
        return 0x22;
    if(Cube[(Cube1[i].Up[1]-Cube[0])/9][4]!=*Cube1[i].Up[2] ||Cube[(Cube1[i].Right[1]-Cube[0])/9][4]!=*Cube1[i].Right[0])//��2����
        return 0x23;
    if(Cube[(Cube1[i].Right[1]-Cube[0])/9][4]!=*Cube1[i].Right[2] ||Cube[(Cube1[i].Down[1]-Cube[0])/9][4]!=*Cube1[i].Down[2])//��3����
        return 0x24;
    if(Cube[(Cube1[i].Down[1]-Cube[0])/9][4]!=*Cube1[i].Down[0] || Cube[(Cube1[i].Left[1]-Cube[0])/9][4]!=*Cube1[i].Left[2])//��4����
        return 0x25;
    if(end==0x20)//�ڶ��׶�У��
        return 0;
    return 0;
}


//��ĳһ�滹ԭħ�� ���ֻ�����
unsigned char Cube_Restore(u8 face)
{

    u8 Area= face&0x07,order;
    u8 Color_D[6];//self,Up,Right,Down,Left,Opposite;  0-5
    //bit 2~0 color bit 5-3 Area  bit7-6:�Զ���Ϊ׼��Area���ϣ�����������Cube��ʽ�洢ʱ������򣨴���һ����������0-2��3-5��6-8��˳ʱ��ת 90*n
    //�����������Area��ת�ĽǶ� 90*n
    u8 location;//�����λ�� ��Ա�׼λ�� bit6-4 �� 0-���棨Area �������¿��� 1�� 2�� 3�� 4�� 5-��
    //bit1-0 0-3�ı�׼λ�ã�˳ʱ����  �� �� �� ��  bit7 0ż��0 2 8 6�� 1������1 5 7 3�飩 �磺0x81-->���� ��5��
    u8 i,j,temp,temp1,m,n;

    u8 target_C1,target_C2;//Ŀ����ɫ1 2����ߺ��ұߵģ�
    u8 Area_Operate,Area_Real,Area_Calc;
    u8 compare1[3],compare2[3],index_temp,data_temp;//����������ɫ�Ա� �Ӵ�С����

    u8 Area_index[4]= {1,5+0x20,7+0x80,3+0x60}; //˳ʱ��0 2 8 6�� 1 5 7 3 ����λ��ż����
    u8 state=0;//����3�õ���״̬��־	 bit0-3 1-4���Ƿ�Ժ� 1�Ժ� 0��
    u8 *seamed_edge_p1[4],*seamed_edge_p2[4],seamed_edge_Color[4];//�������¿� �м���1����ߣ�˳ʱ���� 1-4�����Ϊseamed_edge_p1[0]���ұ�Ϊseamed_edge_p2[0]
    //seamed_edge_Color�洢������������ɫ������λΪ��ߵ���ɫ������λΪ�ұߵ�

    flag=1;

    //����������ɫ
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


    //�Ȼ�ԭĳһ���ʮ��  cross �� �� �� ������

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
        if(temp==Cube[Area][4] && temp1 == (Color_D[order]&0x07))//������ȷλ��
        {}
        else//���������ǿ�
        {
            for(i=0,location=4; i<6; i++) //Color_Up Cube[Area][4]
            {
                temp=((Color_D[i]&0x38)>>3);//ɨ��ڼ���
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

            //������������� Ŀ��ɫ���ڣ� ���� ���� ����
            if((location&0x70)==0 || (location&0x70)==0x50)//�ڱ�������
            {
                //���ڱ�����Ϊ�������
                if((location&0x70)==0)
                {
                    temp=(Color_D[1+(location&0x03)]>>3)&0x07;
                    Turn_Cube(0x30+ temp);//�˿������ĸ����� ��ת�ĸ���
                    //printf ( "Step%d %X\n",order,0x30+ temp);///////////////
                    temp=(location&0x03)+1;
                    if(temp!=1)location =0xD0+5-temp;//ע������������淴��
                    else  location=0xD0;
                }
                //Up�Ǹ�ʱ���Ƚ��˿��ڵ�����ת���������������Ҳ�
                if((order&0x01)!=(location&0x01))
                {
                    Turn_Cube(0x20+ ((Color_D[5]>>3)&0x07));//������ת90
                    //printf ( "Step%d %X\n",order,0x20+ ((Color_D[5]>>3)&0x07));///////////////
                    location=((location+1)&0xF3);
                }
                //�жϴ˿������ĸ����� 1-4  location&0x03��0--1�� 3->2�� 2->3�� 1->4��
                temp1=location&0x03;
                //printf ( " L: %X T1 %X\n",location,temp1);///////////////
                if(temp1==0)
                {
                    temp=1;
                }
                else {
                    temp=5-temp1;
                }
                temp1=(Color_D[temp]>>3)&0x07;//Ҫ��ת�Ĳ���
                //���Ҫת������У��Ŀ�괦�Ҳ�����ʱ��ת90����֮˳ʱ��90

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
                Turn_Cube(temp+temp1);//��Ŀ���ת���м��
                //printf ( "Step%d %X\n",order,temp+temp1);///////////////
                if(temp==0x10)temp=0x20;
                else temp=0x10;
                Turn_Cube( ((Color_D[order]>>3)&0x07) +temp);//��Ŀ���ת��λ
                //printf ( "Step%d %X\n",order,((Color_D[order]>>3)&0x07) +temp);///////////////
                Turn_Cube(temp+temp1);//��ת���Ĳ���ת��ȥ
                //printf ( "Step%d %X\n",order,temp+temp1);///////////////
            }

            else //�ڲ���
            {
                //�Ƚ��˴�ת������  0-180  1-90 2-0  3-270
                i=location&0x03;
                temp=0;

                temp1=(location>>4)&0x07;//�ڵڼ����� ��׼��Ե�

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
                    Turn_Cube( ((Color_D[temp1]>>3)&0x07) +temp);//��Ŀ���ת����
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
                    Turn_Cube(((Color_D[5]>>3)&0x07) +temp);//��Ŀ���ת��order��ĵ�
                    if(i)Turn_Cube(((Color_D[temp1]>>3)&0x07) +i);//��ԭ�����ĵط�
                    Turn_Cube(((Color_D[order]>>3)&0x07) +0x30);//ת��Ŀ��λ��
                }
            }
        }
        order++;
        LCD_Cube_Paint();//��ʾһ��
    } while(order<5);
    //��һ�׶����
    //У���һ�׶�
    temp=Check(Area+0x10);
    if(temp)return temp;
    else  printf ( "Mission 1 Finish\n");////////

    //return 0;////////

    //	pause=1;////////////////
    //	while(pause && flag)delay_us(100);///////////////��ͣ


    //������Ľ�
    //���ж��Ƿ�λ�ö�  �����0 2 6 8 �ĸ�  location 0x00-0x03

    order=1;//1-4
    //�Զ���Ϊ�� �ֱ��ж��ĸ���
    do {
        switch(order)//�ֱ���ȡ�ĸ�����ɫ
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
        else //��ɫ������Ҫ����
        {
            //���ҵ�Ŀ���(Color[0]����ɫ�����ڵ�λ��)
            location=0xFF;
            i=0;//
            //���ڵײ���  0 2 8 6�����棩 ����  ����  ����  ����
            Area_Real=(Color_D[5]>>3)&0x07;//����ʵ�ʵ���
Again1:
            while((++i)<5)
            {
                switch(i)//��ȡ�ǿ���ɫ
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
                //�ж�temp temp1 j    target_C1 target_C2 Cube[Area][4]
                compare1[0]=temp+0x10;
                compare1[1]=temp1+0x20;
                compare1[2]=j+0x30;
                compare2[0]=target_C1+0x10;
                compare2[1]=target_C2+0x20;
                compare2[2]=Cube[Area][4]+0x30;
                index_temp=2;
                //ð������
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
                            if(n==index_temp)index_temp=m;//�洢�±�
                        }
                    }
                if((compare1[0]&0x0F)!=(compare2[0]&0x0F) || (compare1[1]&0x0F)!=(compare2[1]&0x0F) || (compare1[2]&0x0F)!=(compare2[2]&0x0F))
                    continue;
                //����Ŀ���Cube[Area][4] �ڲ����Ļ������
                m=(compare1[index_temp]>>4);//
                if(Area_Real==((Color_D[5]>>3)&0x07))//�ڵ���
                {
                    //�Ȱ�i������Ա�׼���1-4
                    //�жϵ�����ת�˶��ٶ�
                    n=(Color_D[5]>>6);
                    if(n!=0)
                    {
                        n=i+n;
                        if(n>4)n&=0x03;
                    }
                    else n=i;
                    if(m==3)location=0x50+n-1;//ʶ����� Ӧ������Ա�׼��� 0-3������
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
                else//���ϲ�����
                {
                    if(m==3)location=i-1;
                    else
                    {
                        location=m-1;
                        location+=((i+m-2)<<4);
                        if((location&0xF0)==0)location |=0x40;//����������

                    }

                }
                //		i++;
            }
            if(location==0xFF && Area_Real==((Color_D[5]>>3)&0x07)) {
                Area_Real=Area;
                i=0;
                goto Again1;
            }

            if(location==0xFF)return 0x21;//�ڶ��׶δ���1

            //if(order==4){printf ( "Lo %X",location);return 0;}//////////////////

#ifdef DEBUG2
            printf ( "Pause:order %X Find  Location %X",order,location);///////
            pause=1;
            while(pause && flag)delay_us(100);//////��ʾ��ͣ  ���͡�A���ַ�����  �������(��ͬ)
            printf ( " >\n");
#endif
            //�ҵ�����λ��
            //�ܼ�Ŀ����ɫ��������ܼ����
            //���ڶ��㻻���ױ�ȥ
            //1.�ڱ����� ����L ����L ����R ����Ϊ�ɼ�״̬��
            //2.�ڲ��ϲ�
            if((location&0xF0)==0)
            {
                Area_Operate=(Color_D[(location&0x03)+1]>>3)&0x07;//˳ʱ����ת����
                temp=(Color_D[5]>>3)&0x07;//����ʵ��
                Turn_Cube(Area_Operate+0x20);//��Ŀ���ת���ĵײ�

                Turn_Cube(temp+0x20);//����˳ʱת90��
                Turn_Cube(Area_Operate+0x10);//��Ŀ���ת�����ϲ�
                location=(((location&0x03)+3)<<4) +3;  //�ڲ�����Ķ���
                if((location&0xF0)>0x40)
                    location &=0x3F;//Ĩ����� ʹ��Ϊ1-4��
            }
            else if((location&0xF0)!=0x50 && (location&0x03)<2)//0 1���ϲ� 2 3�²㣡����
            {
                temp=(location>>4);
                if(location&0x01)//����  �������1������ʱ��ת ������˳ʱ��ת90  ��������˳ʱת��ȥ  ����ڲ�����ļ�1��2��ԭ�����棩
                {
                    if(temp==1)Area_Operate=(Color_D[4]>>3)&0x07;
                    else Area_Operate=(Color_D[temp-1]>>3)&0x07;
                    temp1=0x10;
                    location+=1;
                }
                else  //0 �������1����˳ʱ��ת90 ��������ʱ��ת90  ����������ʱת��ȥ ����ڲ�����ļ�1��3��ԭ�����棩
                {
                    if(temp==4)Area_Operate=(Color_D[1]>>3)&0x07;
                    else Area_Operate=(Color_D[temp+1]>>3)&0x07;
                    temp1=0x20;
                    location+=3;
                }

                //  printf ( "A_Op1  %X %X\n",Area_Operate+temp1,location);//////////
                //  pause=1;////////////////
                //	while(pause && flag)delay_us(100);///////////////��ͣ

                Turn_Cube(Area_Operate+temp1);//��Ŀ���ת�����²�
                if(temp1==0x10)temp1=0x20;
                else temp1=0x10;
                Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//������   ת90

                Turn_Cube(Area_Operate+temp1);//����������ʱת��ȥ

            }
            else if((location&0xF0)==0x50)//�����ɼ���Ŀ���  ���ڵ���
            {
                //�Ƚ��˿�ת����Ŀ��λ���·�������
                //	printf ( "Lo undo  %X Pause \n",location);//////////

                //	pause=1;printf ( "   Pause\n");////////////////
                //	while(pause && flag)delay_us(100);///////////////��ͣ

                //order1-location&0x03(1) 2-0 3-3 4-2
                temp=location&0x03;
                if((temp&0x01)==0)temp+=2;//�����λ��
                //������������ת�Ƕ�90*n
                if(temp!=order)
                {
                    if(((temp^order)&0x01)==0) {
                        temp1=0x30;   //����Ҫת180��
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

                    Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//������  ת90
                    //	printf ( "Lo undo  %X order %X temp1%X\n",location,order,temp1);//////////

                    if(temp1==0x10) {
                        if(location&0x03)temp=location-1;    /////////���Բ���
                        else temp=location+3;
                    }
                    else if(temp1==0x20) {
                        temp=location+1;
                        temp &=0xF3;
                    }
                    else {
                        temp=location+2;    //////////���Բ���
                        temp &=0xF3;
                    }

                    location=0x50+order;
                    if((order&0x01)==0)location-=2;

                    if(temp!=location)return 0x22;///����2
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
                temp1=0x10;//��ʱ��ת

                //	printf ( "PR Ar   %X\n",Area_Operate+temp1);//////////
                //	pause=1;printf ( "   Pause\n");////////////////
                //	while(pause && flag)delay_us(100);///////////////��ͣ

                Turn_Cube(Area_Operate+temp1);//��Ŀ���ת�����

                temp1=temp1^0x30;//5-4λȡ��
                Turn_Cube(((Color_D[5]>>3)&0x07)+0x20);//������˳ʱ��ת90

                //	printf ( "Ar   %X\n",Area_Operate+temp1);//////////
                //	pause=1;////////////////
                //	while(pause && flag)delay_us(100);///////////////��

                Turn_Cube(Area_Operate+temp1);//����������ʱת��ȥ
            }
            //�ײ㴦��
            //�Ƚ���Ŀ��������ȷλ�����·�
            //����˿������ĸ�������
            if((location&0x03)==2)temp=(location>>4);
            else {
                temp=(location>>4)+1;
                if(temp==5)temp=1;
            }
            //������order�����ٶ�
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
                //	while(pause && flag)delay_us(100);///////////////��ͣ

                Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//������ ת90*n	������

                if(temp1==0x10)//���1
                {
                    if((location&0xF0)==0x40)location=0x10+(location&0x03);
                    else location+=0x10;
                }
                else if(temp1==0x20)//���1
                {
                    if((location&0x70)==0x10)location=0x40+(location&0x03);
                    else location-=0x10;
                }
                else //���2
                {
                    location+=0x20;
                    if((location&0x70)>0x40)location &=0x3F;//Ĩ����� ʹ��Ϊ1-4��
                }
            }


            //���������·���
            if((location&0x03)==2)
            {
                temp1=0x20;
            }
            else
            {
                temp1=0x10;//��ʱ��ת
            }

            Area_Operate=(Color_D[location>>4]>>3)&0x07;
            Turn_Cube(Area_Operate+temp1);//������ ת

            Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//�����ٰ�temp1ת90
            temp1 =temp1^0x30;


            Turn_Cube(Area_Operate+temp1);//����������ʱת��ȥ
            //printf ( "Area_Op  %X\n",Area_Operate+temp1);//////////
#ifdef DEBUG2
            pause=1;
            printf ( "  Order %X Pause",order);////////////////
            while(pause && flag)delay_us(100);///////////////��ͣ
            printf ( " >\n");
#endif
            //return 0;
        }
        order++;
        LCD_Cube_Paint();//��ʾһ��
        //ÿ��У����

    } while(order<5);

    temp=Check(Area+0x20);
    if(temp)return temp;
    else  printf ( "Mission 2 Finish\n");////////

    //�м�㴦�� �ĸ�
    //order=1;
    //do{
    // 	//��order Ϊ1 �����������ɫΪʵ�ʿ��3-(Color_D[4]>>6)  3Ϊ˳ʱ��0-3������0-ԭ���1�� 1-5 2-7 3-3��
    //	//(Color_D[4]>>6)= 0-3 ��0 90 180 270��  ���ֱ�Ϊ3 2 1 0��3�Ŀ�ת���ٶȺ�
    //	//ͬ�� �ϲ����� ʵ�ʿ飺1-(Color_D[1]>>6)+4 �����и��� ����+4 ���bit2��0)��0��-1 90��-0 180��-3 270��-2
    //	//�ֱ���ȡ�ĸ�����ɫ ���������¿�˳ʱ��1-4  temp temp1Ϊʵ����ɫ target_C1 target_C2ΪĿ����ɫ����Ϊ1 ��Ϊ2��

    //	m=order-1;if(m==0)m=4;
    //	temp=Cube[(Color_D[m]>>3)&0x07][Area_index[3-(Color_D[m]>>6)]&0x0F];
    //	temp1= Cube[(Color_D[order]>>3)&0x07][Area_index[(5-(Color_D[order]>>6))&0x03]&0x0F];
    //	target_C1=Color_D[m]&0x07;target_C2=Color_D[order]&0x07;
    //
    //	if(temp==target_C1 && temp1==target_C2)//Ŀ����ɫ�Ե�
    //	{}
    //	else
    //	{
    //	 //������Ҫ�ҵ��ǿ�����

    //	}
    // LCD_Cube_Paint();//��ʾһ��
    // //ÿ��У����
    // m=order-1;if(m==0)m=4;
    //	temp=Cube[(Color_D[m]>>3)&0x07][Area_index[3-(Color_D[m]>>6)]&0x0F];
    //	temp1= Cube[(Color_D[order]>>3)&0x07][Area_index[(5-(Color_D[order]>>6))&0x03]&0x0F];
    // if(temp!=target_C1 || temp1!=target_C2)return 0x33;//����3
    //
    //  order++;
    //}while(order<5);

    //���ڵײ���û�еײ���ɫ���� �ٽ���ŵ���׼λ�ã��ײ��Ҳ���˵���м����λ�û���ɫû�Ժã��ٽ���������ײ��ٴ���
    //�ټ���м�������Ƿ񶼻�ԭ���������ѭ������

    //u8 *seamed_edge_p1[4],*seamed_edge_p2[4],seamed_edge_Color[4];//�������¿� �м���1����ߣ�˳ʱ���� 1-4�����Ϊseamed_edge_p1[0]���ұ�Ϊseamed_edge_p2[0]
    //seamed_edge_Color�洢����������Ŀ����ɫ������λΪ��ߵ���ɫ������λΪ�ұߵ�
    state=0;////////��ʼ��
    //�Ƚ���Ϣ׼����
    for(n=1; n<5; n++)
    {
        m=n-1;
        if(m==0)m=4;
        seamed_edge_p1[n-1]=&Cube[(Color_D[m]>>3)&0x07][Area_index[3-(Color_D[m]>>6)]&0x0F];
        seamed_edge_p2[n-1]=&Cube[(Color_D[n]>>3)&0x07][Area_index[(5-(Color_D[n]>>6))&0x03]&0x0F];
        //seamed_edge_Color[n-1]=Color_D[m]&0x07;
        seamed_edge_Color[n-1]=((Color_D[m]&0x07)<<4)+(Color_D[n]&0x07);
    }
    //����ɨ���ĸ��м�����Ƿ��й�λ��
    for(i=0; i<4; i++)
    {
        if(*seamed_edge_p1[i]==(seamed_edge_Color[i]>>4) && *seamed_edge_p2[i]==(seamed_edge_Color[i]&0x0F))
            state |=(1<<i);
    }
    while((state&0x0F)!=0x0F)
    {
        temp=Color_D[5]&0x07;//�ײ�����ɫ

        for(i=0; i<4; i++) //�ڵ��� 0 -3 �ҷ���Ҫ������  0�鴦��Ӧʵ�ʵ�0��ת��n=0��ʱ��  3��90�㣩 2��180�㣩 1��270�㣩  0+4-n
        {
            temp1=Area_index[(i+4-(Color_D[5]>>6))&0x03]&0x0F;
            target_C1=Cube[(Color_D[5]>>3)&0x07][temp1];//����������ɫ

            switch(temp1)//�ҵ����ɫ
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
        if(i!=4)//�ҵ�û�еײ���ɫ����
        {
            //�Ƚ��˿�����ɫ�����������ɫ���루����תn*90�ȣ�
            n=5-i;//target_C2�ڵ���˿���Ա�׼λ�� 1-4
            if(n==5)n=1;
            //target_C2��ɫӦ���Ǹ��棨��Ա�׼���棩
            for(m=1; m<5; m++)
            {
                if(target_C2==(Color_D[m]&0x07))break;
            }
            if(m==5)return 0x31;//����1
            //�������Ҫ��תn*90
            if(m!=n) {
                i=m>n?(m-n):(n-m+0x10);//m>n ��Ҫ������ʱ��תi*90 ��֮˳ʱ��ת
                if((i&0x03)==2)temp1=0x30;
                else
                {
                    temp1=0x10+(i&0x10);
                    if((i&0x03)==3)temp1 ^=0x30;//����ȡ��
                }

                Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//�����ٰ�temp1ת90
            }

            location=0x82+(m<<4);
#ifdef DEBUG3
            pause=1;
            printf ( "under %X",location);
            while(pause && flag)delay_us(100);///////////////��ͣ
            printf ( " >\n");
#endif

            //��ת����׼λ��
            //����target_C1��ɫ�� location�������໹���Ҳࣺ���������location����ʱ��ת90 ��֮��˳ʱ��ת90
            //Area_Operate=(Color_D[(location>>4)&0x07]>>3)&0x07;
            Area_Operate=(Color_D[m]>>3)&0x07;
            temp=m-1;//��ߵ�
            //temp1=m+1;//�ұߵ�
            if(temp==0)temp=4;
            //if(temp1==5)temp1=1;

            if((Color_D[temp]&0x07)==target_C1)//��ߵ�������ɫһ��  location����ʱ��ת90
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
                if(i&0x01) Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//�����ٰ�temp1ת90
                else Turn_Cube(Area_Operate+temp1);//����Area_Operate �ٰ�temp1ת90
            }
            temp1 ^=0x30;
            for(i=0; i<4; i++)
            {
                if(i&0x01)Turn_Cube(Area_Operate+temp1);//����Area_Operate �ٰ�temp1ת90
                else Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//�����ٰ�temp1ת90
            }
            state|=(1<<temp);
        }
        else
        {
            //�Ҳ������ǻ��в���λ�õĻ򲻶�ɫ��������м�㣬�����ƶ����ײ�ȥ����ײ�����һ������λ�ã�
#ifdef DEBUG3
            printf ( "No find Area5!\n");
#endif

            for(i=0; i<4; i++)
            {
                if(state&(1<<i))continue;//��������ȷ
                if(*seamed_edge_p1[i]==(seamed_edge_Color[i]>>4) && *seamed_edge_p2[i]==(seamed_edge_Color[i]&0x0F))
                    state |=(1<<i);
                else//�����ⲻ�Ե�
                {
                    break;//����ת���ײ�  ����һ��ײ�Ľ���
                }
            }
            //ͳһ�� i+1��ĵ������佻��  i+1����ʱ��ת
            Area_Operate=(Color_D[i+1]>>3)&0x07;
            temp1=0x10;
            for(i=0; i<5; i++)
            {
                if(i&0x01) Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//�����ٰ�temp1ת90
                else Turn_Cube(Area_Operate+temp1);//����Area_Operate �ٰ�temp1ת90
            }
            temp1 ^=0x30;
            for(i=0; i<4; i++)
            {
                if(i&0x01)Turn_Cube(Area_Operate+temp1);//����Area_Operate �ٰ�temp1ת90
                else Turn_Cube(((Color_D[5]>>3)&0x07)+temp1);//�����ٰ�temp1ת90
            }

        }

#ifdef DEBUG3
        pause=1;
        printf ( "|| State  %X Pause",state);////////////////
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif

        LCD_Cube_Paint();////��ʾһ�� �����־λ
    }

    //����һ��У׼
    temp=Check(Area+0x20);
    if(temp)return temp;
    for(i=0; i<4; i++)
    {
        if(*seamed_edge_p1[i]==(seamed_edge_Color[i]>>4) && *seamed_edge_p2[i]==(seamed_edge_Color[i]&0x0F))
            state |=(1<<i);
    }
    if(state!=0x0F) return 0x31;
    printf ( "Mission 3 Finish\n");////////

    //���е��Ľ׶�
    //�ײ�ʮ�ּ� ֻ���������ɫ
    //�����������1 ���ⶼ���ڵ��� 2���������ڣ���Ե�2���� 3���ڵ�����   4�����޵���һ�����ڵ���ģ�
    Area_Real=(Color_D[5]>>3)&0x07;//����ʵ����
    do {
        for(i=0,n=0,state=0; i<4; i++)
        {
            //(i+4-(Color_D[5]>>6))&0x03  ---->�����ģ�0-3��תΪʵ�ʵ���ģ�0-3��
            if(Cube[Area_Real][Area_index[(i+4-(Color_D[5]>>6))&0x03]&0x0F]==Cube[Area_Real][4])
                n++;//�м����ڵ���
            else state|=(1<<i);
        }
        if(state!=0)//�в��ڵ����
        {

            if(n==0)//�ĸ�������  ���Ƚ���ת��Ϊ�������ڲ��ڵ�
            {
                //ת��1��  �ڶ��漰����
                temp1=0x20;
                i=(Color_D[1]>>3)&0x07;
                j=(Color_D[2]>>3)&0x07;
                Turn_Cube(i+temp1);//��һ��
                Turn_Cube(j+temp1);//2��
                Turn_Cube(Area_Real+temp1);//����
                temp1 ^=0x30;
                Turn_Cube(j+temp1);//2��
                Turn_Cube(Area_Real+temp1);//����
                Turn_Cube(i+temp1);//��һ��
            }
            else if(n==2)
            {

                if(state==0x05 || state==0x0A)//���ⲻͬɫ
                {
                    if(state==0x05)temp=1;
                    else temp=2;//��ʼ��ת����
                    temp1=0x20;

                    i=(Color_D[temp]>>3)&0x07;
                    j=(Color_D[temp+1]>>3)&0x07;
#ifdef DEBUG4
                    printf ( " 2 Areas not DUI State %X i:%X j:%X ",state,i,j);
                    pause=1;
                    while(pause && flag)delay_us(100);///////////////��ͣ
                    printf ( " >\n");
#endif
                    Turn_Cube(i+temp1);//��һ��
                    Turn_Cube(j+temp1);//2��
                    Turn_Cube(Area_Real+temp1);//����
                    temp1 ^=0x30;
                    Turn_Cube(j+temp1);//2��
                    Turn_Cube(Area_Real+temp1);//����
                    Turn_Cube(i+temp1);//��һ��
                }
                else//����������ɫ���Ե�
                {
                    //state bit0-3: bit0/3 Ϊ1ʱ Ӧת2���ڵ��棨����0-3�ĸ���ߣ�
                    //bit0/1=1:turn Area3  bit1/2 Ϊ1ʱ Ӧת0���ڵ��� bit2/3 =1 turn Area1
                    temp=state+(state<<4);
                    //Ѱ��temp���110������λ����λ��
                    for(i=0; i<4; i++)
                    {
                        if((temp&(0x07<<i))==(0x06<<i))
                            break;
                    }
                    if(i==4)return 0x41;//����1

#ifdef DEBUG4
                    printf ( "i= %X \n",i);
#endif

                    //0-Area1 1-Area4 2-Area3 3-Area2
                    temp=5-i;
                    if(temp==5)temp=1;//ת��Ϊ�������¿��Ĳ���
                    //�����桰����������תΪ�������Ա�׼��  ��Ϊ��ʼλ����������Ա�׼����ת���ģ���cube��ά���������
                    temp=((temp+1)&0x03)+1;//  DOC�ĵ�ͼ����ʾ���� ������ѡ����ת180
                    i=(Color_D[temp]>>3)&0x07;//��һ����
                    j=temp+1;
                    if(j==5)j=1;//ֻ��1-4�Ĳ���
                    j=(Color_D[j]>>3)&0x07;//��һ����+1��
                    temp1=0x20;//˳ʱ��ת

#ifdef DEBUG4
                    printf ( " 2 Areas not LIN State %X i:%X j:%X ",state,i,j);
                    pause=1;
                    while(pause && flag)delay_us(100);///////////////��ͣ
                    printf ( " >\n");
#endif

                    //��һ����˳ʱ�� ��˳ ��һ����+1��˳ʱ��  ����ʱ��  ��һ����+1����ʱ�� ��һ������ʱ��
                    Turn_Cube(i+temp1);
                    Turn_Cube(Area_Real+temp1);
                    Turn_Cube(j+temp1);

                    temp1 ^=0x30;
                    Turn_Cube(Area_Real+temp1);
                    Turn_Cube(j+temp1);
                    Turn_Cube(i+temp1);
                    //����Ĵ�����һ��Ҳ���ԣ������Ҳ�У����������Ҫ�������
                    /*Turn_Cube(i+temp1);//��һ��
                    Turn_Cube(j+temp1);//2��
                    Turn_Cube(Area_Real+temp1);//����
                    temp1 ^=0x30;
                    Turn_Cube(j+temp1);//2��
                    Turn_Cube(Area_Real+temp1);//����
                    Turn_Cube(i+temp1);//��һ��*/
                }
            }

            LCD_Cube_Paint();////��ʾһ�� �����־λ
        }
#ifdef DEBUG4
        pause=1;
        printf ( "|| State  %X n=%XPause",state,n);////////////////
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif

    } while(state!=0);

    //if(state!=0x0F) return 0x31;//��ʱ��У��
    printf ( "Mission 4 Finish\n");////////

    //�ײ���ɫ����
    //����ײ��Ľǵ�7�����

    //Area_Real�����ǵײ���� ��Ҫ�ı���

    //�Ƚ��Ľ� ��������ľ���λ�ô��뵽����
    //*seamed_edge_p1[4],*seamed_edge_p2[4],ǰ��Ϊ��࣬����Ϊ�Ҳ�  �Ա�׼���λ�õ�0-3
    //��ȡ�ײ��Ľǿ������ɫ i=1 2��2(L) 1��3(R) i=2 Area1_2(L) Area4_3(R) i=3 Area4_2(L) Area3_3(R) i=4 Area3_2(L) Area2_3(R)
    for(i=1; i<5; i++)
    {
        m=i<3?3-i:7-i;
        n=(i&0x01)?i:6-i;
        seamed_edge_p1[i-1]=&Cube[(Color_D[m]>>3)&0x07][Area_index[(6-(Color_D[m]>>6))&0x03]>>4];// ˳ʱ��2
        seamed_edge_p2[i-1]=&Cube[(Color_D[n]>>3)&0x07][Area_index[3-(Color_D[n]>>6)]>>4]; //˳ʱ��3
    }


    do {
        //ɨ������Ľ���ɫ ��0 - 2 - 8 - 6��0-3��Ա�׼λ�ã�
        for(i=0,n=0,state=0; i<4; i++)
        {
            temp=Area_index[(i+4-(Color_D[5]>>6))&0x03]>>4;
            if(Cube[Area_Real][temp]==Cube[Area_Real][4])
                n++;//�м����ڵ���
            else
            {
                state|=(0x10<<i);
                //���ҳ���ɫ���ڴ˽���໹���Ҳࣨ���Ϊ0 �Ҳ�Ϊ1 �ֱ�������bit 0-3λ��
                if(*seamed_edge_p2[i]==Cube[Area_Real][4]) state|=(0x01<<i);
                else if(*seamed_edge_p1[i]!=Cube[Area_Real][4])//�����Ҳ��Ҳ��������  ˵��������
                {
                    return 0x51;//���岽����1
                }
            }
        }//ɨ�����
        if(state==0)break;//�����������ٴ���

        //�� ֻ�� 0 1 2 �����������

        if(n==0)//�������
        {
            temp=state&0x0F;
            temp=temp+(temp<<4);
            //Ѱ��temp���0101��0011������λ����λ��
            for(i=0,Area_Operate=0; i<4; i++)
            {
                if((temp&(0x0F<<i))==(0x05<<i))// i=0-->i=4 ������ʱ����ת��i��  scene 3
                {
                    Area_Operate=i+0x30;
                    break;
                }
                else if((temp&(0x0F<<i))==(0x03<<i))// i=0-->i=4 ������ʱ����ת��i��  scene 6
                {
                    Area_Operate=i+0x60;
                    break;
                }
            }
            if(i==0)i=4;
            else if(i==4)return 0x53;//����������������


            //������ת
            //Turn_Cube(Area_Operate+0x10);//����Area_Operate �ٰ���ʱ��ת90
            //Turn_Cube(Area_Real+0x30);//������ת180
            //Turn_Cube(Area_Operate+0x20);//����Area_Operate �ٰ�˳ʱ��ת90
            //Turn_Cube(Area_Real+0x20);//������ת˳ʱ��ת90
            //Turn_Cube(Area_Operate+0x10);//����Area_Operate �ٰ���ʱ��ת90
            //Turn_Cube(Area_Real+0x20);//������ת˳ʱ��ת90
            //Turn_Cube(Area_Operate+0x20);//����Area_Operate �ٰ�˳ʱ��ת90
        }
        else if(n==1)//�������
        {
            //�ҵ�state����λΪ0����λ
            for(i=0; i<4; i++)
            {
                if((state&(0x10<<i))==0)break;
            }
            if(i==0)i=4;
            else if(i==4)return 0x54;//����������������

            //if((i&0x01)==0)i=6-i;// 2 4�滥��
            //Area_Operate=(Color_D[i]>>3)&0x07;//��Ҫ��������  ע����� ��2��4�������濴���� 4��2��

        }
        else if(n==2)//3�����
        {
            //Ѱ��state�����λΪ1�Ҷ�Ӧ����λ���Ǹ�Ϊ0
            temp=state | ((~(state>>4))&0x0F);
            for(i=0,Area_Operate=0; i<4; i++)
            {
                if((temp&(0x11<<i))==(0x10<<i))break;
            }
            if(i==0)i=4;
            else if(i==4)return 0x55;//����������������

            //if((i&0x01)==0)i=6-i;// 2 4�滥��
        }
        else return 0x52;//���岽����2  �����Ƿ������

        if((i&0x01)==0)i=6-i;// 2 4�滥��
        //i=((i+3-(Color_D[5]>>6))&0x03)+1;//ע���ʱ�൱�ڵײ㽫��ֵ��ʱ����ת n*90  �˴�����Ҫ��  ��ʼѰ��ʱ�ѽ��仯Ϊ��׼�����
        Area_Operate=(Color_D[i]>>3)&0x07;//��Ҫ�������� ע����� ��2��4�������濴���� 4��2��
#ifdef DEBUG5
        pause=1;
        printf ( "|| n=%X A=%X state=%X Pause",n,Area_Operate,state);////////////////
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif
        Turn_Cube(Area_Operate+0x10);//����Area_Operate �ٰ���ʱ��ת90
        Turn_Cube(Area_Real+0x30);//������ת180
        Turn_Cube(Area_Operate+0x20);//����Area_Operate �ٰ�˳ʱ��ת90
        Turn_Cube(Area_Real+0x20);//������ת˳ʱ��ת90
        Turn_Cube(Area_Operate+0x10);//����Area_Operate �ٰ���ʱ��ת90
        Turn_Cube(Area_Real+0x20);//������ת˳ʱ��ת90
        Turn_Cube(Area_Operate+0x20);//����Area_Operate �ٰ�˳ʱ��ת90
#ifdef DEBUG5
        pause=1;
        printf ( "|| State  %X Pause",state);////////////////
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif
        LCD_Cube_Paint();////��ʾһ�� �����־λ
    } while(state!=0);//���Ľǵ��涼�ǵ���ɫ  state����λȫΪ0

    printf ( "Mission 5 Finish\n");////////

    //��ԭ�ײ��λ��
    //��������Mission 5��*seamed_edge_p1[4],*seamed_edge_p2[4],ǰ��Ϊ��࣬����Ϊ�Ҳ�  �Ա�׼���λ�õ�0-3
    //��Ȼ��һ���ǿ�λ���ǶԵģ�������˵���ײ���Ҫת
    //�Ľǿ������ɫ i=1 2��2(L) 1��3(R) i=2 Area1_2(L) Area4_3(R) i=3 Area4_2(L) Area3_3(R) i=4 Area3_2(L) Area2_3(R)


    //��¼�Ĳ�����ɫ
    seamed_edge_Color[0]=Cube[(Color_D[2]>>3)&0x07][4];
    seamed_edge_Color[1]=Cube[(Color_D[1]>>3)&0x07][4];
    seamed_edge_Color[2]=Cube[(Color_D[4]>>3)&0x07][4];
    seamed_edge_Color[3]=Cube[(Color_D[3]>>3)&0x07][4];


    do {
        Area_Operate=0;
        for(i=0,location=0,state=0,temp1=0; i<4; i++) //��������ת����Ϣ���뵽location
        {
            location >>=2;//bit1-0��¼�ǿ�1�Ƿ���Ҫ��ת��0���� 1��ʱת90 2˳ʱ90 3ת180�㣩 ��λ��������
            if(i==3)j=0;
            else j=i+1;
            if(*seamed_edge_p1[i]!=seamed_edge_Color[i] || *seamed_edge_p2[i] !=seamed_edge_Color[j])//λ�ò���
            {
                state++;
                for(m=0; m<4; m++) //Ѱ�Ҵ˽������ĸ��ط� ����Ҫת���ٶ�
                {
                    if(m==3)n=0;
                    else n=m+1;
                    if(*seamed_edge_p1[i]==seamed_edge_Color[m] && *seamed_edge_p2[i] ==seamed_edge_Color[n])//���ĸ���
                        break;
                }
                if(m==4)return 0x61;//����1 �Ҳ���
                //m>i ������Ҫ˳ʱ��ת  ��֮����ʱ��
                temp=m>i?m-i:(i-m+0x80);//0x80����˿���Ҫ ��ʱ�� ת 90*��temp&0x0F���Ȳ��ܹ�λ
                if((temp&0x03)==2) {
                    location|=0xC0;
                    temp1++;
                }
                else
                {
                    if(temp&0x80)location |=0x40;//��ʱ��ת
                    else location |=0x80;//˳ʱ��ת
                    if((temp&0x03)==3)location ^=0xC0;//ת270�ȼ�Ϊ����ת90
                }

            }
            else Area_Operate=i;//for state=3
        }
#ifdef DEBUG6
        pause=1;
        printf ( "|| Loca %X state=%X Area_O=%X temp1 %X",location,state,Area_Operate,temp1);
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif
        if(state!=0)
        {
            if(state==3)//���������������������
            {
                //�ԵĽǿ�����λ����Ҫ������Ĺ�ϵ��0-3  1-2  2-1 3-4
                Area_Operate=3-Area_Operate;
                if(Area_Operate==0)Area_Operate=4;
                //�ж�������˳ʱ������ʱ��ת
                for(i=0,j=location; i<4; i++,j>>=2)
                {
                    if((j&0x03)==0x02)//����˳ʱ���Ȧ
                    {   Area_Operate+=0x21;
                        if(Area_Operate==0x25)Area_Operate=0x21;
                        break;
                    }
                    else if((j&0x03)==0x01)//������ʱ���Ȧ
                    {
                        Area_Operate+=0x10;
                        break;
                    }
                }
                if(i!=4)Area_Operate=0x80+Area_Operate;//������
            }
            else if(state==4)
            {
                //���ĸ��ǲ��Ե������2��(��2��ֱ�ӿ��Ը�ԭ��)�������以��(�Խǽ����Ļ� �����ڴ�ֱ�����)��8���ν���-> ת90�ȱ�3����ͬ����� (��3��������˳��ʱ�� ��ʱת90�ȼ���ԭ)
                if(temp1==4)//��ת180����
                    Turn_Cube(Area_Real+0x30);//������ת180
                else if(temp1==2)//8����
                {
                    Turn_Cube(Area_Real+0x20);//������ת˳ʱ��ת90
                }
                else//û��Ҫת180���      ������˳��ʱ����ˮƽ����ֱ�����以��
                {
                    if(location==0xAA)//������˳��ʱ��
                    {
                        Turn_Cube(Area_Real+0x20);   //������ת˳ʱ��ת90
                    }
                    else if(location==0x55)//������˳��ʱ��
                    {
                        Turn_Cube(Area_Real+0x10);//������ת��ʱ��ת90
                    }
                    else //�����ѡһ������šһ�����߽����Ĺ�ʽ   �����以��
                    {
                        //2+0x30 1+0x30 2+0x20 3+0x20 2+0x10 1+0x30 2+0x20 3+0x10 2+0x20��1  3�Ǵӵ������Ͽ��� ��ʵ����Ա�׼�治ͬ 2 - 4�������ɣ�
                        //�ҵ�Ҫ����������ͬһ�� ��0<-->1  2<-->3  �ҵ�01���Ǹ�����
                        Turn_Cube(Area_Real+0x10);//5'   ����Ӵ�
                        for(i=0; i<8; i+=2)
                        {
                            if((location&(0x03<<i))==(0x02<<i))
                                break;
                        }
#ifdef DEBUG6
                        printf ( "! i=%X Loca=%X\n",i,location);

#endif
                        //�ԵĽǿ�����λ����Ҫ������Ĺ�ϵ��0-1  1-4  2-3 3-2
                        Area_Operate=5-(i>>1);
                        if(Area_Operate==5)Area_Operate=1;
                        Area_Operate+=0xB0;//����
                    }
                }
#ifdef DEBUG6
                printf ( "state=4; Area_Operate=%X\n",Area_Operate);

#endif

            }
            else //��������ֻ��2�����������
            {
                // 0-3 �ĸ���λ�� 01�� 23�����(����ת90�ȱ�1������ȷ��) 02�� 13�����(��ʱ������ʽת��Ҫת����90 ����Ū��4����ͬ��״̬)
                Turn_Cube(Area_Real+0x20);//������ת˳ʱ��ת90
            }

            if(Area_Operate&0x80)//����Ҫ����
            {
#ifdef DEBUG6
                printf ( " Area_Operate=%X  lo=%X\n",Area_Operate,location);

#endif
                i=Area_Operate&0x70;//�ж����������ַ�ʽ
                Area_Operate&=0x0F;
                temp= Area_Operate;
                m=(Area_Operate+1);//��1��
                if(m>4)m=1;
                n=Area_Operate-1;//��һ��
                if(n==0)n=4;
                Area_Operate=(Color_D[temp]>>3)&0x07; //���ʵ�ʲ�����

                m=(Color_D[m]>>3)&0x07;//���ʵ�ʲ�����

                n=(Color_D[n]>>3)&0x07;//���ʵ�ʲ�����

#ifdef DEBUG6
                pause=1;
                printf ( "|| n= %X Ar=%X m=%X",n,Area_Operate,m);
                while(pause && flag)delay_us(100);///////////////��ͣ
                printf ( " >\n");
#endif
                //��������ת
                if(i==0x10)//����ʱ���Ȧ
                {   Turn_Cube(Area_Operate+0x30);//��ǰ����ת180
                    Turn_Cube(m+0x30);//+1����180
                    Turn_Cube(Area_Operate+0x20);//��ǰ����ת˳ʱ��ת90
                    Turn_Cube(n+0x20);//-1����ת˳ʱ��ת90
                    Turn_Cube(Area_Operate+0x10);//��ǰ����ת��ʱ��ת90
                    Turn_Cube(m+0x30);//+1����ת180
                    Turn_Cube(Area_Operate+0x20);//��ǰ����ת˳ʱ��ת90
                    Turn_Cube(n+0x10);//-1����ת��ʱ��ת90
                    Turn_Cube(Area_Operate+0x20);//��ǰ����ת˳ʱ��ת90

                }
                else if(i==0x20)//��˳ʱ���Ȧ
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
                else if(i==0x30) //�����以�� ����֮��
                {
#ifdef DEBUG6
                    pause=1;
                    printf ( "|| i=0x30 Ar=%X m=%X",Area_Operate,m);
                    while(pause && flag)delay_us(100);///////////////��ͣ
                    printf ( " >\n");
#endif
                    //Turn_Cube(Area_Real+0x10);//5'   ����Ӵ�
                    //����Ϊ���������棨m��Area_Operate������߽��������������������γɵĶԽǽ���
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
                    while(pause && flag)delay_us(100);///////////////��ͣ
                    printf ( " >\n");
#endif
                }
            }
            LCD_Cube_Paint();////��ʾһ�� �����־λ
        }
#ifdef DEBUG6
        pause=1;
        printf ( "State %X",state);
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif
    } while(state!=0);//}while(state!=0);

    printf ( "Mission 6 Finish\n");////////

    ////��ԭ�ײ����λ��
    // 4��߶����ԡ�3�����ԣ��������ԵĻ�Ҫת���ˣ�˳����ʱ��ת90�ȼ��� ��Ϊ�ĸ����Ե�ƽ�н��� ����3�����Եģ�

    //��¼������߲�����ɫ
    //��¼�Ĳ�����ɫ
    seamed_edge_Color[0]=Cube[(Color_D[1]>>3)&0x07][4];
    seamed_edge_Color[1]=Cube[(Color_D[4]>>3)&0x07][4];
    seamed_edge_Color[2]=Cube[(Color_D[3]>>3)&0x07][4];
    seamed_edge_Color[3]=Cube[(Color_D[2]>>3)&0x07][4];
    //�Ƚ���Ϣ׼����  ��������1-4��ߵ�ַ����seamed_edge_p2
    for(i=1; i<5; i++)
    {
        n=(i&0x01)?i:6-i;
        seamed_edge_p2[i-1]=&Cube[(Color_D[n]>>3)&0x07][Area_index[(6-(Color_D[n]>>6))&0x03]&0x0F];//˳ʱ��2
    }

    do
    {
        location=0;//location bit1-0��ʾ0λ�õ������Ҫ�ƶ����ٶ� n*90 ����һ��

        //ע��������������λ������ת��  ������Color_D����λ
        //(i+(Color_D[5]>>6))&0x03---->ʵ�ʵ����i��0-3��תΪ�����ģ�0-3��  �����㷨������Ҫ������

        for(i=0,temp=0,state=0,j=0xFF; i<4; i++)
        {
            if(seamed_edge_Color[i]!=*seamed_edge_p2[i])
            {   state|=(0x01<<i);
                temp++;
                //������Ӧ��ʲô�ط�
                for(m=0; m<4; m++)
                {
                    if(seamed_edge_Color[m]==*seamed_edge_p2[i])break;
                }
                if(m==4)return 0x71+i;

                m=m>i?m-i:4-i+m;//  �˴���4-��i-m��
                location+=(m<<(i<<1));
            }
            else j=i;//for temp=3  ��¼�Ե������ĸ���

        }


#ifdef DEBUG7
        /*printf ( "DI:%X Color0:%X--%X\n",Area_Real,seamed_edge_Color[0],*seamed_edge_p2[0]);
        printf ( "Color1:%X--%X \n",seamed_edge_Color[1],*seamed_edge_p2[1]);
        printf ( "Color2:%X--%X \n",seamed_edge_Color[2],*seamed_edge_p2[2]);
        printf ( "Color3:%X--%X \n",seamed_edge_Color[3],*seamed_edge_p2[3]);*/

        pause=1;
        printf ( "|| Start:state:%X Lo:%X temp:%X j %X",state,location,temp,j);
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif

        //�Լ�������д���
        if(temp!=0)
        {
            if(temp==4)
            {
                if(location==0xAA)//ʮ�ֽ�����  M'2 U' M'2 U2 M'2 U' M'2
                {
                    Area_Operate=0x02;//�������濪ʼ����
                    //m= Area_Operate+2;
                    //if(m>4)m &=0x03;//Area_Operate����
                    m=(Color_D[4]>>3)&0x07;
                    Area_Operate=(Color_D[2]>>3)&0x07;

                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);
                    Turn_Cube(Area+0x10);//0��'
                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);
                    Turn_Cube(Area_Real+0x30);//5_2
                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);
                    Turn_Cube(Area+0x10);//0'
                    Turn_Cube(Area_Operate+0x30);//M'2
                    Turn_Cube(m+0x30);

                }
                else if((location&0x0F)==(location>>4))//ƽ�еĽ���  Ѱ��1101 �������� (U R' U')(R U' R)(U R U')(R' U R U)(R2 U')(R' U)
                {

                    for(i=0; i<5; i+=2)
                    {
                        if((location&(0x0F<<i))==(0x0D<<i))
                        {
                            break;
                        }
                    }
                    if(i==6)return 0x77;//�Ҳ�����
                    i>>=1; //i=0 - 2
                    Area_Operate=i+1;////0����1��
                    Area_Operate=(Color_D[Area_Operate]>>3)&0x07;//תΪʵ����

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
                else return 0x76;//���������ϵ����
            }
            else if(temp==3)
            {
                Area_Operate=4-j;//��Ӧ����˳ʱ��+1���� 0->4  1->3 2->2 3->1
                Area_Operate=(Color_D[Area_Operate]>>3)&0x07;//תΪʵ����
                //�ж�������˳ʱ������ʱ��ת
                for(i=0,j=location,temp1=0; i<4; i++,j>>=2)
                {
                    if((j&0x03)==0x01)//����˳ʱ���Ȧ   (R2 U)(R U R' U')(R' U')(R' U R')
                    {
                        temp1=0x20;
                        break;
                    }
                    else if((j&0x03)==0x03)//������ʱ���Ȧ  (R U' R) (U R U R) (U' R' U��R2)
                    {
                        temp1=0x10;
                        break;
                    }
                }
                if(temp1==0)return 0x78;////

                if(temp1==0x20)//	//���˳ʱ����
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
                else //�����ʱ����
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
            else  //ֻʣ2�����Ե�   ֻ��˵����װ����
            {
                return 0x75;// �˴��ǲ��ɴﵽ��
                //Turn_Cube(Area_Real+0x20);//������ת˳ʱ��ת90
            }

            //��ת����
            //m= Area_Operate+2;
            //if(m>4)m &=0x03;//Area_Operate����
            //m=(Color_D[m]>>3)&0x07;


#ifdef DEBUG7
            pause=1;
            printf ( "|| temp1 %X  OP %X Lo %X",temp1,Area_Operate,location);
            while(pause && flag)delay_us(100);///////////////��ͣ
            printf ( " >\n");
#endif

            LCD_Cube_Paint();////��ʾһ�� �����־λ
        }

#ifdef DEBUG7
        pause=1;
        printf ("|| State %X temp %X ",state,temp);
        while(pause && flag)delay_us(100);///////////////��ͣ
        printf ( " >\n");
#endif
    } while(state!=0);

    printf ( "|| End Pause\n");//��ʾ��ͣ  ���͡�A���ַ�����
    pause=1;////////////////
    while(pause && flag)
        delay_us(100);///////////////��ͣ
    printf ( " >\n");
    //USART_RX_STA=0;
    flag=0;
    return 0;

}

