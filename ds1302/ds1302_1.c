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
sbit TSCLK = P2^1;//串行时钟输入端
sbit TIO   = P2^2;//双向输入线（数据线）
sbit TRST  = P2^3;//使能端
//变量
uint ms=0,s=0,m=0,h=0,sflash=0,mflash=0,hflash=0,Turn=0;
uchar s1=15,m1=0,h1=0,Ifdisplay=1,Distime;
//延时函数
void delay(uchar i)
{
uchar j,k;
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
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
//	if(h)
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
//	if(m)
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
/*******************************************************************/
/*                                                                 */
/*  				ds1302写一个字节                               */
/*                                                                 */
/*******************************************************************/
void write_DS1302(uchar cmd,uchar dat)//写一个字节
{
	uchar i ;
	TRST = 0;//拉低使能端
	TSCLK = 0;//拉低数据总线
	TRST = 1;//使能端产生上升沿
	for(i = 0; i < 8; i ++)//写命令
	{
		TSCLK = 0;
		TIO = cmd & 0x01;//最低位先传
		TSCLK = 1;//数据总线产生上升沿，数据被DS1302读走
		cmd >>= 1;//右移1位
	}	
	for(i = 0; i < 8;i ++)//写数据
	{
		TSCLK = 0;
		TIO = dat & 0x01;//最低位先传
		TSCLK = 1;//数据总线产生上升沿，数据被DS1302读走
		dat >>= 1;//右移1位
	}
	TRST = 0;//拉低使能端，关闭读写功能
}
/*******************************************************************/
/*                                                                 */
/*  				ds1302读取数据                                */
/*                                                                 */
/*******************************************************************/
uchar read_DS1302(uchar cmd)//读取数据
{
	uchar i,dat;
	TRST = 0;//拉低使能端
	TSCLK = 0;//拉低数据总线
	TRST = 1;//使能端产生上升沿
	for(i = 0; i < 8; i ++)//传命令
	{
		TSCLK = 0;
		TIO = cmd & 0x01;//最低位先传
		TSCLK = 1;//数据总线产生上升沿，数据被DS1302读走
		cmd >>= 1;//右移1位
	}
	for(i = 0;i < 8; i ++)//读数据
	{
		TSCLK = 0;//拉低数据总线
		dat >>= 1;
		if(TIO)
		{
			dat |= 0x80;
		}
		TSCLK = 1;//数据总线产生上升沿，数据被DS1302读走
	}
	TRST = 0;//拉低使能端，关闭读写功能
	return dat;
}
/*******************************************************************/
/*                                                                 */
/*  				数据转BCD码                                    */
/*                                                                 */
/*******************************************************************/
uchar dat_to_BCD(uchar dat)//数据转BCD码
{
	uchar dat1,dat2;
	dat1 = dat / 10;
	dat2 = dat % 10;
	dat2 = dat2 + dat1 * 16;
	return dat2;
}
/*******************************************************************/
/*                                                                 */
/*  				BCD码转数据                                    */
/*                                                                 */
/*******************************************************************/
uchar BDD_to_dat(uchar dat)//BCD码转数据
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
	//测试
//	uchar i;
//	uchar sec,min,hour;
//	write_DS1302(0x8e,0);//清除写保护
//	write_DS1302(0x80,dat_to_BCD(0));//30秒
//	write_DS1302(0x82,dat_to_BCD(54));//15分
//	write_DS1302(0x84,dat_to_BCD(0));//19时
//	write_DS1302(0x8e,0x80);//开写保护
s = BDD_to_dat(read_DS1302(0x81));//读秒寄存器（进行BCD码转换）
m = BDD_to_dat(read_DS1302(0x83));//读分寄存器
h = BDD_to_dat(read_DS1302(0x85));//读时寄存器
delay(10);
write_DS1302(0x8e,0x80); //开写保护
	while(1)
	{
		//P0=0xff;
		//display();

		//测试
//		write_DS1302(0x8e,0);//清除写保护
//		s = BDD_to_dat(read_DS1302(0x81));//读秒寄存器（进行BCD码转换）
//		delay(5);
//		delay(10);
//		m = BDD_to_dat(read_DS1302(0x83));//读分寄存器
//		delay(10);
//		h = BDD_to_dat(read_DS1302(0x85));//读时寄存器
//		delay(10);
	//	write_DS1302(0x8e,0x80); //开写保护
//		delay(5);
		display();
	}
}
//定时器
void T0_int() interrupt 1
{
	TH0=(66635-50000)/256;
	TL0=(66635-50000)%256;
	//测试
	/*
		write_DS1302(0x8e,0);
		s = BDD_to_dat(read_DS1302(0x81));//读秒寄存器（进行BCD码转换）
		//delay(10);
		m = BDD_to_dat(read_DS1302(0x83));//读分寄存器
		//delay(10);
		h = BDD_to_dat(read_DS1302(0x85));//读时寄存器
		//delay(10);
		write_DS1302(0x8e,0x80); //开写保护
		//delay(10);
		*/
	//测试结束
	ms++;//到了20次说明到了1s,ms加一次是50ms
	if(ms == 20)//一秒到了
	{
		ms=0;//重新算一秒
		s++;
		LED=!LED;//灯闪一下
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