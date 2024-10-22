#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

#define BOTON 4
#define SegF 13
#define SegD 14
#define SegA 11
#define SegDP 1
#define SegR 10
#define SegE 0
#define SegC 6
#define A1 8
#define A2 9

int main(void) {

    BOARD_InitBootClocks();

    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };

    gpio_pin_config_t in_config = { kGPIO_DigitalInput};


    GPIO_PortInit(GPIO, 0);
    GPIO_PinInit(GPIO, 0, BOTON, &in_config);
    GPIO_PinInit(GPIO, 0, SegA, &out_config);
    GPIO_PinInit(GPIO, 0, SegR, &out_config);
    GPIO_PinInit(GPIO, 0, SegE, &out_config);
    GPIO_PinInit(GPIO, 0, SegC, &out_config);
    GPIO_PinInit(GPIO, 0, SegF, &out_config);
    GPIO_PinInit(GPIO, 0, SegD, &out_config);
    GPIO_PinInit(GPIO, 0, SegDP, &out_config);
    GPIO_PinInit(GPIO, 0, A1, &out_config);
    GPIO_PinInit(GPIO, 0, A2, &out_config);

    while(1) {
    	if(!GPIO_PinRead(GPIO, 0, BOTON)) {

    		GPIO_PinWrite(GPIO, 0, A2, 0);
    		GPIO_PinWrite(GPIO, 0, A1, 0);
    		GPIO_PinWrite(GPIO, 0, SegC, 0);
        	for(uint32_t i = 0; i < 300000; i++);

    		GPIO_PinWrite(GPIO, 0, SegDP, 1);
    		GPIO_PinWrite(GPIO, 0, SegDP, 0);
        	for(uint32_t i = 0; i < 300000; i++);

    		GPIO_PinWrite(GPIO, 0, SegE, 1);
    		GPIO_PinWrite(GPIO, 0, SegE, 0);
        	for(uint32_t i = 0; i < 300000; i++);

        	GPIO_PinWrite(GPIO, 0, SegD, 1);
    		GPIO_PinWrite(GPIO, 0, SegD, 0);
        	for(uint32_t i = 0; i < 300000; i++);

        	GPIO_PinWrite(GPIO, 0, SegF, 1);
    		GPIO_PinWrite(GPIO, 0, SegF, 0);
        	for(uint32_t i = 0; i < 300000; i++);


        	GPIO_PinWrite(GPIO, 0, SegA, 1);
    		GPIO_PinWrite(GPIO, 0, SegA, 0);
        	for(uint32_t i = 0; i < 300000; i++);

        	GPIO_PinWrite(GPIO, 0, SegR, 1);
    		GPIO_PinWrite(GPIO, 0, SegR, 0);
        	for(uint32_t i = 0; i < 300000; i++);




    	}
    	else {
    		GPIO_PinWrite(GPIO, 0, SegC, 1);
    		GPIO_PinWrite(GPIO, 0, SegDP, 1);
    		GPIO_PinWrite(GPIO, 0, SegE, 1);
    		GPIO_PinWrite(GPIO, 0, SegD, 1);
    		GPIO_PinWrite(GPIO, 0, SegF, 1);
    		GPIO_PinWrite(GPIO, 0, SegA, 1);
    		GPIO_PinWrite(GPIO, 0, SegR, 1);
    		GPIO_PinWrite(GPIO, 0, A1, 1);
    		GPIO_PinWrite(GPIO, 0, A2, 1);

    	}
    }
    return 0;
}
