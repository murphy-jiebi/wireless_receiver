#include "bsp_led.h"
#include "myiic.h"

#define LED_ADDR                0x78

#define REG_SHUTDOWN            0x00
#define REG_DUTY_CH(x)          (x)
#define REG_UPDATE              0x25
#define REG_LED_CTRL(ch)        (ch+0x25)
#define REG_GLOBAL_CTRL         0x4A
#define REG_FRE_SET             0x4B
#define REG_RESET               0x4F

#define DATA_POWER_OFF          0x00
#define DATA_POWER_ON           0x01
#define DATA_PWM_DUTY           0x0F
#define DATA_REG_UPDATE         0x00
#define DATA_CURRENT_DIV1       (0x00 <<1)
#define DATA_CURRENT_DIV2       (0x01 <<1)
#define DATA_CURRENT_DIV3       (0x10 <<1)
#define DATA_CURRENT_DIV4       (0x11 <<1)
#define DATA_LED_OFF            0x00
#define DATA_LED_ON             0x01
#define DATA_FRE_3K             0x00
#define DATA_FRE_22K            0x01


void I2C_Init(void);                //初始化I2C的IO口				 
void I2C_Start(void);				//发送I2C开始信号
void I2C_Stop(void);	  			//发送I2C停止信号
void I2C_Send_Byte(u8 txd);			//I2C发送一个字节
u8 I2C_Read_Byte(void);//I2C读取一个字节
u8 I2C_Wait_Ack(void); 				//I2C等待ACK信号
void I2C_Ack(void);					//I2C发送ACK信号
void I2C_NAck(void);				//I2C不发送ACK信号

uint8_t pwmDuty[36]={0};
uint8_t ledCtrl[36]={0};

void LedWrite(uint8_t reg,uint8_t data)
{
    I2C_Start();
    I2C_Send_Byte(LED_ADDR);
    I2C_Wait_Ack();
    I2C_Send_Byte(reg);
    I2C_Wait_Ack();
    I2C_Send_Byte(data);
    I2C_Wait_Ack();
    I2C_Stop();
}
void LedWriteMulti(uint8_t reg,uint8_t *data,uint8_t len)
{
    uint8_t i;
    I2C_Start();
    I2C_Send_Byte(LED_ADDR);
    I2C_Wait_Ack();
    I2C_Send_Byte(reg);
    I2C_Wait_Ack();
    for(i=0;i<len;i++)
    {
        I2C_Send_Byte(data[i]);
        I2C_Wait_Ack();
    }
    I2C_Stop();
}

void LedPower(uint8_t data)
{
    LedWrite(REG_UPDATE,data);
}
void LedUpdate(void)
{
    LedWrite(REG_UPDATE,0x00);
}

void LedPwmDutySet(uint8_t ch,uint8_t *duty,uint8_t len)
{
    uint8_t i;
    if(ch)
    {
        LedWrite(REG_DUTY_CH(ch),*duty);
    }else{
       LedWriteMulti(REG_DUTY_CH(1),duty,len);
    }
}
void LedSet(uint8_t ch,uint8_t *cmd,uint8_t len)
{
    uint8_t i;
    if(ch)
    {
        LedWrite(REG_LED_CTRL(ch),*cmd);
    }else{
       LedWriteMulti(REG_LED_CTRL(1),cmd,len);
    }
}

void LedInit(void)
{
    I2C_Init();
    
    LedWrite(REG_SHUTDOWN,DATA_POWER_ON);
    LedWrite(REG_FRE_SET,DATA_FRE_3K);
    memset(pwmDuty,DATA_PWM_DUTY,36);
    LedPwmDutySet(0,pwmDuty,36);
    memset(ledCtrl,DATA_CURRENT_DIV1|DATA_LED_OFF,36);
    LedSet(0,ledCtrl,36);
    LedWrite(REG_UPDATE,0x00);
}

uint8_t status_color[5]={LED_NONE,LED_GREEN,LED_BLUE,LED_RED,LED_YELLOW};
void LedRefresh(uint8_t *state)
{
    static uint8_t preState[6]={0xFF,0xFF,0xFF};
    uint8_t buf[18]={0};
    if(memcmp(preState,state,6)!=0)
    {
        for(uint8_t i=0;i<6;i++)
        {
            buf[i*3]=(status_color[state[i]]&LED_BLUE)?1:0;
            buf[i*3+1]=(status_color[state[i]]&LED_GREEN)?1:0;
            buf[i*3+2]=(status_color[state[i]]&LED_RED)?1:0;
        }
        LedSet(0,buf,18);
        LedWrite(REG_UPDATE,0x00);
        memcpy(preState,state,6);
    }
}

