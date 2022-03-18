#include "i2c.h"
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define somenop() _nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_()

void I2C_Start()     //起始
{
   SCL=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=0;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SCL=0;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
}

void I2C_Stop()      //终止
{  
   SDA=0;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SCL=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
}

void I2C_SendByte(unsigned char dat)   //发送一个字节
{
   uchar i,j,b=0;
   for(i=0;i<8;i++)
   {    
       SCL=0;  
   _nop_();	_nop_();_nop_();_nop_();_nop_();
       SDA=(bit)(dat&0x80);     //每次取最高位进行发送
       dat<<=1;        //从最高位开始发送，左移使每一位逐渐成为最高位
       SCL=1;          //上升沿时发送数据
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   }
   SCL=0;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=1;     
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SCL=1;
   _nop_();
   while((SDA==1)&&(j<250))  j++;  //等待应答，也就是等待从设备把SDA拉低
   SCL=0;
   _nop_();   
}

 unsigned char I2C_ReadByte()     //读一个字节
{
   uchar i,dat=0;
   SCL=0;         //此处也可以不置低，因为起始和发送一个字节之后SCL都是0
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=1;      //拉高准备数据读取
   _nop_();
   for(i=0;i<8;i++)   //读取8位数据
   {
      SCL=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
      dat<<=1;
      if(SDA==1)
         dat=dat|0x01;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
      SCL=0;     //下降沿时读取数据
   _nop_();	_nop_();_nop_();_nop_();_nop_();
    }
    return dat;
}
