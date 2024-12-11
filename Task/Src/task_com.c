#include "task_com.h"
#include "protocol.h"
#include "bsp_usart.h"
#include "24cxx.h" 

void TaskComLora(void)
{
    uint8_t res=0;
    uint8_t txbuf[15]={0};
    if(usart2.usRxFrame)
    {
        usart2.usRxFrame=0;
        res=ProtocolParse(usart2.pRxBuf,usart2.usRxCount);
        if(res)
        {
            res=ProtocolPackage(txbuf,res);
            HAL_UART_Transmit(&huart2,txbuf,res,1000);
        }
        usart2.usRxCount=0;
    }
}
void TaskComDebug(void)
{
    uint8_t txbuf[16]={0x48,0x4C,0x01,};
    uint8_t len=0;
    if(usart1.usRxFrame)
    {
        usart1.usRxFrame=0;
        if((usart1.pRxBuf[0]!=0x48) || (usart1.pRxBuf[1]!=0x4C))
        {
            return;
        }
        if(usart1.pRxBuf[2]!=0x01)
        {
           return; 
        }
        if(usart1.usRxCount<6)
        {
            return;
        }
        switch(usart1.pRxBuf[3])
        {
            case 0x01:
                txbuf[4]=groupSN;
                len=1;
                break;
            case 0x02:
                groupSN=usart1.pRxBuf[4];
                AT24CXX_Write(GROUP_SN_ADDR,&groupSN,1);
                len=0;
                break;
            case 0x03:
                txbuf[4]=devSN;
                len=1;
                break;
            case 0x04:
                devSN=usart1.pRxBuf[4];
                AT24CXX_Write(GROUP_DEV_ADDR,&devSN,1);
                len=0;
                break;
            default:
                break;
            
        }
        txbuf[3]=usart1.pRxBuf[3];
        len+=6;
        txbuf[len-1]=0x0A;
        txbuf[len-2]=0x0D;
        HAL_UART_Transmit(&huart1,txbuf,len,1000);
    }
    
}


void TaskCom(void)
{
    TaskComLora();
    TaskComDebug();
}
