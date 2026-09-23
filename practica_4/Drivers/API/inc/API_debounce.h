/*
 * API_debounce.h
 *
 *  Created on: 17/09/2026
 *      Author: c_and
 */
#include "API_delay.h"
#include "main.h"

#ifndef DRIVERS_API_INC_API_DEBOUNCE_H_
#define DRIVERS_API_INC_API_DEBOUNCE_H_

/* ========================== INCLUDES ========================== */

/* ============================================================== */
/* ========================= PROTOTYPES ========================= */

void debounceFSM_init();
void debounceFSM_update();
bool_t readKey();

/* ============================================================== */

#endif /* DRIVERS_API_INC_API_DEBOUNCE_H_ */
