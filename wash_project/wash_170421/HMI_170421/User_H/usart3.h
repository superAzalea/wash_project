#ifndef __USART3_H
#define __USART3_H

#define USART3_IRQn	39
#define RS485_RX3 GPIOB->ODR &= 0xfffd;//RS485��Ϊ���� PB1
#define RS485_TX3 GPIOB->ODR |= 0x0002;//RS485��Ϊ���� PB1

#ifdef	__usart2_C

void uart_init3(u32 bound);

#else

extern void uart_init3(u32 bound);
extern u8 USART_RX_BUF3[64];     //���ջ���,���63���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART_RX_STA3;         //����״̬���	

#endif
#endif

