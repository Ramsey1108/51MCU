#include<reg52.h>
 #define uchar unsigned char
 #define uint unsigned int
 uchar code d[]={0x3f,0x06,0x5b,0x4f,
 					 0x66,0x6d,0x7d,0x07,
 					 0x7f,0x6f/*,0x77,0x7c,
					 0x39,0x5e,0x79,0x71,*/
					};
 uchar code w[]={0xfe,0xfd,0xfb,0xf7,
 					 0xef,0xdf/*0xbf,0x7f,*/
					};
sbit LED=P2^0;
sbit TSCLK = P2^1;//����ʱ�������
sbit TIO   = P2^2;//˫�������ߣ������ߣ�
sbit TRST  = P2^3;//ʹ�ܶ�
//����
uint ms=0,s=0,m=0,h=0,sflash=0,mflash=0,hflash=0,Turn=0;
uchar s1=15,m1=0,h1=0,Ifdisplay=1,Distime;
//��ʱ����
void delay(uchar i)
{
uchar j,k;
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}
//��ʱ���ж�
void T0_init()
{
TMOD=0X01;//ѡ��ʱ��0
TH0=(65536-50000)/256;//װ��50MS�ĳ�ֵ
TL0=(65536-50000)%256;
EA=1;//�����ж�
ET0=1;//�򿪶�ʱ��0�ж�
TR0=1;//������ʱ��0
}
//�������ʾ����
void display(){
		if(Ifdisplay == 0)
		{
			//������ʾ
			
//ֻ��Сʱ��=0��ʱ�����ʾ
//	if(h)
	{
	//ʮλ
		P1=d[h/10];
		P0=w[5];
		delay(10);
	//��λ
		P1=d[h%10]+0x80;
		P0=w[4];
		delay(10);
	}
//ֻ�з��Ӳ�=0��ʱ�����ʾ
//	if(m)
	{
	//ʮλ
		P1=d[m/10];
		P0=w[3];
		delay(10);
	//��λ
		P1=d[m%10]+0x80;
		P0=w[2];
		delay(10);
	}
//����զ�����Ӷ���ʾ
	//ʮλ
		P1=d[s/10];
		P0=w[1];
		delay(10);
	//��λ
		P1=d[s%10];
		P0=w[0];
		delay(10);			
		}
		else
		{
			P0=0xff;
		}
	}
/*******************************************************************/
/*                                                                 */
/*  				ds1302дһ���ֽ�                               */
/*                                                                 */
/*******************************************************************/
void write_DS1302(uchar cmd,uchar dat)//дһ���ֽ�
{
	uchar i ;
	TRST = 0;//����ʹ�ܶ�
	TSCLK = 0;//������������
	TRST = 1;//ʹ�ܶ˲���������
	for(i = 0; i < 8; i ++)//д����
	{
		TSCLK = 0;
		TIO = cmd & 0x01;//���λ�ȴ�
		TSCLK = 1;//�������߲��������أ����ݱ�DS1302����
		cmd >>= 1;//����1λ
	}	
	for(i = 0; i < 8;i ++)//д����
	{
		TSCLK = 0;
		TIO = dat & 0x01;//���λ�ȴ�
		TSCLK = 1;//�������߲��������أ����ݱ�DS1302����
		dat >>= 1;//����1λ
	}
	TRST = 0;//����ʹ�ܶˣ��رն�д����
}
/*******************************************************************/
/*                                                                 */
/*  				ds1302��ȡ����                                */
/*                                                                 */
/*******************************************************************/
uchar read_DS1302(uchar cmd)//��ȡ����
{
	uchar i,dat;
	TRST = 0;//����ʹ�ܶ�
	TSCLK = 0;//������������
	TRST = 1;//ʹ�ܶ˲���������
	for(i = 0; i < 8; i ++)//������
	{
		TSCLK = 0;
		TIO = cmd & 0x01;//���λ�ȴ�
		TSCLK = 1;//�������߲��������أ����ݱ�DS1302����
		cmd >>= 1;//����1λ
	}
	for(i = 0;i < 8; i ++)//������
	{
		TSCLK = 0;//������������
		dat >>= 1;
		if(TIO)
		{
			dat |= 0x80;
		}
		TSCLK = 1;//�������߲��������أ����ݱ�DS1302����
	}
	TRST = 0;//����ʹ�ܶˣ��رն�д����
	return dat;
}
/*******************************************************************/
/*                                                                 */
/*  				����תBCD��                                    */
/*                                                                 */
/*******************************************************************/
uchar dat_to_BCD(uchar dat)//����תBCD��
{
	uchar dat1,dat2;
	dat1 = dat / 10;
	dat2 = dat % 10;
	dat2 = dat2 + dat1 * 16;
	return dat2;
}
/*******************************************************************/
/*                                                                 */
/*  				BCD��ת����                                    */
/*                                                                 */
/*******************************************************************/
uchar BDD_to_dat(uchar dat)//BCD��ת����
{
	uchar dat1,dat2;
	dat1 = dat /16;
	dat2 = dat % 16;
	dat2 = dat2 + dat1 * 10;
	return dat2;
}



void main()
{
	T0_init();
	P0=0xff;
	Ifdisplay =0;
	//����
//	uchar i;
//	uchar sec,min,hour;
//	write_DS1302(0x8e,0);//���д����
//	write_DS1302(0x80,dat_to_BCD(0));//30��
//	write_DS1302(0x82,dat_to_BCD(54));//15��
//	write_DS1302(0x84,dat_to_BCD(0));//19ʱ
//	write_DS1302(0x8e,0x80);//��д����
s = BDD_to_dat(read_DS1302(0x81));//����Ĵ���������BCD��ת����
m = BDD_to_dat(read_DS1302(0x83));//���ּĴ���
h = BDD_to_dat(read_DS1302(0x85));//��ʱ�Ĵ���
delay(10);
write_DS1302(0x8e,0x80); //��д����
	while(1)
	{
		//P0=0xff;
		//display();

		//����
//		write_DS1302(0x8e,0);//���д����
//		s = BDD_to_dat(read_DS1302(0x81));//����Ĵ���������BCD��ת����
//		delay(5);
//		delay(10);
//		m = BDD_to_dat(read_DS1302(0x83));//���ּĴ���
//		delay(10);
//		h = BDD_to_dat(read_DS1302(0x85));//��ʱ�Ĵ���
//		delay(10);
	//	write_DS1302(0x8e,0x80); //��д����
//		delay(5);
		display();
	}
}
//��ʱ��
void T0_int() interrupt 1
{
	TH0=(66635-50000)/256;
	TL0=(66635-50000)%256;
	//����
	/*
		write_DS1302(0x8e,0);
		s = BDD_to_dat(read_DS1302(0x81));//����Ĵ���������BCD��ת����
		//delay(10);
		m = BDD_to_dat(read_DS1302(0x83));//���ּĴ���
		//delay(10);
		h = BDD_to_dat(read_DS1302(0x85));//��ʱ�Ĵ���
		//delay(10);
		write_DS1302(0x8e,0x80); //��д����
		//delay(10);
		*/
	//���Խ���
	ms++;//����20��˵������1s,ms��һ����50ms
	if(ms == 20)//һ�뵽��
	{
		ms=0;//������һ��
		s++;
		LED=!LED;//����һ��
		if(s>59)
		{
			s=0;
			m++;
			if(m>59)
			{
				m=0;
				h++;
				if(h>23)
					h=0;
			}
		}
		//�����ǵ����趨ʱ��ĺ���(�Ȳ�д)
	}
}