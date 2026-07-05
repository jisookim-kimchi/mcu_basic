#ifndef STM32F407XX_DMA_DRIVER_H
#define STM32F407XX_DMA_DRIVER_H

#include "stm32f407xx.h"

#define DMA_OK 0
#define DMA_NG -1

/*
    DMA timeout
*/
#define DMA_TIMEOUT_ERROR       -1

/*
    RESET : before init
    READY : init done ready to start
    BUSY : dma on going
    COMPLETE : trasnfer complete 
    ERROR : error
*/
typedef enum
{
    DMA_STATE_RESET = 0,
    DMA_STATE_IDLE,
    DMA_STATE_COMPLETE,
    DMA_STATE_BUSY,
    DMA_STATE_ERROR
} DMA_State_t;

typedef enum
{
    DMA_CONFIG_OK = 0,
    DMA_CONFIG_INVALID_PARAM,
    DMA_CONFIG_INVALID_STREAM,
    DMA_CONFIG_INVALID_CHANNEL,
    DMA_CONFIG_INVALID_REQUEST,
} DMA_ConfigStatus_t;


// DMA MODE ENABLE
#define DMA_DMDIS_BIT 2

#define DMA_MODE_DIRECT_BIT (0 << DMA_DMDIS_BIT)
#define DMA_MODE_FIFO_BIT   (1 << DMA_DMDIS_BIT)

typedef enum
{
    DMA_MODE_DIRECT,
    DMA_MODE_FIFO
}DMA_Mode_t;

/*
	DMA FIFO Threshold selection
*/
#define DMA_FIFO_THRES_1_4_BIT   0
#define DMA_FIFO_THRES_2_4_BIT   1
#define DMA_FIFO_THRES_3_4_BIT   2
#define DMA_FIFO_THRES_FULL_BIT  3

typedef enum
{
    DMA_FIFO_THRES_1_4,
    DMA_FIFO_THRES_2_4,
    DMA_FIFO_THRES_3_4,
    DMA_FIFO_THRES_FULL
}DMA_FIFO_t;

// DMA channael select
#define DMA_CH0_BIT (0 << 25)
#define DMA_CH1_BIT (1 << 25)
#define DMA_CH2_BIT (2 << 25)
#define DMA_CH3_BIT (3 << 25)
#define DMA_CH4_BIT (4 << 25)
#define DMA_CH5_BIT (5 << 25)
#define DMA_CH6_BIT (6 << 25)
#define DMA_CH7_BIT (7 << 25)

typedef enum
{
    DMA_CH0,
    DMA_CH1,
    DMA_CH2,
    DMA_CH3,
    DMA_CH4,
    DMA_CH5,
    DMA_CH6,
    DMA_CH7
}DMA_Channel_t;

// DMA STREAM EN or DI
#define DMA_STREAM_ENABLE_BIT  (1 << 0)
#define DMA_STREAM_DISABLE_BIT (0 << 0)

typedef enum
{
    DMA_STREAM_ENABLE,
    DMA_STREAM_DISABLE
}DMA_StreamState_t;

/*
    DMA Memory brust transfer config
    - These bits are protected and can be written only if EN is ‘0’
    - In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'.
*/
#define DMA_MBURST_SINGLE_BIT   (0 << 23)
#define DMA_MBURST_INCR4_BIT    (1 << 23)
#define DMA_MBURST_INCR8_BIT    (2 << 23)
#define DMA_MBURST_INCR16_BIT   (3 << 23)

typedef enum
{
    DMA_MBURST_SINGLE,
    DMA_MBURST_INCR4,
    DMA_MBURST_INCR8,
    DMA_MBURST_INCR16
}DMA_MBurst_t;

/*
    DMA Pheripheral burst transfer config
    - These bits are protected and can be written only if EN is ‘0’
    - In direct mode, these bits are forced to 0x0 by hardware.
*/
#define DMA_PBURST_SINGLE_BIT   (0 << 21)
#define DMA_PBURST_INCR4_BIT    (1 << 21)
#define DMA_PBURST_INCR8_BIT    (2 << 21)
#define DMA_PBURST_INCR16_BIT   (3 << 21)

typedef enum
{
    DMA_PBURST_SINGLE,
    DMA_PBURST_INCR4,
    DMA_PBURST_INCR8,
    DMA_PBURST_INCR16
}DMA_PBurst_t;

