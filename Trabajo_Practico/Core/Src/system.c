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
static uint8_t angle = 0;

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
			Servomotor_SetPosition(INITIAL_POS);
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
			if (mode){
				current_state = SYS_AUTOMATIC;
				// Encoder_ResetCounter();
			}
			else{
				current_state = SYS_MANUAL;
				//Encoder_ResetCounter();
			}
		}

		break;

	case SYS_MANUAL:

		if (current_state != previous_state){
			previous_state = current_state;
			LCD_Manual_Menu();
			LCD_SetCursor(2, 11);
			LCD_WriteInt(INITIAL_POS);
			break;
		}

		select = Encoder_GetDelta();

		if (select != 0){
			angle = Encoder_GetPosition();
			LCD_SetCursor(2, 11);
			LCD_WriteInt(angle);
			Servomotor_SetPosition(angle);
		}

		if (Read_Key())
			current_state = SYS_MENU;

		break;

	case SYS_AUTOMATIC:

		if (current_state != previous_state){
			previous_state = current_state;
			LCD_Automatic_Menu();
			LCD_SetCursor(2, 11);
			LCD_WriteInt(INITIAL_POS);
			break;
		}

		if (CmdParser_GetCommand(&angle)){
			LCD_SetCursor(2, 11);
			LCD_WriteInt(angle);
			Servomotor_SetPosition(angle);
		}

		if (Read_Key()){
			mode = false;
			current_state = SYS_MENU;
		}

		break;

	case SYS_ERROR:

		Encoder_Stop();
		Servomotor_Stop();
		current_state = SYS_INIT;

		break;

	default:
		break;
	}
}

static bool_t initialize_system_modules(void){

	bool_t flag = true;

	/* Initializar el pin para el pulsador */
	GPIO_Init();

	/* Inicializar la comunicación UART (por defecto 115200,8N1) */
	if (!CMD_Parser_Config())
		flag = false;

	/* Inicializar la comunicación I2C para la LCD */
	if (!LCD_Init())
		flag = false;

	/* Secuencias para inicializar y configurar la LCD */
	LCD_Startup_Sequence();
	LCD_Config();

	/* Configurar el timer e iniciar el conteo de pulsos */
	if (!Encoder_Init() || !Encoder_Start())
		flag = false;

	/* Configurar el timer y generar la señal */
	if (!Servomotor_Init() || !Servomotor_Start())
		flag = false;

	/* Inicializar las MEF de Button y CMDParser */
	CMD_Parser_Init();
	Button_FSM_Init();

	return flag;
}
