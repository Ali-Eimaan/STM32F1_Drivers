#include "ADC.h"

void ADC_INIT(ADC_TypeDef *ADCx, uint8_t *PinsofADC, uint8_t NumOfConversions, Channel_Priority Priorities)
{
    if (ADCx == ADC1)
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    else if (ADCx == ADC2)
        RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
    
    for (int i = 0; i < NumOfConversions; i++)
        SetADCpins(ADCx, PinsofADC[i]);

    setSequence(ADCx, Priorities);
    ADCx->SQR1 |= NumOfConversions<<20;
    ADCx->CR2 |= ADC_CR2_ADON;
}

void SetADCpins(ADC_TypeDef *ADCx, ADC_ChannelDef CHx)
{
    if (CHx < Channel8)
        SetPinMode(GPIOA, PORTA, CHx, InputMode, AnalogInput);
    else
        SetPinMode(GPIOB, PORTB, (CHx - 8), InputMode, AnalogInput);
}

void setSequence(ADC_TypeDef *ADCx, Channel_Priority Priorities)
{
    ADCx->SQR3 = Priorities.Priority0 << 0;
    ADCx->SQR3 = Priorities.Priority1 << 5;
    ADCx->SQR3 = Priorities.Priority2 << 10;
    ADCx->SQR3 = Priorities.Priority3 << 15;
    ADCx->SQR3 = Priorities.Priority4 << 20;
    ADCx->SQR3 = Priorities.Priority5 << 25;
    ADCx->SQR2 = Priorities.Priority6 << 0;
    ADCx->SQR2 = Priorities.Priority7 << 5;
    ADCx->SQR2 = Priorities.Priority8 << 10;
    ADCx->SQR2 = Priorities.Priority9 << 15;
}

void ADC_INTERRUPT_INIT(ADC_TypeDef *ADCx, uint8_t *PinsofADC, uint8_t NumOfConversions, Channel_Priority Priorities)
{
    if (ADCx == ADC1)
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    else if (ADCx == ADC2)
        RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;

    for (int i = 0; i < NumOfConversions; i++)
        SetADCpins(ADCx, PinsofADC[i]);

    setSequence(ADCx, Priorities);
    ADCx->SQR1 |= NumOfConversions<<20; 
    ADCx->CR2 |= ADC_CR2_ADON;
    ADCx->CR1 |= ADC_CR1_EOCIE;

    NVIC_EnableIRQ(ADC1_IRQn);
}

void Start_Conversion(ADC_TypeDef *ADCx)
{
    ADCx->CR2 |= ADC_CR2_SWSTART;
}

void Start_Conversion_Continous(ADC_TypeDef *ADCx)
{
    ADC1->CR2 |= ADC_CR2_CONT;
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t ADC_Read(ADC_TypeDef *ADCx)
{
    while(!(ADCx->SR & ADC_SR_EOC));
    return ADCx->DR;
}
