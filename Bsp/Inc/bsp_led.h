#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "main.h" 	


void LedInit(void);

void LedRefresh(uint8_t *state);

void BatVoltRefresh(uint8_t volt,uint8_t step);

#endif

