
#include "stm32f407xx_spi_driver.h"

/*
    @Brief: Enable or disable the peripheral clock for a given SPI peripheral
    @Param 1: SPI Register Base Address pointer
    @Param 2: Enable or Disable
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
    @Note : The caller must set SPI_Config_t before calling this
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
        temp &= ~(1 << SPI_CR1_BIDIMODE); // Full-duplex
    }
    else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        temp |= (1 << SPI_CR1_BIDIMODE); // Half-duplex
    }
    else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX)
    {
        temp &= ~(1 << SPI_CR1_BIDIMODE);
        temp |= (1 << SPI_CR1_RXONLY);
    }
    pSPIHandle->pSPIx->CR1 = temp; 
}

/*
    @Brief: De-initialize the SPI peripheral
    @Param: SPI Register Base Address pointer
*/
void SPI_DeInit(SPI_Reg_t *pSPIx)
{
    if (pSPIx == SPI1)
    {
        SPI1_REG_RESET();
    }
    else if (pSPIx == SPI2)
    {
        SPI2_REG_RESET();
    }
    else if (pSPIx == SPI3)
    {
        SPI3_REG_RESET();
    }
}

/*
    @Brief: Send Data(Blocking)
    @Param 1: SPI Handle pointer
    @Param 2: Tx Buffer Pointer
    @Param 3: Length
*/
void SPI_SendData(SPI_Reg_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while (Len > 0)
    {
        // Wait until TXE is set
        while (!(pSPIx->SR & (1 << SPI_SR_TXE)));
        if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            pSPIx->DR = *((uint16_t*)pTxBuffer);
            Len -= 2;
            pTxBuffer += 2;
        }
        else
        {
            pSPIx->DR = *pTxBuffer;
            Len--;
            pTxBuffer++;
        }
    }
}

/*
    @Brief: Receive Data(Blocking)
    @Param 1: SPI Handle pointer
    @Param 2: Rx Buffer Pointer
    @Param 3: Length
*/
void SPI_ReceiveData(SPI_Reg_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    while (Len > 0)
    {
        while (!(pSPIx->SR) & (1 << SPI_SR_RXNE));
        if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            *((uint16_t*)pRxBuffer) = pSPIx->DR;
            Len -= 2;
            pRxBuffer += 2;
        }
        else
        {
            *pRxBuffer = pSPIx->DR;
            Len--;
            pRxBuffer++;
        }
    }
}


/*
    @Brief: Enable or Disable IRQ Number
    @Param 1: IRQ Number
    @Param 2: Enable or Disable
*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{

}

/*
    @Brief: Set Priority of IRQ Number
    @Param 1: IRQ Number
    @Param 2: IRQ Priority
*/
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    
}

/*
    @Brief: Handle SPI Interrupt
    @Param 1: SPI Handle pointer
*/
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
    
}

/*
    @Brief: Enable or Disable SPI Peripheral
    @Param 1: SPI Register Base Address pointer
    @Param 2: Enable or Disable
*/
void SPI_PeripheralControl(SPI_Reg_t *pSPIx, uint8_t EnOrDi)
{
    
}

/*
    @Brief: Software Internal Slave Select Management
    @Param 1: SPI Register Base Address pointer
    @Param 2: Enable or Disable
*/
void SPI_SSIConfig(SPI_Reg_t *pSPIx, uint8_t EnOrDi)
{
    
}

/*
    @Brief: Slave Select Output Enable
    @Param 1: SPI Register Base Address pointer
    @Param 2: Enable or Disable
*/
void SPI_SSOEConfig(SPI_Reg_t *pSPIx, uint8_t EnOrDi)
{
    
}
