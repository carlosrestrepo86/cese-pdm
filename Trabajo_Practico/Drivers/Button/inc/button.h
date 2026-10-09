/*
 * API_debounce.h
 *
 *  Created on: 17/09/2026
 *      Author: c_and
 */
#ifndef DRIVERS_API_INC_API_DEBOUNCE_H_
#define DRIVERS_API_INC_API_DEBOUNCE_H_

#include "button_port.h"

#define TIME_DEBOUNCE 40

void Button_FSM_Init(void);
void Button_FSM_Update(void);
bool_t Read_Key(void);
void GPIO_Init(void);

/* ============================================================== */

#endif /* DRIVERS_API_INC_API_DEBOUNCE_H_ */
