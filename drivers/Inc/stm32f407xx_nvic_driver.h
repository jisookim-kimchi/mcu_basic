#ifndef INC_STM32F407XX_CORTEX_DRIVER_H_
#define INC_STM32F407XX_CORTEX_DRIVER_H_

#include "stm32f407xx.h"

/*
 * NVIC Interrupt Functions (ARM Cortex-M4)
 */
void NVIC_IRQConfig(uint8_t IRQNum, uint8_t EnableOrDisable);
void NVIC_IRQPriorityConfig(uint8_t IRQNum, uint8_t IRQPriority);

#endif /* INC_STM32F407XX_CORTEX_DRIVER_H_ */
