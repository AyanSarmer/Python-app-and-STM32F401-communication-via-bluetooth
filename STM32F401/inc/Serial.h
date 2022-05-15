#ifndef SERIAL_H_
#define SERIAL_H_


#include "stm32f4xx.h"

#define BRR_VALUE             0x683
#define KEY                   'k'
#define CH1                   '1'
#define CH3                   '3'
#define CH4                   '4'

void serialBegin(void);
void serialSendByte(char data);
void serialPrintln(char* buff);

extern volatile uint8_t receivedByte[2], byteNum;

#endif /* SERIAL_H_ */