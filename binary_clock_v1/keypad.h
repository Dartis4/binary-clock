/*
 * keypad.h
 *
 *  Created on: Mar 29, 2022
 *      Author: Brother Allred
 *      Adapted by Dane Artis
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

// Port 3 Pins (Data Available signal)
#define DA BIT0

// Port 4 Pins (Keypad Data Pins)
#define DATAPINS (BIT0|BIT1|BIT2|BIT3)

int set_enable = 0;
int set_mode = 0;

/***
 * keypad decoder function
 ***/
uint8_t keypad_decode(void)
{
    uint8_t key = 0;

    // Read data from keypad into a variable
    uint8_t data = P4->IN & DATAPINS;

    // Translate the data from the keypad provided value to the printed button values
    switch (data)
    {
    case 0x0D:
        key = 0x0;
        break; /* 0 */
    case 0x00:
        key = 0x1;
        break; /* 1 */
    case 0x01:
        key = 0x2;
        break; /* 2 */
    case 0x02:
        key = 0x3;
        break; /* 3 */
    case 0x04:
        key = 0x4;
        break; /* 4 */
    case 0x05:
        key = 0x5;
        break; /* 5 */
    case 0x06:
        key = 0x6;
        break; /* 6 */
    case 0x08:
        key = 0x7;
        break; /* 7 */
    case 0x09:
        key = 0x8;
        break; /* 8 */
    case 0x0A:
        key = 0x9;
        break; /* 9 */
    case 0x03:
        key = 0xA;
        break; /* A */
    case 0x07:
        key = 0xB;
        break; /* B */
    case 0x0B:
        key = 0xC;
        break; /* C */
    case 0x0F:
        key = 0xD;
        break; /* D */
    case 0x0C:
        key = 0xE;
        break; /* * */
    case 0x0E:
        key = 0xF;
        break; /* # */
    }

    return key;
}

void keypad_init(void)
{
    // Configure Data Input Pins (P4.0, 4.1, 4.2, 4.3)
    P4->DIR &= ~DATAPINS;       // set up data pins as inputs

    // Configure "Data Available" Signal Pin (P3.0)
    P3->DIR &= ~DA;             // set up DA pin as input
    P3->REN |= DA;              // connect pull resistor to DA
    P3->OUT |= DA;              // configure resistor as pull-up
    P3->IFG &= ~DA;             // clear interrupt flag for DA
    P3->IE |= DA;               // enable pin-level interrupt for DA

    // Enable Port-level Interrupts (Table 6.2)
    NVIC->ISER[1] |= 0x00000020;  // enable Port 3 interrupts
    NVIC->IP[37] = 0; // Set Priority

    // Enable Interrupts Generally
    __enable_interrupts();
    _enable_interrupts();
}

#endif /* KEYPAD_H_ */
