#ifndef wendu18b20_H 			//���Ϊ	if not define led.h
#define wendu18b20_H 			//���û�ж��� led.h ,����Ͷ���һ�� led.h
#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
//extern dis3[];
void dsreset(void);
bit tempreadbit(void);
uchar tempread(void);
void tempwritebyte(uchar dat);
void tempchange(void);
uint get_temp();
void tempdisplay();

#endif	// �������