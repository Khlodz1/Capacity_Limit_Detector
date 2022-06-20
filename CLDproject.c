#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "lcd.h"
#define _XTAL_FREQ 8000000
/*
 * 
 */
void __interrupt() inttmr()
{
   if (INT3IF&&INT3IE)// if interrupt occurred, customer left
   {
        __delay_ms(500);
        TMR0L--;
      
        //    Lcd_Write_String("STATUS: ");
       
       WREG=0xff;
       if(TMR0L!=WREG)
       {
            INT3IF=0;
            TMR0IF=0;
            return;
       }
       Lcd_Clear();
       Lcd_Set_Cursor(1,1);
       Lcd_Write_Char('S');
       Lcd_Write_Char('T');
       Lcd_Write_Char('A');
       Lcd_Write_Char('T');
       Lcd_Write_Char('U');
       Lcd_Write_Char('S');
       Lcd_Write_Char(':');
       Lcd_Write_Char(' ');
       Lcd_Set_Cursor(2,5);
//       Lcd_Write_String("OPEN ");
       Lcd_Write_Char('O');
       Lcd_Write_Char('P');
       Lcd_Write_Char('E');
       Lcd_Write_Char('N');
       LATC6=1;//green
       LATC7=0;//red
       INT3IF=0;
       TMR0IF=0;
   }
   if(TMR0IF)//if timer 0 occurred, customer entered
   {
       __delay_ms(500);
       Lcd_Clear();
       Lcd_Set_Cursor(1,1);
//    Lcd_Write_String("STATUS: ");
       Lcd_Write_Char('S');
       Lcd_Write_Char('T');
       Lcd_Write_Char('A');
       Lcd_Write_Char('T');
       Lcd_Write_Char('U');
       Lcd_Write_Char('S');
       Lcd_Write_Char(':');
       Lcd_Write_Char(' ');
       Lcd_Set_Cursor(2,5);
//       Lcd_Write_String("CLOSE");
       Lcd_Write_Char('C');
       Lcd_Write_Char('L');
       Lcd_Write_Char('O');
       Lcd_Write_Char('S');
       Lcd_Write_Char('E');
       LATC6=0;//Green
       LATC7=1;//Red
       TMR0IF=0;
   }
}

void main(void)
{
    OSCCON=0x60;
    ANCON0=0x00;
    ANCON1=0x03;
    ADCON1=0x00;
    ADCON2=0x21;
    TRISB3=1;
    TRISB5=1;
    TRISD=0;
    TRISC=0;
    TRISE=0;
    ANCON1=0;
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
//    Lcd_Write_String("STATUS: ");
    Lcd_Write_Char('S');
    Lcd_Write_Char('T');
    Lcd_Write_Char('A');
    Lcd_Write_Char('T');
    Lcd_Write_Char('U');
    Lcd_Write_Char('S');
    Lcd_Write_Char(':');
    Lcd_Write_Char(' ');
    Lcd_Set_Cursor(2,5);
//    Lcd_Write_String("OPEN ");
    Lcd_Write_Char('O');
    Lcd_Write_Char('P');
    Lcd_Write_Char('E');
    Lcd_Write_Char('N');
    LATC6=1;//Green
    LATC7=0;//Red
    T0CON=0x68;
    TMR0L=0xFB;
    TMR0IF=0;
    INT3IF=0;
    TMR0IE=1;
    INT3IE=1;
    T0SE=1;//FAILLING EDGE
    INTEDG3=0;//FAILLING EDGE
    GIE=1;
    TMR0ON=1;
    while(1)
    {
        // wait here
    }
    return;
}