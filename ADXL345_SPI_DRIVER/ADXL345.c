#include "ADXL345.h"

uint8_t ADXL_ReadAddr(uint8_t reg)
{
    uint8_t RegVal;
    reg |= READOPERATION;
    reg |= MULTIBYTEEN;
    CS_Enable(Low);
    SPI1_Transmit(reg, 1);
    SPI1_Receive(RegVal, 1);
    return RegVal;
}

void ADXL_Write(uint8_t reg, uint8_t value)
{
    uint8_t data[2];
    data[0] = reg | MULTIBYTEEN;
    data[1] = value;
    CS_Enable(Low);
    SPI1_Transmit(data, sizeof(data));
    CS_Enable(High);
}

void ADXL_Read(uint8_t reg, uint8_t* Data)
{
    reg |= READOPERATION;
    reg |= MULTIBYTEEN;
    CS_Enable(Low);
    SPI1_Transmit(reg, 1);
    SPI1_Receive(Data, sizeof(Data));
    CS_Enable(High);
}

void ADXL_init(void)
{
    SPI_GPIO_init();
    SPI_Config();
    ADXL_ReadAddr(ADXL345ID);
    ADXL_Write(DATAFORMAT, FOUR_G);
    ADXL_Write(PWRCTRL, RESET);
    ADXL_Write(PWRCTRL, SETMEASUREMENT);
}
