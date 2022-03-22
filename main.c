//###########################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################



#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#include "gpio.h"
#include "spi.h"

__interrupt void spiTxFifoIsr(void);
__interrupt void spiRxFifoIsr(void);

void delay_loop(void);
void error();

uint16_t tx_data = 0;
uint16_t rx_data = 0;



void main(void) {

// WARNING: Always ensure you call memcpy before running any functions from RAM
// InitSysCtrl includes a call to a RAM based function and without a call to
// memcpy first, the processor will go "into the weeds"
   #ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
   #endif

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks. Turn off the clock for unused peripherals
// This example function is found in the f2802x_SysCtrl.c file.
   InitSysCtrl();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the f2802x_PieCtrl.c file.
   InitPieCtrl();


// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in f2802x_DefaultIsr.c.
// This function is found in f2802x_PieVect.c.
   InitPieVectTable();





    spia_io_init();
    spia_init();
    gpio_select();

    while(1) {

       //gpio_select();
       //spia_tx(tx_data);
       led_rider();
       //gpio_example();
       DELAY_US(100000);
       spia_tx(tx_data);
       //rx_data = spia_rx();
       tx_data++;
    }

}


void error(void)
{
    __asm("     ESTOP0");    //Test failed!! Stop!
    for (;;);
}


//===========================================================================
// No more.
//===========================================================================

