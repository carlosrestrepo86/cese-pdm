/*
 * API_delay.c
 *
 *  Created on: 10/09/2026
 *      Author:
 */

#include "button_port.h"

/**
  * @brief Función para inicializar el delay.
  * @param delay: Puntero a la estructura del delay.
  * @param duration: Tiempo de duración del delay.
  * @retval None
  */
bool_t Delay_Port_Init(delay_t *delay, tick_t duration){

	if (delay == NULL || duration == 0)
		return false;

	delay->duration = duration;
	delay->running = false;
	return true;
}

/**
  * @brief Función para lectura de HAL_GetTick.
  * @param NONE.
  * @retval uint32_t Valor de tick en milisegundos.
  */
uint32_t Delay_Port_GetTick(void){
	return HAL_GetTick();
}

/**
  * @brief Función para cambiar el tiempo del delay.
  * @param delay: Puntero a la estructura del delay.
  * @param duration: Tiempo de duración del delay
  * @retval None
  */
bool_t Delay_Port_Write(delay_t *delay, tick_t duration){

	if (delay == NULL || duration == 0)
		return false;

	delay->duration = duration;
	return true;
}

/**
  * @brief Función para obtener el estado de la variable running.
  * @param delay: Puntero a la estructura del delay.
  * @retval False --> Termino tiempo del delay.
  *         True  --> Delay en operacion.
  */
bool_t Delay_Port_IsRunning(delay_t *delay){

	if (delay == NULL)
		return false;

	return delay->running;
}

/**
  * @brief Función para lectura del estado del botón.
  * @param NONE.
  * @retval bool_t: True -> Botón no presionado.
  *                False -> Botón presionado.
  */
bool_t Button_Port_ReadPin(void){
	return HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN);
}

void GPIO_Port_Init(void){

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin */
  GPIO_InitStruct.Pin = BUTTON_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);
}


