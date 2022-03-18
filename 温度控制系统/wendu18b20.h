#ifndef wendu18b20_H 			//理解为	if not define led.h
#define wendu18b20_H 			//如果没有定义 led.h ,这里就定义一个 led.h
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

#endif	// 定义结束