#ifndef lcd_H 			//���Ϊ	if not define led.h
#define lcd_H 			//���û�ж��� led.h ,����Ͷ���һ�� led.h
 
#include "reg52.h"		//����  led,c ����Ҫ�õ� 51��Ƭ���Ĵ���	P1��
                      // �����������	51 ��Ƭ����ͷ�ļ�
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
void lcd_pos(uchar X,uchar Y);  //ȷ����ʾλ��
//���庯��
void delay(int ms);
bit lcd_busy();
void lcd_wcmd(uchar cmd);
void lcd_wdat(uchar dat);
void lcd_init();
void initdisplay();
void Ledflash(int n);
#endif	// �������