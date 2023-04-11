#include "ADXL345.h"

uint8_t ADXL_ReadAddr(uint8_t reg)
{
    char data;
    I2C_byteread(ADXLADDR, reg, &data);
    return data;
}

void ADXL_Write(uint8_t reg, uint8_t value)
{
    I2C1_burstWrite(ADXLADDR, reg, 1, (char*)&value);
}

void ADXL_Read(uint8_t reg, uint8_t* Data)
{
    I2C1_burstRead(ADXLADDR, reg, sizeof(Data), (char*)Data);
}

void ADXL_init(void)
{
    I2C1_init();
    ADXL_ReadAddr(ADXL345ID);
    ADXL_Write(DATAFORMAT, FOUR_G);
    ADXL_Write(PWRCTRL, RESET);
    ADXL_Write(PWRCTRL, SETMEASUREMENT);
}
