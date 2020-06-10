/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-06 15:12:28
*@FilePath: \DEMO\hardware\gpt.h
*@Drscription: 
***********************************************************************/
#ifndef __GPT__H
#define __GPT__H

#include "fsl_common.h"
#include "fsl_clock.h"

#define GPT_PORT                GPT2
#define GPT_CHANNLE             kGPT_OutputCompare_Channel1
#define GPT_DIVIDER             1

#define TIME_MS                 1000U
#define GPT_CLOCK_FREQ          (CLOCK_GetFreq(kCLOCK_IpgClk)/GPT_DIVIDER)
#define GPT_COUNT               ((TIME_MS/1000)*GPT_CLOCK_FREQ)

#define GPT_CAPTURE_GPIO         GPIO3
#define GPT_CAPTURE_GPIO_PIN     (26U)
#define GPT_CAPTURE_IOMUXC       IOMUXC_GPIO_EMC_40_GPT2_CAPTURE2

void GPT_config(void);

#endif


