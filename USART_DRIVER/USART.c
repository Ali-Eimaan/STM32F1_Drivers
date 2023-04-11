#include "USART.h"

static uint16_t compute_baud_rate(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

static void USART_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = compute_baud_rate(PeriphClk, BaudRate);
}

USART_StatusTypedef USART_Init(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params, uint32_t Baud_Rate, REMAP_Type remap)
{
    if (USARTx == USART1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        if (remap)
        {
            SetPinMode(GPIOB, PORTB, PIN6, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOB, PORTB, PIN7, InputMode, FloatingInput);
        }
        else
        {
            SetPinMode(GPIOA, PORTA, PIN9, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOA, PORTA, PIN10, InputMode, FloatingInput);
        }
    }
    else if (USARTx == USART2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
        if (remap)
        {
            SetPinMode(GPIOD, PORTD, PIN5, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOD, PORTD, PIN6, InputMode, FloatingInput);
        }
        else
        {
            SetPinMode(GPIOA, PORTA, PIN2, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOA, PORTA, PIN3, InputMode, FloatingInput);
        }
    }
    else if (USARTx == USART3)
    {
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
        if (remap == NoRemap)
        {
            SetPinMode(GPIOB, PORTB, PIN10, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOB, PORTB, PIN11, InputMode, FloatingInput);
        }
        else if (remap == PartialRemap)
        {
            SetPinMode(GPIOC, PORTC, PIN10, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOC, PORTC, PIN11, InputMode, FloatingInput);
        }
        else if (remap == FullRemap)
        {
            SetPinMode(GPIOD, PORTD, PIN8, OutputMode50MHz, AlternateFunctionOpenDrain);
            SetPinMode(GPIOD, PORTD, PIN9, InputMode, FloatingInput);
        }
    }

    USART_set_baudrate(USARTx, APB2_CLK, Baud_Rate);

    Set_USART_Params(USARTx, USART_Params);

    if ((USARTx->CR1 & USART_CR1_IDLEIE) || (USARTx->CR1 & USART_CR1_RXNEIE) || (USARTx->CR1 & USART_CR1_TCIE) || (USARTx->CR1 & USART_CR1_TXEIE) || (USARTx->CR1 & USART_CR1_PEIE))
    {
        if (USARTx == USART1)
            NVIC_EnableIRQ(USART1_IRQn);
        else if (USARTx == USART2)
            NVIC_EnableIRQ(USART2_IRQn);
        else if (USARTx == USART3)
            NVIC_EnableIRQ(USART3_IRQn);
    }

    USARTx->CR1 = (USART_CR1_TE | USART_CR1_RE);
    USARTx->CR1 |= USART_CR1_UE;

    return (Read_USART_Status(USARTx));
}

void USART_write(USART_TypeDef *USARTx, int ch)
{
    while(!(USARTx->SR & USART_SR_TXE));
    USARTx->DR = (ch & 0xFF);
}

int __io_putchar(USART_TypeDef *USARTx, int ch)
{
    USART_write(USARTx, ch);
    return ch;
}

char USART_read(USART_TypeDef *USARTx)
{
    while(!(USARTx->SR & USART_SR_RXNE));
    return USARTx->DR;
}

USART_StatusTypedef USART_Write_Buff(USART_TypeDef *USARTx, uint8_t *Buff, uint16_t len)
{
    for (int i = 0; i < len; i++)
        USART_write(USARTx, Buff[i]);
    return Read_USART_Status(USARTx);
}

USART_StatusTypedef USART_Read_Buff(USART_TypeDef *USARTx, uint8_t *Buff, uint16_t len)
{
    for (int i = 0; i < len; i++)
        Buff[i] = USART_read(USARTx);
    return Read_USART_Status(USARTx);
}

