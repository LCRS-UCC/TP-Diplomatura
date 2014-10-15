#include <stdint.h>
#include "bsp/bsp.h"

/* Simple funcion de delay */
void Delay(volatile uint32_t nCount);
void pulsoLed(int n_led, uint32_t delay_t);

int main(void) {
	uint8_t i = 0;
	uint32_t delay = 0;

	// Inicializo la placa
	bsp_init();

	while (1) {
		i++;
		if (i > 3)
			i = 0;

		pulsoLed(i, delay);

		if (sw_getState()) {
			delay += delay / 50 + 10;
		}
	}
}

void pulsoLed(int n_led, uint32_t delay_t) {
	led_on(n_led);
	Delay(delay_t);
	led_off(n_led);
}

void Delay(volatile uint32_t nCount) {
	while (nCount--) {
	}
}
