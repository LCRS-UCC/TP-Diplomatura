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
	float acc;

	// Inicializo hardware
	bsp_init();

	while (1) {
		// X
		acc = bsp_get_acc('x') * 20.0;
		if (acc >= 0) {
			led_setBright(2, (int) acc);
			led_setBright(3, 0);
		} else {
			acc*= -1;
			led_setBright(3, (int) acc);
			led_setBright(2, 0);
		}
		// Y
		acc = bsp_get_acc('y') * 20.0;
		if (acc >= 0) {
			led_setBright(0, (int) acc);
			led_setBright(1, 0);
		} else {
			acc*= -1;
			led_setBright(1, (int) acc);
			led_setBright(0, 0);
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
