#include "../Inc/stm32f407xx_dma_driver.h"

/*
    DMA Clock Enable Disable
    @param1 : DMA base address
    @param2 :ENABLE or DISABLE
*/
void DMA_PeriClockControl(DMA_Reg_t *pDMAx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (pDMAx == DMA1)
        {
            DMA1_CLOCK_ENABLE();
        }
        else if (pDMAx == DMA2)
        {
            DMA2_CLOCK_ENABLE();
        }
    }
    else
    {
        if (pDMAx == DMA1)
        {
            DMA1_CLOCK_DISABLE();
        }
        else if (pDMAx == DMA2)
        {
            DMA2_CLOCK_DISABLE();
        }
    }
}

/*
    DMA MAP init 
*/
static int32_t DMA_mapRequest(DMA_Handle_t *pDMAHandler, DMA_Request_t req)
{
    if (pDMAHandler == NULL) return -DMA_CONFIG_INVALID_PARAM;
    if (req >= DMA_REQ_TABLE_MAX) return -DMA_CONFIG_INVALID_REQUEST;
    
    const DMA_Map_t *map = &dma_map[req];

    pDMAHandler->streamNum = map->stream;
    pDMAHandler->channel = map->channel;
    pDMAHandler->pDMAx = map->pDMAx;
    
    return DMA_OK;
}

static int32_t DMA_waitDisable(DMA_Handle_t *handler)
{
    uint32_t timeout = 100000;

    DMA_Stream_Reg_t *stream = &handler->pDMAx->stream[handler->streamNum];
    while (stream->CR & (DMA_STREAM_ENABLE_BIT))
    {
        if (--timeout == 0)
            return DMA_TIMEOUT_ERROR;
    }
    return DMA_OK;
}

static int32_t DMA_clearFlags(DMA_Handle_t *handler)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    
    const DMA_FlagMap_t *fmap = &dma_flag_map[handler->streamNum];
    uint32_t mask = (0x3D << fmap->offset);

    if (fmap->is_high == 0)
        handler->pDMAx->LIFCR = mask;
    else
        handler->pDMAx->HIFCR = mask;

    return DMA_OK;
}

static int32_t DMA_CR_dirConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.TransferDir)
    {
        case DMA_DIR_P2M:
            *temp |= DMA_DIR_P2M_BIT;
            break;
        case DMA_DIR_M2P:
            *temp |= DMA_DIR_M2P_BIT;
            break;
        case DMA_DIR_M2M:
            *temp |= DMA_DIR_M2M_BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_MIncConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.MemInc)
    {
        case DMA_MINC_ENABLE:
            *temp |= DMA_MINC_ENABLE_BIT;
            break;
        case DMA_MINC_DISABLE:
            *temp |= DMA_MINC_DISABLE_BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_PIncConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.PeriphInc)
    {
        case DMA_PINC_ENABLE:
            *temp |= DMA_PINC_ENABLE_BIT;
            break;
        case DMA_PINC_DISABLE:
            *temp |= DMA_PINC_DISABLE_BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_PeriDataSizeConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.PeriDataSize)
    {
        case DMA_DATASIZE_8BIT:
            *temp |= DMA_PERI_DATASIZE_8BIT;
            break;
        case DMA_DATASIZE_16BIT:
            *temp |= DMA_PERI_DATASIZE_16BIT;
            break;
        case DMA_DATASIZE_32BIT:
            *temp |= DMA_PERI_DATASIZE_32BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_MemDataSizeConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.MemDataSize)
    {
        case DMA_DATASIZE_8BIT:
            *temp |= DMA_MEM_DATASIZE_8BIT;
            break;
        case DMA_DATASIZE_16BIT:
            *temp |= DMA_MEM_DATASIZE_16BIT;
            break;
        case DMA_DATASIZE_32BIT:
            *temp |= DMA_MEM_DATASIZE_32BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_MemBurstConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.MemBurst)
    {
        case DMA_MBURST_SINGLE:
            *temp |= DMA_MBURST_SINGLE_BIT; 
            break;
        case DMA_MBURST_INCR4:
            *temp |= DMA_MBURST_INCR4_BIT;  
            break;
        case DMA_MBURST_INCR8:
            *temp |= DMA_MBURST_INCR8_BIT;  
            break;
        case DMA_MBURST_INCR16:
            *temp |= DMA_MBURST_INCR16_BIT; 
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_PeriBurstConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.PerBurst)
    {
        case DMA_PBURST_SINGLE:
            *temp |= DMA_PBURST_SINGLE_BIT;
            break;
        case DMA_PBURST_INCR4:
            *temp |= DMA_PBURST_INCR4_BIT;
            break;
        case DMA_PBURST_INCR8:
            *temp |= DMA_PBURST_INCR8_BIT;
            break;
        case DMA_PBURST_INCR16:
            *temp |= DMA_PBURST_INCR16_BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_PriorityConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.Priority)
    {
        case DMA_PRIORITY_LOW:
            *temp |= DMA_PRIORITY_LOW_BIT;
            break;
        case DMA_PRIORITY_MEDIUM:
            *temp |= DMA_PRIORITY_MEDIUM_BIT;
            break;
        case DMA_PRIORITY_HIGH:
            *temp |= DMA_PRIORITY_HIGH_BIT;
            break;
        case DMA_PRIORITY_VERY_HIGH:
            *temp |= DMA_PRIORITY_VERY_HIGH_BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_CircularModeConfig(DMA_Handle_t *handler, uint32_t *temp)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.CircularMode)
    {
        case DMA_CIRC_ENABLE:
            *temp |= DMA_CIRC_ENABLE_BIT;
            break;
        case DMA_CIRC_DISABLE:
            *temp |= DMA_CIRC_DISABLE_BIT;
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}

