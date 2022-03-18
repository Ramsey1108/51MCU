#include  "lcd.h"
#include  "wendu.h"
#include  "led.h"

#define	uchar unsigned char
#define	uint unsigned int	// 这些宏定义都可以在头文件 .h 里定义
//灯
sbit BlueLed = P1^0;
sbit YellowLed = P1^1;
sbit WhileLed = P1^2;
//
uchar table3[]="Motor is CCW ";//逆时针
uchar table4[]="Motor is  CW ";//顺时针
uchar table5[]="Motor is Stop";//停了
//主函数

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
	//测试
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
				//测试
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
				//写入液晶第一行
				write_com(0x80);
				for(a=0;a<13;a++)
				{
					write_date(table4[a]);
					delay(10);
				}
				YellowLedLight();
				MotorCW();   //顺时针转动	
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
				MotorCCW();  //逆时针转动	
				}
			}

	}
		
}



