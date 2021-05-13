#include "main.h"


/**
 * main.c
 */

static unsigned int FirstADCVal;            // holds 1st ADC result

float temporary = 0;
float temperature = 0;
volatile int ADCon = 0;
volatile int des_temp = 25;// Celcus
volatile uint8_t on = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	ADC10CTL1 = ADC10DIV_3 + INCH_10 + CONSEQ_0;  // TA trig., rpt, A10
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REF2_5V + ADC10IE + REFON + ADC10ON;
    _delay_cycles(300);                       // Wait for reference to settle
    ADC10CTL0 |= ENC + ADC10SC;
    while (!(ADC10IFG & ADC10CTL0));          // First conversion?
    FirstADCVal = ADC10MEM;                   // Read out 1st ADC value
    P1OUT = 0x00;                             // Clear P1 // FET OFF
    P1DIR |= BIT0 + BIT3;                             // P1.0 as output // BIT0 -> LED :: BIT3 -> FET OUT
    init_buttons();
    ADC10CTL0 &= ~ENC; // Turns off ADC
    wdt_init();

    while (1) {
        ADC10CTL0 &= ~ENC; // Turns off ADC

        if (on) {
            P1OUT |= (BIT0 + BIT3); // LED and heat on
            ADC10CTL0 |= ENC + ADC10SC;
            ADCon = 1;
            while (ADCon) {
                __bis_SR_register(LPM0_bits + GIE);
            }
            temporary = ADC10MEM;
            ADC10CTL0 &= ~ENC; // Turns off ADC
            temperature = ADC_to_temp(temporary);

            if ((temperature*.95 > des_temp)) {
                on = 0;
            }
        } else {
            P1OUT &= ~(BIT0 + BIT3); // LED and heat off
        }
        __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
	    }


	return 0;
}




// Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{

    __bic_SR_register_on_exit(LPM0_bits); // exit LPM3 when returning to program (clear LPM3 bits)
}

// ADC10 ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
    ADCon = 0;
    __bic_SR_register_on_exit(LPM0_bits);       // Enter LPM0 w/ interrupt
}

// Button (Port 2) interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void button(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) button (void)
#else
#error Compiler not supported!
#endif
{
    //2.0 -> ON/OFF
    //2.1 -> Lower des_temp
    //2.2 -> higher des_temp

    if (P2IFG & BIT0) {
        on ^= 0x01;
    } else if ((P2IFG & BIT1)) {
        if (des_temp > 0) {
            des_temp--;
        }
    } else if ((P2IFG & BIT2)) {
        if (des_temp < 100) {
            des_temp++;
        }
    }

    P2IFG &= ~(BIT0 + BIT1 + BIT2); // Clear any pending interrupts

    __bic_SR_register_on_exit(LPM0_bits); // exit LPM0 when returning to program (clear LPM3 bits)
}
