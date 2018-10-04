/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 15:42:40
Version		:1.0.0
*/
#include "main.h"


int main(void)
{
    bspInit();
    driverInit();
    ledSet(ledIndex0, ledOptionOn);
    displayString(0, 0, "What A Nice Day!(^_^)", FontIndexSongTi, 0x0000, 0x0000);
    while(1)
    {
        displayString(0, 0, "What A Nice Day!(^_^)", FontIndexSongTi, 0x0000, 0x0000);
    }
}

