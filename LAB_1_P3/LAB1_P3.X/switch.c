/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include "switch.h"
#define INPUT 1
#define OUTPUT 0
#define ENABLED 1;
#define DISABLED 0;

void initSW(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
 //FOR SW2   
    TRISAbits.TRISA7 = INPUT;           // Configure switch as input
    CNCONAbits.ON = 1;                  // Enable overall interrupt
    CNENAbits.CNIEA7 = ENABLED;         // Enable pin CN
    CNPUAbits.CNPUA7 = ENABLED;         // Enable pull-up resistor
    IFS1bits.CNAIF = 0;                 // Put down the flag
    IPC8bits.CNIP = 2;                  // Configure interrupt priority
    IPC8bits.CNIS = 3;                  // Configure the interrupt sub-priority
    IEC1bits.CNAIE = ENABLED;           // Enable interrupt for A pins
    
//FOR SW1
    TRISDbits.TRISD6 = INPUT;           // Configure switch as input
    CNCONDbits.ON = 1;                  // Enable overall interrupt
    CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
    CNPUDbits.CNPUD6 = ENABLED;         // Enable pull-up resistor
    IFS1bits.CNDIF = 0;                 // Put down the flag
    IPC8bits.CNIP = 2;                  // Configure interrupt priority
    IPC8bits.CNIS = 3;                  // Configure the interrupt sub-priority
    IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
}

void SW_ISR_Control(int command){
    
    if(command == 1){
    //FOR SW2   
        CNCONAbits.ON = ENABLED;            // Enable overall interrupt
        CNENAbits.CNIEA7 = ENABLED;         // Enable pin CN
        IEC1bits.CNAIE = ENABLED;           // Enable interrupt for A pins
    //FOR SW1     
        CNCONDbits.ON = ENABLED;            // Enable overall interrupt
        CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
        IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
        
    } else {
    //FOR SW2
        CNCONAbits.ON = DISABLED;           // Enable overall interrupt
        CNENAbits.CNIEA7 = DISABLED;         // Enable pin CN
        IEC1bits.CNAIE = DISABLED;           // Enable interrupt for A pins
    //FOR SW1
        CNCONDbits.ON = DISABLED;            // Enable overall interrupt
        CNENDbits.CNIED6 = DISABLED;         // Enable pin CN
        IEC1bits.CNDIE = DISABLED;           // Enable interrupt for D pins

    }   
}
