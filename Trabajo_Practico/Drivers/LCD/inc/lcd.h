/*
 * API_lcd.h
 *
 *  Created on: 23/09/2026
 *      Author: c_and
 */

/*
 * BL   EN   RW RS
 * x  H,H->L 0  0   Enviar comando
 * x  H,H->L 0  1   Enviar dato
 * */

/*
 * columna
        0 ..................... 19
       ┌─────────────────────────┐
fila 0 │ 0x00 .............. 0x13│ con bit 8 en 1 0x80
fila 1 │ 0x40 .............. 0x53│ con bit 8 en 1 0xc0
fila 2 │ 0x14 .............. 0x27│ con bit 8 en 1 0x94
fila 3 │ 0x54 .............. 0x67│ con bit 8 en 1 0xd4
       └─────────────────────────┘
 * */

#ifndef DRIVERS_LCD_INC_LCD_H_
#define DRIVERS_LCD_INC_LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define NUM_ROWS    4
#define NUM_COLUMNS 20
#define ROW1        0x80
#define ROW2        0xc0
#define ROW3        0x94
#define ROW4        0xd4

#define COMMAND 0b0000
#define DATA    0b0001

//Bits de ENABLE y BACK LIGHT
#define EN 0b0100
#define BL 0b1000

typedef bool bool_t;

bool_t LCD_Init(void);
void LCD_Startup_Sequence(void);
void LCD_Config(void);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_SetCursor(uint8_t row, uint8_t column );
void LCD_WriteChar(uint8_t character);
void LCD_WriteString(char *text);
void LCD_WriteInt(uint8_t number);
void LCD_Main_Menu(void);
void LCD_Manual_Menu(void);
void LCD_Automatic_Menu(void);

#endif /* DRIVERS_LCD_INC_LCD_H_ */
