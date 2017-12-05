#ifndef __RTOS_H
#define __RTOS_H
#include "stm32f1xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"
extern TaskHandle_t xHandler_LED1;
extern TaskHandle_t xHandler_LED2;
extern TaskHandle_t xHandler_Key1;
extern TaskHandle_t xHandler_Key2;
extern  uint32_t ulHighFrequencyTimerTicks;
extern TIM_HandleTypeDef htim6;
void LEDTask1(void *Parameters);

void LEDTask2(void *Parameters);

void Key1(void *Parameters);

void Key2(void *Parameters);
void mTaskCreate(void);


#endif
