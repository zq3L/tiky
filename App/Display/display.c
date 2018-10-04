/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-20 13:43:38
Version		:1.0.0
*/
#include "display.h"
#include "ili9325.h"
#include "font.h"
#include "string.h"


u8 displayString(u16 x,u16 y,const char* str,FontIndex font,u16 bgColor,u16 fontColor)
{
    u8 i ,j , z ;
    u8 *charBufferTmp = 0 ;
    u8 strLength = strlen(str);
    const Font* usingFont = fontGetObj(font) ;
    ILI9325_CS_L() ;
    for(i=0;i<strLength;i++)
    {
        ili9325SetCursor(x+i*usingFont->width, y);
        ili9325SetWindows(x+i*usingFont->width, x+(i+1)*usingFont->width-1, y, x+usingFont->hight-1);
        ili9325StartWriteDram();
        
        charBufferTmp = usingFont->data+(*(str+i)-usingFont->startPerson)*usingFont->hight ;
        for(j=0;j<usingFont->hight;j++)
        {
            for(z=0;z<8;z++)
            {
                if((*(charBufferTmp+j)>>z)&0x01)
                {
                    ili9325WriteIo(0xffff) ;
                }else{
                    ili9325WriteIo(0x0000) ;
                }
            }
        }
    }
    ILI9325_CS_H() ;  
    return 0 ;
}

void displayTest(void)
{
    //u8 tmpBuffer[] = {0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00} ;
    u8 tmpBuffer[] = {0xaa,0x00,0x00,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0x00,0x00,0xaa} ;
    //u8 tmpBuffer[] = {0xaa,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa} ;
    u8 i ,j;
    
    ILI9325_CS_L() ;
    ili9325SetCursor(0, 0);
    ili9325SetWindows(0, 7, 0,15);
    ili9325StartWriteDram();
    
    for(i=0;i<16;i++)
    {
        for(j=0;j<8;j++)
        {
            if((*(tmpBuffer+i)>>j)&0x01)
            {
                ili9325WriteIo(0xffff) ;
            }else{
                ili9325WriteIo(0x0000) ;
            }
        }
    }
    ILI9325_CS_H() ;  
}


