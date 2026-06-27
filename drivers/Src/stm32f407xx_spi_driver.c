
#include "stm32f407xx_spi_driver.h"
#include "stm32f407xx_nvic_driver.h"

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
    @Note : Interrupt Based
*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        NVIC_IRQConfig(IRQNumber, ENABLE);   
    }
    else
    {
        NVIC_IRQConfig(IRQNumber, DISABLE);
    }
}

/*
    @Brief: Set Priority of IRQ Number
    @Param 1: IRQ Number
    @Param 2: IRQ Priority
*/
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    NVIC_IRQPriorityConfig(IRQNumber, IRQPriority);
}

/*
    @Brief: Handle SPI Interrupt
    @Param 1: SPI Handle pointer
    @Case 1: if TXE is set, data is sent
    @Case 2: if RXNE is set, data is received
    @Case 3: if ERRIE is set, data is cleared
*/
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
    uint32_t sr = pHandle->pSPIx->SR;
    
    // Case 1: TXE is set, data is sent
    if (sr & (1 << SPI_SR_TXE))
    {
        
    }
    // Case 2: RXNE is set, data is received
    if (sr & (1 << SPI_SR_RXNE))
    {

    }
    //error case...
    if (sr & (1 << SPI_SR_CRCERR))
    {

    }
    if (sr & (1 << SPI_SR_MODF))
    {

    }
    if (sr & (1 << SPI_SR_OVR))
    {

    }
    if (sr & (1 << SPI_SR_UDR))
    {

    }
    if (sr & (1 << SPI_SR_FRL))
    {

    }
    if (sr & (1 << SPI_SR_FRE))
    {

    }
}

/*
    @Brief: Send Data(Interrupt)
    @Param 1: SPI Handle pointer
    @Param 2: Tx Buffer Pointer
    @Param 3: Length
    @Return: Status
*/
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->TxState;
    if (state == SPI_BUSY_IN_TX)
    {
        return SPI_BUSY_IN_TX;
    }
    pSPIHandle->pTxBuffer = pTxBuffer;
    pSPIHandle->TxLen = Len;
    pSPIHandle->TxState = SPI_BUSY_IN_TX;
    pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
    return SPI_READY;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->RxState;
    if (state == SPI_BUSY_IN_RX)
    {
        return SPI_BUSY_IN_RX;
    }
    pSPIHandle->pRxBuffer = pRxBuffer;
    pSPIHandle->RxLen = Len;
    pSPIHandle->RxState = SPI_BUSY_IN_RX;
    pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXEIE);
    return SPI_READY;
}

/*
    @Brief: Enable or Disable SPI Peripheral
    @Param 1: SPI Register Base Address pointer
    @Param 2: Enable or Disable
*/
void SPI_PeripheralControl(SPI_Reg_t *pSPIx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
    }
}

/*
    @Brief: Software Internal Slave Select Management
    @Param 1: SPI Register Base Address pointer
    @Param 2: Enable or Disable
*/
void SPI_SSIConfig(SPI_Reg_t *pSPIx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
    }
}

/*
    @Brief: Slave Select Output Enable
    @Param 1: SPI Register Base Address pointer
    @Param 2: Enable or Disable
    @Note : Only one Slave Select 
*/
void SPI_SSOEConfig(SPI_Reg_t *pSPIx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
    }
    else
    {
        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}
