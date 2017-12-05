#include "key_cap.h"

 __IO uint16_t default_val=0;
static void  Key_Cap_Reset(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_TIM5_CLK_ENABLE();
  
    /**TIM5 GPIO Configuration    
    PA1     ------> TIM5_CH2 
    */

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_RESET);
    
    HAL_Delay(5);
    
    __HAL_TIM_SET_COUNTER(&htim5,0);
    __HAL_TIM_CLEAR_FLAG(&htim5,TIM_FLAG_UPDATE|TIM_FLAG_CC2);
    
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    HAL_TIM_IC_Start(&htim5, TIM_CHANNEL_2);
}

static uint16_t Get_Key_Cap_Val(void)
{
    Key_Cap_Reset();
    while(__HAL_TIM_CLEAR_FLAG(&htim5,TIM_FLAG_CC2)==RESET)
    {
        uint16_t count;
        count=__HAL_TIM_GET_COUNTER(&htim5);
        if (count>0xffff-500)
            return count;
    }
    return HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_2);

}

static uint16_t Get_Key_Cap_MaxVal(uint8_t n)
{
    uint16_t temp=0,res=0;
    while(n--)
    {
        temp=Get_Key_Cap_Val();
        if(temp>res)
            res=temp;
    }
    return res;
        
}

uint8_t Key_Cap_Init(void)
{
    uint16_t buf[10],temp;
    uint8_t i,j;
    for(i=0;i<10;i++)
    {
        buf[i]=Get_Key_Cap_Val();
        HAL_Delay(10);
    }
    for(i=0;i<9;i++)
    {
        for(j=i+1;j<10;j++)
        {
            if(buf[i]>buf[j])
            {
                temp=buf[i];
                buf[i]=buf[j];
                buf[j]=buf[i];
            }
        }
    }
    temp=0;
    for(i=2;i<8;i++)
        temp+=buf[i];
    default_val=temp/6;
    printf("default_val=%d\n",default_val);
    if(default_val>Key_Cap_GateVal/2)
        return 1;
    return 0;
}

uint8_t Key_Cap_Scan(uint8_t mode)
{
    uint8_t keyen=0,res=0,sample=0;
    uint16_t rval;
    if(mode)
    {
        sample=6;
        keyen=0;
    }
    rval=Get_Key_Cap_MaxVal(sample);
    printf("scan_rval=%d\n",rval);
    if(rval>(default_val+Key_Cap_GateVal))
    {
        rval=Get_Key_Cap_MaxVal(sample);
        if((keyen==0)&&(rval>(default_val+Key_Cap_GateVal)))
            res=1;
        keyen=5;
    }
    else if(keyen>2)
        keyen=2;
    if(keyen)
        keyen--;
    return res;

}
