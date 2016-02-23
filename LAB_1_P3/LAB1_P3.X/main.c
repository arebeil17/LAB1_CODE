// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         Feb 16, 2016
// Authors:      Andres D. Rebeil
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

typedef enum stateTypeEnum{
    INITIAL, RUN, STOP , RESET
} stateType;

//Volatile variable declarations
volatile stateType state = RUN;
volatile unsigned int SW2 = 0, SW1 = 1, i = 0, j = 0, temp = 0,
                      Pressed_1 = 0, Pressed_2 = 0;

// ******************************************************************************************* //

int main(void)
{
    
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    
    //INITIALIZING PROCESS
    initLEDs();
    initTimer1();
    initTimer2();
    
    initLCD();
    initSW();
    turnOnLED(4);
    delaySec(3);
   //INITIALIZING COMPLETE
    
    while(1)
    {    
        
        if(state == STOP) SW_ISR_Control(1);
        else SW_ISR_Control(2);
        

        if(state != RUN) delayMs(50); 
            
        if((Pressed_1 == 1) || (Pressed_2 == 1)) delayMs(50);
            //SW2 HAS PRIORITY
            if((SW2 == 1) || (SW1 == 1)){
                delayMs(10);
                switch(state){
                    
                    case INITIAL:
                        if(SW2 == 1) state = RUN; 
                        SW2 = 0; SW1 = 0;
                         i = 0;
                        turnOnLED(0);
                    break;

                    case RUN:
                        if(SW2 == 1) state = STOP; 
                        SW2 = 0; SW1 = 0;
                        //turnOnLED(1);
                    break;
                    case STOP:
                       if(SW2 == 1) state = RUN;
                       else if(SW1 == 1) state = RESET;
                       SW2 = 0; SW1 = 0;
                       turnOnLED(2);
                    break;
                    case RESET:
                        if(SW2 == 1) state = RUN;
                        SW2 = 0; SW1 = 0;
                        turnOnLED(2);
                        i = 0; 
                    break;
                }
                delayMs(10);
            }
        
        
        if(state != RUN) SW_ISR_Control(0);
  

        if(SW2 == 0){
            if(state == INITIAL) {
                i = 0;
                turnOnLED(0);
                moveCursorLCD(1,1);
                printStringLCD("Stopped:");
                moveCursorLCD(1,2);
                getString(1,0);
            }else if(state == RUN){
                turnOnLED(1);
                delayMs(1);
                if((i%10) == 0){
                    SW_ISR_Control(0);
                    moveCursorLCD(1,1);
                    printStringLCD("Running:");
                    moveCursorLCD(1,2);
                    getString(0,i);
                }
                i = i + 1;
            }
            else if(state == STOP){
                turnOnLED(2);
                moveCursorLCD(1,1);
                printStringLCD("Stopped:");
                moveCursorLCD(1,2);
                getString(0,temp);
            }
            else if(state == RESET){
                turnOnLED(2);
                i = 0;
                moveCursorLCD(1,1);
                printStringLCD("Stopped:");
                moveCursorLCD(1,2);
                getString(1,0);
            }
        }
    }
    return 0;
}
//void __ISR(_TIMER_1_VECTOR, IPL7SRS)_T1Interrupt()
//{
//    IFS0bits.T1IF = 0; //FLAG DOWN
//    LATDbits.LATD0 = LATDbits.LATD0;
//    //time++;
//}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //----------------------------------------
   
    int k;
    k = PORTD;
    
    temp = i;
        
    //CHECK SW1 TOGGLE
    if(state == STOP){
        
        if((PORTDbits.RD6 == 1) && (Pressed_1 == 1))  { // not pressed
            SW1 = 1;              //released
            Pressed_1 = 0;
            //next_state = RESET;
        }
        else SW1 = 0;
   
        if(PORTDbits.RD6 == 0) { //released
            Pressed_1 = 1;
            Pressed_2 = 0;
        }
    } else SW1 = 0;
    //----------------------------------------
    //FOR RUN/STOP FUNCTION
    //IFS1bits.CNAIF = 0; //FLAG DOWN
    PORTA; 
    j = PORTAbits.RA7; //RA7
    
  
    
    //CHECK SW2 TOGGLE
    if((PORTAbits.RA7 == 1) && (Pressed_2 == 1)) { // not pressed
        SW2 = 1;             //released
        Pressed_2 = 0;
        //if(state == STOP) next_state = RUN;
    }
    else SW2 = 0; 
    if(PORTAbits.RA7 == 0) {
        Pressed_2 = 1;
        Pressed_1 = 0;
    }
    //IFS0bits.T2IF = 1;         // SETS FLAG AND STOPS TIMER 2
    //RESET FLAGS
    IFS1bits.CNDIF = 0; //FLAG DOWN
    IFS1bits.CNAIF = 0; //FLAG DOWN
}
