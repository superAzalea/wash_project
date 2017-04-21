/**************************************************************************************************
Project: TTK_ACPR
Filename: main.c
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
#ifndef __MAIN_C
#define __MAIN_C

#include "stm32f10x.h"
#include "define.h"
#include "delay.h"
#include "Menu.h"
#include "IIC.h"
#include "24CXX.h"
#include "timer.h"
#include "LCD_display.h"
#include "SystemInit.h"
#include "usart.h"
#include "usart3.h"
#include "crc.h"
#include "SysPr.h"
#include "rtc.h"
#include "Interrupt_Init.h"
#include "key.h"
#include "ziku.h"
#include "main.h"
#include "led.h"
#include "buzz.h"
//#include "struct_comm.h"
//extern u16 modbus_check[MBS_BufSize];
//extern u8 fact_temp;//ʵ���¶�
//extern u8 fact_liquid_height;//ʵ��Һλ
u8 flag_err_handshake = 0; 

void ini_data(void)
{
	main_cycle_1s_timer = 500;
	flag_fault_display = 1;
	_if_save_data = 0;
	LED_RUN = 1;
	LED_STOP = 0;
	back_light_timer = 30;
	_set_mode_symbol = 0;//�����趨ģʽ��־
	auto_run_mode = 1;//Ϊ��׼����ģʽ  
	//fact_temp = 12;
	//fact_liquid_height = 10;
//	_enable_dece_time = 0;azalea__
}

int main(void)
{
	int i;
	SystemInit();			//ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	    	//��ʱ��ʼ�� 72M��Ƶ                                                                                                            
	GPIOInit();  	//IO��ʼ��
	init_LCD();
	init_sap1024();
	//MenuIndex = 1000;//�˵���ǩ��
	lcd_wrstring(0,0,disresetmenu);
	AT24CXX_Init();			//��ʼ��IIC�ӿ�
	SysPrInit();			//ϵͳ������ʼ����IIC��ʼ��֮��
	usart_config(9600);		//���ڳ�ʼ��������Ϊ9600��ֹͣλ1
	sendtobuff(0,0,disresetmenu);			//�˵��ľ�̬����
	lcd_wrstring(0,0,DisBuff);
	Timerx_Init(10,7200);//10Khz�ļ���Ƶ�ʣ�������10Ϊ1ms
	NVIC_Configuration();	
	for(i=0;i<250;i++)
	{
		sendBuf[i] = 0;
		receBuf[i] = 0;
	}
	//����Ҫ�·���������������MBS_HoldRegs[] 	
	MBS_HoldRegs[1] = 0x5a5a;//�����źŵ�ַ
	flag_writing_0x06 = 1;
	while(flag_writing_0x06 == 1)
	{
		if(flag_2s_WrSysPr == 1)
		{
			flag_2s_WrSysPr = 0;
			usart_WriteRegister(1,MBS_HoldRegs[1]);//���������ź�
			counter_wr_handshake ++;
			delay_ms(1000);
		}
		if(counter_wr_handshake >= 200)
		{
			counter_wr_handshake = 0;
			flag_err_handshake = 1;
			break;
		}
		modbus_dataUnpack_host();
	}
	if(flag_err_handshake == 1)
	{
		handshake_pro();
	}
	
	ini_data();
	flag_InitFinish = 1;//��һ����ʼ����ɱ�־λ
	
	while(1)
	{
		 Lcd_KEYPro();		
		 LCDDisplay();
		 sub_buzz();
		 fault_dis_pro();   //����ɨ��ʹ���
		 Auto_WashPro();		 //�Զ�ϴ�³���
	}
}

#endif
 


