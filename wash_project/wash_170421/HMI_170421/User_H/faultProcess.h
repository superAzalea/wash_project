/**************************************************************************************************
Project: TTK_ACPR
Filename: faultProcess.h
Description: time interruput functions for air compressor.
Complier: Keil uVision5.
***************************************************************************************************
Copyright (c) 2014 TTK.
All rights reserved.
***************************************************************************************************
DESCRIPTION:
Revision History:
Original Author:JesonsSun
First edition Time:20140601
Last Review Time:20140701 11:11;V1.0
**************************************************************************************************/
#ifndef __FAULTPROCESS_H
#define __FAULTPROCESS_H

#ifdef __FAULTPROCESS_C

u8 FaultCode_Z = 0;

u8 FaultCode = 0;//������˸��־λ

u8 flag_fault_1s = 0;
u8 flag_butttery_lv = 0;

u16 faultCode_inv = 0;			//��Ƶ��������


u16 glFaultCode = 0;

u8 page_FaultCode = 0;		//����ҳ��
u8 num_FaultCode = 0;		//���ϴ������
u8 tempFaultCode[8];

u8 flag_FaultDis_500ms = 0;
u8 flag_FaultDis_1s = 0;

void sub_fault_init(void);
void sub_faultProcess(void);
//void Menu_FaultRecord(u8 CodePage,u8 CodeNum);	//���ϼ�¼

#else

extern u8 FaultCode_Z;
extern u8 FaultCode;//������˸��־λ

extern u8 flag_fault_1s;
extern u8 flag_butttery_lv;

extern u16 faultCode_inv;				//��Ƶ��������


extern u16 glFaultCode;

extern u8 page_FaultCode;		//����ҳ��
extern u8 num_FaultCode;		//���ϴ������
extern u8 tempFaultCode[8];

extern u8 flag_FaultDis_500ms;
extern u8 flag_FaultDis_1s;

extern void sub_fault_init(void);
extern void sub_faultProcess(void);
//extern void Menu_FaultRecord(u8 CodePage,u8 CodeNum);	//���ϼ�¼

#endif
#endif



























