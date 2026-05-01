/*
 * led_button.c
 *
 *  Created on: Apr 30, 2026
 *      Author: wltn2
 */

/*
 * 001led_toggle.c
 *
 *  Created on: Apr 20, 2026
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

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinPullUpDownControl = GPIO_NOPULL;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Set(&GpioLed);

	while(1)
	{
		if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_0) == BUTTON_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_12);
		}
	}
	return 0;
}
