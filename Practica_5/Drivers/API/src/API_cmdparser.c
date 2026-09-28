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
}cmd_state_t;

typedef enum
{
    CMD_NONE,
	CMD_LED_ON,
    CMD_LED_OFF,
    CMD_LED_TOGGLE,
	CMD_LED_STATUS,
	CMD_HELP
} cmd_action_t;


static cmd_state_t current_state;
static cmd_action_t action = CMD_NONE;
static uint8_t buffer[CMD_MAX_LINE];
uint8_t byte;
uint8_t buffer_index = 0;

static void cmdProcessLine(void);

// Inicializa el módulo parser de comandos
void cmdParserInit(void){
	current_state = CMD_IDLE;
}

// Maquina de estado del parser. Llamado periodicamente desde el bucle
// procesa hasta 16 bytes por invocación (no bloqueante)
void cmdPoll(void){

	switch(current_state){
		case CMD_IDLE:

			uartReceiveStringSize(&byte, 1);

			if ((byte != '\n') && (byte != '\r') && (byte != '\0')){
				buffer[buffer_index] = byte;
				buffer_index++;
				current_state = CMD_RECEIVING;
			}
			break;

		case CMD_RECEIVING:

			while ((byte != '\n') && (byte != '\r')){
				uartReceiveStringSize(&byte, 1);
				buffer[buffer_index] = byte;
				buffer_index++;
			}

			buffer[buffer_index] = '\0';
			current_state = CMD_PROCESS;
			break;

		case CMD_PROCESS:

			cmdProcessLine();
			current_state = CMD_EXEC;
			break;

		case CMD_EXEC:

			if (action == CMD_LED_ON)
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

			if (action == CMD_LED_OFF)
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

			buffer_index = 0;
			current_state = CMD_IDLE;
			break;

		case CMD_ERROR:
			break;
		default:
			break;
	}
}

static void cmdProcessLine(void){
	uartSendStringSize(buffer, 7);
	if(strncmp((char*)buffer, "LED ON", 6) == 0){
		action = CMD_LED_ON;
	}

	if(strncmp((char*)buffer, "LED OFF", 7) == 0){
		action = CMD_LED_OFF;
	}
}

// Imprime por USART la lista de comandos disponibles
void cmdPrintHelp(void){

}
