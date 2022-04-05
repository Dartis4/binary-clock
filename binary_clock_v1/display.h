/*
 * display.h
 *
 *  Created on: Mar 22, 2022
 *      Author: Danea
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "binary_time.h"

// Shortcuts for Port 6
#define CE      BIT0    // P6.0 chip enable
#define RESET   BIT6    // P6.6 reset
#define DC      BIT7    // P6.7 data/control

// Shortcuts for screen size
#define GLCD_WIDTH  84
#define GLCD_LENGTH 48

void convert_time(char realtime[6][6]);
void GLCD_display(void);
void GLCD_writePart(char part);
void GLCD_setCursor(unsigned char x, unsigned char y);
void GLCD_clear(void);
void GLCD_init(void);
void GLCD_data_write(unsigned char data);
void GLCD_command_write(unsigned char data);
void SPI_init(void);
void SPI_write(unsigned char data);

void convert_time(char realtime[6][6])
{
    /* Possible fill values:
     *      0x7F, // 0
     *      0xFE, // 1
     *      0x07, // 2
     *      0xE0, // 3
     *      0xE7, // 4
     *      0xFF  // 5
     */

    /* Row fill layouts:
     *      Bank0 - {1, 1, 1, 1, 1, 1}, // 0xFE
     *      Bank1 - {5, 2, 0, 2, 0, 2}, // 0xFF 0x07 0x7F
     *      Bank1 - {5, 3, 0, 3, 0, 3}, // 0xFF 0xE0 0x7F
     *      Bank1 - {5, 4, 0, 4, 0, 4}, // 0xFF 0xE7 0x7F
     *      Bank2 - {0, 0, 1, 0, 1, 0}, // 0x7F 0xFE
     *      Bank3 - {1, 1, 0, 1, 0, 1}, // 0xFE 0x7F
     *      Bank4 - {5, 2, 1, 2, 1, 2}, // 0xFF 0x07 0xFE
     *      Bank4 - {5, 3, 1, 3, 1, 3}, // 0xFF 0xE0 0xFE
     *      Bank4 - {5, 4, 1, 4, 1, 4}, // 0xFF 0xE7 0xFE
     *      Bank5 - {0, 0, 0, 0, 0, 0}  // 0x7F
     */

    // time_val is an array of 4-bit values (little-endian)
    int time_val[6][4];
    time(time_val); // hh:mm:ss

    int c; // col
    for (c = 0; c < 6; c++)
    {
        // 2-bit (col 0)
        if (c == 0)
        {
            // Upper Banks
            if (time_val[c][2])
            {
                realtime[0][c] = 0xFE;
                realtime[1][c] = 0xFF;
                realtime[2][c] = 0x7F;
            }
            // Lower Banks
            if (time_val[c][3])
            {
                realtime[3][c] = 0xFE;
                realtime[4][c] = 0xFF;
                realtime[5][c] = 0x7F;
            }
        }
        // 3-bit (col 2 & 4)
        if (c % 2 == 0 && c > 0)
        {
            // Upper banks
            if (time_val[c][1])
            {
                realtime[0][c] = 0xFE;
                realtime[1][c] = 0x7F;
            }
            // Middle Banks
            if (time_val[c][2])
            {
                realtime[2][c] = 0xFE;
                realtime[3][c] = 0x7F;
            }
            // Lower Banks
            if (time_val[c][3])
            {
                realtime[4][c] = 0xFE;
                realtime[5][c] = 0x7F;
            }
        }
        // 4-bit (col 1 & 3)
        if (c % 2 == 1)
        {
            // Upper banks
            if (time_val[c][0] && !time_val[c][1])
            {
                realtime[0][c] = 0xFE;
                realtime[1][c] = 0x07;
            }
            else if (!time_val[c][0] && time_val[c][1])
            {
                realtime[1][c] = 0xE0;
                realtime[2][c] = 0x7F;
            }
            else if (time_val[c][0] && time_val[c][1])
            {
                realtime[0][c] = 0xFE;
                realtime[1][c] = 0xE7;
                realtime[2][c] = 0x7F;
            }
            // Lower banks
            if (time_val[c][2] && !time_val[c][3])
            {
                realtime[3][c] = 0xFE;
                realtime[4][c] = 0x07;
            }
            else if (!time_val[c][2] && time_val[c][3])
            {
                realtime[4][c] = 0xE0;
                realtime[5][c] = 0x7F;
            }
            else if (time_val[c][2] && time_val[c][3])
            {
                realtime[3][c] = 0xFE;
                realtime[4][c] = 0xE7;
                realtime[5][c] = 0x7F;
            }
        }
    }

    return;
}

