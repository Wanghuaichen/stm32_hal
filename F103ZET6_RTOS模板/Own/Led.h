#ifndef __led_H
#define __led_H

#include "stm32f1xx_hal.h"


#define LEDR_PIN GPIO_PIN_5
#define LEDB_PIN GPIO_PIN_1
#define LEDG_PIN GPIO_PIN_0
#define LED_PORT  GPIOB

#define ON       1
#define OFF      0

#define LEDG(state) if(state)\
                        HAL_GPIO_WritePin(LED_PORT,LEDG_PIN,GPIO_PIN_RESET);\
                    else HAL_GPIO_WritePin(LED_PORT,LEDG_PIN,GPIO_PIN_SET);
#define LEDB(state) if(state)\
                        HAL_GPIO_WritePin(LED_PORT,LEDB_PIN,GPIO_PIN_RESET);\
                    else HAL_GPIO_WritePin(LED_PORT,LEDB_PIN,GPIO_PIN_SET);
#define LEDR(state) if(state)\
                    HAL_GPIO_WritePin(LED_PORT,LEDR_PIN,GPIO_PIN_RESET);\
                    else HAL_GPIO_WritePin(LED_PORT,LEDR_PIN,GPIO_PIN_SET);
#define LEDG_TOGGLE  HAL_GPIO_TogglePin(LED_PORT,LEDG_PIN);
#define LEDB_TOGGLE  HAL_GPIO_TogglePin(LED_PORT,LEDB_PIN);
#define LEDR_TOGGLE  HAL_GPIO_TogglePin(LED_PORT,LEDR_PIN);




#endif
