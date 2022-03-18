 /*
 #include<reg52.h>
 #define uchar unsigned char
 #define uint unsigned int
 sbit dula=P2^6;// 	声明控制段选的锁存端
 sbit wela=P2^7;//	声明控制位选的锁存端
 uchar num;
 uchar code table[]={0x3f,0x06,0x5b,0x4f,
 					 0x66,0x6d,0x7d,0x07,
 					 0x7f,0x6f,0x77,0x7c,
					 0x39,0x5e,0x79,0x71,
					};
void delayms(unit);
void main()
{
			   
		wela=1;
	//	P0=0xc0;//六个全亮
		P0=0xea;//1 3 5亮 从左是第一位11101010
		wela=0;
		while(1)
		{
			for(num=0;num<10;num++)
			{
				dula=1;
				P0=table[num];
				dula=0;
				delayms(500);
			}
		}
}
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}			
*/









