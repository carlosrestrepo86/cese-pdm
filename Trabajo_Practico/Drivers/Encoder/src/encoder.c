/*
 * encoder.c
 *
 *  Created on: 30/09/2026
 *      Author: c_and
 */

#include "encoder.h"
#include "encoder_port.h"

/**
  * @brief  Función para inicializar el encoder.
  * @param  NONE.
  * @retval bool: True -> Inicialización OK.
  *               False -> Error en la inicialización.
  */
bool_t Encoder_Init(void){
	return Encoder_Port_Init();
}

/**
  * @brief  Función para iniciar el encoder.
  * @param  NONE.
  * @retval bool: True -> Inicialización OK.
  *               False -> Error en la inicialización.
  */
bool_t Encoder_Start(void){
	return Encoder_Port_Start();
}

/**
  * @brief  Función para detener el encoder.
  * @param  NONE.
  * @retval bool: True -> Encoder detenido OK.
  *               False -> Error al detener el encoder.
  */
bool_t Encoder_Stop(void){
	return Encoder_Port_Stop();
}

/**
  * @brief  Función para obtener la posición del encoder con referencia
  * a la posición inicial.
  * @param  NONE.
  * @retval float: Ángulo en referencia a la posición inicial.
  */
float Encoder_GetPosition(void){

	static bool flag = false;
	static uint16_t reference_value;
	uint16_t current_value;
	uint16_t delta_raw;
	int16_t delta_count;

	if (!flag){
		flag = true;
		reference_value = Encoder_Port_GetCounter();
		return INITIAL_POS;
	}

	current_value = Encoder_Port_GetCounter();
	delta_raw = current_value - reference_value;
	delta_count = (int16_t)delta_raw;

	float angle = (delta_count * 360.0) / (PPR * COMBINATIONS);

	return angle;
}

// retorna -1, 0 o +1
/**
  * @brief  Función para obtener el sentido de giro del encoder.
  * @param  NONE.
  * @retval int8_t: 1  -> Giro a la derecha.
  *               	-1 -> Giro a la izquierda.
  *               	0  -> No hay movimiento del encoder
  */
int8_t Encoder_GetDelta(void){

	static bool flag = false;
	static uint16_t previous_value;
	uint16_t current_value;
	uint16_t delta_raw;
	int16_t delta_count;

	if (!flag){
		flag = true;
		previous_value = Encoder_Port_GetCounter();
		return 0;
	}

	current_value = Encoder_Port_GetCounter();

	delta_raw = current_value - previous_value;
	delta_count = (int16_t)delta_raw;

	// Para el EC11 en modo x4, un clic completo equivale a un delta de 4 o -4.
	// Umbral de >= 4 (o <= -4) para asegurar que el usuario completó el clic físico.
	if (delta_count >= 4) {
		previous_value = current_value; // Sincronizamos solo al completar el paso.
		return 1;
	}
	else if (delta_count <= -4) {
		previous_value = current_value; // Sincronizamos solo al completar el paso.
		return -1;
	}else
		return 0;
}
