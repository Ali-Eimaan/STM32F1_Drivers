#ifndef I2C_H_
#define I2C_H_

#include "stm32f1xx.h"
#include "GPIO.h"

#define T_RISE_SCL_SM           (1000)
#define T_HIGH_SCL_SM           (4000)
#define T_RISE_SCL_FM           (300)
#define T_HIGH_SCL_FM           (600)
#define T_PCLK                  (125)
#define CLK_100Khz              ((T_RISE_SCL_SM + T_HIGH_SCL_SM)/T_PCLK)
#define CLK_400Khz              ((T_RISE_SCL_FM + T_HIGH_SCL_FM)/T_PCLK)
#define I2CSLAVEADDR            (78<<1)
#define I2CTRISE                (9)

typedef enum 
{
    Remap_Disable,
    Remap_Enable
}RemapEnable_Type;

void I2C_Read(I2C_TypeDef *I2Cx, char saddr, int n, char* data);
void I2C_Write(I2C_TypeDef *I2Cx, char saddr, int n, char* data);

void I2C_init(I2C_TypeDef *I2Cx, RemapEnable_Type remap, uint32_t Clock);
void I2C_addrbyteread(I2C_TypeDef *I2Cx, char saddr, char maddr, char* data);
void I2C_burstRead(I2C_TypeDef *I2Cx, char saddr, char maddr, int n, char* data);
void I2C_burstWrite(I2C_TypeDef *I2Cx, char saddr, char maddr, int n, char* data);

void I2C_Slave_init_Interrupt(I2C_TypeDef *I2Cx, RemapEnable_Type remap, uint32_t Clock);
void I2C_Slave_Write(I2C_TypeDef *I2Cx, int n, char* data);
void I2C_Slave_Read(I2C_TypeDef *I2Cx, int n, char* data);

#endif
