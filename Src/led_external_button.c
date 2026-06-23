/*
 * led_external_button.c
 *
 *  Created on: Apr 30, 2026
 *      Author: wltn2
 */

#include <stdint.h>

#include "../drivers/Inc/stm32f407xx_gpio_driver.h"
#include "../drivers/Inc/stm32f407xx_exti_driver.h"
#include "../drivers/Inc/stm32f407xx_cortex_driver.h"

// void delay(void)
// {
//     for(uint32_t i = 0; i < 500000/2; i++);
// }

// int main(void)
// {
//     GPIO_Handler_t GpioLed, GpioButton;
//     // LED config
//     GpioLed.pGPIOx = GPIOD;
//     GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
//     GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
//     GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//     GpioLed.GPIO_PinConfig.GPIO_PinOutPutType = GPIO_OP_TYPE_PP;
//     GpioLed.GPIO_PinConfig.GPIO_PinPullUpDownControl = GPIO_NOPULL;
    
// 	// button config
//     GpioButton.pGPIOx = GPIOB;
//     GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
//     GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT;
//     GpioButton.GPIO_PinConfig.GPIO_PinPullUpDownControl = GPIO_PULLUP;
    
//     // EXTI config
//     GpioButton.EXTI_Config.EXTI_TriggerMode = EXTI_TRIGGER_FALLING;
//     GpioButton.EXTI_Config.EXTI_IRQ_Enable = ENABLE;

//     // clock enable
//     GPIO_PeriClockControl(GPIOD, ENABLE);
//     GPIO_PeriClockControl(GPIOB, ENABLE);

//     // GPIO and EXTI init
//     GPIO_Set(&GpioLed);
//     GPIO_Set(&GpioButton);
//     EXTI_Init(&GpioButton);
//     EXTI_TriggerModeSet(&GpioButton);
//     EXTI_IMRSet(&GpioButton);
	
//     // NVIC config (pin 10~15 is IRQ 40)
//     NVIC_IRQConfig(IRQ_NO_EXTI10_15, ENABLE);
//     NVIC_IRQPriorityConfig(IRQ_NO_EXTI10_15, 15);
//     while(1);
// }

// // IRQ handler (pin 12 is included in this handler name)
// void EXTI15_10_IRQHandler(void)
// {
//     delay();
//     PendingReg_Clear(GPIO_PIN_12);
//     GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_12);
// }