/*
    DMA SxCR CIRC Circular mode
*/
#define DMA_CIRC_ENABLE_BIT (1 << 8)
#define DMA_CIRC_DISABLE_BIT (0 << 8)

typedef enum
{
    DMA_CIRC_ENABLE,
    DMA_CIRC_DISABLE
}DMA_Circ_t;


/*
    DMA Transfer Dir
*/
#define DMA_DIR_P2M_BIT (0 << 6)
#define DMA_DIR_M2P_BIT (1 << 6)
#define DMA_DIR_M2M_BIT (2 << 6)

typedef enum
{
    DMA_DIR_P2M,
    DMA_DIR_M2P,
    DMA_DIR_M2M
} DMA_Direction_t;

/*
    DMA Peripheral Increment Mode
*/
#define DMA_MINC_ENABLE_BIT (1 << 10)
#define DMA_MINC_DISABLE_BIT (0 << 10)

typedef enum
{
    DMA_MINC_ENABLE,
    DMA_MINC_DISABLE
}DMA_MInc_t;
/*
    DMA Memory Increment Mode
*/

#define DMA_PINC_ENABLE_BIT (1 << 9)
#define DMA_PINC_DISABLE_BIT (0 << 9)

typedef enum
{
    DMA_PINC_ENABLE,
    DMA_PINC_DISABLE
}DMA_PInc_t;

/*
    DMA Priority
*/
#define DMA_PRIORITY_LOW_BIT (0 << 16)
#define DMA_PRIORITY_MEDIUM_BIT (1 << 16)
#define DMA_PRIORITY_HIGH_BIT (2 << 16)
#define DMA_PRIORITY_VERY_HIGH_BIT (3 << 16)

typedef enum
{
    DMA_PRIORITY_LOW,
    DMA_PRIORITY_MEDIUM,
    DMA_PRIORITY_HIGH,
    DMA_PRIORITY_VERY_HIGH
}DMA_Priority_t;


typedef enum
{
    DMA_DATASIZE_8BIT,
    DMA_DATASIZE_16BIT,
    DMA_DATASIZE_32BIT
}DMA_DataSize_t;

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

typedef struct
{
    uint8_t offset;
    uint8_t is_high; // 1 or 0
} DMA_FlagMap_t;

/*
    LISR
    bit 0 : Stream 0 all flags
    bit 6 : Stream 1 all flags
    bit 16 : Stream 2 all flags
    bit 22 : Stream 3 all flags
    
    HISR
    bit 0 : Stream 4 all flags
    bit 6 : Stream 5 all flags
    bit 16 : Stream 6 all flags
    bit 22 : Stream 7 all flags
*/
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
    DMA_Direction_t TransferDir;
    DMA_PInc_t PeriphInc;
    DMA_MInc_t MemInc;
    DMA_DataSize_t PeriDataSize;
    DMA_DataSize_t MemDataSize;
    DMA_Priority_t Priority;
    DMA_Circ_t CircularMode;
    DMA_Mode_t FIFO_Or_DirectMode;
    DMA_FIFO_t FIFOThreshold;
    DMA_MBurst_t MemBurst;
    DMA_PBurst_t PerBurst;
}DMA_Config_t;

/*
    ISR functions
*/
typedef enum
{
    DMA_EVENT_TC, //transfer complete
    DMA_EVENT_HTC, //half transfer complete 
    DMA_EVENT_TE, //transfer error
    DMA_EVENT_FE  //fifo error
}DMA_Event_t;

struct DMA_Handle_s; 

typedef void (*DMA_Callback_fn)(struct DMA_Handle_s *pHandler, DMA_Event_t event);

typedef struct DMA_Handle_s
{
  DMA_Reg_t *pDMAx;
  DMA_Channel_t channel;
  uint8_t streamNum;
  uintptr_t peripheral; //peirpheral addr.
  uintptr_t mem;        // mem addr.
  uint32_t length;
  DMA_Config_t config;
  volatile DMA_State_t state;
  DMA_Callback_fn pCallback;
} DMA_Handle_t;

void DMA_PeriClockControl(DMA_Reg_t *pDMAx, uint8_t EnOrDi);
int32_t DMA_Init(DMA_Handle_t *pDMAHandler);
int32_t DMA_Start(DMA_Handle_t *handler);
int32_t DMA_DeInit(DMA_Handle_t *pDMAHandler);
#endif
