/*
 * API_uart.c
 *
 *  Created on: 24/09/2026
 *      Author:
 */

#include "API_uart.h"

/* ============================================================== */
typedef enum
{
    UART_OK,
    UART_ERROR_HAL,
	UART_ERROR_PARAM,
    UART_TIMEOUT

} uart_status_t;
/* ============================================================== */

UART_HandleTypeDef huart2;
static uart_status_t uart_status = UART_OK;
/* ============================================================== */

static uint16_t getStringLength(uint8_t * pstring);
/* ============================================================== */

/**
  * @brief Función para la inicialización del puerto UART.
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
		char mensaje[50];
		snprintf(mensaje, sizeof(mensaje), "Baudrate: %" PRIu32 " bps\n\r", baudrate);
		uartSendString((uint8_t*)"Puerto:\n\r");
		uartSendString((uint8_t*)mensaje);
		uartSendString((uint8_t*)"Parity: NONE\n\r");
		uartSendString((uint8_t*)"Stop bits: 1\n\r");
		return true;
	}
}

/**
  * @brief Función para enviar un string por el puerto USART sin conocer su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
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

		case HAL_TIMEOUT:
			uart_status = UART_TIMEOUT;
			break;

		default:
			uart_status = UART_ERROR_HAL;
			break;
	}
}

/**
  * @brief Función para enviar un string por el puerto USART conociendo su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
  * @param uint16_t size: Tamaño del texto.
  * @retval None.
  */
void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_StatusTypeDef hal_status;

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE)){
		uart_status = UART_ERROR_PARAM;
		return;
	}

	hal_status = HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT_MS);

	switch (hal_status)
	{
		case HAL_OK:
			uart_status = UART_OK;
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
  * @brief Función para recibir un string por el puerto USART conociendo su tamaño.
  * @param uint8_t * pstring: Puntero para el buffer que almacenara  el string.
  * @param uint16_t size: Tamaño del texto a recibir.
  * @retval None.
  */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	HAL_StatusTypeDef hal_status;

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE)){
		uart_status = UART_ERROR_PARAM;
		return;
	}

	hal_status = HAL_UART_Receive(&huart2, pstring, size, UART_TIMEOUT_MS); // cambio de UART_TIMEOUT_MS a 0, para no bloqueante y verificar con HAL_TIMEOUT

	switch (hal_status)
	{
		case HAL_OK:
			uart_status = UART_OK;
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
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
  * @retval uint16_t: Tamaño del buffer.
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
  * UART_OK, UART_ERROR_HAL, UART_ERROR_PARAM o UART_TIMEOUT.
  * @param None.
  * @retval uint8_t: Estado de la transmisión.
  */
uint8_t uartGetStatus(void){
	return uart_status;
}

/**
  * @brief Función que retorna el estado de un pin.
  * @param GPIO_TypeDef* port: Puerto.
  * @param uint16_t pin: Pin.
  * @retval bool_t: Estado del pin.
  * 		true -> Pin en 1.
  * 		false -> Pin en 0.
  */
bool_t uartGetPinState(GPIO_TypeDef* port, uint16_t pin){

	bool_t pin_state;

	pin_state = HAL_GPIO_ReadPin(port, pin);

	return pin_state;
}
