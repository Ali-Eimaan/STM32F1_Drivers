#include "I2C.h"

void I2C1_init(void)
{
    RCC->APB2ENR |= GPIOBEN;
    RCC->APB1ENR |= I2C1EN;

    GPIOB->CRL |= PB6SCL;
    GPIOB->CRL |= PB7SDA;

    I2C1->CR1 |= I2CSWRST;
    I2C1->CR1 &= ~I2CSWRST;
    I2C1->CR2 |= I2CFREQ;
    I2C1->CCR = I2C100kHz;
    I2C1->TRISE = I2CTRISE;
    I2C1->CR1 |= I2CPE;
}

void I2C1_Slave_init_Interrupt(void)
{
    RCC->APB2ENR |= GPIOBEN;
    RCC->APB1ENR |= I2C1EN;

    GPIOB->CRL |= PB6SCL;
    GPIOB->CRL |= PB7SDA;

    I2C1->CR1 |= I2CSWRST;
    I2C1->CR1 &= ~I2CSWRST;
    I2C1->CR2 |= I2CFREQ;
    I2C1->CR2 |= ITEVTEN;

    I2C1->OVR1 |= SLAVEADDR;
    I2C1->CCR = I2C100kHz;
    I2C1->TRISE = I2CTRISE;
    I2C1->CR1 |= I2CPE;

    NVIC_EnableIRQ(I2C1_EV);
}

void I2C_addrbyteread(char saddr, char maddr, char* data)
{
    volatile int tmp;
    while(I2C1->SR2 & I2CBUSY);

    I2C1->CR1 |= I2CSTART;
    while(!(I2C1->SR1 & I2CSB));

    I2C1->DR = saddr << 1;
    while(!(I2C1->SR1 & I2CSRADDR));

    tmp = I2C1->SR2;
    while(!(I2C1->SR1 & I2CTXE));

    I2C1->DR = maddr;
    while(!(I2C1->SR1 & I2CTXE));

    I2C1->CR1 |= I2CSTART;
    while(!(I2C1->SR1 & I2CSB));

    I2C1->DR = saddr << 1 | 1;
    while(!(I2C1->SR1 & I2CSRADDR));

    tmp = I2C1->SR2;
    I2C1->CR1 &= ~I2CACK;
    I2C1->CR1 |= I2CSTOP;

    while(!(I2C1->SR1 & I2CRXNE));
    *data++ = I2C1->DR;
}

void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{
    volatile int tmp;
    while(I2C1->SR2 & I2CBUSY);

    I2C1->CR1 |= I2CSTART;
    while(!(I2C1->SR1 & I2CSB));

    I2C1->DR = saddr << 1;
    while(!(I2C1->SR1 & I2CSRADDR));

    tmp = I2C1->SR2;
    while(!(I2C1->SR1 & I2CTXE));

    I2C1->DR = maddr;
    while(!(I2C1->SR1 & I2CTXE));

    I2C1->CR1 |= I2CSTART;
    while(!(I2C1->SR1 & I2CSB));

    I2C1->DR = saddr << 1 | 1;
    while(!(I2C1->SR1 & I2CSRADDR));

    tmp = I2C1->SR2;
    I2C1->CR1 |= I2CACK;

    while(n > 0U)
    {
        if(n == 1)
        {
            I2C1->CR1 &= ~I2CACK;
            I2C1->CR1 |= I2CSTOP;

            while(!(I2C1->SR1 & I2CRXNE));
            *data++ = I2C1->DR;
            break;
        }
        else
        {
            while(!(I2C1->SR1 & I2CRXNE));
            *data++ = I2C1->DR;
            n--;
        }
    }
}

void I2C1_burstWrite(char saddr, char maddr, int n, char* data)
{
    volatile int tmp;
    while(I2C1->SR2 & I2CBUSY);

    I2C1->CR1 |= I2CSTART;
    while(!(I2C1->SR1 & I2CSB));

    I2C1->DR = saddr << 1;
    while(!(I2C1->SR1 & I2CSRADDR));

    tmp = I2C1->SR2;
    while(!(I2C1->SR1 & I2CTXE));

    I2C1->DR = maddr;
    for (int i = 0; i < n; i++)
    {
        while(!(I2C1->SR1 & I2CTXE));
        I2C1->DR = *data++;
    }
    while(!(I2C1->SR1 & I2CBTF));
    I2C1->CR1 |= I2CSTOP;
}

void I2C1_Write(char saddr, int n, char* data)
{
    volatile int tmp;
    while(I2C1->SR2 & I2CBUSY);

    I2C1->CR1 |= I2CSTART;
    while(!(I2C1->SR1 & I2CSB));

    I2C1->DR = saddr << 1;
    while(!(I2C1->SR1 & I2CSRADDR));

    tmp = I2C1->SR2;
    while(!(I2C1->SR1 & I2CTXE));

    for (int i = 0; i < n; i++)
    {
        while(!(I2C1->SR1 & I2CTXE));
        I2C1->DR = *data++;
    }
    while(!(I2C1->SR1 & I2CBTF));
    I2C1->CR1 |= I2CSTOP;
}

void I2C1_Read(char saddr, int n, char* data)
{
    volatile int tmp;
    while(I2C1->SR2 & I2CBUSY);

    I2C1->CR1 |= I2CSTART;
    while(!(I2C1->SR1 & I2CSB));

    I2C1->DR = saddr << 1 | 1;
    while(!(I2C1->SR1 & I2CSRADDR));

    tmp = I2C1->SR2;
    I2C1->CR1 |= I2CACK;

    while(n > 0U)
    {
        if(n == 1)
        {
            I2C1->CR1 &= ~I2CACK;
            I2C1->CR1 |= I2CSTOP;

            while(!(I2C1->SR1 & I2CRXNE));
            *data++ = I2C1->DR;
            break;
        }
        else
        {
            while(!(I2C1->SR1 & I2CRXNE));
            *data++ = I2C1->DR;
            n--;
        }
    }
}

void I2C1_SLave_Write(char saddr, int n, char* data)
{
    volatile int tmp;
    while(I2C1->SR2 & I2CBUSY);

    I2C1->CR1 |= I2CACK;

    for (int i = 0; i < n; i++)
    {
        while(!(I2C1->SR1 & I2CTXE));
        I2C1->DR = *data++;
    }
    while(!(I2C1->SR1 & I2CBTF));
    I2C1->CR1 |= I2CSTOP;
}

void I2C1_Slave_Read(int n, char* data)
{
    volatile int tmp;
    while(I2C1->SR2 & I2CBUSY);

    I2C1->CR1 |= I2CACK;

    while(n > 0U)
    {
        if(n == 1)
        {
            I2C1->CR1 &= ~I2CACK;
            I2C1->CR1 |= I2CSTOP;

            while(!(I2C1->SR1 & I2CRXNE));
            *data++ = I2C1->DR;
            break;
        }
        else
        {
            while(!(I2C1->SR1 & I2CRXNE));
            *data++ = I2C1->DR;
            n--;
        }
    }
}