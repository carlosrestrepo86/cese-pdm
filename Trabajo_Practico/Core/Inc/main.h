#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/* User Button */
#define B1_Pin              GPIO_PIN_13
#define B1_GPIO_Port        GPIOC

/* User LED */
#define LD2_Pin             GPIO_PIN_5
#define LD2_GPIO_Port       GPIOA

/* SWD / Debug */
//#define TMS_Pin             GPIO_PIN_13
//#define TMS_GPIO_Port       GPIOA

//#define TCK_Pin             GPIO_PIN_14
//#define TCK_GPIO_Port       GPIOA

//#define SWO_Pin             GPIO_PIN_3
//#define SWO_GPIO_Port       GPIOB

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */
