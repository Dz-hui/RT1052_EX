/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-01 11:54:53
*@FilePath: \DEMO\user\main.c
*@Drscription: 
***********************************************************************/
/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   用V2.3.1版本库建的工程模板
  ******************************************************************
  * @attention
  *
  * 实验平台:野火  i.MXRT1052开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************
  */
#include "fsl_debug_console.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "led.h"
#include "key.h"
#include "uart.h"
#include "stdio.h"
#include "lpi2c.h"
#include "core_delay.h"
#include "mpu6050.h"
#include "adc.h"
#include "fsl_adc.h"
#include "pit.h"
#include "fsl_pit.h"
#include "core_delay.h"
#include "gpt.h"
#include "w25Qxx.h"
/*******************************************************************
 * Prototypes
 *******************************************************************/
volatile bool ADC_ConversionDoneFlag;
volatile uint32_t ADC_ConvertedValue;
adc_channel_config_t adc_channle_config;
/*******************************************************************
 * Code
 *******************************************************************/

uint8_t TX_buff[8]="h";
uint8_t RX_buff[8];


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{

	uint8_t keystatus=1;
	uint32_t flash_ID=0x11;
  	//uint8_t MPU6050_ID=0;

	/* 初始化内存保护单元 */
	BOARD_ConfigMPU();
	/* 初始化开发板引脚 */
	BOARD_InitPins();
	/* 初始化开发板时钟 */
	BOARD_BootClockRUN();
	/* 初始化调试串口 */
	BOARD_InitDebugConsole();
	/* 打印系统时钟 */
    
	LED_config();
	//KEY_config();
	USB_UART_config();
	//ADC_config();
  	//LPI2C_config();
  	//MPU6050_config();
	//PIT_config();
	//PIT_StartTimer(PIT,PIT_CHANNLE);
	GPT_config();
	W25QXX_config();
	
	
  /*表示初始化完成*/
	printf("hello！\n");

	flash_ID=W25QXX_readID();

	printf("flash_ID=0x%X\n",flash_ID);

	W25Qxx_sector_erase(0x00000);
	W25QXX_pagewrite(0x00000,TX_buff,1);
	W25QXX_readdata(0x00000,RX_buff,1);
	printf("读出数据为%s\n",RX_buff);


	
	
#if 0
  /*读取MPU6050的ID*/
  	LPI2C_readdata(MPU6050_ADDR,MPU6050_RA_WHO_AM_I,&MPU6050_ID);
  	printf("MPU6050_ID=%x\n",MPU6050_ID);
#endif  

  /*ADC通道的的配置*/
	//adc_channle_config.channelNumber=ADC_IRQ;
	//adc_channle_config.enableInterruptOnConversionCompleted=true;


	while(1)
	{
		#if 0
		keystatus=KEY_scan();
		
		//ADC_ConversionDoneFlag=false;
		//ADC_SetChannelConfig(ADC_PORT,ADC_CHANNLE_GROUP,&adc_channle_config);
		//while(ADC_ConversionDoneFlag==false)
		//{
			
			
		//}
		
		//adc_value=(float)ADC_ConvertedValue/(float)4096*(float)3.3;
		//printf("adc_value=%f\n",adc_value);
		
		if(keystatus ==KEY_ON)
		{
			CORE_BOARD_LED_TOGGLE();      
		}
		#endif
	}     

}
/****************************END OF FILE**********************/
