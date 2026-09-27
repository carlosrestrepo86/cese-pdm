/*
 * API_uart.c
 *
 *  Created on: 24/09/2026
 *      Author: c_and
 */

#include "API_uart.h"
#include "API_delay.h"

UART_HandleTypeDef huart2;

static void UART_Handler(void);
static uint16_t getStringLength(uint8_t * pstring);

bool_t uartInit(){

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		return false;
	}else{
		uint8_t config[] = "Configuración: 115200,8N1\n\r"; // \0 incluido implicitamente.
		uartSendString(config);
		return true;
	}
}

void uartSendString(uint8_t * pstring){
	if (pstring == NULL)
		UART_Handler();

	uint16_t size = getStringLength(pstring);

	if (size == 0 || size > 256)
		UART_Handler();

	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT_MS);

	switch(status){
		case HAL_OK:
			break;
		case HAL_ERROR:
			UART_Handler();
			break;
		case HAL_BUSY:
			// Falta -----------------
			break;
		case HAL_TIMEOUT:
			// Falta -----------------
			break;
		default:
			break;
	}
}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	if (pstring == NULL || size == 0 || size > 256)
		UART_Handler();

	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT_MS);

	switch(status){
		case HAL_OK:
			break;
		case HAL_ERROR:
			UART_Handler();
			break;
		case HAL_BUSY:
			// Falta -----------------
			break;
		case HAL_TIMEOUT:
			// Falta ----------------
			break;
		default:
			break;
	}
}

void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

}

static uint16_t getStringLength(uint8_t * pstring){

	uint16_t size = 0;
	for (uint16_t i = 0; i < MAX_STRING_SIZE; i++){
		if (*(pstring + i) == '\0'){
			size = i;
			break;
		}
	}
	return size;
}

static void UART_Handler(void)
{
  while (1)
  {
  }
}
