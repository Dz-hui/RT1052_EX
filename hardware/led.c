/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-05-17 21:27:35
*@FilePath: \DEMO\hardware\led.c
*@Drscription: 
***********************************************************************/
#include "led.h"
#include "pad_config.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"


/*pad参数设置*/
#define LED_PAD_SETTING_DATA    (SRE_0_SLOW_SLEW_RATE| \
                                 DSE_1_R0_1| \
								 SPEED_1_MEDIUM_100MHz| \
								 ODE_0_OPEN_DRAIN_DISABLED| \
								 PKE_0_PULL_KEEPER_DISABLED| \
								 PUE_0_KEEPER_SELECTED| \
								 PUS_0_100K_OHM_PULL_DOWN| \
								 HYS_0_HYSTERESIS_DISABLED)
					
/***********************************************************************
*@Function: void LED_PAD_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 19:27:16
*@Drscription: pad配置
***********************************************************************/
void LED_PAD_config(void)
{
	IOMUXC_SetPinConfig(CORE_BOARD_LED_IOMUXC,LED_PAD_SETTING_DATA);
	
}

/***********************************************************************
*@Function: void LED_MUX_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 19:28:14
*@Drscription: mux配置
***********************************************************************/
void LED_MUX_config(void)
{
	IOMUXC_SetPinMux(CORE_BOARD_LED_IOMUXC,0U);
}

/***********************************************************************
*@Function: void LED_GPIO_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 19:28:36
*@Drscription: GPIO配置
***********************************************************************/
void LED_GPIO_config(void)
{
	gpio_pin_config_t Config;
	
	Config.direction = kGPIO_DigitalOutput;
	Config.outputLogic= 1;
	Config.interruptMode= kGPIO_NoIntmode;
	
	GPIO_PinInit(CORE_BOARD_LED_GPIO,CORE_BOARD_LED_PIN,&Config);
	
}

/***********************************************************************
*@Function:void LED_config(void) 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 19:29:00
*@Drscription: LED初始化
***********************************************************************/
void LED_config(void)
{
	LED_PAD_config();
	LED_MUX_config();
	LED_GPIO_config();
	
}

/***********************************************************************
*@Function: void LED_TTOGLE(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 19:29:21
*@Drscription: LED反转函数
***********************************************************************/
void LED_TTOGLE(void)
{
	if(GPIO_PinRead(CORE_BOARD_LED_GPIO,CORE_BOARD_LED_PIN)==1U)
	{
		CORE_BOARD_LED_ON();
	}
	
	else
	{
		CORE_BOARD_LED_OFF();
	}
}



