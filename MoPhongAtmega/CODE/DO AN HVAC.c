/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/05/2023
Author  : 
Company : 
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>
#include <init_all.c>
#include <delay.h>
// Alphanumeric LCD functions
#include <DHT_me.c>
#define MAY_SO PORTB.0
#define CAP_AM PORTB.1
#define QUAT_GIO PORTB.2
#define CHILLER PORTB.3
#define ON 1
#define OFF 0
#define ON_SW PINC.1
#define SpanOn PINC.2
// Declare your global variables here   
int temperature_set = 50; //////cai nhiet do o day
int humidity_set = 50;   //////cai do am o day
int temperature_int = 0;
int humidity_int = 0;
int temperature_float = 0;
int humidity_float = 0;
int temperature_raw = 0;
int humidity_raw = 0;
unsigned char lcd[20];
void main(void)
{
    fn_initall();
    lcd_puts("hello world");
    delay_ms(500);
    lcd_clear();
while (1)           
      {   
         dht_GetTempUtil(&temperature_raw, &humidity_raw);
         temperature_int=temperature_raw/10;
         temperature_float=temperature_raw%10;  
         humidity_int=humidity_raw/10;
         humidity_float=humidity_raw%10;
         
         sprintf(lcd,"TEMP:%d.%d�C",temperature_int,temperature_float); 
         lcd_gotoxy(0,0);
         lcd_puts(lcd); 
         sprintf(lcd,"HUM:%d.%d%%",humidity_int,humidity_float); 
         lcd_gotoxy(0,1);
         lcd_puts(lcd);
         delay_ms(200);
         ///////////////HOAT DONG DAU RA///////////  
         if(ON_SW==ON)//bat he thong
         {    
            //
             QUAT_GIO=SpanOn;
            
                 //bat QUAT_GIO
             if(temperature_int>temperature_set)  ///nhiet do LON hon cai dat 
             {   
                if(humidity_int>humidity_set)  ///do am LON hon cai dat
                {
                 MAY_SO=OFF;
                 CHILLER=ON;
                 CAP_AM=OFF;    
                } 
                if(humidity_int<humidity_set)  ///do am NHO hon cai dat
                {
                 MAY_SO=OFF;
                 CHILLER=ON;
                 CAP_AM=ON;    
                }
             }         
             if(temperature_int<temperature_set)   ///nhiet do NHO hon cai dat
             {
                 if(humidity_int>humidity_set)  ///do am LON hon cai dat
                {
                 MAY_SO=ON;
                 CHILLER=ON;
                 CAP_AM=OFF;    
                } 
                if(humidity_int<humidity_set)  ///do am NHO hon cai dat
                {
                 MAY_SO=ON;
                 CHILLER=OFF;
                 CAP_AM=ON;    
                }
             } 
         }
         if(ON_SW==OFF)//tat he thong
         {             
            QUAT_GIO =OFF;
            MAY_SO   =OFF;
            CHILLER  =OFF;
            CAP_AM   =OFF;
         }
         
      }
}
