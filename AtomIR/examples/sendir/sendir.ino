/*
  AtomIR 
  Send some IR Signals with a blink :)
 
 */
 
// Pin 13 has an LED connected on most Arduino boards.

#include "atomir.h"

// Pin 4 is our IR LED, which can be also changed to any I/O Pin
AtomIR myREM(4);

int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  
  //myREM.sendTWC(TWC_CABLE,TWC_CABLE_PAUSE);
  //myREM.sendDynex(DYNEX_TV,DYNEX_TV_VOLDOWN);
  //myREM.sendLGAC(LG_AC,LG_AC_TEMP_M);
}
