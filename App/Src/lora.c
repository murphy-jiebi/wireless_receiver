#include "lora.h"
#include "bsp_gpio.h"


extern UART_HandleTypeDef huart2;

uint8_t loraSendBuf[128]={0};

loraParam_typedef loraParam={0x0000,AIR_SPEED_2400,0x17,COM_MODE_BD,WAKE_TIME_250MS,TX_POWER_30DB};
void loraSendData(uint8_t *buf,uint8_t len)
{
    HAL_UART_Transmit(&huart2,buf,len,1000);
}
void LoraInit(void)
{
    LORA_MO_L;
    LORA_M1_L;
    
    LORA_PWR_EN;
    
}

void LoraReadVerInfo(void)
{
    memset(loraSendBuf,0xC3,3);
    loraSendData(loraSendBuf,3);
}

void LoraReadParam(void)
{
    memset(loraSendBuf,0xC1,3);
    loraSendData(loraSendBuf,3);
}

void LoraWriteParam(loraParam_typedef *para,uint8_t store)
{
    loraSendBuf[0]=store?0xC0:0xC2;
    loraSendBuf[1]=para->addr>>8;
    loraSendBuf[2]=para->addr&0xFF;
    
    
    loraSendData(loraSendBuf,3);
}
