/**************************************************************************************************
Project: TTK_ACPR
Filename: menu_sub.c
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
#ifndef __MENU_SUB_C
#define __MENU_SUB_C

#include "stm32f10x.h"
#include "delay.h"
#include "Menu.h"
#include "IIC.h"
#include "24CXX.h" 
#include "LCD_display.h"
#include "key.h"
#include "SysPr.h"
#include "adc.h"
#include "rtc.h"
#include "faultProcess.h"
#include "main.h"
#include "usart.h"
#include "timer.h"
#include "menu_sub.h"

void ClearDisBuff()
{
	u8 i = 0;
	for(i=0;i<121;i++)	DisBuff[i] = 0x20;	
};
void Menu_SoftwareVersion()
{
	char DisData[2] = {0,0};

	UserPrData_L = AT24CXX_ReadOneByte(NUM_USER_PR*2);		
	UserPrData_H = AT24CXX_ReadOneByte(NUM_USER_PR*2 + 1);	//��λ���λ����λ���λ

	hex_to_asc(DisData,UserPrData_H,1,0);	
	sendtobuff_n(2,1,DisData,1);				// ��λ
	sendtobuff(2,2,".");					//С����
	hex_to_asc(DisData,UserPrData_L,2,0);	// ��λ
	sendtobuff_n(2,3,DisData,2);	
}
//void Menu_FaultRecord(void)
//{
//	
//}

void M_999(void)//������
{
	char DisData[5] = {0,0,0,0,0};
//	static u8 flag_flash = 0;



//===============================================ͨѶ���Խ���===============================//

	//sendtobuff(0,10,"ͨѶ����");
	sendtobuff(0,10,"        ");
	
	//sendtobuff(1,0,"����ʱ��:");
	sendtobuff(1,0,"        :");
	hex_to_asc(DisData,(counter_rd/5),9,0);//counter_wr
	sendtobuff(1,9,DisData);
	//sendtobuff(1,19,"(��)");
	sendtobuff(1,19,"(  )");

	sendtobuff(2,0,"write:");
	hex_to_asc(DisData,counter_wr,9,0);//counter_wr
	sendtobuff(2,6,DisData);
	
	sendtobuff(2,16,"ok:");
	hex_to_asc(DisData,counter_wr_ok,9,0);//counter_wr_ok
	sendtobuff(2,19,DisData);

	sendtobuff(3,0,"read :");
	hex_to_asc(DisData,counter_rd,9,0);//counter_rd
	sendtobuff(3,6,DisData);
	
	sendtobuff(3,16,"ok:");
	hex_to_asc(DisData,counter_rd_ok,9,0);//counter_rd_ok
	sendtobuff(3,19,DisData);

//===============================================ͨѶ���Խ���===============================//
	
/*	
	if(SystemFault.bit.butttery_lv == 1)// ���Ƿѹ
	{
		flag_flash ^= 1;
		if(flag_flash)	sendtobuff(3,29,"$");//��ص�ѹͼ��
		else	sendtobuff(3,29,"&");
	}
	else
	{
		sendtobuff(3,29,"&");
	}
*/	
}

