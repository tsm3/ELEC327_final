/*
 * helper.h
 *
 *  Created on: May 10, 2021
 *      Author: vipzs
 */

#ifndef ELEC327_FINAL_HELPER_H_
#define ELEC327_FINAL_HELPER_H_


void wdt_init();
void gen_init();

void init_buttons();
void temp_init();

float ADC_to_temp(float adc_val);

#endif /* ELEC327_FINAL_HELPER_H_ */
