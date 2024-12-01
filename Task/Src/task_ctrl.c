#include "task_ctrl.h"
#include "bsp_gpio.h"

#define FIRE_DELAY   50
extern uint8_t channelStatus[6];

void ChannelDetect(void)
{
    if(READ_CH1_CTL || (channelFireflag[0]==1))
    {
        channelStatus[0]=CH_FIRED; 
    }else{
        if(READ_CH1_DET)
        {
            channelStatus[0]=CH_CONNECT; 
        }else{
            channelStatus[0]=CH_NO_CON; 
        }  
    }
    if(READ_CH2_CTL || (channelFireflag[1]==1))
    {
        channelStatus[1]=CH_FIRED; 
    }else{
        if(READ_CH2_DET)
        {
            channelStatus[1]=CH_CONNECT; 
        }else{
            channelStatus[1]=CH_NO_CON; 
        }  
    }
    if(READ_CH3_CTL || (channelFireflag[2]==1))
    {
        channelStatus[2]=CH_FIRED; 
    }else{
        if(READ_CH3_DET)
        {
            channelStatus[2]=CH_CONNECT; 
        }else{
            channelStatus[2]=CH_NO_CON; 
        }  
    }
    if(READ_CH4_CTL || (channelFireflag[3]==1))
    {
        channelStatus[3]=CH_FIRED; 
    }else{
        if(READ_CH4_DET)
        {
            channelStatus[3]=CH_CONNECT; 
        }else{
            channelStatus[3]=CH_NO_CON; 
        }  
    }
    if(READ_CH5_CTL || (channelFireflag[4]==1))
    {
        channelStatus[4]=CH_FIRED; 
    }else{
        if(READ_CH5_DET)
        {
            channelStatus[4]=CH_CONNECT; 
        }else{
            channelStatus[4]=CH_NO_CON; 
        }  
    }
    if(READ_CH6_CTL || (channelFireflag[5]==1))
    {
        channelStatus[5]=CH_FIRED; 
    }else{
        if(READ_CH6_DET)
        {
            channelStatus[5]=CH_CONNECT; 
        }else{
            channelStatus[5]=CH_NO_CON; 
        }  
    }
}

void ChannelFire(uint32_t tb,uint8_t *fire,uint8_t *ch)
{
    static uint32_t cTime=0;
    static uint8_t step=0;
    if(!(*fire))
    {
        return;
    }
    if(tb-cTime<FIRE_DELAY)
    {
        return;
    }
    cTime=tb;
    switch(step)
    {
        case 0:
            step++;
            if(ch[0])
            {
                CH1_CTL_EN;
                channelFireflag[0]=1;
//                channelStatus[0]=CH_FIRED;
                break;
            }
        case 1:
            step++;
            if(ch[1])
            {
                CH2_CTL_EN;
                channelFireflag[1]=1;
//                channelStatus[1]=CH_FIRED;
                break;
            }
            
        case 2:
            step++;
            if(ch[2])
            {
                CH3_CTL_EN;
                channelFireflag[2]=1;
//                channelStatus[2]=CH_FIRED;
                break;
            }

        case 3:
            step++;
            if(ch[3])
            {
                CH4_CTL_EN;
                channelFireflag[3]=1;
//                channelStatus[3]=CH_FIRED;
                break;
            }

        case 4:
            step++;
            if(ch[4])
            {
                CH5_CTL_EN;
                channelFireflag[4]=1;
//                channelStatus[4]=CH_FIRED;
                break;
            }
        case 5:
            step++;
            if(ch[5])
            {
                CH6_CTL_EN;
                channelFireflag[5]=1;
//                channelStatus[5]=CH_FIRED;
                break;
            }
        case 6:
            CH1_CTL_DIS;
            CH2_CTL_DIS;
            CH3_CTL_DIS;
            CH4_CTL_DIS;
            CH5_CTL_DIS;
            CH6_CTL_DIS;
            *fire=0;
            step=0;
            break;
        default:
            break;
    }
}


