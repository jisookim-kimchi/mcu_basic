/*
 * 001led_toggle.c
 *
 *  Created on: Apr 20, 2026
 *      Author: wltn2
 */

#include "stm32f407xx_gpio_driver.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
	GPIO_Handler_t GpioLed;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOutPutType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPullUpDownControl = GPIO_NOPULL;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Set(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_12);
		delay();
	}
	return 0;
}
