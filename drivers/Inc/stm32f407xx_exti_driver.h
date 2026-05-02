#ifndef INC_STM32F407XX_EXTI_DRIVER_H_
#define INC_STM32F407XX_EXTI_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

/*
 * EXTI / NVIC Interrupt Functions
 */
void EXTI_Init(GPIO_Handler_t *pGPIOHandler);
void EXTI_TriggerModeSet(GPIO_Handler_t *pGPIOHandler);
void EXTI_IMRSet(GPIO_Handler_t *pGPIOHandler);


void PendingReg_Clear(uint8_t PinNum);

#endif /* INC_STM32F407XX_EXTI_DRIVER_H_ */
