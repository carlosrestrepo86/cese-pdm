/*
 * encoder_port.h
 *
 *  Created on: 30/09/2026
 *      Author: c_and
 */

#ifndef DRIVERS_ENCODER_INC_ENCODER_PORT_H_
#define DRIVERS_ENCODER_INC_ENCODER_PORT_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define PERIOD    0xFFFF // Periodo máximo para timer de 16 bits.
#define PRESCALER 0      // F = 84 MHz -> Prescaler = (Frec. reloj / Frec deseada) - 1.

#define ENCODER_TIMER     TIM5                 // Timer seleccionado.
#define SERVO_PWM_MODE    TIM_ENCODERMODE_TI12 // Modo cuadratura, utiliza las dos señales del encoder para contar.
#define ENCODER_GPIO_PORT GPIOA
#define ENCODER_CH1_PIN   GPIO_PIN_0
#define ENCODER_CH2_PIN   GPIO_PIN_1
#define SERVO_PWM_AF      GPIO_AF2_TIM5 // Función alternativa para timer en PA0 y PA1.
#define TIMx_CLK_ENABLE()   __HAL_RCC_TIM5_CLK_ENABLE()  // Habilitar el reloj del timer.
#define TIMx_CLK_DISABLE()  __HAL_RCC_TIM5_CLK_DISABLE() // Deshabilitar el reloj del timer.
#define GPIOx_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE() // Habilitar el reloj del puerto.

typedef bool bool_t;

bool_t Encoder_Port_Init(void);
bool_t Encoder_Port_Start(void);
bool_t Encoder_Port_Stop(void);
uint16_t Encoder_Port_GetCounter(void);
void Encoder_Port_ResetCounter(void);

#endif /* DRIVERS_ENCODER_INC_ENCODER_PORT_H_ */
