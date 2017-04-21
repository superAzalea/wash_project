#ifndef __USART_FREQU_C
#define __USART_FREQU_C

#include "usart_Frequ.h"
#include "delay.h"
#include "crc.h"

u8 counter_error_usart3 = 0;
u16 crcData3 = 0;
extern u16 acce_time;
extern u16 dece_time;
extern u16 frequency;
extern u8 fault_clear;
extern u16 systick_flag_200ms_rd ;
extern u8 flag_usart3_wr_500ms;
extern u8 flag_rd;
extern u8 flag_wr;
extern void Delay(__IO uint32_t nTime);
extern u16 MBS_HoldRegs[100];
static __IO uint32_t ReadINV_Timeout_Count;

void ReadINV_Timeout_Count_Decrement(void)
{
	if (ReadINV_Timeout_Count != 0x00)
	{ 
		ReadINV_Timeout_Count--;
	}
}

void USART3_IRQHandler(void)
{
	u8 res;	    
	counter_error_usart3 ++;
	if(counter_error_usart3 >= 100)
	{
		counter_error_usart3 = 0;
		flag_error_usart3 = 1;  
	}
 	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //���յ�����
	{	 
	 	counter_error_usart3 = 0;
		res =USART_ReceiveData(USART3); 	//��ȡ���յ�������
		if(RS485_RX_CNT3 < 100)
		{
			RS485_RX_BUF3[RS485_RX_CNT3]=res;		//��¼���յ���ֵ
			RS485_RX_CNT3++;						//������������1 
		}
		else
		{
			RS485_RX_CNT3 = 0;
		}			
	}

  	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)//�����ж�
		{
			counter_error_usart3 = 0;
			if(sendPosi3 <= RS485_TX_CNT3)
			{
				USART_SendData(USART3,RS485_TX_BUF3[sendPosi3 ++]);
			}
			else
			{
				sendPosi3 = 0;
				RS485_TX_EN3 = 0;
				delay_ms(1);//1ms
				USART_ITConfig(USART3,USART_IT_TXE,DISABLE);//�����ص������ж�			
				USART_ITConfig(USART3,USART_IT_RXNE,ENABLE); //�򿪽����ж�	
			}
		}
} 
  
void RS485_Init3(u32 bound)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIOA,Dʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART1ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //PD7�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//PB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3,ENABLE);//��λ����2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3,DISABLE);//ֹͣ��λ
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); ; //��ʼ������
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
	RS485_TX_EN3=0;			//Ĭ��Ϊ����ģʽ 
}

void usart_ReadRegister3(u16 add,u16 num)//0x03 ��1����������
{
	u16 crcData = 0;
	RS485_TX_BUF3[0] = localAddr3;
	RS485_TX_BUF3[1] = 0x03;	
	RS485_TX_BUF3[2] = (add&0xff00)>>8; 
	RS485_TX_BUF3[3] = add&0x00ff;
	RS485_TX_BUF3[4] = (num&0xff00)>>8; 
	RS485_TX_BUF3[5] = num&0x00ff;
	RS485_TX_CNT3 = 6;
	crcData = crc16(RS485_TX_BUF3,RS485_TX_CNT3); 
	RS485_TX_BUF3[6] = (crcData >> 8) & 0xff;	//��λ��ǰ  
	RS485_TX_BUF3[7] = crcData & 0xff; 		//��λ�ں�
	RS485_TX_CNT3 = 8;
	sendPosi3 = 0;
	RS485_TX_EN3 = 1;
	delay_ms(1);//1ms
	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART3,USART_IT_TXE,ENABLE);//�򿪷����ж�	
}
void usart_WriteRegister3(u16 add,u16 data)//0x06 дһ������
{	
	u16 crcData = 0;
	RS485_TX_BUF3[0] = localAddr3;
	RS485_TX_BUF3[1] = 0x06; 
	RS485_TX_BUF3[2] = (add&0xff00)>>8; 
	RS485_TX_BUF3[3] = add&0x00ff;
	RS485_TX_BUF3[4] = (data&0xff00)>>8; 
	RS485_TX_BUF3[5] = data&0x00ff;
	RS485_TX_CNT3 = 6;
	crcData = crc16(RS485_TX_BUF3,RS485_TX_CNT3); 
	RS485_TX_BUF3[6] = (crcData >> 8) & 0xff;  
	RS485_TX_BUF3[7] = crcData & 0xff;
	RS485_TX_CNT3 = 8;
	sendPosi3 = 0;
	RS485_TX_EN3 = 1;
	delay_ms(1);//1ms
	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);//�ص������ж�
	USART_ITConfig(USART3,USART_IT_TXE,ENABLE);//�򿪷����ж� 
}

