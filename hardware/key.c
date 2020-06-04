/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-05-27 14:52:04
*@FilePath: \DEMO\hardware\key.c
*@Drscription: 
***********************************************************************/
#include "key.h"
#include "pad_config.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "exit.h"

uint8_t flag=0;


/*PAD参数设置*/
#define KEY_PAD_SETTING_DATA    (SRE_0_SLOW_SLEW_RATE| \
                                 DSE_0_OUTPUT_DRIVER_DISABLED| \
								 SPEED_1_MEDIUM_100MHz| \
								 ODE_0_OPEN_DRAIN_DISABLED| \
								 PKE_1_PULL_KEEPER_ENABLED| \
								 PUE_1_PULL_SELECTED| \
								 PUS_3_22K_OHM_PULL_UP| \
								 HYS_1_HYSTERESIS_ENABLED)   
                                 
/***********************************************************************
*@Function: void KEY_PAD_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-05-27 15:07:56
*@Drscription: pad配置
***********************************************************************/
void KEY_PAD_config(void)
{
    IOMUXC_SetPinConfig(WAKEUP_KEY_IOMUCX,KEY_PAD_SETTING_DATA);
}

/***********************************************************************
*@Function: void KEY_IOMUXC_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-05-27 15:14:33
*@Drscription: MUX配置
***********************************************************************/
void KEY_IOMUXC_config(void)
{
    IOMUXC_SetPinMux(WAKEUP_KEY_IOMUCX,0U);
}


/***********************************************************************
*@Function: void KEY_GPIO_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-05-27 15:14:52
*@Drscription: GPIO口配置
***********************************************************************/
void KEY_GPIO_config(void)
{
    gpio_pin_config_t key_config;
    
    key_config.direction=kGPIO_DigitalInput;
    key_config.outputLogic=1;
    key_config.interruptMode=kGPIO_IntLowLevel;

    GPIO_PinInit(WAKEUP_KEY_GPIO,WAKEUP_KEY_PIN,&key_config);

}

/***********************************************************************
*@Function: void KEY_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-05-27 15:21:48
*@Drscription:按键初始化
***********************************************************************/
void KEY_config(void)
{
    KEY_PAD_config();
    KEY_IOMUXC_config();
    KEY_GPIO_config();
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-05-31 20:30:08
*@Drscription: 按键中断配置
***********************************************************************/
void KEY_IQRN_config(void)
{
    /*开启GPIO引脚中断*/
    GPIO_EnableInterrupts(WAKEUP_KEY_GPIO,1<<WAKEUP_KEY_PIN);
    
    /*中断优先级配置*/
    IRQN_priority(4,1,1,WAKEUP_KEY_IQRN);

    /*开启GPIO端口中断*/
    EnableIRQ(WAKEUP_KEY_IQRN);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-05-31 20:42:21
*@Drscription: 按键中断函数
***********************************************************************/
void GPIO5_Combined_0_15_IRQHandler(void)
{
    GPIO_ClearPinsInterruptFlags(WAKEUP_KEY_GPIO,1<<WAKEUP_KEY_PIN);
    flag=1;
}


/***********************************************************************
*@Function: uint8_t KEY_scanf(void)
*@Input: 
*@Return: 
*@Author: Dz_hui
*@Date: 2020-05-27 15:23:26
*@Drscription: 按键扫描
***********************************************************************/
uint8_t KEY_scan(void)
{
    static uint8_t flag=0;

    if(WAKEUP_READ_PIN()==KEY_ON &&flag)
    {
        flag=0;
        return KEY_ON;
    }
    else if((WAKEUP_READ_PIN()==KEY_OFF))
    {
        flag=1;
    }
    return KEY_OFF;
}