void M_14(void)//����ʱ�䶯̬��ʾ����
{
	char DisData[2] = {0,0};

	hex_to_asc(DisData,timer.hour,2,0);		//ʱ
	sendtobuff(1,13,DisData);
	sendtobuff(1,15,"Сʱ");
	
	hex_to_asc(DisData,timer.min,2,0);		//��
	sendtobuff(1,19,DisData);
	sendtobuff(1,21,"��");
	
	hex_to_asc(DisData,timer.hour,2,0);		//ʱ
	sendtobuff(2,13,DisData);
	sendtobuff(2,15,"Сʱ");
	
	hex_to_asc(DisData,timer.min,2,0);		//��
	sendtobuff(2,19,DisData);
	sendtobuff(2,21,"��");	
};
void M_15(void)//��������̬��ʾ����
{
	char DisData[4] = {0,0,0,0};
	char WeekData[7][3] = {{"��"},{"һ"},{"��"},{"��"},{"��"},{"��"},{"��"}};
	char (*p)[3];

	p = WeekData;

	hex_to_asc(DisData,timer.w_year,4,0);	//��
	sendtobuff_n(1,0,DisData,4);
	
	hex_to_asc(DisData,timer.w_month,2,0);	//��
	sendtobuff_n(1,6,DisData,2);

	hex_to_asc(DisData,timer.w_date,2,0);	//��
	sendtobuff_n(1,10,DisData,2);
		
	sendtobuff(2,4,*(p+timer.week));		//����

	hex_to_asc(DisData,timer.hour,2,0);		//ʱ
	sendtobuff_n(3,0,DisData,2);
	
	hex_to_asc(DisData,timer.min,2,0);		//��
	sendtobuff_n(3,3,DisData,2);

	hex_to_asc(DisData,timer.sec,2,0);		//��
	sendtobuff_n(3,6,DisData,2);	
	
	lcd_wrstring(0,0,DisBuff);	//��ʾBuff�������
};
void M_16(void)//��ص�ѹ
{
	u8 BatteryVoltag = 0;
	char TempArray[3] = {0,0,0};

	BatteryVoltag = (u32)Adc_BatteryVoltag*33 >> 12;
	hex_to_asc(TempArray,BatteryVoltag,2,1);
	
	sendtobuff(1,0,TempArray);
	sendtobuff(1,3,"V");	
}
void Menu_SetCalendar()//����������
{/***
	u8 i = 0;
	u8 Counter = 0;
	char TempArray[2] = {0,0};
	char data_keyin[6] = {0,0,0,0,0,0};
	char data_disply[6] = {0,0,0,0,0,0};
	u8 temp1 = 0,temp2 = 0,temp3 = 0;

	if(MenuIndex == 361)
	{
		temp1 = timer.w_year - 2000;
		temp2 = timer.w_month;
		temp3 = timer.w_date;
	}
	else
	{
		temp1 = timer.hour;
		temp2 = timer.min;
		temp3 = timer.sec;		
	}
	hex_to_asc(TempArray,temp1,2,0);
	sendtobuff_n(1,7,TempArray,2);
	hex_to_asc(TempArray,temp2,2,0);
	sendtobuff_n(1,11,TempArray,2);
	hex_to_asc(TempArray,temp3,2,0);
	sendtobuff_n(1,15,TempArray,2);			//��ǰֵ

	while(1)
	{
		if((KeyVal)&&(KeyVal <= 10))//����1~10��������1234567890 ���ò���
		{								
			if(KeyVal == KEY_0)	KeyVal = 0;//����10��������0
			data_keyin[Counter] = KeyVal;
			if(++Counter >= 6) Counter = 0;
			KeyVal = 0;
			sendtobuff(3,17,"�趨��..");	// ��"�趨��.."д��buff
		}
		
		for(i=0;i<6;i++)	data_disply[i] = data_keyin[i] + 0x30;//������ת��ΪASCII��
		
		if(KeyVal == KEY_SET)
		{
			if(MenuIndex == 361)
			{
				timer.w_year = 2000 + data_keyin[0]*10 + data_keyin[1];
				timer.w_month = data_keyin[2]*10 + data_keyin[3];
				timer.w_date = data_keyin[4]*10 + data_keyin[5];
			}
			else
			{
				timer.hour = data_keyin[0]*10 + data_keyin[1];
				timer.min = data_keyin[2]*10 + data_keyin[3];
				timer.sec = data_keyin[4]*10 + data_keyin[5];					
			}
			RTC_Set(timer.w_year,timer.w_month ,timer.w_date,timer.hour,timer.min,timer.sec);  //�������ڡ�ʱ��
			
			sendtobuff(3,17,"�趨���");	// ��"�趨���"д��buff
			lcd_wrstring(0,0,DisBuff);		// ��ʾbuff�����������
			delay_ms(1000);					// ��ʱ��ʾ"�趨���"
			sendtobuff(3,17,"        ");	// ���buff���"�趨���"
			
			Counter = 0;
			MenuIndex = MenuIndex/10;//�����ϼ��˵�
			KeyVal = 0;
			break;
		}											
		if(KeyVal == KEY_ESC)
		{
			Counter = 0;
			MenuIndex = MenuIndex/10;//�����ϼ��˵�
			KeyVal = 0;
			break;			
		}
		switch(Counter)
		{
			case 0:sendtobuff(3,7,"_         ");break;
			case 1:sendtobuff(3,7," _        ");break;
			case 2:sendtobuff(3,7,"    _     ");break;
			case 3:sendtobuff(3,7,"     _    ");break;
			case 4:sendtobuff(3,7,"        _ ");break;
			case 5:sendtobuff(3,7,"         _");break;
		}
		sendtobuff_n(2,7,&data_disply[0],1);
		sendtobuff_n(2,8,&data_disply[1],1);
		sendtobuff_n(2,11,&data_disply[2],1);
		sendtobuff_n(2,12,&data_disply[3],1);
		sendtobuff_n(2,15,&data_disply[4],1);
		sendtobuff_n(2,16,&data_disply[5],1);	//�趨ֵ	
		
		lcd_wrstring(0,0,DisBuff);// ��ʾbuff�������
	}  ***/
}

