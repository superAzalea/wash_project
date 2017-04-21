#ifndef __TYPEDEF_H
#define __TYPEDEF_H


typedef enum 
{
   dismod0,
   dismod1,
   dismod2,
   dismod3,
   dismod4,
   dismod5,
   dismod6,
   dismod7,
   dismod8,
   dismod9,
   dismod10,
   dismod11,

}EDISPLAY;


typedef enum 
{
	MENUCUR0,//���˵�
	MENUCUR1,//��ѯ���޸�ѡ��˵�
	MENUCUR2,//�����������
	MENUCUR3,//�����б����
	MENUCUR4,
	MENUCUR5,
	MENUCUR6,
	MENUCUR7,
	MENUCUR8,
	MENUCUR9,
	MENUCUR10,
	MENUCUR11,
      
}EMENU;

typedef struct
{
	unsigned char dispnum;
	unsigned char pst_rev_dis;// �и��ѱ��
	unsigned char set_rev_flg;//���Ա��
	unsigned char disp_flg; //ˢ����־
	unsigned char disp_cir;
	char dispdata[6];
}EPASS;


typedef struct
{
	unsigned char dis_mode;
	unsigned char data_mode;
	unsigned char sub_menucur;// �����˵�ָ��   azalea ?
	unsigned char sub_chosecur;//ѡ��ָ��    azalea ?
	unsigned char sub_chosecurbuf;

}DISMENU;



typedef struct 
{
	unsigned char P1[8];//����������
	unsigned char P2[8];//��������1
	unsigned char P3[8];//��������2
    unsigned char P4[8];//���붨��
	unsigned char P5[8];//�������
	unsigned char P6[8];//Һλ����
	unsigned char P7[8];//��Һ����ʱ��
	unsigned char P8[8];//ϴ��ʱ������
	unsigned char P9[8];//��ˮ����ʱ��
	unsigned char P10[8];//��ˮ������ʱ
	unsigned char P11[8];//ȡ��ʱ������
	unsigned char P12[8];//�¶�����
	unsigned char P13[8];//��������
	unsigned char P14[8];//�ٶ�����
	unsigned char P15[8];//Һλ�߶�У׼
	unsigned char P16[8];//˫�ٵ������
	unsigned char P17[8];
}FUNC_CODE_I ;

#endif