static int32_t DMA_CR_ModeConfig(DMA_Handle_t *handler, uint32_t *fcr)
{
    if (handler == NULL) return DMA_CONFIG_INVALID_PARAM;
    switch(handler->config.FIFO_Or_DirectMode)
    {
        case DMA_MODE_DIRECT:
            *fcr |= DMA_MODE_DIRECT_BIT;
            break;
        case DMA_MODE_FIFO:
            *fcr |= DMA_MODE_FIFO_BIT;
            switch(handler->config.FIFOThreshold)
            {
                case DMA_FIFO_THRES_1_4:
                    *fcr |= DMA_FIFO_THRES_1_4_BIT;
                    break;
                case DMA_FIFO_THRES_2_4:
                    *fcr |= DMA_FIFO_THRES_2_4_BIT;
                    break;
                case DMA_FIFO_THRES_3_4:
                    *fcr |= DMA_FIFO_THRES_3_4_BIT;
                    break;
                case DMA_FIFO_THRES_FULL:
                    *fcr |= DMA_FIFO_THRES_FULL_BIT;
                    break;
                default:
                    return -DMA_CONFIG_INVALID_PARAM;
            }
            break;
        default:
            return -DMA_CONFIG_INVALID_PARAM;
    }
    return DMA_OK;
}
/*
    DMA Initialization
    @param1 : DMA Handle pointer
    @note: The caller must set DMA_Config_t before calling this
*/
int32_t DMA_Init(DMA_Handle_t *pDMAHandler)
{
    if (pDMAHandler == NULL)
        return DMA_CONFIG_INVALID_PARAM;
    if (DMA_waitDisable(pDMAHandler) != DMA_OK)
        return DMA_NG;
    if (DMA_clearFlags(pDMAHandler) != DMA_OK)
        return DMA_NG;
    uint32_t temp = 0;
    temp |= pDMAHandler->channel;
    if (DMA_CR_dirConfig(pDMAHandler, &temp) != DMA_OK)
        return DMA_NG;
    if (DMA_CR_MIncConfig(pDMAHandler, &temp) != DMA_OK)
        return DMA_NG;
    if (DMA_CR_PIncConfig(pDMAHandler, &temp) != DMA_OK)
        return DMA_NG;
    if (DMA_CR_PeriDataSizeConfig(pDMAHandler, &temp) != DMA_OK)
        return DMA_NG;
    if (DMA_CR_MemDataSizeConfig(pDMAHandler, &temp) != DMA_OK)
        return DMA_NG;
    if (DMA_CR_PriorityConfig(pDMAHandler, &temp) != DMA_OK)
        return DMA_NG;
    if (DMA_CR_CircularModeConfig(pDMAHandler, &temp) != DMA_OK)
        return DMA_NG;
    if (pDMAHandler->config.FIFO_Or_DirectMode == DMA_MODE_FIFO)
    {
        if (DMA_CR_MemBurstConfig(pDMAHandler, &temp) != DMA_OK)
            return DMA_NG;
        if (DMA_CR_PeriBurstConfig(pDMAHandler, &temp) != DMA_OK)
            return DMA_NG;
    }
    DMA_Stream_Reg_t *stream = &pDMAHandler->pDMAx->stream[pDMAHandler->streamNum];
    temp &= ~DMA_STREAM_ENABLE_BIT;
    stream->CR = temp;
    uint32_t fcr = 0;
    if (DMA_CR_ModeConfig(pDMAHandler, &fcr) != DMA_OK)
        return DMA_NG;
    stream->FCR = fcr;
    stream->PAR = pDMAHandler->peripheral;
    stream->M0AR = pDMAHandler->mem;
    stream->NDTR = pDMAHandler->length;
    pDMAHandler->state = DMA_STATE_IDLE;
    return DMA_OK;
}

