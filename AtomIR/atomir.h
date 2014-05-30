/*
  atomir.h - Library for controlling an IR led
  Created by Jason Lopez (AtomSoft), May 29, 2014..
  Not to be released to public.
*/

#ifndef AtomIR_h
#define AtomIR_h

#include "Arduino.h"

//TWC Remote Codes
#define TWC 0x60
#define TWC_CABLE 0x1B
#define TWC_CABLE_VIDEO 0x2C
#define TWC_CABLE_UP 0x10 // 016
#define TWC_CABLE_SWAP 0x0F
#define TWC_CABLE_STOP 0x0B // 011
#define TWC_CABLE_STAR 0x3c //060
#define TWC_CABLE_SHIFT 0x3e
#define TWC_CABLE_SETTING 0x27 //039
#define TWC_CABLE_RIGHT 0x08 // 008
#define TWC_CABLE_REWIND 0x25 // 037
#define TWC_CABLE_RECORD 0x2b // 043
#define TWC_CABLE_POUND 0x17 // 023
#define TWC_CABLE_PLAY 0x33  // 051
#define TWC_CABLE_PAGEUP 0x1b //027
#define TWC_CABLE_PAGEDN 0x3b //059
#define TWC_CABLE_PAUSE 0x28 // 040
#define TWC_CABLE_PIP 0x37
#define TWC_CABLE_MUTE 0x11
#define TWC_CABLE_MOVE 0x2f
#define TWC_CABLE_MENU 0x1f //031
#define TWC_CABLE_M2 0x27
#define TWC_CABLE_M1 0x2d
#define TWC_CABLE_LIVE 0x16  // 022
#define TWC_CABLE_LIST 0x19  // 025
#define TWC_CABLE_LEFT 0x30 // 048
#define TWC_CABLE_LAST 0x1c
#define TWC_CABLE_JMPBCK 0x39 //057
#define TWC_CABLE_INFO 0x04 //004
#define TWC_CABLE_GUIDE 0x18
#define TWC_CABLE_FFW 0x05  // 005
#define TWC_CABLE_FAV 0x3e
#define TWC_CABLE_EXIT 0x0D // 013
#define TWC_CABLE_ENTER 0x0C // 012
#define TWC_CABLE_DOWN 0x34 // 052
#define TWC_CABLE_DAYUP 0x3c
#define TWC_CABLE_DAYDN 0x02
#define TWC_CABLE_D 0x2F
#define TWC_CABLE_CHUP 0x2e // 046
#define TWC_CABLE_CHDN 0x1e // 030
#define TWC_CABLE_C 0x23
#define TWC_CABLE_B 0x03
#define TWC_CABLE_A 0x3D
#define TWC_CABLE_9 0x06 // 006
#define TWC_CABLE_8 0x3A // 058
#define TWC_CABLE_7 0x1A // 026
#define TWC_CABLE_6 0x2A // 042
#define TWC_CABLE_5 0x0A // 010
#define TWC_CABLE_4 0x32 // 050
#define TWC_CABLE_3 0x12 // 018
#define TWC_CABLE_2 0x22 // 034
#define TWC_CABLE_1 0x02 // 002
#define TWC_CABLE_0 0x26 // 038
#define TWC_CABLE_PIPUP 0x1D
#define TWC_CABLE_PIPDN  0x3F


//Dynex Remote Codes
#define DYNEX 0x61
#define DYNEX_TV 0xA0
#define DYNEX_TV_HDMI 0x0A //010
#define DYNEX_TV_TIME 0X59
#define DYNEX_TV_SLEEP 0XC8
#define DYNEX_TV_SAP 0X88
#define DYNEX_TV_CCD 0X38
#define DYNEX_TV_BLUE 0X29
#define DYNEX_TV_YELLOW 0XC9
#define DYNEX_TV_GREEN 0X49
#define DYNEX_TV_RED 0X89
#define DYNEX_TV_RECALL 0X08
#define DYNEX_TV_DOT 0X82
#define DYNEX_TV_ZERO 0X90
#define DYNEX_TV_NINE 0X10
#define DYNEX_TV_EIGHT 0XE0
#define DYNEX_TV_SEVEN 0X60
#define DYNEX_TV_SIX 0XA0
#define DYNEX_TV_FIVE 0X20
#define DYNEX_TV_FOUR 0XC0
#define DYNEX_TV_THREE 0X40
#define DYNEX_TV_TWO 0X80
#define DYNEX_TV_ONE 0X00
#define DYNEX_TV_DOWN 0XC2
#define DYNEX_TV_ENTER 0X18
#define DYNEX_TV_RIGHT 0XA8
#define DYNEX_TV_LEFT 0X68
#define DYNEX_TV_UP 0X42
#define DYNEX_TV_EXIT 0XD8
#define DYNEX_TV_MENU 0X27
#define DYNEX_TV_CHANDOWN 0XD0
#define DYNEX_TV_MUTE 0X70
#define DYNEX_TV_VOLDOWN 0XB0 //176
#define DYNEX_TV_CHANUP 0X50
#define DYNEX_TV_INFO 0XE8
#define DYNEX_TV_VOLUP 0X30 //048
#define DYNEX_TV_AUDIO 0X12
#define DYNEX_TV_PICTURE 0X92
#define DYNEX_TV_GUIDE 0XA2
#define DYNEX_TV_ZOOM 0X22
#define DYNEX_TV_VGA 0X72
#define DYNEX_TV_COMP 0XB2
#define DYNEX_TV_VIDEO 0X32
#define DYNEX_TV_INPUT 0XB8
#define DYNEX_TV_TV 0XF2
#define DYNEX_TV_POWER 0XF0 //0x0F//015


class AtomIR
{
  public:
    AtomIR(int ir_pin);
    void sendSIRC(unsigned char dev, unsigned char cmd);
    void sendRC6(unsigned char dev, unsigned char cmd);
	void sendTWC(unsigned char dev, unsigned char cmd);
	void sendDynex(unsigned char dev, unsigned char cmd);
};

#endif