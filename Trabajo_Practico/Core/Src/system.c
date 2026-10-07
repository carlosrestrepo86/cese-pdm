/*
 * system.c
 *
 *  Created on: 7/10/2026
 *      Author: c_and
 */
#include "system.h"

typedef enum{
	SYS_INIT,
	SYS_MENU,
	SYS_MANUAL,
	SYS_AUTOMATIC,
	SYS_ERROR
}SystemState_t;

static bool_t initialize_system_modules(void);

static SystemState_t current_state;
static SystemState_t previous_state;
static bool_t mode = false;
static int8_t select = 0;

void SYS_FSM_Init(void){
	current_state = SYS_INIT;
	previous_state = SYS_INIT;
}

void SYS_FSM_Update(void){

	switch (current_state){

	case SYS_INIT:

		if (!initialize_system_modules())
			current_state = SYS_ERROR;
		else
			current_state = SYS_MENU;

		break;

	case SYS_MENU:

		if (current_state != previous_state){
			previous_state = current_state;
			LCD_Main_Menu();
		}

		select = Encoder_GetDelta();

		if (select != 0) {
			if (select == 1) {
				mode = true;
				LCD_SetCursor(2, 1);
				LCD_WriteChar(' ');
				LCD_SetCursor(3, 1);
				LCD_WriteChar('>');
			} else {
				mode = false;
				LCD_SetCursor(3, 1);
				LCD_WriteChar(' ');
				LCD_SetCursor(2, 1);
				LCD_WriteChar('>');
			}
		}

		if (Read_Key()){
			if (mode)
				current_state = SYS_AUTOMATIC;
			else
				current_state = SYS_MANUAL;
		}

		break;

	case SYS_MANUAL:

		if (current_state != previous_state){
			previous_state = current_state;
			LCD_Manual_Menu();
		}

		if (Read_Key())
			current_state = SYS_MENU;

		break;

	case SYS_AUTOMATIC:

		if (current_state != previous_state){
			previous_state = current_state;
			LCD_Automatic_Menu();
		}

		if (Read_Key()){
			mode = false;
			current_state = SYS_MENU;
		}

		break;

	case SYS_ERROR:
		break;

	default:
		break;
	}
}

static bool_t initialize_system_modules(void){

	/* Initialize all configured peripherals */
	GPIO_Init();

	/* Inicializar el CMDParser*/
	if (!CMDParser_Config()){
		return false;
	}

	CMDParser_Init();
	ButtonFSM_Init();

	/* Inicializar la LCD */
	if (!LCD_Init())
		return false;

	LCD_Startup_Sequence();
	LCD_Config();

	if (!Encoder_Init())
		return false;

	if (!Encoder_Start())
		return false;

	return true;
}
