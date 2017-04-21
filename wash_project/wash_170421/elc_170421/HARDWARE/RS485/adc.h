#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"
#define Num_AdBuff 6

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    macADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    macADC_CLK                       RCC_APB2Periph_ADC1

#define    macADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    macADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    macADC_PORT                      GPIOC

#define    macNOFCHANEL											5
#define    macADC_PIN1                      GPIO_Pin_0
#define    macADC_CHANNEL1                  ADC_Channel_10

#define    macADC_PIN2                      GPIO_Pin_1
#define    macADC_CHANNEL2                  ADC_Channel_11

#define    macADC_PIN3                      GPIO_Pin_3
#define    macADC_CHANNEL3                  ADC_Channel_13

#define    macADC_PIN4                      GPIO_Pin_4
#define    macADC_CHANNEL4                  ADC_Channel_14

#define    macADC_PIN5                      GPIO_Pin_5
#define    macADC_CHANNEL5                 ADC_Channel_15

#define    macADCx                          ADC1
#define    macADC_DMA_CHANNEL               DMA1_Channel1


/**************************��������********************************/
void               ADCx_Init                               (void);
#ifdef __ADC_C

//u16 ad0[Num_AdBuff];
u16 adc_result[4] = {0,0,0,0};
void sub_adc(void);

#else
//extern u16 ad0[Num_AdBuff];
extern u16 adc_result[4];
extern void sub_adc(void);
#endif
#endif

