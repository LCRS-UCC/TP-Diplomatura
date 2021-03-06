#ifndef _BSP_H
#define _BSP_H

/**
 * @brief Prende un led
 *
 * @param led Led a prender
 */
void led_on(uint8_t led);

/**
 * @brief Apaga un led
 *
 * @param led Led a apagar
 */
void led_off(uint8_t led);

/**
 * @brief Conmuta un led
 *
 * @param led Led a apagar
 */
void led_toggle(uint8_t led);

/**
 * @brief Delay por software
 */
uint8_t sw_getState();

/**
 * @brief Inicializacion de los servicios de BSP
 */
void bsp_init();

/**
 * @brief Delay de x ms
 */
void bsp_delayMs(uint16_t x);

/**
 * @brief Configura la intencidad del led.
 */
void led_setBright(uint8_t led, float value);

/**
 * @brief Devuelve valor de acc del sensor.
 */
float bsp_get_acc(char eje);

/**
 * @brief Devuelve valor del ADC en porcentaje
 */
float adc_get();

#endif
