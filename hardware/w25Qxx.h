/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-08 21:02:12
*@FilePath: \DEMO\hardware\w25Qxx.h
*@Drscription: 
***********************************************************************/
#ifndef __W25QXX__H
#define __W25QXX__H

#include "fsl_common.h"

#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		      0x05 
#define W25X_WriteStatusReg		      0x01 
#define W25X_ReadData			      0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	      0xAB 
#define W25X_DeviceID			      0xAB 
#define W25X_ManufactDeviceID   	  0x90 
#define W25X_JedecDeviceID		      0x9F 

#define WIP_Flag                      0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                    0xFF

void W25QXX_config(void);
void W25QXX_writeenable(void);
uint32_t W25QXX_readID(void);
void W25Qxx_sector_erase(uint32_t addr);
void W25QXX_pagewrite(uint32_t addr,uint8_t *buff,uint8_t size);
void W25QXX_readdata(uint32_t addr,uint8_t *buff,uint8_t size);

#endif /*__W25QXX__H*/

