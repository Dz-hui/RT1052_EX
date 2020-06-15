/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-03 11:59:53
*@FilePath: \DEMO\hardware\mpu6050.c
*@Drscription: 
***********************************************************************/
#include "MPU6050.h"
#include "lpi2C.h"
#include "core_delay.h"



/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-03 12:10:41
*@Drscription: MPU6050≥ı ºªØ
***********************************************************************/
void MPU6050_config(void)
{
    CPU_TS_Tmr_Delay_US(600);
    LPI2C_writebyte(MPU6050_ADDR,MPU6050_RA_PWR_MGMT_1,0x00);
    LPI2C_writebyte(MPU6050_ADDR,MPU6050_RA_SMPLRT_DIV,0x07);
    LPI2C_writebyte(MPU6050_ADDR,MPU6050_RA_CONFIG,0x06);
    LPI2C_writebyte(MPU6050_ADDR,MPU6050_RA_ACCEL_CONFIG,0x018);
    LPI2C_writebyte(MPU6050_ADDR,MPU6050_RA_GYRO_CONFIG,0x018);
    
}

