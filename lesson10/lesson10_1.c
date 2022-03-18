#include <reg52.h>
#include<intrins.h>
#include"lesson10_2.h"
#define uint unsigned int    //宏定义
#define uchar unsigned char  //宏定义
sbit dula=P2^6;
sbit wela=P2^7;//声明锁存端关闭led数码管
sbit lcden=P3^4;//液晶使能端
sbit lcdrs=P3^5;//液晶命令数据端
sbit beep=P2^3;//蜂鸣器端口
//按键的定义
sbit s1=P3^0;//S9按键
sbit s2=P3^1;//S13按键
sbit s3=P3^2;//S17按键
sbit rd=P3^7;

uchar code table[]="  2021-8-25 WEN";
//uchar code table1[]="    00:00:00";
uchar count,s1num;//按了几次按键
char shi,fen,miao;//定时器变量和显示时分秒的变量
void delay1ms(uint z)     //延时子函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	lcdrs=0;//选择写命令模式
	P0=com;//把命令送到数据总线上面去
	delay1ms(5);
	lcden=1; //一低一高可以传出数据
	delay1ms(5);//稍微延时可以把数据传出去
	lcden=0;//搞完重新把他置低

}
void write_data(uchar date)
{
	lcdrs=1;//选择写数据模式
	P0=date;
	delay1ms(5);
	lcden=1; //一低一高可以传出数据
	delay1ms(5);//稍微延时可以把数据传出去
	lcden=0;//搞完重新把他置低
}
void write_sfm(uchar add, uchar date)//add是位置已经算好了
{	
	uchar shi,ge;
	shi=date/10;
	ge=date%10;//分离出十位和个位
	write_com(0x80+0x40+add);//设置显示位置
	write_data(0x30+shi);//0x30是ASCII码 加上数字就是显示数字
	//初始化的时候自动后移了所以不用刻意往后面推一位
	write_data(0x30+ge);
}
void init()//初始化程序
{
	uchar num;	
	dula=0;
	wela=0;//把控制数码管亮的两个锁存端都关了
	lcden=0;
	rd=0;//矩阵键盘第四列置低，分离出独立按键
	//初始化变量值
	shi=0;
	fen=0;
	miao=0;
	//count=0;
	//24c02初始化
	init_24c02();
	//测试
	/*
	write_add(1,0);
	delay1ms(5);
	write_add(2,0);
	delay1ms(5);
	write_add(3,0);
	delay1ms(5);
	*/

	write_com(0x38);
	write_com(0x06);//地址指针自动 +1
	write_com(0x0c);//不显示光标
	write_com(0x01); //显示清0数据指针清0

	write_com(0x80);//写第一行

	for(num=0;num<15;num++)
		{
			write_data(table[num]);
			delay1ms(5);
		}
	//第二行显示位置两个地方加分号先
		write_com(0x80+0x40+6);
		write_data(':');
		delay1ms(5);
		write_com(0x80+0x40+9);
		write_data(':');
		delay1ms(5);
		miao=read_add(1); //从存储器读取
		fen=read_add(2);
		shi=read_add(3);
	//读取的数据送去液晶显示
		write_sfm(10,miao);
		write_sfm(7,fen);
		write_sfm(4,shi);

	//定时器的初始化
	TMOD=0X01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;//开始计时


}
void di()//蜂鸣器发声函数
{
	beep=0;
	delay1ms(100);
	beep=1;
}
void keyscan()
{
	if(s1 == 0);//功能键被按下
	{
		delay1ms(5);
		if(s1 == 0)//消抖
		{
			s1num++;
			while(!s1);//松手确认
			di();//松手了才响
			if(s1num == 1)
			{
				TR0=0;//关闭定时器
				write_com(0x80+0x40+10);//定位到秒的位置
				write_com(0x0f);//光标开始闪烁;
			}
			if(s1num == 2)
			{	
				write_com(0x80+0x40+7);//定位到分钟的位置
			}
			if(s1num == 3)
			{	
				write_com(0x80+0x40+4);//定位到秒钟的位置
			}
			if(s1num == 4)
			{	
				s1num=0;//按了四次就退出
				write_com(0x0c);//光标不闪烁了
				TR0=1;//调完了定时器开始走
				
			}
		}
	}
	if(s1num != 0)//确认功能键被按下的时候
	{ 
		if(s2 == 0)//增加键按下
		{
			delay1ms(5);
			if(s2 == 0)//消抖
			{
				while(!s2);//松手确认
				di();
				if(s1num == 1)//按一次调整秒钟按到秒的时候
				{
					miao++;
					if(miao == 60)
						miao =0 ;//加到60就清零
					write_sfm(10,miao);//按一次液晶更新一次
					write_com(0x80+0x40+10);//定位到秒的位置
					write_add(1,miao);//向24c02写入数据
				}
				if(s1num == 2)//按一次调整秒钟按到秒的时候
				{
					fen++;
					if(fen == 60)
						fen =0 ;//加到60就清零
					write_sfm(7,fen);//按一次液晶更新一次
					write_com(0x80+0x40+7);//定位到秒的位置
					write_add(2,fen);//向24c02写入数据
				}
				if(s1num == 3)//按一次调整秒钟按到秒的时候
				{
					shi++;
					if(shi == 24)
						shi =0 ;//加到60就清零
					write_sfm(4,shi);//按一次液晶更新一次
					write_com(0x80+0x40+4);//定位到秒的位置
					write_add(3,shi);//向24c02写入数据
				}
			}
		}
		if(s3 == 0)//减小键按下
		{
			delay1ms(5);
			if(s3 == 0);//消抖
			{
				while(!s3);//松手确认
				di();
				if(s1num ==1)//按了减小秒钟的
				{
					miao--;
					if(miao == -1)//到了0再按一次就60
						miao=59;
					write_sfm(10,miao);//按一次液晶更新一次
					write_com(0x80+0x40+10);//定位到秒的位置
					write_add(1,miao);//向24c02写入数据
				}
				if(s1num ==2)//按了减小分钟的
				{
					fen--;
					if(fen == -1)//到了0再按一次就60
						fen=59;
					write_sfm(7,fen);//按一次液晶更新一次
					write_com(0x80+0x40+7);//定位到秒的位置
					write_add(2,fen);//向24c02写入数据
				}
				if(s1num ==3)//按了减小秒钟的
				{
					shi--;
					if(shi == -1)//到了0再按一次就60
						shi=23;
					write_sfm(4,shi);//按一次液晶更新一次
					write_com(0x80+0x40+4);//定位到秒的位置
					write_add(3,shi);//向24c02写入数据
				}
			}
		}
	}
}
int main()
{
	init();
	while(1)
	{
		keyscan();	
	}
}
void t0() interrupt 1	//定时中断服务函数
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//重新计数
	count++;//每过50ms  tcnt加1
	if(count == 18)//1s到了(用11.0592 MHZ 精确的)
	{
		count=0;//清零
		miao++;//加一秒
		if(miao==60)//1分钟到了
		{
			miao=0;//清零
			fen++;//加一分钟
			if(fen == 60)//一小时到了
			{
				fen=0;//清零
				shi++;
				if(shi == 24)//一天到了
				{
					shi = 0;
				}
				write_sfm(4,shi);//若小时改变则重新写入
				write_add(3,shi);//数据改变立马存储到24c02
			}
			write_sfm(7,fen);//若分钟改变则重新写入
			write_add(2,fen);//数据改变立马存储到24c02	
		}
		write_sfm(10,miao);//若秒钟改变则重新写入
		write_add(1,miao);//数据改变立马存储到24c02
	}
}







