// 74HC165TestMain.c
// Runs on MSP432
// Use eUSCI3 to receive an 8-bit code from the 74HC165.
// Input port expander
// Daniel Valvano
// July 22, 2015

/* This example accompanies the book
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2015
   Program 7.3

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// MSP432        74HC165
//   +3.3        pin 16 Vcc powewr
//   Gnd         pin 8  ground
//   Gnd         pin 15 CLK INH (allow clock to operate)
//   Gnd         pin 10 SER (data in is NA)
// P9.5 UCA3CLK  pin 2  CLK
// P9.4 UCA3STE  pin 1  SH/LD (0 for load, 1 for shift)
// P9.6 UCA3SOMI pin 9  Qh (data shifted out)
//     nc        pin 7  Qh' is not needed

// Port          74HC165
// bit 7 (MSB)   pin 6  H
// bit 6         pin 5  G
// bit 5         pin 4  F
// bit 4         pin 3  E
// bit 3         pin 14 D
// bit 2         pin 13 C
// bit 1         pin 12 B
// bit 0 (LSB)   pin 11 A

#include <stdint.h>
#include "74HC165.h"

uint8_t Data=0;
int main(void) {
  Port_Init();
  while(1){
    Data = Port_In();
  }
}
