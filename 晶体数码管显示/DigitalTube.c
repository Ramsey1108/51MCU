/*
#include<reg52.h>
sbit dula=P2^6;//声明锁存端，用来控制段选信号
sbit wela=P2^7;	//声明锁存端，用来控制位选信号
void main()
{
	wela=1;
	P0=0xc0; //送入段选信号，控制6个数码管哪个灯亮
	wela=0;
	//
	dula=1;
	P0=0x66;  //送入段选信号，控制亮的内容
	dula=0;
	while(1);
}
*/
