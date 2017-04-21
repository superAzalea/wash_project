#ifndef __Menu_H
#define __Menu_H

#define NUM_PAGE	106

#ifdef  __Menu_C
#include "bit_define.h"

u16 Tab_MenuNum[NUM_PAGE] = {
0,1,2,3,4,5,6,
11,12,13,14,15,16,
21,22,23,24,25,26,27,
31,32,33,34,35,36,37,	
41,	
51,52,53,54,	
61,62,63,64,65,66,67,68,	
211,212,213,214,215,216,
221,222,223,224,225,
231,232,233,
241,242,243,244,245,246,247,
251,252,253,254,255,256,257,	
261,262,263,264,265,
271,272,273,274,275,
311,312,313,314,315,
321,322,323,
331,332,333,334,335,336,337,338,
341,342,343,344,
351,352,
361,362,
411,412,413,	
999,
};

char Tab_unit[14][3] = {" "," ","V","A","Mp","'C","Kw","h","s","Hz","%"," "," "," "};

char ResetMenu[121] = {
  "        ��  ӭ  ʹ  ��        "
  "      ��  ��  ��  ѹ  ��      "
  "                              "
  "V1.0                          "};  

char disresetmenu[ ] = {
  "           ���˵��           "
  "DKC400-LS04 ȫ�Զ�ϴ�ѻ�������"
  "      V1.00 ������...         "
  "                              "};

char handshakemenu[] = {
  "                              "
  "   ����ʧ��,����ͨѶ��·    "
  "                              "
  "                              "
};

char dispMainMenu[] = {
	"    ����                      "
	"�趨�¶�   �� �趨Һλ        "
	"ʵ���¶�   �� ʵ��Һλ        "
	"                              "};//120		


char dispSetMenu[] = {
  "    ����  ��                  "
  "�趨�¶�  ��  �趨Һλ        "
  "                              "
  "                              "};

char disMenu[] = {
  "�ֶ�ģʽ       00:00          "
  "ʵ���¶�   �� ʵ��Һλ        "
  "    ����ϴ��!                 "
  "                              "};//120
  
char dismodeMenu[] = {
  "  ��ѯ��ʽ                    "
  "  �޸ķ�ʽ                    "
  "                              "
  "   ����    ��    ��    ����   "};

char dismmMenu[] = {
    "                              "
    "             ����             "
    "                              "
    "   ����    +      -    ȷ��   "};//120


  
char dis_main_menu[] = {
  //"          �����ò˵�          "
  "  P01 ����������              "
  "  P02 ��������1               "
  "  P03 ��������2               "
  "  P04 ���붨��                "
  "  P05 �������                "
  "  P06 Һλ����                "
  "  P07 ��Һ����ʱ��            "
  "  P08 ϴ��ʱ������            "
  "  P09 ��ˮ����ʱ��            "
  "  P10 ��ˮ������ʱ            "
  "  P11 ȡ��ʱ������            "
  "  P12 �¶�����                "    
  "  P13 ��������                "
  "  P14 �ٶ�����                "
  "  P15 Һλ�߶�У׼            "
  "  P16 ˫�ٵ������            "};

  
char dis_sub_menu_one[] = {
  "  ��ʼ������                  "
  "  ��ʼ������                  "
  "  �������ѡ��                "
  "  ��������                    "
  "  ��������                    "
  "  ��������                    "};
  
char dis_sub_menu_two[] = {
  "  �Ƿ��Զ�����                "
  "  �Ƿ��Զ���ˮ                "
  "  �Ƿ��������                "
  "  �Ƿ���ȡ��                  "
  "  ��Һλ������                "};

char dis_sub_menu_three[] = {
  "  ��ˮȫ����ˮ                "
  "  �Զ���ˮҺ��                "
  "  ��ˮ���Һλ                "
  "  �������Դ���                "
  "  ��Ƶ���ٶȻ���              "};  
	

char dis_sub_menu_four[] = {
  "  �Źض���                    "
  "  ���ض���                    "
  "  ������                    "
  "  ����ֹͣ����                "
  "  ��Һλ����                  "
  "  ��Һλ����                  "
  "  ��Һλ����                  "};
  
char dis_sub_menu_five[] = {
  "  ��ˮ����                    "
  "  ��������                    "};

 
