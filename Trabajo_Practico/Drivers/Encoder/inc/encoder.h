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

typedef bool bool_t;

#define PPR          20  // Encoder de 20 pulsos x vuelta
#define COMBINATIONS 4   // Trabajando con los dos canales tenemos 4 combinaciones.
#define INITIAL_POS  90  // 90°
#define MAX_ANGLE    180 // Máximo ángulo permitido por el servomotor.

bool_t Encoder_Init(void);
bool_t Encoder_Start(void);
bool_t Encoder_Stop(void);
int16_t Encoder_GetPosition(void);
int8_t Encoder_GetDelta(void);

#endif /* DRIVERS_ENCODER_INC_ENCODER_H_ */
