#ifndef __TIMER_H
#define __TIMER_H

#define TIM3_IRQn   29

#ifdef __TIMER_C	  

u16 ad_ps1, ad_ps2, ad_temp1, ad_temp2;
u16 dis_ad_ps1 = 0;
u16 dis_ad_temp1 = 0;
u8 flag_fault = 0;//���ϱ�־λ
u8 flag_FaultFlash = 0;//������˸��־λ

//u8 flag_buzz = 0;//���������־λ
u8 flag_buzz_2 = 0;
u8 flag_warning = 0;
u8 flag_holding = 0;//ͨѶ���ֱ�־λ
//u8 flag_50ms = 0;
//u8 flag_100ms = 0;
u8 flag_500ms_rd= 0;
u8 flag_1s_wr= 0;
u8 flag_wr_more = 0;
u8 flag_2s_WrSysPr = 0;
u8 flag_500ms = 0;
u8 flag_1s = 0;
u8 flag_5s = 0;
u8 flag_shining = 0;//0.5����˸(�趨����ʱ��)
u8 flag_InitFinish = 0;//��ʼ����ɱ�־λ
u8 flag_usart_read_error = 0;


u32 counter_rd = 0;
u32 counter_rd_err = 0;
u32 counter_wr06_err = 0;
u32 counter_wr10_err = 0;
u32 counter_wr = 0;
u32 counter_wr_handshake = 0;
u32 counter_wr_ok = 0;



u16 time_1s_sleep = 0;//����ʱ�� ��λ ��

void Timerx_Init(u16 arr,u16 psc); 
void TIM2_Configuration(void);
void NVIC_Configuration(void);

extern EPASS  passdisp;

#else

extern u16 ad_ps1, ad_ps2, ad_temp1, ad_temp2;
extern u16 dis_ad_ps1;
extern u16 dis_ad_temp1;
extern u8 flag_fault;
extern u8 flag_FaultFlash;//������˸��־λ

//extern u8 flag_buzz;
extern u8 flag_buzz_2;
extern u8 flag_warning;
extern u8 flag_holding;//ͨѶ���ֱ�־λ
//extern u8 flag_50ms;
//extern u8 flag_100ms;
extern u8 flag_500ms_rd;
extern u8 flag_1s_wr;
extern u8 flag_wr_more;


extern u8 flag_2s_WrSysPr;
extern u8 flag_500ms;
extern u8 flag_1s;
extern u8 flag_5s;
extern u8 flag_shining;//0.5����˸(�趨����ʱ��)
extern u8 flag_InitFinish;//
extern u8 flag_usart_read_error;

extern u32 counter_rd;
extern u32 counter_rd_err;
extern u32 counter_wr06_err;
extern u32 counter_wr10_err;
extern u32 counter_wr;
extern u32 counter_wr_handshake;
extern u32 counter_wr_ok;

extern u16 time_1s_sleep;//����ʱ�� ��λ ��

extern void Timerx_Init(u16 arr,u16 psc); 
extern void TIM2_Configuration(void);
extern void NVIC_Configuration(void);

#endif
#endif

