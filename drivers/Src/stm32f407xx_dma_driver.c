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
DMA_MapStatus_t DMA_reqMapInit(DMA_Handle_t *pDMAHandler, DMA_Request_t req)
{
    if (pDMAHandler == NULL) return DMA_MAP_INVALID_COMBINATION;
    if (req >= DMA_REQ_TABLE_MAX) return DMA_MAP_INVALID_COMBINATION;
    

    
}


/*
    DMA Initialization
    @param1 : DMA Handle pointer
    @note: The caller must set DMA_Config_t before calling this
*/
void DMA_Init(DMA_Handle_t *pDMAHandler)
{
    uint32_t timeout = 100000;
    DMA_Stream_Reg_t *stream = &pDMAHandler->pDMAx->stream[pDMAHandler->streamNum];
    stream->CR &= ~(1 << 0);
    while(stream->CR & (1 << 0))
    {
        if(--timeout == 0)
            break;
            //return DMA_TIMEOUT_ERROR;
    }
    const DMA_FlagMap_t *fmap = &dma_flag_map[pDMAHandler->streamNum];
    uint32_t clear_mask = (0x3D << fmap->offset);
    if (fmap->is_high == 0)
    {
        pDMAHandler->pDMAx->LIFCR = clear_mask;
    }
    else
    {
        pDMAHandler->pDMAx->HIFCR = clear_mask;
    }
    
    // Config CR reg
    // Channel select
    uint32_t temp = 0;
    temp |= pDMAHandler->channel;
    temp |= DMA_PERIPHERAL_TO_MEMORY;
    temp |= DMA_MINC_ENABLE;
    temp |= DMA_MEM_DATASIZE_8BIT;
    temp |= DMA_PERI_DATASIZE_8BIT;
    temp |= DMA_PRIORITY_LOW;
    temp |= DMA_CIRC_ENABLE;
    stream->CR = temp;
    
}

void DMA_DeInit(DMA_Stream_Reg_t *pDCMAx)
{

}
