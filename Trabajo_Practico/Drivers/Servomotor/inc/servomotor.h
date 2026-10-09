/*
 * servomotor.h
 *
 *  Created on: 4/10/2026
 *      Author: c_and
 */

#ifndef DRIVERS_SERVOMOTOR_INC_SERVOMOTOR_H_
#define DRIVERS_SERVOMOTOR_INC_SERVOMOTOR_H_

#include <stdint.h>
#include <stdbool.h>

#define SERVO_MIN_PULSE 500  // 1 us * 1000 = 1 ms.
#define SERVO_MAX_PULSE 2500 // 1 us * 2000 = 2 ms.

typedef bool bool_t;

bool_t Servomotor_Init(void);
bool_t Servomotor_Start(void);
bool_t Servomotor_Stop(void);
void Servomotor_SetPosition(uint8_t angle);

#endif /* DRIVERS_SERVOMOTOR_INC_SERVOMOTOR_H_ */
