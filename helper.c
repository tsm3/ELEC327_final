/*
 * helper.c
 *
 *  Created on: May 10, 2021
 *      Author: vipzs
 */
#include "main.h"

void gen_init() {
    _enable_interrupts();
    wdt_init();
    uart_init();
    temp_init();

    DCOCTL = 0;                 // Select lowest DCOx and MODx settings -> 16MHz
    BCSCTL1 = CALBC1_16MHZ;     // Set range
    DCOCTL = CALDCO_16MHZ;      // Set DCO step + modulation */
    BCSCTL3 |= LFXT1S_2;        // ACLK = VLO
    BCSCTL2 |= DIVS_0;          // This makes SMCLK run at 16 MHz!!

}

void temp_init() {
    P1DIR &= ~TEMPPIN; // Set this to be 0 for INPUT
}

float ADC_to_temp(float adc_val) {
    return ((adc_val * 2.5)/(1023*.00355) - 277.75);
}

void wdt_init() {
    BCSCTL3 |= LFXT1S_2;     // ACLK = VLO ->
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    WDTCTL = WDT_ADLY_1000;    // WDT 1000ms (~43.3ms since clk 12khz), ACLK, interval timer
    IE1 |= WDTIE;            // Enable WDT interrupt
}



void init_buttons() {
    P2DIR &= ~(BIT0 + BIT1 + BIT2); // set to input
    P2REN = BIT0 + BIT1 + BIT2; // enable pullup/down resistors
    P2OUT = BIT0 + BIT1 + BIT2; // set resistors to pull up
    P2IES = BIT0 + BIT1 + BIT2; // listen for high to low transitions
    P2IFG &=  ~(BIT0 + BIT1 + BIT2); // clear any pending interrupts
    P2IE = BIT0 + BIT1 + BIT2; // enable interrupts for these pins
}


