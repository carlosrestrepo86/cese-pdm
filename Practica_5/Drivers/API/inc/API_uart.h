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

#define UART_TIMEOUT_MS 50 // 115200, 11.520 bytes por segundo = 1 byte cada 0.08 ms para 128 aprox 11 ms
#define MAX_STRING_SIZE 256

bool_t uartInit(void);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
uint8_t uartGetStatus(void);
bool_t uartGetPinState(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* DRIVERS_API_INC_API_UART_H_ */
