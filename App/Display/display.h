/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-20 13:43:38
Version		:1.0.0
*/
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "stm32f10x.h"
#include "font.h"

#ifdef __cplusplus
extern C{
#endif

u8 displayString(u16 x,u16 y,const char* str,FontIndex font,u16 bgColor,u16 fontColor);
void displayTest(void);


#ifdef __cplusplus
}
#endif
#endif
