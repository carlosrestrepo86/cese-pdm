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
#include <stdbool.h>
#include <stdint.h>

typedef bool bool_t;

void CMDParser_FSM_Init(void);
bool_t CMDParser_Config(void);
void CMDParser_FSM_Update(void);
bool_t CMDParser_GetCommand(uint8_t *value);

#endif /* DRIVERS_CMDPARSER_INC_CMDPARSER_H_ */
