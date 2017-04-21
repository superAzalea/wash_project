#ifndef __INPUT_SIGNAL_H

#define __INPUT_SIGNAL_H

typedef union
{
	struct
	{
		u16 X1					:	1;//�ſ����ź�
		u16 X2					:	1;//�����ź�
		u16 X3					:	1;//����ֹͣ�ź�
		u16 X4					:	1;//��Һλ�ź�
		u16 X5					:	1;//��Һλ�ź�
		u16 X6					:	1;//��Һλ�ź�
		u16 X7					:	1;// 39
		u16 X8					:	1;// 40
		
		u16 SystemSleep			:	1;//ϵͳ����
		u16 PhaseMiss			:	1;//����ȱ�� 26
		u16 PhaseSequenceError	:	1;//������� 27
		u16 ElcInv_CommError	:	1;//��λ�����Ƶ��ͨѶ���� 28
		u16 HmiElc_CommError	:	1;//��λ������λ��ͨѶ���� 29
		u16 bit5				:	1;// 30
		u16 bit6				:	1;// 31
		u16 bit7				:	1;// 32
		
		


	}bit;
	u16 all;
}SystemStateWord;

#ifdef  __input_signal_c
SystemStateWord SystemState;//ȫ��ϵͳ������

unsigned char Input_X1 = 0,Input_X2 = 0,Input_X3 = 0,Input_X4 = 0,Input_X5 = 0,Input_X6 = 0,Input_X7 = 0,Input_X8 = 0;
unsigned int Input_All = 0;

void getInput(void);

#else 
extern unsigned char Input_X1,Input_X2,Input_X3 ,Input_X4 ,Input_X5 ,Input_X6 ,Input_X7 ,Input_X8 ;
extern unsigned int Input_All;

extern void getInput(void);
extern SystemStateWord SystemState;//ȫ��ϵͳ������

#endif
#endif

