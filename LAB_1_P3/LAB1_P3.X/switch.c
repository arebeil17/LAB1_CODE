/*
 * File:   switch.c
 * Author: Andres D. Rebeil
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include "switch.h"
#define INPUT 1
#define OUTPUT 0
#define ENABLED 1;
#define DISABLED 0;
#define pressed_released 1
#define not_pressed 1
#define pressed 0

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
    //HOPEFULLY TO FIX THE SECOND SWITCH ISSUE
    //Make three different states.  
    //first where sw2 is initially on and sw1 off. 
    //The second stage where sw1 is initially on and sw2 is off
    //and the third when both are off
    //if state is run you enable this . in stop they both need to be used????
    //run for stop state
    if (command == 0) {
    //FOR SW2
        CNCONAbits.ON = DISABLED;           // Disable overall interrupt
        CNENAbits.CNIEA7 = DISABLED;         // Disable pin CN
        IEC1bits.CNAIE = DISABLED;           // Disable interrupt for A pins
    //FOR SW1
        CNCONDbits.ON = DISABLED;            // Disable overall interrupt
        CNENDbits.CNIED6 = DISABLED;         // Disable pin CN
        IEC1bits.CNDIE = DISABLED;           // Disable interrupt for D pins
 
    } else if(command == 1){
    //FOR SW2   
        CNCONAbits.ON = ENABLED;            // Enable overall interrupt
        CNENAbits.CNIEA7 = ENABLED;         // Enable pin CN
        IEC1bits.CNAIE = ENABLED;           // Enable interrupt for A pins
    //FOR SW1     
        CNCONDbits.ON = ENABLED;            // Enable overall interrupt
        CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
        IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
  
    } 
    else if (command == 2) {    //SW2 enabled, SW1 disabled
        //FOR SW2   
        CNCONAbits.ON = ENABLED;            // Enable overall interrupt
        CNENAbits.CNIEA7 = ENABLED;         // Enable pin CN
        IEC1bits.CNAIE = ENABLED;           // Enable interrupt for A pins
        
    //FOR SW1     
        CNCONDbits.ON = DISABLED;            // Disable overall interrupt
        CNENDbits.CNIED6 = DISABLED;         // Disable pin CN
        IEC1bits.CNDIE = DISABLED;           // Disable interrupt for D pins

    } 
    else if (command == 3) {    //SW1 enabled, SW2 disabled
        //FOR SW2   
        CNCONAbits.ON = DISABLED;            // Disable overall interrupt
        CNENAbits.CNIEA7 = DISABLED;         // Disable pin CN
        IEC1bits.CNAIE = DISABLED;           // Disable interrupt for A pins
    //FOR SW1     
        CNCONDbits.ON = ENABLED;            // Enable overall interrupt
        CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
        IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
    } else {
     //FOR SW2
        CNCONAbits.ON = DISABLED;           // Disable overall interrupt
        CNENAbits.CNIEA7 = DISABLED;         // Disable pin CN
        IEC1bits.CNAIE = DISABLED;           // Disable interrupt for A pins
    //FOR SW1
        CNCONDbits.ON = DISABLED;            // Disable overall interrupt
        CNENDbits.CNIED6 = DISABLED;         // Disable pin CN
        IEC1bits.CNDIE = DISABLED;           // Disable interrupt for D pins
    } 
}
