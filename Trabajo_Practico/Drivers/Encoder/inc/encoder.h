/*
 * encoder.h
 *
 *  Created on: 30/09/2026
 *      Author: c_and
 */
/*
 * Pulso por vuelta: 20
 * Salida: Código Gray de 2 bits
 * Sentido horario: 00 → 01 → 11 → 10 (COMBINACIONES)
 * Sentido antihorario: 00 → 10 → 11 → 01
 * */

#ifndef DRIVERS_ENCODER_INC_ENCODER_H_
#define DRIVERS_ENCODER_INC_ENCODER_H_

#include <stdint.h>
#include <stdbool.h>

#define PPR          20.0  // Encoder de 20 pulsos x vuelta
#define COMBINATIONS 4.0   // Trabajando con los dos canales tenemos 4 combinaciones.
#define INITIAL_POS  90.0  // 90°
#define MAX_ANGLE    180.0 // Máximo ángulo permitido por el servomotor.

typedef bool bool_t;

bool_t Encoder_Init(void);
bool_t Encoder_Start(void);
bool_t Encoder_Stop(void);
uint8_t Encoder_GetPosition(void);
int8_t Encoder_GetDelta(void);

#endif /* DRIVERS_ENCODER_INC_ENCODER_H_ */
