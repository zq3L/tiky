/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 22:36:50
Version		:1.0.0
*/
#ifndef _ILI9325_H_
#define _ILI9325_H_

#include "stm32f10x.h"

#define ILI9325_CS_H()  GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define ILI9325_CS_L()  GPIO_ResetBits(GPIOA,GPIO_Pin_0)

#ifdef __cplusplus
extern C{
#endif

void ili9325Init(void);
void drawLine(u16 xStart,u16 xEnd,u16 yStart,u16 yEnd,u16 color);
void drawDot(u16 x,u16 y,u16 color);
void fillShape(u16 xStart,u16 yStart,u16 xSize,u16 ySize,u16* dataP);

void ili9325WriteIo(u16 data);
void ili9325StartWriteDram(void);
void ili9325SetCursor(u16 x,u16 y);
void ili9325SetWindows(u16 xStart,u16 xEnd,u16 yStart,u16 yEnd);



void ili9325Test(void);

#ifdef __cplusplus
}
#endif
#endif
