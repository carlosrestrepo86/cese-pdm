/*
 * API_cmdparser.h
 *
 *  Created on: 27/09/2026
 *      Author: c_and
 */

#ifndef DRIVERS_API_INC_API_CMDPARSER_H_
#define DRIVERS_API_INC_API_CMDPARSER_H_

#define CMD_MAX_LINE 64  // incluye '\0'
#define CMD_MAX_TOKENS 3 // COMANDO + máximo 2 argumentos

#include <string.h>
#include "API_uart.h"
#include "main.h"

typedef enum {
	CMD_OK = 0,
	CMD_ERR_OVERFLOW,
	CMD_ERR_SYNTAX,
	CMD_ERR_UNKNOWN,
	CMD_ERR_FLAG
}cmd_status_t;

typedef enum
{
    CMD_NONE,
	CMD_LED_ON,
    CMD_LED_OFF,
    CMD_LED_TOGGLE,
	CMD_LED_STATUS,
	CMD_GET_BAUD,
	CMD_SET_BAUD,
	CMD_HELP
} cmd_action_t;

void cmdParserInit(void);
void cmdPoll(void);
void cmdPrintHelp(void);
cmd_action_t readCommand();

#endif /* DRIVERS_API_INC_API_CMDPARSER_H_ */
