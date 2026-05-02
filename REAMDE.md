
### INTERRUPT EXTI
SYSCFG_CLOCK_ENABLE()
        ↓
SYSCFG->EXTICR[pin/4] : GPIO Port select
        ↓
EXTI->FTSR or RTSR   : edge direction
EXTI->IMR            : Enable or Disable IRQ
        ↓
NVIC_IRQConfig()     : IRQ number enable + priority
        ↓
ISR function         : EXTI->PR clear

                                   [bridge]
GPIO(STM32)  ->  SYSCFG(STM32) -> EXTI(STM32) -> NVIC(Arm Cortex)
NVIC can identify just only IRQ number.
In ISR, EXTI->PR(Pending Register) is checked to identify the pending line
                                    
IRQ : a specefic ID that NVIC controller identify (Arm Cortex) position in the vector table.

#### EXTI and IRQ maaping
ref : vector table 
EXTI_line 			   IRQ 		             ISR function
EXTI0				    6	                 EXTI0_IRQHandler
EXTI1				    7	                 EXTI1_IRQHandler
EXTI2				    8	                 EXTI2_IRQHandler
EXTI3				    9	                 EXTI3_IRQHandler
EXTI4				    10	                 EXTI4_IRQHandler
EXTI5~9				    23	                 EXTI9_5_IRQHandler
EXTI10~15		            40	                 EXTI15_10_IRQHandler