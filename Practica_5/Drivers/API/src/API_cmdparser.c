/*
 * API_cmdparser.c
 *
 *  Created on: 27/09/2026
 *      Author: c_and
 */
#include "API_cmdparser.h"
#include "API_uart.h"

/* ========================== TYPEDEFS ========================== */

typedef enum{
	CMD_IDLE,
	CMD_RECEIVING,
	CMD_PROCESS,
	CMD_EXEC,
	CMD_ERROR
}parserState_t;

static parserState_t current_state;
static uint8_t data[16]; // 16 bytes

// Inicializa el módulo parser de comandos
void cmdParserInit(void){
	current_state = CMD_IDLE;
}

// Maquina de estado del parser. Llamado periodicamente desde el bucle
// procesa hasta 16 bytes por invocación (no bloqueante)
void cmdPoll(void){
	switch(current_state){
		case CMD_IDLE:
			uartReceiveStringSize(data, 1);

			if ((data[0] != '\n') && (data[0] != '\r') && (data[0] != '\0'))
				current_state = CMD_RECEIVING;

			break;

		case CMD_RECEIVING:
			uartSendStringSize(data, 1);
			break;
		case CMD_PROCESS:
			break;
		case CMD_EXEC:
			break;
		case CMD_ERROR:
			break;
		default:
			break;
	}
}

// Imprime por USART la lista de comandos disponibles
void cmdPrintHelp(void);
