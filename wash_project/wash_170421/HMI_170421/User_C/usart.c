/**************************************************************************************************
Project: TTK_ACPR
Filename: usart.c
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
#ifndef __USART_C
#define __USART_C

#include "stm32f10x.h"
#include "define.h"
#include "crc.h"
#include "menu.h"
#include "main.h"
#include "key.h"
#include "timer.h"
#include "delay.h"
#include "usart.h"

extern unsigned char usart3_flag_fault_clear;
extern unsigned char _enable_commu_Inventer;
void usart_config(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);  
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		//USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		//USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��������λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����Ч��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//���ù���ģʽ
    USART_Init(USART1, &USART_InitStructure);//������ṹ��
	
	sendPosi = 0;
	RS485_RX
	delay(10000);//1ms
	USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);   
	
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 		
}

volatile unsigned long counter_crc_error1 = 1;//��¼CRCУ��������
volatile unsigned long counter_crc_error2 = 0;//��¼CRCУ��������
u8 counter_break_usart = 0;
u8 counter_error_usart = 0;
void USART1_IRQHandler(void)
{
//	counter_error_usart ++;
//	if(counter_error_usart >= 20)
//	{
//		counter_error_usart = 0;
//		flag_error_usart = 1;
//	}
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//�����ж�
	{
		
		//counter_error_usart = 0;		

		if(receCount < 100)
		{
			receBuf[receCount++]= USART_ReceiveData(USART1);   
		}
		else
		{
			receCount = 0;
			
		}			
  }
	
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)//�����ж�
	{
		//counter_error_usart = 0;
		if (sendPosi <= sendCount) 
		{
			USART_SendData(USART1,sendBuf[sendPosi++]);
		}
		else 
		{ 
			sendPosi = 0;
			RS485_RX	  
			delay(10000);//1ms
			USART_ITConfig(USART1,USART_IT_TXE,DISABLE);//�����ص������ж�			
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //�򿪽����ж�
		} 
	}
}	

void usart_ReadRegister(u16 add,u16 num)//0x03 ��1����������
{
	u16 crcData = 0;
	sendBuf[0] = localAddr;
	sendBuf[1] = 0x03;	
    sendBuf[2] = (add&0xff00)>>8; 
    sendBuf[3] = add&0x00ff;
    sendBuf[4] = (num&0xff00)>>8; 
    sendBuf[5] = num&0x00ff;
    sendCount = 6;
    crcData = crc16(sendBuf,sendCount); 
    sendBuf[6] = (crcData >> 8) & 0xff;	//��λ��ǰ  
    sendBuf[7] = crcData & 0xff; 		//��λ�ں�
    sendCount = 8;

	RS485_TX
	delay(10000);//1ms
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
    USART_ITConfig(USART1,USART_IT_TXE,ENABLE);//�򿪷����ж�	
}
void usart_WriteRegister(u16 add,u16 data)//0x06 дһ������
{	
	u16 crcData = 0;
	
    sendBuf[0] = localAddr;
    sendBuf[1] = 0x06; 
    sendBuf[2] = (add&0xff00)>>8; 
    sendBuf[3] = add&0x00ff;
    sendBuf[4] = (data&0xff00)>>8; 
    sendBuf[5] = data&0x00ff;
    sendCount = 6;

    crcData = crc16(sendBuf,sendCount); 
    sendBuf[6] = (crcData >> 8) & 0xff;  
    sendBuf[7] = crcData & 0xff;
    //sendCount = 8;
		sendCount=8;
	
	RS485_TX
	delay(10000);//1ms
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);//�ص������ж�
  USART_ITConfig(USART1,USART_IT_TXE,ENABLE);//�򿪷����ж� 
}
u8 aRXDBuffer[10]={0x01,0x02,0x03,0x04,0x05};
u8 cnt = 0;

void usart_WriteMultipleRegister(u16 add,u16 num)//0x10 д�������(32,3)//01 10 00 20 00 03 06 00 11 00 22 00 33 FB F6
{
	u16 crcData = 0;
	u8 i = 0;	
	sendBuf[0] = localAddr;
	sendBuf[1] = 0x10;	
    sendBuf[2] = (add&0xff00)>>8; 
    sendBuf[3] = add&0x00ff;
    sendBuf[4] = (num&0xff00)>>8; 
    sendBuf[5] = num&0x00ff;
	sendBuf[6] = num<<1;
	sendCount = 7;
	for(i=0;i<num;i++)
	{
		sendBuf[7+i*2] = (MBS_HoldRegs[add+i]&0xff00)>>8;
		sendBuf[8+i*2] = MBS_HoldRegs[add+i]&0x00ff;
	}

	sendCount += (num<<1);

    crcData = crc16(sendBuf,sendCount);
    sendBuf[sendCount] = (crcData >> 8) & 0xff;	//��λ��ǰ
    sendBuf[sendCount+1] = crcData & 0xff; 		//��λ�ں�
    sendCount += 2;

	RS485_TX
	delay(10000);//1ms
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);//�ص������ж�
    USART_ITConfig(USART1,USART_IT_TXE,ENABLE);//�򿪷����ж�
}

void modbus_dataUnpack_host(void)
{	
	u8 i = 0;
	u16 add = 0;
	u16 data = 0;
	u8 byteCount;
	u8 tempAddr;
	u16 crcData = 0;
	
	if(receCount > 4)
	{
		switch(receBuf[1])
		{
			case 0x03: 
			{
				byteCount = receBuf[2];		//�ֽڸ���(8λ1��)
				tempAddr = receBuf[2] >> 1;	//���ݸ���(16λ1��)	
				if(receCount >= byteCount+5)
				{
					if(receBuf[0]==localAddr)
					{
						crcData = crc16(receBuf,byteCount+3);
						if(crcData == (receBuf[byteCount+3]<<8) + receBuf[byteCount+4])
						{
							add = (receBuf[2]<<8) + receBuf[3];//4:��ַ��8λ 5:��8λ
							if(byteCount == 12)
							{
								
								for(i=0;i<tempAddr;i++)
								{
									MBS_HoldRegs[58 + i] = ((u16)receBuf[3 + i*2]<<8) + receBuf[4 + i*2];//��62��ʼ����4�����ݣ����Դ�62��ʼ��
								}
								if(MBS_HoldRegs[63] == 0xff)
								{
									flag_rd03_fault = 1;
									counter_rd_err ++;
								}
								else
								{
									flag_reading_0x03 = 0;

								}
				
								readINV_handshake = 0;

							}
							else if(byteCount == 14)
							{	
								for(i=0;i<tempAddr;i++)
								{
									MBS_HoldRegs[68 + i] = ((u16)receBuf[3 + i*2]<<8) + receBuf[4 + i*2];//��68��ʼ����9�����ݣ�����68��ʼ��
								}
							}
							else if(byteCount == 16)
							{
								for(i=0;i<tempAddr;i++)
								{
									MBS_HoldRegs[55 + i] = ((u16)receBuf[3 + i*2]<<8) + receBuf[4 + i*2];//��62��ʼ����4�����ݣ����Դ�62��ʼ��
								}
								if(MBS_HoldRegs[57] == 0x0A)
								{
									readINV_handshake = 1;//elc���ֳɹ��ı��
									flag_reading_0x03 = 0;
									
								}
								else
								{
								counter_rd_err++;
								}
							}
							
							if(counter_rd_err >= 3)
							{
								flag_usart2_read_error = 1;
								flag_reading_0x03 = 0;
								counter_rd_err = 0;
								flag_rd03_fault = 0;

							}

							flag_rw_elc_err = 0;
							counter_rd =0;
						}
						else
						{
						//У��ʧ��
						}
					}						
					receCount = 0;

				}
			}break;
			case 0x06://��λ����λд�����Ĵ�������λ���ص���Ϣ
			{
				if(receCount >= 8)
				{
					if(receBuf[0]==localAddr)
					//if(receBuf[0]==0x55)	//
					{
						crcData = crc16(receBuf,6);
						if(crcData == (((u16)receBuf[6]<<8) + receBuf[7]))
						{							
							add = (receBuf[2]<<8) + receBuf[3];//4:��ַ��8λ 5:��8λ
							data = (receBuf[4]<<8) + receBuf[5];//4:���ݸ�8λ 5:��8λ								
							modbus_check[add] = data;
							
							if(add == 76)
							{
								MBS_HoldRegs[76] = data;
								counter_wr06_err++;
								flag_wr_fault = 1;
								if(counter_wr06_err >= 10)
								{
									flag_usart2_read_error = MBS_HoldRegs[76];//��λ���Ƶ����ͨѶ״̬
									counter_wr06_err = 0;
									usart3_flag_fault_clear = 0;
									flag_wr_fault = 0;
									flag_writing_0x06 = 0;

								}
							}
							else
							{
								flag_writing_0x06 = 0;
								usart3_flag_fault_clear = 0;
								flag_wr_fault = 0;
								counter_wr06_err = 0;
								flag_rw_elc_err = 0;
							}
							counter_wr_ok ++;
							//flag_writing_0x06 = 0;
						}		
					}						
					receCount = 0;
				}
			}break;	
			case 0x10://��λ����λд����Ĵ�������λ���ص���Ϣ
			{
				if(receCount >= 8)
				{
					if(receBuf[0]==localAddr)
					{
						crcData = crc16(receBuf,6);
						if(crcData == ((receBuf[6]<<8) + receBuf[7]))
						{							
							add = (receBuf[2]<<8) + receBuf[3];//4:��ַ��8λ 5:��8λ
							data = (receBuf[4]<<8) + receBuf[5];//4:���ݸ�8λ 5:��8λ								
							//modbus_check[add] = data;
							if(add == 76)
							{
								MBS_HoldRegs[76] = data;
								counter_wr10_err++ ;
								flag_wr10_fault = 1;
								if(counter_wr10_err >= 10)
								{
									flag_usart2_read_error = MBS_HoldRegs[76];//��λ���Ƶ����ͨѶ״̬
									flag_wr10_fault = 0;
									counter_wr10_err = 0;
									_enable_commu_Inventer = 0;
									flag_writing_0x10 = 0;

								}
							}
							else
							{

								flag_writing_0x10 = 0;
								flag_wr10_fault = 0;
								counter_wr10_err = 0;
								flag_rw_elc_err = 0;
								_enable_commu_Inventer = 0;
							}
							
							counter_wr_ok ++;
						}
					}						
					receCount = 0;
				}
			}break;				
			default:
			{
				receCount = 0;
			}break;
		}
	}
	else
	{
		flag_rw_elc_err = 1;
	}
	

	
}

#endif

