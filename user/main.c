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
  * @brief   ��V2.3.1�汾�⽨�Ĺ���ģ��
  ******************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  i.MXRT1052������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
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

/*******************************************************************
 * Prototypes
 *******************************************************************/
volatile bool ADC_ConversionDoneFlag;
volatile uint32_t ADC_ConvertedValue;

/*******************************************************************
 * Code
 *******************************************************************/

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	uint8_t keystatus=1;
	float adc_value=0;
  uint8_t MPU6050_ID=0;
	adc_channel_config_t adc_channle_config;
	/* ��ʼ���ڴ汣����Ԫ */
	BOARD_ConfigMPU();
	/* ��ʼ������������ */
	BOARD_InitPins();
	/* ��ʼ��������ʱ�� */
	BOARD_BootClockRUN();
	/* ��ʼ�����Դ��� */
	BOARD_InitDebugConsole();
	/* ��ӡϵͳʱ�� */
    
	LED_config();
	KEY_config();
	USB_UART_config();
	ADC_config();
  LPI2C_config();
  MPU6050_config();

  /*��ʾ��ʼ�����*/
	printf("hello��\n");
  
  /*��ȡMPU6050��ID*/
  LPI2C_readdata(MPU6050_ADDR,MPU6050_RA_WHO_AM_I,&MPU6050_ID);
  printf("MPU6050_ID=%x\n",MPU6050_ID);
  
  /*ADCͨ���ĵ�����*/
	adc_channle_config.channelNumber=ADC_IRQ;
	adc_channle_config.enableInterruptOnConversionCompleted=true;
  
	while(1)
	{
		keystatus=KEY_scan();
		ADC_ConversionDoneFlag=false;
		ADC_SetChannelConfig(ADC_PORT,ADC_CHANNLE_GROUP,&adc_channle_config);
		while(ADC_ConversionDoneFlag==false)
		{
      
		}
		adc_value=(float)ADC_ConvertedValue/(float)4096*(float)3.3;
		printf("adc_value=%f\n",adc_value);

		if(keystatus ==KEY_ON)
		{
			CORE_BOARD_LED_TOGGLE();      
		}

	}     

}
/****************************END OF FILE**********************/