#ifndef __RS485_C
#define __RS485_C
#include "stm32f10x.h"
#include "sys.h"		    
#include "rs485.h"	 
#include "delay.h"
#include "crc.h"
#include "usart_Frequ.h"
//#include "struct_comm_receive.h"
u8 ELC2INV_usart3_error = 0;
extern u8 flag_writing3;
extern u8 ReadINV_usart3_ok ;
extern u8 WriteINV_usart3_ok;
u8 readINV_error = 0;

void USART1_IRQHandler(void)
{
	u8 res;	     
 	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�
	{	 	 
		res =USART_ReceiveData(USART1); 	//��ȡ���յ�������
		if(RS485_RX_CNT<100)
		{
			RS485_RX_BUF[RS485_RX_CNT]=res;		//��¼���յ���ֵ
			RS485_RX_CNT++;						//������������1 
		} 
	}
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)//�����ж�
	{
		//counter_error_usart = 0;
		if(sendPosi <= RS485_TX_CNT)
		{
			USART_SendData(USART1,RS485_TX_BUF[sendPosi++]);
		}
		else
		{
			sendPosi = 0;
			RS485_TX_EN = 0;
			delay_ms(1);//1ms
			USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		}
	}		
} 	

void RS485_Init(u32 bound)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOA,Dʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PD7�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1,ENABLE);//��λ����2
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1,DISABLE);//ֹͣ��λ
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); ; //��ʼ������ 
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
   
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
	RS485_TX_EN=0;			//Ĭ��Ϊ����ģʽ
}

void readRegisters(void)
{
	u8 addr;
	u8 tempAddr;
	u16 crcData;
	u8 readCount;
	u8 byteCount;
	u16 i;
	u16 tempData = 0;	
	addr = RS485_RX_BUF[3];
	tempAddr = addr;	
	readCount = RS485_RX_BUF[5];
	byteCount = readCount<<1;//����1λ����2	
	for(i = 0; i < byteCount; i += 2,tempAddr++)
	{
		tempData = MBS_HoldRegs[tempAddr];
		RS485_TX_BUF[i+3] = tempData >> 8;
		RS485_TX_BUF[i+4] = tempData & 0xff;
	}
	RS485_TX_BUF[0] = localAddr;
	RS485_TX_BUF[1] = 3;
	RS485_TX_BUF[2] = byteCount;
	byteCount += 3;
	crcData = crc16(RS485_TX_BUF,byteCount);
	RS485_TX_BUF[byteCount] = crcData >> 8;
	byteCount++;
	RS485_TX_BUF[byteCount] = crcData & 0xff;
	RS485_TX_CNT = byteCount + 1;
	sendPosi = 0;
	RS485_TX_EN=1;			//����Ϊ����ģʽ
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	
	USART_ITConfig(USART1,USART_IT_TXE,ENABLE);		
}

void presetSingleRegister(void)// ���õ����Ĵ���
{
	u8 addr;
	u8 tempAddr;
	u16 crcData;
	u16 tempData;
	
	addr = RS485_RX_BUF[3];
	tempAddr = addr & 0xff;
	tempData = (RS485_RX_BUF[4] << 8) + RS485_RX_BUF[5];
	MBS_HoldRegs[tempAddr] = tempData;

	RS485_TX_BUF[0] = localAddr;
	RS485_TX_BUF[1] = 6;
	RS485_TX_BUF[2] = addr >> 8;
	RS485_TX_BUF[3] = addr & 0xff;
	RS485_TX_BUF[4] = tempData >>8;
	RS485_TX_BUF[5] = tempData & 0xFF;
	crcData = crc16(RS485_TX_BUF,6);
	RS485_TX_BUF[6] = crcData >> 8;
	RS485_TX_BUF[7] = crcData & 0xff;
	RS485_TX_CNT = 8;
	sendPosi = 0;
	RS485_TX_EN=1;			//����Ϊ����ģʽ
	delay_ms(1);//1ms
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	
	USART_ITConfig(USART1,USART_IT_TXE,ENABLE);	
}