USART_StatusTypedef Read_USART_Status(USART_TypeDef *USARTx)
{
    if (USARTx->SR & USART_SR_PE)
        return Parity_Error;
    if (USARTx->SR & USART_SR_FE)
        return Framing_Error;
    if (USARTx->SR & USART_SR_NE)
        return Noise_Error;
    if (USARTx->SR & USART_SR_ORE)
        return Overrun_Error;
    else
        return Success;
}

void Set_USART_Params(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params)
{
    Set_CR1(USARTx, USART_Params);
    Set_CR2(USARTx, USART_Params);
    Set_CR3(USARTx, USART_Params);
}

void Set_CR1(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params)
{
    if (USART_Params.Send_Break)
        USARTx->CR1 |= USART_CR1_SBK;
    if (USART_Params.Receiver_Wakeup)
        USARTx->CR1 |= USART_CR1_RWU;
    if (USART_Params.Idle_Interrupt)
        USARTx->CR1 |= USART_CR1_IDLEIE;
    if (USART_Params.RXNE_Interrupt)
        USARTx->CR1 |= USART_CR1_RXNEIE;
    if (USART_Params.TxCplt_Interrupt)
        USARTx->CR1 |= USART_CR1_TCIE;
    if (USART_Params.TXE_Interrupt)
        USARTx->CR1 |= USART_CR1_TXEIE;
    if (USART_Params.PE_Interrupt)
        USARTx->CR1 |= USART_CR1_PEIE;
    if (USART_Params.Parity_Selection)
        USARTx->CR1 |= USART_CR1_PS;
    if (USART_Params.Parity_Ctrl)
        USARTx->CR1 |= USART_CR1_PCE;
    if (USART_Params.Wakeup_Method)
        USARTx->CR1 |= USART_CR1_WAKE;
    if (USART_Params.Word_Length_9)
        USARTx->CR1 |= USART_CR1_M;
}

void Set_CR2(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params)
{
    if (USART_Params.Break_Detection_Len)
        USARTx->CR2 |= USART_CR2_LBDL;
    if (USART_Params.Break_Detection_en)
        USARTx->CR2 |= USART_CR2_LBDIE;
    if (USART_Params.Last_Bit_Clk_Pulse)
        USARTx->CR2 |= USART_CR2_LBCL;
    if (USART_Params.Clock_Phase)
        USARTx->CR2 |= USART_CR2_CPHA;
    if (USART_Params.Clock_Polarity)
        USARTx->CR2 |= USART_CR2_CPOL;
    if (USART_Params.Clock_Enable)
        USARTx->CR2 |= USART_CR2_CLKEN;
    if (USART_Params.Lin_Mode)
        USARTx->CR2 |= USART_CR2_LINEN;
}

void Set_CR3(USART_TypeDef *USARTx, USART_ParamsTypedef USART_Params)
{
    if (USART_Params.Error_Interrupt)
        USARTx->CR3 |= USART_CR3_EIE;
    if (USART_Params.IrDA_Mode)
        USARTx->CR3 |= USART_CR3_IREN;
    if (USART_Params.IrDA_Low_PWR)
        USARTx->CR3 |= USART_CR3_IRLP;
    if (USART_Params.Half_Duplex_Selection)
        USARTx->CR3 |= USART_CR3_HDSEL;
    if (USART_Params.NACK_Enable)
        USARTx->CR3 |= USART_CR3_NACK;
    if (USART_Params.Smartcard_Enable)
        USARTx->CR3 |= USART_CR3_SCEN;
    if (USART_Params.DMA_Enable_RX)
        USARTx->CR3 |= USART_CR3_DMAR;
    if (USART_Params.DMA_Enable_TX)
        USARTx->CR3 |= USART_CR3_DMAT;
    if (USART_Params.RTS_Enable)
        USARTx->CR3 |= USART_CR3_RTSE;
    if (USART_Params.CTS_Enable)
        USARTx->CR3 |= USART_CR3_CTSE;
    if (USART_Params.CTS_Interrupt_Enable)
        USARTx->CR3 |= USART_CR3_CTSIE;
}