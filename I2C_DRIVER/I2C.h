#ifndef I2C_H_
#define I2C_H_

#include "stm32f1xx.h"

#define GPIOBEN                 (1U<<3)
#define PB6SCL                  (1U<<24 | 1U<<25 | 1U<<26 | 1U<<27)
#define PB7SDA                  (1U<<28 | 1U<<29 | 1U<<30 | 1U<<31)

#define I2C1EN                  (1U<<21)
#define I2CSWRST                (1U<<15)
#define I2CFREQ                 (8U<<0)
#define I2CPE                   (1U<<0)
#define I2C100kHz               (40<<0)
#define I2CTRISE                (9)

#define I2CBUSY                 (1U<<1)
#define I2CSTART                (1U<<8)
#define I2CSB                   (1U<<0)
#define I2CSRADDR               (1U<<1)
#define I2CTXE                  (1U<<7)
#define I2CACK                  (1U<<10)
#define I2CRXNE                 (1U<<6)
#define I2CSTOP                 (1U<<9)
#define I2CBTF                  (1U<<2)

#define I2CITEVTEN              (1U<<9)
#define I2CSLAVEADDR            (78<<1)
#define I2CENGC                 (1U<<6)

void I2C1_Read(char saddr, int n, char* data);
void I2C1_Write(char saddr, int n, char* data);

void I2C1_init(void);
void I2C_addrbyteread(char saddr, char maddr, char* data);
void I2C1_burstRead(char saddr, char maddr, int n, char* data);
void I2C1_burstWrite(char saddr, char maddr, int n, char* data);

void I2C1_Slave_init_Interrupt(void);
void I2C1_SLave_Write(int n, char* data);
void I2C1_Slave_Read(int n, char* data);

#endif
