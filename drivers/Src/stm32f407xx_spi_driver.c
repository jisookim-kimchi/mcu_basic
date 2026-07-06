
#include "../Inc/stm32f407xx_spi_driver.h"
#include "../Inc/stm32f407xx_nvic_driver.h"

static void SPI_SetState(SPI_Handle_t *pSPIHandler, SPI_State_t state)
{
    if (pSPIHandler)
    {
        pSPIHandler->SPI_State = state;
    }
}

void SPI_TxCompleteCallback(SPI_Handle_t *pSPIHandler)
{
    SPI_SetState(pSPIHandler, SPI_STATE_READY);
}

void SPI_RxCompleteCallback(SPI_Handle_t *pSPIHandler)
{
    SPI_SetState(pSPIHandler, SPI_STATE_READY);
}

void SPI_ErrorCallback(SPI_Handle_t *pSPIHandler)
{
    SPI_SetState(pSPIHandler, SPI_STATE_ERROR);
}

void SPI_TxHalfCompleteCallback(SPI_Handle_t *pSPIHandler)
{
    ;//pingpong buffer
}

void SPI_RxHalfCompleteCallback(SPI_Handle_t *pSPIHandler)
{
    ;//pingpong buffer
}

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
void SPI_Init(SPI_Handle_t *pSPIHandler)
{
    uint32_t temp = 0;
    temp |= (pSPIHandler->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR);
    temp |= (pSPIHandler->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR);
    temp |= (pSPIHandler->SPI_Config.SPI_DFF << SPI_CR1_DFF);
    temp |= (pSPIHandler->SPI_Config.SPI_CPOL << SPI_CR1_CPOL);
    temp |= (pSPIHandler->SPI_Config.SPI_CPHA << SPI_CR1_CPHA);
    temp |= (pSPIHandler->SPI_Config.SPI_SSM << SPI_CR1_SSM);
    if (pSPIHandler->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        temp &= ~(1 << SPI_CR1_BIDIMODE); // Full-duplex
    }
    else if (pSPIHandler->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        temp |= (1 << SPI_CR1_BIDIMODE); // Half-duplex
    }
    else if (pSPIHandler->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX)
    {
        temp &= ~(1 << SPI_CR1_BIDIMODE);
        temp |= (1 << SPI_CR1_RXONLY);
    }
    pSPIHandler->pSPIx->CR1 = temp;
    SPI_SetState(pSPIHandler, SPI_STATE_READY);
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
void SPI_SendData(SPI_Handle_t *pSPIHandler, uint8_t *pTxBuffer, uint32_t Len)
{
    SPI_SetState(pSPIHandler, SPI_STATE_BUSY_TX);
    while (Len > 0)
    {
        // Wait until TXE is set
        while (!(pSPIHandler->pSPIx->SR & (1 << SPI_SR_TXE)));
        if (pSPIHandler->pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            pSPIHandler->pSPIx->DR = *((uint16_t*)pTxBuffer);
            Len -= 2;
            pTxBuffer += 2;
        }
        else
        {
            pSPIHandler->pSPIx->DR = *pTxBuffer;
            Len--;
            pTxBuffer++;
        }
    }
    SPI_SetState(pSPIHandler, SPI_STATE_READY);
}

/*
    @Brief: Receive Data(Blocking)
    @Param 1: SPI Handle pointer
    @Param 2: Rx Buffer Pointer
    @Param 3: Length
*/
void SPI_ReceiveData(SPI_Handle_t *pSPIHandler, uint8_t *pRxBuffer, uint32_t Len)
{
    SPI_SetState(pSPIHandler, SPI_STATE_BUSY_RX);
    while (Len > 0)
    {
        while (!(pSPIHandler->pSPIx->SR) & (1 << SPI_SR_RXNE));
        if (pSPIHandler->pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            *((uint16_t*)pRxBuffer) = pSPIHandler->pSPIx->DR;
            Len -= 2;
            pRxBuffer += 2;
        }
        else
        {
            *pRxBuffer = pSPIHandler->pSPIx->DR;
            Len--;
            pRxBuffer++;
        }
    }
    SPI_SetState(pSPIHandler, SPI_STATE_READY);
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
void SPI_IRQHandling(SPI_Handle_t *pSPIHandler)
{
    //snapshot status register
    uint32_t sr = pSPIHandler->pSPIx->SR;
    
    // Case 1: TXE is set, data is sent
    if (sr & (1 << SPI_SR_TXE) && (pSPIHandler->pSPIx->CR2 & (1 << SPI_CR2_TXEIE)))
    {
        if(pSPIHandler->SPI_Config.SPI_DFF == SPI_DFF_16BIT)
        {
            pSPIHandler->pSPIx->DR = *((uint16_t*)pSPIHandler->pTxBuffer);
            pSPIHandler->TxLen -= 2;
            pSPIHandler->pTxBuffer += 2;
        }
        else if (pSPIHandler->SPI_Config.SPI_DFF == SPI_DFF_8BIT)
        {
            pSPIHandler->pSPIx->DR = *pSPIHandler->pTxBuffer;
            pSPIHandler->TxLen--;
            pSPIHandler->pTxBuffer++;
        }
        if (pSPIHandler->TxLen == 0)
        {
            pSPIHandler->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
            SPI_TxCompleteCallback(pSPIHandler);
        }
    }
    // Case 2: RXNE is set, data is received
    if (sr & (1 << SPI_SR_RXNE) && (pSPIHandler->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE)))
    {
        if(pSPIHandler->SPI_Config.SPI_DFF == SPI_DFF_16BIT)
        {
            *((uint16_t*)pSPIHandler->pRxBuffer) = pSPIHandler->pSPIx->DR;
            pSPIHandler->RxLen -= 2;
            pSPIHandler->pRxBuffer += 2;
        }
        else if (pSPIHandler->SPI_Config.SPI_DFF == SPI_DFF_8BIT)
        {
            *pSPIHandler->pRxBuffer = pSPIHandler->pSPIx->DR;
            pSPIHandler->RxLen--;
            pSPIHandler->pRxBuffer++;
        }
        if (pSPIHandler->RxLen == 0)
        {
            pSPIHandler->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
            SPI_RxCompleteCallback(pSPIHandler);
        }
    }
    //error case...
    if (((sr & (1 << SPI_SR_CRCERR)) && (pSPIHandler->pSPIx->CR2 & (1 << SPI_CR2_ERRIE))))
    {
        //event call
        pSPIHandler->pSPIx->SR &= ~(1 << SPI_SR_CRCERR);
        SPI_ErrorCallback(pSPIHandler);  
    }
    //Master Mode Fault
    //im a Master but, someone call me as Slave
    if (((sr & (1 << SPI_SR_MODF)) && (pSPIHandler->pSPIx->CR2 & (1 << SPI_CR2_ERRIE))))
    {
        //event call
        uint32_t temp = pSPIHandler->pSPIx->CR1;
        pSPIHandler->pSPIx->CR1 = temp;
        SPI_ErrorCallback(pSPIHandler);  
    }
    if (((sr & (1 << SPI_SR_OVR)) && (pSPIHandler->pSPIx->CR2 & (1 << SPI_CR2_ERRIE))))
    {
        //event call
        if (pSPIHandler->SPI_State != SPI_STATE_BUSY_TX)
        {
            uint8_t temp;
            temp = pSPIHandler->pSPIx->DR;
            temp = pSPIHandler->pSPIx->SR;
            (void)temp;
        }
        SPI_ErrorCallback(pSPIHandler); 
    }
    if (((sr & (1 << SPI_SR_FRE)) && (pSPIHandler->pSPIx->CR2 & (1 << SPI_CR2_ERRIE))))
    {
        //event call
        SPI_ErrorCallback(pSPIHandler); 
    }
}

/*
    @Brief: Send Data(Interrupt)
    @Param 1: SPI Handle pointer
    @Param 2: Tx Buffer Pointer
    @Param 3: Length
    @Return: Status
*/
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandler, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandler->SPI_State;
    if (state == SPI_STATE_BUSY_TX)
    {
        return SPI_STATE_BUSY_TX;
    }
    pSPIHandler->pTxBuffer = pTxBuffer;
    pSPIHandler->TxLen = Len;
    SPI_SetState(pSPIHandler, SPI_STATE_BUSY_TX);
    pSPIHandler->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
    return SPI_STATE_READY;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandler, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandler->SPI_State;
    if (state == SPI_STATE_BUSY_RX)
    {
        return SPI_STATE_BUSY_RX;
    }
    pSPIHandler->pRxBuffer = pRxBuffer;
    pSPIHandler->RxLen = Len;
    SPI_SetState(pSPIHandler, SPI_STATE_BUSY_RX);
    pSPIHandler->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
    return SPI_STATE_READY;
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

static void SPI_DMX_TX_Enable(SPI_Reg_t *pSPIx)
{
    pSPIx->CR2 |= (1 << SPI_CR2_TXDMAEN);
}

static void SPI_DMX_RX_Enable(SPI_Reg_t *pSPIx)
{
    pSPIx->CR2 |= (1 << SPI_CR2_RXDMAEN);
}

static void SPI_DMA_TxCallback(DMA_Handle_t *pDMAHandler, DMA_Event_t event)
{
    SPI_Handle_t *pSPIHandler = (SPI_Handle_t*)pDMAHandler->pParent;
    if (!pSPIHandler)
        return;
    switch (event)
    {
        case DMA_EVENT_TC:
            SPI_TxCompleteCallback(pSPIHandler);
            break;
        case DMA_EVENT_HTC:
            SPI_TxHalfCompleteCallback(pSPIHandler);
            break;
        case DMA_EVENT_FE:
        case DMA_EVENT_TE:
            SPI_ErrorCallback(pSPIHandler);
            break;
        default:
            break;
    }
}

static void SPI_DMA_RxCallback(DMA_Handle_t *pDMAHandler, DMA_Event_t event)
{
    SPI_Handle_t *pSPIHandler = (SPI_Handle_t*)pDMAHandler->pParent;
    if (!pSPIHandler)
        return;
    switch (event)
    {
        case DMA_EVENT_TC:
            SPI_RxCompleteCallback(pSPIHandler);
            break;
        case DMA_EVENT_HTC:
            SPI_RxHalfCompleteCallback(pSPIHandler);
            break;
        case DMA_EVENT_FE:
        case DMA_EVENT_TE:
            SPI_ErrorCallback(pSPIHandler);
            break;
        default:
            break;
    }
}

SPI_Status_t SPI_DMA_TX(SPI_Handle_t *pSPIHandler, uint8_t *txBuf, uint32_t len)
{
    if (!pSPIHandler || !txBuf || len == 0)
        return SPI_ERROR;

    if (pSPIHandler->SPI_State != SPI_STATE_READY)
        return SPI_BUSY;

    DMA_Handle_t *dmx = pSPIHandler->pDMA_Tx;

    if (!dmx)
        return SPI_ERROR;

    dmx->mem        = (uintptr_t)txBuf;
    dmx->length     = len;
    dmx->peripheral = (uintptr_t)&pSPIHandler->pSPIx->DR;
    dmx->pParent    = (void*)pSPIHandler;
    DMA_loadCallback(dmx, SPI_DMA_TxCallback);

    SPI_SetState(pSPIHandler, SPI_STATE_BUSY_TX);
    
    if (DMA_Init(dmx) != DMA_OK)
    {
        SPI_SetState(pSPIHandler, SPI_STATE_READY);
        return SPI_ERROR;
    }

    SPI_DMX_TX_Enable(pSPIHandler->pSPIx);

    if (DMA_Start(dmx) != DMA_OK)
    {
        SPI_SetState(pSPIHandler, SPI_STATE_READY);
        return SPI_ERROR;
    }

    return SPI_OK;
}

SPI_Status_t SPI_DMA_RX(SPI_Handle_t *pSPIHandler, uint8_t *pRxBuffer, uint32_t len)
{
    if (!pSPIHandler || !pRxBuffer || len == 0)
        return SPI_ERROR;

    if (pSPIHandler->SPI_State != SPI_STATE_READY)
        return SPI_BUSY;

    DMA_Handle_t *dmx = pSPIHandler->pDMA_Rx;

    if (!dmx)
        return SPI_ERROR;

    dmx->mem        = (uintptr_t)pRxBuffer;
    dmx->length     = len;
    dmx->peripheral = (uintptr_t)&pSPIHandler->pSPIx->DR;
    dmx->pParent    = (void*)pSPIHandler;
    DMA_loadCallback(dmx, SPI_DMA_RxCallback);
    
    SPI_SetState(pSPIHandler, SPI_STATE_BUSY_RX);
    
    if (DMA_Init(dmx) != DMA_OK)
    {
        SPI_SetState(pSPIHandler, SPI_STATE_READY);
        return SPI_ERROR;
    }

    SPI_DMX_RX_Enable(pSPIHandler->pSPIx);

    if (DMA_Start(dmx) != DMA_OK)
    {
        SPI_SetState(pSPIHandler, SPI_STATE_READY);
        return SPI_ERROR;
    }

    return SPI_OK;
}