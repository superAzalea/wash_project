/**************************************************************************************************
Project: TTK_ACPR
Filename: SystemInit.c
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
#ifndef __SystemInit_C
#define __SystemInit_C

#include "stm32f10x.h"
#include "SystemInit.h"

void GPIOInit(void)
{
	
    RCC->APB2ENR |= RCC_APB2Periph_GPIOA;//PA   
    GPIOA->CRL = 0x33333333;    //LCD数据口PA0~7=0  (推挽输出，最大速度50mhz)
    GPIOA->CRH &= 0x000FF00F;   //
    GPIOA->CRH |= 0x00033003;   //3:输出	LCD数据口PA0~7=0，LED灯PA8 PA11 PA12
	GPIOA->ODR = 0x1900;		//LCD数据口PA0~7=0，LED灯PA8 PA11 PA12=0，没用到PA9 PA10 PA14 PA15 = 0
	//	GPIOA->ODR = 0xFFFF;
    
    RCC->APB2ENR |= RCC_APB2Periph_GPIOB;//PB
    //GPIOB->CRL &= 0xFF0FFF00;   //PB0:AD输入�
    //GPIOB->CRL |= 0x00300038;   //PB1:rs485使能脚，PB5 output
	  GPIOB->CRL &= 0xFF0FFF00;   //PB0:FS输出 ()
    GPIOB->CRL |= 0x00300033;   //PB1:L-RUN输出，PB5 output
    //GPIOB->CRH &= 0x0000FF00;   //
    //GPIOB->CRH |= 0x33330033;   //3:输出	PB12 13 14 15:矩阵键盘的输出部分，PB9:rs485使能脚，PB8:Buzz
	  GPIOB->CRH &= 0x00000000;   //
	GPIOB->CRH |= 0x33333333;   //3:输出	PB12 13 14 15:矩阵键盘的输出部分，PB9:rs485使能脚，PB8:Buzz,PB10,PB11:29,30脚灯输出。
    GPIOB->ODR = 0x0D22;        //
     // GPIOB->ODR = 0xFFFF;  
  
  RCC->APB2ENR |= RCC_APB2Periph_GPIOC;//PC
   // GPIOC->CRL = 0x88333333;    //PC0~5:CD RD WR CE RST BLA输出 PC6 PC7:普通按键输入
	  GPIOC->CRL = 0x33333333;    //PC0~5:CD RD WR CE RST BLA输出 PC6 PC7:Led灯
    GPIOC->CRH = 0x33338888;    //PC8 9 10 11:矩阵键盘的输入部分 PC12:FS输出 	[PC13 14 15时钟部分，待定为输出]
      GPIOC->ODR = 0x10C0;        //
//GPIOC->ODR = 0xFFFF;

    RCC->APB2ENR |= RCC_APB2Periph_GPIOD;//PD
    GPIOD->CRL &= 0xFFFFF0FF;
    GPIOD->CRL |= 0x00000300;	//PD2 WP EEPROM的读写保护脚
    GPIOD->ODR &= 0xFFFB;		//PD2
	
}

#endif

