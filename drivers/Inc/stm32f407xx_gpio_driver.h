/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Apr 16, 2026
 *      Author: wltn2
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#define GPIO_PIN_NUM_0
#include "stm32f407xx.h"

/*
 * GPIO Pin Modes
 */
typedef enum
{
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_AF,
    GPIO_MODE_ANALOG,
	GPIO_MODE_IT, //interrupt mode -> trigger handled by EXTI Config
} GPIO_MODE_t;

typedef enum
{
    GPIO_NOPULL,
    GPIO_PULLUP,
    GPIO_PULLDOWN
} GPIO_PUPD_t;

typedef enum
{
    GPIO_OP_TYPE_PP,   // push-pull
    GPIO_OP_TYPE_OD,    // open-drain
} GPIO_OP_TYPE_t;

typedef enum
{
    GPIO_SPEED_LOW,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_FAST,
    GPIO_SPEED_HIGH
} GPIO_SPEED_t;

typedef struct
{
    uint8_t 		GPIO_PinNumber;
    GPIO_MODE_t 	GPIO_PinMode;
    GPIO_SPEED_t 	GPIO_PinSpeed;
    GPIO_PUPD_t 	GPIO_PinPullUpDownControl;
    GPIO_OP_TYPE_t 	GPIO_PinOutPutType;
    uint8_t 		GPIO_PinAltFunMode;
} GPIO_PinConfig_t;
/*
 * Handler for a GPIO pin
 */
typedef struct
{
	GPIO_Reg_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;
	EXTI_Config_t EXTI_Config;
}GPIO_Handler_t;

/*
 * Interrupt EXTI
 */
void GPIO_PeriClockControl(GPIO_Reg_t *pGPIOx, uint8_t EnableOrDisable);
void GPIO_Set(GPIO_Handler_t *pGPIOHandler);
void GPIO_Reset(GPIO_Reg_t *pGPIOx);
uint8_t GPIO_ReadFromInputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum);
uint16_t GPIO_ReadFromInputPort(GPIO_Reg_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_Reg_t *pGPIOx, uint16_t Value );
void GPIO_ToggleOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum);


#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
