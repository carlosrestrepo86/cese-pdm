/*
 * API_uart.c
 *
 *  Created on: 24/09/2026
 *      Author: c_and
 */

#include "API_uart.h"


UART_HandleTypeDef huart1;

static void UART_Handler(void);

bool_t uartInit(){

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		return false;
	}else{
		return true;
	}
}

void uartSendString(uint8_t * pstring){
	HAL_UART_Transmit(&huart1, pstring, sizeof(&pstring) / sizeof(uint8_t), UART_TIMEOUT_MS);
}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Transmit(&huart1, pstring, size, UART_TIMEOUT_MS);
}

void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

}

static void UART_Handler(void)
{
  while (1)
  {
  }
}
