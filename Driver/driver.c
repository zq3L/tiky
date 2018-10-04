/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 16:44:49
Version		:1.0.0
*/
#include "driver.h"

#include "SysTick.h"
#include "led.h"
#include "ili9325.h"

void driverInit(void)
{
    sysTickInit();
    ledInit();
    ili9325Init();
}


