#include "I2C.h"

void I2C_init(I2C_TypeDef *I2Cx, RemapEnable_Type remap, uint32_t Clock)
{
    if (I2Cx == I2C1)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        if (remap)
        {
            SetPinMode(GPIOB, PORTB, PIN6, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOB, PORTB, PIN7, OutputMode50MHz, AlternateFunctionOpenDrain);
        }
        else
        {
            SetPinMode(GPIOB, PORTB, PIN8, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOB, PORTB, PIN9, OutputMode50MHz, AlternateFunctionOpenDrain);
        }
    }

    if (I2Cx == I2C2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

        SetPinMode(GPIOB, PORTB, PIN10, OutputMode50MHz, AlternateFunctionOpenDrain);
        SetPinMode(GPIOB, PORTB, PIN11, OutputMode50MHz, AlternateFunctionOpenDrain);
    }
    
    I2Cx->CR1 |= I2C_CR1_SWRST;
    I2Cx->CR1 &= ~I2C_CR1_SWRST;
    I2Cx->CR2 |= I2C_CR2_FREQ_3;
    I2Cx->CCR = Clock;
    I2Cx->TRISE = I2CTRISE;
    I2Cx->CR1 |= I2C_CR1_PE;
}

void I2C_Slave_init_Interrupt(I2C_TypeDef *I2Cx, RemapEnable_Type remap, uint32_t Clock)
{
    if (I2Cx == I2C1)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        if (remap)
        {
            SetPinMode(GPIOB, PORTB, PIN6, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOB, PORTB, PIN7, OutputMode50MHz, AlternateFunctionOpenDrain);
        }
        else
        {
            SetPinMode(GPIOB, PORTB, PIN8, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOB, PORTB, PIN9, OutputMode50MHz, AlternateFunctionOpenDrain);
        }
    }

    if (I2Cx == I2C2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

        SetPinMode(GPIOB, PORTB, PIN10, OutputMode50MHz, AlternateFunctionOpenDrain);
        SetPinMode(GPIOB, PORTB, PIN11, OutputMode50MHz, AlternateFunctionOpenDrain);
    }

    I2Cx->CR1 |= I2C_CR1_SWRST;
    I2Cx->CR1 &= ~I2C_CR1_SWRST;
    I2Cx->CR2 |= I2C_CR2_FREQ_3;
    I2Cx->CR2 |= I2C_CR2_ITEVTEN;

    I2Cx->OAR1 |= I2CSLAVEADDR;
    I2Cx->CCR = Clock;
    I2Cx->TRISE = I2CTRISE;
    I2Cx->CR1 |= I2C_CR1_PE;

    if (I2Cx == I2C1)
        NVIC_EnableIRQ(I2C1_EV_IRQn);
    if (I2Cx == I2C2)
        NVIC_EnableIRQ(I2C2_EV_IRQn);
}

void I2C_addrbyteread(I2C_TypeDef *I2Cx, char saddr, char maddr, char* data)
{
    volatile int tmp;
    while(I2Cx->SR2 & I2C_SR2_BUSY);

    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));

    I2Cx->DR = saddr << 1;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));

    tmp = I2Cx->SR2;
    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    I2Cx->DR = maddr;
    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));

    I2Cx->DR = saddr << 1 | 1;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));

    tmp = I2Cx->SR2;
    I2Cx->CR1 &= ~I2C_CR1_ACK;
    I2Cx->CR1 |= I2C_CR1_STOP;

    while(!(I2Cx->SR1 & I2C_SR1_RXNE));
    *data++ = I2Cx->DR;
}

