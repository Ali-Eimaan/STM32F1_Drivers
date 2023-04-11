#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f1xx.h"

typedef enum 
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF,
    PORTG
}PORTS_Type;

typedef enum 
{
    pSPI1,
    pI2C1,
    pUSART1,
    pUSART2,
    pUSART3,
    pTIM1 = 6,
    pTIM2 = 8,
    pTIM3 = 10,
    pTIM4 = 12,
    pCAN,
    pPD01 = 15,
    pTIM5CH4,
    pADC1ETRGINJ,
    pADC1ETRGREG,
    pADC2ETRGINJ,
    pADC2ETRGREG,
    pSWJCFG = 24
}PERIPHERERALS_Type;

typedef enum
{
    NoRemap,
    PartialRemap,
    PartialRemap1,
    FullRemap
}REMAP_Type;

typedef enum
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15
}PINS_Type;

typedef enum 
{
    LOW,
    HIGH
}PinState_Type;

typedef enum CNF_Type
{
    AnalogInput,
    FloatingInput,
    Input_Pullup_PullDown,

    GeneralPurposePushPull = 0,
    GeneralPurposeOpenDrain,
    AlternateFunctionPushPull,
    AlternateFunctionOpenDrain
}CNF_Type;

typedef enum Modes_Type
{
    InputMode,
    OutputMode10MHz,
    OutputMode2MHz,
    OutputMode50MHz
}Modes_Type;

PinState_Type ReadPin(GPIO_TypeDef *GPIOx, PINS_Type Pin);
void ResetPin(GPIO_TypeDef *GPIOx, PINS_Type Pin);
void TogglePin(GPIO_TypeDef *GPIOx, PINS_Type Pin);
void SetPinMode(GPIO_TypeDef *GPIOx, PORTS_Type Port, PINS_Type Pin, Modes_Type Mode, CNF_Type Cnf);
void WritePin(GPIO_TypeDef *GPIOx, PINS_Type Pin, PinState_Type State);
void LockPin(GPIO_TypeDef *GPIOx, PINS_Type Pin, uint32_t LockState);
void GPIO_Remap(PERIPHERERALS_Type Periphererals, REMAP_Type Remap);
void EXTI_Init(PINS_Type Pin, PORTS_Type Port);

#endif