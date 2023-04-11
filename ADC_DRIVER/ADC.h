#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"
#include "stm32f1xx.h"

#define ADC1EN              (1U<<9)
#define GPIOAEN             (1U<<2)
#define ADC1CH4             (4U<<0)
#define SEQLEN1             (0x00U)
#define CR2_ADON            (1U<<0)
#define CR2_SWSTART         (1U<<30)
#define SR_EOC              (1U<<1)
#define CR2_CONT            (1U<<1)
#define CR1_EOCIE           (1U<<5)

void PA4_ADC_INIT(void);
void Start_Conversion(void);
uint32_t ADC_Read(void);
void Start_Conversion_Continous(void);
void PA4_ADC_INTERRUPT_INIT(void);

#endif