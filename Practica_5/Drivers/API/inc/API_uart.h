/*
 * API_uart.h
 *
 *  Created on: 24/09/2026
 *      Author: c_and
 */

#ifndef DRIVERS_API_INC_API_UART_H_
#define DRIVERS_API_INC_API_UART_H_

#include <stdio.h>
#include <inttypes.h>
#include "API_delay.h"
#include "stm32f4xx_hal.h"

typedef enum
{
    UART_NONE,
	UART_OK,
    UART_ERROR_HAL,
	UART_ERROR_PARAM,
    UART_TIMEOUT

} uart_status_t;

#define UART_TIMEOUT_MS 50 // 115200, 11.520 bytes por segundo = 1 byte cada 0.08 ms para 128 aprox 11 ms
#define MAX_STRING_SIZE 256

bool_t uartInit(uint32_t baudrate);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
uart_status_t uartGetStatus(void);
bool_t uartGetPinState(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* DRIVERS_API_INC_API_UART_H_ */
