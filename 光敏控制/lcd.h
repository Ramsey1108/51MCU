#ifndef lcd_H 			//���Ϊ	if not define led.h
#define lcd_H 			//���û�ж��� led.h ,����Ͷ���һ�� led.h
 
//#include "reg52.h"		//����  led,c ����Ҫ�õ� 51��Ƭ���Ĵ���	P1��
                      // �����������	51 ��Ƭ����ͷ�ļ�
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
#endif	// �������