#ifndef __INVERTER_H
#define __INVERTER_H

#ifdef __INVERTER_C
unsigned char HmiCmd_Run = 0;			//��λ�������� ����
//unsigned char SystemState_Run = 0;		//ϵͳ״̬�� ����
unsigned char INV_fault_code;
void Inverter_control(void);
//void sub_fun(void);
#else
extern unsigned char HmiCmd_Run;			//��λ�������� ����
//extern unsigned char SystemState_Run = 0;		//ϵͳ״̬�� ����
extern unsigned char INV_fault_code;
extern void Inverter_control(void);
//extern void sub_fun(void);

#endif
#endif
