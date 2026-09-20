/*
 * API_debounce.c
 *
 *  Created on: 17/09/2026
 *      Author: c_and
 */
#include "API_debounce.h"

/* ========================== TYPEDEFS ========================== */

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
}debounceState_t;

/* ============================================================== */

static debounceState_t current_state;
const uint8_t time_debounce = 40;
static delay_t debounce_delay;
static bool_t button_pressed_flag = false;

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
	current_state = BUTTON_UP;
	delayInit(&debounce_delay, time_debounce);
}

/**
  * @brief Función para actualizar la maquina de estados.
  * @param None
  * @retval None
  */
void debounceFSM_update(){
	switch(current_state){
	case BUTTON_UP:
		if(!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
			current_state = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if(delayRead(&debounce_delay)){
			if(!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
				current_state = BUTTON_DOWN;
				buttonPressed();
			}else{
				current_state = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
			current_state = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		if(delayRead(&debounce_delay)){
			if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
				current_state = BUTTON_UP;
				buttonReleased();
			}else{
				current_state = BUTTON_DOWN;
			}
		}
		break;
	default:
		debounceFSM_init();
	}
}

static void buttonPressed(){
	button_pressed_flag = true;
}

static void buttonReleased(){
}

bool_t readKey(){
	bool_t button_status = button_pressed_flag;

	if (button_pressed_flag)
		button_pressed_flag = false;

	return button_status;
}
