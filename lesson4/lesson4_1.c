 /*
 #include<reg52.h>
 #include<intrins.h>
 #define uchar unsigned char
 #define uint unsigned int
 sbit dula=P2^6;// 	�������ƶ�ѡ�������
 sbit wela=P2^7;//	��������λѡ�������
 void delayms(uint xms);
 uchar aa;//ȫ�ֱ�������ˮ��
 uchar bb,num,numdu,numwe;//�����������
 uchar code table[]={0x3f,0x06,0x5b,0x4f,
 					 0x66,0x6d,0x7d,0x07,
 					 0x7f,0x6f,0x77,0x7c,
					 0x39,0x5e,0x79,0x71,
					};

uchar code tablewe[]={0xfe,0xfd,0xfb,0xf7,
					  0xef,0xdf
 					 	
						};


 void main()
 {
 //������ʼ��
	num=0;
	aa=0;
	numdu=0;
	numwe=0;

 	//aa=0xfe;//11111110 �õ�һ����
	
//��ʱ�����ó�ʼ��
			TMOD=0x01;
		//	TH0=(66635-45872)/256;
		//	TL0=(66635-45872)%256;
		TH0=(66635-5872)/256;
		TL0=(66635-5872)%256;

//��ʱ�����ó�ʼ��


			EA=1;  //�����ж�
			ET0=1; //����ʱ��0�ж�
			TR0=1; //������ʱ��0

//����ܳ�ʼ��
					//����ѡ������
			dula=1;
			P0=table[0];//���ݳ�ʼ��Ϊ0
			dula=0;
					//�ٸ�λѡ�������������Ǽ�������
			wela=1;
			P0=0xc0;//����ȫ��
			P0=tablewe[2];
			wela=0;

	
	while(1)
		{

			if(bb==20) //bb*50ms=�ж�һ�εĴ���
			{
			 bb=0;
			 numdu++;
			 if(numdu==7)
				 {
				 	numdu=1;
				 }
			 //��ѡ
			 dula=1;
			 P0=table[numdu];
			 dula=0;
			 //λѡ
			 wela=1;
			 P0=tablewe[numwe];
			 wela=0;
			 numwe++;
			  if(numwe==6)
				 {
				 	numwe=0;
				 }
			}








	  
		// ��ˮ�ƿ���
			
			delayms(1000);
			aa=_crol_(aa,1);//��װ�õ����ƺ���
			P1=aa;
		//
	


2021��7��24��14:24:37
����:ǰ���	delayms(1000)����ʱ���ϻ��������ܵ���
��bb==40��һ˲�䲻�ܽ����жϣ�ֻ��һֱѭ�������պ�����
bb==40���ܽ����жϵ��������һֱ��0������Ҫ���жϷŵ��ж�����


		if(bb==40)	
			{
			   bb=0;
			   num++;//����ʼ��Ĭ��Ϊ0
			   if(num==16)	//�ж���û�е�16 ������ʾ����
			   {
			   		num==0;
			   }
			   //���´򿪶�ѡ
			   dula=1;
			   P0=table[num];
			   dula=0;

			}	
			
		}
 }
 void delayms(uint xms)
 {
 	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
		
 }

void time_0() interrupt 1
{
		// TH0=(66635-45872)/256;
	//	 TL0=(66635-45872)%256;
		 TH0=(66635-5872)/256;
		 TL0=(66635-5872)%256;
		 bb++;
		 
		 	if(bb==40)	
			{
			   bb=0;
			   num++;//����ʼ��Ĭ��Ϊ0
			   if(num==16)	//�ж���û�е�16 ������ʾ����
			   {
			   		num=0;
			   }
			   //���´򿪶�ѡ
			   dula=1;
			   P0=table[num];
			   dula=0;
				   
			}
			
}	
	 */
		

