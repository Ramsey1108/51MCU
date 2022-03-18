
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
u8 table0[]="51��Ƭ������ϵͳ";
u8 table1[]="�����ߣ� �޴�  ";
u8 table2[]="��Ƭ��ϵͳ��Ӧ��";
u8 table3[]="LED �̵Ʊ�����  ";
u8 table4[]="LED ���Ʊ�����  ";
u8 table5[]="LED ��Ʊ�����  ";

void BeepOn()
{
	beep=0;
	delay(500);
	beep=1;
}
void Usart_Init()
{
	TMOD=0x20;//��T1�����ڶ�ʱ��ģʽ2
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;    //������ʱ��1����ʼ��ʱ
	SM0=0;
	SM=1;
	REN=1;    //�������
	ES=1;     //��ͨ�����жϿ���
	EA=1;     //��ͨ��Ƭ���жϿ���
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