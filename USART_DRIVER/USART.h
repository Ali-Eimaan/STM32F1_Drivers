#ifndef USART_H_
#define USART_H_

#include "GPIO.h"
#include "stdio.h"
#include "stdint.h"
#include "stm32f1xx.h"

#define SYS_FREQ            8000000
#define APB2_CLK            SYS_FREQ

#define BAUDRATE            115200

typedef enum
{
    Parity_Error,
    Framing_Error,
    Noise_Error,
    Overrun_Error,
    Success
}USART_StatusTypedef;

typedef struct
{
    uint8_t Send_Break;
    uint8_t Receiver_Wakeup;
    uint8_t Idle_Interrupt;
    uint8_t RXNE_Interrupt;
    uint8_t TxCplt_Interrupt;
    uint8_t TXE_Interrupt;
    uint8_t PE_Interrupt;
    uint8_t Parity_Selection;
    uint8_t Parity_Ctrl;
    uint8_t Wakeup_Method;
    uint8_t Word_Length_9;

    uint8_t Break_Detection_Len;
    uint8_t Break_Detection_en;
    uint8_t Last_Bit_Clk_Pulse;
    uint8_t Clock_Phase;
    uint8_t Clock_Polarity;
    uint8_t Clock_Enable;
    uint8_t Lin_Mode;

    uint8_t Error_Interrupt;
    uint8_t IrDA_Mode;
    uint8_t IrDA_Low_PWR;
    uint8_t Half_Duplex_Selection;
    uint8_t NACK_Enable;
    uint8_t Smartcard_Enable;
    uint8_t DMA_Enable_RX;
    uint8_t DMA_Enable_TX;
    uint8_t RTS_Enable;
    uint8_t CTS_Enable;
    uint8_t CTS_Interrupt_Enable;
}USART_ParamsTypedef;

USART_StatusTypedef USART_Init(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params, uint32_t Baud_Rate);
void Set_USART_Params(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params);
void USART_write(USART_TypeDef *USARTx, int ch);
char USART_read(USART_TypeDef *USARTx);
static uint16_t compute_baud_rate(uint32_t PeriphClk, uint32_t BaudRate);
static void USART_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void Set_CR1(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params);
void Set_CR1(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params);
void Set_CR1(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params);
USART_StatusTypedef USART_Write_Buff(USART_TypeDef *USARTx, uint8_t *Buff, uint16_t len);
USART_StatusTypedef USART_Read_Buff(USART_TypeDef *USARTx, uint8_t *Buff, uint16_t len);

#endif
