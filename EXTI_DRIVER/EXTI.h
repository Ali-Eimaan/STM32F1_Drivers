#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f1xx.h"

#define GPIOAEN                 (1U<<2)
#define AFIOEN                  (1U<<0)
#define LINE8                   (1U<<8)

void PA8_EXTI_INIT(void);

#endif