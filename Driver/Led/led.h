/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 16:51:05
Version		:1.0.0
*/
#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x.h"

typedef enum
{
    ledIndex0 = 0,
    ledSum,
}LedIndex ;

typedef enum
{
    ledOptionOff = 0 ,
    ledOptionOn,
    ledOptionReverse,
}LedOption ;

#ifdef __cplusplus
extern C{
#endif

void ledInit(void);
u8 ledSet(LedIndex index,LedOption option);
u8 ledGetState(LedIndex index);


#ifdef __cplusplus
}
#endif
#endif
