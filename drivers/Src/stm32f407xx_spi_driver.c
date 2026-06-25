
#include "stm32f407xx_spi_driver.h"

/*
    @Brief: Enable or disable the peripheral clock for a given SPI peripheral
    @Param: SPI Register Base Address pointer
    @Param: Enable or Disable
*/
void SPI_PeriClockControl(SPI_Reg_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(pSPIx == SPI1)
        {
            SPI1_CLOCK_ENABLE();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_CLOCK_ENABLE();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_CLOCK_ENABLE();
        }
    }
    else
    {
        if(pSPIx == SPI1)
        {
            SPI1_CLOCK_DISABLE();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_CLOCK_DISABLE();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_CLOCK_DISABLE();
        }
    }
}

/*
    @Brief: Initialize the SPI peripheral
    @Param: SPI Handle pointer
*/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    
}