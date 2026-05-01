/*
 * exti.h
 *
 *  Created on: May 1, 2026
 *      Author: wltn2
 */


typedef struct
{
    uint8_t EXTI_PinNumber;
    uint8_t EXTI_TriggerMode;
    uint8_t EXTI_IRQ_Enable;
} EXTI_Config_t;
