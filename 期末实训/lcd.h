#ifndef lcd_H 			//理解为	if not define led.h
#define lcd_H 			//如果没有定义 led.h ,这里就定义一个 led.h
 
#include "reg52.h"		//由于  led,c 里面要用到 51单片机寄存器	P1，
                      // 所以这里包含	51 单片机的头文件
#include "intrins.h"
//#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
//sbit rs=P3^5;
//sbit lcden=P3^4;
//sbit dula=P2^6;
//sbit wela=P2^7;
//extern code uchar dis1[];
//extern code uchar dis2[];
//extern code uchar dis3[];
//extern code uchar dis4[];
void delay0(uchar x);  //x*0.14MS
void beep();
void  dataconv();
void lcd_pos(uchar X,uchar Y);  //确定显示位置
//定义函数
void delay(int ms);
bit lcd_busy();
void lcd_wcmd(uchar cmd);
void lcd_wdat(uchar dat);
void lcd_init();
void initdisplay();
void Ledflash(int n);
#endif	// 定义结束