#ifndef __I2C_H_
#define __I2C_H_

#include <reg51.h>

sbit SCL=P2^1;
sbit SDA=P2^0;

unsigned char I2C_ReadByte();
void I2C_SendByte( unsigned char dat);
void I2C_Stop();
void I2C_Start();

#endif
