#include "../Own/Rtos.h"
#include "../Own/key.h"
#include "dialog.h"
#include "FreeRTOSConfig.h"

TaskHandle_t xHandler_0=NULL;
TaskHandle_t xHandler_1=NULL;
TaskHandle_t xHandler_2=NULL;
TaskHandle_t xHandler_3=NULL;
TaskHandle_t xHandler_4=NULL;
TaskHandle_t xHandler_5=NULL;
TaskHandle_t xHandler_6=NULL;
TaskHandle_t xHandler_7=NULL;


volatile uint32_t ulHighFrequencyTimerTicks;


#define WM_M_MID (WM_USER+0x00)
#define WM_M_UP (WM_USER+0x01)
#define WM_M_DOWN (WM_USER+0x02)
#define WM_M_LEFT (WM_USER+0x03)
#define WM_M_RIGHT (WM_USER+0x04)

void Task0(void *Parameters)
{
    #if RTOS_STATE_ENABLE
    uint8_t pcWriteBuffer[500];
    while(1)
    {         
        printf("=================================================\r\n");
        printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
        vTaskList((char *)&pcWriteBuffer);
        printf("%s\r\n", pcWriteBuffer);
        printf("\r\n任务名       运行计数         使用率\r\n");
        vTaskGetRunTimeStats((char *)&pcWriteBuffer);
        printf("%s\r\n", pcWriteBuffer);      
        vTaskDelay(5000);     
    }
    #endif
}


void Task2(void *Parameters)
{
    while(1)
    {
    MainTask();
    }        
}

void Task3(void *Parameters)
{
    while(1)
    {
    LCD_Refresh_M();
    vTaskDelay(50);
    }        
}







void mTaskCreate(void)
{
    #if RTOS_STATE_ENABLE
    xTaskCreate( Task0, "TASK_STATE", 300, NULL, 1, &xHandler_0 );
    #endif
    xTaskCreate( Task2, "LCD_GUI", 512, NULL, 3, &xHandler_2 );
    xTaskCreate( Task3, "LCD_REFRESH",256, NULL, 4, &xHandler_3 );
}



