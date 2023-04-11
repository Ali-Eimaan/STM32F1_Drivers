#include "EXTI.h"

void PA8_EXTI_INIT(void)
{
    __disable_irq();

    RCC->APB2ENR |= GPIOAEN;
    RCC->APB2ENR |= AFIOEN;

    GPIOA->CRH &= ~(1U<<0);
    GPIOA->CRH &= ~(1U<<1);
    GPIOA->CRH &= ~(1U<<2);
    GPIOA->CRH |= (1U<<3);

    AFIO->EXTICR3 = 0;

    EXTI->IMR |= LINE8;
    EXTI->FTSR |= LINE8;

    NVIC_EnableIRQ(EXTI9_5_IRQn);

    __enable_irq();
}