#ifndef __key_H
#define __key_H

#include "stm32f1xx_hal.h"


extern uint8_t Key_Number;

typedef enum
{
    KEY_ON = 1,
    KEY_OFF = 0,
}KEY_STATE;


KEY_STATE key1_scan(void);
KEY_STATE key2_scan(void);

#endif
