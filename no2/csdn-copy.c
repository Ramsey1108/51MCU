#include<reg52.h>
unsigned int i = 0;			//无符号整型 范围0-65535
unsigned char cnt = 0;  //无符号字符型 范围0-255，省字节，所以用这个，无符号整型也可以的
sbit beep = P2^3;				//蜂鸣器
void main()
{
	while(1)				//大循环
	{
			for(cnt=0;cnt<8;cnt++) //最多移动7位，加上不移动，总共八次
		{
			P1 = ~(0x01<<cnt);			//左移cnt位,然后取反，刚好达到效果
			beep = ~beep;					//蜂鸣器发滴滴声
			for(i=0;i<30000;i++);	//延时
		
		}
	}

}
