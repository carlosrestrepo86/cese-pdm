/*
 * servomotor_port.h
 *
 *  Created on: 4/10/2026
 *      Author: c_and
 */

#ifndef DRIVERS_SERVOMOTOR_INC_SERVOMOTOR_PORT_H_
#define DRIVERS_SERVOMOTOR_INC_SERVOMOTOR_PORT_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define PERIOD    19999 // Periodo de la señal 20 ms (Periodo base 1 us).
#define PRESCALER 83    // Prescaler = (Frec. reloj / Frec deseada) - 1 = (84 MHz / 1 MHz) - 1 = 84 - 1 = 83.
#define INIT_POS  1500  // 90°

#define SERVO_TIMER         TIM2          // Timer seleccionado.
#define SERVO_PWM_CHANNEL   TIM_CHANNEL_1 // Canal seleccionado.
#define SERVO_PWM_PIN       GPIO_PIN_0
#define SERVO_PWM_GPIO_PORT GPIOA         // Pin para TIM2 - CH1.
#define SERVO_PWM_AF        GPIO_AF1_TIM2 // Funcion auxiliar del pin.

typedef bool bool_t;

bool_t Servomotor_Port_Init(void);
bool_t Servomotor_Port_Start(void);
bool_t Servomotor_Port_Stop(void);
void Servomotor_Port_SetPosition(float count);

#endif /* DRIVERS_SERVOMOTOR_INC_SERVOMOTOR_PORT_H_ */
