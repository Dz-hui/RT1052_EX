/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-08 21:02:26
*@FilePath: \DEMO\hardware\w25Qxx.c
*@Drscription: 
***********************************************************************/
#include "w25Qxx.h"
#include "spi.h"
#include "core_delay.h"

/***********************************************************************
*@Function: void W25QXX_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-08 21:09:01
*@Drscription: 
***********************************************************************/
void W25QXX_config(void)
{
    SPI_GPIO_config();
   
}

/***********************************************************************
*@Function: void W25QXX_writeenable(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 10:18:22
*@Drscription: 
***********************************************************************/
void W25QXX_writeenable(void)
{
    SPI_CS_L();
    SPI_write_data(W25X_WriteEnable);
    SPI_CS_H();
    
}

/***********************************************************************
*@Function: uint32_t W25Qxx_readID(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 10:18:42
*@Drscription: 
***********************************************************************/
uint32_t W25QXX_readID(void)
{
    uint32_t temp=0;
    uint8_t temp0=0, temp1=0, temp2=0;
    
    SPI_CS_L();
    SPI_write_data(W25X_JedecDeviceID);
    temp0=SPI_read_data();
    temp1=SPI_read_data();
    temp2=SPI_read_data();
    SPI_CS_H();

    temp=(temp0<<16) | (temp1<<8) | temp2;

    return temp;
    
}

/***********************************************************************
*@Function: uint8_t W25QXX_read_regstatus(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 11:48:38
*@Drscription: 
***********************************************************************/
uint8_t W25QXX_read_regstatus(void)
{
    uint8_t res=0;

    SPI_CS_L();
    SPI_write_data(W25X_ReadStatusReg);
    res=SPI_read_data();
    SPI_CS_H();
    
    return res;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 11:51:56
*@Drscription: 
***********************************************************************/
void W25QXX_check_busy(void)
{
    uint8_t res=0;

    do{
        res=W25QXX_read_regstatus();
        res &=1;
        
    }while(res);

}

/***********************************************************************
*@Function: void W25Qxx_sector_erase(uint32_t addr)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 11:43:39
*@Drscription: 
***********************************************************************/
void W25Qxx_sector_erase(uint32_t addr)
{
    W25QXX_writeenable();

    SPI_CS_L();
    SPI_write_data(W25X_SectorErase);
    SPI_write_data((uint8_t)addr>>16);
    SPI_write_data((uint8_t)addr>>8);
    SPI_write_data((uint8_t)addr);
    SPI_CS_H();
    W25QXX_check_busy();

}

/***********************************************************************
*@Function: void W25QXX_pagewrite(uint32_t addr,uint8_t *buff,uint8_t size)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 12:02:00
*@Drscription: 
***********************************************************************/
void W25QXX_pagewrite(uint32_t addr,uint8_t *buff,uint8_t size)
{
    uint8_t i;
    W25QXX_writeenable();
    
    SPI_CS_L();
    SPI_write_data(W25X_PageProgram);
    SPI_write_data((uint8_t)addr>>16);
    SPI_write_data((uint8_t)addr>>8);
    SPI_write_data((uint8_t)addr);

    for(i=0;i<size;i++)
    {
        SPI_write_data(buff[i]);
    }

    SPI_CS_H();

    W25QXX_check_busy();
}

/***********************************************************************
*@Function: void W25QXX_readdata(uint32_t addr,uint8_t *buff,uint8_t size)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-10 12:14:24
*@Drscription: 
***********************************************************************/
void W25QXX_readdata(uint32_t addr,uint8_t *buff,uint8_t size)
{
    uint8_t i;
    
    SPI_CS_L();
    SPI_write_data(W25X_ReadData);
    SPI_write_data((uint8_t)addr>>16);
    SPI_write_data((uint8_t)addr>>8);
    SPI_write_data((uint8_t)addr);
    
    for(i=0;i<size;i++)
    {
        buff[i]=SPI_read_data();
    }

    SPI_CS_H();

}

