/*
 * API_debounce.c
 *
 *  Created on: 17/09/2026
 *      Author: c_and
 */
#include "API_debounce.h"

static debounceState_t estadoActual;
const uint8_t time_debounce = 40;
static delay_t delay;

/* ===================== FUNCTION PROTOTYPES ==================== */

static void buttonPressed();
static void buttonReleased();

/* ============================================================== */

/**
  * @brief Función para inicializar la maquina de estados.
  * @param None
  * @retval None
  */
void debounceFSM_init(){
	estadoActual = BUTTON_UP;
	delayInit(&delay, time_debounce);
}

/**
  * @brief Función para actualizar la maquina de estados.
  * @param None
  * @retval None
  */
void debounceFSM_update(){
	switch(estadoActual){
	case BUTTON_UP:
		if(!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
			estadoActual = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if(delayRead(&delay)){
			if(!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
				estadoActual = BUTTON_DOWN;
				buttonPressed();
			}else{
				estadoActual = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
			estadoActual = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		if(delayRead(&delay)){
			if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
				estadoActual = BUTTON_UP;
				buttonReleased();
			}else{
				estadoActual = BUTTON_DOWN;
			}
		}
		break;
	default:
		buttonReleased();
		debounceFSM_init();
	}
}

static void buttonPressed(){
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}

static void buttonReleased(){
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}

bool_t readKey();
