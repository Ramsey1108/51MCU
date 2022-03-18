/*********************************************************************
题目：基于51单片机的微信消息推送，post模式
内容：通过MCU上位机对ESP8266wifi模块的控制和设置，实现stc89c51向微信推送消息
注意：晶振一定是11.0592MHz。
关于UID：在巴法云注册登陆，即可看到自己UID，推送微信消息，需要手机绑定微信，bemfa.com在控制台进行绑定即可。
QQ交流群：824273231
巴法云官网：bemfa.com
时间：2020/04/02
注意：新买的ESP8266-01默认是115200波特率，需要利用串口调试助手更改esp8266波特率为9600
更改方法：USB转串口板连接到ESP8266，波特率115200，发送  AT+UART=9600,8,1,0,0   //末尾有回车换行
USB转串口板接线方法：tx--rx ,rx--tx,gnd-gnd,3.3v--3.3v,EN--3.3v //esp8266--USB转串口板
官方文档见官网：http://www.cloud.bemfa.com/docs/#/?id=_51-tcp%e5%88%9b%e5%ae%a2%e4%ba%91

控制LED，控制引脚P10
********************************************************************/
#include <reg52.h>  
#include <stdio.h>
#include <string.h>//包含头文件
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
//测试继电器
sbit IN1 = P2^0;
//开始定义LED
//uchar table2[]="l";
uchar code table3[]="luminance:      ";
uchar code table4[]="The Led is: ON  ";
uchar code table5[]="The Led is: Off ";
uchar code table6[]="The Led is: ON  ";
uchar code table7[]="The Led is: ON  ";
uchar code table8[]="The Led is: ON  ";
//结束
unsigned char code LEDTAB[] =               //--- 多样花灯的显示代码表 ---
{
  0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,0xfc,0xf3,0xcf,0x3f,0xfa,0xf5,0xaf,0x5f,
  0xf0,0x0f,0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe,0x3f,0xcf,0xf3,0xfc,
  0x5f,0xaf,0xf5,0xfa,0x0f,0xf0,
};
//sbit LED1=P1^0;//黄灯
//sbit LED2=P1^5;//红灯
//sbit LED3=P1^2;//蓝灯

//需要修改的部分
#define Ssid  "Ramsey"											//WIFI名称，，修改为自己路由器的WIFI名称，好像不支持中文
#define PassWord  "11223344"              //WIFI密码，修改为自己路由器的
#define Uid  "d6b1cbc7d2a2103af9d33b83b2bf652c" //巴法云UID密钥，控制台获取
#define TopicLed  "Light001" //巴法云控制台创建，名称自定义，app订阅主题要和这个推送主题一致

/*****************相关变量**************/
uchar Receive;  //接收到的字节
uchar i,i2,count; //定时器所用变量
uint n; 					//接收到字节的个数
uchar flag=0; //标志位，检查是否有数据通过串口发到MCU
uchar connected = 0;  //标志位，检查是否已连接服务器
uchar Recive_table[100]; //用于接收wifi模块反馈到MCU上的数据

/*******************************************************************
名称：延时函数
作用：毫秒级延时，微妙级延时函数，为数据收发完成作等待.......
********************************************************************/
void ms_delay(uint t)
{
      uint i,j;
      for(i=t;i>0;i--)
       for(j=110;j>0;j--);
}

void us_delay(uchar t)
{
      while(t--);
}



/********************************************************************
名称：波特率发生器函数
作用：波特率发生器可以是T1定时器实现，也可以是MCU内部独立的波特率发生器，
各自不同的载入值计算式，具体根据寄存器相关设置来参考计算，以实现
异步串行通讯。（经测试，两种设置方式均可用，可任选一种。）
********************************************************************/
void Uart_Init()//使用定时器1作为波特率发生器（STC89C52、STC89C51、AT89C51或者STC12C560S2等均可）
{
	SCON=0x50;     //设置为串行口以方式1工作，8位异步通讯,允许接收中断。
	//一帧信息为10位，1位起始位，8位数据位（低位在先），1位停止位。
	PCON=0x80;     //SMOD波特率选择位为1，SMOD=1.
	TMOD=0x21;    //设置定时器1为波特率发生器，工作在模式2，8位自动装载
	TH1=0xFA ;//波特率9600 ，TH1=256-FOSC/16/12/波特率
	TL1=TH1;
	EA=1;                            //总中断打开
	ES=0;                             //关闭串口中断
	TR1=1;                     //启动定时器1

	TH0=0xD8;                  //定时10ms
	TL0=0xF0;
	ET0=1;
	TR0=1;
}




/********************************************************************
名称：串口发送函数
功能：MCU向其他与其连接的设备发送数据（此处是无线WIFI模块ESP8266)
********************************************************************/
void Send_Uart(uchar value)
{
      ES=0;         //关闭串口中断
      TI=0;         //清发送完毕中断请求标志位
      SBUF=value;     //发送
      while(TI==0);    //等待发送完毕
      TI=0;         //清发送完毕中断请求标志位
      ES=1;         //允许串口中断
}
/********************************************************************
名称：串口发送数据
作用: 通过串口发送指令到WIFI模块，以便可以实现无线接入和控制，带回车换行
********************************************************************/
void SerialSend(uchar *puf) // 数组指针*puf指向字符串数组               
{

      while(*puf!='\0')    //遇到空格跳出循环
      {
           Send_Uart(*puf);  //向WIFI模块发送控制指令。
           us_delay(5);
           puf++;      
      }
      us_delay(5);
      Send_Uart('\r');//回车
      us_delay(5);
      Send_Uart('\n');   //换行
}   

