/*
 * lcdctrl.h
 *
 *  Created on: May 10, 2021
 *      Author: vipzs
 */

#ifndef ELEC327_FINAL_LCDCTRL_H_
#define ELEC327_FINAL_LCDCTRL_H_

void data_read(void );
void data_high(void );
void data_low(void );
void clk_high(void);
void clk_low(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_out(unsigned char d);
void init_LCD(void);
void clear_display(void);
void show( unsigned char *text, int len );



#endif /* ELEC327_FINAL_LCDCTRL_H_ */
