/*
 * Final Project: Binary Clock
 *
 * File: Main
 * Desc: Main program driver, calls functions from other files to handle parts
 *
 * Use the PCD8544 display to show the clock. Two columns for hours, two columns for minutes,
 * two columns for seconds to display each in binary.
 */

#include "msp.h"
#include "binary_time.h"
#include "display.h"
#include "timer.h"
#include "keypad.h"
#include "port.h"

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    GLCD_init();        // Initialize the display
    GLCD_clear();       // Reset the display memory
    keypad_init();      // Initialize the keypad
    set_output(1, 0);   // Setup LED1
    TIMER_32_init();    // Initialize the timer
}

/***
 * Timer interrupt at 1-second interval to update display
 *
 * See timer.h for code citation
 */
void T32_INT1_IRQHandler(void)
{
    TIMER32_1->INTCLR = 0;  // Clear the flag
    GLCD_display();         // Display everything
    if (set_enable == 0){
        if (P1->OUT & 1)
            reset(1,0);
        addSec();           // Add to the time
    }
    else
        toggle_output(1, 0);
}

/***
 * IRQ handler for Port 3 (Keypad)
 ***/
void PORT3_IRQHandler(void)
{
    uint8_t key = 0;

    // if DA interrupt received
    if (P3->IFG & DA)
    {
        // Clear interrupt flag for DA
        P3->IFG &= ~DA;

        // Read data
        key = keypad_decode();  // determine which key was pressed

        // Setup Mode
        if (set_enable)
        {
            /************************************************************************************************
             * Setup Modes
             *  (*) -> Indicates the default
             *
             *      "*" - Toggle Setup Mode
             *
             *      IN SETUP MODE:
             *          "D" - Switch between Add and Assign Modes
             *          "#" - Reset time
             *
             *          ASSIGN MODE:                                                                        (*)
             *              Switch between assigning the Ones and Tens(*) place
             *              "A" - of Hour                                                                   (*)
             *              "B" - of Minute                                                                 ( )
             *              "C" - of Second                                                                 ( )
             *
             *          ADD MODE:                                                                           ( )
             *              Add one (1) to the time category
             *              "A" - Hour                                                                      ( )
             *              "B" - Minute                                                                    ( )
             *              "C" - Second                                                                    ( )
             *
             ************************************************************************************************/

            // Change modes or choose
            switch (key)
            {
            /* Add Mode */
            case 0xA:
                // Hour             "A"
                if (!set_mode)
                    addHour();      // Add hour
                else if (set_mode == 1)
                    set_mode = 4;   // Ones place
                else
                    set_mode = 1;   // Tens place
                break;
            case 0xB:
                // Minute           "B"
                if (!set_mode)
                    addMin();       // Add minute
                else if (set_mode == 2)
                    set_mode = 5;   // Ones place
                else
                    set_mode = 2;   // Tens placej
                break;
            case 0xC:
                // Second           "C"
                if (!set_mode)
                    addSec();       // Add second
                else if (set_mode == 3)
                    set_mode = 6;   // Ones place
                else
                    set_mode = 3;   // Tens place
                break;
            case 0xD:
                // Enter Add Mode   "D"
                if (set_mode)
                    set_mode = 0;
                // Enter Assign Mode
                else
                    set_mode = 1;
                break;
            case 0xE:
                // Leave setup mode "*"
                set_enable = 0;
                break;
            case 0xF:
                // Reset Clock      "#"
                reset_time();
                break;
            default:
                /* Assign Mode */
                switch (set_mode)
                {
                case 1:
                    setHour(1, key);     // Value => Hour Tens Place
                    break;
                case 2:
                    setMinute(1, key);   // Value => Min Tens Place
                    break;
                case 3:
                    setSecond(1, key);   // Value => Sec Tens Place
                    break;
                case 4:
                    setHour(0, key);     // Value => Hour Ones Place
                    break;
                case 5:
                    setMinute(0, key);   // Value => Min Ones Place
                    break;
                case 6:
                    setSecond(0, key);   // Value => Sec Ones Place
                    break;
                default:
                    break;
                }
            }
        }
        // Normal Mode
        else
        {
            // Enter setup mode
            if (key == 0xE)
            {
                // Enable setup "*"
                set_enable = 1;
                set_mode = 1;
            }
        }
    }
}
