 #include<reg52.h>
 #define uchar unsigned char
 #define uint unsigned int
 sbit dula=P2^6;// 	�������ƶ�ѡ�������
 sbit wela=P2^7;//	��������λѡ�������
 uchar num,tt;
 uchar code table[]={0x3f,0x06,0x5b,0x4f,
 					 0x66,0x6d,0x7d,0x07,
 					 0x7f,0x6f,0x77,0x7c,
					 0x39,0x5e,0x79,0x71,
					};
void delayms(unit);
void main()
{
		num=0;
		tt=0;
		//�жϿ���
		TMOD=0x01;
		TH0=(66635-45872)/256;
		TL0=(66635-45872)%256;

		//
		EA=1;
		ET0=1;
		TR0=1;
		//�ж� 
		 
		wela=1;
	//	P0=0xc0;//����ȫ��
		P0=0xea;//1 3 5�� �����ǵ�һλ11101010
		wela=0;
		//����ѡ������
		dula=1;
		P0=0x3f;
		dula=0;
		while(1)
	{
		
		if(tt==20)
		   {
				tt=0;
				num++;
				if(num==10)
				num=0;
				dula=1;
				P0=table[num];
				dula=0;	
			}
	}
}
/*
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
*/
void exter0() interrupt 1
{
	TH0=(66635-45872)/256;
	TL0=(66635-45872)%256;
	tt++;
}









