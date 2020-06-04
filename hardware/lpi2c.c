/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-02 19:24:01
*@FilePath: \DEMO\hardware\lpi2c.c
*@Drscription: 
***********************************************************************/
#include "lpi2c.h"
#include "fsl_gpio.h"
#include "fsl_lpi2c.h"
#include "pad_config.h"
#include "stdio.h"
#include "core_delay.h"
#include "fsl_iomuxc.h"

/***********************************************************************
*@Function: void LPI2C_PAD_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-02 19:29:49
*@Drscription: pad配置
***********************************************************************/
void LPI2C_PAD_config(void)
{
    IOMUXC_SetPinConfig(LPI2C_SDA_IOMUXC,LPI2C_PAD_SETTING_DATA);
    IOMUXC_SetPinConfig(LPI2C_SCL_IOMUXC,LPI2C_PAD_SETTING_DATA);
}

/***********************************************************************
*@Function: void LPI2C_IOMUXC_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-02 19:38:45
*@Drscription: MUX配置
***********************************************************************/
void LPI2C_IOMUXC_config(void)
{
    IOMUXC_SetPinMux(LPI2C_SCL_IOMUXC,1U);
    IOMUXC_SetPinMux(LPI2C_SDA_IOMUXC,1U);
}

/***********************************************************************
*@Function: void LPI2C_MODE_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-02 19:41:14
*@Drscription: LPI2C的模式配置
***********************************************************************/
void LPI2C_MODE_config(void)
{
    lpi2c_master_config_t masterConfig;

    /*选择PLL3作为LPI2C的时钟源480/8=60M*/
    /*LPI2C六分频     LPI2C=10MHz*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux,LPI2C_CLOCK_SOURCE);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv,LPI2C_CLOCK_DIV);

    /*默认LPI2C的初始配置*/
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    /*LPI2C通讯速率=400KHz*/
    masterConfig.baudRate_Hz=LPI2C_BAUDRATE;
    
    LPI2C_MasterInit(LPI2C_PORT,&masterConfig,LPI2C_CLOCK_SOURE_FREQ);
}

/***********************************************************************
*@Function: void LPI2C_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-02 20:05:45
*@Drscription: LPI2C初始化
***********************************************************************/
void LPI2C_config(void)
{
    LPI2C_PAD_config();
    LPI2C_IOMUXC_config();
    LPI2C_MODE_config();
}

/***********************************************************************
*@Function: void LPI2C_writebyte(uint8_t addr,uint8_t subaddr,uint8_t *data)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-02 20:07:11
*@Drscription: LPI2C写数据
***********************************************************************/
uint8_t LPI2C_writebyte(uint8_t addr,uint8_t subaddr,uint8_t data)
{
    lpi2c_master_transfer_t lpi2c_transfer;
    status_t reval=kStatus_Fail;
    
    lpi2c_transfer.direction=kLPI2C_Write;
	lpi2c_transfer.slaveAddress=(addr>>1);
	lpi2c_transfer.subaddress=subaddr;
	lpi2c_transfer.subaddressSize=SLAVER_INIT_SIZE;
	lpi2c_transfer.data=&data;
	lpi2c_transfer.dataSize=0x01;
	lpi2c_transfer.flags=kLPI2C_TransferDefaultFlag;
    
    reval=LPI2C_MasterTransferBlocking(LPI2C_PORT,&lpi2c_transfer);

    if(reval==kStatus_Success)
    {
        return 1;
    }

    else
    {
        return 0;
    }  

}

/***********************************************************************
*@Function: void LPI2C_readdata(uint8_t addr,uint8_t subaddr,uint8_t data)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-02 20:43:41
*@Drscription: LPI2C读数据
***********************************************************************/
void LPI2C_readdata(uint8_t addr,uint8_t subaddr,uint8_t *data)
{
    lpi2c_master_transfer_t lpi2c_transfer;
    status_t reval=kStatus_Fail;
    
    lpi2c_transfer.direction=kLPI2C_Read;
	lpi2c_transfer.slaveAddress=(addr>>1);
	lpi2c_transfer.subaddress=subaddr;
	lpi2c_transfer.subaddressSize=SLAVER_INIT_SIZE;
	lpi2c_transfer.data=data;
	lpi2c_transfer.dataSize=0x01;
	lpi2c_transfer.flags=kLPI2C_TransferDefaultFlag;
    
    reval=LPI2C_MasterTransferBlocking(LPI2C_PORT,&lpi2c_transfer);   
}






