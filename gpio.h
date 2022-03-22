/*
 * gpio.h
 *
 *  Created on: 18 Oct 2021
 *      Author: Knalle
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "DSP28x_Project.h"

#define LED0    GPIO0
#define LED1    GPIO1
#define LED2    GPIO2
#define LED3    GPIO3

#define DELAY   10
#define MY_DEL  for (i = 0; i<0; i++)    __asm("     NOP");
#define MIN_DELAY   1000


void gpio_select(void);
void gpio_example(void);
void led_rider(void);

enum dir {left = 0, right = 1};





#endif /* GPIO_H_ */
