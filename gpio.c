#include "gpio.h"


void gpio_select(void) {

    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.LED0 = 0;   // Disable pullup on GPIO0
    GpioCtrlRegs.GPAPUD.bit.LED1 = 0;   // Disable pullup on GPIO1
    GpioCtrlRegs.GPAPUD.bit.LED2 = 0;   // Disable pullup on GPIO2
    GpioCtrlRegs.GPAPUD.bit.LED3 = 0;   // Disable pullup on GPIO3

    GpioCtrlRegs.GPAMUX1.bit.LED0 = 0;  // GPIO0 = GPIO0
    GpioCtrlRegs.GPAMUX1.bit.LED1 = 0;  // GPIO1 = GPIO1
    GpioCtrlRegs.GPAMUX1.bit.LED2 = 0;  // GPIO2 = GPIO2
    GpioCtrlRegs.GPAMUX1.bit.LED3 = 0;  // GPIO3 = GPIO3

    GpioCtrlRegs.GPADIR.bit.LED0 = 1;   // GPIO0 = output
    GpioCtrlRegs.GPADIR.bit.LED1 = 1;   // GPIO1 = output
    GpioCtrlRegs.GPADIR.bit.LED2 = 1;   // GPIO2 = output
    GpioCtrlRegs.GPADIR.bit.LED3 = 1;   // LED3 = output

    GpioDataRegs.GPACLEAR.bit.LED0    = 1;
    GpioDataRegs.GPACLEAR.bit.LED1    = 1;
    GpioDataRegs.GPACLEAR.bit.LED2    = 1;
    GpioDataRegs.GPACLEAR.bit.LED3    = 1;
    EDIS;

}

void gpio_example(void) {

    GpioDataRegs.GPACLEAR.bit.LED0  = 1;
    GpioDataRegs.GPACLEAR.bit.LED1  = 1;
    GpioDataRegs.GPACLEAR.bit.LED2  = 1;
    GpioDataRegs.GPACLEAR.bit.LED3  = 1;

    DELAY_US(1000000);

    GpioDataRegs.GPASET.bit.LED0    = 1;
    GpioDataRegs.GPASET.bit.LED1    = 1;
    GpioDataRegs.GPASET.bit.LED2    = 1;
    GpioDataRegs.GPASET.bit.LED3    = 1;

    DELAY_US(1000000);
}


void led_rider() {

    static enum dir dir = left;

    static uint16_t led_pos = 1;

    GpioDataRegs.GPADAT.bit.LED0  = ~(led_pos & 1);

    DELAY_US(MIN_DELAY);

    GpioDataRegs.GPADAT.bit.LED1  = ~((led_pos & 2) >> 1);

    DELAY_US(MIN_DELAY);

    GpioDataRegs.GPADAT.bit.LED2  = ~((led_pos & 4) >> 2);

    DELAY_US(MIN_DELAY);

    GpioDataRegs.GPADAT.bit.LED3  = ~((led_pos & 8) >> 3);

    DELAY_US(MIN_DELAY);

    if (dir == left) {
        led_pos = (led_pos << 1);
        if (led_pos == 8) dir = right;
    } else {
        led_pos = (led_pos >> 1);
        if (led_pos == 1) dir = left;
    }

}
