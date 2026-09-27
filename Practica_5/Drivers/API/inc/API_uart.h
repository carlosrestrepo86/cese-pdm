/*
 * API_uart.h
 *
 *  Created on: 24/09/2026
 *      Author: c_and
 */

#ifndef DRIVERS_API_INC_API_UART_H_
#define DRIVERS_API_INC_API_UART_H_

#include "API_delay.h"
#include "stm32f4xx_hal.h"

#define UART_TIMEOUT_MS 100
#define MAX_SIZE 255

bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* DRIVERS_API_INC_API_UART_H_ */
