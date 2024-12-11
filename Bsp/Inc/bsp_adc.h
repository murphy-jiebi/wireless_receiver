#ifndef _BSP_ADC_H
#define _BSP_ADC_H

#include "main.h"

void bsp_InitAdc(void);

float GetBatVol(void);

uint8_t GetBalPct(void);

#endif

