 #include<reg52.h>
  #include<math.h>
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
//��������
uint ms=0,s=0,m=0,h=0,sflash=0,mflash=0,hflash=0,Turn=0;
uchar s1=15,m1=0,h1=0,Ifdisplay=1,Distime;
uchar j,k;


sbit beep=P2^4;//�������ӿ�

sbit keyset=P3^2;
sbit keyadd=P2^0;
sbit keylow=P2^1;
//����
/*
LED=0;//�����
LED1=1;//������
LED2=1;//�̵���
*/
sbit keyend=P3^3;//
sbit LED1=P3^4;
sbit LED2=P3^5;
sbit LED3=P2^2;
//���ؽӿ�
sbit Sound=P2^5;


//��ʱ����
void delay(uchar i)
{
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

//����������
void beepon(){
beep=0;
delay(500);
beep=1;
}
//�ⲿ�ж�
void EX0_init()
{
	IT0=1;
	EX0=1;
	EA=1;
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
	if(h)
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
	if(m)
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
//�������
void keyscan()
{
	//ֻ�й��ܼ����²ż��
	if(Turn!=0)
	{
	//����ȥ����һ����һ�εĵƲ���
		LED3=1;
	//�ȼ������
		if(keyadd == 0)//���Ӽ�������
		{
			delay(20);//����
			if(keyadd == 0)//���ּ��
			{
				while(!keyadd);
				beepon();
				switch(Turn)//ѡ������ʱ��������һ��
				{
					case 1:
						//	LED=!LED;
							s++;
							if(s>59)
								s=0;
							break;
					case 2:
						//	LED1=!LED1;
							m++;
							if(m>59)
								m=0;
							break;
					case 3:
							h++;
							if(h>23)
								h=0;
							break;
				}
			}
		}

	//�ټ���С
		if(keylow == 0)//��С��������
		{
			delay(20);//����
			if(keylow == 0)//���ּ��
			{
				while(!keylow);
				beepon();
				switch(Turn)//ѡ�����ʱ��������һ��
				{
					case 1:
						//	LED=!LED;
							s--;
							if(s == -1)	//��Ҫ��==-1 ������<0;��Ȼ������ 2021��10��3��16:45:59
								{
							//	P1=d[5];
							//	P0=w[1];
							//	delay(10);
								P1=0Xff;
								delay(20);
								s=59;
								}
							break;
					case 2:
						//	LED1=!LED1;
							m--;
							if(m== -1)
								m=59;
							break;
					case 3:
							h--;
							if(h== -1)
								h=23;
							break;
				}
			}
		}

	}
}

void main()
{
	P1=0xff;
	EX0_init();
	T0_init();
	Turn=0;

	while(1)
	{
	//	P0=0xff;
	//	display();	
	   /*
		if(s1==s)
		{
			//��������20s
			beep=0;
			delay(1000);
			beep=1;
			TR0=0;
			LED3=0;
		//	s1=61;
			//��������
		
		}
		*/
		EX0=1;
		Sound=1;
		keyscan();
		delay(30);
	//	Ifdisplay=0;
		
		Sound=1;
		if(Sound==0 )
		{
			Ifdisplay=0;
			Distime=s;
			//P0=0xff;
			//delay(1000);
			//Ifdisplay=1;
				
		}
		display();
		
		if(abs(s-Distime) == 10)
		{
			Ifdisplay=1;
		//	display();
		}
		
		
		
	}
}
//��ʱ��
void T0_int() interrupt 1
{
	TH0=(66635-50000)/256;
	TL0=(66635-50000)%256;
	ms++;//����20��˵������1s,ms��һ����50ms
	if(ms == 20)//һ�뵽��
	{
		ms=0;//������һ��
		s++;
		LED3=!LED3;//����һ��
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
//�ⲿ�ж�
void EX0_int() interrupt 0
{
	if(keyset==0)//���S1
	{
		delay(5);
		if(keyset==0)
		{	
		//	LED=!LED;
			Turn++;
			//������������������գ�
		//	s1=s+5;
		//	beep=1;
			TR0=0;
			if(Turn == 1)
			{
			  //	LED=0;//�����
				LED1=1;//������
				LED2=1;//�̵���
		
			}
			if(Turn == 2)
			{
			//	LED=1;//�����
				LED1=0;//������
				LED2=1;//�̵���
			}
			if(Turn == 3)
			{
		//		LED=1;//�����
				LED1=1;//������
				LED2=0;//�̵���
				//LED=1;
			}
			if(Turn == 4)
				{
				//��һ�η������Ͳ���
			//	beep=1;
				//ָʾ�Ʋ���(ȫ��)
		//		LED=1;
				LED1=1;
				LED2=1;
				//�򿪶�ʱ������һ����һ�µĵƼ���
				TR0=1;
				LED3=0;
				//��ʱ
			//	s1=s+5;
				Turn=0;
				}
		}
	}
}





