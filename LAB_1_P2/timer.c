/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"
#include <math.h>

void initTimer1(){
    TMR1 = 0;
    T1CONbits.ON = 0;   //ENABLE CN
    T1CONbits.TCKPS = 0;
    T1CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
}

void delayMs(unsigned int delay){
    TMR1 = 0;                  //RESET TIME
    PR1 = delay*5000;           
    IFS0bits.T1IF = 0;         // SETS FLAG
    T1CONbits.ON = 1;          //ENABLE CN
    while(IFS0bits.T1IF == 0); //DELAY TILL FLAG IS RAISED
    T1CONbits.ON = 0;          //DISABLE CN
}



void delayUs(unsigned int delay){

    //TODO: Create a delay for "delay" micro seconds using timer 2
    TMR1 = 0;                  //RESET TIME
    PR1 = delay*5;           //SET PRESCALAR
    IFS0bits.T1IF = 0;         // SETS FLAG
    T1CONbits.ON = 1;          //ENABLE CN
    while(IFS0bits.T1IF == 0); //DELAY TILL FLAG IS RAISED
    T1CONbits.ON = 0;          //DISABLE CN
}