 /*
 #include<reg52.h>
 #include<intrins.h>
 #define uchar unsigned char
 #define uint unsigned int
 sbit dula=P2^6;// 	声明控制段选的锁存端
 sbit wela=P2^7;//	声明控制位选的锁存端
 void delayms(uint xms);
 uchar aa;//全局变量给流水灯
 uchar bb,num,numdu,numwe;//变量给数码管
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
 //变量初始化
	num=0;
	aa=0;
	numdu=0;
	numwe=0;

 	//aa=0xfe;//11111110 让等一个亮
	
//定时器设置初始化
			TMOD=0x01;
		//	TH0=(66635-45872)/256;
		//	TL0=(66635-45872)%256;
		TH0=(66635-5872)/256;
		TL0=(66635-5872)%256;

//定时器设置初始化


			EA=1;  //开总中断
			ET0=1; //开定时器0中断
			TR0=1; //启动定时器0

//数码管初始化
					//给段选先送数
			dula=1;
			P0=table[0];//内容初始化为0
			dula=0;
					//再给位选先送数（控制那几个亮）
			wela=1;
			P0=0xc0;//六个全亮
			P0=tablewe[2];
			wela=0;

	
	while(1)
		{

			if(bb==20) //bb*50ms=中断一次的次数
			{
			 bb=0;
			 numdu++;
			 if(numdu==7)
				 {
				 	numdu=1;
				 }
			 //段选
			 dula=1;
			 P0=table[numdu];
			 dula=0;
			 //位选
			 wela=1;
			 P0=tablewe[numwe];
			 wela=0;
			 numwe++;
			  if(numwe==6)
				 {
				 	numwe=0;
				 }
			}








	  
		// 流水灯控制
			
			delayms(1000);
			aa=_crol_(aa,1);//封装好的左移函数
			P1=aa;
		//
	


2021年7月24日14:24:37
问题:前面的	delayms(1000)函数时间上会有误差，可能导致
在bb==40那一瞬间不能进入判断，只能一直循环，到刚好碰巧
bb==40才能进入判断导致数码管一直是0，所以要把判断放到中断里面


		if(bb==40)	
			{
			   bb=0;
			   num++;//不初始化默认为0
			   if(num==16)	//判断有没有到16 多了显示不了
			   {
			   		num==0;
			   }
			   //重新打开段选
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
			   num++;//不初始化默认为0
			   if(num==16)	//判断有没有到16 多了显示不了
			   {
			   		num=0;
			   }
			   //重新打开段选
			   dula=1;
			   P0=table[num];
			   dula=0;
				   
			}
			
}	
	 */
		

