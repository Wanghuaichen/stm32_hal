#include "../Own/Rtos.h"
#include "../Own/led.h"
#include "../Own/key.h"



void LEDTask1(void *Parameters)
{
    while(1)
    {
    LEDG_TOGGLE;
    vTaskDelay(1000);  
    }        
}

void LEDTask2(void *Parameters)
{
    while(1)
    {
     LEDR_TOGGLE; 
    vTaskDelay(500);
    }        
}


void StackOverFlowTest(void)
{
    uint16_t i;
    uint8_t buf[2000];
    for(i=2000;i>0;i--)
    {
        buf[i]=0x55;
        vTaskDelay(1);
    }

}


void Key1(void *Parameters)
{
    while(1)
    {
      if(key1_scan()==KEY_ON)
      {
          if(xHandler_LED1!=NULL)
          {
              vTaskDelete(xHandler_LED1);
              xHandler_LED1=NULL;
              printf("Delete led1 task\n");
              
          }
          else
          {
              xTaskCreate( LEDTask1, "LED_TASK1", 40, NULL, 2, &xHandler_LED1 );
              printf("Creat led1 task");
          }
//          vTaskResume(xHandler_LED2);
StackOverFlowTest();
      }
      vTaskDelay(50);
    }
        
}
void Key2(void *Parameters)
{
    uint8_t pcWriteBuffer[500];
    while(1)
    {
      if(key2_scan()==KEY_ON)
      {
//          if(xHandler_LED2!=NULL)
//          {
//              vTaskSuspend(xHandler_LED2);
//          }
          
					printf("=================================================\r\n");
					printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
					vTaskList((char *)&pcWriteBuffer);
					printf("%s\r\n", pcWriteBuffer);
         
					printf("\r\n任务名       运行计数         使用率\r\n");
					vTaskGetRunTimeStats((char *)&pcWriteBuffer);
					printf("%s\r\n", pcWriteBuffer);        
      }
      vTaskDelay(50);
    }
}

void mTaskCreate(void)
{
    xTaskCreate( LEDTask1, "LED_TASK1", 512, NULL, 3, &xHandler_LED1 );
    xTaskCreate( LEDTask2, "LED_TASK2", 512, NULL, 4, &xHandler_LED2 );
    xTaskCreate( Key1, "KEY1", 512, NULL, 5, &xHandler_Key1 );
    xTaskCreate( Key2, "KEY2", 512, NULL, 6, &xHandler_Key2 );
}

//void configureTimerForRunTimeStats(void)
//{
//    ulHighFrequencyTimerTicks = 0ul;
//}

//unsigned long getRunTimeCounterValue(void)
//{
//    return ulHighFrequencyTimerTicks;
//}