char dis_sub_menu_six[] = {
  "  ��Һλ�ĸ߶�                "
  "  ��Һλ�ĸ߶�                "
  "  ��Һλ�ĸ߶�                "
  "  ���׼Һλ                  "
  "  ϴ�����Һλ                "
  "  �������Һλ                "
  "  ������ˮҺλ                "
  "  ��ˮ���Һλ                "};  
	
 
char dis_sub_menu_seven[] = {
  "  ��Һ�ĸ���             ��   "
  "  ��Һ1����ʱ��          ��   "
  "  ��Һ2����ʱ��          ��   "
  "  ��Һ3����ʱ��          ��   "
  "  ����ҺҺλ                  "
  "  ����Һ����ˮ                "};

char dis_sub_menu_eight[] = {
  "  ϴ�ӹ���ʱ��           ��   "
  "  ϴ��ת��ʱ��           ��   "
  "  ϴ��ֹͣʱ��           ��   "};
	
  
char dis_sub_menu_nine[] = {
  "  ��ˮ��ʱʱ��           ��   "
  "  ����ͣ��ʱ��           ��   "
  "  ������ˮʱ��           ��   "
  "  ������ˮʱ��           ��   "
  "  ����ͣ��ʱ��           ��   "
  "  ���ѱ���ʱ��           ��   "
  "  ���ѱ���ʱ��           ��   "};
  
char dis_sub_menu_ten[] = {
  "  ���������ʱ           ��   "
  "  ����������ʱ           ��   "
  "  ���ѽ�����ʱ           ��   "
  "  ���ѽ�����ʱ           ��   "
  "  ��������ɲ��           ��   "
  "  ���ѽ���ɲ��           ��   "
  "  ���ѽ���ɲ��           ��   "};
  
char dis_sub_menu_eleven[] = {
  "  ȡ�¹���ʱ��           ��   "
  "  ȡ����תʱ��           ��   "
  "  ȡ����תֹͣ           ��   "
  "  ȡ�·�תʱ��           ��   "
  "  ȡ�·�תֹͣ           ��   "};
  
char dis_sub_menu_twelve[] = {
  "  �ֶ�Ĭ���¶�           ��   "
  "  ���Ĭ���¶�           ��   "
  "  ��߿����¶�           ��   "
  "  ��Ϳ����¶�           ��   "};
  
char dis_sub_menu_thirteen[] = {
  "  �����ٶȸ���           ��   "
  "  ����1����ʱ��          ��   "
  "  ����2����ʱ��          ��   "};
  //"  ����3����ʱ��          ��   "};  

char dis_sub_menu_fourteen[] = {
  "  ��תƵ��               Hz   "
  "  ��תƵ��               Hz   "
  "  ����Ƶ��               Hz   "
  "  ����Ƶ��               Hz   "
  "  ����Ƶ��               Hz   "
  "  ����2Ƶ��              Hz   "
  "  ����3Ƶ��              Hz   "
  "  ȡ��Ƶ��               Hz   "};

char dis_sub_menu_fifteen[] = {
  "                              "
  "            �޹���            "
  "                              "
  "                              "};
  
char dis_sub_menu_sixteen[] = {
  "                              "
  "            �޹���            "
  "                              "
  "                              "};       

char save_data_menu[] = {
  "                              "
  "        �Ƿ񱣴�����?         "
  " ��ʼ��:����    ֹͣ��:������ "
  "                              "};
  
char fault_dis_menu[] = {
  "                              "
  " �й���,�밴�������ѯ���ϱ�! "
  "                              "
  "                              "};
                                     
char wash_complete_menu[] = {
  "                              "
  "          ϴ�����!           "
  "      �밴�����������ҳ      "
  "                              "};

char shake_stop_menu[] = {
  "                              "
  "          ����ͣ��            "
  "      �밴�����������ҳ      "
  "                              "};

char instancy_stop_menu[] = {
  "                              "
  "          ����ͣ��            "
  "      �밴�����������ҳ      "
  "                              "};  



typedef void (*UserPrFun) (u8 i);
	
