
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
#define 

typedef struct
{
				//is it master or slave?
				//communication way
				//clk speed
				//data size
				//cpol & cpha
				//ssm software or hardware
} SPI_Config_t;

#endif