/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-04 13:09:44
*@FilePath: \DEMO\hardware\adc.h
*@Drscription: 
***********************************************************************/
#ifndef __ADC__H
#define __ADC__H


#include "fsl_common.h"

#define ADC_GPIO_PORT          GPIO1
#define ADC_GPIO_PIN           (24U)
#define ADC_IOMUXC             IOMUXC_GPIO_AD_B1_08_GPIO1_IO24
#define ADC_PORT               ADC1
#define ADC_CHANNLE            (13U)
#define ADC_CHANNLE_GROUP      (0U)
#define ADC_IRQ                 ADC1_IRQn
#define ADC_IRQHandler          ADC1_IRQHandler

void ADC_config(void);

#endif /*__ADC__H*/