u8 flag_prSetting = 0;			//�����趨�б�־λ
u8 Counter_KeyIn = 0;			//�Լ�����������ļ����������趨����
u8 UserPrNum = 0;				//ϵͳ��������Ч����
u8 Data_KeyIn_Dis[5] = {0,0,0,0,0};	//�ڲ����趨ʱ��������¼�������������
u8 Data_KeyIn[5] = {0,0,0,0,0};	//Ϊ�˽�������ʾ�����黹ԭΪ��ʵ�����֣������������ֵ�����������
u16 UserPrIndex = 0;				//����������
u8 flag_firstInSetPrPage = 0;	//�״ν�������趨�����־λ
u16 UserPrData = 0;				//������������趨ֵ
u8 UserPrData_H = 0;				//�����趨ֵ�ĸ�8λ
u8 UserPrData_L = 0;				//��8λ
u16 MenuIndex = 0;			//�˵�������
//u16 MenuIndex_Z = 0;			//�����ڵĲ˵�������
u8 CheckState = 0;
u8 CheckOk[6] = {0,0,0,0,0,0};
u8 DispMod_Old = 0;

char passportdata[6] = {0,0,0,0,0,0};
char passportdata_buffer[6] = {0,0,0,0,0,0};

void sendtobuff(u8 h,u8 l,char *p);
void Menu_RunPrPro(void);			//���в���
void Menu_FactoryPrPro(void);		//���Ҳ���
void Menu_DebugPrPro(void);			//���Բ���
void Menu_FaultRecordPro(void);		//���ϼ�¼
void Menu_UserPasswordPro(void);	//�û�����

void lcd_mainmenu(void);
///***
void menu_first_page(void);
void menu_second_page(void);
void main_set_menu(void);
void lcd_menu_one(void);
void lcd_menu_two(void);
void lcd_menu_three(void);
void lcd_menu_four(void);
void lcd_menu_five(void);
void lcd_menu_six(void);
void lcd_menu_seven(void);
void lcd_menu_eight(void);
void lcd_menu_nine(void);
void lcd_menu_ten(void);
void lcd_menu_eleven(void);
void lcd_menu_twelve(void);
void lcd_menu_thirteen(void);
void lcd_menu_fourteen(void);
void lcd_menu_fifteen(void);//???
void lcd_menu_sixteen(void);
void lcd_wash_complete_menu(void);
void menu_fault_page(void);
void menu_fault_dis(void);
void menu_handshake_dis(void);
void menu_set_program(void);
void lcd_shake_stop_menu(void);
void lcd_instancy_stop_menu(void);
void menu_save_data(void);//�������ݲ˵�
void key_mainmenu_handler(void);//dismod0
void key_menu_first_page_handler(void);//dismod1
void key_menu_second_page_handler(void);//dismod2
void key_main_set_menu_handler(void);//dismod3
void key_lcd_menu_one_handler(void);//dismod4_1
void key_lcd_menu_two_handler(void);//dismod4_2
void key_lcd_menu_three_handler(void);//dismod4_3
void key_lcd_menu_four_handler(void);//dismod4_4
void key_lcd_menu_five_handler(void);//dismod4_5
void key_lcd_menu_six_handler(void);//dismod4_6
void key_lcd_menu_seven_handler(void);//dismod4_7
void key_lcd_menu_eight_handler(void);//dismod4_8
void key_lcd_menu_nine_handler(void);//dismod4_9
void key_lcd_menu_ten_handler(void);//dismod4_10
void key_lcd_menu_eleven_handler(void);//dismod4_11
void key_lcd_menu_twelve_handler(void);//dismod4_12
void key_lcd_menu_thirteen_handler(void);//dismod4_13
void key_lcd_menu_fourteen_handler(void);//dismod4_14
void key_lcd_menu_fifteen_handler(void);//dismod4_15
void key_lcd_menu_sixteen_handler(void); // dismod4_16
void key_menu_fault_page_handler(void) ;//dismod5
void key_menu_set_program_handler(void);//dismod6_1
void key_menu_save_data_handler(void) ;         // dismod6_2
void key_wash_complete_menu_handler(void); //dismod7
void key_shake_stop_menu_handler(void);       //dismod8
void key_instancy_stop_menu_handler(void);   //dismod9
void key_menu_fault_dis_handler(void);           //dismod10

void disphex_asc_le(char *array,u32 idat,u8 num);
void kp_menucur(u8 sline,u8 ucol,u8 cur);
void lcd_lastline(u8 g1, u8 g2);
void disphex_asc_be(char *array,u32 idat,u8 num);
void (*RunPrFunTable[16])(void) = {lcd_menu_one,lcd_menu_two,lcd_menu_three,lcd_menu_four,lcd_menu_five,lcd_menu_six,
                                    lcd_menu_seven,lcd_menu_eight,lcd_menu_nine,lcd_menu_ten,lcd_menu_eleven,lcd_menu_twelve,
	                                  lcd_menu_thirteen,lcd_menu_fourteen,lcd_menu_fifteen,lcd_menu_sixteen};

