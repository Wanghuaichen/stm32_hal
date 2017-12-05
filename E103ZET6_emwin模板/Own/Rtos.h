#ifndef __RTOS_H
#define __RTOS_H
#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "../Own/12864TXA.h"
#include "GUI.h"
extern TaskHandle_t xHandler_1;
extern TaskHandle_t xHandler_2;
extern TaskHandle_t xHandler_3;
extern TaskHandle_t xHandler_4;

extern volatile uint32_t ulHighFrequencyTimerTicks;





void mTaskCreate(void);


#endif
