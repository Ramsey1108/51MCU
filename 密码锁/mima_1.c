
u8 datavaue=0;
u8 table0[]="51��Ƭ������ϵͳ";
u8 table1[]="�����ߣ��޷���  ";
u8 table2[]="��Ƭ��ϵͳ��Ӧ��";
u8 table3[]="LED �̵Ʊ�����  ";
u8 table4[]="LED ���Ʊ�����  ";
u8 table5[]="LED ��Ʊ�����  ";

void BeepOn()
{
	beep=0;
	delay(500);
	beep=1;
}
void Usart_Init()
{
	TMOD=0x20;//��T1�����ڶ�ʱ��ģʽ2
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;    //������ʱ��1����ʼ��ʱ
	SM0=0;
	SM=1;
	REN=1;    //�������
	ES=1;     //��ͨ�����жϿ���
	EA=1;     //��ͨ��Ƭ���жϿ���
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