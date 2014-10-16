#include <stdint.h>
#include "bsp/bsp.h"

/**
 * @brief Se encarga de prender un led y apagarlo luego de un tiempo
 *
 * @param led    Numero de led a pulsar
 * @param tiempo Numero de ciclos del delay entre prendido y apagado
 */
void pulsoLed(uint8_t led, uint32_t tiempo);

/**
 * @brief Aplicacion principal
 */
int main(void) {
	float val;
	uint8_t i;
	// Inicializo hardware
	bsp_init();

	while (1) {
		// Leo el valor del ADC
		val = adc_get();

		// Recorro los 8 leds y prendo/apago los que correspondan
		for (i = 0; i < 8; i++) {
			if (val > (i * 100) / 8) {
				led_off(i + 4);
			} else {
				led_on(i + 4);
			}
		}
	}
}

void pulsoLed(uint8_t led, uint32_t tiempo) {
	led_on(led);
	bsp_delayMs(tiempo);
	led_off(led);
}

void APP_ISR_sw(void) {

}

void APP_ISR_1ms(void) {
	static uint16_t count_1s = 1000;
	count_1s--;
	if (!count_1s) {
		led_toggle(0);
		count_1s = 1000;
	}
}