/*
    @brief : DMA start
    @param1 : DMA Handle pointer
    @note : if hardware is already enabled, start is rejected.
*/
int32_t DMA_Start(DMA_Handle_t *handler)
{
    if (handler == NULL) return DMA_NG;
    if (handler->state == DMA_STATE_BUSY || handler->state == DMA_STATE_ERROR) return DMA_NG;

    if (handler->pDMAx->stream[handler->streamNum].CR & DMA_STREAM_ENABLE_BIT)
        return DMA_NG;

    handler->pDMAx->stream[handler->streamNum].CR |= DMA_STREAM_ENABLE_BIT;
    handler->state = DMA_STATE_BUSY;
    return DMA_OK;
}

/*
    @brief : DMA De Init
    @note : We may use again same Channel, Stream, DMAx after DeInit...
*/
int32_t DMA_DeInit(DMA_Handle_t *handler)
{
    if (handler == NULL || handler->pDMAx == NULL) return DMA_NG;
    handler->state = DMA_STATE_BUSY;
    DMA_Stream_Reg_t *stream = &handler->pDMAx->stream[handler->streamNum];
    stream->CR &= ~DMA_STREAM_ENABLE_BIT;
    if (DMA_waitDisable(handler) != DMA_OK)
        return DMA_NG;
    DMA_clearFlags(handler);
    stream->CR = 0;
    stream->NDTR = 0;
    stream->M0AR = 0;
    stream->M1AR = 0;
    stream->PAR = 0;
    stream->FCR = 0;
    handler->peripheral = 0;
    handler->mem = 0;
    handler->length = 0;
    handler->state = DMA_STATE_RESET;
    handler->pParent = NULL;
    return DMA_OK;
}

/*
    @brief : load Callback functions..
*/
void DMA_loadCallback(DMA_Handle_t *pDMAHandler, DMA_Callback_fn pCallback)
{
    if (pDMAHandler == NULL || pCallback == NULL)
        return;
    pDMAHandler->pCallback = pCallback;
}

void DMA_IRQHandling(DMA_Handle_t *pDMAHandler)
{
    if (pDMAHandler == NULL || pDMAHandler->pDMAx == NULL) return;

    const DMA_FlagMap_t *flagmap = &dma_flag_map[pDMAHandler->streamNum];
    DMA_Stream_Reg_t *stream = &pDMAHandler->pDMAx->stream[pDMAHandler->streamNum];
    uint32_t status = 0;
    if (flagmap->is_high)
        status = (pDMAHandler->pDMAx->HIFCR >> flagmap->offset) & 0x3F;
    else
        status = (pDMAHandler->pDMAx->LIFCR >> flagmap->offset) & 0x3F;

    //TCIF -> TCIE
    if ((status & (1 << 5)) && (stream->CR & (1 << 4)))
    {
        if (flagmap->is_high)
            pDMAHandler->pDMAx->HIFCR = (1 << (5 + flagmap->offset));
        else
            pDMAHandler->pDMAx->LIFCR = (1 << (5 + flagmap->offset));
        if (pDMAHandler->pCallback != NULL)
            pDMAHandler->pCallback(pDMAHandler, DMA_EVENT_TC);
    }
    // HTIF -> HTIE
    if ((status & (1 << 4)) && (stream->CR & (1 << 3)))
    {
        if (flagmap->is_high)
            pDMAHandler->pDMAx->HIFCR = (1 << (4 + flagmap->offset));
        else
            pDMAHandler->pDMAx->LIFCR = (1 << (4 + flagmap->offset));
        if (pDMAHandler->pCallback != NULL)
            pDMAHandler->pCallback(pDMAHandler, DMA_EVENT_HTC);
    }
    // TEIF -> TEIE
    if ((status & (1 << 3)) && (stream->CR & (1 << 2)))
    {
        if (flagmap->is_high)
            pDMAHandler->pDMAx->HIFCR = (1 << (3 + flagmap->offset));
        else
            pDMAHandler->pDMAx->LIFCR = (1 << (3 + flagmap->offset));
        if (pDMAHandler->pCallback != NULL)
            pDMAHandler->pCallback(pDMAHandler, DMA_EVENT_TE);
    }
    // FEIF -> FEIE
    if ((status & (1 << 0)) && (stream->FCR & (1 << 7)))
    {
        if (flagmap->is_high)
            pDMAHandler->pDMAx->HIFCR = (1 << (0 + flagmap->offset));
        else
            pDMAHandler->pDMAx->LIFCR = (1 << (0 + flagmap->offset));
        if (pDMAHandler->pCallback != NULL)
            pDMAHandler->pCallback(pDMAHandler, DMA_EVENT_FE);
    }
}