#ifndef __DataExchange_C
#define __DataExchange_C

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "rs485.h"
#include "usart_Frequ.h"
#include "dataExchange.h"
#include "faultProcess.h"
#include "adc.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
//��USART3�յ����ݣ�ͨ��USART1��������λ����ʾ��
//��AD������ֵ��������ͨ��USART1��������λ����ʾ��
//////////////////////////////////////////////////////////////////////////////////////////////////	
void DataExchange(void)
{
	unsigned char i = 0;
	for(i = 0;i < 5; i++) //ADֵ
	{
		if(i == 4)
		{
			MBS_HoldRegs[62 + i] = SystemState.all;
		}
		else
		{
			MBS_HoldRegs[62 + i] = adc_result[i]; //test by andy

		}
	}
	
	for( i = 0; i < 8; i++) // ��Ƶ���ķ�����Ϣ,���Ӽ���ʱ�䡢����ʱ��
	{
		MBS_HoldRegs[68 + i] = MBS_HoldRegs3[i];//MBS[73]��ʼ����¼10����Ƶ��������Ϣ��73~82
	}	
//	MBS_HoldRegs[83] = SystemState.all;	//��λ��ϵͳ״̬��
}

#endif
