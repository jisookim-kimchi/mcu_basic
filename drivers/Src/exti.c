#include "../Inc/stm32f407xx_gpio_driver.h"

/*
    EXTI line and Port mapping.
*/
void EXTI_Init(GPIO_Handler_t *pGPIOHandler)
{
    SYSCFG_CLOCK_ENABLE();
    uint8_t PinNum = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber;
    uint8_t exticr_idx = PinNum / 4;
    uint8_t shift = (PinNum % 4) * 4;

    SYSCFG->EXTICR[exticr_idx] &= ~(0xF << shift);
    SYSCFG->EXTICR[exticr_idx] |=  (GPIO_BASEADDR_TO_CODE(pGPIOHandler->pGPIOx) << shift);
}

void EXTI_TriggerModeSet(GPIO_Handler_t *pGPIOHandler)
{
    EXTI_TriggerMode_t mode = pGPIOHandler->EXTI_Config.EXTI_TriggerMode;
    if (mode == EXTI_TRIGGER_FALLING)
    {
        
    }
}