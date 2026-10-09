/*
 * API_cmdparser.h
 *
 *  Created on: 27/09/2026
 *      Author: c_and
 */

#ifndef DRIVERS_CMDPARSER_INC_CMDPARSER_H_
#define DRIVERS_CMDPARSER_INC_CMDPARSER_H_

#define CMD_MAX_LINE   64 // incluye '\0'
#define CMD_MAX_TOKENS 3  // COMANDO + máximo 2 argumentos

#include <string.h>
#include "cmdparser_port.h"
#include "main.h"

void CMD_Parser_Init(void);
bool_t CMD_Parser_Config(void);
void CMD_Parser_Update(void);
bool_t CmdParser_GetCommand(uint8_t *value);

#endif /* DRIVERS_CMDPARSER_INC_CMDPARSER_H_ */
