#ifndef __PID_C
#define __PID_C

#include "stm32f10x.h"
#include "define.h"
#include "pid.h"

// static int32 Xn_Int=0;
// int16	ek=0,uk=0;
// int32   Yn_Pro=0,Yn_Int=0,tmpVar_Int=0;
#define PU_VALUE_CONST 4095//����ı���ֵ���Ƶ�ʡ���������ѹ�ı���ֵ��

int16 PidCtrl_ps1(u16 Xref,u16 Xact,u16 Kp, u16 Ki,int16 UpperLim,int16 LowerLim)//PID������
{//   PidCtrl_ps1(13405,Iact_filter,16,4096,0,-PuValue);
	static int32 Xn_Int=0;
	int16 ek=0,uk=0;
	int32 Yn_Pro=0,Yn_Int=0,tmpVar_Int=0;

	ek=Xref-Xact;					//PI����������

	Yn_Pro=(int32)Kp*ek>>12;		//�����������Kp 

	tmpVar_Int=(int32)Ki*ek>>12;	//������ɢ��,Ki<1;

	Yn_Int=(Xn_Int<<12)/(PU_VALUE_CONST+Ki)+tmpVar_Int;		//���������

	if(Yn_Int<LowerLim)	Yn_Int=LowerLim;
	else if(Yn_Int>UpperLim) Yn_Int=UpperLim;		//�������޷�

	Xn_Int=Yn_Int;		//�������ڹ̶�

	uk=Yn_Pro + Yn_Int;				//PI���

	if(uk<LowerLim)	uk=LowerLim;
	else if(uk>UpperLim) uk=UpperLim;		//PI����������޷�
	return uk; 
}

#endif


 
