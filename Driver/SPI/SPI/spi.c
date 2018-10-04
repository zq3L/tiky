/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-24 15:11:32
Version		:1.0.0
*/
#include "spi.h"

#ifdef HARDWARE_SPI
#include "./HardwareSPI/spi.c"
#endif

#ifdef SOFTWARE_SPI
#include "./SoftwareSPI/spi.c"
#endif
