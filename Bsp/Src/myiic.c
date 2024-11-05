#include "myiic.h"
#include "delay.h"


void I2C_Init(void)
{			
  //GPIOB8,B9初始化设置
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = I2C_SCL_PIN|I2C_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_PORT, &GPIO_InitStruct);
  
	I2C_SCL_H;
	I2C_SDA_H;
}
void EE_delay(void)
{
	uint8_t i;
	for (i = 0; i < 50; i++);
}
/**********************************************************************************************************
*	函 数 名: EE_Start
*	功能说明: CPU发起EE总线启动信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Start(void)
{
	/* 当SCL高电平时，SDA出现一个下跳沿表示EE总线启动信号 */
	EE_SDA_HIGH();
	EE_SCL_HIGH();
	EE_delay();
	EE_SDA_LOW();
	EE_delay();
	
	EE_SCL_LOW();
	EE_delay();
}
/*********************************************************************************************************
*	函 数 名: void EE_Stop(void)
*	功能说明: CPU发起EE总线停止信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Stop(void)
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示EE总线停止信号 */
	EE_SDA_LOW();
	EE_SCL_HIGH();
	EE_delay();
	EE_SDA_HIGH();
	EE_delay();
}

/**********************************************************************************************************
*	函 数 名: EE_SendByte
*	功能说明: CPU向EE总线设备发送8bit数据
*	形    参:  _ucByte ： 等待发送的字节
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Send_Byte(uint8_t _ucByte)
{
	uint8_t i;

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			EE_SDA_HIGH();
		}
		else
		{
			EE_SDA_LOW();
		}
		EE_delay();
		EE_SCL_HIGH();
		EE_delay();
		EE_SCL_LOW();
		if (i == 7)
		{
			 EE_SDA_HIGH(); // 释放总线
		}
		_ucByte <<= 1;	/* 左移一个bit */
		EE_delay();
	}
}

/**********************************************************************************************************
*	函 数 名: EE_ReadByte
*	功能说明: CPU从EE总线设备读取8bit数据
*	形    参:  无
*	返 回 值: 读到的数据
**********************************************************************************************************/
uint8_t I2C_Read_Byte(void)
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		EE_SCL_HIGH();
		EE_delay();
		if (EE_SDA_READ())
		{
			value++;
		}
		EE_SCL_LOW();
		EE_delay();
	}
	return value;
}

/**********************************************************************************************************
*	函 数 名: EE_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参:  无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
**********************************************************************************************************/
uint8_t I2C_Wait_Ack(void)
{
	uint8_t re;

	EE_SDA_HIGH();	/* CPU释放SDA总线 */
	EE_delay();
	EE_SCL_HIGH();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	EE_delay();
	if (EE_SDA_READ())	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	EE_SCL_LOW();
	EE_delay();
	return re;
}

/**********************************************************************************************************
*	函 数 名: EE_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Ack(void)
{
	EE_SDA_LOW();	/* CPU驱动SDA = 0 */
	EE_delay();
	
	EE_SCL_HIGH();	/* CPU产生1个时钟 */
	EE_delay();
	EE_SCL_LOW();
	EE_delay();
	EE_SDA_HIGH();	/* CPU释放SDA总线 */
}

/**********************************************************************************************************
*	函 数 名: EE_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_NAck(void)
{
	EE_SDA_HIGH();	/* CPU驱动SDA = 1 */
	EE_delay();
	EE_SCL_HIGH();	/* CPU产生1个时钟 */
	EE_delay();
	EE_SCL_LOW();
	EE_delay();
}

































