#include "ADC.h"

void PA4_ADC_INIT(void)
{
    RCC->APB2ENR |= GPIOAEN;
    RCC->APB2ENR |= ADC1EN;

    GPIOA->CRL &= ~(1U<<16); 
    GPIOA->CRL &= ~(1U<<17); 
    GPIOA->CRL &= ~(1U<<18);
    GPIOA->CRL &= ~(1U<<19);  

    ADC1->SQR3 = ADC1CH4;
    ADC1->SQR1 = SEQLEN1; 
    ADC1->CR2 |= CR2_ADON;
}

void PA4_ADC_INTERRUPT_INIT(void)
{
    RCC->APB2ENR |= GPIOAEN;
    RCC->APB2ENR |= ADC1EN;

    GPIOA->CRL &= ~(1U<<16); 
    GPIOA->CRL &= ~(1U<<17); 
    GPIOA->CRL &= ~(1U<<18);
    GPIOA->CRL &= ~(1U<<19);  

    ADC1->SQR3 = ADC1CH4;
    ADC1->SQR1 = SEQLEN1; 
    ADC1->CR2 |= CR2_ADON;
    ADC1->CR1 |= CR1_EOCIE;

    NVIC_EnableIRQ(ADC1_IRQn);
}

void Start_Conversion(void)
{
    ADC1->CR2 |= CR2_SWSTART;
}

void Start_Conversion_Continous(void)
{
    ADC1->CR2 |= CR2_CONT;
    ADC1->CR2 |= CR2_SWSTART;
}

uint32_t ADC_Read(void)
{
    while(!(ADC1->SR & SR_EOC));
    return ADC1->DR;
}
