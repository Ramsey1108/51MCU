
u8 datavaue=0;
u8 table0[]="51单片机蓝牙系统";
u8 table1[]="开发者：罗发新  ";
u8 table2[]="单片机系统与应用";
u8 table3[]="LED 绿灯被点亮  ";
u8 table4[]="LED 蓝灯被点亮  ";
u8 table5[]="LED 红灯被点亮  ";

void BeepOn()
{
	beep=0;
	delay(500);
	beep=1;
}
void Usart_Init()
{
	TMOD=0x20;//让T1工作在定时器模式2
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;    //启动定时器1，开始定时
	SM0=0;
	SM=1;
	REN=1;    //允许接收
	ES=1;     //接通串口中断开关
	EA=1;     //接通单片机中断开关
}
void send(u8 a)
{
	SBUF=a;
	while(!TI);
	ES=1;
	TI=0;
}
void main()
{
	Usart_Init();
	LCD_init();
	display(0x80,table0);
	display
}