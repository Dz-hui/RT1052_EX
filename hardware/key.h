/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-05-27 14:51:51
*@FilePath: \DEMO\hardware\key.h
*@Drscription: 
***********************************************************************/
#ifndef __KEY__H
#define __KEY__H

#include "fsl_common.h"

#define WAKEUP_KEY_GPIO             GPIO5
#define WAKEUP_KEY_PIN              (0U)
#define WAKEUP_KEY_IOMUCX           IOMUXC_SNVS_WAKEUP_GPIO5_IO00

#define WAKEUP_READ_PIN()           GPIO_PinRead(WAKEUP_KEY_GPIO,WAKEUP_KEY_PIN)

#define KEY_ON                      0
#define KEY_OFF                     1

#define WAKEUP_KEY_IQRN             GPIO5_Combined_0_15_IRQn 

void KEY_config(void);
uint8_t Key_Scan(GPIO_Type* base, uint32_t pin);
void KEY_IQRN_config(void);
uint8_t KEY_scan(void);

#endif/*__KEY__H*/

