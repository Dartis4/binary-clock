/*
 * timer.h
 *
 *  Created on: Mar 29, 2022
 *
 *  Taken from Chapter 7 of Programmable Microcontrollers:
 *  Applications on the MSP432 LaunchPad, 1st Edition
 *  See Listing 7.7
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "msp.h"

#define TIMER_PERIOD 3000000

void TIMER_32_init(void){
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_MODE | TIMER32_CONTROL_PRESCALE_1;
    TIMER32_1->LOAD = TIMER_PERIOD;

    while (PCM->CTL0 & PCM_CTL1_PMR_BUSY);
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while (PCM->CTL1 & PCM_CTL1_PMR_BUSY);

    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;

    PJ->SEL0 |= BIT2 | BIT3;
    PJ->SEL1 &= ~(BIT2 | BIT3);

    CS->KEY = CS_KEY_VAL;
    CS->CTL2 |= CS_CTL2_HFXT_EN | CS_CTL2_HFXTFREQ_6;
    while (CS->IFG & CS_IFG_HFXTIFG)
        CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;
    CS->CTL1 &= ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK);
    CS->CTL1 |= CS_CTL1_SELM_5;
    CS->KEY = 0;

    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_IE;

    __enable_irq();
    NVIC->ISER[0] = 1 << ((T32_INT1_IRQn) & 31);
    NVIC->IP[25] = 1; // Set Priority


    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;

    __sleep();
}

#endif /* TIMER_H_ */
