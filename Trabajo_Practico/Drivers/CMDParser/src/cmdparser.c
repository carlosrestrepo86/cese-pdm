/*
 * API_cmdparser.c
 *
 *  Created on: 27/09/2026
 *      Author: c_and
 */
#include "cmdparser.h"

/* ============================================================== */
typedef enum{
	CMD_IDLE,
	CMD_RECEIVING,
	CMD_PROCESS,
	CMD_EXEC,
	CMD_ERROR
}cmd_state_t;

typedef enum {
	CMD_OK = 0,
	CMD_ERR_OVERFLOW,
	CMD_ERR_SYNTAX,
	CMD_ERR_UNKNOWN,
	CMD_ERR_FLAG
}cmd_status_t;

typedef struct
{
    const char *command;
} cmd_command_t;

static const cmd_command_t commands[] =
{
		{"SERVO"},
		{"HELP"}
};
/* ============================================================== */

static cmd_state_t current_state;
static cmd_status_t status = CMD_OK;

static uint8_t buffer[CMD_MAX_LINE];
static bool_t command_pending = false;
static uint8_t buffer_index = 0;
static uint8_t byte;
static uint8_t angle;
/* ============================================================== */

/* ============================================================== */
static void cmdProcessLine(void);
static void toUpperCase(uint8_t *pchar);
static bool_t CMDParser_SendString(uint8_t * pstring);
static bool_t CMDParser_SendStringSize(uint8_t * pstring, uint8_t size);
static bool_t CMDParser_ReceiveStringSize(uint8_t * pstring, uint8_t size);
static uint16_t getStringLength(uint8_t * pstring);
static void CMDParser_PrintHelp(void);
static bool_t CMDParser_StringToUint8(uint8_t *string, uint8_t *value);

/**
  * @brief Función para inicializar la MEF.
  * @param NONE.
  * @retval NONE.
  */
void CMDParser_Init(void){
	current_state = CMD_IDLE;
}

bool_t CMDParser_Config(){
	return CMDParser_Port_Init();
}
/**
  * @brief Función para actualizar la MEF.
  * @param NONE.
  * @retval NONE.
  */
void CMDParser_Poll(void){

	switch(current_state){
		case CMD_IDLE:

			/* Lectura de un byte para validar el inicio de la trama. */
			if (!CMDParser_ReceiveStringSize(&byte, 1))
				break;

			toUpperCase(&byte);

			if ((byte != '\n') && (byte != '\r') && (byte != '\0')){
				buffer[buffer_index] = byte;
				buffer_index++;
				current_state = CMD_RECEIVING;
			}
			break;

		case CMD_RECEIVING:

			/* Almacenar en el buffer los datos recibidos hasta encontrar '\n' o '\r'*/
			if (!CMDParser_ReceiveStringSize(&byte, 1))
				break;

			toUpperCase(&byte);

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

			/* Procesar la linea recibida y controlar si son comandos validos. */
			cmdProcessLine();

			if (status == CMD_OK)
				current_state = CMD_EXEC;
			else{
				current_state = CMD_ERROR;
			}
			break;

		case CMD_EXEC:

			command_pending = true;
			buffer_index = 0;                  // Reiniciar el contador utilizado para guardar en el buffer.
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer para la proxima linea.
			current_state = CMD_IDLE;
			break;

		case CMD_ERROR:

			/* Envio de los mensajes de error y pasar al estado inicial */
			if (status == CMD_ERR_OVERFLOW)
				CMDParser_SendString((uint8_t*)"Line too long\r\n");

			if (status == CMD_ERR_UNKNOWN)
				CMDParser_SendString((uint8_t*)"Unknown command\r\n");

			if (status == CMD_ERR_SYNTAX)
				CMDParser_SendString((uint8_t*)"Bad arguments\r\n");

			buffer_index = 0;                  // Reiniciar el contador utilizado para guardar en el buffer.
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer para la proxima linea.
			current_state = CMD_IDLE;
			break;

		default:

			CMDParser_Init();
			buffer_index = 0;                  // Reiniciar el contador utilizado para guardar en el buffer.
			memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer para la proxima linea.
			break;
	}
}

