#include  "lcd.h"
//#include<reg52.h>
//#define uchar unsigned char
//#define uint unsigned int

sbit rs=P2^5;
sbit rd=P2^6;
sbit lcden=P2^4;
//sbit dula=P2^6;
//sbit wela=P2^7;
//uchar table1[]="TX-1C MCU";
//uchar table2[]="WWW.TXMCU.COM";
void delay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=10;b>0;b--); 
}

void delay1(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=100;b>0;b--); 
}

void write_com(uchar com)
{
	rs=0;
	lcden=0;
	rd=0;
	P0=com;
	delay(10);
	lcden=1;
	delay(20);
	lcden=0;	
}

void write_date(uchar date)
{
	rs=1;
	lcden=0;
	rd=0;
	P0=date;
	delay(10);
	lcden=1;
	delay(20);
	lcden=0;	
}

void init()
{
//	dula=0;
//	wela=0;
	lcden=0;
	write_com(0x38);
	delay(10);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);

}

