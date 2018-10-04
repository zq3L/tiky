/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 15:54:25
Version		:1.0.0
*/
#include "bsp.h"

static void rccInit(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE) ;
}

static void debugInit(void)
{
    /*
    两个都是可以的
    */
    //*(u32*)(AFIO_BASE+0x04) = 0x04000000 ;    
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}

void bspInit(void)
{
    //SystemInit() ;
    rccInit() ;
    debugInit() ;
}

