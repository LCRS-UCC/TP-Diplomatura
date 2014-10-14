#include "stm32f4xx.h"			// Header del micro
#include "stm32f4xx_gpio.h"		// Perifericos de E/S
#include "stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
/* Simple funcion de delay */
void Delay(__IO uint32_t nCount);

/* Inicializa los puertos E/S */
void ES_Init();

// Definiciones de hardware
#define LED_V GPIO_Pin_12
#define LED_N GPIO_Pin_13
#define LED_R GPIO_Pin_14
#define LED_A GPIO_Pin_15

#define BOTON GPIO_Pin_0

/* Puertos de los leds disponibles */
GPIO_TypeDef* leds_port[] = { GPIOD, GPIOD, GPIOD, GPIOD };
/* Leds disponibles */
const uint16_t leds[] = { LED_V, LED_N, LED_R, LED_A };

// Funcion para prender leds por indice
void pulsoLed(uint8_t led, uint32_t tiempo);

// Leer el estado del switch
uint8_t sw_getState(void);

int main(void) {
	uint8_t i = 0;
	uint32_t delay = 0;

	// configuro Clock del periferico GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// configuro GPIO
	ES_Init();

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

void ES_Init() {
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

void pulsoLed(uint8_t led, uint32_t tiempo) {
	GPIO_SetBits(leds_port[led], leds[led]);
	Delay(tiempo);
	GPIO_ResetBits(leds_port[led], leds[led]);
}

uint8_t sw_getState(void) {
	return GPIO_ReadInputDataBit(GPIOA, BOTON);
}

void Delay(__IO uint32_t nCount) {
	while (nCount--) {
	}
}
