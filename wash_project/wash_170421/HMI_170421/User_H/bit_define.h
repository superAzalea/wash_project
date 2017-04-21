#ifndef __BIT_DEFINE_H
#define __BIT_DEFINE_H

unsigned char _manual_mode;
//unsigned char input_door_switch;
unsigned char run_state;
//unsigned char _enable_display;

unsigned int run_frequency;//����Ƶ��
unsigned int acce_time;//����ʱ��
unsigned int dece_time;//����ʱ��

unsigned char set_liquid_height;//�趨Һλ�߶�
unsigned char _1s_timer	;
unsigned char flag_read_Inv;
unsigned char _key_pro_ok_2;
extern unsigned char _set_mode_symbol;
extern unsigned char _if_save_data;
//unsigned char set_bit;//b0--����ʱ���  b1--����ʱ���� b2--�����趨�¶� b3--����Һλ�߶�
unsigned char set_num;//���÷��� 0--�� 1--�� 2--�� 3--�¶� 4--ˮλ
unsigned char set_num_timer;//���ʱ��
unsigned char wash_run_time;//ϴ������ʱ��
unsigned char wash_stop_time;//ϴ��ֹͣʱ��
//unsigned char soap_liquid_run_time;//��Һ����ʱ��
//unsigned char dehydration_state;//��ˮ״̬
//unsigned char auto_mode_run_step;//�Զ�ģʽ���в�
//unsigned char wait_state;//ˮ��״̬  //d5������ˮ, d4������ˮ, d3������Һ, d2�������, d1������ˮ,d0������ˮ,
//unsigned char auto_mode_liquid_height;//�Զ��趨ģʽҺλ
//unsigned char auto_mode_wash_dehydration;//�Զ�ģʽϴ�Ӻ���ˮ
unsigned char auto_mode_s;//�Զ�ģʽ����ʱ����
unsigned char auto_mode_m;//�Զ�ģʽ����ʱ���
//unsigned char auto_mode_temp;//�Զ�ģʽ�趨�¶�
//unsigned char auto_mode_soap_liquid;//�Զ�ģʽ��Һ
//unsigned char add_water_dehydration;//��ˮ���ʵ�Һλ��ˮ
unsigned char soap_liquid_num;//�ڼ�����Һ
unsigned char dehydration_num;//�ڼ�����ˮ

unsigned char mode_data[200]; //���ݵ�ַ
unsigned char mode_data_buffer[200];
unsigned char fault[12];
unsigned char *data_group2;



//unsigned char trans_data_num;//����ڼ�������
//unsigned char tran_num;//����ڼ�������

unsigned char program_step_num;//����ʱ�ĳ�����
unsigned char soap_liquid_time;//��Һ����ʱ��             
unsigned char tell_stop_num;//��ʾֹͣ�Ĵ���
//unsigned char receive_num;//�������ݵ�����
//unsigned int error_for_commu_num;//ͨѶ������ϼ���
unsigned char new_fault;//�¹���
//unsigned char check_fault_num;//�����ϼ���
//unsigned char commun_state;//ͨѶ״̬
unsigned char commun_interval;//ͨѶ���
extern unsigned char back_light_timer;//����ʱ��
extern unsigned char auto_run_mode;//�Զ�����ģʽ


unsigned char wash_provide_timer;       //ϴ�ӿ�ʼǰ��׼��ʱ��

unsigned char single_wash_have_water_time;     //������ˮʱ��
unsigned char single_wash_drain_time;          //������ˮʱ��
unsigned char single_wash_complete_delay_time; //����������ʱ
unsigned char single_wash_complete_skid;       //��������ɲ��

