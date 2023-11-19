/*
 * spi.h
 *
 *  Created on: 21 Oct 2021
 *      Author: Knalle
 */

#ifndef SPI_H_
#define SPI_H_

#include "DSP28x_Project.h"

void spia_io_init(void);
void spia_int_init(void);
void spia_init(void);
void spio_io_disable(void);
void spia_tx(uint16_t);
uint16_t spia_rx(void);

#endif /* SPI_H_ */
