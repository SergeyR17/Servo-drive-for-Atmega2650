/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define ServoPORT1 PORTF
#define ServoPORT2 PORTC

 unsigned int servo_angle_array[16];
 const unsigned int cycle =10000;// 10000
 unsigned char takt = 0;
 unsigned char takt2 = 8;
 unsigned int nambuf=0;
 unsigned int nambu2=0;
 unsigned int ax1 =3000;
 unsigned int ax2 =0;




void servo_set_angle(unsigned int setangle,unsigned int servo_number)
{
cli();

if(setangle > 3800)
{
 setangle = 3800;
}
if(setangle < 0)
{
 setangle = 0;
}

setangle=1050+setangle;//500+angle ms
servo_angle_array[servo_number]=setangle;

sei();
}







ISR(TIMER1_COMPA_vect)
    {
    if (takt == 0)
        {
        ServoPORT1 = ServoPORT1| 1<<PF0;
        OCR1A = OCR1A + servo_angle_array[1];
        }
    if (takt == 1)
        {
        ServoPORT1 = ServoPORT1 & ~(1<<PF0);
        OCR1A = (cycle - servo_angle_array[1]) + OCR1A;
        }
    if (takt == 2)
        {
        ServoPORT1 = ServoPORT1| 1<<PF1;
        OCR1A = OCR1A + servo_angle_array[2];
        }
    if (takt == 3)
        {
        ServoPORT1 = ServoPORT1 & ~(1<<PF1);
        OCR1A = (cycle - servo_angle_array[2]) + OCR1A;
        }
    if (takt == 4)
        {
        ServoPORT1 = ServoPORT1| 1<<PF2;
        OCR1A = OCR1A + servo_angle_array[3];
        }
    if (takt == 5)
        {
        ServoPORT1 = ServoPORT1 & ~(1<<PF2);
        OCR1A = (cycle - servo_angle_array[3]) + OCR1A;
        }
    if (takt == 6)
        {
        ServoPORT1 = ServoPORT1| 1<<PF3;
        OCR1A = OCR1A + servo_angle_array[4];
        }
    if (takt == 7)
        {
       ServoPORT1 = ServoPORT1 & ~(1<<PF3);
        OCR1A = (cycle - servo_angle_array[4])+ OCR1A;
        }

 takt = takt + 1;


     if (takt == 8)
     {

         takt = 0;
     }

    }




ISR(TIMER1_COMPB_vect)
{

    if (takt2 == 8)
        {
        ServoPORT1 = ServoPORT1| 1<<PF4;
        OCR1B = OCR1B + servo_angle_array[5];
        }
    if (takt2 == 9)
        {
        ServoPORT1 = ServoPORT1 & ~(1<<PF4);
        OCR1B = (cycle - servo_angle_array[5]) + OCR1B;
        }
    if (takt2 == 10)
        {
       ServoPORT1 = ServoPORT1| 1<<PF5;
        OCR1B = OCR1B + servo_angle_array[6];
        }
    if (takt2 == 11)
        {
       ServoPORT1 = ServoPORT1 & ~(1<<PF5);
        OCR1B = (cycle - servo_angle_array[6]) + OCR1B;
        }
    if (takt2 == 12)
        {
       ServoPORT1 = ServoPORT1| 1<<PF6;
        OCR1B = OCR1B + servo_angle_array[7];
        }
    if (takt2 == 13)
        {
       ServoPORT1 = ServoPORT1 & ~(1<<PF6);
        OCR1B = (cycle - servo_angle_array[7]) + OCR1B;
        }
    if (takt2 == 14)
        {
      ServoPORT1 = ServoPORT1| 1<<PF7;
        OCR1B = OCR1B + servo_angle_array[8];
        }
    if (takt2 == 15)
        {
      ServoPORT1 = ServoPORT1 & ~(1<<PF7);
        OCR1B = (cycle - servo_angle_array[8]) + OCR1B;
        }

     if (takt2 == 16)
     {
         takt2 = 8;

         TCNT1 = 0;

     }
 takt2 = takt2 + 1;


}

int main(void)
{
 DDRF = 0xFF;
 DDRC = 0xFF;
 DDRB = 0xFF;
 PORTF = 0x00;
 PORTC = 0x00;
 TCNT1H=0;
 TCNT1L=0;
 TIMSK1 |= (1<<OCIE1A)|(1<<OCIE1B);
 sei();
 OCR1A=0;
 OCR1B=0;
TCCR1B |= (0<<CS12)|(1<<CS11)|(0<<CS10);//CLK/8// 2000000 гц 0.0000005   =0.0005 мсек\ 1800 \  3000max
                // выставить бит общего разрешения прерываний



    // Insert code
servo_set_angle(1900,1);
    while(1)
    {


servo_set_angle(3500,2); //3800
servo_set_angle(3500,3);
servo_set_angle(3500,4);
servo_set_angle(3500,8);
PORTB=0xFF;
_delay_ms (4000);
servo_set_angle(0,2);
servo_set_angle(0,3);
servo_set_angle(0,4);
servo_set_angle(0,8);

PORTB=0x00;
_delay_ms (4000);
    }

    return 0;
}


