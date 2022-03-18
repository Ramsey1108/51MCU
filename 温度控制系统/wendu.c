/*******************************************************
ULN2003驱动5V减速步进电机程序
*********************/
#include  "wendu.h"	// 这里包含 led.h 这个头文件
#include<reg52.h>
//#define uchar unsigned char
//#define uint  unsigned int
//#define MotorData P2                    //步进电机控制接口定义
uchar phasecw[8] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};//正转 电机导通相序 D-C-B-A
uchar phaseccw[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};//反转 电机导通相序 A-B-C-D
//ms延时函数
void Delay_xms(uint x)
{
 uint i,j;
 for(i=0;i<x;i++)
  for(j=0;j<112;j++);
}
//顺时针转动
void MotorCW(void)
{
 uchar i,j;
 for(j=0;j<8;j++)
 {
 	for(i=0;i<8;i++)
  {
   MotorData=phasecw[i];
   Delay_xms(5);//转速调节
  }
 }
}
//逆时针转动
void MotorCCW(void)
{
 uchar i,j;
 for(j=0;j<8;j++)
 {
 	for(i=0;i<8;i++)
  {
   MotorData=phaseccw[i];
   Delay_xms(5);//转速调节
  }
 }
}
//停止转动
void MotorStop(void)
{
 MotorData=0x00;
}
