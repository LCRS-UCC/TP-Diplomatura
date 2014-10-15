// Definiciones de hardware
#include <stdint.h>
#include "cmsis_boot/stm32f4xx.h"					// Header del micro
#include "cmsis_lib/include/stm32f4xx_gpio.h"		// Perifericos de E/S
#include "cmsis_lib/include/stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
#include "bsp/bsp.h"

#define LED_V GPIO_Pin_12
#define LED_N GPIO_Pin_13
#define LED_R GPIO_Pin_14
#define LED_A GPIO_Pin_15
#define BOTON GPIO_Pin_0

GPIO_TypeDef* const leds_port[4] = { GPIOD, GPIOD, GPIOD, GPIOD };
uint16_t const leds[4] = { LED_A, LED_V, LED_N, LED_R };

void led_on(uint8_t led) {
	GPIO_SetBits(leds_port[led], leds[led]);
}

void led_off(uint8_t led) {
	GPIO_ResetBits(leds_port[led], leds[led]);
}

uint8_t sw_getState() {
	return GPIO_ReadInputDataBit(GPIOA, BOTON);
}
/* Inicializa los puertos E/S */
void bsp_init() {

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	// configuro GPIO
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
			| GPIO_Pin_12;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // (Push/Pull)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

// Arranco el clock del periferico
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
