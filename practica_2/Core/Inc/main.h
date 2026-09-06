#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================== INCLUDES ========================== */

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/* ============================================================== */
/* ====================== PORT DEFINITIONS ====================== */

/* User Button */
#define B1_Pin              GPIO_PIN_13
#define B1_GPIO_Port        GPIOC

/* User LED */
#define LD2_Pin             GPIO_PIN_5
#define LD2_GPIO_Port       GPIOA

/* USART2 */
#define USART_TX_Pin        GPIO_PIN_2
#define USART_TX_GPIO_Port  GPIOA

#define USART_RX_Pin        GPIO_PIN_3
#define USART_RX_GPIO_Port  GPIOA

/* SWD / Debug */
//#define TMS_Pin             GPIO_PIN_13
//#define TMS_GPIO_Port       GPIOA

//#define TCK_Pin             GPIO_PIN_14
//#define TCK_GPIO_Port       GPIOA

//#define SWO_Pin             GPIO_PIN_3
//#define SWO_GPIO_Port       GPIOB

/* ============================================================== */
/* ========================== TYPEDEFS ========================== */

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
	tick_t startTime;
	tick_t duration;
	bool_t running;
}delay_t;

/* ============================================================== */
/* ========================== CONSTANTS ========================= */

/* ============================================================== */
/* ========================= PROTOTYPES ========================= */

void Error_Handler(void);
void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);

/* ============================================================== */

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */
