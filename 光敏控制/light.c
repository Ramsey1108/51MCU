#include <reg51.h>			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
//#include <reg52.h>
#include <intrins.h>
#include <i2c.h>
#include <stdio.h>
#include  "lcd.h"

#define uint unsigned int
#define uchar unsigned char

/*����pcf8591�����Ͽ�֪���Ķ�д��ַ����*/
#define  WRITEADDR 0x90    //д��ַ
#define  READADDR  0x91    //����ַ
//����
uchar table3[]="luminance:      ";
uchar table4[]="The Led is: ON  ";
uchar table5[]="The Led is: Off ";
sbit LED=P1^0;

void Pcf8591SendByte(uchar channel)	
{   
    I2C_Start();    //��ʼI2C����
    I2C_SendByte(WRITEADDR);        //����д������ַ
    I2C_SendByte(0x40|channel);     //���Ϳ��ƼĴ���
    I2C_Stop();
}

uchar Pcf8591ReadByte()		//��ȡֵ
{
    uchar num;
    I2C_Start();
    I2C_SendByte(READADDR);      //���Ͷ�������ַ
    num=I2C_ReadByte();          //��ȡ����
    I2C_Stop();                  //��������
    return num;
}

void UsartInit()        //���ô���
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF4;				//��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF4;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					//�򿪼�����
	TI=1;			 //�����жϱ��λ����������
}


void delay1s(void)   //��� 0us
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
	//lcd��ʼ��
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
		
				 	
            Pcf8591SendByte(0);      //ʹ��ͨ��0   (��ѡ��ͨ��0-3)����������A0����PCF8591��������AIN0
            /*adNumһ����0��255֮���һ��������Ϊpcf8591��8λ��AD/DAоƬ����������ķ�ΧΪ00000000��11111111����0��255*/
            
			adNum=Pcf8591ReadByte();   //������ֵ
			value = adNum;
			value=100.0 - value*100.0/255.0; //�ѹ���ֵת��Ϊ0-100����ֵ������255.0�ɸ��ģ�����ʵ�ʲ���value�ֵ��
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
				LED=0;//����
				write_com(0x80+0x40);
				for(a=0;a<16;a++)
				{
				write_date(table4[a]);
				delay(10);
				}
				
			}
			else
			{
				LED=1;//�ص�
				write_com(0x80+0x40);
				for(a=0;a<16;a++)
				{
				write_date(table5[a]);
				delay(10);
				}
			}
			printf("light:");	       
			printf("%.2f\n",value);	   //��ӡ���ݵ�����
			delay1s();
			
    }
}
