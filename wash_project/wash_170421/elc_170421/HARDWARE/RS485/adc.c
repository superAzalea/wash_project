#ifndef __ADC_C
#define __ADC_C
#include "adc.h"
#include "stdio.h"
__IO uint16_t ADC_ConvertedValue[macNOFCHANEL]={0,0,0,0};

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	// �� ADC IO�˿�ʱ��
	macADC_GPIO_APBxClock_FUN ( macADC_GPIO_CLK, ENABLE );
	// ���� ADC IO ����ģʽ
	// ADC 3��ͨ��
	GPIO_InitStructure.GPIO_Pin = macADC_PIN1;
	GPIO_InitStructure.GPIO_Pin = macADC_PIN2;
	GPIO_InitStructure.GPIO_Pin = macADC_PIN3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	// ��ʼ�� ADC IO
	GPIO_Init(macADC_PORT, &GPIO_InitStructure);				
}
static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;	
	// ��DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// ��ADCʱ��
	macADC_APBxClock_FUN ( macADC_CLK, ENABLE );	
	// ��λDMA������
	DMA_DeInit(macADC_DMA_CHANNEL);	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( u32 ) ( & ( macADCx->DR ) );	
	// �洢����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	
	// ��������С��Ӧ�õ�������Ŀ�ĵصĴ�С
	DMA_InitStructure.DMA_BufferSize = macNOFCHANEL;	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �洢����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	
	// �ڴ����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
	// ��ʼ��DMA
	DMA_Init(macADC_DMA_CHANNEL, &DMA_InitStructure);	
	// ʹ�� DMA ͨ��
	DMA_Cmd(macADC_DMA_CHANNEL , ENABLE);	
	// ADC ģʽ����
	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	// ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	// ת��ͨ������
	ADC_InitStructure.ADC_NbrOfChannel = macNOFCHANEL;			
	// ��ʼ��ADC
	ADC_Init(macADCx, &ADC_InitStructure);	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(macADCx, macADC_CHANNEL1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(macADCx, macADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(macADCx, macADC_CHANNEL3, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(macADCx, macADC_CHANNEL4, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(macADCx, macADC_CHANNEL5, 5, ADC_SampleTime_55Cycles5);	
	// ʹ��ADC DMA ����
	ADC_DMACmd(macADCx, ENABLE);	
	// ����ADC ������ʼת��
	ADC_Cmd(macADCx, ENABLE);	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(macADCx);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(macADCx));	
	// ADC��ʼУ׼
	ADC_StartCalibration(macADCx);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(macADCx));	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(macADCx, ENABLE);
}

void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}

short T[131] = {
	-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,
	-10, -9, -8, -7, -6, -5, -4, -3, -2, -1,
	0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
	70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
	100,101,102,103,104,105,106,107,108,109,
	110
};

float R[131] = {
	115.266, 108.146, 101.517, 96.3423, 89.5865,  84.219,  79.311,  74.536, 70.1698, 66.0898,
	62.2756, 58.7079, 56.3694, 52.2438, 49.3161, 46.5725,      44, 41.5878, 39.8239, 37.1988,
	35.2024, 33.3269, 31.5635, 29.9058, 28.3459, 26.8778, 25.4954, 24.1932, 22.5662, 21.8094,
	20.7184, 19.6891, 18.7177, 17.8005, 16.9341, 16.1156, 15.3418, 14.6181,  13.918, 13.2631,
	12.6431, 12.0561,    11.5, 10.9731, 10.4736,      10, 9.55074, 9.12445, 8.71983, 8.33566,
	7.97078, 7.62411, 7.29464, 6.98142, 6.68355, 6.40021, 6.13059, 5.87359, 5.62961, 5.39689,
	5.17519, 4.96392, 4.76253,  4.5705, 4.38736, 4.21263, 4.04589, 3.88673, 3.73476, 3.58962,
	3.45097, 3.31847, 3.19183, 3.07075, 2.95896, 2.84421, 2.73823, 2.63682, 2.53973, 2.44677,
	2.35774, 2.27249, 2.19073, 2.11241, 2.03732, 1.96532, 1.89627, 1.83003, 1.76647, 1.70547,
	1.64691, 1.59068, 1.53668, 1.48481, 1.43498, 1.38703, 1.34105, 1.29078, 1.25423,  1.2133,
	1.17393, 1.13604, 1.09958, 1.06448, 1.03069, 0.99815, 0.96681, 0.93662, 0.90753,  0.8795,
	0.85248, 0.82643, 0.80132, 0.77709, 0.75373, 0.73119, 0.70944, 0.68844, 0.66818, 0.64862,
	0.62973, 0.61148, 0.59387, 0.57683, 0.56038, 0.54448, 0.52912, 0.51426, 0.49989,   0.486,
	0.47256
};

int get_T_from_R(float rest)
{
	int i = 0;
	int ret_t = 0;
	int r_array_len = sizeof(R)/sizeof(float);
	float error1,error2 = 0;
	//printf("rest=%.3f/r_array_len=%d\n",rest,r_array_len);
	//printf("rest[%.4f]/R0[%.4f]/R6[%.4f]\n",rest,R[0],R[r_array_len-1]);
	if(rest>R[0])
	{
		rest = 115.266;
	}
	else if(rest<R[r_array_len-1])
	{
		rest = R[r_array_len-1];
	}
	for(i=0;i<sizeof(R)/sizeof(float);i++)
	{
		//printf("i=%d/rest=%.4f/%.4f/%.4f\n",i,rest,R[i],R[i+1]);
		if(rest<R[i]&&rest>=R[i+1])
		{
			if(rest==R[i])
			{
				//printf("-1-ret_t=%d\n",T[i]);
				return T[i];
			}
			else if(rest==R[i+1])
			{
				//printf("-1-ret_t=%d\n",T[i+1]);
				return T[i+1];
			}else{
				error1 = R[i] - rest ;
				error2 = rest - R[i+1];
			//	printf("error1=%.4f/error2=%.4f\n",error1,error2);
				if(error1>=error2)
				{
					ret_t = T[i];
				}
				else
				{
					ret_t = T[i+1];
				}
				//printf("-1-ret_t=%d\n",ret_t);
			}
			return ret_t;
		}
	}
	return -1;	
}


void sub_adc(void)
{
	adc_result[0] = ADC_ConvertedValue[0];
	adc_result[1] = ADC_ConvertedValue[1];
	adc_result[2] = ADC_ConvertedValue[2];
	adc_result[3] = ADC_ConvertedValue[3];
	//adc_result[1] = 200;//get_T_from_R(input_R);
	//adc_result[0] = 50;
}

#endif
