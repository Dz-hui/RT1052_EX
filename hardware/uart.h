/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-01 10:45:12
*@FilePath: \hello_world\component\uart\uart.h
*@Drscription: 
***********************************************************************/
#ifndef __UART__H
#define __UART__H

#include "fsl_common.h"


#define USB_UART_TX_GPIO       GPIO1
#define USB_UART_TX_PIN        (12U)
#define USB_UART_TX_IOMUXC     IOMUXC_GPIO_AD_B0_12_LPUART1_TX

#define USB_UART_RX_GPIO       GPOIO1
#define USB_UART_RX_PIN        (13U)
#define USB_UART_RX_IOMUXC     IOMUXC_GPIO_AD_B0_13_LPUART1_RX

#define USB_UART_PORT          LPUART1
#define USB_UART_CLK_FREQ      BOARD_DebugConsoleSrcFreq()


void USB_UART_config(void);
void UART_senddata(LPUART_Type *base,uint8_t data);
void UART_sendstring(LPUART_Type *base,const char *str);

#endif






