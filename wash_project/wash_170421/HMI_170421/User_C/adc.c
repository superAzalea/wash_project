/**************************************************************************************************
Project: TTK_ACPR
Filename: adc.c
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
#ifndef __ADC_C
#define __ADC_C

#include "stm32f10x.h"
#include "delay.h"
#include "Menu.h"
#include "SysPr.h"
#include "main.h" 
#include "faultProcess.h"
#include "adc.h"
	   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3	

void  Adc_Init(void)
{                                                                                                                                                                                                                                                                                                                   
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
	//PB0 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
 

	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//����ָ����ADC1��У׼�Ĵ���
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
	
	ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
 
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}				  

void Get_Adc(void)   
{
  	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  			    
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);				//ʹ��ָ����ADC1�����ת����������		 
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC ));		//�ȴ�ת������
	Adc_BatteryVoltag = ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}


#endif




























