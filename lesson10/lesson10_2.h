#define uint unsigned int    //�궨��
#define uchar unsigned char  //�궨��
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

void init_24c02()//���߳�ʼ����ȫ������
{
	scl=1;
	delay();
	scl=1;
	delay();	
}


void start()//��ʼ�ź�:scl�ڸߵ�ƽ�ڼ䣬sdaһ���½����ź�
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
}

void stop()	//ֹͣ�źţ�scl�ߵ�ƽ�ڼ� sdaһ���������ź�
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();	
}

void respons() //scl�ߵ�ƽ�ڼ䣬sda���豸��Ϊ�͵�ƽ
{
	uchar i=0;
	scl=1;
	delay();
	while((sda == 1) && (i<250))//��һ��ʱ��ûӦ�����Ѿ�Ӧ��
		i++;
	scl=0;
	delay();
}

void write_byte(uchar date)
{
	uchar i,temp;//temp�м����
	temp=date;
	for(i=0;i<8;i++)//����һλ�����λ�Ƶ�PSW�Ĵ�����CYλ��Ȼ��CY��ֵ��sda��scl��0��1���������ͳ�ȥ
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

uchar read_byte()//����������ʱ����k����;��k���ƻ����������ǵ�λ��0����������
//ͨ�� scl�Ӹߵ��͵������ȡ
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













