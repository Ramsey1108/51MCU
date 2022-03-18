/*******************************************************************/
/*                                                                 */
/*                                                                 */
//;*  LCD�ͺţ�TS12864A-3�������ֿ⣩������ͺ�    ������ST7920      */
//;*  MCU:STC89S52 ,����Ƶ�ʣ�11.0592MHz                              */
/*                                                                 */
/*                                                                 */                             
/*���������˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��       */
/*                                                                 */
/*******************************************************************/

//#include <reg51.h>

#include  "lcd.h"					 
//#define uchar unsigned char
//#define uint  unsigned int
/*12864�˿ڶ���*/
#define LCD_data  P0             //���ݿ�
sbit LCD_RS  =  P2^0;            //�Ĵ���ѡ������ 
sbit LCD_RW  =  P2^1;            //Һ����/д����
sbit LCD_EN  =  P2^2;            //Һ��ʹ�ܿ���
sbit LCD_PSB =  P2^3;            //��/����ʽ����
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;

uchar code dis1[] = {"WIFI����ϵͳ"};
uchar code dis2[] = {"΢��:Ramsey1108"};
uchar code dis3[] = {"ϵͳ��ʼ�����  "};
uchar code dis4[] = {"�������: �̼�Ȩ"};
//led��ʾ�Ķ���
uchar code table3[]="The ���� is: ON ";
uchar code table4[]="The �׵� is: ON ";
uchar code table5[]="The ��� is: ON ";
uchar code table6[]="The ���� is: Off";
uchar code table7[]="The �׵� is: Off";
uchar code table8[]="The ��� is: Off";
uchar code table9[]="Lihhts ShowTime!";
uchar code table2[]="ALL  Lihhts  off";

//#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
//uchar IRDIS[2];
//uchar IRCOM[4];
/*******************************************************************/
/*                                                                 */
/*  LED�����й̶���ʾ����                                          */
/*                                                                 */
/*******************************************************************/
void Ledflash(int n)
{
	uchar i;
	switch(n)
   {
      case 1:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table3[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table3[i]);
			       i++;
			     }
	  	break;       
      case 2:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table4[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table4[i]);
			       i++;
			     }
	  	break; 
      case 3:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table5[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table5[i]);
			       i++;
			     }
	  	break;      
      case 4:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table6[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table6[i]);
			       i++;
			     }
	  	break;      
      case 5:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table7[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table7[i]);
			       i++;
			     }
	  	break;          
      case 6:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table8[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table8[i]);
			       i++;
			     }
	  	break; 
	    case 7:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table9[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table9[i]);
			       i++;
			     }
	  	break;
		case 8:  
			 lcd_pos(2,0);             //������ʾλ��Ϊ��3�еĵ�1���ַ�
		     i = 0;
			    while(table2[i] != '\0')
			     {                         //��ʾ�ַ�
			       lcd_wdat(table2[i]);
			       i++;
			     }
	  	break;            
      default:   
	  break;  //���ܵ��������ݣ����䷢�͸������         
   }	
}

/*******************************************************************/
/*                                                                 */
/*  ��ʱ����                                                       */
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
/*���LCDæ״̬                                                    */
/*lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ�      */
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
/*дָ�����ݵ�LCD                                                  */
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣                             */
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
/*д��ʾ���ݵ�LCD                                                  */
/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�                               */
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
/*  LCD��ʼ���趨                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD_PSB = 1;         //���ڷ�ʽ
    
    lcd_wcmd(0x34);      //����ָ�����
    delay(5);
    lcd_wcmd(0x30);      //����ָ�����
    delay(5);
    lcd_wcmd(0x0C);      //��ʾ�����ع��
    delay(5);
    lcd_wcmd(0x01);      //���LCD����ʾ����
    delay(5);
}
/*********************************************************/
/*														 */
/* ������           									 */
/*                                                       */
/*********************************************************/


void initdisplay()
 {
    uchar i;
    delay(10);                 //��ʱ
//    wela=0;
//	dula=0; 
    lcd_init();                //��ʼ��LCD             
  
    lcd_pos(0,0);             //������ʾλ��Ϊ��һ�еĵ�1���ַ�
     i = 0;
    while(dis1[i] != '\0')
     {                         //��ʾ�ַ�
       lcd_wdat(dis1[i]);
       i++;
     }
    lcd_pos(1,0);             //������ʾλ��Ϊ�ڶ��еĵ�1���ַ�
     i = 0;
    while(dis2[i] != '\0')
     {
       lcd_wdat(dis2[i]);      //��ʾ�ַ�
       i++;
     }
 	 lcd_pos(2,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
     i = 0;
    while(dis3[i] != '\0')
     {
       lcd_wdat(dis3[i]);      //��ʾ�ַ�
       i++;
     }
	 lcd_pos(3,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
     i = 0;
    while(dis4[i] != '\0')
     {
       lcd_wdat(dis4[i]);      //��ʾ�ַ�
       i++;
     }
     //while(1);
}



/*********************************************************/
/*														 */
/* ��ʱx*0.14ms�ӳ���									 */
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
/* �趨��ʾλ��                                          */
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
   lcd_wcmd(pos);     //��ʾ��ַ
}