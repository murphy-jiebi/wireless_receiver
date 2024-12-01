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
#include "lora.h"
#include "bsp_tim.h"
#include "task_ctrl.h"
#include "24cxx.h" 
#include "task_com.h"

uint8_t groupSN=1;
uint8_t devSN=1;

#define DEBUG
uint8_t test=0;
uint8_t test_buf[15]={0};
uint8_t test_data=0x11;

uint8_t chgstate=0;
uint8_t state1=0;



uint8_t INT250ms=0;
uint32_t preTb1s=0;
uint8_t channelFireflag[6]={0};
uint8_t channelStatus[6]={0};
uint8_t fireChannel[6]={0};
uint8_t flagFire=0;
uint8_t cnt1min=0;
float bat=0.0f;
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    bsp_InitGpio();
    AT24CXX_Init();
    bsp_InitParam();
    LedInit();
    bsp_InitAdc();
    bsp_usartInit();
    LoraInit();
    Bsp_tim4_Init();
    bat=GetBatVol();
    BatVoltRefreash(bat/4.20f*100);
    while (1)
    {
        if(preTb1s!=TimerGet1s())
        {
            preTb1s=TimerGet1s();
            cnt1min++;
        }
        BatLedHandle();
        ChannelDetect();
        LedRefresh(channelStatus);
        ChannelFire(TimerGet1ms(),&flagFire,fireChannel);
        TaskCom();
        
        #ifdef DEBUG
        switch(test)
        {
            case 1:
                memset(test_buf,test_data,15);
                loraSendData(test_buf,15);
                break;
            case 2:
                memset(test_buf,test_data,15);
                AT24CXX_Write(10,test_buf,15);
                break;
            case 3:
                memset(test_buf,0,15);
                AT24CXX_Read(10,test_buf,15);
                break;
            case 4:
                CHG_CTL_EN;
                break;
            case 5:
                CHG_CTL_DIS;
                break;
            default:
                break;
        }
        chgstate=READ_CHG_INT;
        state1=READ_PWR_INT;
        test=0;
        #endif
    }
}

void BatLedHandle(void)
{
    static uint8_t a=0;
    static uint8_t step=0;
    if(READ_PWR_INT)
    {
        if(INT250ms)
        {
            INT250ms=0;
            if(READ_CHG_INT)
            {
                if(cnt1min>60)
                {
                    cnt1min=0;
                    CHG_CTL_DIS;
                    delay_ms(5);
                    bat=GetBatVol();
                    CHG_CTL_EN;
                }
                if(step%2)
                {
                    BatVoltRefreash(bat/4.20f*100);
                }else{
                    BatVoltRefreash(0);
                }
                step++;
            }else{
                BatVoltRefreash(100);
            }
        }     
    }else{
        a=1;
        if(cnt1min>60)
        {
            cnt1min=0;
            bat=GetBatVol();
            BatVoltRefreash(bat/4.20f*100);
        }
    }
    
}


