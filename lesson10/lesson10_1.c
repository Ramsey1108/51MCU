#include <reg52.h>
#include<intrins.h>
#include"lesson10_2.h"
#define uint unsigned int    //�궨��
#define uchar unsigned char  //�궨��
sbit dula=P2^6;
sbit wela=P2^7;//��������˹ر�led�����
sbit lcden=P3^4;//Һ��ʹ�ܶ�
sbit lcdrs=P3^5;//Һ���������ݶ�
sbit beep=P2^3;//�������˿�
//�����Ķ���
sbit s1=P3^0;//S9����
sbit s2=P3^1;//S13����
sbit s3=P3^2;//S17����
sbit rd=P3^7;

uchar code table[]="  2021-8-25 WEN";
//uchar code table1[]="    00:00:00";
uchar count,s1num;//���˼��ΰ���
char shi,fen,miao;//��ʱ����������ʾʱ����ı���
void delay1ms(uint z)     //��ʱ�Ӻ���
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	lcdrs=0;//ѡ��д����ģʽ
	P0=com;//�������͵�������������ȥ
	delay1ms(5);
	lcden=1; //һ��һ�߿��Դ�������
	delay1ms(5);//��΢��ʱ���԰����ݴ���ȥ
	lcden=0;//�������°����õ�

}
void write_data(uchar date)
{
	lcdrs=1;//ѡ��д����ģʽ
	P0=date;
	delay1ms(5);
	lcden=1; //һ��һ�߿��Դ�������
	delay1ms(5);//��΢��ʱ���԰����ݴ���ȥ
	lcden=0;//�������°����õ�
}
void write_sfm(uchar add, uchar date)//add��λ���Ѿ������
{	
	uchar shi,ge;
	shi=date/10;
	ge=date%10;//�����ʮλ�͸�λ
	write_com(0x80+0x40+add);//������ʾλ��
	write_data(0x30+shi);//0x30��ASCII�� �������־�����ʾ����
	//��ʼ����ʱ���Զ����������Բ��ÿ�����������һλ
	write_data(0x30+ge);
}
void init()//��ʼ������
{
	uchar num;	
	dula=0;
	wela=0;//�ѿ��������������������˶�����
	lcden=0;
	rd=0;//������̵������õͣ��������������
	//��ʼ������ֵ
	shi=0;
	fen=0;
	miao=0;
	//count=0;
	//24c02��ʼ��
	init_24c02();
	//����
	/*
	write_add(1,0);
	delay1ms(5);
	write_add(2,0);
	delay1ms(5);
	write_add(3,0);
	delay1ms(5);
	*/

	write_com(0x38);
	write_com(0x06);//��ַָ���Զ� +1
	write_com(0x0c);//����ʾ���
	write_com(0x01); //��ʾ��0����ָ����0

	write_com(0x80);//д��һ��

	for(num=0;num<15;num++)
		{
			write_data(table[num]);
			delay1ms(5);
		}
	//�ڶ�����ʾλ�������ط��ӷֺ���
		write_com(0x80+0x40+6);
		write_data(':');
		delay1ms(5);
		write_com(0x80+0x40+9);
		write_data(':');
		delay1ms(5);
		miao=read_add(1); //�Ӵ洢����ȡ
		fen=read_add(2);
		shi=read_add(3);
	//��ȡ��������ȥҺ����ʾ
		write_sfm(10,miao);
		write_sfm(7,fen);
		write_sfm(4,shi);

	//��ʱ���ĳ�ʼ��
	TMOD=0X01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;//��ʼ��ʱ


}
void di()//��������������
{
	beep=0;
	delay1ms(100);
	beep=1;
}
void keyscan()
{
	if(s1 == 0);//���ܼ�������
	{
		delay1ms(5);
		if(s1 == 0)//����
		{
			s1num++;
			while(!s1);//����ȷ��
			di();//�����˲���
			if(s1num == 1)
			{
				TR0=0;//�رն�ʱ��
				write_com(0x80+0x40+10);//��λ�����λ��
				write_com(0x0f);//��꿪ʼ��˸;
			}
			if(s1num == 2)
			{	
				write_com(0x80+0x40+7);//��λ�����ӵ�λ��
			}
			if(s1num == 3)
			{	
				write_com(0x80+0x40+4);//��λ�����ӵ�λ��
			}
			if(s1num == 4)
			{	
				s1num=0;//�����Ĵξ��˳�
				write_com(0x0c);//��겻��˸��
				TR0=1;//�����˶�ʱ����ʼ��
				
			}
		}
	}
	if(s1num != 0)//ȷ�Ϲ��ܼ������µ�ʱ��
	{ 
		if(s2 == 0)//���Ӽ�����
		{
			delay1ms(5);
			if(s2 == 0)//����
			{
				while(!s2);//����ȷ��
				di();
				if(s1num == 1)//��һ�ε������Ӱ������ʱ��
				{
					miao++;
					if(miao == 60)
						miao =0 ;//�ӵ�60������
					write_sfm(10,miao);//��һ��Һ������һ��
					write_com(0x80+0x40+10);//��λ�����λ��
					write_add(1,miao);//��24c02д������
				}
				if(s1num == 2)//��һ�ε������Ӱ������ʱ��
				{
					fen++;
					if(fen == 60)
						fen =0 ;//�ӵ�60������
					write_sfm(7,fen);//��һ��Һ������һ��
					write_com(0x80+0x40+7);//��λ�����λ��
					write_add(2,fen);//��24c02д������
				}
				if(s1num == 3)//��һ�ε������Ӱ������ʱ��
				{
					shi++;
					if(shi == 24)
						shi =0 ;//�ӵ�60������
					write_sfm(4,shi);//��һ��Һ������һ��
					write_com(0x80+0x40+4);//��λ�����λ��
					write_add(3,shi);//��24c02д������
				}
			}
		}
		if(s3 == 0)//��С������
		{
			delay1ms(5);
			if(s3 == 0);//����
			{
				while(!s3);//����ȷ��
				di();
				if(s1num ==1)//���˼�С���ӵ�
				{
					miao--;
					if(miao == -1)//����0�ٰ�һ�ξ�60
						miao=59;
					write_sfm(10,miao);//��һ��Һ������һ��
					write_com(0x80+0x40+10);//��λ�����λ��
					write_add(1,miao);//��24c02д������
				}
				if(s1num ==2)//���˼�С���ӵ�
				{
					fen--;
					if(fen == -1)//����0�ٰ�һ�ξ�60
						fen=59;
					write_sfm(7,fen);//��һ��Һ������һ��
					write_com(0x80+0x40+7);//��λ�����λ��
					write_add(2,fen);//��24c02д������
				}
				if(s1num ==3)//���˼�С���ӵ�
				{
					shi--;
					if(shi == -1)//����0�ٰ�һ�ξ�60
						shi=23;
					write_sfm(4,shi);//��һ��Һ������һ��
					write_com(0x80+0x40+4);//��λ�����λ��
					write_add(3,shi);//��24c02д������
				}
			}
		}
	}
}
int main()
{
	init();
	while(1)
	{
		keyscan();	
	}
}
void t0() interrupt 1	//��ʱ�жϷ�����
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//���¼���
	count++;//ÿ��50ms  tcnt��1
	if(count == 18)//1s����(��11.0592 MHZ ��ȷ��)
	{
		count=0;//����
		miao++;//��һ��
		if(miao==60)//1���ӵ���
		{
			miao=0;//����
			fen++;//��һ����
			if(fen == 60)//һСʱ����
			{
				fen=0;//����
				shi++;
				if(shi == 24)//һ�쵽��
				{
					shi = 0;
				}
				write_sfm(4,shi);//��Сʱ�ı�������д��
				write_add(3,shi);//���ݸı�����洢��24c02
			}
			write_sfm(7,fen);//�����Ӹı�������д��
			write_add(2,fen);//���ݸı�����洢��24c02	
		}
		write_sfm(10,miao);//�����Ӹı�������д��
		write_add(1,miao);//���ݸı�����洢��24c02
	}
}







