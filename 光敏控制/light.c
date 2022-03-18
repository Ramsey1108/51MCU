#include <reg51.h>			 //此文件中定义了单片机的一些特殊功能寄存器
//#include <reg52.h>
#include <intrins.h>
#include <i2c.h>
#include <stdio.h>
#include  "lcd.h"

#define uint unsigned int
#define uchar unsigned char

/*查阅pcf8591的资料可知它的都写地址如下*/
#define  WRITEADDR 0x90    //写地址
#define  READADDR  0x91    //读地址
//定义
uchar table3[]="luminance:      ";
uchar table4[]="The Led is: ON  ";
uchar table5[]="The Led is: Off ";
sbit LED=P1^0;

void Pcf8591SendByte(uchar channel)	
{   
    I2C_Start();    //开始I2C总线
    I2C_SendByte(WRITEADDR);        //发送写器件地址
    I2C_SendByte(0x40|channel);     //发送控制寄存器
    I2C_Stop();
}

uchar Pcf8591ReadByte()		//读取值
{
    uchar num;
    I2C_Start();
    I2C_SendByte(READADDR);      //发送读器件地址
    num=I2C_ReadByte();          //读取数据
    I2C_Stop();                  //结束总线
    return num;
}

void UsartInit()        //设置串口
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF4;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF4;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
	TI=1;			 //发送中断标记位，必须设置
}


void delay1s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}


void main()
{
    uint adNum;
	uint temp;
	uint temp1;
	uchar a;
    double value;
    UsartInit();
	//lcd初始化
	init();
	write_com(0x80);
	for(a=0;a<16;a++)
		{
			write_date(table3[a]);
			delay(10);
		}
	LED=1;	
    while(1)
    {	
			//
		
				 	
            Pcf8591SendByte(0);      //使用通道0   (可选择通道0-3)光敏传感器A0连接PCF8591传感器的AIN0
            /*adNum一定是0到255之间的一个数，因为pcf8591是8位的AD/DA芯片，所以输出的范围为00000000到11111111，即0到255*/
            
			adNum=Pcf8591ReadByte();   //读出数值
			value = adNum;
			value=100.0 - value*100.0/255.0; //把光敏值转换为0-100的数值，这里255.0可更改（根据实际测试value最暗值）
			temp=value;
			table3[11]=temp%100/10+'0';
			table3[12]=temp%10/1+'0';
			table3[13]='.';
			temp1=value*100+1;		
			table3[14]=temp1/10%10+'0';
			table3[15]=temp1%10+'0';
			write_com(0x80);
				for(a=0;a<16;a++)
				{
				write_date(table3[a]);
				delay(10);
				}
			if(temp<20)
			{
				LED=0;//开打
				write_com(0x80+0x40);
				for(a=0;a<16;a++)
				{
				write_date(table4[a]);
				delay(10);
				}
				
			}
			else
			{
				LED=1;//关灯
				write_com(0x80+0x40);
				for(a=0;a<16;a++)
				{
				write_date(table5[a]);
				delay(10);
				}
			}
			printf("light:");	       
			printf("%.2f\n",value);	   //打印数据到串口
			delay1s();
			
    }
}
