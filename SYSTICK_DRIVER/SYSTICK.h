#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stdint.h"
#include "stm32f1xx.h"

#define SYSTICK_LOAD                (8000)
#define CSR_EN                      (1U<<0)
#define CSR_CLKSRC                  (1U<<2)
#define CSR_COUNTFLAG               (1U<<16)
#define ONE_SEC_LOAD                (8000000)
#define CSR_TICKINT                 (1U<<1)

void SYSTICK_DelayMS(int delay);
void SYSTICK_1Hz_Interrupt(void);

#endif
