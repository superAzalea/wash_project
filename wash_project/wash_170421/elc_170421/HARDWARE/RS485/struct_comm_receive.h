#ifndef __STRUCT_COMM_RECEIVE_H
#define __STRUCT_COMM_RECEIVE_H
#include "sys.h"	 

typedef union
{
	struct
	{
		u16  wash_1_1			:    	1; // ��Ƶ���̵��� X1
		u16  wash_2_1			:		1;// ��Ƶ���̵��� X2
		u16  soap_liquid_3_1		:		1; // ��Һ3
		u16	 soap_liquid_2_1	    :		1; // ��Һ2
		u16	 soap_liquid_1_1	    :		1; // ��Һ1
		u16  cold_water_1	  	: 	    1; // ��ˮ
		u16  hot_water_1	  	:  	    1; // ��ˮ
		u16  calefaction_1	: 	    1;//����
		u16  drain_1	 	    : 	    1;  //��ˮ
		u16  skid_1		    : 	    1;//ɲ��
		u16  door_lock_1	    :  	    1;//����
		u16  backup_one_1     :       1;//����
		
		u16  backup_two_1     :       1; //����
		u16  backup_three_1   :       1; //����
		u16  backup_four_1    :       1; //����
	    u16  backup_five_1    :       1; //����
		
		

	}bit;
	u16 all;

}StructCommReceiveWord;


#ifdef  __STRUCT_COMM_RECEIVE_C

StructCommReceiveWord structCommReceive;

void getCommReceive(void);

#else 
extern StructCommReceiveWord structCommReceive;


extern void getCommReceive(void);

#endif
#endif

