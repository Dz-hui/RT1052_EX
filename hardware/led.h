/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-05-17 21:27:22
*@FilePath: \hello_world\component\uart\led.h
*@Drscription: 
***********************************************************************/
#ifndef __LED__H
#define __LED__H


#include "fsl_common.h"

#define CORE_BOARD_LED_GPIO          GPIO1
#define CORE_BOARD_LED_PIN           (9U)
#define CORE_BOARD_LED_IOMUXC        IOMUXC_GPIO_AD_B0_09_GPIO1_IO09




#define CORE_BOARD_LED_ON()         GPIO_PinWrite(CORE_BOARD_LED_GPIO,CORE_BOARD_LED_PIN,0U)
      
#define CORE_BOARD_LED_OFF()		GPIO_PinWrite(CORE_BOARD_LED_GPIO,CORE_BOARD_LED_PIN,1U)	


#define CORE_BOARD_LED_TOGGLE()     GPIO_PortToggle(CORE_BOARD_LED_GPIO,1<<CORE_BOARD_LED_PIN)






void LED_config(void);



#endif /*__LED__H*/


