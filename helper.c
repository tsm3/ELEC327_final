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

onewire_t * wire_init() {
    onewire_t *ow;
    ow->port_out    = P1OUT;
    ow->port_in     = P1IN;
    ow->port_ren    = P1REN;
    ow->port_dir    = P1DIR;
    ow->pin         = BIT1;
    return (ow);
}

void wdt_init() {
    BCSCTL3 |= LFXT1S_2;     // ACLK = VLO ->
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    WDTCTL = WDT_ADLY_1000;    // WDT 1000ms (~43.3ms since clk 12khz), ACLK, interval timer
    IE1 |= WDTIE;            // Enable WDT interrupt

}

void temp_init() {
    P1DIR &= ~TEMPPIN; // Set this to be 0 for INPUT
}

void uart_init()
{
  P1SEL = BIT1; // If P1SEL and P1SEL2 are 1, pin 1 function is either "UCA0RXD" or "UCA0SOMI", as per page 43 (not sure which)
  P1SEL2 = BIT1; // ^^
  P1DIR &= ~ BIT1;
  UCA0CTL1 |= UCSSEL_2;                     // USCI A set to SMCLK
  UCA0BR0 = 0x41;                            // 8MHz 9600 // this is specifically for USCI_A0 baud rate setting
  UCA0BR1 = 0x03;                              // 8MHz 9600 // this is specifically for USCI_A0 baud rate setting
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // Clear the Reset bit so that it activates
}

