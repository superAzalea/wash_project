#include "sys.h"
#include "stm32f10x.h"
void sub_gpio_init(void)
{
//3��� 8����
//PA	
    RCC->APB2ENR |= RCC_APB2Periph_GPIOA;//ʹ��PAʱ��   
	
   // GPIOA->CRL = 0x88888888;  //PA0~6 AD���� PA7 IO����
	
    GPIOA->CRH &= 0xFFF00FF0;   //
	GPIOA->CRH |= 0x00033003;//PA8��RO11�� PA11(RO12) PA12(RO10)���
	GPIOA->ODR = 0xFFFF;		//����ߵ�ƽ

//PB    
    RCC->APB2ENR |= RCC_APB2Periph_GPIOB;//ʹ��PBʱ��
	
    GPIOB->CRL &= 0XFF0FFF00;   //
    GPIOB->CRL |= 0x00808033;   //PB0 PB1:���(rs485ʹ�ܽ�) PB3���� PB5����
	
    GPIOB->CRH &= 0x0000FF00;   //
    GPIOB->CRH |= 0x33330088;   //PB8 9���� PB12 13 14 15:���
	
    GPIOB->ODR = 0xFFFF;        //

//PC	
    RCC->APB2ENR |= RCC_APB2Periph_GPIOC;//ʹ��PCʱ��
		
    GPIOC->CRL &= 0x00FFFF00;   //
    GPIOC->CRL |= 0x33000088;    //
	GPIOC->CRH &= 0xFFF00000;
    GPIOC->CRH |= 0x00088333;    //
    GPIOC->ODR = 0xFFFF;        //


    RCC->APB2ENR |= RCC_APB2Periph_GPIOD;//PD �°��·ͼPD2ΪX4����
    GPIOD->CRL &= 0XFFFFF0FF;
    GPIOD->CRL |= 0X00000800;	//PD2����(WP EEPROM�Ķ�д������)
    GPIOD->ODR &= 0xFFFF;		//PD2


}

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
