#ifndef __MYIIC_H
#define __MYIIC_H 

#include "main.h" 	
#include "delay.h"

//#define soft_iic
#define		EE_IIC
#define I2C_PORT                GPIOB

#define I2C_SCL_PIN 			GPIO_PIN_6
#define I2C_SCL_PORT 		    GPIOB

#define I2C_SDA_PIN 			GPIO_PIN_7
#define I2C_SDA_PORT 		    GPIOB

#define I2C_SCL_H			 	(I2C_SCL_PORT->BSRR = I2C_SCL_PIN)
#define I2C_SCL_L	            (I2C_SCL_PORT->BRR = I2C_SCL_PIN)

#define I2C_SDA_H				(I2C_SDA_PORT->BSRR = I2C_SDA_PIN)
#define I2C_SDA_L				(I2C_SDA_PORT->BRR = I2C_SDA_PIN)

#define READ_I2C_SDA   			((I2C_SDA_PORT->IDR & I2C_SDA_PIN) != 0)	/* 读SDA口线状态 */

#define EE_SDA_HIGH()		    I2C_SDA_H
#define	EE_SDA_LOW()		    I2C_SDA_L
#define	EE_SCL_HIGH()		    I2C_SCL_H
#define	EE_SCL_LOW()		    I2C_SCL_L
#define	EE_SDA_READ()		    READ_I2C_SDA

//I2C所有操作函数
void I2C_Init(void);                //初始化I2C的IO口				 
void I2C_Start(void);				//发送I2C开始信号
void I2C_Stop(void);	  			//发送I2C停止信号
void I2C_Send_Byte(u8 txd);			//I2C发送一个字节
u8 I2C_Read_Byte(void);//I2C读取一个字节
u8 I2C_Wait_Ack(void); 				//I2C等待ACK信号
void I2C_Ack(void);					//I2C发送ACK信号
void I2C_NAck(void);				//I2C不发送ACK信号

void I2C_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 I2C_Read_One_Byte(u8 daddr,u8 addr);	 

void EE_delay(void);



#endif
















