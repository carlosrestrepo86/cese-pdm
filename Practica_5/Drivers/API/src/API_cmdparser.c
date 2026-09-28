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

			while ((byte != '\n') && (byte != '\r')){ // validar tamaño para salir de while sin fin de trama
				uartReceiveStringSize(&byte, 1);

				if ((byte != '\n') && (byte != '\r')){
					buffer[buffer_index] = byte;
					buffer_index++;
				}
			}

//			buffer[buffer_index] = '\0';
//			buffer_index++;
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
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer.
			current_state = CMD_IDLE;
			break;

		case CMD_ERROR:
			break;
		default:
			break;
	}
}

static void cmdProcessLine(void){

	uint8_t *token[CMD_MAX_TOKENS];
	uint8_t count = 1;
	token[0] = buffer;

	for (uint8_t i = 0; i < buffer_index; i++){
		if (buffer[i] == ','){
			buffer[i] = '\0';
			token[count] = &buffer[i + 1];
			count++;
		}
	}

//	uartSendString(token[0]);
	uartSendString(token[1]);
	if (strcmp((char *)token[0], "LED") == 0){
		if(strcmp((char *)token[1], "ON") == 0)
			action = CMD_LED_ON;
		if(strcmp((char *)token[1], "OFF") == 0)
			action = CMD_LED_OFF;
		if(strcmp((char *)token[1], "TOGGLE") == 0)
			action = CMD_LED_TOGGLE;
	}else if (strcmp((char *)token[0], "STATUS") == 0){
		action = CMD_LED_STATUS;
	}else if (strcmp((char *)token[0], "HELP") == 0){
		action = CMD_HELP;
	}

}

// Imprime por USART la lista de comandos disponibles
void cmdPrintHelp(void){

}
