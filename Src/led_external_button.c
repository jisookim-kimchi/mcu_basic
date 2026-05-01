/*
 * led_external_button.c
 *
 *  Created on: Apr 30, 2026
 *      Author: wltn2
 */


#include "stm32f407xx_gpio_driver.h"
#define BUTTON_PRESSED 1
#define BUTTON_REALEASED 0

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
	GPIO_Handler_t GpioLed, GpioButton;

	//LED config
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOutPutType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPullUpDownControl = GPIO_NOPULL;

	//Button config
	GpioButton.pGPIOx = GPIOA;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPullUpDownControl = GPIO_PULLUP;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_PeriClockControl(GPIOA, ENABLE);

	GPIO_Set(&GpioLed);
	GPIO_Set(&GpioButton);

	while(1)
	{
	    if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_0) == BUTTON_PRESSED)
	    {
	        delay();
	        GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_12);
	    }
	}
}
