#ifndef WENDU_H 			//���Ϊ	if not define led.h
#define WENDU_H 			//���û�ж��� led.h ,����Ͷ���һ�� led.h
 
#include "reg52.h"		//����  led,c ����Ҫ�õ� 51��Ƭ���Ĵ���	P1��
                      // �����������	51 ��Ƭ����ͷ�ļ�
//#include "intrins.h"		// ѭ����λ�õ�
#define	uchar unsigned char
#define	uint unsigned int	// ��Щ�궨�嶼������ͷ�ļ� .h �ﶨ��
#define MotorData P3                    //����������ƽӿڶ���
extern uchar phasecw[8];
extern uchar phaseccw[8];
void Delay_xms(uint x);
//˳ʱ��ת��
void MotorCW(void);
//��ʱ��ת��
void MotorCCW(void);
//ֹͣת��
void MotorStop(void);
#endif	// �������
