/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"


void initTimer1(){
    TMR1 = 0;
    T1CONbits.ON = 0;   //ENABLE CN
    T1CONbits.TCKPS = 2; 
    T1CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
}

void delayMs(unsigned int delay){
    TMR1 = 0;                  //RESET TIME
    PR1 = delay*624;           //SET PRESCALAR
    IFS0bits.T1IF = 0;         // SETS FLAG
    T1CONbits.ON = 1;          //ENABLE CN
    while(IFS0bits.T1IF == 0); //DELAY TILL FLAG IS RAISED
    T1CONbits.ON = 0;          //DISABLE CN
}

//Uses timer 2
void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR1 = 0;                  //RESET TIME
    PR1 = delay;           //SET PRESCALAR
    IFS0bits.T1IF = 0;         // SETS FLAG
    T1CONbits.ON = 1;          //ENABLE CN
    while(IFS0bits.T1IF == 0); //DELAY TILL FLAG IS RAISED
    T1CONbits.ON = 0;          //DISABLE CN
}