unsigned char dehydration_provide_timer;        //��ˮ��ʼǰ��׼��ʱ��
unsigned char middle_dehydration_settle_timer;  //���Ѻ͸���֮���ͣ��ʱ��
unsigned int middle_dehydration_max_run_timer; //�����������������ʱ��
unsigned int high_dehydration_max_run_timer;   //�����������������ʱ��
unsigned char middle_dehydration_stop_wait_timer;//���ѳ�������ȴ�ʱ��
unsigned char high_dehydration_stop_wait_timer;  //���ѳ�������ȴ�ʱ�� 
unsigned char middle_dehydration_stop_skid_time; //���ѽ���ɲ��ʱ��
unsigned char high_dehydration_stop_skid_time;   //���ѽ���ɲ��ʱ�� 
//unsigned char scan_dehydration_num;//ɨ������ˮֵ
unsigned char trans_num;//�ظ����͵Ĵ���
unsigned char wait_trans_time;//�ظ����͵ļ��ʱ��
unsigned char shake_num;//�������
unsigned int rxe_receive_timer;//ͨѶ�����ʱ
unsigned int ad_fault_num;//ADת�����ϼ�ʱ

unsigned char buzzer_timer;
unsigned char buzzer_num;
unsigned char _buzzer_run;
unsigned char _tell_alarm;
unsigned char _tell_stop;
//unsigned char data_number;//���ݸ���
//unsigned char data_address;//���ݵ�ַ
//unsigned char data_page;
//unsigned char checkout;
//unsigned int run_anyone_step_timer;
extern unsigned int main_cycle_1s_timer;
extern unsigned int flag_fault_display;
extern unsigned char _glitter_warm_led;
extern unsigned char _glitter_heat_led;
extern unsigned char _glitter_drain_led;
extern unsigned char _glitter_spin_led;
extern unsigned char _glitter_wash_led;
extern unsigned char _glitter_cold_led;

//unsigned char manual_mode_m;//�ֶ�ģʽ����ʱ���
//unsigned char manual_mode_s;//�ֶ�ģʽ����ʱ����
//unsigned char manual_mode_temp;//�ֶ�ģʽ�趨�¶�
//unsigned char manual_mode_liquid_height;//�ֶ��趨ģʽҺλ

unsigned char step_num;

unsigned char get_clothes_provide_timer; // azalea???
unsigned char deasil_run_time; // azalea???
unsigned char deasil_stop_time; // azalea???
unsigned char anticlockwise_run_time; // azalea???
unsigned char anticlockwise_stop_time;
unsigned char lcd_chosen_sub_step; //azalea???
//unsigned char receive_delay;
//unsigned int timer_800ms;
//unsigned char data_num;
unsigned char all_time_h;
unsigned char all_time_m;
unsigned char all_time_s;

typedef union {
  unsigned char BYTE;
  struct {
    unsigned char b0    :1;
    unsigned char b1    :1;
    unsigned char b2    :1;
    unsigned char b3    :1;
    unsigned char b4    :1;
    unsigned char b5    :1;
    unsigned char b6    :1;
    unsigned char b7    :1;
  }bool;
}FLAGBYTE;

volatile FLAGBYTE DATA1; 
#define data1 DATA1.BYTE
#define _clear_for_stop			  DATA1.bool.b0
#define _dis_open_close_door 	DATA1.bool.b1
#define _get_clothes_function DATA1.bool.b2
#define _enable_single_wash		DATA1.bool.b3  //�������
#define _had_single_way_wash  DATA1.bool.b4  //�Ѿ��о���
#define _all_time  					  DATA1.bool.b5
#define _error_commu          DATA1.bool.b6   //crcУ����󣬳���45�α���
#define _clear_for_start			DATA1.bool.b7  //������ǰ״̬  1-����  0-ֹͣ

volatile FLAGBYTE DATA2; 
#define data2 DATA2.BYTE
#define _have_wash			 		 	DATA2.bool.b0 //ϴ�ӱ�־
#define _enable_wash 					DATA2.bool.b1	//����ϴ��
#define _have_cool_water			DATA2.bool.b2 //����ˮ
#define _add_cool_water_stop 	DATA2.bool.b3 //ֹͣ�����ˮ
#define _have_hot_water 			DATA2.bool.b4	
#define _add_hot_water_stop		DATA2.bool.b5 //ֹͣ�����ˮ	
#define _have_calefaction   	DATA2.bool.b6
#define _had_drain_double_dis DATA2.bool.b7 //azalea???

