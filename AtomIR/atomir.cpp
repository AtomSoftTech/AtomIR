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
void IR_DYNEX(unsigned char dat1, unsigned char dat2, unsigned char data);
void IR_PULSE_DYNEX (unsigned char type);

int _ir_pin;

AtomIR::AtomIR(int ir_pin)
{
  pinMode(ir_pin, OUTPUT);
  _ir_pin = ir_pin;
}

void AtomIR::sendSIRC(unsigned char  dev, unsigned char  cmd)
{
  delay(1);  
}

void AtomIR::sendTWC(unsigned char  dev, unsigned char  cmd)
{
  IR_TWC(dev,cmd);
}

void AtomIR::sendRC6(unsigned char  dev, unsigned char  cmd)
{
  delay(1);
}

void AtomIR::sendDynex(unsigned char dev, unsigned char cmd)
{
  IR_DYNEX(DYNEX, dev, cmd);
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
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(2);
            }

            digitalWrite(_ir_pin, LOW); 
            delay(3);
            delayMicroseconds(330);
            break;
        case ONE:
            time = 48;
            while(time--)
            {
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(2);
            }

            digitalWrite(_ir_pin, LOW); 
            delay(2);
            delayMicroseconds(540);
            break;
        case ZERO:
            time = 48;
            while(time--)
            {
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(2);
            }

            digitalWrite(_ir_pin, LOW); 
            delayMicroseconds(837);
            break;
        case MISC:
            time = 48;
            while(time--)
            {
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(2);
            }
            digitalWrite(_ir_pin, LOW); 
            break;

    }

}
void IR_DYNEX(unsigned char dat1, unsigned char dat2, unsigned char data)
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

    IR_PULSE_DYNEX(START);

    for(count = 0; count < 8; count++)
    {
        if(dat1 & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        dat1<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(dat2 & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        dat2<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(data & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        data<<=1;
    }

    for(count = 0; count < 8; count++)
    {
        if(reci & 0x80)
            IR_PULSE_DYNEX(ONE);
        else
            IR_PULSE_DYNEX(ZERO);

        reci<<=1;
    }

    IR_PULSE_DYNEX(MISC);

}

void IR_PULSE_DYNEX (unsigned char type)
{

    unsigned int time;//0.00000001

    switch(type)
    {
        case START:
            time = 344;
            while(time--)
            {
                digitalWrite(_ir_pin, HIGH); 
                delayMicroseconds(1);
                digitalWrite(_ir_pin, LOW); 
                delayMicroseconds(10);
            }

            digitalWrite(_ir_pin, HIGH); 
            delay(4);
            delayMicroseconds(700);//delayMicroseconds(475);
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

            digitalWrite(_ir_pin, HIGH); 
            delay(1);
            delayMicroseconds(665);
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

            digitalWrite(_ir_pin, HIGH); 
            delayMicroseconds(665);
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
            digitalWrite(_ir_pin, HIGH); 
            break;

    }

}
