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
	float acc_x;

	// Inicializo hardware
	bsp_init();

	while (1) {
		acc_x = bsp_get_acc('x') * 10.0;
		if (acc_x >= 0) {
			led_setBright(1, (int) acc_x);
			led_setBright(0, 0);
		} else {
			led_setBright(0, (int) acc_x);
			led_setBright(1, 0);
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
