#include  "led.h"
#include "reg52.h"
sbit BlueLed = P1^0;
sbit YellowLed = P1^1;
sbit WhileLed = P1^2;
void BlueLedLight()
{
	 BlueLed=0;
	 YellowLed=1;
	 WhileLed=1;
}
void YellowLedLight()
{
	 BlueLed=1;
	 YellowLed=0;
	 WhileLed=1;
}
void WhileLedLight()
{
	 BlueLed=1;
	 YellowLed=1;
	 WhileLed=0;
}