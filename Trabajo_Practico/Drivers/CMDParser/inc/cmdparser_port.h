/*
 * API_uart.h
 *
 *  Created on: 24/09/2026
 *      Author: c_and
 */

#ifndef DRIVERS_CMDPARSER_INC_CMDPARSER_PORT_H_
#define DRIVERS_CMDPARSER_INC_CMDPARSER_PORT_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef bool bool_t;

#define UART_TIMEOUT_MS 50 // 115200, 11.520 bytes por segundo = 1 byte cada 0.08 ms para 128 aprox 11 ms
#define MAX_STRING_SIZE 256

#define CMDPARSER_UART  USART2
#define BAUDRATE        115200
#define UART_WORDLENGTH UART_WORDLENGTH_8B
#define UART_STOPBITS   UART_STOPBITS_1
#define UART_PARITY     UART_PARITY_NONE

#define CMDPARSER_UART_GPIO_PORT GPIOA
#define CMDPARSER_UART_TX_PIN    GPIO_PIN_2
#define CMDPARSER_UART_RX_PIN    GPIO_PIN_3
#define CMDPARSER_UART_AF        GPIO_AF7_USART2

bool_t CMDParser_Port_Init();
bool_t CMDParser_Port_SendString(uint8_t * pstring, uint8_t size);
bool_t CMDParser_Port_SendStringSize(uint8_t * pstring, uint8_t size);
bool_t CMDParser_Port_ReceiveStringSize(uint8_t * pstring, uint8_t size);

#endif /* DRIVERS_CMDPARSER_INC_CMDPARSER_PORT_H_ */
