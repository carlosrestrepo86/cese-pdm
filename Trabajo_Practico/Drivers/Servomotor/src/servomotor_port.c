/*
 * servomotor_port.c
 *
 *  Created on: 4/10/2026
 *      Author: c_and
 */
#include "servomotor_port.h"

static TIM_HandleTypeDef hservo;

/**
  * @brief  Función para iniciar la generación de la señal PWM.
  * @param  NONE
  * @retval bool True -> HAL OK.
  *              False -> HAL ERROR.
  */
bool_t Servomotor_Port_Start(void){

	HAL_StatusTypeDef status;

	status = HAL_TIM_PWM_Start(&hservo, SERVO_PWM_CHANNEL);

	if(status != HAL_OK)
		return false;
	else
		return true;
}

/**
  * @brief  Función para detener la generación de la señal PWM.
  * @param  NONE
  * @retval bool True -> HAL OK.
  *              False -> HAL ERROR.
  */
bool_t Servomotor_Port_Stop(void){

	HAL_StatusTypeDef status;

	status = HAL_TIM_PWM_Stop(&hservo, SERVO_PWM_CHANNEL);

	if(status != HAL_OK)
		return false;
	else
		return true;
}

/**
  * @brief  Función para cambiar el ancho de pulso de la señal PWM.
  * @param  uint16_t count: Cantidad de pulsos que se deben contar.
  * @retval NONE
  */
void Servomotor_Port_SetPosition(float count){
	hservo.Instance->CCR1 = count;
}

/**
  * @brief  Función para inicializar TIM PWM MSP.
  * @param  htim: Manejador TIM PWM.
  * @retval NONE
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if (htim->Instance == SERVO_TIMER){

		/* Peripheral clock enable */
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM2 GPIO Configuration
		    PA5     ------> CH1
		*/
		GPIO_InitStruct.Pin = SERVO_PWM_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = SERVO_PWM_AF;

		HAL_GPIO_Init(SERVO_PWM_GPIO_PORT, &GPIO_InitStruct);
	}
}

/**
  * @brief  Función para desinicializar TIM PWM MSP.
  * @param  htim: Manejador TIM PWM.
  * @retval NONE
  */
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim){

	if (htim->Instance == SERVO_TIMER){

		/* Peripheral clock enable */
		__HAL_RCC_TIM2_CLK_DISABLE();

		HAL_GPIO_DeInit(SERVO_PWM_GPIO_PORT, SERVO_PWM_PIN);
	}
}

/**
  * @brief  Función para configurar el PWM generado (frecuencia base, periodo y ancho de pulso).
  * @param  NONE.
  * @retval bool: True -> Configuración OK.
  *               False -> Error de configuración.
  */
bool_t Servomotor_Port_Init(void){

	TIM_OC_InitTypeDef TIMx_InitStruct = {0};

	/* Cofiguración de la base de tiempo */
	hservo.Instance = SERVO_TIMER;
	hservo.Init.Prescaler = PRESCALER; //
	hservo.Init.CounterMode = TIM_COUNTERMODE_UP;
	hservo.Init.Period = PERIOD;
	hservo.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hservo.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	/* Configuración del canal */
	TIMx_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIMx_InitStruct.Pulse = INIT_POS;
	TIMx_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIMx_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;

	if (HAL_TIM_PWM_Init(&hservo) != HAL_OK || HAL_TIM_PWM_ConfigChannel(&hservo, &TIMx_InitStruct, SERVO_PWM_CHANNEL) != HAL_OK)
		return false;
	else
		return true;
}
