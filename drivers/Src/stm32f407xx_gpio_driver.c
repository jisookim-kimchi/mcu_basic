/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Apr 16, 2026
 *      Author: wltn2
 */


#include "../Inc/stm32f407xx_gpio_driver.h"
#include <assert.h>
#include <stddef.h>

/*
 * @param[in]: GPIO Regster's Address
 */
void GPIO_PeriClockControl(GPIO_Reg_t *pGPIOx, uint8_t EnableOrDisable)
{
	assert(pGPIOx != NULL);
	if(EnableOrDisable == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_CLOCK_ENABLE();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_CLOCK_ENABLE();
		}
	}
	else
	{

	}

}

void GPIO_Set(GPIO_Handler_t *pGPIOHandler)
{
	assert(pGPIOHandler != NULL);
    uint8_t pin = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber;

    pGPIOHandler->pGPIOx->MODER &= ~(0b11 << (2 * pin));
    GPIO_MODE_t mode   = pGPIOHandler->GPIO_PinConfig.GPIO_PinMode;
    GPIO_SPEED_t speed = pGPIOHandler->GPIO_PinConfig.GPIO_PinSpeed;
    GPIO_PUPD_t pupd   = pGPIOHandler->GPIO_PinConfig.GPIO_PinPullUpDownControl;
    GPIO_OP_TYPE_t otype = pGPIOHandler->GPIO_PinConfig.GPIO_PinOutPutType;
    uint8_t af = pGPIOHandler->GPIO_PinConfig.GPIO_PinAltFunMode;

    // 1. MODE (MODER)
    if (mode <= GPIO_MODE_ANALOG)
    {
		pGPIOHandler->pGPIOx->MODER &= ~(0b11 << (2 * pin)); //clear
		pGPIOHandler->pGPIOx->MODER |=  (mode << (2 * pin)); //set
    }
    // 2. SPEED (OSPEEDR)
    pGPIOHandler->pGPIOx->OSPEEDR &= ~(0b11 << (2 * pin));
    pGPIOHandler->pGPIOx->OSPEEDR |=  (speed << (2 * pin));
    // 3. PUPD (PUPDR)
    pGPIOHandler->pGPIOx->PUPDR &= ~(0b11 << (2 * pin));
    pGPIOHandler->pGPIOx->PUPDR |=  (pupd << (2 * pin));
    // 4. OUTPUT TYPE (OTYPER)
    pGPIOHandler->pGPIOx->OTYPER &= ~(0b01 << pin);
    pGPIOHandler->pGPIOx->OTYPER |=  (otype << pin);
    // 5. ALTERNATE FUNCTION (AFR)
    if(mode == GPIO_MODE_AF)
    {
        uint8_t temp1 = pin / 8;
        uint8_t temp2 = pin % 8;

        pGPIOHandler->pGPIOx->AFR[temp1] &= ~(0b1111 << (4 * temp2)); 	//clear
        pGPIOHandler->pGPIOx->AFR[temp1] |=  (af << (4 * temp2));  		//set
    }
}

//
void GPIO_Reset(GPIO_Reg_t *pGPIOx)
{
	assert(pGPIOx != NULL);
	if(pGPIOx == GPIOA)
	{
		GPIOA_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_REGISTER_RESET();
	}
	else if(pGPIOx == GPIOI)
	{
		GPIOI_REGISTER_RESET();
	}
}

uint8_t GPIO_ReadFromInputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum)
{
	assert(pGPIOx != NULL);
	assert(PinNum < 16);
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNum) & 0x00000001);
	return value;
}

//
uint16_t GPIO_ReadFromInputPort(GPIO_Reg_t *pGPIOx)
{
	assert(pGPIOx != NULL);
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

//
void GPIO_WriteToOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum, uint8_t Value)
{
	if (!pGPIOx || PinNum >= 16)
		return;
	if (Value == SET)
	{
		pGPIOx->ODR |= (1 << PinNum);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNum);
	}
}

//
void GPIO_WriteToOutputPort(GPIO_Reg_t *pGPIOx, uint16_t Value )
{
	assert(pGPIOx != NULL);
	pGPIOx->ODR = Value;
}

//
void GPIO_ToggleOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum)
{
	if (!pGPIOx || PinNum >= 16)
		return;
	pGPIOx->ODR ^= (1 << PinNum);
}

//
void GPIO_IRQConfig(uint8_t IQRNum, uint8_t IRQPriority, uint8_t EnableOrDisable)
{

}

//
void GPIO_IRQHandler(uint8_t PinNum)
{

}


