#include "bsp_gpio.h"


void bsp_InitGpio(void)
{
    //GPIOB8,B9≥ı ºªØ…Ë÷√
	GPIO_InitTypeDef GPIO_InitStruct = {0};	
	__HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    
    
    GPIO_InitStruct.Pin = PWR_CTL_PIN;
	HAL_GPIO_Init(PWR_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH_PWR_PIN;
	HAL_GPIO_Init(CH_PWR_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH1_CTL_PIN;
	HAL_GPIO_Init(CH1_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH2_CTL_PIN;
	HAL_GPIO_Init(CH2_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH3_CTL_PIN;
	HAL_GPIO_Init(CH3_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH4_CTL_PIN;
	HAL_GPIO_Init(CH4_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH5_CTL_PIN;
	HAL_GPIO_Init(CH5_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH6_CTL_PIN;
	HAL_GPIO_Init(CH6_CTL_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LORA_MO_PIN;
	HAL_GPIO_Init(LORA_MO_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LORA_M1_PIN;
	HAL_GPIO_Init(LORA_M1_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LORA_RST_PIN;
	HAL_GPIO_Init(LORA_RST_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LORA_PWR_PIN;
	HAL_GPIO_Init(LORA_PWR_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LED_SDB_PIN;
	HAL_GPIO_Init(LED_SDB_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    
    GPIO_InitStruct.Pin = PWR_INT_PIN;
	HAL_GPIO_Init(PWR_INT_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CHG_INT_PIN;
	HAL_GPIO_Init(CHG_INT_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH1_DET_PIN;
	HAL_GPIO_Init(CH1_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH2_DET_PIN;
	HAL_GPIO_Init(CH2_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH3_DET_PIN;
	HAL_GPIO_Init(CH3_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH4_DET_PIN;
	HAL_GPIO_Init(CH4_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH5_DET_PIN;
	HAL_GPIO_Init(CH5_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = CH6_DET_PIN;
	HAL_GPIO_Init(CH6_DET_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LORA_AUX_PIN;
	HAL_GPIO_Init(LORA_AUX_PORT, &GPIO_InitStruct);
    
    PWR_CTL_EN;
    CH_PWR_EN;
    
    LED_RST_DIS;
    
}

