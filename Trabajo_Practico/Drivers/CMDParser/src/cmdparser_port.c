/*
 * API_uart.c
 *
 *  Created on: 24/09/2026
 *      Author:
 */

#include "cmdparser_port.h"

/* ============================================================== */
static UART_HandleTypeDef hcmdparser;

/* ============================================================== */

/**
  * @brief Función para enviar un string por el puerto USART sin conocer su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
  * @retval None.
  */
bool_t CMDParser_Port_SendString(uint8_t * pstring, uint8_t size){

	HAL_StatusTypeDef hal_status;

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
		return false;

	hal_status = HAL_UART_Transmit(&hcmdparser, pstring, size, UART_TIMEOUT_MS);

	if(hal_status != HAL_OK)
		return false;
	else
		return true;
}

/**
  * @brief Función para enviar un string por el puerto USART conociendo su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
  * @param uint16_t size: Tamaño del texto.
  * @retval None.
  */
bool_t CMDParser_Port_SendStringSize(uint8_t * pstring, uint8_t size){

	HAL_StatusTypeDef hal_status;

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
		return false;

	hal_status = HAL_UART_Transmit(&hcmdparser, pstring, size, UART_TIMEOUT_MS);

	if(hal_status != HAL_OK)
		return false;
	else
		return true;
}

/**
  * @brief Función para recibir un string por el puerto USART conociendo su tamaño.
  * @param uint8_t * pstring: Puntero para el buffer que almacenara  el string.
  * @param uint16_t size: Tamaño del texto a recibir.
  * @retval None.
  */
bool_t CMDParser_Port_ReceiveStringSize(uint8_t * pstring, uint8_t size){

	HAL_StatusTypeDef hal_status;

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
		return false;

	hal_status = HAL_UART_Receive(&hcmdparser, pstring, size, UART_TIMEOUT_MS); // cambio de UART_TIMEOUT_MS a 0, para no bloqueante y verificar con HAL_TIMEOUT

	if(hal_status != HAL_OK)
		return false;
	else
		return true;
}

/**
* @brief Inicialización de UART MSP.
* @param huart: Puntero al manejador de UART.
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef UARTx_InitStruct = {0};

  if(huart->Instance == CMDPARSER_UART)
  {
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    UARTx_InitStruct.Pin = CMDPARSER_UART_TX_PIN | CMDPARSER_UART_RX_PIN;
    UARTx_InitStruct.Mode = GPIO_MODE_AF_PP;
    UARTx_InitStruct.Pull = GPIO_NOPULL;
    UARTx_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    UARTx_InitStruct.Alternate = CMDPARSER_UART_AF;

    HAL_GPIO_Init(GPIOA, &UARTx_InitStruct);
  }
}

/**
* @brief Desinicialización de UART MSP.
* @param huart: Puntero al manejador de UART.
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance == CMDPARSER_UART)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(CMDPARSER_UART_GPIO_PORT, CMDPARSER_UART_TX_PIN | CMDPARSER_UART_RX_PIN);
  }
}

/**
  * @brief Función para la inicialización del puerto UART.
  * @param NONE.
  * @retval bool_t: False -> Si se presenta un error en la inicialización.
  *                 True  -> Puerto USART inicializado correctamente.
  */
bool_t CMDParser_Port_Init(){

	hcmdparser.Instance = CMDPARSER_UART;
	hcmdparser.Init.BaudRate = BAUDRATE;
	hcmdparser.Init.WordLength = UART_WORDLENGTH;
	hcmdparser.Init.StopBits = UART_STOPBITS;
	hcmdparser.Init.Parity = UART_PARITY;
	hcmdparser.Init.Mode = UART_MODE_TX_RX;
	hcmdparser.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	hcmdparser.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&hcmdparser) != HAL_OK)
		return false;
	else
		return true;
}
