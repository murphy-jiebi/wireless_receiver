#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H

#include "main.h" 	


#define PWR_INT_PORT        GPIOA
#define PWR_INT_PIN         GPIO_PIN_0

#define PWR_CTL_PORT        GPIOC
#define PWR_CTL_PIN         GPIO_PIN_13

#define CHG_INT_PORT        GPIOC
#define CHG_INT_PIN         GPIO_PIN_15

#define CH_PWR_PORT         GPIOB
#define CH_PWR_PIN          GPIO_PIN_5

#define CH1_CTL_PORT        GPIOB
#define CH1_CTL_PIN         GPIO_PIN_11

#define CH2_CTL_PORT        GPIOB
#define CH2_CTL_PIN         GPIO_PIN_1

#define CH3_CTL_PORT        GPIOB
#define CH3_CTL_PIN         GPIO_PIN_0

#define CH4_CTL_PORT        GPIOA
#define CH4_CTL_PIN         GPIO_PIN_7

#define CH5_CTL_PORT        GPIOA
#define CH5_CTL_PIN         GPIO_PIN_6

#define CH6_CTL_PORT        GPIOA
#define CH6_CTL_PIN         GPIO_PIN_5

#define CH1_DET_PORT        GPIOA
#define CH1_DET_PIN         GPIO_PIN_8

#define CH2_DET_PORT        GPIOB
#define CH2_DET_PIN         GPIO_PIN_15

#define CH3_DET_PORT        GPIOB
#define CH3_DET_PIN         GPIO_PIN_14

#define CH4_DET_PORT        GPIOB
#define CH4_DET_PIN         GPIO_PIN_13

#define CH5_DET_PORT        GPIOB
#define CH5_DET_PIN         GPIO_PIN_12

#define CH6_DET_PORT        GPIOB
#define CH6_DET_PIN         GPIO_PIN_10

#define LORA_MO_PORT        GPIOA
#define LORA_MO_PIN         GPIO_PIN_12

#define LORA_M1_PORT        GPIOA
#define LORA_M1_PIN         GPIO_PIN_11

#define LORA_RST_PORT       GPIOA
#define LORA_RST_PIN        GPIO_PIN_15

#define LORA_PWR_PORT       GPIOB
#define LORA_PWR_PIN        GPIO_PIN_3

#define LORA_AUX_PORT       GPIOC
#define LORA_AUX_PIN        GPIO_PIN_14

#define LED_SDB_PORT        GPIOB
#define LED_SDB_PIN         GPIO_PIN_4


#define READ_PWR_INT        ((PWR_INT_PORT->IDR & PWR_INT_PIN) != 0)
#define READ_CHG_INT        ((CHG_INT_PORT->IDR & CHG_INT_PIN) != 0)
#define READ_CH1_DET        ((CH1_DET_PORT->IDR & CH1_DET_PIN) != 0)
#define READ_CH2_DET        ((CH2_DET_PORT->IDR & CH2_DET_PIN) != 0)
#define READ_CH3_DET        ((CH3_DET_PORT->IDR & CH3_DET_PIN) != 0)
#define READ_CH4_DET        ((CH4_DET_PORT->IDR & CH4_DET_PIN) != 0)
#define READ_CH5_DET        ((CH5_DET_PORT->IDR & CH5_DET_PIN) != 0)
#define READ_CH6_DET        ((CH6_DET_PORT->IDR & CH6_DET_PIN) != 0)
#define READ_LORA_AUX       ((LORA_AUX_PORT->IDR & LORA_AUX_PIN) != 0)

#define PWR_CTL_EN          (PWR_CTL_PORT->BSRR = PWR_CTL_PIN)
#define PWR_CTL_DIS         (PWR_CTL_PORT->BRR = PWR_CTL_PIN)

#define CH_PWR_EN           (CH_PWR_PORT->BSRR = CH_PWR_PIN)
#define CH_PWR_DIS          (CH_PWR_PORT->BRR = CH_PWR_PIN)

#define CH1_CTL_EN          (CH1_CTL_PORT->BSRR = CH1_CTL_PIN)
#define CH1_CTL_DIS         (CH1_CTL_PORT->BRR = CH1_CTL_PIN)

#define CH2_CTL_EN          (CH2_CTL_PORT->BSRR = CH2_CTL_PIN)
#define CH2_CTL_DIS         (CH2_CTL_PORT->BRR = CH2_CTL_PIN)

#define CH3_CTL_EN          (CH3_CTL_PORT->BSRR = CH3_CTL_PIN)
#define CH3_CTL_DIS         (CH3_CTL_PORT->BRR = CH3_CTL_PIN)

#define CH4_CTL_EN          (CH4_CTL_PORT->BSRR = CH4_CTL_PIN)
#define CH4_CTL_DIS         (CH4_CTL_PORT->BRR = CH4_CTL_PIN)

#define CH5_CTL_EN          (CH5_CTL_PORT->BSRR = CH5_CTL_PIN)
#define CH5_CTL_DIS         (CH5_CTL_PORT->BRR = CH5_CTL_PIN)

#define CH6_CTL_EN          (CH6_CTL_PORT->BSRR = CH6_CTL_PIN)
#define CH6_CTL_DIS         (CH6_CTL_PORT->BRR = CH6_CTL_PIN)

#define LORA_MO_H           (LORA_MO_PORT->BSRR = LORA_MO_PIN)
#define LORA_MO_L           (LORA_MO_PORT->BRR = LORA_MO_PIN)

#define LORA_M1_H           (LORA_M1_PORT->BSRR = LORA_M1_PIN)
#define LORA_M1_L           (LORA_M1_PORT->BRR = LORA_M1_PIN)

#define LORA_RST_H           (LORA_RST_PORT->BSRR = LORA_RST_PIN)
#define LORA_RST_L           (LORA_RST_PORT->BRR = LORA_RST_PIN)

#define LORA_PWR_EN          (LORA_PWR_PORT->BSRR = LORA_PWR_PIN)
#define LORA_PWR_DIS         (LORA_PWR_PORT->BRR = LORA_PWR_PIN)

#define LED_RST_DIS          (LED_SDB_PORT->BSRR = LED_SDB_PIN)
#define LED_RST_EN           (LED_SDB_PORT->BRR = LED_SDB_PIN)


void bsp_InitGpio(void);

#endif

