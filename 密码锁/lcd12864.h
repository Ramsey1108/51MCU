
#include "reg52.h"
typedef unsigned int u16
typedef unsigned char u8
sbit RS=P1^0;
sbit RW=P1^1;
sbit E=P1^2;
sbit beep=P1^3;
sbit LEDgreen=P1^4;
sbit LEDbule=P1^5;
sbit LEDred=P1^6;
void LCD_init();
void delay(u16 t);
void Write_cmd(u8 cmd);
void Write_data(u8 dat);
void display(u8 y,u8 a[16]);

u8 datavaue=0;
u8 table0[]="51单片机蓝牙系统";
u8 table1[]="开发者： 罗聪  ";
u8 table2[]="单片机系统与应用";
u8 table3[]="LED 绿灯被点亮  ";
u8 table4[]="LED 蓝灯被点亮  ";
u8 table5[]="LED 红灯被点亮  ";

void BeepOn()
{
	beep=0;
	delay(500);
	beep=1;
}
void Usart_Init()
{
	TMOD=0x20;//让T1工作在定时器模式2
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;    //启动定时器1，开始定时
	SM0=0;
	SM=1;
	REN=1;    //允许接收
	ES=1;     //接通串口中断开关
	EA=1;     //接通单片机中断开关
}
void send(u8 a)
{
	SBUF=a;
	while(!TI);
	ES=1;
	TI=0;
}
void main()
{
	Usart_Init();
	LCD_init();
	display(0x80,table0);
	display
}

		  void delay(u16 t)
{
	u8 i;
	while(t--)
		for(i=19;i>0;i--);
}
void Write_cmd(u8 cmd)
{
	RS=0;
	RW=0;
	P0=cmd;
	delay(5);
	E=1;
	delay(10);
	E=0;
}
void Write_data(u8 dat)
{
	RS=1;
	RW=0;
	P0=dat;
	delay(5);
	E=1;
	delay(10);
	E=0;
}
void LCD_init()
{
	delay(400);
	Wtite_cma(0x30);
	delay(100);
	Write_cmd(0x30);
	delay(37);
	Wtite_cmd(0x30);
	delay(10);
	Write_cmd(0x0c);
	delay(10);
	Write_cmd(0x01):
	delay(100);
	Write_cmd(0x06);
}
void display(u8 y,u8 a[16])
{
	u8 i;
	Write_cmd(y);
	for(i=0;i<16;i++)
	{
		Write_data(a[i]);
	}
}