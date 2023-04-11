#ifndef ADXL345_H_
#define ADXL345_H_

#include "I2C.h"

#define ADXL345ID                   0x00
#define ADXLADDR                    0x53
#define DATAFORMAT                  0x31
#define PWRCTRL                     0x2D
#define DATASTART                   0x32

#define FOUR_G                      0x01
#define RESET                       0x00
#define SETMEASUREMENT              0x08

void ADXL_init(void);
void ADXL_Read(uint8_t reg, uint8_t* Data);
void ADXL_Write(uint8_t reg, uint8_t value);
uint8_t ADXL_ReadAddr(uint8_t reg);

#endif
