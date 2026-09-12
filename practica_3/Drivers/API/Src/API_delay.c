/*
 * API_delay.c
 *
 *  Created on: 10/09/2026
 *      Author:
 */

#include "API_delay.h"

/* ===================== FUNCTION PROTOTYPES ==================== */

/**
  * @brief Función para manejo de errores en la API.
  * @param None
  * @retval None
  */
static void API_Error_Handler(void);

/* ============================================================== */

/**
  * @brief Función para inicializar el delay.
  * @param delay: Puntero a la estructura del delay.
  * @param duration: Tiempo de duración del delay.
  * @retval None
  */
void delayInit(delay_t *delay, tick_t duration){

	if (delay == NULL || duration == 0)
		API_Error_Handler();

	delay->duration = duration;
	delay->running = false;
}

/**
  * @brief Función para lectura del delay.
  * @param delay: Puntero a la estructura del delay.
  * @retval False --> El delay esta corriendo.
  *         True  --> El delay termino.
  */
bool_t delayRead(delay_t *delay){

	if (delay == NULL)
		API_Error_Handler();

	bool_t delay_state = false;

	if (delay->running){
		if((HAL_GetTick() - delay->startTime) >= delay->duration){
			delay->running = false;
			delay_state = true;
		}
	}else{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	return delay_state;
}

/**
  * @brief Función para cambiar el tiempo del delay.
  * @param delay: Puntero a la estructura del delay.
  * @param duration: Tiempo de duración del delay
  * @retval None
  */
void delayWrite(delay_t *delay, tick_t duration){

	if (delay == NULL || duration == 0)
		API_Error_Handler();

	delay->duration = duration;
}

/**
  * @brief Función para obtener el estado de la variable running.
  * @param delay: Puntero a la estructura del delay.
  * @retval False --> Termino tiempo del delay.
  *         True  --> Delay en operacion.
  */
bool_t delayIsRunning(delay_t *delay){

	if (delay == NULL)
		API_Error_Handler();

	return delay->running;
}

static void API_Error_Handler(void){
	while(1);
}