volatile FLAGBYTE DATA3; 
#define data3 DATA3.BYTE
#define _start_set_program        DATA3.bool.b0
#define	_wash_enable 				   	  DATA3.bool.b1  //ϴ��
#define	_cold_enable              DATA3.bool.b2  //��ˮ
#define	_warm_enable 					  	DATA3.bool.b3  //��ˮ
#define	_heat_enable  						DATA3.bool.b4  //����
#define	_soap_enable 						  DATA3.bool.b5  //��Һ
#define _drain_enable 						DATA3.bool.b6  //��ˮ
#define _spin_enable  						DATA3.bool.b7  //��ˮ 
	
volatile FLAGBYTE DATA4; 
#define data4 DATA4.BYTE
#define _had_soap     					  DATA4.bool.b0  //�Ѿ�����Һ��
#define _had_drain    					  DATA4.bool.b1 //�Ѿ�����ˮ
#define _had_spin     					  DATA4.bool.b2 //�Ѿ�����ˮ 
#define _num_4        					  DATA4.bool.b3 // azalea???
#define _num_3        					  DATA4.bool.b4 // azalea???
#define _num_2        					  DATA4.bool.b5 // azalea???
#define _num_1       						  DATA4.bool.b6 // azalea???
#define _had_wash    						  DATA4.bool.b7 //�Ѿ���ϴ�ӱ�־��
	
volatile FLAGBYTE DATA5; 
#define data5 DATA5.BYTE
#define _enable_scan_one 					DATA5.bool.b0//������ɨ��
#define _enable_scan_two 					DATA5.bool.b1//������ɨ��
#define _enable_scan_three 				DATA5.bool.b2//������ɨ��
#define _enable_scan_four 				DATA5.bool.b3//������ɨ��
//#define _buzzer_run 							DATA5.bool.b4//��������
#define _have_fault								DATA5.bool.b5
#define _sign_13 									DATA5.bool.b6
#define _wash_txd									DATA5.bool.b7 //ϴ�ӷ��ͱ�־

volatile FLAGBYTE DATA6; 
#define data6 DATA6.BYTE
#define _enable_ini_program 			DATA6.bool.b0 //���г�ʼ��
#define _high_dehydration_txd     DATA6.bool.b2 //��Ч�𶯱�־
#define _enable_dehydration				DATA6.bool.b3 //������ˮ
//#define _enable_commu_clear_fault DATA6.bool.b5
#define _dehydration_stop_pro     DATA6.bool.b6
#define _middle_dehydration_txd   DATA6.bool.b7
	
volatile FLAGBYTE DATA7; 
#define data7 DATA7.BYTE
#define _auto_mode_run_stop       DATA7.bool.b0 //�Զ�ģʽ�������б�־
#define _single_way_wash_stop_pro DATA7.bool.b1 //����������ɲ�������־
#define _single_wash_dis          DATA7.bool.b2 //������ʾ
#define _single_wash_txd					DATA7.bool.b3 //����ͨѶ
#define _soap_liquid_1						DATA7.bool.b4
#define _soap_liquid_2						DATA7.bool.b5	
#define _soap_liquid_3						DATA7.bool.b6	
#define _drain										DATA7.bool.b7
	
volatile FLAGBYTE DATA8; 
#define data8 DATA8.BYTE 
#define _shake_bit								DATA8.bool.b0
#define _new_step							  	DATA8.bool.b1
#define _wait_trans							  DATA8.bool.b2 //�ȴ��ٴη��ͱ�־
#define _fault_pro_complete				DATA8.bool.b3 
#define _key_pro_ok								DATA8.bool.b3
#define _positive_reverse_dis     DATA8.bool.b4 //�и��ѱ�־
#define _ini_program_ok           DATA8.bool.b5 //�������ʼ�����
#define _error_door_open					DATA8.bool.b6
#define _no_read_fault						DATA8.bool.b7

volatile FLAGBYTE DATA9; 
#define data9 DATA9.BYTE 
//#define _tell_stop 								DATA9.bool.b0 //ֹͣ��־
#define _error_shake							DATA9.bool.b1 //�𶯹���
#define _soap_liquid_pro					DATA9.bool.b2 //��Һ�����־
//#define _tell_alarm								DATA9.bool.b5
//#define _init_param								DATA9.bool.b6 //��ʼ��������־
//#define _init_proce								DATA9.bool.b7	//��ʼ�������־
#endif



