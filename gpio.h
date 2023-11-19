/*
 * gpio.h
 *
 *  Created on: 18 Oct 2021
 *      Author: Knalle
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "DSP28x_Project.h"
#include "drv8353_evm_pins.h"



#define DELAY   10
#define MY_DEL  for (i = 0; i<0; i++)    __asm("     NOP");
#define MIN_DELAY   1

void button_init(void);
void gpio_select(void);
void gpio_gate_drivers(void);
void gpio_example(void);
void led_rider(void);
void ext_int_init(void);

enum dir {left = 0, right = 1};





#endif /* GPIO_H_ */
