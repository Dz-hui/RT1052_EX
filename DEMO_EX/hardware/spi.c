/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-08 12:02:48
*@FilePath: \DEMO\hardware\spi.c
*@Drscription: 
***********************************************************************/
#include "spi.h"
#include "pad_config.h"
#include "core_delay.h"

#include "fsl_gpio.h"
#include "fsl_iomuxc.h"


/*PAD参数配置*/
#define SPI_PAD_SETTING_DATA            (SRE_0_SLOW_SLEW_RATE| \
                                        DSE_6_R0_6| \
								        SPEED_1_MEDIUM_100MHz| \
								        ODE_0_OPEN_DRAIN_DISABLED| \
								        PKE_0_PULL_KEEPER_DISABLED| \
								        PUE_1_PULL_SELECTED| \
								        PUS_3_22K_OHM_PULL_UP| \
								        HYS_0_HYSTERESIS_DISABLED)

#define SPIINPUT_PAD_SETTING_DATA    (SRE_0_SLOW_SLEW_RATE| \
                                        DSE_6_R0_6| \
								        SPEED_1_MEDIUM_100MHz| \
								        ODE_0_OPEN_DRAIN_DISABLED| \
								        PKE_1_PULL_KEEPER_ENABLED| \
								        PUE_1_PULL_SELECTED| \
								        PUS_3_22K_OHM_PULL_UP| \
								        HYS_0_HYSTERESIS_DISABLED)
/***********************************************************************
*@Function: void SPI_GPIO_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-08 12:06:34
*@Drscription: SPI引脚初始化
***********************************************************************/
void SPI_GPIO_config(void)
{
    gpio_pin_config_t gpio_Config;

    IOMUXC_SetPinConfig(SPI_CS_IOMUXC,SPI_PAD_SETTING_DATA);
    IOMUXC_SetPinConfig(SPI_SCK_IOMUXC,SPI_PAD_SETTING_DATA);
    IOMUXC_SetPinConfig(SPI_MISO_IOMUXC,SPIINPUT_PAD_SETTING_DATA);
    IOMUXC_SetPinConfig(SPI_MOSI_IOMUXC,SPI_PAD_SETTING_DATA);
    
    IOMUXC_SetPinMux(SPI_CS_IOMUXC,0U);
    IOMUXC_SetPinMux(SPI_SCK_IOMUXC,0U);
    IOMUXC_SetPinMux(SPI_MISO_IOMUXC,0U);
    IOMUXC_SetPinMux(SPI_MOSI_IOMUXC,0U);

    gpio_Config.direction=kGPIO_DigitalOutput;
	gpio_Config.outputLogic=0;
	gpio_Config.interruptMode=kGPIO_NoIntmode;
    GPIO_PinInit(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN,&gpio_Config);
    GPIO_PinInit(SPI_SCK_GPIO_PORT,SPI_SCK_GPIO_PIN,&gpio_Config);
    GPIO_PinInit(SPI_MOSI_GPIO_PORT,SPI_MOSI_GPIO_PIN,&gpio_Config);

    gpio_Config.outputLogic=0;
	gpio_Config.interruptMode=kGPIO_NoIntmode;
    gpio_Config.direction=kGPIO_DigitalInput;
    GPIO_PinInit(SPI_MISO_GPIO_PORT,SPI_MISO_GPIO_PIN,&gpio_Config);

    /*片选线一开始应该拉高*/
    SPI_CS_H();
    SPI_SCK_H();
    SPI_MOSI_H();
}

/***********************************************************************
*@Function: uint8_t SPI_readwrite_data(uint8_t data)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-08 16:06:02
*@Drscription: 
***********************************************************************/
void SPI_write_data(uint8_t data)
{
    uint8_t i;
    
    for(i=0;i<8;i++)
    {
        SPI_SCK_L();
        // CPU_TS_Tmr_Delay_US(10);
        //MSB Mode
        if(data & 0x80)
        {
            SPI_MOSI_H();
        }
        else
        {
            SPI_MOSI_L();
        }
        
        data <<= 1;

        CPU_TS_Tmr_Delay_US(5);

        SPI_SCK_H();
        
        CPU_TS_Tmr_Delay_US(5);
    }
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 14:45:52
*@Drscription: 
***********************************************************************/
uint8_t SPI_read_data(void)
{
    uint8_t i;
    uint8_t res=0;
    
    for(i=0;i<8;i++)
    {
        SPI_SCK_L();
        // CPU_TS_Tmr_Delay_US(10);

        res<<=1;
        
        if(SPI_MISO()==1)
        {
            res |= 0x01;
        }

        CPU_TS_Tmr_Delay_US(5);

        SPI_SCK_H();
        
        CPU_TS_Tmr_Delay_US(5);
    }
    return res;
}

