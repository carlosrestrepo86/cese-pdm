/*
 * API_lcd_port.c
 *
 *  Created on: 23/09/2026
 *      Author: c_and
 */

#include "lcd_port.h"

static I2C_HandleTypeDef hlcd;

/**
  * @brief  Función para enviar un byte a la pantalla.
  * @param  byte: Dato que se va a enviar.
  * @retval bool: True -> Envío OK.
  *               False -> Error en el envío.
  */
bool LCD_Write_Byte(uint8_t byte){

	HAL_StatusTypeDef status;

	status = HAL_I2C_Master_Transmit (&hlcd, LCD_DIR << 1, &byte, sizeof(byte), HAL_MAX_DELAY);

	if (status != HAL_OK)
		return false;
	else
		return true;
}

/**
  * @brief  Función para generar un delay.
  * @param  time: Tiempo para el delay.
  * @retval NONE.
  */
void LCD_delay(uint32_t time){

	if (time != 0U)
		  HAL_Delay(time);
}

/**
  * @brief  Función para inicializar I2C MSP.
  * @param  htim: Manejador I2C.
  * @retval NONE
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if (hi2c->Instance == LCD_I2C){

		__HAL_RCC_I2C1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**I2C1 GPIO Configuration
		    PB6     ------> SCL
		    PB7     ------> SDA
		 */
		GPIO_InitStruct.Pin = LCD_SCL_PIN | LCD_SDA_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = LCD_I2C_AF;
		HAL_GPIO_Init(LCD_GPIO_PORT, &GPIO_InitStruct);
	}
}

/**
  * @brief  Función para desinicializar I2C MSP.
  * @param  htim: Manejador I2C.
  * @retval NONE
  */
void HAL_I2C_MspDeInit (I2C_HandleTypeDef* hi2c){

	if (hi2c->Instance == LCD_I2C){

		__HAL_RCC_I2C1_CLK_DISABLE();

		HAL_GPIO_DeInit(LCD_GPIO_PORT, LCD_SCL_PIN | LCD_SDA_PIN);
	}
}

/**
  * @brief  Función para configurar la comunicación I2C (velocidad de reloj, dirección del maestro).
  * @param  NONE.
  * @retval bool: True -> Configuración OK.
  *               False -> Error de configuración.
  */
bool_t LCD_Port_Init(void){

	hlcd.Instance = LCD_I2C;
	hlcd.Init.ClockSpeed = CLOCK_SPEED;
	hlcd.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hlcd.Init.AddressingMode = ADDRESSING_MODE;
	hlcd.Init.OwnAddress1 = 0;
	hlcd.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hlcd.Init.OwnAddress2 = 0;
	hlcd.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hlcd.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hlcd) != HAL_OK)
		return false;
	else
		return true;
}
