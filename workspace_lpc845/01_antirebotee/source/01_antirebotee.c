#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

#define LED 2
#define BOTON 4

int main(void) {
	// Inicializacion
    BOARD_InitBootClocks();

    // Habilito el clock del GPIO 1
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };

    gpio_pin_config_t in_config = { kGPIO_DigitalInput };


    GPIO_PortInit(GPIO, 0);
    GPIO_PinInit(GPIO, 0, BOTON, &in_config);
    GPIO_PortInit(GPIO, 1);
    GPIO_PinInit(GPIO, 1, LED, &out_config);


    while(1) {
    	if(!GPIO_PinRead(GPIO, 0, BOTON)) {

    		GPIO_PinWrite(GPIO, 1, LED, 0);
    	}
    	else {
    		// Apago el LED
    		GPIO_PinWrite(GPIO, 1, LED, 1);
    	}
    	for(uint32_t i = 0; i < 300000; i++);
    }
    return 0;
}
