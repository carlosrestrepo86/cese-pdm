/*
 * servomotor.c
 *
 *  Created on: 4/10/2026
 *      Author: c_and
 */
#include "servomotor.h"
#include "servomotor_port.h"

/**
  * @brief  Función para inicializar el puerto del servomotor.
  * @param  NONE.
  * @retval bool: True -> Inicialización OK.
  *               False -> Error de inicialización.
  */
bool_t Servomotor_Init(void){
	return Servomotor_Port_Init();
}

/**
  * @brief  Función para iniciar la generación de PWM.
  * @param  NONE.
  * @retval bool: True -> Inicialización OK.
  *               False -> Error de inicialización.
  */
bool_t Servomotor_Start(void){
	return Servomotor_Port_Start();
}

/**
  * @brief  Función para detener la generación de PWM.
  * @param  NONE.
  * @retval bool: True -> Inicialización OK.
  *               False -> Error de inicialización.
  */
bool_t Servomotor_Stop(void){
	return Servomotor_Port_Stop();
}

/**
  * @brief  Función para llevar el servomotor a la posición deseada.
  * @param  angle: Ángulo entre 0° y 180°.
  * @retval NONE.
  */
void Servomotor_SetPosition(uint8_t angle){

	uint8_t count;

	count = SERVO_MIN_PULSE + ((angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE)) / 180);
	Servomotor_Port_SetPosition(count);
}
