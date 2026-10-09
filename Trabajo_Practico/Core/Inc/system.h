/*
 * system.h
 *
 *  Created on: 7/10/2026
 *      Author: c_and
 */

#ifndef CORE_INC_SYSTEM_H_
#define CORE_INC_SYSTEM_H_

#include "button.h"
#include "lcd.h"
#include "cmdparser.h"
#include "encoder.h"
#include "servomotor.h"

typedef bool bool_t;

void SYS_FSM_Init(void);
void SYS_FSM_Update(void);

#endif /* CORE_INC_SYSTEM_H_ */