void Menu_UserPrPro(void)//�û���������
{  /****
	u8 i = 0;
	static u8 Flag_FirstSetPrData = 0;//�״����ò���ֵ��־λ   	
	static u16 UserPr_data_z = 0;
	
	UserPr_data_z = UserPr[UserPrIndex][DATA];//������ˢ��ǰ���ȱ����ֵ���Ա��趨����ʱʹ�þ�ֵ��
	
	
	if((KeyVal)&&(KeyVal <= 10))//����1~10��������1234567890 ���ò���
	{				
		if(KeyVal == KEY_0)	KeyVal = 0;//����10��������0
		
		flag_prSetting = 1;//���ò�����־λ��1
		
		if(Flag_FirstSetPrData == 0)	//��һ�ν������ò���ֵ״̬
		{
			Flag_FirstSetPrData = 1;	//���뿪��״̬ʱ���ǵ�����ñ�־λ
			Counter_KeyIn = 0;
			for(i=0;i<5;i++)	Data_KeyIn[i] = 0;//�״ν������ò���ֵ״̬ʱ����֮ǰ�����趨����ʱֵȫ������
								
			switch(UserPr[UserPrIndex][UNIT])
			{
				case U_BIT  :	{UserPrNum = 1;}break;//Bit
				
				case U_Hz :
				case U_C  :
				case U_Per:
				case U_344:	{UserPrNum = 2;}break;//�ٷֱ� ��

								 
				case U_MPa:				
				case U_Kw :
				case U_S:
				case U_343:	{UserPrNum = 3;}break;//�� ѹ�� �¶� Ƶ��
				
				case U_PI :
				case U_V  :
				case U_A  :
				case U_H  :	{UserPrNum = 4;}break;//KpKi ��ѹ  ���� Сʱ �� 
				
				default:break;
			}
		}							
		Data_KeyIn_Dis[Counter_KeyIn] = KeyVal;
		Counter_KeyIn++;
		if(Counter_KeyIn >= UserPrNum)	Counter_KeyIn = 0;		
		KeyVal = 0;
	} 
	
	if(KeyVal == KEY_SET)//�����趨״̬������ENTER
	{	
		if(flag_prSetting)//�����趨״̬������ENTER
		{	
			Flag_FirstSetPrData = 0;
			flag_prSetting = 0;//����ȷ�ϼ��󣬽��������ò�����־λ��0	
			for(i=0;i<5;i++)
			{
				Data_KeyIn[i] = Data_KeyIn_Dis[i];
			}
			for(i=0;i<5;i++)	Data_KeyIn_Dis[i] = 0;//����ȷ�ϼ��󣬽���¼������������0
	
			switch(UserPr[UserPrIndex][UNIT])
			{					
				case U_BIT  :UserPr[UserPrIndex][DATA] = Data_KeyIn[0];break;

				case U_Hz :
				case U_C  :
				case U_Per:
				case U_344:	UserPr[UserPrIndex][DATA] = Data_KeyIn[0]*10 + Data_KeyIn[1];break;//Hz �¶� �ٷֱ�
				
				case U_343:
				case U_MPa:
				case U_Kw :
				case U_S:	UserPr[UserPrIndex][DATA] = Data_KeyIn[0]*100 + Data_KeyIn[1]*10 + Data_KeyIn[2];break;				
				
				case U_PI :
				case U_V  :
				case U_A  :
				case U_H  :	UserPr[UserPrIndex][DATA] = Data_KeyIn[0]*1000 + Data_KeyIn[1]*100 + Data_KeyIn[2]*10 + Data_KeyIn[3];break;				
				
				default:break;					
			}
		
			if((UserPr[UserPrIndex][DATA] <= UserPr[UserPrIndex][MAX])&&(UserPr[UserPrIndex][DATA] >= UserPr[UserPrIndex][MIN]))//�����趨��ȷ
			{			
				Flag_FirstSetPrData = 0;				
				flag_firstInSetPrPage = 0;	
				
				UserPrData = UserPr[UserPrIndex][DATA];	//�������ֵ��ȷ����������
				UserPrData_H = (UserPrData>>8)&0xff;//��8λ
				UserPrData_L = UserPrData&0xff;//��8λ	
				
				MBS_HoldRegs[UserPrIndex] = UserPr[UserPrIndex][DATA];
				
				AT24CXX_WriteOneByte(UserPrIndex*2,UserPrData_L);//д��EEPROM ��8λд��͵�ַ
				AT24CXX_WriteOneByte(UserPrIndex*2+1,UserPrData_H);//д��EEPROM	��8λд��ߵ�ַ

				MBS_HoldRegs[90] = UserPrIndex;					//90�ŵ�ַ
				MBS_HoldRegs[91] = UserPr[UserPrIndex][DATA];	//91������
				flag_writing_0x10 = 1;
				
 				if(UserPrIndex == 59)//���Ҳ�����λ
 				{
					flag_warning = 12;//���Ҳ����ָ��ɹ�
 				}
			}
			else//�����趨����
			{
				UserPr[UserPrIndex][DATA] = UserPr_data_z;//�趨����ʱʹ�þ�ֵ
				Flag_FirstSetPrData = 0;				
				flag_firstInSetPrPage = 0;

				flag_warning = 2;//�趨����			
			}
		}
		else//�ǲ����趨״̬(Ϊ�˷�ֹEEPROM���ݴ���ʹ���û����������ֵ�ڳ�ʼ������ǳ��޵�)
		{
			if((UserPr[UserPrIndex][DATA] <= UserPr[UserPrIndex][MAX])&&(UserPr[UserPrIndex][DATA] >= UserPr[UserPrIndex][MIN]))//�����趨��ȷ
			{
				UserPrData = UserPr[UserPrIndex][DATA];	//�������ֵ��ȷ����������
				UserPrData_H = (UserPrData>>8)&0xff;//��8λ
				UserPrData_L = UserPrData&0xff;//��8λ	
				
				MBS_HoldRegs[UserPrIndex] = UserPr[UserPrIndex][DATA];
				
				AT24CXX_WriteOneByte(UserPrIndex*2,UserPrData_L);//д��EEPROM ��8λд��͵�ַ
				AT24CXX_WriteOneByte(UserPrIndex*2+1,UserPrData_H);//д��EEPROM	��8λд��ߵ�ַ
				
				MBS_HoldRegs[90] = UserPrIndex;					//90�ŵ�ַ
				MBS_HoldRegs[91] = UserPr[UserPrIndex][DATA];	//91������
				flag_writing_0x10 = 1;

				flag_warning = 11;//�趨��ȷ
			}
			else//�����趨����
			{
				flag_warning = 2;//�趨����
 				UserPr[UserPrIndex][DATA] = UserPr_data_z;//�趨����ʱʹ�þ�ֵ(��ʱ��ֵΪ0)
			}
			Flag_FirstSetPrData = 0;				
			flag_firstInSetPrPage = 0;					
		}
		KeyVal = 0;
	}
	if(KeyVal == KEY_ESC) 
	{	
		MenuIndex = MenuIndex/10;//�����һ���˵�				
		Flag_FirstSetPrData = 0;	
		flag_prSetting = 0;//����ESC���󣬽��������ò�����־λ��0				
		flag_firstInSetPrPage = 0;
		for(i=0;i<5;i++)	Data_KeyIn_Dis[i] = 0;//����ESC���󣬽���¼������������0
		KeyVal = 0;	
	}   ****/
}

