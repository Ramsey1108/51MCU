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
//变量声明
uint ms=0,s=0,m=0,h=0,sflash=0,mflash=0,hflash=0,Turn=0;
uchar s1=15,m1=0,h1=0,Ifdisplay=1,Distime;
uchar j,k;


sbit beep=P2^4;//蜂鸣器接口

sbit keyset=P3^2;
sbit keyadd=P2^0;
sbit keylow=P2^1;
//灯泡
/*
LED=0;//红灯亮
LED1=1;//蓝灯灭
LED2=1;//绿灯灭
*/
sbit keyend=P3^3;//
sbit LED1=P3^4;
sbit LED2=P3^5;
sbit LED3=P2^2;
//声控接口
sbit Sound=P2^5;


//延时函数
void delay(uchar i)
{
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

//蜂鸣器发声
void beepon(){
beep=0;
delay(500);
beep=1;
}
//外部中断
void EX0_init()
{
	IT0=1;
	EX0=1;
	EA=1;
}
//定时器中断
void T0_init()
{
TMOD=0X01;//选择定时器0
TH0=(65536-50000)/256;//装入50MS的初值
TL0=(65536-50000)%256;
EA=1;//打开总中断
ET0=1;//打开定时器0中断
TR0=1;//开启定时器0
}

//数码管显示函数
void display(){
		if(Ifdisplay == 0)
		{
			//正常显示
			
//只有小时不=0的时候才显示
	if(h)
	{
	//十位
		P1=d[h/10];
		P0=w[5];
		delay(10);
	//个位
		P1=d[h%10]+0x80;
		P0=w[4];
		delay(10);
	}
//只有分钟不=0的时候才显示
	if(m)
	{
	//十位
		P1=d[m/10];
		P0=w[3];
		delay(10);
	//个位
		P1=d[m%10]+0x80;
		P0=w[2];
		delay(10);
	}
//不管咋样秒钟都显示
	//十位
		P1=d[s/10];
		P0=w[1];
		delay(10);
	//个位
		P1=d[s%10];
		P0=w[0];
		delay(10);			
		}
		else
		{
			P0=0xff;
		}
	}
//按键检测
void keyscan()
{
	//只有功能键按下才检测
	if(Turn!=0)
	{
	//按下去先让一秒亮一次的灯不亮
		LED3=1;
	//先检测增大
		if(keyadd == 0)//增加键被按下
		{
			delay(20);//消抖
			if(keyadd == 0)//松手检测
			{
				while(!keyadd);
				beepon();
				switch(Turn)//选择增加时分秒其中一个
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

	//再检测减小
		if(keylow == 0)//减小键被按下
		{
			delay(20);//消抖
			if(keylow == 0)//松手检测
			{
				while(!keylow);
				beepon();
				switch(Turn)//选择减少时分秒其中一个
				{
					case 1:
						//	LED=!LED;
							s--;
							if(s == -1)	//这要用==-1 不能用<0;不然猛乱码 2021年10月3日16:45:59
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
			//蜂鸣器响20s
			beep=0;
			delay(1000);
			beep=1;
			TR0=0;
			LED3=0;
		//	s1=61;
			//按键测试
		
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
//定时器
void T0_int() interrupt 1
{
	TH0=(66635-50000)/256;
	TL0=(66635-50000)%256;
	ms++;//到了20次说明到了1s,ms加一次是50ms
	if(ms == 20)//一秒到了
	{
		ms=0;//重新算一秒
		s++;
		LED3=!LED3;//灯闪一下
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
		//这里是到了设定时间的函数(先不写)
	}
}
//外部中断
void EX0_int() interrupt 0
{
	if(keyset==0)//检测S1
	{
		delay(5);
		if(keyset==0)
		{	
		//	LED=!LED;
			Turn++;
			//特殊情况（仅用于验收）
		//	s1=s+5;
		//	beep=1;
			TR0=0;
			if(Turn == 1)
			{
			  //	LED=0;//红灯亮
				LED1=1;//蓝灯灭
				LED2=1;//绿灯灭
		
			}
			if(Turn == 2)
			{
			//	LED=1;//红灯灭
				LED1=0;//蓝灯亮
				LED2=1;//绿灯灭
			}
			if(Turn == 3)
			{
		//		LED=1;//红灯灭
				LED1=1;//蓝灯灭
				LED2=0;//绿灯亮
				//LED=1;
			}
			if(Turn == 4)
				{
				//按一次蜂鸣器就不响
			//	beep=1;
				//指示灯操作(全灭)
		//		LED=1;
				LED1=1;
				LED2=1;
				//打开定时器，让一秒闪一下的灯继续
				TR0=1;
				LED3=0;
				//定时
			//	s1=s+5;
				Turn=0;
				}
		}
	}
}





