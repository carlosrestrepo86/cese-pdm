/*
 * API_lcd.c
 *
 *  Created on: 23/09/2026
 *      Author: c_and
 */

#include "lcd.h"
#include "lcd_port.h"

static void send_4_bits(uint8_t byte, bool type);
static void send_8_bits(uint8_t byte, bool type);

static uint8_t address[NUM_ROWS] = {ROW1, ROW2, ROW3, ROW4};

/**
  * @brief  Función para inicializar la comunicación I2C.
  * @param  NONE.
  * @retval bool_t: True --> Inicialización OK.
  *                 False --> Falló en la inicialización.
  */
bool_t LCD_Init(void){
	return LCD_Port_Init();
}

/**
  * @brief  Función para inicializar la pantalla LCD.
  * @param  NONE.
  * @retval NONE.
  */
void LCD_Startup_Sequence(void){
	LCD_delay(20);
	send_4_bits(0x30, COMMAND);
	LCD_delay(10);
	send_4_bits(0x30, COMMAND);
	LCD_delay(1);
	send_4_bits(0x30, COMMAND);
	send_4_bits(0x20, COMMAND);
}

/**
  * @brief  Función para la configuración inicial de la pantalla.
  * @param  NONE.
  * @retval NONE.
  */
void LCD_Config(void){
	send_8_bits(0x28, COMMAND); // 4 bits, 2 líneas, 5x7
	LCD_delay(2);
	send_8_bits(0x08, COMMAND); // Display OFF
	LCD_delay(2);
	send_8_bits(0x02, COMMAND); // Return home
	LCD_delay(2);
	send_8_bits(0x06, COMMAND); // Incrementar cursor
	LCD_delay(2);
	send_8_bits(0x0C, COMMAND); // Display ON + Cursor OFF
	LCD_delay(2);
	send_8_bits(0x01, COMMAND); // Clear display.
	LCD_delay(2);
}

/**
  * @brief  Función para mostrar un carácter en la LCD.
  * @param  character: Carácter a enviar.
  * @retval NONE.
  */
void LCD_WriteChar(uint8_t character){
	send_8_bits(character, DATA);
}

/**
  * @brief  Función para mostrar una cadena de texto en la LCD.
  * @param  *text: Dirección base del texto a enviar.
  * @retval NONE.
  */
void LCD_WriteString(char *text){

	if (text == NULL)
		return;

	while(*text)
		send_8_bits(*text++, DATA);
}

/**
  * @brief  Función para mostrar un número en la LCD.
  * @param  number: Número que se desea enviar.
  * @retval NONE.
  */
void LCD_WriteInt(uint8_t number){
    // Crear un buffer de texto (un entero de 8 bits ocupa máximo 3 dígitos + el carácter nulo '\0')
    char buffer_texto[4];

    // Convertir el entero a texto.
    sprintf(buffer_texto, "%3u", number);

    // Enviar la cadena de texto al LCD.
    LCD_WriteString(buffer_texto);
}

void LCD_WriteFloat(float number) {

    char buffer_texto[6];

    // Convertir el float a texto con 2 decimales (%.2f)
    snprintf(buffer_texto, sizeof(buffer_texto), "%.1f", number);

    // Enviar la cadena de texto al LCD.
    LCD_WriteString(buffer_texto);
}

/**
  * @brief  Función para ubicar el cursor en una posición específica.
  * @param  row: Número de la fila.
  * @param  column: Número de la columna.
  * @retval NONE.
  */
void LCD_SetCursor(uint8_t row, uint8_t column ){

	if ((row >= NUM_ROWS) || (column >= NUM_COLUMNS))
		return;

	send_8_bits(address[row] + column, COMMAND);
}

/**
  * @brief  Función para limpiar la pantalla.
  * @param  NONE
  * @retval NONE.
  */
void LCD_Clear(void){
	send_8_bits(0x01, COMMAND); // Clear display.
}

/**
  * @brief  Función para llevar el cursor a la posición (0,0).
  * @param  NONE
  * @retval NONE.
  */
void LCD_Home(void){
	send_8_bits(0x02, COMMAND); // Return home
}

/**
  * @brief  Función para mostrar el menú principal en la pantalla LCD.
  * @param  NONE
  * @retval NONE.
  */
void LCD_Main_Menu(void){
	LCD_Clear();
	LCD_SetCursor(0, 2);
	LCD_WriteString("MODO DE TRABAJO");
	LCD_SetCursor(2, 1);
	LCD_WriteString("> MANUAL");
	LCD_SetCursor(3, 3);
	LCD_WriteString("AUTOMATICO");
}

/**
  * @brief  Función para mostrar el menú del modo manual en la pantalla LCD.
  * @param  NONE
  * @retval NONE.
  */
void LCD_Manual_Menu(void){
	LCD_Clear();
	LCD_SetCursor(0, 7);
	LCD_WriteString("MANUAL");
	LCD_SetCursor(2, 3);
	LCD_WriteString("Angulo: 0");
	LCD_SetCursor(3, 1);
	LCD_WriteString("> Regresar");
}

/**
 * @brief  Función para mostrar el menú del modo automático en la pantalla LCD.
 * @param  NONE
 * @retval NONE.
 */
void LCD_Automatic_Menu(void){
	LCD_Clear();
	LCD_SetCursor(0, 5);
	LCD_WriteString("AUTOMATICO");
	LCD_SetCursor(2, 3);
	LCD_WriteString("Angulo: 0");
	LCD_SetCursor(3, 1);
	LCD_WriteString("> Regresar");
}

/**
  * @brief  Función para enviar 8 bits.
  * Primero se envian los 4 bits más significativos y luego los 4 menos significativos.
  * @param  byte: Dato que se va a enviar.
  * @param  type: 0 -> comando y 1 -> datos.
  * @retval NONE.
  */
static void send_8_bits(uint8_t byte, bool type){
	send_4_bits(byte & 0xf0, type); // Enviar los 4 bits más significativos.
	send_4_bits(byte << 4, type);   // Enviar los 4 bits menos significativos.
}

/**
  * @brief  Función para enviar 4 bits.
  * Se envian los bits y se genera el pulso requerido para la adquisición de los datos.
  * @param  byte: Dato que se va a enviar.
  * @param  type: 0 -> comando y 1 -> datos.
  * @retval NONE.
  */
static void send_4_bits(uint8_t byte, bool type){
	LCD_Write_Byte(byte + EN + BL + type); // EN = 1 BL = 1
	LCD_delay(1);
	LCD_Write_Byte(byte + BL + type); // EN = 0 BL = 1
	LCD_delay(1);
}