void Menu_UserPrDis(void)//�û�������ʾ
{  /****
	char DisTemp[5] = {0,0,0,0,0};
	char temp_data[5] = {0,0,0,0,0};
	char temp_max[5] = {0,0,0,0,0};
	char temp_min[5] = {0,0,0,0,0};
	u8 data_num = 0,data_n = 0,data_dis = 0;//����λ����С��λ����Ҫ��ʾ������(��С����)
 
	if(0 == flag_firstInSetPrPage)
	{
		flag_firstInSetPrPage = 1;
	}			
	if(flag_prSetting == 0)//���������ò���״̬
	{	
		switch(UserPr[UserPrIndex][UNIT])
		{
			case U_BIT	:{data_num=1;data_n=0,data_dis=data_num;}break;//1 0
			
			case U_Hz	:{data_num=2;data_n=0,data_dis=data_num;}break;
			case U_C	:{data_num=2;data_n=0,data_dis=data_num;}break;			
			case U_Per	:{data_num=2;data_n=0,data_dis=data_num;}break;
			case U_344	:{data_num=2;data_n=0,data_dis=data_num;}break;//2 0

			case U_S	:{data_num=3;data_n=0,data_dis=data_num;}break;
			case U_343	:{data_num=3;data_n=0,data_dis=data_num;}break;//3 0		
			
			case U_Kw	:{data_num=3;data_n=1,data_dis=data_num+1;}break;//3 1
			case U_MPa	:{data_num=3;data_n=2,data_dis=data_num+1;}break;//3 2
			
			case U_PI	:{data_num=4;data_n=0,data_dis=data_num;}break;
			case U_H	:{data_num=4;data_n=0,data_dis=data_num;}break;//4 0
			
			case U_V	:{data_num=4;data_n=1,data_dis=data_num+1;}break;
			case U_A	:{data_num=4;data_n=1,data_dis=data_num+1;}break;//4 1
			
			default:break;			
		}
		
//������ת���ɵ����ַ�
		hex_to_asc(temp_data,UserPr[UserPrIndex][DATA],data_num,data_n);//����
		hex_to_asc(temp_max,UserPr[UserPrIndex][MAX],data_num,data_n);//���ֵ
		hex_to_asc(temp_min,UserPr[UserPrIndex][MIN],data_num,data_n);//��Сֵ

//����ʾbuffer��д������
		sendtobuff(0,0,Tab_MenuData[search(Tab_MenuNum,NUM_PAGE,MenuIndex)]);//�˵��ľ�̬����
		sendtobuff(2,7,temp_data);//����
		if((UserPr[UserPrIndex][UNIT] != U_BIT))//��λ��bit�ģ�ֻ��0��1����ֵ
		{
			sendtobuff(1,7,temp_max);//���ֵ
			sendtobuff(1,22,temp_min);//��Сֵ
			sendtobuff(2,7+data_dis,Tab_unit[UserPr[UserPrIndex][UNIT]]);//��λ
		}

		lcd_wrstring(0,0,DisBuff);//LCD��ʾ����
	}
	if(flag_prSetting)//�������ò���״̬
	{
		if(flag_shining == 0)//��ʾ����
		{
			
			switch(UserPr[UserPrIndex][UNIT])
			{
	//1λ����			
				case U_BIT :	
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;
					sendtobuff(2,7,DisTemp);				
				}break;
	//1λ���� 2λС��
				case U_MPa:	//ѹ��
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;
					DisTemp[1] = 0x2e;//С����					
					DisTemp[2] = Data_KeyIn_Dis[1]+0x30;
					DisTemp[3] = Data_KeyIn_Dis[2]+0x30;	
					sendtobuff(2,7,DisTemp);
				}break;
	//2λ����			
				case U_Hz:		//Ƶ��
				case U_C :		//�¶�
				case U_344:
				case U_Per:	//�ٷֱ�
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;
					DisTemp[1] = Data_KeyIn_Dis[1]+0x30;
					sendtobuff(2,7,DisTemp);					
				}break;				
	//2λ���� 1λС��			
				case U_Kw:							
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;				
					DisTemp[1] = Data_KeyIn_Dis[1]+0x30;
					DisTemp[2] = 0x2e;		//С����
					DisTemp[3] = Data_KeyIn_Dis[2]+0x30;
					sendtobuff(2,7,DisTemp);				
				}break;	
	//3λ����	
				case U_343:
				case U_S:	//�� 
				{		
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;
					DisTemp[1] = Data_KeyIn_Dis[1]+0x30;
					DisTemp[2] = Data_KeyIn_Dis[2]+0x30;	
					sendtobuff(2,7,DisTemp);					
				}break;				
	//3λ���� 1λС��
				case U_V :	//��ѹ
				case U_A :	//����
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;
					DisTemp[1] = Data_KeyIn_Dis[1]+0x30;				
					DisTemp[2] = Data_KeyIn_Dis[2]+0x30;
					DisTemp[3] = 0x2e;		//С����
					DisTemp[4] = Data_KeyIn_Dis[3]+0x30;		
					sendtobuff(2,7,DisTemp);			
				}break;	
	//4λ����			
				case U_PI:	//PI����
				case U_Num4://4λ����
				case U_H :	//Сʱ				
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;
					DisTemp[1] = Data_KeyIn_Dis[1]+0x30;				
					DisTemp[2] = Data_KeyIn_Dis[2]+0x30;
					DisTemp[3] = Data_KeyIn_Dis[3]+0x30;
					sendtobuff(2,7,DisTemp);				
				}break;			
				
				default:break;
			}
		}
		else//��ʾ�հ�(�趨����ʱ����˸Ч��)
		{
			switch(UserPr[UserPrIndex][UNIT])
			{
	//1λ����			
				case U_BIT :	
				{				
					sendtobuff(2,7," ");				
				}break;
	//1λ���� 2λС��
				case U_MPa:	//ѹ��
				{
					switch(Counter_KeyIn)
					{
						case 0:sendtobuff(2,7," ");break;
						case 1:sendtobuff(2,9," ");break;
						case 2:sendtobuff(2,10," ");break;
					}
				}break;
	//2λ����			
				case U_Hz:		//Ƶ��
				case U_C :		//�¶�
				case U_344:
				case U_Per:	//�ٷֱ�
				{
					switch(Counter_KeyIn)
					{
						case 0:sendtobuff(2,7," ");break;
						case 1:sendtobuff(2,8," ");break;
					}					
				}break;				
	//2λ���� 1λС��			
				case U_Kw:							
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;				
					DisTemp[1] = Data_KeyIn_Dis[1]+0x30;
					DisTemp[2] = 0x2e;		//С����
					DisTemp[3] = Data_KeyIn_Dis[2]+0x30;
					sendtobuff(2,7,DisTemp);
					switch(Counter_KeyIn)
					{
						case 0:sendtobuff(2,7," ");break;
						case 1:sendtobuff(2,8," ");break;
						case 2:sendtobuff(2,10," ");break;
					}					
				}break;	
	//3λ����	
				case U_343:
				case U_S:	//�� 
				{		
					switch(Counter_KeyIn)
					{
						case 0:sendtobuff(2,7," ");break;
						case 1:sendtobuff(2,8," ");break;
						case 2:sendtobuff(2,9," ");break;
					}					
				}break;				
	//3λ���� 1λС��
				case U_V :	//��ѹ
				case U_A :	//����
				{
					switch(Counter_KeyIn)
					{
						case 0:sendtobuff(2,7," ");break;
						case 1:sendtobuff(2,8," ");break;
						case 2:sendtobuff(2,9," ");break;
						case 3:sendtobuff(2,11," ");break;
					}				
				}break;	
	//4λ����			
				case U_PI:	//PI����
				case U_Num4://4λ����
				case U_H :	//Сʱ				
				{
					DisTemp[0] = Data_KeyIn_Dis[0]+0x30;
					DisTemp[1] = Data_KeyIn_Dis[1]+0x30;				
					DisTemp[2] = Data_KeyIn_Dis[2]+0x30;
					DisTemp[3] = Data_KeyIn_Dis[3]+0x30;
					sendtobuff(2,7,DisTemp);				
					switch(Counter_KeyIn)
					{
						case 0:sendtobuff(2,7," ");break;
						case 1:sendtobuff(2,8," ");break;
						case 2:sendtobuff(2,9," ");break;
						case 3:sendtobuff(2,10," ");break;
					}				
				}break;			
				
				default:break;
			}		
		}	
		lcd_wrstring(0,0,DisBuff);
	}	  ****/
}

