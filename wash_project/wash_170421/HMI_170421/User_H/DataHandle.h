#ifndef __DataHandle_H
#define __DataHandle_H

typedef union
{
	struct
	{
		u16 X1					:	1;//��Һλ�ź�// 33
		u16 X2					:	1;//��Һλ�ź� 34
		u16 X3					:	1;// ��Һλ�ź�35
		u16 X4					:	1;// ����ֹͣ�ź�36
		u16 X5					:	1;// �����ź�37
		u16 X6					:	1;// �ſ����ź�38
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

#ifdef __DataHandle_C	  


u8 fact_temp;//ʵ���¶�
u16 fact_liquid_height;//ʵ��Һλ
u8 INVCurrent_command;//��Ƶ����ǰ����
u8 INVCurrent_state;//��Ƶ����ǰ״̬
u8 INVCurrent_fault;//��Ƶ����ǰ����
u16 INVRun_frequency;//��Ƶ������Ƶ��
u16 INVSet_frequency;//��Ƶ���趨Ƶ��
u16 INVBus_voltage;//��Ƶ��ĸ�ߵ�ѹ
u16 INVOutput_voltage;//��Ƶ�������ѹ
u16 INVOutput_current;//��Ƶ���������
void sub_DataHandle(void);
u16 SearchTemp(u16 ad_temp);

u8 input_door_switch = 0;//�ſ����ź�
u8 input_shake = 0;//�����ź�
u8 input_exigency_stop = 0;//����ֹͣ�ź�
u8 input_low_liquid = 0;//��Һλ�ź�
u8 input_middle_liquid = 0;//��Һλ�ź�
u8 input_high_liquid = 0; // ��Һλ�ź�
SystemStateWord SystemState;

void sub_InputStates(void);


#else
extern u8 fact_temp;//ʵ���¶�
extern u16 fact_liquid_height;//ʵ��Һλ
extern u8 INVCurrent_command;//��Ƶ����ǰ����
extern u8 INVCurrent_state;//��Ƶ����ǰ״̬
extern u8 INVCurrent_fault;//��Ƶ����ǰ����
extern u16 INVRun_frequency;//��Ƶ������Ƶ��
extern u16 INVSet_frequency;//��Ƶ���趨Ƶ��
extern u16 INVBus_voltage;//��Ƶ��ĸ�ߵ�ѹ
extern u16 INVOutput_voltage;//��Ƶ�������ѹ
extern u16 INVOutput_current;//��Ƶ���������
extern u16 SearchTemp(u16 ad_temp);
extern void sub_DataHandle(void);

extern u8 input_door_switch;//�ſ����ź�
extern u8 input_shake;//�����ź�
extern u8 input_exigency_stop;//����ֹͣ�ź�
extern u8 input_low_liquid;//��Һλ�ź�
extern u8 input_middle_liquid;//��Һλ�ź�
extern u8 input_high_liquid; // ��Һλ�ź�
extern SystemStateWord SystemState;

extern void sub_InputStates(void);

#endif
#endif