void presetMultipleRegister(void)
{
	u8 addr;
//	u8 tempAddr;
	u8 setCount;
	u16 crcData;
	//u16 tempData;
//	u8 i;
	addr = RS485_RX_BUF[3];
	//tempAddr = addr & 0xff;
	setCount = RS485_RX_BUF[5];
//	for(i = 0; i < setCount; i++,tempAddr++)
//	{
//		tempData = (RS485_RX_BUF[i*2+7] << 8)+ RS485_RX_BUF[i*2+8];
//		MBS_HoldRegs[ addr+ i] = tempData;
//	}	
	RS485_TX_BUF[0] = localAddr;
	RS485_TX_BUF[1] = 16;
	RS485_TX_BUF[2] = addr >> 8;
	RS485_TX_BUF[3] = addr & 0xff;
	RS485_TX_BUF[4] = setCount >> 8;
	RS485_TX_BUF[5] = setCount & 0xff;
	crcData = crc16(RS485_TX_BUF,6);
	RS485_TX_BUF[6] = crcData >> 8;
	RS485_TX_BUF[7] = crcData & 0xff;
	RS485_TX_CNT = 8;
	sendPosi = 0;
	RS485_TX_EN=1;			//����Ϊ����ģʽ
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	//��ֹ�����ж�
	USART_ITConfig(USART1,USART_IT_TXE,ENABLE);		//ʹ�ܷ����ж�
}

//void preset_error(u8 errocode)
//{
//	u8 addr;
//	u16 crcData;
//	u16 tempData;
//	addr = 76;
//	MBS_HoldRegs[76] = errocode;
//	tempData = MBS_HoldRegs[76];
//	RS485_TX_BUF[0] = localAddr;
//	RS485_TX_BUF[1] = 6;
//	RS485_TX_BUF[2] = addr >> 8;
//	RS485_TX_BUF[3] = addr & 0xff;
//	RS485_TX_BUF[4] = tempData >>8;
//	RS485_TX_BUF[5] = tempData & 0xFF;
//	crcData = crc16(RS485_TX_BUF,6);
//	RS485_TX_BUF[6] = crcData >> 8;
//	RS485_TX_BUF[7] = crcData & 0xff;
//	RS485_TX_CNT = 8;
//	sendPosi = 0;
//	RS485_TX_EN=1;			//����Ϊ����ģʽ
//	delay_ms(1);//1ms
//	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	
//	USART_ITConfig(USART1,USART_IT_TXE,ENABLE);	
//}

