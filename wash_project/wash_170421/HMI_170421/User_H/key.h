#ifndef __KEY_H
#define __KEY_H


#define  Wash    10 //ϴ��
#define  Cold    4  //��ˮ
#define  Warm    8  //��ˮ
#define  Heat    13 //����
#define  Soap    1  //��Һ
#define  Drain   5  //��ˮ
#define  Spin    9  //��ˮ
#define  Remove  15 //ȡ��
#define  Return  12 //����
#define  UP      14 // ����
#define  Down    3  //����
#define  Setup   7  //����

#define  Setup_C   20  //����
#define  STOP    11 //ֹͣ
#define  RUN     16 //����



#ifdef __KEY_C

unsigned char KeyVal = 0;
unsigned char KeyAct = 0;
unsigned char KeyCmd = 0;
unsigned char KeyBuzz = 0;
//unsigned char KeyCode = 0;
//unsigned char key_flag = 0;

void KeyScan(void);

#else

extern unsigned char KeyVal;
extern unsigned char KeyAct;
extern unsigned char KeyCmd;
extern unsigned char KeyBuzz;
//extern unsigned char key_flag;

extern void KeyScan(void);
//extern void KeyScancode(void);

#endif
#endif


