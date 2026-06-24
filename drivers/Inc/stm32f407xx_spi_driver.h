
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
	
} SPI_Config_t;

#endif