/*
 * encoder_port.c
 *
 *  Created on: 30/09/2026
 *      Author: c_and
 */

#include "encoder_port.h"

static TIM_HandleTypeDef hencoder;

/**
  * @brief Función para iniciar la interfaz del timer en modo encoder.
  * @param None
  * @retval
  */
bool_t Encoder_Port_Start(void){

	HAL_StatusTypeDef status;

	status = HAL_TIM_Encoder_Start(&hencoder, TIM_CHANNEL_ALL);

	if(status != HAL_OK)
		return false;
	else
		return true;
}

/**
  * @brief Función para detener la interfaz del timer en modo encoder.
  * @param None
  * @retval
  */
bool_t Encoder_Port_Stop(void){

	HAL_StatusTypeDef status;

	status = HAL_TIM_Encoder_Stop(&hencoder, TIM_CHANNEL_ALL);

	if (status != HAL_OK)
		return false;
	else
		return true;
}

/**
  * @brief Función para obtener el valor del contador para el timer.
  * @param None
  * @retval
  */
uint16_t Encoder_Port_GetCounter(void){
	// Acceder al contador CNT del timer y leer el valor.
	// Giro derecha valor 10
	// Giro derecha valor 25
	// Giro izquierda 15
	uint16_t counter_value = hencoder.Instance->CNT;

	return counter_value;
}

/**
  * @brief Función para reiniciar el contador del timer.
  * @param None
  * @retval NONE.
  */
void Encoder_Port_ResetCounter(void){
	hencoder.Instance->CNT = 0;
}

/**
  * @brief  Función para inicializar TIM ENCODER MSP.
  * @param  htim: Manejador TIM.
  * @retval NONE
  */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(htim->Instance == ENCODER_TIMER)
	{
		/* Peripheral clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitStruct.Pin = ENCODER_CH1_PIN | ENCODER_CH2_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = SERVO_PWM_AF;

		HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
	}
}

/**
  * @brief  Función para desinicializar TIM ENCODER MSP.
  * @param  htim: Manejador TIM.
  * @retval NONE
  */
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim){

	if(htim->Instance == ENCODER_TIMER){
		__HAL_RCC_TIM3_CLK_DISABLE();

		HAL_GPIO_DeInit(ENCODER_GPIO_PORT, ENCODER_CH1_PIN | ENCODER_CH2_PIN);
	}
}

/**
  * @brief Función para inicializar el TIMER (frecuencia base, periodo y modo de operación).
  * @param None
  * @retval bool: True -> Inicialización OK.
  *               False -> Error en la inicialización.
  */
bool_t Encoder_Port_Init(void){

	TIM_Encoder_InitTypeDef TIMx_InitStruct = {0};

	hencoder.Instance = ENCODER_TIMER;
	hencoder.Init.Prescaler = PRESCALER;
	hencoder.Init.CounterMode = TIM_COUNTERMODE_UP;
	hencoder.Init.Period = PERIOD;
	hencoder.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hencoder.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	TIMx_InitStruct.EncoderMode = SERVO_PWM_MODE;

	TIMx_InitStruct.IC1Polarity = TIM_ICPOLARITY_RISING;
	TIMx_InitStruct.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	TIMx_InitStruct.IC1Prescaler = TIM_ICPSC_DIV1;
	TIMx_InitStruct.IC1Filter = 0xF;

	TIMx_InitStruct.IC2Polarity = TIM_ICPOLARITY_RISING;
	TIMx_InitStruct.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	TIMx_InitStruct.IC2Prescaler = TIM_ICPSC_DIV1;
	TIMx_InitStruct.IC2Filter = 0xF;

	if (HAL_TIM_Encoder_Init(&hencoder, &TIMx_InitStruct) != HAL_OK)
		return false;
	else
		return true;
}
