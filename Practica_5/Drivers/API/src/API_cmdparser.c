/*
 * API_cmdparser.c
 *
 *  Created on: 27/09/2026
 *      Author: c_and
 */
#include "API_cmdparser.h"

/* ============================================================== */
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
/* ============================================================== */

static cmd_state_t current_state;
static cmd_action_t action = CMD_NONE;
static cmd_status_t status = CMD_OK;
static uint8_t buffer[CMD_MAX_LINE];

uint8_t byte;
uint8_t buffer_index = 0;
/* ============================================================== */

static void cmdProcessLine(void);

/**
  * @brief Función para inicializar la MEF.
  * @param NONE.
  * @retval NONE.
  */
void cmdParserInit(void){
	current_state = CMD_IDLE;
}

/**
  * @brief Función para actualizar la MEF.
  * @param NONE.
  * @retval NONE.
  */
void cmdPoll(void){

	switch(current_state){
		case CMD_IDLE:

			/* Lectura de un byte para validar el inicio de la trama
			 * Verificar que sea diferente de caracter fin de linea */
			uartReceiveStringSize(&byte, 1);

			if ((byte != '\n') && (byte != '\r') && (byte != '\0')){
				buffer[buffer_index] = byte;
				buffer_index++;
				current_state = CMD_RECEIVING;
			}
			break;

		case CMD_RECEIVING:

			/* Almacenar en el buffer los datos recibidos hasta
			 * encontrar uno de los finales de linea */
			uartReceiveStringSize(&byte, 1);

			if ((byte != '\n') && (byte != '\r')){
				buffer[buffer_index] = byte;
				buffer_index++;
			}else{
				current_state = CMD_PROCESS;
			}

			/* Verificar que no se supere la cantidad maxima de caracteres permitidos */
			if (buffer_index == CMD_MAX_LINE){
				status = CMD_ERR_OVERFLOW;
				current_state = CMD_ERROR;
			}
			break;

		case CMD_PROCESS:

			/* Procesar la linea recibida y controlar si son comandos validos */
			cmdProcessLine();

			if (status == CMD_OK)
				current_state = CMD_EXEC;
			else{
				current_state = CMD_ERROR;
			}
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
			action = CMD_NONE;
			current_state = CMD_IDLE;
			break;

		case CMD_ERROR:

			uartSendString((uint8_t*)"Error de comando\r\n");
			buffer_index = 0;
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer.
			action = CMD_NONE;
			current_state = CMD_IDLE;
			break;

		default:

			cmdParserInit();
			buffer_index = 0;
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer.
			action = CMD_NONE;
			break;
	}
}

/**
  * @brief Función para procesar una linea recibida por el USART.
  * @param NONE.
  * @retval bool_t: False -> Error en el comando o argumento.
  *                 True  -> Comando y argumento validos.
  */
static void cmdProcessLine(void){

	uint8_t *command = NULL;
	uint8_t *argument = NULL;

	/* Ignorar lineas que inicien con # o / */
	if ((buffer[0] == '#') || ((buffer[0] == '/') && (buffer[1] == '/'))){
		status = CMD_ERR_SYNTAX;
		return;
	}

	command = buffer;

	/* Separa el comando del argumento para procesarlos independientemente. */
	for (uint8_t i = 0; i < buffer_index; i++){
		if (buffer[i] == ','){
			buffer[i] = '\0';
			argument = &buffer[i + 1];
			break;
		}
	}

	/* Verifica el comando recibido para guardar los parametros y leer en EXEC */
	if (strcmp((char *)command, "LED") == 0){
		if (argument != NULL){
			if(strcmp((char *)argument, "ON") == 0){
				action = CMD_LED_ON;
				status = CMD_OK;
			}else if(strcmp((char *)argument, "OFF") == 0){
				action = CMD_LED_OFF;
				status = CMD_OK;
			}else if(strcmp((char *)argument, "TOGGLE") == 0){
				action = CMD_LED_TOGGLE;
				status = CMD_OK;
			}else{
				status = CMD_ERR_UNKNOWN;
			}
		}else{
			status = CMD_ERR_SYNTAX;
		}
	}else if (strcmp((char *)command, "STATUS") == 0){
		action = CMD_LED_STATUS;
		status = CMD_OK;
	} else if (strcmp((char *)command, "HELP") == 0){
		action = CMD_HELP;
		status = CMD_OK;
	} else{
		status = CMD_ERR_UNKNOWN;
	}
}

/**
  * @brief Función para enviar el menu de ayuda.
  * @param NONE.
  * @retval NONE.
  */
void cmdPrintHelp(void){
	uartSendString((uint8_t*)"Comandos disponibles:\r\n");
	uartSendString((uint8_t*)"LED,ON\r\n");
	uartSendString((uint8_t*)"LED,OFF\r\n");
	uartSendString((uint8_t*)"LED,TOGGLE\r\n");
	uartSendString((uint8_t*)"STATUS\r\n");
}
