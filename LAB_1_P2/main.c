// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         Feb 16, 2016
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "switch.h"
#include "leds.h"
#include "config.h"
#include "interrupt.h"

volatile unsigned int SW2 = 0;
// ******************************************************************************************* //

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initLEDs();
    initTimer1();
    initTimer2();
    initSW2();
    int i;
    
    while(1)
    {        testLCD();
//           turnOnLED(0);
//           moveCursorLCD(1,1);
//           printStringLCD("Hello!");
//           delaySec(1);
//           clearLCD();
//          
//           turnOnLED(2);
//           moveCursorLCD(1,2);
//           printStringLCD("Hello!");
//           delaySec(1);

//           clearLCD();
//           if(SW2 ==  1)
//           {    
//               turnOnLED(1);
//               initLCD();
//               SW2 = 0;
//               writeLCD(0x06,0,100); //cursor remain stationary
//           }     
    }
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    //SW 2 ISR
    
    IFS1bits.CNDIF = 0; //FLAG DOWN
    PORTD; //SWITCH BACK TO A AND RA7
    int i;
    i = PORTD;
    
    if(PORTDbits.RD6 == 0)
    {   SW2 = 1;
    }
}
