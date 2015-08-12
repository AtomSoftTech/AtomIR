/*
  atomir.h - Library for controlling an IR led
  Created by Jason Lopez (AtomSoft), May 29, 2014..
  Not to be released to public.
*/

#include "Arduino.h"
#include "AtomIR.h"

#define ZERO 0
#define ONE 1
#define START 2
#define MISC 3

void IR_TWC(unsigned char device, unsigned char cmd);
void IR_PULSE_TWC (unsigned char type);
void IR_DYNEX(unsigned char address_h, unsigned char address_l, unsigned char command);
void IR_PULSE_DYNEX (unsigned char type);
void IR_LG (unsigned char dat1, unsigned char dat2, unsigned char data);
void IR_PULSE_LG (unsigned char type);

int _ir_pin;
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 
AtomIR::AtomIR(int ir_pin)
{
  pinMode(ir_pin, OUTPUT);
  _ir_pin = ir_pin;
  digitalWrite(_ir_pin, LOW);
}

void AtomIR::sendSIRC(unsigned char  dev, unsigned char  cmd)
{
  delay(1);  
  digitalWrite(_ir_pin, LOW);
}

void AtomIR::sendTWC(unsigned char  dev, unsigned char  cmd)
{
  IR_TWC(dev,cmd);
  digitalWrite(_ir_pin, LOW);
}

void AtomIR::sendRC6(unsigned char  dev, unsigned char  cmd)
{
  delay(1);
  digitalWrite(_ir_pin, LOW);
}

void AtomIR::sendDynex(unsigned char address_l, unsigned char cmd)
{
  IR_DYNEX(DYNEX, address_l, cmd);
  digitalWrite(_ir_pin, LOW);
}

void AtomIR::sendLGAC(unsigned char dev, unsigned char cmd)
{
  IR_LG(LG_AC_CORE , dev, cmd);
  digitalWrite(_ir_pin, LOW);
}

void IR_TWC(unsigned char device, unsigned char cmd)
{
    unsigned char Ndevice = ~device;
    unsigned char count = 0;
    unsigned char Ncmd = ~cmd;

    IR_PULSE_TWC(START);

    for(count = 0; count < 5; count++)
    {
        if(device & 0x10)
            IR_PULSE_TWC(ONE);
        else
            IR_PULSE_TWC(ZERO);

        device<<=1;
    }
    for(count = 0; count < 6; count++)
    {
        if(cmd & 0x20)
            IR_PULSE_TWC(ONE);
        else
            IR_PULSE_TWC(ZERO);

        cmd<<=1;
    }
    for(count = 0; count < 5; count++)
    {
        if(Ndevice & 0x10)
            IR_PULSE_TWC(ONE);
        else
            IR_PULSE_TWC(ZERO);

        Ndevice<<=1;
    }
    for(count = 0; count < 6; count++)
    {
        if(Ncmd & 0x20)
            IR_PULSE_TWC(ONE);
        else
            IR_PULSE_TWC(ZERO);

        Ncmd<<=1;
    }


    IR_PULSE_TWC(MISC);
}

void IR_PULSE_TWC (unsigned char type)
{

    unsigned int time;

    switch(type)
    {
        case START:
            time = 195;
            while(time--)
            {
                cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(4);
				__asm__("nop\n\t"); //
                sbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(4);
				__asm__("nop\n\t"); //delayMicroseconds(1);
            }

            cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
            delay(3);
            delayMicroseconds(330);
            break;
        case ONE:
            time = 48;
            while(time--)
            {
                cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(4);
                sbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(4);
            }

            cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
            delay(2);
            delayMicroseconds(540);
            break;
        case ZERO:
            time = 48;
            while(time--)
            {
                cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(4);
                sbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(4);
            }

            cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
            delayMicroseconds(837);
            break;
        case MISC:
            time = 48;
            while(time--)
            {
                cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(4);
                sbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(4);
            }
            cbi(PORTD, _ir_pin); //digitalWrite(_ir_pin, LOW); 
            break;

    }
    

}
void IR_DYNEX(unsigned char address_h, unsigned char address_l, unsigned char command)
{
    unsigned char iCmd = 0;
    unsigned char count = 0;
    unsigned char cmd = command;

    for(count = 0; count < 8; count++)
    {
        iCmd>>=1;

        if(cmd & 0x01)
            iCmd &= 0x7F;
        else
            iCmd |= 0x80;

        cmd>>=1;
    }

    IR_PULSE_DYNEX(START);

    for(count = 0; count < 8; count++)
    {
        if(address_h & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        address_h<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(address_l & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        address_l<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(command & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        command<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(iCmd & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        iCmd<<=1;
    }

    IR_PULSE_DYNEX(MISC);

}

void IR_PULSE_DYNEX (unsigned char type)
{

    unsigned int time;//0.00000001

    switch(type)
    {
        case START:
            time = 341;
            while(time--)
            {
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(10);
            }

            digitalWrite(_ir_pin, LOW); 
            delay(4);
            delayMicroseconds(480);//700 //delayMicroseconds(475);
            break;
        case ONE:
            time = 21;
            while(time--)
            {
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(10);
            }

            digitalWrite(_ir_pin, LOW); 
            delay(1);
            delayMicroseconds(480); //665
            break;
        case ZERO:
            time = 21;
            while(time--)
            {
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(10);
            }

            digitalWrite(_ir_pin, LOW); 
            delayMicroseconds(480);
            break;
        case MISC:
            time = 21;
            while(time--)
            {
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(10);
            }
            digitalWrite(_ir_pin, LOW); 
            break;

    }

}
void IR_LG(unsigned char dat1, unsigned char dat2, unsigned char data)
{
    unsigned char reci = 0;
    unsigned char count = 0;
    unsigned char dat0 = data;

    for(count = 0; count < 8; count++)
    {
        reci>>=1;

        if(dat0 & 0x01)
            reci &= 0x7F;
        else
            reci |= 0x80;

        dat0>>=1;
    }

    IR_PULSE_LG(START);

    for(count = 0; count < 8; count++)
    {
        if(dat1 & 0x80)
            IR_PULSE_LG(ONE);
        else
            IR_PULSE_LG(ZERO);

        dat1<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(dat2 & 0x80)
            IR_PULSE_LG(ONE);
        else
            IR_PULSE_LG(ZERO);

        dat2<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(data & 0x80)
            IR_PULSE_LG(ONE);
        else
            IR_PULSE_LG(ZERO);

        data<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(reci & 0x80)
            IR_PULSE_LG(ONE);
        else
            IR_PULSE_LG(ZERO);

        reci<<=1;
    }

    IR_PULSE_LG(MISC);

}

void IR_PULSE_LG (unsigned char type)
{

    unsigned int time;//0.00000001

    switch(type)
    {
        case START:
            time = 341;
            while(time--)
            {
                sbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(5);
                cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(14);
            }

            cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
            delay(4);
            delayMicroseconds(480);//700 //delayMicroseconds(475);
            break;
        case ONE:
            time = 21;
            while(time--)
            {
                sbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(5);
                cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(14);
            }

            cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
            delay(1);
            delayMicroseconds(480); //665
            break;
        case ZERO:
            time = 21;
            while(time--)
            {
                sbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(5);
                cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(14);
            }

            cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
            delayMicroseconds(480);
            break;
        case MISC:
            time = 21;
            while(time--)
            {
                sbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(5);
                cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(14);
            }
            cbi(PORTD, _ir_pin);//digitalWrite(_ir_pin, LOW); 
            break;

    }

}
