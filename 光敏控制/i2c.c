#include "i2c.h"
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define somenop() _nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_()

void I2C_Start()     //��ʼ
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

void I2C_Stop()      //��ֹ
{  
   SDA=0;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SCL=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
}

void I2C_SendByte(unsigned char dat)   //����һ���ֽ�
{
   uchar i,j,b=0;
   for(i=0;i<8;i++)
   {    
       SCL=0;  
   _nop_();	_nop_();_nop_();_nop_();_nop_();
       SDA=(bit)(dat&0x80);     //ÿ��ȡ���λ���з���
       dat<<=1;        //�����λ��ʼ���ͣ�����ʹÿһλ�𽥳�Ϊ���λ
       SCL=1;          //������ʱ��������
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   }
   SCL=0;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=1;     
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SCL=1;
   _nop_();
   while((SDA==1)&&(j<250))  j++;  //�ȴ�Ӧ��Ҳ���ǵȴ����豸��SDA����
   SCL=0;
   _nop_();   
}

 unsigned char I2C_ReadByte()     //��һ���ֽ�
{
   uchar i,dat=0;
   SCL=0;         //�˴�Ҳ���Բ��õͣ���Ϊ��ʼ�ͷ���һ���ֽ�֮��SCL����0
   _nop_();	_nop_();_nop_();_nop_();_nop_();
   SDA=1;      //����׼�����ݶ�ȡ
   _nop_();
   for(i=0;i<8;i++)   //��ȡ8λ����
   {
      SCL=1;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
      dat<<=1;
      if(SDA==1)
         dat=dat|0x01;
   _nop_();	_nop_();_nop_();_nop_();_nop_();
      SCL=0;     //�½���ʱ��ȡ����
   _nop_();	_nop_();_nop_();_nop_();_nop_();
    }
    return dat;
}
