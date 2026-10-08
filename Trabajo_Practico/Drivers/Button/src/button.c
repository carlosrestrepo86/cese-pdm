/*
 * API_debounce.c
 *
 *  Created on: 17/09/2026
 *      Author: c_and
 */
#include "button.h"

/* ========================== TYPEDEFS ========================== */

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
}debounceState_t;

/* ============================================================== */

static bool_t key_pressed_flag = false;
static debounceState_t current_state;
static delay_t debounce_delay;

/* ===================== FUNCTION PROTOTYPES ==================== */

static void Button_Pressed();
static void Button_Released();
static bool_t Delay_Read(delay_t *delay);

/* ============================================================== */

/**
  * @brief Función para inicializar la maquina de estados.
  * @param None
  * @retval None
  */
void Button_FSM_Init(){
	current_state = BUTTON_UP;
	Delay_Port_Init(&debounce_delay, TIME_DEBOUNCE);
}

/**
  * @brief Función que actualiza la maquina de estados.
  * @param None
  * @retval None
  */
void Button_FSM_Update(){
	switch(current_state){
	case BUTTON_UP:
		if(!Button_Port_ReadPin()){
			current_state = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if(Delay_Read(&debounce_delay)){
			if(!Button_Port_ReadPin()){
				current_state = BUTTON_DOWN;
				Button_Pressed();
			}else{
				current_state = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(Button_Port_ReadPin()){
			current_state = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		if(Delay_Read(&debounce_delay)){
			if(Button_Port_ReadPin()){
				current_state = BUTTON_UP;
				Button_Released();
			}else{
				current_state = BUTTON_DOWN;
			}
		}
		break;
	default:
		Button_FSM_Init();
	}
}

/**
  * @brief Funcion para consultar el estado del pulsador.
  * @param None
  * @retval True --> El boton fue presionado.
  *         False --> El boton no ha sido presionado.
  */
bool_t Read_Key(){
	bool_t button_status = key_pressed_flag;

	if (key_pressed_flag)
		key_pressed_flag = false;

	return button_status;
}

/**
  * @brief Funcion que se llama cuando hay un cambio de estado alto a bajo.
  * @param None
  * @retval None
  */
static void Button_Pressed(){
	key_pressed_flag = true;
}

/**
  * @brief Funcion que se llama cuando hay un cambio de estado bajo a alto.
  * @param None
  * @retval None
  */
static void Button_Released(){
}

/**
  * @brief Función para la lectura del estado del delay.
  * @param delay: Puntero a la estructura del delay.
  * @retval bool_t: True -> Termino el tiempo del delay.
  *                 False -> El delay aún esta corriendo.
  */
static bool_t Delay_Read(delay_t *delay){
	if (delay == NULL)
		return false;

	bool_t delay_state = false;

	if (delay->running){
		if((Delay_Port_GetTick() - delay->startTime) >= delay->duration){
			delay->running = false;
			delay_state = true;
		}
	}else{
		delay->startTime = Delay_Port_GetTick();
		delay->running = true;
	}
	return delay_state;
}

/**
  * @brief Función para la configuración de los pines.
  * @param NONE.
  * @retval bool_t: True -> Configuración OK.
  *                 False -> Error de configuración.
  */
void GPIO_Init(void){
	GPIO_Port_Init();
}
