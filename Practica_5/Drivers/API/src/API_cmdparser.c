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

static bool_t cmdProcessLine(void);

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

			uartReceiveStringSize(&byte, 1);

			if ((byte != '\n') && (byte != '\r')){
				buffer[buffer_index] = byte;
				buffer_index++;
			}else{
				current_state = CMD_PROCESS;
			}

			if (buffer_index == CMD_MAX_LINE)
				current_state = CMD_ERROR;

			/*while ((byte != '\n') && (byte != '\r')){ // validar tamaño para salir de while sin fin de trama
				uartReceiveStringSize(&byte, 1);

				if ((byte != '\n') && (byte != '\r')){
					buffer[buffer_index] = byte;
					buffer_index++;
				}
			}

			current_state = CMD_PROCESS;*/
			break;

		case CMD_PROCESS:

			bool_t line_status;

			line_status = cmdProcessLine();

			if (line_status)
				current_state = CMD_EXEC;
			else
				current_state = CMD_ERROR;

			break;

		case CMD_EXEC:

			if (action == CMD_LED_ON)
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

			if (action == CMD_LED_OFF)
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

			if (action == CMD_LED_TOGGLE)
				HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

			if (action == CMD_LED_STATUS){
				if (uartGetPinState(LD2_GPIO_Port, LD2_Pin))
					uartSendString((uint8_t*)"LED is ON\r\n");
				else
					uartSendString((uint8_t*)"LED is OFF\r\n");
			}

			if (action == CMD_HELP)
				cmdPrintHelp();

			buffer_index = 0;
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer.
			current_state = CMD_IDLE;
			break;

		case CMD_ERROR:

			uartSendString((uint8_t*)"Error de comando\r\n");
			buffer_index = 0;
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer.
			break;

		default:

			cmdParserInit();
			buffer_index = 0;
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer.
			break;
	}
}

static bool_t cmdProcessLine(void){

	uint8_t *command = NULL;
	uint8_t *argument = NULL;
	bool_t line_status = false;

	command = buffer;

	for (uint8_t i = 0; i < buffer_index; i++){
		if (buffer[i] == ','){
			buffer[i] = '\0';
			argument = &buffer[i + 1];
			break;
		}
	}

	//	uartSendString(token[0]);
	//	uartSendString(token[1]);
	if (strcmp((char *)command, "LED") == 0){
		if (argument != NULL){
			if(strcmp((char *)argument, "ON") == 0){
				action = CMD_LED_ON;
				line_status = true;
			}
			if(strcmp((char *)argument, "OFF") == 0){
				action = CMD_LED_OFF;
				line_status = true;
			}
			if(strcmp((char *)argument, "TOGGLE") == 0){
				action = CMD_LED_TOGGLE;
				line_status = true;
			}
		}
	}

	if (strcmp((char *)command, "STATUS") == 0){
		action = CMD_LED_STATUS;
		line_status = true;
	}

	if (strcmp((char *)command, "HELP") == 0){
		action = CMD_HELP;
		line_status = true;
	}

	return line_status;
}

// Imprime por USART la lista de comandos disponibles
void cmdPrintHelp(void){
	uartSendString((uint8_t*)"Comandos disponibles:\r\n");
	uartSendString((uint8_t*)"LED,ON\r\n");
	uartSendString((uint8_t*)"LED,OFF\r\n");
	uartSendString((uint8_t*)"LED,TOGGLE\r\n");
	uartSendString((uint8_t*)"STATUS\r\n");
}
