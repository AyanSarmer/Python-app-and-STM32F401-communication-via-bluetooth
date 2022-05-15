#include "Serial.h"

volatile uint8_t receivedByte[2], byteNum = 0;

void USART2_IRQHandler(void)
{  
    receivedByte[byteNum] = USART2->DR;
	byteNum++;
    if(byteNum > 1)
    {
        byteNum = 0;
        if(receivedByte[0] == CH1)
        {
            TIM3->CCR1 = receivedByte[1];
        }
        else if(receivedByte[0] == CH3)
        {
            TIM3->CCR3 = receivedByte[1];
        }
        else if(receivedByte[0] == CH4)
        {
            TIM3->CCR4 = receivedByte[1];
        }
    }
}

void serialBegin(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER2_1;
    GPIOA->AFR[0] |= (7 << 8);
    GPIOA->MODER |= GPIO_MODER_MODER3_1;
    GPIOA->AFR[0] |= (7 << 12);

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = BRR_VALUE;
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    while(!(USART2->SR & USART_SR_TXE));
    NVIC_EnableIRQ(USART2_IRQn);
}

void serialSendByte(char data)
{
    while (!(USART2->SR & USART_SR_TC));
    USART2->DR = data;
}

void serialPrintln(char* buff)
{
    while(*buff != '\0')
	{
		serialSendByte(*buff);
		buff++;
	}
	serialSendByte('\n');
}