u8 modbus_dataUnpack_2(void)//����Ƶ�������������Ƶ��ͨѶ
{	
	u8 byteCount;
	u8 tempAddr;
	u8 errcode = 0x00;
	int i;
	if(RS485_RX_CNT3 > 4 )
	{
		if(RS485_RX_BUF3[0] != 1 && RS485_RX_BUF3[1] == 1)
		{
			RS485_RX_BUF3[0] = RS485_RX_BUF3[1];
			for(i = 0; i < RS485_RX_CNT3; i++)
			{
				RS485_RX_BUF3[i] = RS485_RX_BUF3[i+1];
			}
			RS485_RX_BUF3[i] = 0;
		}
		switch(RS485_RX_BUF3[1])
		{
			case 0x03:  //����Ƶ����ֵ
			{ 
				byteCount = RS485_RX_BUF3[2];//ֻ����8λ
				tempAddr = RS485_RX_BUF3[2] >> 1;
				if(RS485_RX_CNT3 >= byteCount+5)
				{
					if(RS485_RX_BUF3[0] == localAddr3)
					{
 						crcData3 = crc16(RS485_RX_BUF3,byteCount+3);//��10������ 10.6us
						if(crcData3 == (RS485_RX_BUF3[byteCount+3]<<8) + RS485_RX_BUF3[byteCount+4])
						{	
							if(trans_data_num_old <= 1)
							{
								MBS_HoldRegs3[trans_data_num_old] = ((u16)RS485_RX_BUF3[3]<<8) + RS485_RX_BUF3[4];//3:���ݸ�8λ 4:��8λ	
								MBS_HoldRegs[68 + trans_data_num_old] = MBS_HoldRegs3[trans_data_num_old];
							}
							if(trans_data_num_old == 4)
							{
								MBS_HoldRegs3[trans_data_num_old] = ((u16)RS485_RX_BUF3[3]<<8) + RS485_RX_BUF3[4];
								MBS_HoldRegs[63] = MBS_HoldRegs3[trans_data_num_old];

							}
						    if(trans_data_num_old == 2)
							{
								for(i = 0; i < tempAddr; i++)
								{
									MBS_HoldRegs3[5+i] = ((u16)RS485_RX_BUF3[3+i*2]<<8) + RS485_RX_BUF3[4+i*2];//3:���ݸ�8λ 4:��8λ	
									MBS_HoldRegs[68 + trans_data_num_old+i] = MBS_HoldRegs3[3+i];
								}
							}
							
							flag_reading3 = 0;//�����ɹ���
							flag_rw_err = 0;
						}
						else
						{
							errcode = ERR_CHECKSUM;
						  //flag_writing3 = 1;							
				//			counter_rd_error3 ++;
						}
					}
					RS485_RX_CNT3 = 0;
					flag_rd3_timeout=0;
				}
			}break;
			case 0x06://���Ƶ��д���ݣ����Ƶ�����ص�ֵ
			{
				if(RS485_RX_CNT3 >= 8)
				{
					if(RS485_RX_BUF3[0] == localAddr3)
					{						
 						crcData3 = crc16(RS485_RX_BUF3,6);//дһ������ 3.476us						
						if(crcData3 == ((RS485_RX_BUF3[6]<<8) + RS485_RX_BUF3[7]))
						{	
							if(trans_data_num_old == 5)
							{
								modbus_check3[0] = (RS485_RX_BUF3[4]<<8) + RS485_RX_BUF3[5];
								if(modbus_check3[0] == acce_time)
								{
									//flag_writing3 = 0;
									flag_wr_accetime = 0;									
								}
							}
							else if(trans_data_num_old == 6)
							{
								modbus_check3[1] = (RS485_RX_BUF3[4]<<8) + RS485_RX_BUF3[5];
								if(modbus_check3[1] == dece_time)
								{
									//flag_writing3 = 0;
									flag_wr_decetime = 0;
								}
							}
							else if(trans_data_num_old == 7)
							{
								modbus_check3[2] = (RS485_RX_BUF3[4]<<8) + RS485_RX_BUF3[5];
								if(modbus_check3[2] == frequency)
								{
									//flag_writing3 = 0;
									flag_wr_freqency = 0;
									
								}
							}
							else if(trans_data_num_old == 10)
							{
								modbus_check3[3] = (RS485_RX_BUF3[4]<<8) + RS485_RX_BUF3[5];
								if(modbus_check3[3] == fault_clear)
								{
									flag_writing3 = 0;	
								}
							}
							
							if((flag_wr_accetime == 0) && (flag_wr_decetime == 0) && (flag_wr_freqency == 0))
							{
								flag_writing3 = 0;
							}
						}	
						else
						{					
							errcode = ERR_CHECKSUM;
						}
					}
					RS485_RX_CNT3 = 0;
					flag_wr3_timeout = 0;
				}
			}
			break;			
			default:
			{
				RS485_RX_CNT3 = 0;
			}
			break;
		}
		counter_rw_err = 0;
	}
	else
	{
		flag_rw_err = 1;
		counter_rw_err++;
		
		
	}
	RS485_RX_CNT3 = 0;
	return errcode;
}

