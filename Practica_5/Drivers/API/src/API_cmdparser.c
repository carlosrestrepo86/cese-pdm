/*
 * API_cmdparser.c
 *
 *  Created on: 27/09/2026
 *      Author: c_and
 */
#include "API_cmdparser.h"

/* ========================== TYPEDEFS ========================== */

typedef enum{
	CMD_IDLE,
	CMD_RECEIVING,
	CMD_PROCESS,
	CMD_EXEC,
	CMD_ERROR
}parserState_t;

static parserState_t current_state;
static uint8_t byte;
static uint8_t buffer[CMD_MAX_LINE];
static uint8_t index = 0;
static uint8_t parser_status;

// Inicializa el módulo parser de comandos
void cmdParserInit(void){
	current_state = CMD_IDLE;
}

// Maquina de estado del parser. Llamado periodicamente desde el bucle
// procesa hasta 16 bytes por invocación (no bloqueante)
void cmdPoll(void){
	switch(current_state){
		case CMD_IDLE:

			uartReceiveStringSize(&buffer[index], 1);

			if ((buffer[index] != '\n') && (buffer[index] != '\r') && (buffer[index] != '\0')){
//				buffer[index] = byte;
				index++;
				current_state = CMD_RECEIVING;
			}
			break;

		case CMD_RECEIVING:
			uartReceiveStringSize(&buffer[index], 15);

			current_state = CMD_PROCESS;
			break;

		case CMD_PROCESS:
			uartSendStringSize(buffer, 16);
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
