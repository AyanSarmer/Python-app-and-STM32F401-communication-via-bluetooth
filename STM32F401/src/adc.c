#include "adc.h"

volatile unsigned char adcFlag = 0;
volatile uint32_t adcPreviousValue, adcValue;

void ADC_IRQHandler()
{
    if(ADC1->SR & ADC_SR_EOC)
    {        
        ADC1->SR &= ~ADC_SR_EOC;
        adcValue = ADC1->DR;
        if(adcPreviousValue != adcValue)
        {     
            adcPreviousValue = adcValue;
            adcFlag = 1;
        }
    }
}

void adcInit(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER4;

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC1->SQR3 |= ADC_SQR3_SQ1_2;
    ADC1->CR1 |= ADC_CR1_RES_1 | ADC_CR1_EOCIE;
    ADC1->CR2 |= ADC_CR2_ADON;
    NVIC_EnableIRQ(ADC_IRQn);
}

void adcStartConversion(void)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;
}