void ELC2INV_Read_write(void)
{
//	static u8 by_reset_count = 0;
	trans_data_num_old = trans_data_num;
	switch(trans_data_num)
	{
		case 0:
			usart_ReadRegister3(0x2000,1); //��Ƶ����ǰ����
			trans_data_num = 1;
		break;
		case 1:
			usart_ReadRegister3(0x2001,1); //��Ƶ����ǰ״̬
			trans_data_num = 2;		
		break;
		case 2:
			usart_ReadRegister3(0x4000,5);//��Ƶ������Ƶ��
			trans_data_num = 0;
		break;
		case 4:
			usart_ReadRegister3(0x6000,1);//��Ƶ����ǰ����
		break;
		case 5:
			usart_WriteRegister3(0x000C,acce_time);//д����ʱ��
			flag_wr_accetime = 1;
			trans_data_num = 6;
		break;
		case 6:
			usart_WriteRegister3(0x000D,dece_time);//д����ʱ��
			flag_wr_decetime = 1;
			trans_data_num = 7;
		break;
		case 7:
			usart_WriteRegister3(0x3000,frequency);//дƵ��
			flag_wr_freqency = 1;
			trans_data_num = 15;
		break;
		case 10:
			usart_WriteRegister3(0x2000,7);//д�������
		break;	
		default:
		break;
	}
}

u8 presetReadINV_Adress(void)
{
	u8 errcode = 0x00;
	while(1)
	{
		if(flag_rd == 1)
		{
			flag_rd = 0;
			if(flag_reading3 == 0)
			{
				ELC2INV_Read_write();
				//OUT_COOL_WATER = ~OUT_COOL_WATER;
				flag_reading3 = 1;
				//counter_rw_err = 0;
			}
			else
			{
				if(flag_rw_err == 1 /*&& counter_rw_err == 2*/)
				{
					//OUT_HOT_WATER = ~OUT_HOT_WATER;
					ELC2INV_Read_write();
					flag_rd3_timeout++ ;
					counter_rw_err = 0;

				}
			}
		
		}
		if(flag_rd3_timeout >= 5)
		{
			errcode =  ERR_TIMEOUT;
			flag_rd3_timeout = 0;
			break;
		}
		
		delay_ms(10);
		errcode = modbus_dataUnpack_2();//��Ƶ�����������յ����ݺ���
		if(flag_reading3 == 0 && (trans_data_num_old == 2 || trans_data_num_old == 4))
		{
			//WriteINV_M_TimerOut = 10;
			errcode = ERR_NONE;
			break;	
		}
		
		
	}
	return errcode;
}

u8 presetWriteINV_Adress(void)
{
	u8 errcode = 0x00;
	while(1)
	{
		if(flag_wr == 1)
		{
			flag_wr = 0;
			if(flag_writing3 == 0)
			{
				ELC2INV_Read_write();
				flag_writing3 = 1;
			}
			else
			{
				if(flag_rw_err == 1)
				{
					ELC2INV_Read_write();
					flag_wr3_timeout++;

				}
			}
		}
		
		if(flag_wr3_timeout >= 3)
		{
			errcode =  ERR_TIMEOUT;
			flag_wr3_timeout = 0;
			break;
		}
		delay_ms(10);//10ms
		errcode = modbus_dataUnpack_2();//��Ƶ�����������յ����ݺ���	
		if(flag_writing3 == 0 )
		{
			if(trans_data_num_old == 7 || trans_data_num_old == 10 )
			{
				errcode = ERR_NONE;
				break;
			}
		}
	}
	return errcode;
}


u8 presetWrite10INV_Adress(void)
{
	u8 errcode = 0x00;
	while(1)
	{
		if(flag_wr == 1)
		{
			flag_wr = 0;
			if(flag_writing3 == 0)
			{
				ELC2INV_Read_write();
				//usart_WriteRegister3(0x000C,acce_time);//д����ʱ��
				flag_writing3 = 1;
			}
			else
			{
				if(flag_rw_err == 1 && (flag_wr_accetime == 1 || flag_wr_decetime == 1 ||flag_wr_freqency == 1))
				{
					if(flag_wr_accetime == 1)
					{
						usart_WriteRegister3(0x000C,acce_time);//д����ʱ��

					}
					else if(flag_wr_decetime == 1)
					{
						usart_WriteRegister3(0x000D,dece_time);//д����ʱ��
	
					}
					else if(flag_wr_freqency == 1)
					{
						usart_WriteRegister3(0x3000,frequency);//дƵ��

					}
					//ELC2INV_Read_write();
					flag_wr3_timeout++;

				}
			}
		}
		
		if(flag_wr3_timeout >= 10)
		{
			errcode =  ERR_TIMEOUT;
			flag_wr3_timeout = 0;
			break;
		}
		delay_ms(10);//10ms
		errcode = modbus_dataUnpack_2();//��Ƶ�����������յ����ݺ���	
		if(flag_writing3 == 0 )
		{
			if(trans_data_num_old == 7 || trans_data_num_old == 10 )
			{
				errcode = ERR_NONE;
				break;
			}
		}
	}
	return errcode;
}


#endif




