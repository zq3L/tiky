/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-24 15:11:32
Version		:1.0.0
*/
#include "spi.h"


static spiSoftwareInit(void)
{

}

static spiHardwareInit(void)
{
    
}

void spiInit(void)
{
    SPI_InitTypeDef SPI_InitStruct ;

    SPI_InitStruct.SPI_Mode = SPI_Mode_Master ;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Hard ;
    SPI_InitStruct.SPI_DataSize =SPI_DataSize_8b ; 
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB ; 
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex ; 
    
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge  ;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low ;

    SPI_InitStruct.SPI_BaudRatePrescaler =  ;
    SPI_InitStruct.SPI_CRCPolynomial =  ; 

    SPI_Init(SPI1,&SPI_InitStruct);
}


