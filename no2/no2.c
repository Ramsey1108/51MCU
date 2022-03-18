/*
#include <reg52.h>
#define unit unsigned int
sbit D1=P1^0;
void delay1s();

//后面的P1一定需要大写 系统规定

void main()
{
	while(1)
	{
		D1=0;
		delay1s();
		D1=1;
		delay1s();
	}
	
}
void delay1s()
{
	unit i,j;
	for(i=500;i>0;i--)
		for(j=110;j>0;j--);
}
*/