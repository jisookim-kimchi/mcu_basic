
#ifndef STM32F407XX_SPI_DRIVER_H
#define STM32F407XX_SPI_DRIVER_H

#include "stm32f407xx.h"

/*
 * SPI Device Mode
 */
#define SPI_DEVICE_MODE_SLAVE   0
#define SPI_DEVICE_MODE_MASTER  1

/*
 * SPI Bus Config
*/
#define SPI_BUS_CONFIG_FD   		0
#define SPI_BUS_CONFIG_HD   		1
#define SPI_BUS_CONFIG_SIMPLEX   	2

/*
    SPI Clock Speed - Prescaler
*/
#define SPI_FPCLK_DIV2    0
#define SPI_FPCLK_DIV4    1
#define SPI_FPCLK_DIV8    2
#define SPI_FPCLK_DIV16   3
#define SPI_FPCLK_DIV32   4
#define SPI_FPCLK_DIV64   5
#define SPI_FPCLK_DIV128  6
#define SPI_FPCLK_DIV256  7

/*
    SPI Data Frame Format(DFF)
*/
#define SPI_DFF_8BIT    0
#define SPI_DFF_16BIT   1

/*
	SPI SSM Software or Hardware
*/
#define SPI_SSM_HW    0
#define SPI_SSM_SW    1

/*
    SPI Clock Polarity (CPOL)
*/
#define SPI_CPOL_LOW    0
#define SPI_CPOL_HIGH   1

/*
    SPI Clock Phase (CPHA)
*/
#define SPI_CPHA_1EDGE    0
#define SPI_CPHA_2EDGE    1

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
} SPI_Config_t;

typedef struct
{
	SPI_Reg_t *pSPIx;
	SPI_Config_t SPI_Config;
} SPI_Handle_t;

// @brief: Enable or disable the peripheral clock for a given SPI peripheral
void SPI_PeriClockControl(SPI_Reg_t *pSPIx, uint8_t EnOrDi);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Reg_t *pSPIx);

// @brief: (Polling method)
void SPI_SendData(SPI_Reg_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_Reg_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

// @brief: interrupt
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

// @brief: NSS(Slave Select) Control
void SPI_PeripheralControl(SPI_Reg_t *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_Reg_t *pSPIx, uint8_t EnOrDi);
void SPI_SSOEConfig(SPI_Reg_t *pSPIx, uint8_t EnOrDi);

// @brief: interrupt Data Send or Receive
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

// @brief: DMA Data Send or Receive
void SPI_DMAControl(SPI_Reg_t *pSPIx, uint8_t EnOrDi);
void SPI_SendDataDMA(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveDataDMA(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);




#endif