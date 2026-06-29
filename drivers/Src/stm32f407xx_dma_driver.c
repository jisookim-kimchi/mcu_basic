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
    DMA Initialization
    @param1 : DMA Handle pointer
    @note: The caller must set DMA_Config_t before calling this
*/
void DMA_Init(DMA_Handle_t *pDMAHandler)
{
    pDMAHandler->pDMAStreamx->CR &= ~(1 << 0);
    while(pDMAHandler->pDMAStreamx->CR & (1 << 0))
    {
        ;
    }
    //previos flags clear
    uint8_t stream_num = GET_DMA_STREAM_NUM(pDMAHandler->pDMAx, pDMAHandler->pDMAStreamx);
    uint8_t bit_shift[] = {0, 6, 16, 22};
    uint8_t shift_amount = bit_shift[stream_num % 4];
    if (stream_num < 4)
    {
        pDMAHandler->pDMAx->LIFCR = (0x3D << shift_amount);
    }
    else
    {
        pDMAHandler->pDMAx->HIFCR = (0x3D << shift_amount);
    }

    // Config CR reg
    //PAR reg,,MEM addr,,NDTR
    // FIFO or Direct? 
    
}

void DMA_DeInit(DMA_Stream_Reg_t *pDCMAx)
{

}
