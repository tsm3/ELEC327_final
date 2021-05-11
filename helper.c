/*
 * helper.c
 *
 *  Created on: May 10, 2021
 *      Author: vipzs
 */
#include "main.h"

onewire_t * wire_init() {
    onewire_t *ow;
    ow->port_out    = P1OUT;
    ow->port_in     = P1IN;
    ow->port_ren    = P1REN;
    ow->port_dir    = P1DIR;
    ow->pin         = BIT1;
    return (ow);
}

void uart_setup()
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

