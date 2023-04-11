#include "TIMER.h"

void tim4_1hz_init(void)
{
    RCC->APB1ENR |= TIM4EN;
    TIM4->PSC = 800 - 1;
    TIM4->ARR = 10000 - 1;
    TIM4->CNT = 0;
    TIM4->CR1 = CR1_CEN;
}

void tim4_PB8_output_compare(void)
{
    RCC->APB2ENR |= GPIOBEN;
    RCC->APB1ENR |= TIM4EN;

    GPIOB->CRH &= ~(1U<<0); 
    GPIOB->CRH |= (1U<<1); 
    GPIOB->CRH &= ~(1U<<2);
    GPIOB->CRH |= (1U<<3);  

    TIM4->PSC = 800 - 1;
    TIM4->ARR = 10000 - 1;
    TIM4->CCMR2 = OC_TOGGLE;
    TIM4->CCER |= CCRR_CC3E;
    TIM4->CNT = 0;
    TIM4->CR1 = CR1_CEN;
}

void tim1_PA8_input_capture(void)
{
    RCC->APB2ENR |= GPIOAEN;
    RCC->APB2ENR |= TIM1EN;

    GPIOA->CRH &= ~(1U<<0); 
    GPIOA->CRH &= ~(1U<<1); 
    GPIOA->CRH |= (1U<<2);
    GPIOA->CRH &= ~(1U<<3);  

    TIM1->PSC = 8000 - 1;
    TIM1->CCMR1 = CCMR1_CC1S;
    TIM1->CCER |= CCRR_CC1E;
    TIM1->CR1 = CR1_CEN;
}

void tim4_1hz_interrupt(void)
{
    RCC->APB1ENR |= TIM4EN;
    TIM4->PSC = 800 - 1;
    TIM4->ARR = 10000 - 1;
    TIM4->CNT = 0;
    TIM4->CR1 = CR1_CEN;
    TIM4->DIER |= DIER_UIE;
    NVIC_EnableIRQ(TIM4_IRQn);
}