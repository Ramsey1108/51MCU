#include  "lcd.h"
#include  "wendu.h"
#include  "led.h"

#define	uchar unsigned char
#define	uint unsigned int	// ��Щ�궨�嶼������ͷ�ļ� .h �ﶨ��
//��
sbit BlueLed = P1^0;
sbit YellowLed = P1^1;
sbit WhileLed = P1^2;
//
uchar table3[]="Motor is CCW ";//��ʱ��
uchar table4[]="Motor is  CW ";//˳ʱ��
uchar table5[]="Motor is Stop";//ͣ��
//������

 void main()
{
	uchar a;
	uchar r;
	uint temp;
	uint N=64;
	init();
	P1=0xff;
	//uchar num;
	/*
	for(a=0;a<9;a++)
		{
			write_date(table1[a]);
			delay(10);
		}
		*/
	write_com(0x80);
	for(a=0;a<13;a++)
		{
			write_date(table5[a]);
			delay(10);
		}
	delay(20);
	write_com(0x80+0x40);
	//����
	/*
		for(a=0;a<64;a++)
		{
			MotorCW();
			delay(10);
		}
		*/
	delay(800);
	while(1)
	{
	//MotorCW();
			//YellowLedLight();
		//	tempchange();
			//delay(800);
				
			tempdisplay();
			delay(800);
			temp=get_temp();
			delay(800);
				//����
			for(r=0;r<64;r++)
			{
				tempdisplay();
				delay(800);
				temp=get_temp();
				delay(800);
				if(temp<220)
				{
				write_com(0x80);
				delay(10);
				for(a=0;a<13;a++)
					{
						write_date(table5[a]);
						delay(10);
					}
				BlueLedLight();	
				}
				else if(temp>=220 && temp<=250)
				{
				//д��Һ����һ��
				write_com(0x80);
				for(a=0;a<13;a++)
				{
					write_date(table4[a]);
					delay(10);
				}
				YellowLedLight();
				MotorCW();   //˳ʱ��ת��	
				}
				else if(temp>250)
				{
					write_com(0x80);
				for(a=0;a<13;a++)
				{
					write_date(table3[a]);
					delay(10);
				}
				WhileLedLight();
				MotorCCW();  //��ʱ��ת��	
				}
			}

	}
		
}



