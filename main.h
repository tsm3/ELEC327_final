/*
 * main.h
 *
 *  Created on: May 9, 2021
 *      Author: vipzs
 */

#ifndef ELEC327_FINAL_MAIN_H_
#define ELEC327_FINAL_MAIN_H_

//#include "tempfuncs.h"
#include "lcdctrl.h"
#include "buzzerctrl.h"
#include "helper.h"
#include "onewire.h" // Found it
#include "delay.h"

#include <msp430.h>
#include <stdint.h>

#define TEMPPIN         BIT1
#define MOSFETPIN       BIT2
#define SCLPIN          BIT6
#define SDAPIN          BIT7

#define BUT1PIN         BIT0
#define BUT2PIN         BIT2
#define BUT3PIN         BIT3
#define BUT4PIN         BIT4


#endif /* ELEC327_FINAL_MAIN_H_ */
