/*
 * stm32f407xx.h
 *
 *  Created on: Apr 14, 2026
 *      Author: wltn2
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_


#include <stdint.h>

#define FLASH_BASEADDR				0x08000000U //non volatile like SSD
#define SRAM1_BASEADDR				0x20000000U //volatile like RAM
#define SRAM2_BASEADDR				0x2001C000U
#define ROM							0x1FFF0000U	//system memory
#define SRAM 						SRAM1_BASEADDR

#define PERIPHERAL_BASE 			0x40000000U
#define APB1_PERIPH_BASE			PERIPHERAL_BASE
#define APB2_PERIPH_BASE			0x40010000U
#define AHB1_PERIPH_BASE			0x40020000U
#define AHB2_PERIPH_BASE			0x50000000U


#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15

/*
 * Base address of Peripherals at AHB1_BUS
 * */
#define GPIOA_BASEADDR				(AHB1_PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR				(AHB1_PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR				(AHB1_PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR				(AHB1_PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR				(AHB1_PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR				(AHB1_PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR				(AHB1_PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR				(AHB1_PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR				(AHB1_PERIPH_BASE + 0x2000)
#define RCC_BASEADDR				0x40023800U
/*
 * Base address of Peripherals at APB1_BUS
 * */
#define I2C1_BASEADDR				(PERIPHERAL_BASE + 0x5400)
#define I2C2_BASEADDR				(PERIPHERAL_BASE + 0x5800)
#define I2C3_BASEADDR				(PERIPHERAL_BASE + 0x5C00)
#define SPI2_BASEADDR				(PERIPHERAL_BASE + 0x5C00)
#define SPI3_BASEADDR				(PERIPHERAL_BASE + 0x5C00)

/*
 * Base address of Peripherals at APB2_BUS
 * */
#define USART1_BASEADDR				(APB2_PERIPH_BASE + 0x1000)
#define USART6_BASEADDR				(APB2_PERIPH_BASE + 0x1400)
#define SPI1_BASEADDR				(APB2_PERIPH_BASE + 0x3000)
#define SYSCFG_BASEADDR				(APB2_PERIPH_BASE + 0x3800)
#define EXTI_BASEADDR				(APB2_PERIPH_BASE + 0x3C00)


/*
 * Registers of GPIO.
 * The offset is in 4byte increments.
 * Volatile: because the value can be changed by hardware (outside the CPU).
 */

typedef struct
{
	volatile uint32_t	MODER;		//0x00
	volatile uint32_t	OTYPER;		//0x04
	volatile uint32_t	OSPEEDR;	//0x08
	volatile uint32_t	PUPDR;		//0x0c
	volatile uint32_t	IDR;		//0x10
	volatile uint32_t	ODR;		//0x14
	volatile uint32_t	BSRR;		//0x18
	volatile uint32_t	LCKR;		//0x1C
	volatile uint32_t 	AFR[2];		//0x20~23,0x24~27
}GPIO_Reg_t;

#define GPIOA	((GPIO_Reg_t*)GPIOA_BASEADDR)
#define GPIOB	((GPIO_Reg_t*)GPIOB_BASEADDR)
#define GPIOC	((GPIO_Reg_t*)GPIOC_BASEADDR)
#define GPIOD	((GPIO_Reg_t*)GPIOD_BASEADDR)
#define GPIOE	((GPIO_Reg_t*)GPIOE_BASEADDR)
#define GPIOF	((GPIO_Reg_t*)GPIOF_BASEADDR)
#define GPIOG	((GPIO_Reg_t*)GPIOG_BASEADDR)
#define GPIOH	((GPIO_Reg_t*)GPIOH_BASEADDR)
#define GPIOI	((GPIO_Reg_t*)GPIOI_BASEADDR)

/*
 * Registers of RCC
 * The offset is in 4byte increments. (0x00 ~ 0x8C)
 */

typedef struct
{
	volatile uint32_t	CR;
	volatile uint32_t	PLLCFGR;
	volatile uint32_t	CFGR;
	volatile uint32_t	CIR;
	volatile uint32_t	AHB1RSTR;
	volatile uint32_t	AHB2RSTR;
	volatile uint32_t	AHB3RSTR;
			uint32_t Reserved0;
	volatile uint32_t	APB1RSTR;
	volatile uint32_t	APB2RSTR;
			uint32_t Reserved1[2];
	volatile uint32_t	AHB1ENR;
	volatile uint32_t	AHB2ENR;
	volatile uint32_t	AHB3ENR;
			uint32_t Reserved2;
	volatile uint32_t	APB1ENR;
	volatile uint32_t	APB2ENR;
			uint32_t Reserved3[2];
	volatile uint32_t	AHB1LPENR;
	volatile uint32_t	AHB2LPENR;
	volatile uint32_t	AHB3LPENR;
			uint32_t Reserved4;
	volatile uint32_t	APB1LPENR;
	volatile uint32_t	APB2LPENR;
			uint32_t Reserved5[2];
	volatile uint32_t	BDCR;
	volatile uint32_t	CSR;
			uint32_t Reserved6[2];
	volatile uint32_t	SSCGR;
	volatile uint32_t	PLLI2SCFGR;
	volatile uint32_t	PLLSAICFGR;
	volatile uint32_t	DCKCFGR;
}RCC_Reg_t;

typedef struct
{
	volatile uint32_t MEMRMP;		//0x00
	volatile uint32_t PMC;			//0x04
	volatile uint32_t EXTICR[4];	//0x08~0x14
	        uint32_t Reserved[2];   //0x18~0x1c
	volatile uint32_t CMPCR;		//0x20
}SYSCFG_Reg_t;


