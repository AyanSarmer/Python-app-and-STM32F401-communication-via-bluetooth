#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"
#include "adc.h"

#define PSC_VALUE          300
#define ARR_VALUE          255 
#define CCR_INIT_VALUE     0

#define TIM_COUNTER_MAX    100

void timerInit(void);

#endif /* TIMER_H_ */