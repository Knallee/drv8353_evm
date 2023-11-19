/*
 * spi.c
 *
 *  Created on: 21 Oct 2021
 *      Author: Knalle
 */

#include "spi.h"


void spio_io_disable(){
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0; // Configure GPIO16 as GPIO
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0; // Configure GPIO17 as GPIO
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0; // Configure GPIO18 as GPIO
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0; // Configure GPIO19 as GPIO

    GpioDataRegs.GPACLEAR.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA,  MOSI
    GpioDataRegs.GPACLEAR.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA,  MISO
    GpioDataRegs.GPACLEAR.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA,   SCLK
    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA,   CS
}

void spia_io_init() {

    EALLOW;

 /* Enable internal pull-up for the selected pins */
 // Pull-ups can be enabled or disabled by the user.
 // This will enable the pullups for the specified pins.
 // Comment out other unwanted lines.

     GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
     GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
     GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
     GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

 /* Set qualification for selected pins to asynch only */
 // This will select asynch (no qualification) for the selected pins.
 // Comment out other unwanted lines.

     GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
     GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
     GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
     GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

 /* Configure SPI-A pins using GPIO regs*/
 // This specifies which of the possible GPIO pins will be SPI functional pins.
 // Comment out other unwanted lines.

     GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA,  MOSI
     GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA,  MISO
     GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA,   SCLK
     GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA,   CS

     EDIS;

}

void spia_init() {

    //Step 1. Clear the SPI Software Reset bit (SPISWRESET) to 0 to force the SPI to the reset state.
    //Step 2. Configure the SPI as desired:
        //• Select either master or slave mode (MASTER_SLAVE).
        //• Choose SPICLK polarity and phase (CLKPOLARITY and CLK_PHASE).
        //• Set the desired baud rate (SPIBRR).
        //• Set the SPI character length (SPICHAR).
        //• Clear the SPI Flags (OVERRUN_FLAG, INT_FLAG).
        //• Enable 3-wire mode (TRIWIRE) if needed.
        //• If using FIFO enhancements:
            //– Enable the FIFO enhancements (SPIFFENA).
            //– Clear the FIFO Flags (TXFFINTCLR, RXFFOVFCLR, and RXFFINTCLR).
            //– Release transmit and receive FIFO resets (TXFIFO and RXFIFORESET).
            //– Release SPI FIFO channels from reset (SPIRST).
    //Step 3. If interrupts are used:
        //• In non-FIFO mode, enable the receiver overrun and/or SPI interrupts (OVERRUNINTENA
        //and SPIINTENA).
        //• In FIFO mode, set the transmit and receive interrupt levels (TXFFIL and RXFFIL) then
        //enable the interrupts (TXFFIENA and RXFFIENA).
    //Step 4. Set SPISWRESET to 1 to release the SPI from the reset state.

    SpiaRegs.SPICCR.bit.SPISWRESET      = 0;        // Reset SPI. Should be done when changing the configuration.
    SpiaRegs.SPICTL.bit.MASTER_SLAVE    = 1;        // SPI master
    SpiaRegs.SPIBRR                     = 0x0063;   // SPI Baud Rate = LSPCLK / (SPIBRR + 1), LSPCLK = Low-Speed Peripheral Clock
    SpiaRegs.SPICCR.bit.SPICHAR         = 0xF;      // 16-bit character
    SpiaRegs.SPICCR.bit.CLKPOLARITY     = 0;        // Data is output on rising edge and input on falling edge
    SpiaRegs.SPICTL.bit.CLK_PHASE       = 0;        // Data is output on the rising edge of the SPICLK signal. Input data is latched on the falling edge of the
    SpiaRegs.SPISTS.all                 = 0x0000;   // Clear status register
    SpiaRegs.SPICTL.bit.TALK            = 1;        // Master/Slave transmit enable

    // SpiaRegs.SPICCR.bit.SPILBK       = 1;    // Loop-back enabled

    SpiaRegs.SPICCR.bit.SPISWRESET   = 1;    // SPI out of reset, thus enabled


}

void spia_tx(uint16_t data) {
    SpiaRegs.SPITXBUF = data;
}


uint16_t spia_rx() {
    return SpiaRegs.SPIRXBUF;
}
