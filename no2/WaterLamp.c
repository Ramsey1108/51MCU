/*
#include <reg52.h>
#include<intrins.h>
#define unit unsigned int
#define uchar unsigned char
void delay1s(unit);
uchar aa;
//�����P1һ����Ҫ��д ϵͳ�涨
sbit beep=P2^3;//���������ƶ˿�
void main()
{
	P1=0xfe;//��ֵ11111110 ��һ������
	beep=1;//
//	P1=aa;//������һ�������
	while(1)
	{ 
		delay1s(1000);//��ʱһ�� 
	//	P1=aa;//������һ�������
		beep=~beep;
		delay1s(1000);//��ʱһ��
		P1=_crol_(P1,1);//���ú���������һλ�������11111110��11111101���ǵڶ�����

	}
	
}
void delay1s(unit xms)
{
	unit i,j;
	for(i=xms;i>0;i--)	 //���ӳٶ�����͸�ֵ��xms
		for(j=110;j>0;j--);
}
*/