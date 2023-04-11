#include "SPI.h"

void SPI_GPIO_init(void)
{
    RCC->APB2ENR |= GPIOAEN;

    GPIOA->CRL |= NSSPA4H;
    GPIOA->CRL |= SCLKPA5H;
    GPIOA->CRL |= MISOPA6H;
    GPIOA->CRL |= MOSIPA7H;

    GPIOA->CRL |= NSSPA4L;
    GPIOA->CRL |= SCLKPA5L;
    GPIOA->CRL |= MISOPA6L;
    GPIOA->CRL |= MOSIPA7L;
}

void SPI_Config(void)
{
    RCC->APB2ENR |= SPI1EN;

    SPI1->CR1 &= ~BAUDRATE;
    SPI1->CR1 &= ~DATAFRAME;
    SPI1->CR1 &= ~FULLDUPLEX;
    SPI1->CR1 &= ~DATAFORMAT;

    SPI1->CR1 |= CPHA;
    SPI1->CR1 |= CPOL;
    SPI1->CR1 |= NSSCONF;
    SPI1->CR1 |= MASTEREN;
    SPI1->CR1 |= SPIEN;
}

void SPI1_Transmit(uint8_t *data, uint32_t size)
{
    uint32_t i = 0;
    uint8_t tmp;

    for (int i = 0; i < size; i++)
    {
        while (!(SPI1->SR & TXE));
        SPI1->DR = data[i];
    }

    while (!(SPI1->SR & TXE));
    while (SPI1->SR & BUSY);

    tmp = SPI1->DR;
    tmp = SPI1->SR;
}

void SPI1_Receive(uint8_t *data, uint32_t size)
{
    while (size)
    {
        SPI1->DR = 0;
        while (!(SPI1->SR & RXNE));
        *data++ = SPI1->DR;
        size--;
    }
}

void CS_Enable(uint8_t state)
{
    if (state == Low)
        GPIOA->ODR &= ~CSPIN;
    if (state == High)
        GPIOA->ODR |= CSPIN;
}