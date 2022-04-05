/*
 * PORT.h
 *
 *  Created on: Feb 24, 2022
 *      Author: Danea
 */

#include "msp.h"

#ifndef PORT_H_
#define PORT_H_

void set_output(int port, int pin) {
//  PX->DIR
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            P1->DIR |= bitMask; // Offset for pin number and set as output
            break;
        case 2:
            P2->DIR |= bitMask;
            break;
        case 3:
            P3->DIR |= bitMask;
            break;
        case 4:
            P4->DIR |= bitMask;
            break;
        case 5:
            P5->DIR |= bitMask;
            break;
        case 6:
            P6->DIR |= bitMask;
            break;
        case 7:
            P7->DIR |= bitMask;
            break;
        case 8:
            P8->DIR |= bitMask;
            break;
        case 9:
            P9->DIR |= bitMask;
            break;
        case 10:
            P10->DIR |= bitMask;
            break;
        default:
            break;
    }
}

void set_input(int port, int pin) {
//  PX->OUT, PX->REN
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            P1->DIR &= ~bitMask; // Set as input
            P1->REN |= bitMask; // Enable pull-resistor
            P1->OUT |= bitMask; // Set as pull-up
            break;
        case 2:
            P2->DIR &= ~bitMask;
            P2->REN |= bitMask;
            P2->OUT |= bitMask;
            break;
        case 3:
            P3->DIR &= ~bitMask;
            P3->REN |= bitMask;
            P3->OUT |= bitMask;
            break;
        case 4:
            P4->DIR &= ~bitMask;
            P4->REN |= bitMask;
            P4->OUT |= bitMask;
            break;
        case 5:
            P5->DIR &= ~bitMask;
            P5->REN |= bitMask;
            P5->OUT |= bitMask;
            break;
        case 6:
            P6->DIR &= ~bitMask;
            P6->REN |= bitMask;
            P6->OUT |= bitMask;
            break;
        case 7:
            P7->DIR &= ~bitMask;
            P7->REN |= bitMask;
            P7->OUT |= bitMask;
            break;
        case 8:
            P8->DIR &= ~bitMask;
            P8->REN |= bitMask;
            P8->OUT |= bitMask;
            break;
        case 9:
            P9->DIR &= ~bitMask;
            P9->REN |= bitMask;
            P9->OUT |= bitMask;
            break;
        case 10:
            P10->DIR &= ~bitMask;
            P10->REN |= bitMask;
            P10->OUT |= bitMask;
            break;
        default:
            break;
    }
}

void toggle_output(int port, int pin) {
//  PX->OUT
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            P1->OUT ^= bitMask; // Flip the bit for the pin to toggle its output
            break;
        case 2:
            P2->OUT ^= bitMask;
            break;
        case 3:
            P3->OUT ^= bitMask;
            break;
        case 4:
            P4->OUT ^= bitMask;
            break;
        case 5:
            P5->OUT ^= bitMask;
            break;
        case 6:
            P6->OUT ^= bitMask;
            break;
        case 7:
            P7->OUT ^= bitMask;
            break;
        case 8:
            P8->OUT ^= bitMask;
            break;
        case 9:
            P9->OUT ^= bitMask;
            break;
        case 10:
            P10->OUT ^= bitMask;
            break;
        default:
            break;
    }
}

// Set the given pin output
void set(int port, int pin) {
    uint8_t bitMask = 0x1 << pin; // Offset for pin number
    switch(port) {
        case 1:
            P1->OUT |= bitMask;
            break;
        case 2:
            P2->OUT |= bitMask;
            break;
        case 3:
            P3->OUT |= bitMask;
            break;
        case 4:
            P4->OUT |= bitMask;
            break;
        case 5:
            P5->OUT |= bitMask;
            break;
        case 6:
            P6->OUT |= bitMask;
            break;
        case 7:
            P7->OUT |= bitMask;
            break;
        case 8:
            P8->OUT |= bitMask;
            break;
        case 9:
            P9->OUT |= bitMask;
            break;
        case 10:
            P10->OUT |= bitMask;
            break;
        default:
            break;
    }
}


// Reset the given pin output
void reset(int port, int pin) {
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            P1->OUT &= ~bitMask; // Offset for pin number
            break;
        case 2:
            P2->OUT &= ~bitMask;
            break;
        case 3:
            P3->OUT &= ~bitMask;
            break;
        case 4:
            P4->OUT &= ~bitMask;
            break;
        case 5:
            P5->OUT &= ~bitMask;
            break;
        case 6:
            P6->OUT &= ~bitMask;
            break;
        case 7:
            P7->OUT &= ~bitMask;
            break;
        case 8:
            P8->OUT &= ~bitMask;
            break;
        case 9:
            P9->OUT &= ~bitMask;
            break;
        case 10:
            P10->OUT &= ~bitMask;
            break;
        default:
            break;
    }
}

