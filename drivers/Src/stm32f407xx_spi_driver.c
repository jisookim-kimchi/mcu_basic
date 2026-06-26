
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
    @Note : The caller must configure the SPI_Config members before calling this function.
*/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    uint32_t temp = 0;
    temp |= (pSPIHandle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR);
    temp |= (pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR);
    temp |= (pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF);
    temp |= (pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL);
    temp |= (pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA);
    temp |= (pSPIHandle->SPI_Config.SPI_SSM << SPI_CR1_SSM);
    if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        temp &= ~(1 << SPI_CR1_BIDIMODE);
    }
    else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        temp |= (1 << SPI_CR1_BIDIMODE);
    }
    else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX)
    {
        temp &= ~(1 << SPI_CR1_BIDIMODE);
        temp |= (1 << SPI_CR1_RXONLY);
    }
    pSPIHandle->pSPIx->CR1 = temp; 
}