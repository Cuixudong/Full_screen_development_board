#include "calendar.h"
#include "stdio.h"
#include "settings.h"
#include "mpu6050.h"
#include "ds18b20.h"
#include "24cxx.h"
#include "math.h"
#include "rtc.h"

#include "digital_led.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP-日历 代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/7/20
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//*******************************************************************************
//修改信息
//无
//////////////////////////////////////////////////////////////////////////////////

_alarm_obj alarm;		//闹钟结构体
_calendar_obj calendar;	//日历结构体

static u16 TIME_TOPY;		//	120
static u16 OTHER_TOPY;		//	200

u8*const calendar_week_table[GUI_LANGUAGE_NUM][7]=
{
    {"星期天","星期一","星期二","星期三","星期四","星期五","星期六"},
    {"星期天","星期一","星期二","星期三","星期四","星期五","星期六"},
    {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"},
};
//闹钟标题
u8*const calendar_alarm_caption_table[GUI_LANGUAGE_NUM]=
{
    "闹钟","鬧鐘","ALARM",
};
//再响按钮
u8*const calendar_alarm_realarm_table[GUI_LANGUAGE_NUM]=
{
    "再响","再響","REALARM",
};
u8*const calendar_loading_str[GUI_LANGUAGE_NUM][3]=
{
    {
        "正在加载,请稍候...",
        "未检测到DS18B20!",
        "启用内部温度传感器...",
    },
    {
        "正在加载,请稍候...",
        "未检测到DS18B20!",
        "启用内部温度传感器...",
    },
    {
        "Loading...",
        "DS18B20 Check Failed!",
        "Start Internal Sensor...",
    },
};

void Draw_Line(unsigned short xs,unsigned short ys,unsigned char xe,unsigned short ye,unsigned short color)
{
    POINT_COLOR = color;
    LCD_DrawLine(xs,ys,xe,ye);
}
void Digital_LED_Test(void)
{
    int stp;
    u8 *pname=0;
    pname=gui_memin_malloc(40);

    LCD_Clear(BLACK);
    draw_str.IF_DrawLine = (void *)LCD_DrawLine;
    DIGITAL_COLOR_BACK = BLACK;
    DIGITAL_COLOR_FRONT = RED;
    DIGITAL_COLOR_FRONT_EMP = WHITE;
    draw_str.Digital_Draw_Line = (void *)Draw_Line;
    while(1)
    {
        for(stp=0; stp<16; stp++)
        {
            //Draw_Digital_num(20,20,20,120,300,stp,0);

            Digital_Draw_num(20,0,10,120,180,stp++%16,0x00);
            Digital_Draw_num(20,200,15,120,180,stp++%16,0x20);
            //Digital_Draw_num(20,400,10,120,180,stp%16,0x40);

            Digital_Draw_num(20,400,20,120,180,stp++%16,0x90);
            Digital_Draw_num(20,600,25,120,180,stp++%16,0x60);

            Digital_Draw_num(260,0,10,120,180,stp++%16,0x80);
            Digital_Draw_num(260,200,10,120,180,stp++%16,0xA0);
            //Digital_Draw_num(260,400,10,120,180,stp%16,0xC0);

            Digital_Draw_num(260,400,10,120,180,stp++%16,0xF0);
            Digital_Draw_num(260,600,10,120,180,stp++%16,0xE0);
            delay_ms(1200);

//			sprintf(pname,"0:\\SCREENCUT\\PIC%02d.bmp",stp);
//			bmp_encode(pname,0,0,lcddev.width,lcddev.height,1);
            LCD_Clear(BLACK);
            stp -= 8;
        }
        for(stp=0; stp<16; stp++)
        {
            Digital_Draw_num(20,20,75,440,760,stp%16,0x90);
//			sprintf(pname,"0:\\SCREENCUT\\PIC_BIG%02d.bmp",stp);
//			bmp_encode(pname,0,0,lcddev.width,lcddev.height,1);
//			delay_ms(1200);delay_ms(1200);
            delay_ms(1200);
            LCD_Clear(BLACK);
        }
        break;
    }
    gui_memin_free(pname);
}

//重新初始化闹钟
//alarmx:闹钟结构体
//calendarx:日历结构体
void calendar_alarm_init(_alarm_obj *alarmx,_calendar_obj *calendarx)
{
    u8 temp;
    RTC_Get();
    if(calendarx->week==7)temp=1<<0;
    else temp=1<<calendarx->week;
    if(alarmx->weekmask&temp)		//需要闹铃
    {
        printf("alarm:%d-%d-%d %d:%d\r\n",calendarx->w_year,calendarx->w_month,calendarx->w_date,alarmx->hour,alarmx->min);
        RTC_Alarm_Set(calendarx->w_year,calendarx->w_month,calendarx->w_date,alarmx->hour,alarmx->min,0);//设置闹铃时间
    }
}
//闹钟响闹铃
//type:闹铃类型
//0,滴.
//1,滴.滴.
//2,滴.滴.滴
//4,滴.滴.滴.滴
void calendar_alarm_ring(u8 type)
{
    u8 i;
    for(i=0; i<(type+1); i++)
    {
        BEEP=1;
        delay_ms(50);
        BEEP=0;
        delay_ms(70);
    }
}
//根据当前的日期,更新日历表.
void calendar_date_refresh(void)
{
    u8 weekn;   //周寄存
    u16 offx=(lcddev.width-240)/2;
    //显示阳历年月日
    POINT_COLOR=BRED;
    BACK_COLOR=BLACK;
    LCD_ShowxNum(offx+5,OTHER_TOPY+9,(calendar.w_year/100)%100,2,16,0);//显示年  20/19
    LCD_ShowxNum(offx+21,OTHER_TOPY+9,calendar.w_year%100,2,16,0);     //显示年
    LCD_ShowString(offx+37,OTHER_TOPY+9,lcddev.width,lcddev.height,16,"-"); //"-"
    LCD_ShowxNum(offx+45,OTHER_TOPY+9,calendar.w_month,2,16,0X80);     //显示月
    LCD_ShowString(offx+61,OTHER_TOPY+9,lcddev.width,lcddev.height,16,"-"); //"-"
    LCD_ShowxNum(offx+69,OTHER_TOPY+9,calendar.w_date,2,16,0X80);      //显示日
    //显示周几?
    POINT_COLOR=RED;
    weekn=calendar.week;
    Show_Str(5+offx,OTHER_TOPY+35,lcddev.width,lcddev.height,(u8 *)calendar_week_table[gui_phy.language][weekn],16,0); //显示周几?

}
//闹钟数据保存在:SYSTEM_PARA_SAVE_BASE+sizeof(_system_setings)+sizeof(_vs10xx_obj)
//读取日历闹钟信息
//alarm:闹钟信息
void calendar_read_para(_alarm_obj * alarm)
{
    AT24CXX_Read(SYSTEM_PARA_SAVE_BASE+sizeof(_system_setings)+sizeof(_vs10xx_obj),(u8*)alarm,sizeof(_alarm_obj));
}
//写入日历闹钟信息
//alarm:闹钟信息
void calendar_save_para(_alarm_obj * alarm)
{
    OS_CPU_SR cpu_sr=0;
    alarm->ringsta&=0X7F;	//清空最高位
    OS_ENTER_CRITICAL();	//进入临界区(无法被中断打断)
    AT24CXX_Write(SYSTEM_PARA_SAVE_BASE+sizeof(_system_setings)+sizeof(_vs10xx_obj),(u8*)alarm,sizeof(_alarm_obj));
    OS_EXIT_CRITICAL();		//退出临界区(可以被中断打断)
}

//闹铃处理(尺寸:200*160)
//x,y:坐标
//返回值,处理结果
u8 calendar_alarm_msg(u16 x,u16 y)
{
    u8 rval=0;
    vu8 res=0;
    u32 abr;
    FIL* falarm=0;
    u16 tempcolor=gui_phy.back_color;//备份之前的背景色
    _window_obj* twin=0;			//窗体
    _btn_obj * rbtn=0;				//取消按钮
    _btn_obj * okbtn=0;				//确定按钮
    u8 freadflag=0;
    OSTaskSuspend(6); //挂起主任务
    twin=window_creat(x,y,200,160,0,1|1<<5|1<<6,16);//创建窗口,读取背景色
    okbtn=btn_creat(x+20,y+120,70,30,0,0x02);		//创建按钮
    rbtn=btn_creat(x+20+70+20,y+120,70,30,0,0x02);	//创建按钮
    falarm=(FIL *)gui_memin_malloc(sizeof(FIL));	//开辟FIL字节的内存区域
    if(twin==NULL||rbtn==NULL||okbtn==NULL||falarm==NULL)rval=1;
    else
    {
        //窗口的名字和背景色
        twin->caption=(u8*)calendar_alarm_caption_table[gui_phy.language];
        twin->windowbkc=APP_WIN_BACK_COLOR;
        //返回按钮的颜色
        rbtn->bkctbl[0]=0X8452;		//边框颜色
        rbtn->bkctbl[1]=0XAD97;		//第一行的颜色
        rbtn->bkctbl[2]=0XAD97;		//上半部分颜色
        rbtn->bkctbl[3]=0X8452;		//下半部分颜色
        okbtn->bkctbl[0]=0X8452;	//边框颜色
        okbtn->bkctbl[1]=0XAD97;	//第一行的颜色
        okbtn->bkctbl[2]=0XAD97;	//上半部分颜色
        okbtn->bkctbl[3]=0X8452;	//下半部分颜色

        rbtn->caption=(u8*)GUI_CANCEL_CAPTION_TBL[gui_phy.language];		//取消按钮
        okbtn->caption=(u8*)calendar_alarm_realarm_table[gui_phy.language];	//再响按钮

        if(asc2_s6030==0)//之前是没有字库的?
        {
            freadflag=1;	//标记读取了字库
            res=f_open(falarm,(const TCHAR*)APP_ASCII_S6030,FA_READ);//打开文件
            if(res==0)
            {
                asc2_s6030=(u8*)gui_memex_malloc(falarm->fsize);	//为大字体开辟缓存地址
                if(asc2_s6030==0)rval=1;
                else
                {
                    res=f_read(falarm,asc2_s6030,falarm->fsize,(UINT*)&abr);	//一次读取整个文件
                }
                f_close(falarm);
            }
        }
        window_draw(twin);						//画出窗体
        btn_draw(rbtn);							//画按钮
        btn_draw(okbtn);						//画按钮
        if(res)rval=res;
        else 									//显示闹铃时间
        {
            gui_phy.back_color=APP_WIN_BACK_COLOR;
            gui_show_num(x+15,y+32+14,2,BLUE,60,alarm.hour,0X80);	//显示时
            gui_show_ptchar(x+15+60,y+32+14,lcddev.width,lcddev.height,0,BLUE,60,':',0);	//":"
            gui_show_num(x+15+90,y+32+14,2,BLUE,60,alarm.min,0X80);	//显示分
        }
        system_task_return=0;
        while(rval==0)
        {
            tp_dev.scan(0);
            in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//得到按键键值
            delay_ms(5);
            if(system_task_return)
            {
                rval=1;			//取消
                break;			//TPAD返回
            }
            res=btn_check(rbtn,&in_obj);			//取消按钮检测
            if(res&&((rbtn->sta&0X80)==0))			//有有效操作
            {
                rval=1;
                break;//退出
            }
            res=btn_check(okbtn,&in_obj);			//再响按钮检测
            if(res&&((okbtn->sta&0X80)==0))			//有有效操作
            {
                rval=0XFF;//
                break;//退出
            }
        }
    }
    alarm.ringsta&=~(1<<7);	//取消闹铃
    if(rval==0XFF)			//稍后再响
    {
        alarm.min+=5; 		//推迟5分钟
        if(alarm.min>59)
        {
            alarm.min=alarm.min%60;
            alarm.hour++;
            if(alarm.hour>23)alarm.hour=0;
        }
        calendar_alarm_init((_alarm_obj*)&alarm,&calendar);//重新初始化闹钟
    }
    window_delete(twin);
    btn_delete(rbtn);
    btn_delete(okbtn);
    gui_memin_free(falarm);
    if(freadflag)//读取了字库?释放
    {
        gui_memex_free(asc2_s6030);
        asc2_s6030=0;
    }
    system_task_return=0;	//取消TPAD
    gui_phy.back_color=tempcolor;//恢复背景色
    OSTaskResume(6); 		//恢复主任务
    return rval;
}
//画圆形指针表盘
//x,y:坐标中心点
//size:表盘大小(直径)
//d:表盘分割,秒钟的高度
void calendar_circle_clock_drawpanel(u16 x,u16 y,u16 size,u16 d)
{
    u16 r=size/2;//得到半径
    u16 sx=x-r;
    u16 sy=y-r;
    u16 px0,px1;
    u16 py0,py1;
    u16 i;
    gui_fill_circle(x,y,r,WHITE);		//画外圈
    gui_fill_circle(x,y,r-4,BLACK);		//画内圈
    for(i=0; i<60; i++) //画秒钟格
    {
        px0=sx+r+(r-4)*sin((app_pi/30)*i);
        py0=sy+r-(r-4)*cos((app_pi/30)*i);
        px1=sx+r+(r-d)*sin((app_pi/30)*i);
        py1=sy+r-(r-d)*cos((app_pi/30)*i);
        gui_draw_bline1(px0,py0,px1,py1,0,WHITE);
    }
    for(i=0; i<12; i++) //画小时格
    {
        px0=sx+r+(r-5)*sin((app_pi/6)*i);
        py0=sy+r-(r-5)*cos((app_pi/6)*i);
        px1=sx+r+(r-d)*sin((app_pi/6)*i);
        py1=sy+r-(r-d)*cos((app_pi/6)*i);
        gui_draw_bline1(px0,py0,px1,py1,2,YELLOW);
    }
    for(i=0; i<4; i++) //画3小时格
    {
        px0=sx+r+(r-5)*sin((app_pi/2)*i);
        py0=sy+r-(r-5)*cos((app_pi/2)*i);
        px1=sx+r+(r-d-3)*sin((app_pi/2)*i);
        py1=sy+r-(r-d-3)*cos((app_pi/2)*i);
        gui_draw_bline1(px0,py0,px1,py1,2,YELLOW);
    }
    gui_fill_circle(x,y,d/2,WHITE);		//画中心圈
}
//显示时间
//x,y:坐标中心点
//size:表盘大小(直径)
//d:表盘分割,秒钟的高度
//hour:时钟
//min:分钟
//sec:秒钟
void calendar_circle_clock_showtime(u16 x,u16 y,u16 size,u16 d,u8 hour,u8 min,u8 sec)
{
    static u8 oldhour=0;	//最近一次进入该函数的时分秒信息
    static u8 oldmin=0;
    static u8 oldsec=0;
    float temp;
    u16 r=size/2;//得到半径
    u16 sx=x-r;
    u16 sy=y-r;
    u16 px0,px1;
    u16 py0,py1;
    u8 r1;
    if(hour>11)hour-=12;
///////////////////////////////////////////////
    //清除小时
    r1=d/2+4;
    //清除上一次的数据
    temp=(float)oldmin/60;
    temp+=oldhour;
    px0=sx+r+(r-3*d-7)*sin((app_pi/6)*temp);
    py0=sy+r-(r-3*d-7)*cos((app_pi/6)*temp);
    px1=sx+r+r1*sin((app_pi/6)*temp);
    py1=sy+r-r1*cos((app_pi/6)*temp);
    gui_draw_bline1(px0,py0,px1,py1,2,BLACK);
    //清除分钟
    r1=d/2+3;
    temp=(float)oldsec/60;
    temp+=oldmin;
    //清除上一次的数据
    px0=sx+r+(r-2*d-7)*sin((app_pi/30)*temp);
    py0=sy+r-(r-2*d-7)*cos((app_pi/30)*temp);
    px1=sx+r+r1*sin((app_pi/30)*temp);
    py1=sy+r-r1*cos((app_pi/30)*temp);
    gui_draw_bline1(px0,py0,px1,py1,1,BLACK);
    //清除秒钟
    r1=d/2+3;
    //清除上一次的数据
    px0=sx+r+(r-d-7)*sin((app_pi/30)*oldsec);
    py0=sy+r-(r-d-7)*cos((app_pi/30)*oldsec);
    px1=sx+r+r1*sin((app_pi/30)*oldsec);
    py1=sy+r-r1*cos((app_pi/30)*oldsec);
    gui_draw_bline1(px0,py0,px1,py1,0,BLACK);
///////////////////////////////////////////////
    //显示小时
    r1=d/2+4;
    //显示新的时钟
    temp=(float)min/60;
    temp+=hour;
    px0=sx+r+(r-3*d-7)*sin((app_pi/6)*temp);
    py0=sy+r-(r-3*d-7)*cos((app_pi/6)*temp);
    px1=sx+r+r1*sin((app_pi/6)*temp);
    py1=sy+r-r1*cos((app_pi/6)*temp);
    gui_draw_bline1(px0,py0,px1,py1,2,YELLOW);
    //显示分钟
    r1=d/2+3;
    temp=(float)sec/60;
    temp+=min;
    //显示新的分钟
    px0=sx+r+(r-2*d-7)*sin((app_pi/30)*temp);
    py0=sy+r-(r-2*d-7)*cos((app_pi/30)*temp);
    px1=sx+r+r1*sin((app_pi/30)*temp);
    py1=sy+r-r1*cos((app_pi/30)*temp);
    gui_draw_bline1(px0,py0,px1,py1,1,GREEN);
    //显示秒钟
    r1=d/2+3;
    //显示新的秒钟
    px0=sx+r+(r-d-7)*sin((app_pi/30)*sec);
    py0=sy+r-(r-d-7)*cos((app_pi/30)*sec);
    px1=sx+r+r1*sin((app_pi/30)*sec);
    py1=sy+r-r1*cos((app_pi/30)*sec);
    gui_draw_bline1(px0,py0,px1,py1,0,RED);
    oldhour=hour;	//保存时
    oldmin=min;		//保存分
    oldsec=sec;		//保存秒
}

void show_digital_led(uint8_t x,uint8_t y,uint8_t h,uint8_t m,uint8_t s)
{
    uint8_t size = lcddev.width / 8 - 4*2;
    uint8_t lw = 10;
    uint8_t mode = 0xE0;

    Digital_Draw_num(4 + (size + 4 * 2) * 0,350,lw,size,size * 2,h/10,mode);
    Digital_Draw_num(4 + (size + 4 * 2) * 1,350,lw,size,size * 2,h%10,mode);

    Digital_Draw_num(4 + (size + 4 * 2) * 3,350,lw,size,size * 2,m/10,mode);
    Digital_Draw_num(4 + (size + 4 * 2) * 4,350,lw,size,size * 2,m%10,mode);

    Digital_Draw_num(4 + (size + 4 * 2) * 6,350,lw,size,size * 2,s/10,mode);
    Digital_Draw_num(4 + (size + 4 * 2) * 7,350,lw,size,size * 2,s%10,mode);
}

//时间显示模式
u8 calendar_play(void)
{
    u8 second=0;
    short temperate=0;	//温度值
    u8 t=0;
    u8 tempdate=0;
    u8 rval=0;			//返回值
    u8 res;
    u16 xoff=0;
    u16 yoff=0;	//表盘y偏移量
    u16 r=0;	//表盘半径
    u8 d=0;		//指针长度

    u8 TEMP_SEN_TYPE=0;	//默认使用DS18B20
    FIL* f_calendar=0;

    u8 touch_flag = 0;

    f_calendar=(FIL *)gui_memin_malloc(sizeof(FIL));//开辟FIL字节的内存区域
    if(f_calendar==NULL)rval=1;		//申请失败
    else
    {
        res=f_open(f_calendar,(const TCHAR*)APP_ASCII_S6030,FA_READ);//打开文件
        if(res==FR_OK)
        {
            asc2_s6030=(u8*)gui_memex_malloc(f_calendar->fsize);	//为大字体开辟缓存地址
            if(asc2_s6030==0)rval=1;
            else
            {
                res=f_read(f_calendar,asc2_s6030,f_calendar->fsize,(UINT*)&br);	//一次读取整个文件
            }
            f_close(f_calendar);
        }
        if(res)rval=res;
    }
    if(rval==0)//无错误
    {
        LCD_Clear(BLACK);//清黑屏
        second=calendar.sec;//得到此刻的秒钟
        POINT_COLOR=GBLUE;
        Show_Str(48,60,lcddev.width,lcddev.height,(u8*)calendar_loading_str[gui_phy.language][0],16,0x01); //显示进入信息
        if(DS18B20_Init())
        {
            Show_Str(48,76,lcddev.width,lcddev.height,(u8*)calendar_loading_str[gui_phy.language][1],16,0x01);
            delay_ms(500);
            Show_Str(48,92,lcddev.width,lcddev.height,(u8*)calendar_loading_str[gui_phy.language][2],16,0x01);
            TEMP_SEN_TYPE=1;
        }
        delay_ms(1100);//等待1.1s
        BACK_COLOR= BLACK;
        LCD_Clear(BLACK);//清黑屏
        if(lcddev.width==240)
        {
            r=80;
            d=7;
        } else if(lcddev.width==320)
        {
            r=120;
            d=9;
        } else if(lcddev.width==480)
        {
            r=160;
            d=12;
        }
        yoff=lcddev.height / 40;
        TIME_TOPY=yoff+r*2+10;
        OTHER_TOPY=TIME_TOPY+120+yoff;
        xoff=(lcddev.width-240)/2;
        calendar_circle_clock_drawpanel(lcddev.width/2,yoff+r,r*2,d);//显示指针时钟表盘
        calendar_date_refresh();  //加载日历
        tempdate=calendar.w_date;//天数暂存器
        gui_phy.back_color=BLACK;

        draw_str.IF_DrawLine = (void *)LCD_DrawLine;//数码管大字体接口
        DIGITAL_COLOR_BACK = BLACK;
        DIGITAL_COLOR_FRONT = RED;
        DIGITAL_COLOR_FRONT_EMP = BLACK;
        draw_str.Digital_Draw_Line = (void *)Draw_Line;

//		gui_show_ptchar(xoff+70-4,TIME_TOPY,lcddev.width,lcddev.height,0,GBLUE,60,':',0);	//":"
//		gui_show_ptchar(xoff+150-4,TIME_TOPY,lcddev.width,lcddev.height,0,GBLUE,60,':',0);	//":"
    }
    while(rval==0)
    {
        RTC_Get();					//更新时间
        if(system_task_return)break;//需要返回
        if(second!=calendar.sec)	//秒钟改变了
        {
            second=calendar.sec;
            calendar_circle_clock_showtime(lcddev.width/2,yoff+r,r*2,d,calendar.hour,calendar.min,calendar.sec);//指针时钟显示时间
            show_digital_led(0,TIME_TOPY,calendar.hour,calendar.min,calendar.sec);
//			gui_phy.back_color=BLACK;
//			gui_show_num(xoff+10,TIME_TOPY,2,GBLUE,60,calendar.hour,0X80);	//显示时
//			gui_show_num(xoff+90,TIME_TOPY,2,GBLUE,60,calendar.min,0X80);	//显示分
//			gui_show_num(xoff+170,TIME_TOPY,2,GBLUE,60,calendar.sec,0X80);	//显示秒
            if(t%2==0)//等待2秒钟
            {
                if(TEMP_SEN_TYPE)temperate=Get_Temprate()/10;//得到内部温度传感器的温度值,0.1℃
                else temperate=DS18B20_Get_Temp();//得到18b20温度
                if(temperate<0)//温度为负数的时候，红色显示
                {
                    POINT_COLOR=RED;
                    temperate=-temperate;	//改为正温度
                } else POINT_COLOR=BRRED;	//正常为棕红色字体显示
                gui_show_num(xoff+90,OTHER_TOPY,2,GBLUE,60,temperate/10,0X80);	//XX
                gui_show_ptchar(xoff+150,OTHER_TOPY,lcddev.width,lcddev.height,0,GBLUE,60,'.',0);	//"."
                gui_show_ptchar(xoff+180-15,OTHER_TOPY,lcddev.width,lcddev.height,0,GBLUE,60,temperate%10+'0',0);//显示小数
                gui_show_ptchar(xoff+210-10,OTHER_TOPY,lcddev.width,lcddev.height,0,GBLUE,60,95+' ',0);//显示℃
                if(t>0)t=0;
            }
            if(calendar.w_date!=tempdate)
            {
                calendar_date_refresh();	//天数变化了,更新日历.
                tempdate=calendar.w_date;	//修改tempdate，防止重复进入
            }
            t++;
        }
        tp_dev.scan(0);

        if(tp_dev.sta&TP_PRES_DOWN)//有按键按下
        {
            if(touch_flag == 0)
            {
                if((tp_dev.y[0]>350)&&(tp_dev.y[0]<350 + 104))
                {
                    if(DIGITAL_COLOR_FRONT == RED)
                        DIGITAL_COLOR_FRONT = BLUE;
                    else if(DIGITAL_COLOR_FRONT == BLUE)
                        DIGITAL_COLOR_FRONT = GREEN;
                    else if(DIGITAL_COLOR_FRONT == GREEN)
                        DIGITAL_COLOR_FRONT = WHITE;
                    else if(DIGITAL_COLOR_FRONT == WHITE)
                        DIGITAL_COLOR_FRONT = YELLOW;
                    else if(DIGITAL_COLOR_FRONT == YELLOW)
                        DIGITAL_COLOR_FRONT = GRAY;
                    else if(DIGITAL_COLOR_FRONT == GRAY)
                        DIGITAL_COLOR_FRONT = RED;
                }
                touch_flag = 1;
            }
        }
        else
        {
            touch_flag = 0;
        }
        delay_ms(20);
    };
    while(tp_dev.sta&TP_PRES_DOWN)tp_dev.scan(0);//等待TP松开.
    gui_memex_free(asc2_s6030);	//删除申请的内存
    asc2_s6030=0;				//清零
    gui_memin_free(f_calendar);	//删除申请的内存
    POINT_COLOR=BLUE;
    BACK_COLOR=WHITE ;
    return rval;
}





















