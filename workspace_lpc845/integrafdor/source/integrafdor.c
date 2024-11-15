#include "FreeRTOS"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "fsl_swm.h"
#include "fsl_power.h"
#include "fsl_adc.h"
#include "fsl_sctimer.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "fsl_i2c.h"


volatile uint32_t lux_intensity = 0;
volatile uint32_t setpoint = 50;
volatile uint32_t led_intensity = 0;
volatile uint32_t elapsed_time = 0;

void Task_Luminosity(void *pvParameters);
void Task_Setpoint(void *pvParameters);
void Task_Display(void *pvParameters);
void Task_LEDControl(void *pvParameters);
void Task_Console(void *pvParameters);

int main(void) {
    setupHardware();

    xTaskCreate(Task_Luminosity, "Luminosity", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_Setpoint, "Setpoint", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_Display, "Display", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_LEDControl, "LEDControl", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_Console, "Console", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    for(;;);
}

void setupHardware() {
    BH1750_Init();
    ADC_Init();
    GPIO_Init();
    SEGDisplay_Init();
    Console_Init();
}

// Tarea 1: Medición de Luminosidad
void Task_Luminosity(void *pvParameters) {
    for(;;) {
        uint16_t lux = BH1750_ReadLux(); // Lectura de luminosidad desde BH1750
        lux_intensity = (lux * 100) / 20000; // Conversión a porcentaje
        vTaskDelay(pdMS_TO_TICKS(100)); // Actualización cada 100 ms
    }
}

// Tarea 2: Ajuste de Setpoint
void Task_Setpoint(void *pvParameters) {
    for(;;) {
        if(GPIO_Read(S1) == PRESSED) {
            if(setpoint < 75) setpoint++;
        } else if(GPIO_Read(S2) == PRESSED) {
            if(setpoint > 25) setpoint--;
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Debounce para botones
    }
}

// Tarea 3: Visualización en Display
void Task_Display(void *pvParameters) {
    static uint8_t showLux = 1;
    for(;;) {
        if(GPIO_Read(USER_BUTTON) == PRESSED) {
            showLux = !showLux; // Alternar entre mostrar lux y setpoint
        }
        SEGDisplay_Show(showLux ? lux_intensity : setpoint);
        vTaskDelay(pdMS_TO_TICKS(200)); // Refrescar display
    }
}

// Tarea 4: Control de Intensidad del LED
void Task_LEDControl(void *pvParameters) {
    for(;;) {
        led_intensity = ADC_ReadPercentage(); // Leer porcentaje desde potenciómetro
        GPIO_SetPWM(LED_BLUE, led_intensity);
        vTaskDelay(pdMS_TO_TICKS(100)); // Actualización cada 100 ms
    }
}

// Tarea 5: Envío de Datos a la Consola
void Task_Console(void *pvParameters) {
    for(;;) {
        elapsed_time += 1000; // Aumentar tiempo en ms
        Console_Printf("Tiempo: %d ms, Luminosidad: %d%%, Setpoint: %d%%, LED: %d%%\n",
                       elapsed_time, lux_intensity, setpoint, led_intensity);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Actualización cada segundo
    }
}
