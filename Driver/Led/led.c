/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 16:51:05
Version		:1.0.0
*/
#include "led.h"
#include "stm32f10x.h"

typedef struct
{
    LedIndex index  :7 ;
    u8 state        :1 ;
    GPIO_TypeDef* port ;
    u16 pin ;
}Led; 


static Led leds[] = 
{
    {ledIndex0,0,GPIOA,GPIO_Pin_15},
};

static Led* getLedByIndex(LedIndex index)
{
    u8 i = 0 ;
    for(i=0;i<ledSum;i++)
    {
        if(index == leds[i].index)
        {
            return leds+i ;
        }
    }

    return (Led*)0;
}

void ledInit(void)
{
    u8 i = 0 ;
    GPIO_InitTypeDef GPIO_InitStruct ;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    for(i=0;i<ledSum;i++)
    {
        leds[i].state = 0 ;
        GPIO_ResetBits(leds[i].port, leds[i].pin);
    }
    
}


u8 ledSet(LedIndex index, LedOption option)
{
    Led* obj = getLedByIndex(index);
    u8 state = 0 ;
    if(obj)
    {
        switch(option)
        {
            case ledOptionOff:
            {
                if(obj->state == 0)
                {
                    return 0;
                }else{
                    obj->state = 0 ;
                    state = 0 ;
                }
                break ;
            }
            case ledOptionOn:
            {
                if(obj->state)
                {
                    return 0 ;
                }else{
                    obj->state = 1 ;
                    state = 1 ;
                }
                break ;
            }
            case ledOptionReverse:
            {
                if(obj->state)
                {
                    obj->state = 0;
                    state = 0 ;
                }else{
                    obj->state = 1 ;
                    state = 1 ;
                }
                break; 
            }

        }

        (state>0)?GPIO_SetBits(obj->port, obj->pin):GPIO_ResetBits(obj->port, obj->pin);
        
        return 0 ;
    }else{
        return 1 ;
    }   
}

u8 ledGetState(LedIndex index)
{
    Led* obj = getLedByIndex(index);
    if(obj)
    {
        return obj->state ;
    }
    return 0 ;
}


