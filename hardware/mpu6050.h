/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-03 12:00:04
*@FilePath: \DEMO\hardware\mpu6050.h
*@Drscription: 
***********************************************************************/
#ifndef __MPU6050__H
#define __MPU6050__H

#define MPU6050_RA_PWR_MGMT_1           0x6B
#define MPU6050_RA_SMPLRT_DIV           0x19
#define MPU6050_RA_CONFIG               0x1A
#define MPU6050_RA_ACCEL_CONFIG         0x1C
#define MPU6050_RA_GYRO_CONFIG          0x1B
#define MPU6050_RA_WHO_AM_I             0x75

#define MPU6050_ADDR                    0XD0

void MPU6050_config(void);

#endif /*__MPU6050__H*/

