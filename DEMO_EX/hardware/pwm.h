/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-12 17:05:43
*@FilePath: \DEMO\hardware\pwm.h
*@Drscription: 
***********************************************************************/
#ifndef __PWM__H
#define __PWM__H

#include "fsl_common.h"


#define QTMR_CH0_GPIO_PORT          GPIO1
#define QTMR_CH0_GPIO_PIN           (16U)
#define QTMR_CH0_IOMUXC             IOMUXC_GPIO_AD_B1_00_QTIMER3_TIMER0    

#define QTMR_PORT                   TMR3
#define QTMR_CHANNLE                kQTMR_Channel_0

#define QTMR_PWM_FREQ               50000
#define QTMR_PWM_DUTY_CYCLE         80

#define QTMR_SOURCE_CLOCK           CLOCK_GetFreq(kCLOCK_IpgClk)

void QTMR_PWM_config(void);

#endif /*__PWM__H*/