void preset_error(u8 mode,u8 errocode)
{
	u8 addr;
	u16 crcData;
	u16 tempData;
	addr = 76;
	MBS_HoldRegs[76] = errocode;
	tempData = MBS_HoldRegs[76];
	MBS_HoldRegs[76] = 0;
	RS485_TX_BUF[0] = localAddr;
	if(mode == 0)
	{
		RS485_TX_BUF[1] = 3;
		RS485_TX_BUF[2] = 2;
		RS485_TX_BUF[3] = tempData >>8;
		RS485_TX_BUF[4] = tempData & 0xFF;
		crcData = crc16(RS485_TX_BUF,5);
		RS485_TX_BUF[5] = crcData >> 8;
		RS485_TX_BUF[6] = crcData & 0xff;
		RS485_TX_CNT = 7;
	}
	else if(mode == 1 || mode == 2)
	{
		if(mode == 1)
		{
			RS485_TX_BUF[1] = 6;

		}
		else if(mode == 2)
		{
			RS485_TX_BUF[1] = 16;
		}
		RS485_TX_BUF[2] = addr >> 8;
		RS485_TX_BUF[3] = addr & 0xff;
		RS485_TX_BUF[4] = tempData >>8;
		RS485_TX_BUF[5] = tempData & 0xFF;
		crcData = crc16(RS485_TX_BUF,6);
		RS485_TX_BUF[6] = crcData >> 8;
		RS485_TX_BUF[7] = crcData & 0xff;
		RS485_TX_CNT = 8;
	}
	sendPosi = 0;
	RS485_TX_EN=1;			//����Ϊ����ģʽ
	delay_ms(1);//1ms
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	
	USART_ITConfig(USART1,USART_IT_TXE,ENABLE);	
}
		
										
void modbus_dataUnpack_slave() //����//hmi->elc
{
	u8 i;
	u8 errcode = 0;
	u16 crcData = 0;
	u8 byteCount = 0;
	u8 rxlen=RS485_RX_CNT;
	u16 add = 0;
	u16 data = 0;
	u16 num = 0;
	u16 tempData;
//	*len=0;				//Ĭ��Ϊ0
	delay_ms(10);		//�ȴ�10ms,��������10msû�н��յ�һ������,����Ϊ���ս���
	if(rxlen==RS485_RX_CNT&&rxlen)//���յ�������,�ҽ��������
	{
		if(rxlen > 4)
		{
			switch(RS485_RX_BUF[1])
			{
				case 3:
				case 6:
					if(rxlen >= 8)
					{	
						if(RS485_RX_BUF[0] == localAddr)
						{
							crcData = crc16(RS485_RX_BUF,6);
							if(crcData == RS485_RX_BUF[7] + (RS485_RX_BUF[6] << 8))
							{								
								add = (RS485_RX_BUF[2]<<8) + RS485_RX_BUF[3];//4:��ַ��8λ 5:��8λ
								data = (RS485_RX_BUF[4]<<8) + RS485_RX_BUF[5];//4:���ݸ�8λ 5:��8λ								

								if(RS485_RX_BUF[1] == 3)
								{
									if(add == 55) //�յ�hmiҪ��inv������(������Ϣ)
									{
										MBS_HoldRegs[55] = 0;
										MBS_HoldRegs[56] = 0;
										MBS_HoldRegs[57] = 0x0A;
										readRegisters();//�ر���
										//��ʼ����Ƶ��
										trans_data_num = 4;
										errcode = presetReadINV_Adress();
										if(errcode == ERR_TIMEOUT || errcode == ERR_CHECKSUM )//��ȡʧ��
										{
											readINV_error = 1;
											//MBS_HoldRegs[63] = 0xff;
											flag_reading3 = 0;
											trans_data_num_old =0;

										}
										else if(errcode == ERR_NONE)//�ɹ�
										{
											readINV_error = 0;
										}


									}
									else if(add == 58)//���ض�����
									{
										if(readINV_error == 1)
										{
											MBS_HoldRegs[63] = 0xFF;
										}
										readRegisters();
										
									}
									else if(add == 68)
									{
										trans_data_num = 0;
										errcode = presetReadINV_Adress();
										if(errcode == ERR_NONE)
										{
											//�ظ����������ݱ���
											readRegisters();
										}else if(errcode == ERR_TIMEOUT || errcode == ERR_CHECKSUM)
										{
											preset_error(0,errcode);
											errcode = 0;
											flag_reading3 = 0;
											trans_data_num_old =0;
										}
									}
									
								}
								else if(RS485_RX_BUF[1] == 6)//�޸ģ�д��ȥ֮���������ȷ����
								{
									if(add == 6) //�������
									{
										fault_clear = data; //0x07
										trans_data_num = 10;
										errcode = presetWriteINV_Adress();
										if(errcode == ERR_NONE) //д���Ժ����������д�Ƿ�ɹ�
										{
											//��д������
											presetSingleRegister();
										}else
										if(errcode == ERR_TIMEOUT || errcode == ERR_CHECKSUM)
										{
											preset_error(1,errcode);
											errcode = 0;
											flag_writing3 = 0;
											trans_data_num_old = 0;
										
										}
									}
									else //add = 5,дhmi��������RO1~RRO12+BPQ_X2\BPQ_X1��״̬
									{
										presetSingleRegister();

									}
								}
							}
						}
						rxlen = 0;
						RS485_RX_CNT = 0;
					}
				break;
				case 16:
					if(rxlen >= 7)
					{
						byteCount = RS485_RX_BUF[6];//06
						byteCount += 9;
						if(rxlen >= byteCount)
						{
							add = (RS485_RX_BUF[2]<<8) + RS485_RX_BUF[3];//4:��ַ��8λ 5:��8λ
							num = (RS485_RX_BUF[4]<<8) + RS485_RX_BUF[5];
							crcData = crc16(RS485_RX_BUF,byteCount-2);
							if(crcData == RS485_RX_BUF[byteCount-1]+(RS485_RX_BUF[byteCount-2]<<8))
							{
								for(i = 0; i < num; i++)
								{
									tempData = (RS485_RX_BUF[i*2+7] << 8)+ RS485_RX_BUF[i*2+8];
									MBS_HoldRegs[ add+ i] = tempData;
								}
								
								if(add == 2)
								{	
									acce_time = MBS_HoldRegs[2];
									dece_time = MBS_HoldRegs[3];
									frequency = MBS_HoldRegs[4];
									trans_data_num = 5;
									errcode = presetWrite10INV_Adress();
									if(errcode == ERR_NONE)
									{
										presetMultipleRegister();
									}
									else if(errcode == ERR_TIMEOUT || errcode == ERR_CHECKSUM)
									{
										preset_error(2,errcode);
										errcode = 0;
										flag_writing3 = 0;
										flag_wr_accetime = 0;
										flag_wr_decetime = 0;
										flag_wr_freqency = 0;
										trans_data_num_old = 0;
									}
								}
								else
								{
										presetMultipleRegister();//8.404ms

								}
							}
							else
							{

							}
							rxlen = 0;
							RS485_RX_CNT = 0;
						}
						
					}
					break;
				default:
				break;				
			}	
		}	
	}
	
}

#endif
