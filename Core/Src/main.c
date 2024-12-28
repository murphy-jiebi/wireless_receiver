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

#define DEBUG   0
#if DEBUG
uint8_t test=0;
uint8_t test_buf[15]={0};
uint8_t test_data=0x11;

uint8_t chgstate=0;
uint8_t state1=0;
#endif

uint8_t flagLedblink=0;
uint8_t INT250ms=0;
uint8_t INT500ms=0;
uint32_t preTb1s=0;
uint8_t channelFireflag[6]={0};
uint8_t channelStatus[6]={0};
uint8_t fireChannel[6]={0};
uint8_t flagFire=0;
uint8_t cnt1min=0;
float bat=0.0f;
uint8_t batPct=0;
uint8_t firstCnt1min=0;
uint8_t firstIn=0;
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint8_t i,vol = 0;
    uint8_t ledCnt=0;
	uint8_t chgStatus=1;
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
	  
    while (1)
    {
        if(preTb1s!=TimerGet1s())
        {
            preTb1s=TimerGet1s();
            if(++firstCnt1min<58)
			{
				CHG_CTL_DIS;
                delay_ms(5);
                batPct=GetBalPct();
                CHG_CTL_EN;
			}
            if(++cnt1min>60)
            {
                cnt1min=0;
                CHG_CTL_DIS;
                delay_ms(5);
                batPct=GetBalPct();
                CHG_CTL_EN;
//				chgStatus=READ_CHG_INT;
            }
        }
        if(INT250ms)
        {
            INT250ms=0;
            if(flagLedblink)
            {
                if(ledCnt%2)
                {
                    LED_OFF;
                }else{
                    LED_ON;
                }
                ledCnt++;
                if(ledCnt>4)
                {
					LED_OFF;
                    flagLedblink=0;
                    ledCnt=0;
                }
            }
        } 
        if(INT500ms)
        {
            INT500ms=0;
			if(firstIn<11)
			{
				firstIn++;
				if(firstIn%2)
				{
					LED_OFF;
					BatVoltRefresh(1,0,0,0);
				}else{
					LED_ON;
					BatVoltRefresh(100,0,0,0);
				}
			}else{
				BatVoltRefresh(batPct,READ_PWR_INT,READ_CHG_INT,1);   
			}            
        }
        ChannelDetect();
        LedRefresh(channelStatus);
        ChannelFire(TimerGet1ms(),&flagFire,fireChannel);
        TaskCom();
        
        #if DEBUG
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
                memset(test_buf,test_data,15);
                loraSendData(test_buf,6);
                break;
            case 5:
                
                break;
            default:
                break;
        }
        bat=GetBatVol();
        chgstate=READ_CHG_INT;
        state1=READ_PWR_INT;
        test=0;
        #endif
    }
}

void BatLedHandle(void)
{

        
  
}