typedef enum
{
    EXTI_TRIGGER_FALLING,
    EXTI_TRIGGER_RISING,
    EXTI_TRIGGER_RISING_FALLING
}EXTI_TriggerMode_t;

typedef struct
{
    uint8_t EXTI_PinNumber;         //IMR setting
    EXTI_TriggerMode_t EXTI_TriggerMode; //trigger mode
    uint8_t EXTI_IRQ_Enable;        //Enable or Disable IRQ
} EXTI_Config_t;

typedef struct
{
    volatile uint32_t IMR;    // 0x00 - Interrupt Mask Register
    volatile uint32_t EMR;    // 0x04 - Event Mask Register
    volatile uint32_t RTSR;   // 0x08 - Rising Trigger Selection
    volatile uint32_t FTSR;   // 0x0C - Falling Trigger Selection
    volatile uint32_t SWIER;  // 0x10 - Software Interrupt Event
    volatile uint32_t PR;     // 0x14 - Pending Register
} EXTI_Reg_t;


#define EXTI  ((EXTI_Reg_t*)EXTI_BASEADDR)
#define RCC		((RCC_Reg_t*)RCC_BASEADDR)
#define SYSCFG		((SYSCFG_Reg_t*)SYSCFG_BASEADDR)

/*
 *	Clock Enable Macros for GPIO'x Peripherals
 */

#define GPIOA_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 7))
#define GPIOI_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1 << 8))

/*
 *  Clock Enable Macros for I2C'x
 */

#define I2C1_CLOCK_ENABLE()	(RCC->APB1ENR |= (1 << 21))
#define I2C2_CLOCK_ENABLE()	(RCC->APB1ENR |= (1 << 22))
#define I2C3_CLOCK_ENABLE()	(RCC->APB1ENR |= (1 << 23))

/*
 * 	Clock Enable Macros for SPI'x
 */

#define SPI1_CLOCK_ENABLE()	(RCC->APB2ENR |= (1 << 12))
#define SPI2_CLOCK_ENABLE()	(RCC->APB1ENR |= (1 << 14))
#define SPI3_CLOCK_ENABLE()	(RCC->APB1ENR |= (1 << 15))
#define SPI4_CLOCK_ENABLE()	(RCC->APB2ENR |= (1 << 13))

/*
 * 	Clock Enable Macros for USART'x
 */

#define USART1_CLOCK_ENABLE()   (RCC->APB2ENR |= (1 << 4))
#define USART2_CLOCK_ENABLE()   (RCC->APB1ENR |= (1 << 17))
#define USART3_CLOCK_ENABLE()   (RCC->APB1ENR |= (1 << 18))
#define UART4_CLOCK_ENABLE()    (RCC->APB1ENR |= (1 << 19))
#define UART5_CLOCK_ENABLE()    (RCC->APB1ENR |= (1 << 20))
#define USART6_CLOCK_ENABLE()   (RCC->APB2ENR |= (1 << 5))

/*
 * Clock Enable Macros for SYSCFG
 */
#define SYSCFG_CLOCK_ENABLE()   (RCC->APB2ENR |= (1 << 14))

/*
 * Clock Disable Macros for GPIO'x Peripherals
 */

#define GPIOA_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_CLOCK_DISABLE()   (RCC->AHB1ENR &= ~(1 << 7))

/*
 * Clock Disable Macros for IC2'x Peripherals
 */
#define I2C1_CLOCK_DISABLE()   (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLOCK_DISABLE()   (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_CLOCK_DISABLE()   (RCC->APB1ENR &= ~(1 << 23))

/*
 * Clock Disable Macros for SPI'x Peripherals
 */
#define SPI1_CLOCK_DISABLE()   (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLOCK_DISABLE()   (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLOCK_DISABLE()   (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_CLOCK_DISABLE()   (RCC->APB2ENR &= ~(1 << 13))

/*
 * Clock Disable Macros for USART'x Peripherals
 */
#define USART1_CLOCK_DISABLE()   (RCC->APB2ENR &= ~(1 << 4))
#define USART2_CLOCK_DISABLE()   (RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLOCK_DISABLE()   (RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLOCK_DISABLE()    (RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLOCK_DISABLE()    (RCC->APB1ENR &= ~(1 << 20))
#define USART6_CLOCK_DISABLE()   (RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock Disable Macros for SYSCFG
 */
#define SYSCFG_CLOCK_DISABLE()   (RCC->APB2ENR &= ~(1 << 14))
#define GPIOA_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));} while(0)
#define GPIOB_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));} while(0)
#define GPIOC_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));} while(0)
#define GPIOD_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));} while(0)
#define GPIOE_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));} while(0)
#define GPIOF_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));} while(0)
#define GPIOG_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));} while(0)
#define GPIOH_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));} while(0)
#define GPIOI_REGISTER_RESET()   do{(RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8));} while(0)


/*
*  GPIO base address → SYSCFG EXTICR port code (PA=0, PB=1, ...)
*/
#define GPIO_BASEADDR_TO_CODE(x)  ( (x == GPIOA) ? 0 : \
                                    (x == GPIOB) ? 1 : \
                                    (x == GPIOC) ? 2 : \
                                    (x == GPIOD) ? 3 : \
                                    (x == GPIOE) ? 4 : \
                                    (x == GPIOF) ? 5 : \
                                    (x == GPIOG) ? 6 : \
                                    (x == GPIOH) ? 7 : 0 )


/*
 * config
 */
#define ENABLE 			1
#define DISABLE		 	0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET 	RESET
#endif /* INC_STM32F407XX_H_ */
