/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sys.h"
#include "delay.h"
#include "bsp_usart.h"
#include "bsp_gpio.h"
#include "bsp_adc.h"
#include "bsp_led.h"


uint8_t ledStatus[6]={0};


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    delay_ms(1000);
    bsp_InitGpio();
    LedInit();
    bsp_InitAdc();
    
    while (1)
    {
        LedRefresh(ledStatus);
    }
}




