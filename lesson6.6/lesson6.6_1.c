#include <reg52.h>
#define uint unsigned int    //�궨��
#define uchar unsigned char  //�궨��
sbit dula=P2^6;
sbit wela=P2^7;
sbit dawr=P3^6;
sbit dacs=P3^2;
sbit beep=P2^3;//�������ӿ�
void delay(uint z);
void main()
{
	   uchar val,flag;
	   dula=0;//��ͨ
	   wela=0;//��ͨ
	   dacs=0;
	   dawr=0;
	   P0=0;
	   while(1)
	   {
	   		if(flag == 0)//��־λΪ0�Ļ�
			{
				val=val+5;//û��255��������
				P0=val;
				if(val == 255)
				{
					flag=1;//��־λ��1
					beep=0;//��������;
					delay(100);//��ʱ
					beep=1;
				}
				delay(50);
			}
				else
				{
					val -=5;//����255֮��Ϳ�ʼ��
					P0=val;
					if(val == 0)//����0��
					{
						flag=0;//״̬λ���ԭ����
						beep=0;//��������һ��
						delay(100);//��ʱ;
						beep=1;

					}
					delay(50);//��ʱ;
				}

			
	   }
}
void delay(uint z)     //��ʱ�Ӻ���
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}