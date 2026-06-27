#include "../Inc/stm32f407xx_cortex_driver.h"

/*
	enable or disable
    ISER = 1 : enable
    ICER = 1 : disable 
*/
void NVIC_IRQConfig(uint8_t IRQNum, uint8_t EnableOrDisable)
{
	uint8_t iser_reg_idx = IRQNum / 32;
    uint8_t iser_reg_bit = IRQNum % 32;

    if (EnableOrDisable == ENABLE)
    {
		NVIC->ISER[iser_reg_idx] |= (1 << iser_reg_bit);
    }
    else
    {
        NVIC->ICER[iser_reg_idx] |= (1 << iser_reg_bit);
    }
}

void NVIC_IRQPriorityConfig(uint8_t IRQNum, uint8_t IRQPriority)
{
	uint8_t ipr_reg_idx = IRQNum / 4;
    uint8_t ipr_reg_bit = IRQNum % 4;

    NVIC->IPR[ipr_reg_idx] |= (IRQPriority << (ipr_reg_bit * 8));
}
