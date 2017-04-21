#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"	 

#define MBS_BufSize 100
#define USART_BufSize 100

//ģʽ����
#define RS485_TX_EN		PBout(0)	//485ģʽ����.0,����;1,����.
//����봮���жϽ��գ��벻Ҫע�����º궨��
#define EN_USART2_RX 	1			//0,������;1,����.
#define EN_USART1_RX 	1			//0,������;1,����.

#ifdef __RS485_C

u8 localAddr = 1;	//��Ƭ�����ư�ĵ�ַ
u8 receCount = 0;	//���յ����ֽڸ���
u8 sendPosi = 0;	//����λ��
//���յ������ݳ���
u8 RS485_RX_CNT=0;   
u8 RS485_TX_CNT = 0;   			//���͵����ݳ���
u8 flag_error_usart = 0;
u8 counter_error_usart = 0;
u16 acce_time;
u16 dece_time;
u16 frequency;
u8  fault_clear;

u16 MBS_HoldRegs[MBS_BufSize];
u16 modbus_check[MBS_BufSize];
u8 RS485_TX_BUF[USART_BufSize];
u8 RS485_RX_BUF[USART_BufSize];  	//���ջ���,���64���ֽ�.

void RS485_Init(u32 bound);
//void RS485_Send_Data(u8 *buf,u8 len);
void modbus_dataUnpack_slave(void);
void readRegisters(void);
void presetMultipleRegister(void);
void preset_error(u8,u8);
 //--------------------------- 
 
#else

extern u8 localAddr;	//��Ƭ�����ư�ĵ�ַ
extern u8 receCount;	//���յ����ֽڸ���
extern u8 sendPosi;	//����λ��
//���յ������ݳ���
extern u8 RS485_RX_CNT;   
extern u8 RS485_TX_CNT ;   			//���͵����ݳ���
extern u8 flag_error_usart;
extern u8 counter_error_usart;
extern u16 acce_time;
extern u16 dece_time;

extern u16 frequency;
extern u8 fault_clear;
extern u16 MBS_HoldRegs[MBS_BufSize];
extern u16 modbus_check[MBS_BufSize];
extern u8 RS485_TX_BUF[USART_BufSize];
extern u8 RS485_RX_BUF[USART_BufSize];  	//���ջ���,���64���ֽ�.

extern void RS485_Init(u32 bound);
//extern void RS485_Send_Data(u8 *buf,u8 len);
extern void readRegisters(void);
extern void modbus_dataUnpack_slave(void);
extern void preset_error(u8,u8);
extern void presetMultipleRegister(void);

#endif	   
#endif
















