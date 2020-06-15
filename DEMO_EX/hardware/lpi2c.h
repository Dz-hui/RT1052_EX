/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-02 19:23:39
*@FilePath: \DEMO\hardware\lpi2c.h
*@Drscription: 
***********************************************************************/
#ifndef __LPI2C__H
#define __LPI2C__H

#include "fsl_common.h"


#define LPI2C_PAD_SETTING_DATA  (SRE_0_SLOW_SLEW_RATE| \
                                 DSE_6_R0_6| \
								 SPEED_1_MEDIUM_100MHz| \
								 ODE_1_OPEN_DRAIN_ENABLED| \
								 PKE_1_PULL_KEEPER_ENABLED| \
								 PUE_1_PULL_SELECTED| \
								 PUS_3_22K_OHM_PULL_UP| \
								 HYS_1_HYSTERESIS_ENABLED)   
                                 

#define LPI2C_SDA_IOMUXC      IOMUXC_GPIO_AD_B1_06_LPI2C3_SDA
#define LPI2C_SCL_IOMUXC      IOMUXC_GPIO_AD_B1_07_LPI2C3_SCL
#define LPI2C_PORT            LPI2C3


#define LPI2C_CLOCK_SOURCE      0U
#define LPI2C_CLOCK_DIV         5U
#define LPI2C_BAUDRATE          400000U
#define LPI2C_CLOCK_SOURE_FREQ  10000000

#define SLAVER_WRITE_ADDR       0xA0
#define SLAVER_READ_ADDR        0xA1
#define SLAVER_INIT_SIZE        0x01

#define LP_I2C_DELAY_TIME       10*0x100

void LPI2C_IOMUXC_config(void);
void LPI2C_PAD_config(void);
void LPI2C_config(void);
void LPI2C_MODE_config(void);
uint8_t LPI2C_writebyte(uint8_t addr,uint8_t subaddr,uint8_t data);
void LPI2C_readdata(uint8_t addr,uint8_t subaddr,uint8_t *data);
void LPI2C_waitstandbystatus(uint8_t addr);

#endif /*__LPI2C__H*/







