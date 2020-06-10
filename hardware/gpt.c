/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-06 15:14:39
*@FilePath: \DEMO\hardware\gpt.c
*@Drscription: 
***********************************************************************/
#include "gpt.h"
#include "exit.h"
#include "fsl_gpt.h"
#include "fsl_clock.h"
#include "led.h"
#include "fsl_gpio.h"
#include "pad_config.h"
#include "fsl_iomuxc.h"
#include "stdio.h"

uint8_t i=0;

/*PAD≤Œ ˝…Ë÷√*/
#define GPT_PAD_SETTING_DATA    (SRE_0_SLOW_SLEW_RATE| \
                                 DSE_6_R0_6| \
								 SPEED_1_MEDIUM_100MHz| \
								 ODE_0_OPEN_DRAIN_DISABLED| \
								 PKE_1_PULL_KEEPER_ENABLED| \
								 PUE_0_KEEPER_SELECTED| \
								 PUS_3_22K_OHM_PULL_UP| \
								 HYS_0_HYSTERESIS_DISABLED)

/***********************************************************************
*@Function: void GPT_GPIO_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-06 20:28:58
*@Drscription: 
***********************************************************************/
void GPT_GPIO_config(void)
{
    gpio_pin_config_t gpt_Config;

    IOMUXC_SetPinConfig(GPT_CAPTURE_IOMUXC,GPT_PAD_SETTING_DATA);
    IOMUXC_SetPinMux(GPT_CAPTURE_IOMUXC,0U);

	gpt_Config.direction=kGPIO_DigitalInput;
	gpt_Config.interruptMode=kGPIO_NoIntmode;
	gpt_Config.outputLogic=1;
    GPIO_PinInit(GPT_CAPTURE_GPIO,GPT_CAPTURE_GPIO_PIN,&gpt_Config);

}

/***********************************************************************
*@Function: void GPT_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-06 15:33:42
*@Drscription: 
***********************************************************************/
void GPT_config(void)
{
    gpt_config_t gpt_initConfig;
    
    GPT_GPIO_config();
    
    CLOCK_SetMux(kCLOCK_PerclkMux,0U);
    CLOCK_SetDiv(kCLOCK_PerclkDiv,0U);

    GPT_GetDefaultConfig(&gpt_initConfig);
    GPT_Init(GPT_PORT,&gpt_initConfig);
	
    GPT_SetClockDivider(GPT_PORT,GPT_DIVIDER);
    
    GPT_SetInputOperationMode(GPT_PORT,kGPT_InputCapture_Channel2,kGPT_InputOperation_RiseEdge);

    GPT_EnableInterrupts(GPT_PORT,kGPT_InputCapture2InterruptEnable);
    GPT_EnableInterrupts(GPT_PORT,kGPT_RollOverFlagInterruptEnable);
    
    
    IRQN_priority(4,5,0,GPT2_IRQn);

    EnableIRQ(GPT2_IRQn);

    GPT_StartTimer(GPT_PORT);
    
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-06 16:55:15
*@Drscription: 
***********************************************************************/
void GPT2_IRQHandler(void)
{
    GPT_ClearStatusFlags(GPT_PORT,kGPT_InputCapture2Flag);
    if(GPT_GetStatusFlags(GPT_PORT,kGPT_InputCapture2Flag))
    {
        i=GPT_GetInputCaptureValue(GPT_PORT,kGPT_InputCapture_Channel2);
        printf("GPT_VAL=%d\n",i);
    }
    
    
}

