/*
 * API_delay.h
 *
 *  Created on: 10/09/2026
 *      Author:
 */

#ifndef DRIVERS_API_INC_API_DELAY_H_
#define DRIVERS_API_INC_API_DELAY_H_

/* ========================== INCLUDES ========================== */

#include <stdint.h>
#include <stdbool.h>
#include <stm32f4xx_hal.h>

/* ============================================================== */
/* ========================== TYPEDEFS ========================== */
#define BUTTON_PIN       GPIO_PIN_8
#define BUTTON_GPIO_PORT GPIOA

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
	tick_t startTime;
	tick_t duration;
	bool_t running;
}delay_t;

/* ============================================================== */
/* ========================= PROTOTYPES ========================= */

bool_t Delay_Port_Init(delay_t *delay, tick_t duration);
uint32_t Delay_Port_GetTick(void);
bool_t Delay_Port_Write(delay_t *delay, tick_t duration);
bool_t Delay_Port_IsRunning(delay_t *delay);
bool_t Button_Port_ReadPin(void);
void GPIO_Port_Init(void);

/* ============================================================== */

#endif /* DRIVERS_API_INC_API_DELAY_H_ */
