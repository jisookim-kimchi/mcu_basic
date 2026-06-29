#ifndef STM32F407XX_DMA_DRIVER_H
#define STM32F407XX_DMA_DRIVER_H

#include "stm32f407xx.h"

#define DMA_CHANNEL0 0
#define DMA_CHANNEL1 1
#define DMA_CHANNEL2 2
#define DMA_CHANNEL3 3
#define DMA_CHANNEL4 4
#define DMA_CHANNEL5 5
#define DMA_CHANNEL6 6
#define DMA_CHANNEL7 7

/*
    DMA Transfer Direction
*/
#define DMA_PERIPHERAL_TO_MEMORY 0
#define DMA_MEMORY_TO_PERIPHERAL 1
#define DMA_MEMORY_TO_MEMORY     2

// DMA_FIFO Mode
#define DMA_FIFO_ENABLE 1
#define DMA_FIFO_DISABLE 0

// DMA_DataWidth
#define DMA_DATA_8BIT  0
#define DMA_DATA_16BIT 1
#define DMA_DATA_32BIT 2

//DMA_AddressIncrement (MINC / PINC)
#define DMA_ADDR_INC_DISABLE    0
#define DMA_ADDR_INC_ENABLE     1

// DMA_Priority
#define DMA_PRIORITY_LOW     0
#define DMA_PRIORITY_MEDIUM  1
#define DMA_PRIORITY_HIGH    2
#define DMA_PRIORITY_VERY_HIGH 3

// DMA STREAM EN or DI
#define DMA_ENABLE  1
#define DMA_DISABLE 0

/*
    DMA Memory brust transfer config
    - These bits are protected and can be written only if EN is ‘0’
    - In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'.
*/
#define DMA_MBURST_SINGLE   0
#define DMA_MBURST_INCR4    1
#define DMA_MBURST_INCR8    2
#define DMA_MBURST_INCR16   3

/*
    DMA Pheripheral burst transfer config
    - These bits are protected and can be written only if EN is ‘0’
    - In direct mode, these bits are forced to 0x0 by hardware.
*/
#define DMA_PBURST_SINGLE   0
#define DMA_PBURST_INCR4    1
#define DMA_PBURST_INCR8    2
#define DMA_PBURST_INCR16   3

/*
	DMA FIFO level
*/
#define DMA_FIFO_THRES_1_4      0
#define DMA_FIFO_THRES_2_4      1
#define DMA_FIFO_THRES_3_4      2
#define DMA_FIFO_THRES_FULL     3

/*
    Macro get stream number
*/
#define GET_DMA_STREAM_NUM(pDMAx, pDMAStreamx) (uint8_t)((pDMAStreamx - (pDMAx->stream)))

typedef enum
{
    DMA_STATE_IDLE,
    DMA_STATE_BUSY,
    DMA_STATE_DONE,
    DMA_STATE_ERROR
} DMA_State_t;

typedef struct
{
    uint32_t TransferDir;
    uint32_t PeriphInc;
    uint32_t MemInc;
    uint32_t PeriDataSize;
    uint32_t MemDataSize;
    uint32_t Priority;
    uint32_t FIFOMode;
    uint32_t FIFOThreshold;
    uint32_t MemBurst;
    uint32_t PerBurst;
}DMA_Config_t;

typedef struct
{
  DMA_Reg_t *pDMAx;
  DMA_Stream_Reg_t *pDMAStreamx;
  uint8_t channel;
  //uint8_t stream_num; considering...
  uintptr_t peripheral;
  uintptr_t mem;
  uint32_t length;
  DMA_Config_t config;
  volatile DMA_State_t state;
} DMA_Handle_t;

void DMA_PeriClockControl(DMA_Reg_t *pDMAx, uint8_t EnOrDi);
void DMA_Init(DMA_Handle_t *pDMAHandler);
void DMA_DeInit(DMA_Stream_Reg_t *pDMAx);
#endif
