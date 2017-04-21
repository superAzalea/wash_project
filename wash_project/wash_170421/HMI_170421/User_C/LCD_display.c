/**************************************************************************************************
Project: TTK_ACPR
Filename: LCD_display.c
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
#ifndef __LCD_display_C
#define __LCD_display_C

#include "stm32f10x.h"
#include "Define.h" 
#include "delay.h"
#include "Typedef.h"
#include "ziku.h"
#include "SystemInit.h"
#include "LCD_display.h"

void wait(unsigned char i) 
{
    for(;i>0;i--)
    {

    } 
}

void check_sta01(void)
{
    unsigned char i,k;
    
    PAInPut
    cd = 1;     
    rd = 0;   		
    wait(50);//wait(100)=10us
    for(i=255;i>0;i--)
    {
        k = DATA_IN;
        if((k&0x03) == 0x03)
        {
            rd = 1;
            PAOutPut
            break;
        }
    }
}

void check_sta3(void)
{
    unsigned char i,k;
    
    PAInPut
    cd = 1;     
    rd = 0;     
    wait(50);
    for(i=255;i>0;i--)
    {
        k = DATA_IN;
        if((k&0x08) == 0x08)
        {
            rd = 1;
            PAOutPut
            break;
        }
    }
}


void write_data(u8 i)
{
	u16 temp = 0;
	
    check_sta01();
	//delay_ms(2);
    cd=0;  	
	PAInPut
	temp = DATA_IN;
	PAOutPut
  	DATA_OUT = i + ((temp>>8)<<8); 
	//DATA_OUT = i;	
    wr=0;
    wr=1;
}
void write_com(u8 i)
{
	u16 temp = 0;
	
    check_sta01();
	//delay_ms(2);
    cd=1; 		
	PAInPut
	temp = DATA_IN;
	PAOutPut
	DATA_OUT = i + ((temp>>8)<<8);	
	//DATA_OUT = i;
    wr=0;
    wr=1;
}
void write_reg(uc8 i,uc8 j,uc8 h)//д�������ݺ�һ������
{
      write_data(i);         
	  write_data(j);       
	  write_com(h);
}


void init_LCD(void)
{
	rst = 0;	
	delay_ms(10);
	rst = 1;
	delay_ms(10);
    ce = 0; 
	bla = 0;//���� �͵�ƽ����
	buzzer = 0;
	
}
void init_sap1024(void)
{   
    lcd_grHome = 0x4800;
    write_reg(LC_TXTSTART&0xFF, LC_TXTSTART>>8,0x40);
    write_reg(lcd_grHome&0xFF, lcd_grHome>>8,0x42);
    write_reg(0x1E,0x00,0x41);
    write_reg(0x1E,0x00,0x43);
    write_com(0x90|0x08);
    write_com(0xa0|0x01);
    write_com(0x81);      
}

//-----------------------------------------------------------------------------------------------------------------------//
u16 lcd_WordSearch(type_GB2312 const *p,char *indexs)//?????,??
{
    u16 num;
    
    for(num=0;num<1000;num++,p++)
    {
        if((indexs[0] == p->index[0]) && (indexs[1] == p->index[1]))
        {
            break;
        }
    }
    if(num >= 1000)
    {
        num = 0;
    }
    return num;
}

u16 lcd_ByteSearch(type_GB2312 const *p,char *indexs)//?????,??
{
    u16 num;
    
    for(num=0;num<1000;num++,p++)
    {
        if(indexs[0] == p->index[0])
        {
            break;
        }
    }
    if(num >= 1000)
    {
        num = 0;
    }
    return num;
}

void lcd_wru16(u8 uline,u8 ucol,type_GB2312 const *pp,char *indexs)//Ŀǰ����˳���ѯ���ɿ����Ż�Ϊ���ַ���ѯ
{
    u16 i,num;
    type_GB2312 const *p;
    unsigned int add=0;
    unsigned char data=0,add_l=0,add_h=0;
    
    p = pp;
    num = lcd_WordSearch(pp,indexs);   //???????
 
    for(i=0;i<16;i++)
    {
			  if(passdisp.set_rev_flg) data = ~((p+num)->data[i*2]);
      	else  data = (p+num)->data[i*2];
        add = (u16)uline*30*16 + ucol + lcd_grHome + i*30;
        add_l = add&0xff;
        add_h = add>>8;       
        write_reg(add_l,add_h,0x24);     
        write_com(0xb0);
        write_data(data);
        write_com(0xb2); 

			  if(passdisp.set_rev_flg) data = ~((p+num)->data[i*2 + 1]);
      	else  data = (p+num)->data[i*2 + 1];
        add ++;
        add_l = add&0xff;
        add_h = add>>8;   
        write_reg(add_l,add_h,0x24);     
        write_com(0xb0);
        write_data(data);
        write_com(0xb2); 
    }    
}

void lcd_wru8(u8 uline,u8 ucol,type_GB2312 const *pp,char *indexs)//Ŀǰ����˳���ѯ���ɿ����Ż�Ϊ���ַ���ѯ
{
    u16 i,num;
    type_GB2312 const *p;
    unsigned int add=0;
    unsigned char data=0,add_l=0,add_h=0;
    
    p = pp;
    num = lcd_ByteSearch(pp,indexs);   //

    for(i=0;i<16;i++)
    {
			
				if(passdisp.set_rev_flg) data = ~((p+num)->data[i]);
      	else  data = (p+num)->data[i];
			
        add = (u16)uline*30*16 + ucol + lcd_grHome + i*30;
        add_l = add&0xff;
        add_h = add>>8;       
        write_reg(add_l,add_h,0x24);     
        write_com(0xb0);
        write_data(data);
        write_com(0xb2);
    }    
}

void lcd_wrstring(u8 uline,u8 ucol,char *addrch)//
{
    u8 temp;
    type_GB2312 const *p = hanzi;
    temp = *addrch;

    while(temp!='\0')
    {
        if(temp<0x80)
        {   
            lcd_wru8(uline,ucol,p,addrch);//? ? ?????? ??
            addrch ++;
            temp = *addrch;
            ucol++;
            if(ucol >= 30)
            {
                ucol = 0;
                uline++;
            }        
        }
        else
        {        
            lcd_wru16(uline,ucol,p,addrch);// ? ? ?????? ??
            addrch += 2;
            temp = *addrch;
            ucol = ucol + 2;
            if(ucol >= 30)
            {
                ucol = 0;
                uline++;
            }
        }
    }
}

void lcd_wrpicture(u8 uline,u8 ucol,u8 uline_n,u8 ucol_n,char *addrch)//��ʾͼƬ
{
	unsigned int i = 0;
	unsigned int add=0;
	unsigned char data=0,add_l=0,add_h=0;
	for(i=0; i < ucol_n*uline_n; i++)//10��
	{
		data = *addrch;
		add = (u16)uline*30 + i%ucol_n + lcd_grHome;
		add_l = add&0xff;
		add_h = add>>8;
		write_reg(add_l,add_h,0x24);
		write_com(0xb0);
		write_data(data);
		write_com(0xb2);

		addrch++;

		ucol++;
		if(ucol >= ucol_n)
		{
			ucol = 0;
			uline++;
		}
	}
}

void lcd_drawpane(u8 x,u8 y,u8 x_n,u8 y_n,u8 data)//������
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int add=0;
	unsigned char add_l=0,add_h=0;

	for(i=x; i<x_n; i++)
	{
		for(j=y; j<y_n; j++)
		{
			add = (u16)j  + i*30 + lcd_grHome;
			add_l = add&0xff;
			add_h = add>>8;
			write_reg(add_l,add_h,0x24);
			write_com(0xb0);
			write_data(data);
			write_com(0xb2);		
		}
	}
}

void hex_to_asc_b(char *array,u32 idat,u8 num)//��HEXת��ASC��
{
	u8 t;
	u8 i;
	for(i=0;i<num;i++)//when i>num, num%2=1.
	{
		t = idat % 10;           //��1�εõ���λ���ڶ���ȡʮλ��������ȡ��λ
		t = t+0x30;              //0x30��0��ASC�룬�õ���Ӧ��ASC��
		*(array+i) = t;
		idat = idat / 10;        //��һ��ȥ����λ���ڶ���ȥ��ʮλ��������ȥ����λ
	}
}

void hex_to_asc(char *array,u32 idat,u8 num,u8 n)// ��HEXת��ASC��. ����nλС��
{
	u8 i,t;
	
	hex_to_asc_b(array,idat,num);//��idat��ASC��浽aa������
	for(i=0;i<num/2;i++)	//��λ���λ����
	{
		t= *(array+i);
		*(array+i) = *(array+num-1-i);
		*(array+num-1-i) = t;
	}
	if(n)
	{
		for(i=0;i<n;i++)	*(array + num - i) = *(array + num - i - 1);//����nλС��
		*(array + num - n) = 0x2e;//С������ʾ   
	}
}

void lcd_wrstring_num(u8 uline,u8 ucol,char *addrch,u8 num)//
{
    u8 temp,i;
    type_GB2312 const *p = hanzi;
    temp = *addrch;

   // while(temp!='\0')
		for(i=0;i<num;i++)
    {
        if(temp<0x80)
        {   
            lcd_wru8(uline,ucol,p,addrch);//? ? ?????? ??
            addrch ++;
            temp = *addrch;
            ucol++;
            if(ucol >= 30)
            {
                ucol = 0;
                uline++;
            }        
        }
        else
        {        
            lcd_wru16(uline,ucol,p,addrch);// ? ? ?????? ??
            addrch += 2;
            temp = *addrch;
            ucol = ucol + 2;
            if(ucol >= 30)
            {
                ucol = 0;
                uline++;
            }
        }
    }
}

/*
void lcd_test(void)
{
    unsigned int i;
  
    write_reg(0x00,0x00,0x24);   
    write_com(0xb0);    
    for(i=0;i<1920;i++)
    {            
		check_sta3();
        write_data(0xff); 
    }  
	check_sta3();	
    write_com(0xb2);
}
*/
#endif













