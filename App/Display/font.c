/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-20 19:33:39
Version		:1.0.0
*/
#include "font.h"



#ifdef USE_FONT_SONG_TI_16
#include "songti16.c"
const Font fontSongTi16 = {16,8,' ',(u8*)fontSongTi16Buffer} ;
#endif

const Font* fontGetObj(FontIndex indexOfFont)
{
    switch(indexOfFont)
    {
    
#ifdef USE_FONT_SONG_TI_16
        case FontIndexSongTi:
        {
            return &fontSongTi16 ;
        }
#endif

        default:
        {
            return 0 ;
        }
    }
}

