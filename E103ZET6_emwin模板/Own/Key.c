#include "key.h"
#include "../Own/Rtos.h"
uint8_t KEY_STATE;
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//    switch(GPIO_Pin)
//    {
//        case KEY1_Pin:
//        {
//            if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0);KEY_STATE=1;break;
//        }
//        case KEY2_Pin:
//        {
//            if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0);KEY_STATE=0x01<<1;break;
//        }
//        case KEY3_Pin:
//        {
//            if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0);KEY_STATE=0x01<<2;break;
//        }
//        case KEY4_Pin:
//        {
//            if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0);KEY_STATE=0x01<<3;break;
//        }
//        case KEY5_Pin:
//        {
//            if(HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)==0);KEY_STATE=0x01<<4;break;
//        }
//    }
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
//}



static void KEY_SCAN(void)
{
    uint16_t times;
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
    {
        vTaskDelay(10);
        times=0;
        while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0&&times<100)
        {
            times++;vTaskDelay(10);
        }
        KEY_STATE=0x01;
    }
     else   if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
    {
        vTaskDelay(10);
        times=0;
        while(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0&&times<100)
        {
            times++;vTaskDelay(10);
        }
        KEY_STATE=0x01<<1;
    }
     else   if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0)
    {
        vTaskDelay(10);
        times=0;
        while(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0&&times<100)
        {
            times++;vTaskDelay(10);
        }
        KEY_STATE=0x01<<2;
    }
     else   if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0)
    {
        vTaskDelay(10);
        times=0;
        while(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0&&times<100)
        {
            times++;vTaskDelay(10);
        }
        KEY_STATE=0x01<<3;
    }
     else   if(HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)==0)
    {
        vTaskDelay(10);
        times=0;
        while(HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)==0&&times<100)
        {
            times++;vTaskDelay(10);
        }
        KEY_STATE=0x01<<4;
    }

}

void KEY_MSG(void)
{
    KEY_SCAN();
    if(KEY_STATE)
    {
        //printf("%#x\n",KEY_STATE);
        switch(KEY_STATE)
        {
            case 0x02:GUI_SendKeyMsg(GUI_KEY_RIGHT,1);vTaskDelay(10);GUI_SendKeyMsg(GUI_KEY_RIGHT,0);break;//up
            case 0x08:GUI_SendKeyMsg(GUI_KEY_LEFT,1);vTaskDelay(10);GUI_SendKeyMsg(GUI_KEY_LEFT,0);break;//down
            case 0x04:GUI_SendKeyMsg(GUI_KEY_ENTER,1);vTaskDelay(10);GUI_SendKeyMsg(GUI_KEY_ENTER,0);break;//left
            case 0x01:GUI_SendKeyMsg(GUI_KEY_UP,1);vTaskDelay(10);GUI_SendKeyMsg(GUI_KEY_UP,0);break;//right
            case 0x10:GUI_SendKeyMsg(GUI_KEY_DOWN,1);vTaskDelay(10);GUI_SendKeyMsg(GUI_KEY_DOWN,0);break;//mid
        }
        KEY_STATE=0;
    }
}
