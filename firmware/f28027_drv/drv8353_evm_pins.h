/*
 * drv8353_evm_pins.h
 *
 *  Created on: 10 Apr 2022
 *      Author: Knalle
 */

#ifndef DRV8353_EVM_PINS_H_
#define DRV8353_EVM_PINS_H_


#define LED0    GPIO0
#define LED1    GPIO1
#define LED2    GPIO2
#define LED3    GPIO3

#define BUTTON  GPIO12

#define INHA_EPWM1A     GPIO0
#define INLA_EPWM1B     GPIO1

#define INHB_EPWM2A     GPIO2
#define INLB_EPWM2B     GPIO3

#define INHC_EPWM3A     GPIO4
#define INLC_EPWM3B     GPIO5

#define NFAULT_ADCINA2  AIO2            // Sampled by ad. When low a fault event has occured. Should have been an external interruot pin...





#endif /* DRV8353_EVM_PINS_H_ */