/********************************************************************
名称：串口发送数据
作用: 通过串口发送指令到WIFI模块，不带回车换行
********************************************************************/
void SerialSend_byte(uchar *puf) // 数组指针*puf指向字符串数组               
{

      while(*puf!='\0')    //遇到空格跳出循环
      {
           Send_Uart(*puf);  //向WIFI模块发送控制指令。
           us_delay(5);
           puf++;      
      }
}   


/********************************************************************
名称：心跳函数
作用：发送心跳。如果一分钟不发送心跳，服务器就会认为设备掉线，故建议30s发送一次心跳
在中断1中调用，和发送数据函数，留一个就行，发送数据也相当于心跳
********************************************************************/
void Ping(void)
{	
  SerialSend("cmd=0&msg=ping"); //发送心跳
}
/********************************************************************
名称：流水灯函数
作用：亮起来
********************************************************************/
void WaterLamp()
{
	uint k;
   for(k=0;k<45;k++)
   {
   		P1 = LEDTAB[k];
		ms_delay(100);	
   }  	
}

/********************************************************************
名称：主函数
作用：程序的执行入口
********************************************************************/
void main()
{   
		memset(Recive_table,'\0',sizeof Recive_table);//重置数组
		Uart_Init();//使用独立的波特率发生器


		ms_delay(1000);
		SerialSend("AT+RST");     //重新启动wifi模块
		ms_delay(1000);
		SerialSend("AT");     //重新启动wifi模块
		ms_delay(1000);
		SerialSend("AT+CWMODE=3"); //设置路由器模式 1 station模式 2 AP路由器模式 3 station+AP混合模式
		ms_delay(1000);
		SerialSend("AT+CWJAP=\""Ssid"\",\""PassWord"\"");//设置模块SSID:WIFI, PWD:密码 及安全类型加密模式（WPA2-PSK）
		ms_delay(8000);
		SerialSend("AT+CIPMODE=1"); //开启透明传输模式
		ms_delay(1000);
		SerialSend("AT+CIPSTART=\"TCP\",\"bemfa.com\",8344");  // 连接服务器和端口
		ms_delay(1000);
		SerialSend("AT+CIPSEND"); //进入透传模式，下面发的都会无条件传输
		ms_delay(1000);
		
	
	  //发送订阅指令，原格式为：
		//cmd=1&uid=***UID***&topic=***Topic***
		SerialSend_byte("cmd=1&uid=");
		SerialSend_byte(Uid);
		SerialSend_byte("&topic=");
		SerialSend_byte(TopicLed); //订阅控制灯的主题
		us_delay(5);
		Send_Uart('\r');//回车
		us_delay(5);
		Send_Uart('\n');   //换行
		
		
		connected = 1; //表示连接成功，可以发送数据了

		//测试
		//P1=0;
		ms_delay(1000);
		IN1=0;  //灯灭
		while(1)
		{        
			
				if(flag == 1){
					
					//实际收到到指令：cmd=2&uid=4d9ec352e0376f2110a0c601a2857225&topic=light002&msg=on
					//字符串匹配，当检测到字符串msg=on时，执行开灯 
					//如果有多个主题，可以加上主题名字以区分不同设备控制命令，如: if(strstr(Recive_table,"light002&msg=on"))
					if(strstr(Recive_table,"&msg=on")){ 
								//LED1=0;   //打开灯，P10引脚置高电平
								//LED2=0;
								//LED3=0;
								//P1=0Xfe;
								IN1=1;  //灯亮
								ms_delay(50);
								WaterLamp();
					}else if(strstr(Recive_table,"&msg=off")){ ////当检测到字符串msg=off时，执行关灯
								P1=0xff;	//关闭灯，P10引脚置低电平
								ms_delay(50);
								IN1=0;  //灯灭
					}else if(strstr(Recive_table,"ERROR")){ //如果掉线或网络故障，重新连接
									connected = 1;
									SerialSend("AT+CIPMODE=1"); //开启透明传输模式
									ms_delay(1000);
									SerialSend("AT+CIPSTART=\"TCP\",\"bemfa.com\",8344");  // 连接服务器和端口
									ms_delay(1000);
									SerialSend("AT+CIPSEND"); //进入透传模式，下面发的都会无条件传输
									ms_delay(1000);
						
									//发送订阅指令，原格式为：
									//cmd=1&uid=***UID***&topic=***Topic***
									SerialSend_byte("cmd=1&uid=");
									SerialSend_byte(Uid);
									SerialSend_byte("&topic=");
									SerialSend_byte(TopicLed);
									us_delay(5);
									Send_Uart('\r');//回车
									us_delay(5);
									Send_Uart('\n');   //换行
									connected = 1; //表示连接成功，可以发送数据了

					}
					memset(Recive_table,'\0',sizeof Recive_table);//重置数组
					flag=0;
					
				}
      }         
}

/*********************************************************************
名称：串行通讯中断
作用：发送或接收结束后进入该函数，对相应的标志位软件清0，实现模块对数
         据正常的收发。


********************************************************************/

void Uart_Interrupt() interrupt 4        
{

      if(RI==1)
      {
           RI=0;
           Receive=SBUF;        //MCU接收wifi模块反馈回来的数据
           Recive_table[i]=Receive;      
           i++;         
           if((Receive =='\n')){
						i=0;
						flag = 1;
				}
			}
      else TI=0;   
		
}

//定时发送心跳，或发送传感器数据
//心跳建议30s发一次，一分钟不发数据，服务器会认为设备掉线
void timer0isr(void) interrupt 1  
{
        TH0=0xD8;
        TL0=0xF0;
       	i2++;
        if(i2==100)
        {
            i2=0;
						count++;
						if(count>=30) //30秒，可自行修改
						{
							if(connected == 1){
										Ping();   //发送心跳
							}

							count=0;
						}               
        }	
}
