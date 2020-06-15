/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-05 20:20:36
*@FilePath: \DEMO\hardware\pit.c
*@Drscription: 
***********************************************************************/
#include "pit.h"
#include "exit.h"
#include "fsl_clock.h"
#include "fsl_pit.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "led.h"
#include "stdio.h"
#include "fsl_adc.h"
#include "adc.h"

/*中断计数*/
uint32_t k=0;
extern adc_channel_config_t adc_channle_config;



/***********************************************************************
*@Function: void PIT_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-05 20:57:44
*@Drscription: PIT初始化
***********************************************************************/
void PIT_config(void)
{
    pit_config_t pit_config;
    
    /*设置PIT时钟 OSC_CLOCK*/
    CLOCK_SetMux(kCLOCK_PerclkMux,1U);
    /*设置时钟分频为1*/
    CLOCK_SetDiv(kCLOCK_PerclkDiv,0U);

    /*获取默认值*/
    PIT_GetDefaultConfig(&pit_config);
    /*使能debug模式*/
    //pit_config.enableRunInDebug=false;
    PIT_Init(PIT,&pit_config);

    PIT_SetTimerPeriod(PIT,PIT_CHANNLE,USEC_TO_COUNT(PIT_TIME,PIT_SOURCE_CLCOK));
    /*清除0中断标志*/
    PIT_ClearStatusFlags(PIT,PIT_CHANNLE,kPIT_TimerFlag);
    /*使能中断标志*/
    PIT_EnableInterrupts(PIT,PIT_CHANNLE,kPIT_TimerInterruptEnable);

    IRQN_priority(4,6,0,PIT_IRQn);
    
    EnableIRQ(PIT_IRQn);

}

/***********************************************************************
*@Function: void PIT_IRQHandler(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-06 10:01:26
*@Drscription: PIT中断函数
***********************************************************************/
void PIT_IRQHandler(void)
{
    
    PIT_ClearStatusFlags(PIT,PIT_CHANNLE,kPIT_TimerFlag);
    
    ADC_SetChannelConfig(ADC_PORT,ADC_CHANNLE_GROUP,&adc_channle_config); 
    
}

