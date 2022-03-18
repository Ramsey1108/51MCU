/*******************************************************************/
/*                                                                 */
/*                                                                 */
//;*  LCD型号：TS12864A-3（带汉字库）或兼容型号    控制器ST7920      */
//;*  MCU:STC89S52 ,晶体频率：11.0592MHz                              */
/*                                                                 */
/*                                                                 */                             
/*【声明】此程序仅用于学习与参考，引用请注明版权和作者信息！       */
/*                                                                 */
/*******************************************************************/

//#include <reg51.h>

#include  "lcd.h"					 
//#define uchar unsigned char
//#define uint  unsigned int
/*12864端口定义*/
#define LCD_data  P0             //数据口
sbit LCD_RS  =  P2^0;            //寄存器选择输入 
sbit LCD_RW  =  P2^1;            //液晶读/写控制
sbit LCD_EN  =  P2^2;            //液晶使能控制
sbit LCD_PSB =  P2^3;            //串/并方式控制
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;

uchar code dis1[] = {"WIFI控制系统"};
uchar code dis2[] = {"微信:Ramsey1108"};
uchar code dis3[] = {"系统初始化完成  "};
uchar code dis4[] = {"开发设计: 蔡嘉权"};
//led显示的定义
uchar code table3[]="The 蓝灯 is: ON ";
uchar code table4[]="The 白灯 is: ON ";
uchar code table5[]="The 红灯 is: ON ";
uchar code table6[]="The 蓝灯 is: Off";
uchar code table7[]="The 白灯 is: Off";
uchar code table8[]="The 红灯 is: Off";
uchar code table9[]="Lihhts ShowTime!";
uchar code table2[]="ALL  Lihhts  off";

//#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
//uchar IRDIS[2];
//uchar IRCOM[4];
/*******************************************************************/
/*                                                                 */
/*  LED第三行固定显示函数                                          */
/*                                                                 */
/*******************************************************************/
void Ledflash(int n)
{
	uchar i;
	switch(n)
   {
      case 1:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table3[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table3[i]);
			       i++;
			     }
	  	break;       
      case 2:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table4[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table4[i]);
			       i++;
			     }
	  	break; 
      case 3:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table5[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table5[i]);
			       i++;
			     }
	  	break;      
      case 4:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table6[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table6[i]);
			       i++;
			     }
	  	break;      
      case 5:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table7[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table7[i]);
			       i++;
			     }
	  	break;          
      case 6:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table8[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table8[i]);
			       i++;
			     }
	  	break; 
	    case 7:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table9[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table9[i]);
			       i++;
			     }
	  	break;
		case 8:  
			 lcd_pos(2,0);             //设置显示位置为第3行的第1个字符
		     i = 0;
			    while(table2[i] != '\0')
			     {                         //显示字符
			       lcd_wdat(table2[i]);
			       i++;
			     }
	  	break;            
      default:   
	  break;  //接受到其它数据，将其发送给计算机         
   }	
}

/*******************************************************************/
/*                                                                 */
/*  延时函数                                                       */
/*                                                                 */
/*******************************************************************/
void delay(int ms)
{
    while(ms--)
	{
      uchar i;
	  for(i=0;i<250;i++)  
	   {
	    _nop_();			   
		_nop_();
		_nop_();
		_nop_();
	   }
	}
}		
/*******************************************************************/
/*                                                                 */
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
/*                                                                 */
/*******************************************************************/
bit lcd_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }
/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/
void lcd_wcmd(uchar cmd)
{                          
   while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD_PSB = 1;         //并口方式
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
}
/*********************************************************/
/*														 */
/* 主程序           									 */
/*                                                       */
/*********************************************************/


void initdisplay()
 {
    uchar i;
    delay(10);                 //延时
//    wela=0;
//	dula=0; 
    lcd_init();                //初始化LCD             
  
    lcd_pos(0,0);             //设置显示位置为第一行的第1个字符
     i = 0;
    while(dis1[i] != '\0')
     {                         //显示字符
       lcd_wdat(dis1[i]);
       i++;
     }
    lcd_pos(1,0);             //设置显示位置为第二行的第1个字符
     i = 0;
    while(dis2[i] != '\0')
     {
       lcd_wdat(dis2[i]);      //显示字符
       i++;
     }
 	 lcd_pos(2,0);             //设置显示位置为第三行的第1个字符
     i = 0;
    while(dis3[i] != '\0')
     {
       lcd_wdat(dis3[i]);      //显示字符
       i++;
     }
	 lcd_pos(3,0);             //设置显示位置为第四行的第1个字符
     i = 0;
    while(dis4[i] != '\0')
     {
       lcd_wdat(dis4[i]);      //显示字符
       i++;
     }
     //while(1);
}



/*********************************************************/
/*														 */
/* 延时x*0.14ms子程序									 */
/*                                                       */
/*********************************************************/

void delay0(uchar x)    //x*0.14MS
{
  uchar i;
  while(x--)
 {
  for (i = 0; i<13; i++) {}
 }
}
/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   lcd_wcmd(pos);     //显示地址
}