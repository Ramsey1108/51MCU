#ifndef lcd_H 			//理解为	if not define led.h
#define lcd_H 			//如果没有定义 led.h ,这里就定义一个 led.h
 
//#include "reg52.h"		//由于  led,c 里面要用到 51单片机寄存器	P1，
                      // 所以这里包含	51 单片机的头文件
#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
//sbit rs=P3^5;
//sbit lcden=P3^4;
//sbit dula=P2^6;
//sbit wela=P2^7;
extern uchar table1[];
extern uchar table2[];

void delay(uint x);
void delay1(uint x);
void write_com(uchar com);
void write_date(uchar date);
void init();
#endif	// 定义结束