void I2C_burstRead(I2C_TypeDef *I2Cx, char saddr, char maddr, int n, char* data)
{
    volatile int tmp;
    while(I2Cx->SR2 & I2C_SR2_BUSY);

    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));

    I2Cx->DR = saddr << 1;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));

    tmp = I2Cx->SR2;
    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    I2Cx->DR = maddr;
    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));

    I2Cx->DR = saddr << 1 | 1;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));

    tmp = I2Cx->SR2;
    I2Cx->CR1 |= I2C_CR1_ACK;

    while(n > 0U)
    {
        if(n == 1)
        {
            I2Cx->CR1 &= ~I2C_CR1_ACK;
            I2Cx->CR1 |= I2C_CR1_STOP;

            while(!(I2Cx->SR1 & I2C_SR1_RXNE));
            *data++ = I2Cx->DR;
            break;
        }
        else
        {
            while(!(I2Cx->SR1 & I2C_SR1_RXNE));
            *data++ = I2Cx->DR;
            n--;
        }
    }
}

void I2C_burstWrite(I2C_TypeDef *I2Cx, char saddr, char maddr, int n, char* data)
{
    volatile int tmp;
    while(I2Cx->SR2 & I2C_SR2_BUSY);

    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));

    I2Cx->DR = saddr << 1;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));

    tmp = I2Cx->SR2;
    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    I2Cx->DR = maddr;
    for (int i = 0; i < n; i++)
    {
        while(!(I2Cx->SR1 & I2C_SR1_TXE));
        I2Cx->DR = *data++;
    }
    while(!(I2Cx->SR1 & I2C_SR1_BTF));
    I2Cx->CR1 |= I2C_CR1_STOP;
}

void I2C_Write(I2C_TypeDef *I2Cx, char saddr, int n, char* data)
{
    volatile int tmp;
    while(I2Cx->SR2 & I2C_SR2_BUSY);

    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));

    I2Cx->DR = saddr << 1;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));

    tmp = I2Cx->SR2;
    while(!(I2Cx->SR1 & I2C_SR1_TXE));

    for (int i = 0; i < n; i++)
    {
        while(!(I2Cx->SR1 & I2C_SR1_TXE));
        I2Cx->DR = *data++;
    }
    while(!(I2Cx->SR1 & I2C_SR1_BTF));
    I2Cx->CR1 |= I2C_CR1_STOP;
}

void I2C_Read(I2C_TypeDef *I2Cx, char saddr, int n, char* data)
{
    volatile int tmp;
    while(I2Cx->SR2 & I2C_SR2_BUSY);

    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));

    I2Cx->DR = saddr << 1 | 1;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));

    tmp = I2Cx->SR2;
    I2Cx->CR1 |= I2C_CR1_ACK;

    while(n > 0U)
    {
        if(n == 1)
        {
            I2Cx->CR1 &= ~I2C_CR1_ACK;
            I2Cx->CR1 |= I2C_CR1_STOP;

            while(!(I2Cx->SR1 & I2C_SR1_RXNE));
            *data++ = I2Cx->DR;
            break;
        }
        else
        {
            while(!(I2Cx->SR1 & I2C_SR1_RXNE));
            *data++ = I2Cx->DR;
            n--;
        }
    }
}

void I2C_Slave_Write(I2C_TypeDef *I2Cx, int n, char* data)
{
    volatile int tmp;
    while(I2Cx->SR2 & I2C_SR2_BUSY);

    I2Cx->CR1 |= I2C_CR1_ACK;

    for (int i = 0; i < n; i++)
    {
        while(!(I2Cx->SR1 & I2C_SR1_TXE));
        I2Cx->DR = *data++;
    }
    while(!(I2Cx->SR1 & I2C_SR1_BTF));
    I2Cx->CR1 |= I2C_CR1_STOP;
}

void I2C_Slave_Read(I2C_TypeDef *I2Cx, int n, char* data)
{
    volatile int tmp;
    while(I2Cx->SR2 & I2C_SR2_BUSY);

    I2Cx->CR1 |= I2C_CR1_ACK;

    while(n > 0U)
    {
        if(n == 1)
        {
            I2Cx->CR1 &= ~I2C_CR1_ACK;
            I2Cx->CR1 |= I2C_CR1_STOP;

            while(!(I2Cx->SR1 & I2C_SR1_RXNE));
            *data++ = I2Cx->DR;
            break;
        }
        else
        {
            while(!(I2Cx->SR1 & I2C_SR1_RXNE));
            *data++ = I2Cx->DR;
            n--;
        }
    }
}