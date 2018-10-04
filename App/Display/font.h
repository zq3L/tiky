/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-20 19:33:39
Version		:1.0.0
*/
#ifndef _FONT_H_
#define _FONT_H_

#include "stm32f10x.h"

#define USE_FONT_SONG_TI_16

typedef struct
{
    u8 hight ;
    u8 width ;
    u8 startPerson ;
    u8* data ;
}Font ;

typedef enum
{
    fontIndexNULL = 0 ,
#ifdef USE_FONT_SONG_TI_16
    FontIndexSongTi ,
#endif
}FontIndex;

#ifdef __cplusplus
extern C{
#endif

const Font* fontGetObj(FontIndex indexOfFont);


#ifdef __cplusplus
}
#endif
#endif