void Menu_FactoryPrPro(void)//���Ҳ���
{
}
void Menu_DebugPrPro(void)//���Բ���
{
}
void Menu_FaultRecordPro(void)//���ϼ�¼
{
}
void Menu_UserPasswordPro(void)//�û�����
{
}

void Password_Check(void)//����У��
{/***
	u8 add = 0,index_CheckOk = 0;
	u16 data[4] = {0,0,0,0};
	static u8 KeyIn[4] = {0,1,2,3};
	char a[4] = {0,0,0,0};
	static u8 counter = 0;
	static u8 flag_firstin= 0;

	while(1)
	{	
		if(flag_firstin == 0)//�״ν���
		{		
			flag_firstin = 1;
			KeyVal = 0;
			counter = 0;
			KeyIn[0] = KeyIn[1] = KeyIn[2] = KeyIn[3] = 0;
			ClearDisBuff(); 
			sendtobuff(0,0,"����������");
		}
		
		if((KeyVal>0)&&(KeyVal<=10))
		{
			if(KeyVal==10)	KeyVal = 0;
			
			KeyIn[counter] = KeyVal;
			counter++;
			if(counter >= 4)	counter = 0;		
			KeyVal = 0;
		}
		a[0] = KeyIn[0] + 0x30;
		a[1] = KeyIn[1] + 0x30;
		a[2] = KeyIn[2] + 0x30;
		a[3] = KeyIn[3] + 0x30;
		sendtobuff_n(2,13,a,4);
		sendtobuff_n(3,13,"    ",4);
		sendtobuff(3,13+counter,"_");
		switch(MenuIndex)
		{
			case 2 :{index_CheckOk = 0;add = ADD_PSWD_USER;}break;
			case 3 :{index_CheckOk = 1;add = ADD_PSWD_FACTORY;}break;
			case 51:{index_CheckOk = 2;add = ADD_PSWD_USER;}break;
			case 52:{index_CheckOk = 3;add = ADD_PSWD_FACTORY;}break;
			case 53:{index_CheckOk = 4;add = ADD_PSWD_SPUSER;}break;
			case 54:{index_CheckOk = 5;add = ADD_PSWD_SPFACTORY;}break;
			default:break;
		}				
		if(KeyVal == KEY_SET)
		{
			data[0] = AT24CXX_ReadOneByte(add + 0);
			data[1] = AT24CXX_ReadOneByte(add + 1);	
			data[2] = AT24CXX_ReadOneByte(add + 2);	
			data[3] = AT24CXX_ReadOneByte(add + 3);
			
			if((KeyIn[0] == data[0])&&(KeyIn[1] == data[1])&&(KeyIn[2] == data[2])&&(KeyIn[3] == data[3]))
			{
				lcd_wrstring(3,22,"������ȷ");
				CheckOk[index_CheckOk] = 1;
			}
			else
			{
				lcd_wrstring(3,22,"�������");								
				CheckOk[index_CheckOk] = 0;
				MenuIndex = MenuIndex/10;	//�����ϼ�
			}	
			delay_ms(1000);
			lcd_wrstring(3,22,"        ");
			KeyVal = 0;
			flag_firstin = 0;
			break;
		}
		if(KeyVal == KEY_ESC)
		{
			KeyVal = 0;
			flag_firstin = 0;	
			MenuIndex = MenuIndex/10;		//�����ϼ�		
			break;
		}	
		lcd_wrstring(0,0,DisBuff);	
	}***/
}
void Password_Set(void)//�����趨
{  /***
	u8 add = 0,index = 0;
	static u8 KeyIn[4] = {0,1,2,3};
	char a[4] = {0,0,0,0};
	static u8 counter = 0;
	static u8 flag_firstin= 0;

	while(1)
	{
		if(flag_firstin==0)
		{		
			flag_firstin = 1;
			counter = 0;
			KeyIn[0] = KeyIn[1] = KeyIn[2] = KeyIn[3] = 0;
		}
		ClearDisBuff(); 
		sendtobuff(0,0,"������������");

		if((KeyVal>0)&&(KeyVal<=10))
		{
			if(KeyVal==10)	KeyVal = 0;
			
			KeyIn[counter] = KeyVal;
			counter++;
			if(counter >= 4)	counter = 0;  
			
			KeyVal = 0;
		}
		a[0] = KeyIn[0] + 0x30;
		a[1] = KeyIn[1] + 0x30;
		a[2] = KeyIn[2] + 0x30;
		a[3] = KeyIn[3] + 0x30;
		sendtobuff_n(2,13,a,4);
		sendtobuff_n(3,13,"    ",4);
		sendtobuff(3,13+counter,"_");
		
		switch(MenuIndex)
		{
			case 2 :{index = 0;add = ADD_PSWD_USER;}break;
			case 51:{index = 1;add = ADD_PSWD_USER;}break;
			case 3 :{index = 2;add = ADD_PSWD_FACTORY;}break;
			case 52:{index = 3;add = ADD_PSWD_FACTORY;}break;
			case 53:{index = 4;add = ADD_PSWD_SPUSER;}break;
			case 54:{index = 5;add = ADD_PSWD_SPFACTORY;}break;
			default:break;
		}	
		
		if(KeyVal == KEY_SET)
		{
			AT24CXX_WriteOneByte(add + 0,KeyIn[0]);
			AT24CXX_WriteOneByte(add + 1,KeyIn[1]);	
			AT24CXX_WriteOneByte(add + 2,KeyIn[2]);	
			AT24CXX_WriteOneByte(add + 3,KeyIn[3]);
	  
			lcd_wrstring(3,22,"�趨���");
			delay_ms(1000);
			lcd_wrstring(3,22,"        ");
			
			KeyVal = 0;
			flag_firstin = 0; 
			MenuIndex = MenuIndex/10;//�����ϼ�		
			break;			
		}
		if(KeyVal == KEY_ESC)
		{
			KeyVal = 0;
			flag_firstin = 0;			
			MenuIndex = MenuIndex/10;//�����ϼ�		
			break;
		}
		if(flag_5sKeyNoAct)
		{
			flag_5sKeyNoAct = 0;
			CheckOk[index] = 0;
			flag_firstin = 0;
			MenuIndex = 999;
			break;
		}		
		lcd_wrstring(0,0,DisBuff);
	}  ***/
}

void Password_Show(void)
{  /***
	u8 add = 0;
	char data[4] = {0,0,0,0};

	ClearDisBuff(); 
	switch(MenuIndex)
	{
		case 53:add = ADD_PSWD_USER;break;
		case 54:add = ADD_PSWD_FACTORY;break;
		default:break;
	}

	data[0] = AT24CXX_ReadOneByte(add + 0) + 0x30;
	data[1] = AT24CXX_ReadOneByte(add + 1) + 0x30;	
	data[2] = AT24CXX_ReadOneByte(add + 2) + 0x30;	
	data[3] = AT24CXX_ReadOneByte(add + 3) + 0x30;
	
	sendtobuff(0,0,"�û���������:");
	sendtobuff_n(0,13,data,4);

	lcd_wrstring(0,0,DisBuff);
	
	if(KeyVal == KEY_ESC)
	{
		KeyVal = 0;
		MenuIndex = 5;
		if(CheckOk[4] == 1)	CheckOk[4] = 0;	//��ѯ���룬������У��OK״̬
		if(CheckOk[5] == 1)	CheckOk[5] = 0;
	}	  ****/
}

#endif


