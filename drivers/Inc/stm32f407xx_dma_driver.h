#ifndef STM32F407XX_DMA_DRIVER_H
#define STM32F407XX_DMA_DRIVER_H

#include "stm32f407xx.h"

// DMA MODE ENABLE
#define DMA_DMDIS_BIT 2

#define DMA_MODE_DIRECT (0 << DMA_DMDIS_BIT)
#define DMA_MODE_FIFO   (1 << DMA_DMDIS_BIT)

/*
	DMA FIFO Threshold selection
*/
#define DMA_FIFO_THRES_1_4   0
#define DMA_FIFO_THRES_2_4   1
#define DMA_FIFO_THRES_3_4   2
#define DMA_FIFO_THRES_FULL  3


// DMA channael select
#define DMA_CHANNEL0 (0 << 25)
#define DMA_CHANNEL1 (1 << 25)
#define DMA_CHANNEL2 (2 << 25)
#define DMA_CHANNEL3 (3 << 25)
#define DMA_CHANNEL4 (4 << 25)
#define DMA_CHANNEL5 (5 << 25)
#define DMA_CHANNEL6 (6 << 25)
#define DMA_CHANNEL7 (7 << 25)

// DMA STREAM EN or DI
#define DMA_STREAM_ENABLE  (1 << 0)
#define DMA_STREAM_DISABLE (0 << 0)

/*
    DMA Memory brust transfer config
    - These bits are protected and can be written only if EN is ‘0’
    - In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'.
*/
#define DMA_MBURST_SINGLE   (0 << 23)
#define DMA_MBURST_INCR4    (1 << 23)
#define DMA_MBURST_INCR8    (2 << 23)
#define DMA_MBURST_INCR16   (3 << 23)

/*
    DMA Pheripheral burst transfer config
    - These bits are protected and can be written only if EN is ‘0’
    - In direct mode, these bits are forced to 0x0 by hardware.
*/
#define DMA_PBURST_SINGLE   (0 << 21)
#define DMA_PBURST_INCR4    (1 << 21)
#define DMA_PBURST_INCR8    (2 << 21)
#define DMA_PBURST_INCR16   (3 << 21)

/*
    DMA timeout
*/
#define DMA_TIMEOUT_ERROR       -1
#define DMA_TIME_IN             100000U

/*
    DMA SxCR CIRC Circular mode
*/
#define DMA_CIRC_ENABLE (1 << 8)
#define DMA_CIRC_DISABLE (0 << 8)

/*
    DMA Transfer Dir
*/
#define DMA_PERIPHERAL_TO_MEMORY (0 << 6)
#define DMA_MEMORY_TO_PERIPHERAL (1 << 6)
#define DMA_MEMORY_TO_MEMORY     (2 << 6)

/*
    DMA Peripheral Increment Mode
*/
#define DMA_MINC_ENABLE (1 << 10)
#define DMA_MINC_DISABLE (0 << 10)

/*
    DMA Memory Increment Mode
*/
#define DMA_PINC_ENABLE (1 << 9)
#define DMA_PINC_DISABLE (0 << 9)

/*
    DMA Priority
*/
#define DMA_PRIORITY_LOW (0 << 16)
#define DMA_PRIORITY_MEDIUM (1 << 16)
#define DMA_PRIORITY_HIGH (2 << 16)
#define DMA_PRIORITY_VERY_HIGH (3 << 16)

/*
    DMA MEM DATASIZE  
*/
#define DMA_MEM_DATASIZE_8BIT  (0 << 13)
#define DMA_MEM_DATASIZE_16BIT (1 << 13)
#define DMA_MEM_DATASIZE_32BIT (2 << 13)

/*
    DMA PERI DATASIZE
*/
#define DMA_PERI_DATASIZE_8BIT  (0 << 11)
#define DMA_PERI_DATASIZE_16BIT (1 << 11)
#define DMA_PERI_DATASIZE_32BIT (2 << 11)


/*
    Macro get stream number
*/
#define GET_DMA_STREAM_NUM(pDMAx, pDMAStreamx) (uint8_t)((pDMAStreamx - (pDMAx->stream)))

typedef enum
{
    DMA_STATE_IDLE,
    DMA_STATE_READY,
    DMA_STATE_BUSY,
    DMA_STATE_DONE,
    DMA_STATE_ERROR
} DMA_State_t;

typedef struct
{
    uint8_t offset;
    uint8_t is_high; // 0:LIFCR, 1: HIFCR
} DMA_FlagMap_t;

static const DMA_FlagMap_t dma_flag_map[8] =
{
    {0, 0},  // Stream0
    {6, 0},  // Stream1
    {16,0},  // Stream2
    {22,0},  // Stream3
    {0, 1},  // Stream4
    {6, 1},  // Stream5
    {16,1},  // Stream6
    {22,1}   // Stream7
};

/*
    DMA REQUEST TABLE
*/
typedef enum
{
    DMA_REQ_SPI1_RX,
    DMA_REQ_SPI1_TX,
    DMA_REQ_USART1_RX,
    DMA_REQ_USART1_TX,
    DMA_REQ_TABLE_MAX
} DMA_Request_t;

typedef enum
{
    DMA_STREAM0,
    DMA_STREAM1,
    DMA_STREAM2,
    DMA_STREAM3,
    DMA_STREAM4,
    DMA_STREAM5,
    DMA_STREAM6,
    DMA_STREAM7
} DMA_StreamNum_t;

typedef enum
{
    DMA_CH0 = 0,
    DMA_CH1,
    DMA_CH2,
    DMA_CH3,
    DMA_CH4,
    DMA_CH5,
    DMA_CH6,
    DMA_CH7
} DMA_Channel_t;

typedef enum
{
    DMA_MAP_OK = 0,
    DMA_MAP_INVALID_STREAM,
    DMA_MAP_INVALID_CHANNEL,
    DMA_MAP_INVALID_COMBINATION,
    DMA_MAP_UNSUPPORTED_MODE
} DMA_MapStatus_t;

typedef struct
{
    DMA_Reg_t *pDMAx;
    DMA_StreamNum_t stream;
    DMA_Channel_t channel;
} DMA_Map_t;

static const DMA_Map_t dma_map[DMA_REQ_TABLE_MAX] =
{
    [DMA_REQ_SPI1_RX] =
    {
        DMA2,
        DMA_STREAM0,
        DMA_CH3
    },

    [DMA_REQ_SPI1_TX] =
    {
        DMA2,
        DMA_STREAM3,
        DMA_CH3
    },

    [DMA_REQ_USART1_RX] =
    {
        DMA2,
        DMA_STREAM5,
        DMA_CH4
    },

    [DMA_REQ_USART1_TX] =
    {
        DMA2,
        DMA_STREAM7,
        DMA_CH4
    },
};

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
  const DMA_Map_t *map;
  DMA_Channel_t channel;
  uint8_t streamNum;
  uintptr_t peripheral; //peirpheral addr.
  uintptr_t mem;        // mem addr.
  uint32_t length;
  DMA_Config_t config;
  volatile DMA_State_t state;
} DMA_Handle_t;

void DMA_PeriClockControl(DMA_Reg_t *pDMAx, uint8_t EnOrDi);
DMA_MapStatus_t DMA_reqMapInit(DMA_Handle_t *pDMAHandler, DMA_Request_t req);
void DMA_Init(DMA_Handle_t *pDMAHandler);
void DMA_DeInit(DMA_Stream_Reg_t *pDMAx);
#endif
