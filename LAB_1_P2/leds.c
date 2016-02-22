/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#include "leds.h"
#define INPUT 1
#define OUTPUT 0
#define OFF 0;
#define ON 1;


void initLEDs(){
    //TODO: Initialize the appropriate pins to work with the LEDs
//    TRISGbits.TRISG12 = OUTPUT;
//    TRISGbits.TRISG14 = OUTPUT;
//    ODCGbits.ODCG12 = 1;
//    ODCGbits.ODCG14 = 1;
      TRISDbits.TRISD0 = OUTPUT;
      TRISDbits.TRISD1 = OUTPUT;
    
}
void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    if(led == 1)
    {
//        LATGbits.LATG12 = ON;
//        LATGbits.LATG14 = OFF;
          LATDbits.LATD0 = ON;
          LATDbits.LATD1 = OFF;
    }else if(led == 2)
    {
//        LATGbits.LATG12 = OFF;
//        LATGbits.LATG14 = ON;
          LATDbits.LATD0 = OFF;
          LATDbits.LATD1 = ON;
    }
    else
    {
//        LATGbits.LATG12 = OFF;
//        LATGbits.LATG14 = OFF;
          LATDbits.LATD0 = OFF;
          LATDbits.LATD1 = OFF;
    }
}