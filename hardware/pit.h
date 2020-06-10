/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-05 20:20:07
*@FilePath: \DEMO\hardware\pit.h
*@Drscription: 
***********************************************************************/
#ifndef __PIT__H
#define __PIT__H

#include "fsl_common.h"
#include "fsl_clock.h"

#define PIT_CHANNLE                 kPIT_Chnl_1
#define PIT_TIME                    1000000U
#define PIT_SOURCE_CLCOK             CLOCK_GetFreq(kCLOCK_OscClk)


void PIT_config(void);

#endif


