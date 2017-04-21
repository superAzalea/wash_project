#ifndef __USART3_C
#define __USART3_C

#include "stm32f10x.h"
#include "Define.h" 
#include "usart3.h"

u8 USART_RX_BUF3[64];     //���ջ���,���64���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����յ�0x0d
//bit5~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA3=0;       //����״̬���

void uart_init3(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//USART2 USART3Ҫ��RCC_APB1PeriphClockCmd 
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			//USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);				// GPIOB
     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			//USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    
    GPIO_Init(GPIOB, &GPIO_InitStructure);				// GPIOB  
  
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;			//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART3
  
   //USART ��ʼ������
   
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�        
   
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
}
/*
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
    
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		USART_RX_BUF[USART_RX_STA&0X3F]=Res ;
		USART_RX_STA++;
        if(USART_RX_STA>63)
            USART_RX_STA=0;
    } 
}*/
void USART3_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res = USART_ReceiveData(USART3);//��ȡ���յ�������
		
		if((USART_RX_STA3 & 0x80) == 0)//����δ���
		{
			if(USART_RX_STA3 & 0x40)//���յ���0x0d
			{
				if(Res!=0x0a)	USART_RX_STA3 = 0;//���մ���,���¿�ʼ
				else	USART_RX_STA3 |= 0x80;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)	USART_RX_STA3 |= 0x40;
				else
				{
					USART_RX_BUF3[USART_RX_STA3 & 0X3F] = Res ;
					USART_RX_STA3 ++;
					if(USART_RX_STA3 > 63)	USART_RX_STA3 = 0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}
	} 
} 
#endif

