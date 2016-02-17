/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

/* The pins that you will use for the lcd control will be
 * LCD_RS      RC4
 * LCD_E       RC2
 * LCD_D4      RE7
 * LCD_D5      RE5
 * LCD_D6      RE3
 * LCD_D7      RE1
 * Use these so that we will be able to test your code for grading and to
 * help you debug your implementation!
 */
#define Enable 1
#define Disable 0

#define LCD_DATA  
#define LCD_RS LATCbits.LATC4
#define LCD_E  LATCbits.LATC2

#define OUTPUT 0
#define INPUT 1

#define TRIS_D7 TRISEbits.TRISE1
#define TRIS_D6 TRISEbits.TRISE3
#define TRIS_D5 TRISEbits.TRISE5
#define TRIS_D4 TRISEbits.TRISE7
#define TRIS_RS TRISCbits.TRISC4
#define TRIS_E  TRISCbits.TRISC2

#define LCD_D7 LATEbits.LATE1
#define LCD_D6 LATEbits.LATE3
#define LCD_D5 LATEbits.LATE5
#define LCD_D4 LATEbits.LATE7

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATE. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
     // set the commandType (RS value)
     LCD_RS = commandType;
    
     if(lower){
        LCD_D4 = word&0x01;
        LCD_D5 = word&0x02;
        LCD_D6 = word&0x04;
        LCD_D7 = word&0x08;
     } else
     {
        LCD_D4 = word&0x10;
        LCD_D5 = word&0x20;
        LCD_D6 = word&0x40;
        LCD_D7 = word&0x80;
     }
    //enable
    LCD_E = Enable;
    //delay
    delayUs(1);
    //disable
    LCD_E = Disable;
    if(lower) delayUs(delayAfter);
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
    writeFourBits(word,commandType, delayAfter, 0);
    writeFourBits(word,commandType, delayAfter, 1);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c,1,46);
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    TRIS_D4 = OUTPUT;
    TRIS_D5 = OUTPUT;
    TRIS_D6 = OUTPUT;
    TRIS_D7 = OUTPUT;
    TRIS_E = OUTPUT;
    TRIS_RS = OUTPUT;
    // Initialization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initialization commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.
    
      delayMs(20);
    // Enable 4-bit interface
      writeFourBits(0x03, 0, 4100, 1);
      writeFourBits(0x03, 0, 100, 1);
      writeFourBits(0x30, 0, 0, 1);
      
      //Function Set 4 bit
      writeFourBits(0x02, 0, 40, 1);
      //Function Set
      writeFourBits(0x10,0,0,0);
      writeFourBits(0x08,0,40,1);
      // Turn Display (D) Off
      writeFourBits(0x00,0,100,0);
      writeFourBits(0x08,0,40,1);
      //Clear Display
      writeFourBits(0x00,0,0,0);
      writeFourBits(0x01,0,1800,1);
      //Entry Mode set
      writeFourBits(0x00,0,0,0);
      writeFourBits(0x07,0,40,1);
      //Display On/Off Control
      // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
      writeFourBits(0x00,0,0,0);
      writeFourBits(0x0C,0,40,1);
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
    int i;
    unsigned int size = strlen(s);
    
    for(i = 0; i < size; i++)
    {
        printCharLCD(s[i]);
    }   
}

/*
 * Clear the display.
 */
void clearLCD(){
    
    writeFourBits(0x00, 0, 0 , 0);
    writeFourBits(0x01, 0, 1800 , 1);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    
    if(y == 1) {
        if(x == 1 ) writeFourBits(0x08,0,40,1);      //0000 1000
        else if(x == 2 ) writeFourBits(0x09,0,40,1); //0000 1001
        else if(x == 3 ) writeFourBits(0x0A,0,40,1); //0000 1010
        else if(x == 4 ) writeFourBits(0x0B,0,40,1); //0000 1011
        else if(x == 5 ) writeFourBits(0x0C,0,40,1); //0000 1100
        else if(x == 6 ) writeFourBits(0x0D,0,40,1); //0000 1101
        else if(x == 7 ) writeFourBits(0x0E,0,40,1); //0000 1110
        else if(x == 8 ) writeFourBits(0x0F,0,40,1); //0000 1111
        
    }else if(y == 2){
        if(x == 1 ) writeFourBits(0x28,0,40,1);      //0010 1000
        else if(x == 2 ) writeFourBits(0x29,0,40,1); //0010 1000
        else if(x == 3 ) writeFourBits(0x2A,0,40,1); //0010 1000
        else if(x == 4 ) writeFourBits(0x2B,0,40,1); //0010 1000
        else if(x == 5 ) writeFourBits(0x2C,0,40,1); //0010 1000
        else if(x == 6 ) writeFourBits(0x2D,0,40,1); //0010 1000
        else if(x == 7 ) writeFourBits(0x2E,0,40,1); //0010 1000
        else if(x == 8 ) writeFourBits(0x2F,0,40,1); //0010 1000
    }
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}