bool_t CmdParser_GetCommand(uint8_t *value){

	if (value == NULL)
		return false;

	if (command_pending){
		command_pending = false;
		*value = angle;
		return true;
	}else
		return false;
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
		status = CMD_ERR_FLAG;
		return;
	}

	command = buffer;

	/* Separa el comando del argumento para procesarlos independientemente. */
	for (uint8_t i = 0; i < buffer_index; i++){
		if (buffer[i] == ',' || buffer[i] == '='){
			buffer[i] = '\0';
			argument = &buffer[i + 1];
			break;
		}
	}

	/* Verifica el comando recibido para guardar los parametros y leer en EXEC */
	if (strcmp((char *)command, commands[0].command) == 0){
		if (argument != NULL && argument[0] != '\0'){
			if (CMDParser_StringToUint8(argument, &angle))
				status = CMD_OK;
			else
				status = CMD_ERR_SYNTAX;
		}else{
			status = CMD_ERR_SYNTAX;
		}
	} else if (strcmp((char *)command, commands[1].command) == 0){
		CMDParser_PrintHelp();
		status = CMD_OK;
	} else{
		status = CMD_ERR_UNKNOWN;
	}
}

static bool_t CMDParser_StringToUint8(uint8_t *string, uint8_t *value){

	uint16_t number = 0;

	if (string == NULL)
		return false;

	while (*string != '\0')
	{
		if ((*string < '0') || (*string > '9'))
		{
			return false;
		}

		number = (number * 10) + (*string - '0');

		if (number > UINT8_MAX)
		{
			return false;
		}

		string++;
	}

	*value = (uint8_t)number;
	return true;
}

/**
  * @brief Función para enviar el menu de ayuda.
  * @param NONE.
  * @retval NONE.
  */
static void CMDParser_PrintHelp(void){
	CMDParser_SendString((uint8_t*)"Comandos disponibles:\r\n");
	CMDParser_SendString((uint8_t*)"SERVO,50\r\n");
}

/**
  * @brief Funcion para pasar las letras minusculas a mayusculas.
  * @param uint8_t *pchar: Puntero al caracter.
  * @retval Si el caracter esta en minuscula se realiza la conversion a mayuscula.
  */
static void toUpperCase(uint8_t *pchar){

	if (pchar == NULL){
		return;
	}

	if (*pchar >= 97 && *pchar <= 122){
		*pchar -= 32;
	}
}

/**
  * @brief Función para enviar un string por el puerto USART sin conocer su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
  * @retval None.
  */
static bool_t CMDParser_SendString(uint8_t * pstring){

	uint8_t size;

	if (pstring == NULL)
		return false;

	size = getStringLength(pstring);

	if ((size == 0U) || (size > MAX_STRING_SIZE))
		return false;

	return CMDParser_Port_SendString(pstring, size);
}


/**
  * @brief Función para enviar un string por el puerto USART conociendo su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
  * @param uint16_t size: Tamaño del texto.
  * @retval None.
  */
static bool_t CMDParser_SendStringSize(uint8_t * pstring, uint8_t size){

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
		return false;

	return CMDParser_Port_SendStringSize(pstring, size);
}

/**
  * @brief Función para recibir un string por el puerto USART conociendo su tamaño.
  * @param uint8_t * pstring: Puntero para el buffer que almacenara  el string.
  * @param uint16_t size: Tamaño del texto a recibir.
  * @retval None.
  */
static bool_t CMDParser_ReceiveStringSize(uint8_t * pstring, uint8_t size){

	if ((pstring == NULL) || (size == 0U) || (size > MAX_STRING_SIZE))
		return false ;

	return CMDParser_Port_ReceiveStringSize(pstring, size);

}

/**
  * @brief Función que recorre las posiciones de un array de texto hasta encontrar
  * el caracter nulo (\n) y retorna su tamaño.
  * @param uint8_t * pstring: Puntero al primer elemento del buffer.
  * @retval uint16_t: Tamaño del buffer.
  */
static uint16_t getStringLength(uint8_t * pstring){

	uint16_t size = 0;

	if (pstring == NULL)
		return 0;

	for (uint8_t i = 0; i < MAX_STRING_SIZE; i++){
		if (*(pstring + i) == '\0'){
			size = i;
			break;
		}
	}
	return size;
}
