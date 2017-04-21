#include "stm32f10x.h"
#include "led.h"
#include "SystemInit.h"
//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 |GPIO_Pin_12;				 //L_Soap PA.8 L_Heat PA.11 L_Warm PA.12�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 GPIO_SetBits(GPIOA,GPIO_Pin_8 |GPIO_Pin_11 | GPIO_Pin_12);						 //PA.8,11,12 �����        

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA�˿�ʱ��
	//L_Run PB.1,L_Cold PB.5,L_Stop PB.10,L_Remove PB.11 �˿�����
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5 |GPIO_Pin_10 |GPIO_Pin_11;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_5 |GPIO_Pin_10 |GPIO_Pin_11);	
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //ʹ��PD�˿�ʱ��
//	L_Drain PC.6,L_Spin PC.7,L_Wash PC.12 �˿�����
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_12 ;	 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOC,GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_12); 						 //PD.2 ����� 

}
 
