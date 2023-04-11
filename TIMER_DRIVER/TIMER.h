#ifndef TIMER_H_
#define TIMER_H_

#include "stdint.h"
#include "stm32f1xx.h"

#define TIM4EN              (1U<<2)
#define TIM1EN              (1U<<11)
#define CR1_CEN             (1U<<0)
#define SR_UIF              (1U<<0)
#define OC_TOGGLE           ((1U<<4) | (1U<<5))
#define CCMR1_CC1S          (1U<<0)
#define CCRR_CC3E           (1U<<8)
#define CCRR_CC1E           (1U<<0)
#define GPIOBEN             (1U<<3)
#define GPIOAEN             (1U<<2)
#define SR_CCI1F            (1U<<1)
#define DIER_UIE            (1U<<0)

void tim4_1hz_init(void);
void tim4_PB8_output_compare(void);
void tim1_PA8_input_capture(void);
void tim4_1hz_interrupt(void);

#endif