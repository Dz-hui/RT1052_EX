/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 13:33:51
*@Drscription: 
***********************************************************************/
#include "adc.h"
#include "fsl_adc.h"
#include "fsl_gpio.h"
#include "pad_config.h"
#include "fsl_iomuxc.h"
#include "exit.h"
#include "stdio.h"


extern volatile bool ADC_ConversionDoneFlag;
extern volatile uint32_t ADC_ConvertedValue;
/***********************************************************************
*@Function: PAD��������
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 13:36:26
*@Drscription: 
***********************************************************************/
#define ADC_PAD_SETTING_DATA    (SRE_0_SLOW_SLEW_RATE| \
                                 DSE_6_R0_6| \
								 SPEED_1_MEDIUM_100MHz| \
								 ODE_0_OPEN_DRAIN_DISABLED| \
								 PKE_0_PULL_KEEPER_DISABLED| \
								 PUE_1_PULL_SELECTED| \
								 PUS_3_22K_OHM_PULL_UP| \
								 HYS_0_HYSTERESIS_DISABLED)   
                                 
/***********************************************************************
*@Function: void ADC_PAD_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 13:35:28
*@Drscription: pad����
***********************************************************************/
void ADC_PAD_config(void)
{
    IOMUXC_SetPinConfig(ADC_IOMUXC,ADC_PAD_SETTING_DATA);
}

/***********************************************************************
*@Function: void ADC_IOMUXC_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 13:55:00
*@Drscription: MUX����
***********************************************************************/
void ADC_IOMUXC_config(void)
{
    IOMUXC_SetPinMux(ADC_IOMUXC,0U);
}

/***********************************************************************
*@Function: void ADC_GPIO_Config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 13:57:04
*@Drscription: adc GPIO������
***********************************************************************/
void ADC_GPIO_Config(void)
{
    gpio_pin_config_t adc_config;
	/*
    *����ģʽ
    *����߼���ƽ��Ч
    *��ʹ���ж�
    */
	adc_config.direction=kGPIO_DigitalInput;
	adc_config.outputLogic=1;
	adc_config.interruptMode=kGPIO_NoIntmode;
    
    GPIO_PinInit(ADC_GPIO_PORT,ADC_GPIO_PIN,&adc_config);
}


/***********************************************************************
*@Function: void ADC_mode_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 14:02:56
*@Drscription: adc��ʼ�����á�����Ӳ����ƽ��������adcͨ����У�顢�����ж�
***********************************************************************/
void ADC_mode_config(void)
{
    adc_config_t adc_config;
    adc_channel_config_t adc_channle_config;
    /*���ADC��ʼ������*/
    ADC_GetDefaultConfig(&adc_config);

    /*adc�Ĳ����ʸ�Ϊ12λ����*/
    adc_config.resolution=kADC_Resolution12Bit;
    ADC_Init(ADC_PORT,&adc_config);
    /*����Ӳ����ƽ��*/
    ADC_SetHardwareAverageConfig(ADC_PORT,kADC_HardwareAverageCount32);

    /*
    *ADCͨ��13
    *ʹ��ADCת������ж�
    */
    adc_channle_config.channelNumber=ADC_CHANNLE;
	adc_channle_config.enableInterruptOnConversionCompleted=true;
    ADC_SetChannelConfig(ADC_PORT,ADC_CHANNLE_GROUP,&adc_channle_config);

    /*ADCУ׼*/
    if(kStatus_Success==ADC_DoAutoCalibration(ADC_PORT))
    {
        printf("У׼���\n");
    }
    else
    {
        printf("У׼ʧ��\n");
    }

    /*�����ж����ȼ�*/
    IRQN_priority(4,1,1,ADC_IRQ);

    /*����ADC�ж�*/
    EnableIRQ(ADC_IRQ);
}

/***********************************************************************
*@Function: void ADC_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 14:02:14
*@Drscription: adc��ʼ��
***********************************************************************/
void ADC_config(void)
{
    ADC_IOMUXC_config();
    ADC_IOMUXC_config();
    ADC_GPIO_Config();
    ADC_mode_config();
}

/***********************************************************************
*@Function: void ADC_IRQHandler(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 15:07:14
*@Drscription: adc�жϺ���
***********************************************************************/
void ADC_IRQHandler(void)
{
    /*ת����ɱ�־*/
    ADC_ConversionDoneFlag=true;
    ADC_ConvertedValue=ADC_GetChannelConversionValue(ADC_PORT,ADC_CHANNLE_GROUP);

}

