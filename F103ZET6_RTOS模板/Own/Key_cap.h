#ifndef __key_cap_H
#define __key_cap_H

#include "../Own/af_default.h"

#define Key_Cap_GateVal 80
extern TIM_HandleTypeDef htim5;


uint8_t Key_Cap_Scan(uint8_t mode);
uint8_t Key_Cap_Init(void);



#endif
