

void delay(u16 t)
{
	u8 i;
	while(t--)
		for(i=19;i>0;i--);
}
void Write_cmd(u8 cmd)
{
	RS=0;
	RW=0;
	P0=cmd;
	delay(5);
	E=1;
	delay(10);
	E=0;
}
void Write_data(u8 dat)
{
	RS=1;
	RW=0;
	P0=dat;
	delay(5);
	E=1;
	delay(10);
	E=0;
}
void LCD_init()
{
	delay(400);
	Wtite_cma(0x30);
	delay(100);
	Write_cmd(0x30);
	delay(37);
	Wtite_cmd(0x30);
	delay(10);
	Write_cmd(0x0c);
	delay(10);
	Write_cmd(0x01):
	delay(100);
	Write_cmd(0x06);
}
void display(u8 y,u8 a[16])
{
	u8 i;
	Write_cmd(y);
	for(i=0;i<16;i++)
	{
		Write_data(a[i]);
	}
}