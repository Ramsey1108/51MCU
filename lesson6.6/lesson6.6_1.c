#include <reg52.h>
#define uint unsigned int    //宏定义
#define uchar unsigned char  //宏定义
sbit dula=P2^6;
sbit wela=P2^7;
sbit dawr=P3^6;
sbit dacs=P3^2;
sbit beep=P2^3;//蜂蜜器接口
void delay(uint z);
void main()
{
	   uchar val,flag;
	   dula=0;//接通
	   wela=0;//接通
	   dacs=0;
	   dawr=0;
	   P0=0;
	   while(1)
	   {
	   		if(flag == 0)//标志位为0的话
			{
				val=val+5;//没到255就慢慢加
				P0=val;
				if(val == 255)
				{
					flag=1;//标志位置1
					beep=0;//蜂鸣器响;
					delay(100);//延时
					beep=1;
				}
				delay(50);
			}
				else
				{
					val -=5;//到了255之后就开始减
					P0=val;
					if(val == 0)//减到0了
					{
						flag=0;//状态位变回原来的
						beep=0;//蜂鸣器响一下
						delay(100);//延时;
						beep=1;

					}
					delay(50);//延时;
				}

			
	   }
}
void delay(uint z)     //延时子函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}