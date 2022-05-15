#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"

void adcInit(void);
void adcStartConversion(void);

extern volatile unsigned char adcFlag;
extern volatile uint32_t adcPreviousValue, adcValue;

#endif /* ADC_H_ */