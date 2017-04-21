#ifndef __MENU_SUB_H
#define __MENU_SUB_H
#ifdef  __MENU_SUB_C

void M_11(void);
void M_12(void);
void M_13(void);
void M_14(void);
void M_15(void);
void M_16(void);
//void (*RunPrFunTable[6])(void) = {M_11,M_12,M_13,M_14,M_15,M_16};
void M_999(void);

void Menu_UserPrPro(void);		// �û���������
void Menu_UserPrDis(void);		// �û�������ʾ

void Menu_SoftwareVersion(void);// ����汾��
//void Menu_FaultRecord(void);	//���ϼ�¼
void Menu_SetCalendar(void);	//����������

void Password_Check(void); 
void Password_Set(void);
void Password_Show(void);

#else

extern void M_11(void);
extern void M_12(void);
extern void M_13(void);
extern void M_14(void);
extern void M_15(void);
//extern void (*RunPrFunTable[6])(void); 
extern void M_999(void);
extern void Menu_UserPrPro(void);
extern void Menu_UserPrDis(void);
extern void Menu_SoftwareVersion(void);	// ����汾��
//extern void Menu_FaultRecord(void);		//���ϼ�¼
//void Menu_FaultRecord(void);	//���ϼ�¼

void Menu_SetCalendar(void);			//����������
extern void Password_Check(void);
extern void Password_Set(void);
extern void Password_Show(void);

#endif
#endif

