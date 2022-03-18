#define uint unsigned int    //宏定义
#define uchar unsigned char  //宏定义
bit write =0;
sbit sda=P2^0;
sbit scl=P2^1;


void delay(){  ;  ; }
void start();
void init_24c02();
void stop();
void respons();
void write_byte(uchar date);
uchar read_byte();
void write_add(uchar address,uchar date);
uchar read_add(uchar address) ;

void init_24c02()//总线初始化：全部拉高
{
	scl=1;
	delay();
	scl=1;
	delay();	
}


void start()//开始信号:scl在高电平期间，sda一个下降沿信号
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
}

void stop()	//停止信号：scl高电平期间 sda一个上升沿信号
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();	
}

void respons() //scl高电平期间，sda被设备拉为低电平
{
	uchar i=0;
	scl=1;
	delay();
	while((sda == 1) && (i<250))//在一定时间没应答当做已经应答
		i++;
	scl=0;
	delay();
}

void write_byte(uchar date)
{
	uchar i,temp;//temp中间变量
	temp=date;
	for(i=0;i<8;i++)//左移一位将最高位移到PSW寄存器的CY位中然后将CY赋值给sda在scl从0到1的跳变下送出去
	{
		temp=temp<<1;
		scl=0;
		delay();
		sda=CY;			
		delay();
		scl=1;
		delay();
	}
	scl=0;
	delay();
	sda=1;
	delay();
	
}

uchar read_byte()//读数据用临时变量k接收;将k左移或运算左移是低位补0；接收数据
//通过 scl从高到低的跳变读取
{
	uchar i,k;
	scl=0;
	delay();
	sda=1;
	delay();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay();
		k=(k<<1) | sda;
		scl=0;
		delay();
	}
	
	return k;
}
void write_add(uchar address,uchar date)
{
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	write_byte(date);
	respons();
	stop();
}

uchar read_add(uchar address)
{
	uchar date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	stop();
	return date;
}













