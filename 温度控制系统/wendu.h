#ifndef WENDU_H 			//理解为	if not define led.h
#define WENDU_H 			//如果没有定义 led.h ,这里就定义一个 led.h
 
#include "reg52.h"		//由于  led,c 里面要用到 51单片机寄存器	P1，
                      // 所以这里包含	51 单片机的头文件
//#include "intrins.h"		// 循环移位用到
#define	uchar unsigned char
#define	uint unsigned int	// 这些宏定义都可以在头文件 .h 里定义
#define MotorData P3                    //步进电机控制接口定义
extern uchar phasecw[8];
extern uchar phaseccw[8];
void Delay_xms(uint x);
//顺时针转动
void MotorCW(void);
//逆时针转动
void MotorCCW(void);
//停止转动
void MotorStop(void);
#endif	// 定义结束