//void 	(*FunProgramTable[2])() = {menu_set_program,menu_save_data};														
																		
//***/
///***
//u8  lcd_submenucur;
//u8 lcd_chosencur;
u8 _new_page;
u8 _bit_set;
//u8 auto_run_mode;
//u8 lcd_chosencur;
u8 _read_data;
u8 _read_function;
u8 lcd_maxcur;
//u8 _display_mode;
//u8 lcd_chosencur_buffer;
u8 run_state;
u8 _enable_display;
u8 set_temp;
u8 lcd_cpage;
u8 lcd_cpage_old;																		

EMENU Menu;
EDISPLAY DispMod;

//****/

//u32 pwsd_factory;

extern void ClearDisBuff(void);
extern void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);
extern u8 AT24CXX_ReadOneByte(u16 ReadAddr);


EPASS  passdisp;
DISMENU  dismenu;

volatile FUNC_CODE_I  Code_I;

#else
extern char handshakemenu[];
extern  char disresetmenu[ ];

extern char dispMainMenu[ ];

extern char dispSetMenu[ ];
extern char disMenu[ ];
extern char dismodeMenu[ ];
extern char dismmMenu[ ];

extern char dis_main_menu[ ];

extern char dis_sub_menu_one[ ];
extern char dis_sub_menu_two[ ];
extern char dis_sub_menu_three[ ];

extern char dis_sub_menu_four[ ];
extern char dis_sub_menu_five[ ];

extern char dis_sub_menu_six[ ];

extern char dis_sub_menu_seven[ ];

extern char dis_sub_menu_eight[ ];
///***
extern char dis_sub_menu_nine[ ];
extern char dis_sub_menu_ten[ ];
extern char dis_sub_menu_eleven[ ];
extern char dis_sub_menu_twelve[ ];
extern char dis_sub_menu_thirteen[ ];
extern char dis_sub_menu_fourteen[ ];
extern char dis_sub_menu_fifteen[ ];
extern char dis_sub_menu_sixteen[ ];
extern char save_data_menu[ ];
extern char fault_dis_menu[ ];
extern char wash_complete_menu[ ];
extern char shake_stop_menu[ ];
extern char instancy_stop_menu[ ];
//****/

//extern u32 pwsd_factory;

extern char ResetMenu[121];
//extern char Tab_MenuData[NUM_PAGE][121];
extern char Tab_unit[14][3];
extern u16 Tab_MenuNum[NUM_PAGE];
extern u8 flag_prSetting;			//�����趨�б�־λ
extern u8 Counter_KeyIn;			//�Լ�����������ļ����������趨����
extern u8 UserPrNum;				//ϵͳ��������Ч����
extern u8 Data_KeyIn_Dis[5];	//�ڲ����趨ʱ��������¼�������������
extern u8 Data_KeyIn[5];	//Ϊ�˽�������ʾ�����黹ԭΪ��ʵ�����֣������������ֵ�����������
extern u16 UserPrIndex;				//����������
//extern u16 MenuIndex_Z;			//�����ڵĲ˵�������
extern u8 flag_firstInSetPrPage;	//�״ν�������趨�����־λ
extern u16 UserPrData;				//������������趨ֵ
extern u8 UserPrData_H;				//�����趨ֵ�ĸ�8λ
extern u8 UserPrData_L;				//��8λ
extern u16 MenuIndex;			//�˵�������
extern u8 CheckState;
extern u8 CheckOk[6];

extern void sendtobuff(u8 h,u8 l,char *p);
extern void Lcd_KEYPro(void);
extern void LCDDisplay(void);
extern void Auto_WashPro(void);
extern void ini_data(void);
extern void fault_dis_pro(void);
extern void handshake_pro(void);
extern void Menu_RunPrPro(void);			//���в���
extern void Menu_FactoryPrPro(void);		//���Ҳ���
extern void Menu_DebugPrPro(void);			//���Բ���
extern void Menu_FaultRecordPro(void);		//���ϼ�¼
extern void Menu_UserPasswordPro(void);	//�û�����

#endif
#endif









