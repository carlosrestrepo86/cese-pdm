/*
 * API_uart.c
 *
 *  Created on: 24/09/2026
 *      Author: c_and
 */

#include "API_uart.h"
#include "API_delay.h"

UART_HandleTypeDef huart2;
static uint8_t rx_tx_status;

static uint16_t getStringLength(uint8_t * pstring);

/**
  * @brief Función para la inicialización del puerto USART.
  * @param uint32_t baudrate: Velocidad de transmisión.
  * @retval bool_t: False -> Si se presenta un error en la inicialización.
  *                 True  -> Puerto USART inicializado correctamente.
  */
bool_t uartInit(uint32_t baudrate){

	huart2.Instance = USART2;
	huart2.Init.BaudRate = baudrate;
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
		uint8_t config[100];
		snprintf(config, sizeof(config), "%s%", "Configuracion: ", baudrate);
		uartSendString(config);
		return true;
	}
}

/**
  * @brief Función para enviar un string por el puerto USART
  * sin conocer su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del array.
  * @retval None.
  */
void uartSendString(uint8_t * pstring){

	uint16_t size = getStringLength(pstring);

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
		rx_tx_status = HAL_ERROR;

	rx_tx_status = HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT_MS);
}

/**
  * @brief Función para enviar un string por el puerto USART
  * conociendo su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del array.
  * @param uint16_t size: Tamaño del texto.
  * @retval None.
  */
void uartSendStringSize(uint8_t * pstring, uint16_t size){

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
		rx_tx_status = HAL_ERROR;

	rx_tx_status = HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT_MS);
}

/**
  * @brief Función para recibir un string por el puerto USART
  * conociendo su tamaño.
  * @param uint8_t * pstring: Puntero para el array que almacenara  el string.
  * @param uint16_t size: Tamaño del texto a recibir.
  * @retval None.
  */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
			rx_tx_status = HAL_ERROR;

	rx_tx_status = HAL_UART_Receive(&huart2, pstring, size, UART_TIMEOUT_MS);
}

/**
  * @brief Función que recorre las posiciones de un array de texto hasta encontrar
  * el caracter nulo (\n) y retorna su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del array.
  * @retval uint16_t: Tamaño del array.
  */
static uint16_t getStringLength(uint8_t * pstring){

	uint16_t size = 0;
	for (uint8_t i = 0; i < MAX_STRING_SIZE; i++){
		if (*(pstring + i) == '\0'){
			size = i;
			break;
		}
	}
	return size;
}

/**
  * @brief Función que retorna el estado de la transmisión por USART
  * HAL_OK, HAL_ERROR, HAL_BUSY o HAL_TIMEOUT.
  * @param None.
  * @retval uint8_t: Estado de la transmisión.
  */
uint8_t uartGetStatus(){
	return rx_tx_status;
}
