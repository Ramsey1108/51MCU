/*
#include <reg52.h>
#include<intrins.h>
#define unit unsigned int
#define uchar unsigned char
void delay1s(unit);
uchar aa;
//后面的P1一定需要大写 系统规定
sbit beep=P2^3;//蜂鸣器控制端口
void main()
{
	P1=0xfe;//赋值11111110 第一个灯亮
	beep=1;//
//	P1=aa;//点亮第一个发光灯
	while(1)
	{ 
		delay1s(1000);//延时一秒 
	//	P1=aa;//点亮第一个发光灯
		beep=~beep;
		delay1s(1000);//延时一秒
		P1=_crol_(P1,1);//调用函数向左移一位，例如从11111110到11111101就是第二个亮

	}
	
}
void delay1s(unit xms)
{
	unit i,j;
	for(i=xms;i>0;i--)	 //想延迟多少秒就赋值给xms
		for(j=110;j>0;j--);
}
*/