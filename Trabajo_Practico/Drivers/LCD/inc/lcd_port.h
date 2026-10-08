/*
 * API_lcd_port.h
 *
 *  Created on: 23/09/2026
 *      Author: c_and
 */

#ifndef DRIVERS_LCD_INC_LCD_PORT_H_
#define DRIVERS_LCD_INC_LCD_PORT_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define LCD_DIR 0x27 //0x3F

#define LCD_I2C         I2C1
#define CLOCK_SPEED     100000 // 100 KHz, maximo permitido 100 KHz.
#define ADDRESSING_MODE I2C_ADDRESSINGMODE_7BIT // PCF8574 direccion con 7 bits.
#define LCD_GPIO_PORT   GPIOB
#define LCD_SCL_PIN     GPIO_PIN_8
#define LCD_SDA_PIN     GPIO_PIN_9
#define LCD_I2C_AF      GPIO_AF4_I2C1

typedef bool bool_t;

bool_t LCD_Port_Init(void);
bool_t LCD_Write_Byte(uint8_t byte);
void LCD_delay(uint32_t time);

#endif /* DRIVERS_LCD_INC_LCD_PORT_H_ */
