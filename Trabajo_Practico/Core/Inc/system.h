/*
 * system.h
 *
 *  Created on: 7/10/2026
 *      Author: c_and
 */

#ifndef CORE_INC_SYSTEM_H_
#define CORE_INC_SYSTEM_H_

#include "lcd.h"
#include "cmdparser.h"
#include "Button.h"
#include "encoder.h"

typedef bool bool_t;

void SYS_FSM_Init(void);
void SYS_FSM_Update(void);

#endif /* CORE_INC_SYSTEM_H_ */
