#ifndef __BSP_H
#define __BSP_H

void led_on(uint8_t led);
void led_off(uint8_t led);
uint8_t sw_getState();

void bsp_init();

#endif
