#ifndef  __input_signal_c
#define  __input_signal_c

#include "stm32f10x.h"
#include "sys.h"
#include "Input_signal.h"

void getInput(void)
{
	Input_X1 = PCin(11);//�ſ����ź�
	Input_X2 = PCin(12);//�����ź�
	Input_X3 = PDin(2);//����ֹͣ�ź�
	Input_X4 = PBin(5);//��Һλ�ź�
	Input_X5 = PBin(8);//��Һλ�ź�
	Input_X6 = PBin(9);//��Һλ�ź�	
	Input_X7 = PCin(10);//��Ƶ�� X2
 	Input_X8 = PAin(12);//��Ƶ�� X1	

	SystemState.bit.X1 = ~Input_X1;
	SystemState.bit.X2 = ~Input_X2;
	SystemState.bit.X3 = ~Input_X3;
	SystemState.bit.X4 = ~Input_X4;
	SystemState.bit.X5 = ~Input_X5;
	SystemState.bit.X6 = ~Input_X6;	
 	SystemState.bit.X7 = ~Input_X7;
 	SystemState.bit.X8 = ~Input_X8;
	
//	Input_All = (Input_X1<<0) + (Input_X2<<1) + (Input_X3<<2) + (Input_X4<<3) + 
//	(Input_X5<<4) + (Input_X6<<5) + (Input_X7<<6) + (Input_X8<<7);	//����

}

#endif
