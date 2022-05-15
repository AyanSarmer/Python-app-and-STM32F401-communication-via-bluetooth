#include "timer.h"

volatile unsigned char timerCounter;

void TIM3_IRQHandler()
{
    TIM3->SR &= ~TIM_SR_UIF;
    timerCounter++;
    if(timerCounter == TIM_COUNTER_MAX)
    {
        timerCounter = 0;
        adcStartConversion();
    }    
}

void timerInit(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODER0_1;
    GPIOB->AFR[0] |= (2 << 0);
    GPIOB->MODER |= GPIO_MODER_MODER1_1;
    GPIOB->AFR[0] |= (2 << 4);    
    GPIOB->MODER |= GPIO_MODER_MODER4_1;
    GPIOB->AFR[0] |= (2 << 16); 

    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = PSC_VALUE;
    TIM3->ARR = ARR_VALUE;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CCR1 = CCR_INIT_VALUE;
    TIM3->CCR3 = CCR_INIT_VALUE;
    TIM3->CCR4 = CCR_INIT_VALUE;
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E;
    TIM3->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM3_IRQn);
}