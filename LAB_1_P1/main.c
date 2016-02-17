// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"

typedef enum stateTypeEnum{
    RUN, STOP
} stateType;

//Volatile variable declarations
volatile stateType state = RUN;
volatile unsigned int SW2 = 0;

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    
    initLEDs();
    initSW2();
    initTimer1();
    turnOnLED(1);
   
    
    while(1)
    {
//        if(SW2 == 2) {
//            delayMs(5);
//            SW2 = 0;}
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //De-bounce the switch
        if(SW2 == 1){
            delayMs(5);
            switch(state){
                
                case RUN:
                    if(SW2 == 1) state = STOP;
                    else state = RUN;
                    turnOnLED(1);
                    SW2 = 0;
                    
                break;

                case STOP: 
                   if(SW2 == 1) state = RUN;
                   else state = STOP;
                   turnOnLED(2);
                   SW2 = 0;
                   
                break;
            }
          delayMs(5);
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    //SW 2 ISR
    
    IFS1bits.CNAIF = 0; //FLAG DOWN
    PORTA; //SWITCH BACK TO A AND RA7
    
    //if(PORTAbits.RA7 == 0) SW2 = 2;
    
    
    if(PORTAbits.RA7 == 1) SW2 = 1;
    else {
        //delayMs(5);
        SW2 = 0;
    }
    
     
}