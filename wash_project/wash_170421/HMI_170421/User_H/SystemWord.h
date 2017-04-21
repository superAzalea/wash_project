#ifndef __SYSTEMWORD_H
#define __SYSTEMWORD_H

struct SYSTEMCMD_BITS
{
	u16 Start:1;			//0	����     
	u16 Stop:1;				//1	ֹͣ
	u16 OnLoad:1;			//2	����
	u16 Unload:1;			//3	ж��
	u16 rsvd12:1;			//4~15 ����
};
union SYSTEMCMD_VAR
{
   	u16						all;
   	struct SYSTEMCMD_BITS	bit;
};

struct FAULTWORD_BITS
{
	u16 usart:1;			//0	ͨѶ����
	u16 a:1;				//1	
	u16 b:1;				//2	
	u16 c:1;				//3	
	u16 rsvd12:1;			//4~15 ����
};
union FAULTWORD_VAR
{
   	u16						all;
   	struct FAULTWORD_BITS	bit;
};

#ifdef __SYSTEMWORD_C

volatile union SYSTEMCMD_VAR glSystemCmd;
volatile union FAULTWORD_VAR glFaultWord;

#else

extern volatile union SYSTEMCMD_VAR glSystemCmd;
extern volatile union FAULTWORD_VAR glFaultWord;

#endif
#endif

