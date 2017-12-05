#include "key.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==KEY2_Pin)
    {
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
            printf("key2 down\n");
            Key_Number=2;
    }
    else if(GPIO_Pin==KEY1_Pin)
    {
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
            printf("key1 down\n");
            Key_Number=1;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}


KEY_STATE key1_scan(void)
{
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==KEY_ON)
    {
        HAL_Delay(10);
        while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==KEY_ON);
        return KEY_ON;
    }
    return KEY_OFF;
}
KEY_STATE key2_scan(void)
{
    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==KEY_ON)
    {
        HAL_Delay(10);
        while(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==KEY_ON);
        return KEY_ON;
    }
    return KEY_OFF;
}