// displays a digit part
void GLCD_display(void)
{
    // Initialize the fill values
    char realtime[6][6] = { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

    // Take the column time values and convert them to their fill byte values
    convert_time(realtime);

    int r; // row
    int c; // col
    for (r = 0; r < 6; r++)
    {
        for (c = 0; c < 6; c++)
            GLCD_writePart(realtime[r][c]); // Write part to screen
    }
    return;
}

// write a digit part to the screen
void GLCD_writePart(char fill)
{
    // Fourteen columns per part

    // All parts start with a blank column
    GLCD_data_write(0x00);

    // Twelve columns of the fill value
    int i;
    for (i = 0; i < 12; i++)
        GLCD_data_write(fill);

    // All parts end with a blank column
    GLCD_data_write(0x00);

    return;
}

/*************************************************************************
 * The code below was taken from the scaffolding code from Lab 11.
 * Author: Brother Allred
 *************************************************************************/

// moves the cursor
void GLCD_setCursor(unsigned char x, unsigned char y)
{
    GLCD_command_write(0x80 | x); // column
    GLCD_command_write(0x40 | y); // bank (8 rows per bank)
}

// clears the GLCD by writing zeroes to the entire screen
void GLCD_clear(void)
{
    int i;
    for (i = 0; i < (GLCD_WIDTH * GLCD_LENGTH / 8); i++)
        GLCD_data_write(0x00);
    GLCD_setCursor(0, 0); // return to the home position
}

void GLCD_init(void)
{
    // Initialize the SPI communication protocol
    SPI_init();

    // Configure control lines
    P6->DIR |= (CE | RESET | DC);   // P6.0, P6.6, P6.7 set as output
    P6->OUT |= CE;                  // CE idle high
    P6->OUT &= ~RESET;              // assert reset
    P6->OUT |= RESET;               // de-assert reset

    // Send control signals
    GLCD_command_write(0x21);       // set extended command mode
    GLCD_command_write(0xB8);       // set LCD Vop for contrast
    GLCD_command_write(0x04);       // set temp coefficient
    GLCD_command_write(0x14);       // set LCD bias mode 1:48
    GLCD_command_write(0x20);       // set normal command mode
    GLCD_command_write(0x0C);       // set display normal mode
}

void GLCD_data_write(unsigned char data)
{
    P6->OUT |= DC;                 // Select data mode
    SPI_write(data);                // send the data via SPI
}

void GLCD_command_write(unsigned char data)
{
    P6->OUT &= ~DC;                 // Select command mode
    SPI_write(data);                // send the data via SPI
}

void SPI_init(void)
{
    EUSCI_B0->CTLW0 = 0x0001;    // put UCB0 module in reset mode
    EUSCI_B0->CTLW0 = 0x69C1;    // MSB first, Master, SPI, SMCLK
    EUSCI_B0->BRW = 3;    // 3 MHz / 3 = 1 million baud
    EUSCI_B0->CTLW0 &= ~0x0001;    // enable UCB0 after configuration

    P1->SEL0 |= BIT5 | BIT6;      // P1.5 and P1.6 for UCB0
    P1->SEL1 &= ~(BIT5 | BIT6);
}

void SPI_write(unsigned char data)
{
    P6->OUT &= ~CE;                 // assert CE
    EUSCI_B0->TXBUF = data;         // write data to transmission buffer
    while (EUSCI_B0->STATW & BIT0)
        ;  // wait until transmission is complete
    P6->OUT |= CE;                  // de-assert CE
}

#endif /* DISPLAY_H_ */
