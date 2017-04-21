//#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart_Frequ.h"
#include "rs485.h"
#include "adc.h"
#include "timer.h"
#include "faultProcess.h"
#include "struct_comm_receive.h"
#include "Input_signal.h"
#include "Inverter.h"
int main(void)
{	 
	TIM3_Int_Init(9,7199);
	NVIC_Configuration();
	delay_init();	    	 //��ʱ������ʼ��	  
	sub_gpio_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	RS485_Init(9600);	//��ʼ��RS485
	RS485_Init3(9600);
	ADCx_Init();
	while(1)
	{
		int i;
		modbus_dataUnpack_slave();		
		if(flag_1s == 1) //1s
		{
			flag_1s = 0;
			sub_adc();
			getInput();			
			for(i = 0;i < 6; i++) //ADֵ
			{
				if(i == 4)
				{
					MBS_HoldRegs[58 + i] = SystemState.all;
				}
				else if(i == 5)
				{
					MBS_HoldRegs[58 + i] = MBS_HoldRegs3[4];
				}
				else
				{
					MBS_HoldRegs[58 + i] = adc_result[i]; 

				}
			}
		}		
		getCommReceive(); //����hmi��������RO1~RRO12+BPQ_X2\BPQ_X1��״̬
	} 
}


