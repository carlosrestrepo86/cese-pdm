/*
 * API_uart.c
 *
 *  Created on: 24/09/2026
 *      Author: c_and
 */

#include "API_uart.h"
#include "API_delay.h"

typedef enum
{
    UART_OK,
    UART_ERROR_PARAM,
    UART_ERROR_HAL,
    UART_BUSY,
    UART_TIMEOUT

} uart_status_t;

UART_HandleTypeDef huart2;
static uart_status_t uart_status = UART_OK;

static uint16_t getStringLength(uint8_t * pstring);

/**
  * @brief Función para la inicialización del puerto USART.
  * @param uint32_t baudrate: Velocidad de transmisión.
  * @retval bool_t: False -> Si se presenta un error en la inicialización.
  *                 True  -> Puerto USART inicializado correctamente.
  */
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
		uartSendString((uint8_t*)"Puerto:\n\r");
		uartSendString((uint8_t*)"Baudrate: 115200\n\r");
		uartSendString((uint8_t*)"Parity: NONE\n\r");
		uartSendString((uint8_t*)"Stop bits: 1\n\r");
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

	uint16_t size;
	HAL_StatusTypeDef hal_status;

	if (pstring == NULL){
		uart_status = UART_ERROR_PARAM;
		return;
	}

	size = getStringLength(pstring);

	if ((size == 0U) || (size > MAX_STRING_SIZE)){
		uart_status = UART_ERROR_PARAM;
		return;
	}

	hal_status = HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT_MS);

	switch (hal_status)
	{
		case HAL_OK:
			uart_status = UART_OK;
			break;

		case HAL_BUSY:
			uart_status = UART_BUSY;
			break;

		case HAL_TIMEOUT:
			uart_status = UART_TIMEOUT;
			break;

		default:
			uart_status = UART_ERROR_HAL;
			break;
	}
}

/**
  * @brief Función para enviar un string por el puerto USART
  * conociendo su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del array.
  * @param uint16_t size: Tamaño del texto.
  * @retval None.
  */
void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_StatusTypeDef hal_status;

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE)){
		uart_status = UART_ERROR_PARAM;
		return;
	}

	hal_status = uart_status = HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT_MS);

	switch (hal_status)
	{
		case HAL_OK:
			uart_status = UART_OK;
			break;

		case HAL_BUSY:
			uart_status = UART_BUSY;
			break;

		case HAL_TIMEOUT:
			uart_status = UART_TIMEOUT;
			break;

		default:
			uart_status = UART_ERROR_HAL;
			break;
	}
}

/**
  * @brief Función para recibir un string por el puerto USART
  * conociendo su tamaño.
  * @param uint8_t * pstring: Puntero para el array que almacenara  el string.
  * @param uint16_t size: Tamaño del texto a recibir.
  * @retval None.
  */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	HAL_StatusTypeDef hal_status;

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE)){
		uart_status = UART_ERROR_PARAM;
		return;
	}

	hal_status = uart_status = HAL_UART_Receive(&huart2, pstring, size, UART_TIMEOUT_MS); // cambio de UART_TIMEOUT_MS a 0, para no bloqueante y verificar con HAL_TIMEOUT

	switch (hal_status)
	{
		case HAL_OK:
			uart_status = UART_OK;
			break;

		case HAL_BUSY:
			uart_status = UART_BUSY;
			break;

		case HAL_TIMEOUT:
			uart_status = UART_TIMEOUT;
			break;

		default:
			uart_status = UART_ERROR_HAL;
			break;
	}
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
	return uart_status;
}

bool_t uartGetPinState(GPIO_TypeDef* port, uint16_t pin){

	bool_t pin_state;

	pin_state = HAL_GPIO_ReadPin(port, pin);

	return pin_state;
}
