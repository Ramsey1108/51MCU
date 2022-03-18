/*******************************************************
ULN2003����5V���ٲ����������
*********************/
#include  "wendu.h"	// ������� led.h ���ͷ�ļ�
#include<reg52.h>
//#define uchar unsigned char
//#define uint  unsigned int
//#define MotorData P2                    //����������ƽӿڶ���
uchar phasecw[8] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};//��ת �����ͨ���� D-C-B-A
uchar phaseccw[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};//��ת �����ͨ���� A-B-C-D
//ms��ʱ����
void Delay_xms(uint x)
{
 uint i,j;
 for(i=0;i<x;i++)
  for(j=0;j<112;j++);
}
//˳ʱ��ת��
void MotorCW(void)
{
 uchar i,j;
 for(j=0;j<8;j++)
 {
 	for(i=0;i<8;i++)
  {
   MotorData=phasecw[i];
   Delay_xms(5);//ת�ٵ���
  }
 }
}
//��ʱ��ת��
void MotorCCW(void)
{
 uchar i,j;
 for(j=0;j<8;j++)
 {
 	for(i=0;i<8;i++)
  {
   MotorData=phaseccw[i];
   Delay_xms(5);//ת�ٵ���
  }
 }
}
//ֹͣת��
void MotorStop(void)
{
 MotorData=0x00;
}
