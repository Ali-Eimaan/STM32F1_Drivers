#ifndef I2C_H_
#define I2C_H_

#include "stm32f1xx.h"

#define SPI1EN                      (1U<<12)
#define GPIOAEN                     (1U<<2)

#define SCLKPA5H                    ((1U<<20) | (1U<<21) | (1U<<23)) 
#define SCLKPA5L                    (1U<<22) 
#define MISOPA6H                    (1U<<27)
#define MISOPA6L                    ((1U<<24) | (1U<<25) | (1U<<26))
#define MOSIPA7H                    ((1U<<28) | (1U<<29) | (1U<<31))
#define MOSIPA7L                    (1U<<30)
#define NSSPA4H                     ((1U<<16) | (1U<<17))
#define NSSPA4L                     ((1U<<18) | (1U<<19))

#define CPHA                        (1U<<0)
#define CPOL                        (1U<<1)
#define FULLDUPLEX                  (1U<<10)
#define DATAFORMAT                  (1U<<7)
#define MASTEREN                    (1U<<2)
#define DATAFRAME                   (1U<<11)
#define SPIEN                       (1U<<6)
#define NSSCONF                     ((1U<<8) | (1U<<9))
#define BAUDRATE                    ((1U<<3) | (1U<<4) | (1U<<5))

#define TXE                         (1U<<1)
#define BUSY                        (1U<<7)
#define RXNE                        (1U<<0)
#define CSPIN                       (1U<<4)

enum CS_State
{
    High,
    Low
};

void SPI_GPIO_init(void);
void SPI_Config(void);
void SPI1_Transmit(uint8_t *data, uint32_t size);
void SPI1_Receive(uint8_t *data, uint32_t size);
void CS_Enable(uint8_t state);

#endif