uint8_t input(int port, int pin) {
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            return ((P1->IN & bitMask) >> pin); // Mask for the pin and return the input value
        case 2:
            return ((P2->IN & bitMask) >> pin);
        case 3:
            return ((P3->IN & bitMask) >> pin);
        case 4:
            return ((P4->IN & bitMask) >> pin);
        case 5:
            return ((P5->IN & bitMask) >> pin);
        case 6:
            return ((P6->IN & bitMask) >> pin);
        case 7:
            return ((P7->IN & bitMask) >> pin);
        case 8:
            return ((P8->IN & bitMask) >> pin);
        case 9:
            return ((P9->IN & bitMask) >> pin);
        case 10:
            return ((P10->IN & bitMask) >> pin);
        default:
            return 0xF;
    }
}

void output(int port, int pin, int value) {
//  PX->OUT
    // If value is positive, output high
    if (value > 0) {
        set(port, pin);
    }
    // Output low otherwise
    else {
        reset(port, pin);
    }
}

void digital(int port, int pin) {
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            P1->SEL0 &= ~bitMask; // Offset for pin number
            P1->SEL1 &= ~bitMask;
            break;
        case 2:
            P2->SEL0 &= ~bitMask;
            P2->SEL1 &= ~bitMask;
            break;
        case 3:
            P3->SEL0 &= ~bitMask;
            P3->SEL1 &= ~bitMask;
            break;
        case 4:
            P4->SEL0 &= ~bitMask;
            P4->SEL1 &= ~bitMask;
            break;
        case 5:
            P5->SEL0 &= ~bitMask;
            P5->SEL1 &= ~bitMask;
            break;
        case 6:
            P6->SEL0 &= ~bitMask;
            P6->SEL1 &= ~bitMask;
            break;
        case 7:
            P7->SEL0 &= ~bitMask;
            P7->SEL1 &= ~bitMask;
            break;
        case 8:
            P8->SEL0 &= ~bitMask;
            P8->SEL1 &= ~bitMask;
            break;
        case 9:
            P9->SEL0 &= ~bitMask;
            P9->SEL1 &= ~bitMask;
            break;
        case 10:
            P10->SEL0 &= ~bitMask;
            P10->SEL1 &= ~bitMask;
            break;
        default:
            break;
    }
}

void analog(int port, int pin) {
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            P1->SEL0 |= bitMask; // Offset for pin number
            P1->SEL1 |= bitMask;
            break;
        case 2:
            P2->SEL0 |= bitMask;
            P2->SEL1 |= bitMask;
            break;
        case 3:
            P3->SEL0 |= bitMask;
            P3->SEL1 |= bitMask;
            break;
        case 4:
            P4->SEL0 |= bitMask;
            P4->SEL1 |= bitMask;
            break;
        case 5:
            P5->SEL0 |= bitMask;
            P5->SEL1 |= bitMask;
            break;
        case 6:
            P6->SEL0 |= bitMask;
            P6->SEL1 |= bitMask;
            break;
        case 7:
            P7->SEL0 |= bitMask;
            P7->SEL1 |= bitMask;
            break;
        case 8:
            P8->SEL0 |= bitMask;
            P8->SEL1 |= bitMask;
            break;
        case 9:
            P9->SEL0 |= bitMask;
            P9->SEL1 |= bitMask;
            break;
        case 10:
            P10->SEL0 |= bitMask;
            P10->SEL1 |= bitMask;
            break;
        default:
            break;
    }
}

void communication(int port, int pin) {
    uint8_t bitMask = 0x1 << pin;
    switch(port) {
        case 1:
            P1->SEL0 |=  bitMask; // Offset for pin number
            P1->SEL1 &= ~bitMask;
            break;
        case 2:
            P2->SEL0 |=  bitMask;
            P2->SEL1 &= ~bitMask;
            break;
        case 3:
            P3->SEL0 |=  bitMask;
            P3->SEL1 &= ~bitMask;
            break;
        case 4:
            P4->SEL0 |=  bitMask;
            P4->SEL1 &= ~bitMask;
            break;
        case 5:
            P5->SEL0 |=  bitMask;
            P5->SEL1 &= ~bitMask;
            break;
        case 6:
            P6->SEL0 |=  bitMask;
            P6->SEL1 &= ~bitMask;
            break;
        case 7:
            P7->SEL0 |=  bitMask;
            P7->SEL1 &= ~bitMask;
            break;
        case 8:
            P8->SEL0 |=  bitMask;
            P8->SEL1 &= ~bitMask;
            break;
        case 9:
            P9->SEL0 |=  bitMask;
            P9->SEL1 &= ~bitMask;
            break;
        case 10:
            P10->SEL0 |=  bitMask;
            P10->SEL1 &= ~bitMask;
            break;
        default:
            break;
    }
}

#endif /* PORT_H_ */
