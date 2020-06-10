/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-08 12:02:40
*@FilePath: \DEMO\hardware\spi.h
*@Drscription: 
***********************************************************************/
#ifndef __SPI__H
#define __SPI__H


#include "fsl_common.h"
#include "fsl_gpio.h"

#define SPI_CS_GPIO_PORT             GPIO2
#define SPI_SCK_GPIO_PORT            GPIO2
#define SPI_MISO_GPIO_PORT           GPIO2
#define SPI_MOSI_GPIO_PORT           GPIO2

#define SPI_CS_GPIO_PIN              (2U)
#define SPI_SCK_GPIO_PIN             (3U)
#define SPI_MISO_GPIO_PIN            (4U)
#define SPI_MOSI_GPIO_PIN            (5U)


#define SPI_CS_IOMUXC           IOMUXC_GPIO_B0_02_GPIO2_IO02
#define SPI_SCK_IOMUXC          IOMUXC_GPIO_B0_03_GPIO2_IO03
#define SPI_MISO_IOMUXC         IOMUXC_GPIO_B0_04_GPIO2_IO04
#define SPI_MOSI_IOMUXC         IOMUXC_GPIO_B0_05_GPIO2_IO05

#define SPI_CS_L()              GPIO_PinWrite(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN,0)
#define SPI_CS_H()              GPIO_PinWrite(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN,1)
#define SPI_SCK_L()             GPIO_PinWrite(SPI_SCK_GPIO_PORT,SPI_SCK_GPIO_PIN,0)
#define SPI_SCK_H()             GPIO_PinWrite(SPI_SCK_GPIO_PORT,SPI_SCK_GPIO_PIN,1)
#define SPI_MOSI_L()            GPIO_PinWrite(SPI_MOSI_GPIO_PORT,SPI_MOSI_GPIO_PIN,0)
#define SPI_MOSI_H()            GPIO_PinWrite(SPI_MOSI_GPIO_PORT,SPI_MOSI_GPIO_PIN,1)
#define SPI_MISO()              GPIO_PsinRead(SPI_MISO_GPIO_PORT,SPI_MISO_GPIO_PIN)


void SPI_GPIO_config(void);
void SPI_write_data(uint8_t data);
uint8_t SPI_read_data(void);

#endif  /*__SPI__H*/

