#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"
#include "stm32f1xx.h"
#include "GPIO.h"

typedef enum
{
    Channel0,
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7,
    Channel8,
    Channel9,
    Channel10,
    Channel11,
    Channel12,
    Channel13,
    Channel14,
    Channel15,
    ChannelTemp,
    ChannelVrefint
}ADC_ChannelDef;

typedef struct
{
    ADC_ChannelDef Priority0;
    ADC_ChannelDef Priority1;
    ADC_ChannelDef Priority2;
    ADC_ChannelDef Priority3;
    ADC_ChannelDef Priority4;
    ADC_ChannelDef Priority5;
    ADC_ChannelDef Priority6;
    ADC_ChannelDef Priority7;
    ADC_ChannelDef Priority8;
    ADC_ChannelDef Priority9;
    ADC_ChannelDef Priority10;
    ADC_ChannelDef Priority11;
    ADC_ChannelDef Priority12;
    ADC_ChannelDef Priority13;
    ADC_ChannelDef Priority14;
    ADC_ChannelDef Priority15;
    ADC_ChannelDef Priority16;
}Channel_Priority;

void SetADCpins(ADC_TypeDef *ADCx, ADC_ChannelDef CHx);
void ADC_INIT(ADC_TypeDef *ADCx, uint8_t *PinsofADC, uint8_t NumOfConversions, Channel_Priority Priorities);
void setSequence(ADC_TypeDef *ADCx, Channel_Priority Priorities);
void Start_Conversion(ADC_TypeDef *ADCx);
uint32_t ADC_Read(ADC_TypeDef *ADCx);
void Start_Conversion_Continous(ADC_TypeDef *ADCx);
void ADC_INTERRUPT_INIT(ADC_TypeDef *ADCx, uint8_t *PinsofADC, uint8_t NumOfConversions, Channel_Priority Priorities);

#endif