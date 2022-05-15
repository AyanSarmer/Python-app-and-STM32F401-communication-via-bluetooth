#include "device.h"

void deviceInit() 
{
    adcInit();
    timerInit();    
    serialBegin();      
}

void deviceControl()
{     
    if(adcFlag)
    {
        adcFlag = 0;
        serialSendByte((unsigned char)adcValue);                 
    }
}