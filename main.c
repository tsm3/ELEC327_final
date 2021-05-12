#include "main.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	onewire_t *ow = wire_init();
	gen_init();

	while (1) {

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
    if (!(flag_vec & PETF)) {
        flag_vec |= TIMERF;
    } else {
        flag_vec &= ~PETF;
    }
    __bic_SR_register_on_exit(LPM0_bits); // exit LPM3 when returning to program (clear LPM3 bits)
}
