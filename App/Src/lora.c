#include "lora.h"
#include "bsp_gpio.h"



extern UART_HandleTypeDef huart2;
void loraSendData(uint8_t *buf,uint8_t len)
{
    HAL_UART_Transmit(&huart2,buf,len,1000);
}
void loraInit(void)
{
    LORA_MO_L;
    LORA_M1_L;
    
    LORA_PWR_EN;
    
    
}

