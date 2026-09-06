/*
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* ========================== INCLUDES ========================== */

#include "main.h"

/* ============================================================== */
/* ========================== DEFINITIONS ======================= */

#define VECTOR_SIZE 3

/* ============================================================== */
/* ========================== VARIABLES ========================= */

UART_HandleTypeDef huart2;
delay_t delay;
tick_t delay_times[VECTOR_SIZE] = {1000, 200, 100};  // Vector de tiempos para el delay (valor maximo 4.294.967 ms = 4.294.967 seg).
uint8_t sel_time = 0;                                // Variable para seleccion de los tiempos.
uint8_t i = 0;                                       // Variable para contar los flancos de la señal.

/* ============================================================== */

/* ===================== FUNCTION PROTOTYPES ==================== */

void SystemClock_Config(void);
static void GPIO_Init(void);
static void USART2_UART_Init(void);

/* ============================================================== */

int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	GPIO_Init();
	USART2_UART_Init();

	/* Initialize the non-blocking delay */
	delayInit(&delay, delay_times[sel_time]);
	sel_time++;

	while (1)
	{
		// Verificar si ya se cumplio el tiempo programado.
		if (delayRead(&delay)) {
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			i++;

			/* Verificar si se cumplieron las 5 repeticiones del delay.
			 * Cada periodo (--__ on/off) equivale a 2 incrementos de la variable i.
			 */
			if (i == 10) {
				delayWrite(&delay, delay_times[sel_time]); // Cambiar el tiempo del delay.
				i = 0;

				// Condicional para seleccionar otro tiempo en el vector, verificando el correcto acceso.
				if (sel_time == (VECTOR_SIZE - 1)) {
					sel_time = 0;
				} else {
					sel_time++;
				}
			}
		}
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/**
  * @brief Delay Initialization Function
  * @param delay: Pointer to the delay structure
  * @param duration: Time duration in milliseconds
  * @retval None
  */
void delayInit(delay_t *delay, tick_t duration){

	if (delay == NULL || duration == 0) return;

	delay->duration = duration;
	delay->running = false;
}

/**
  * @brief Delay Read Function
  * @param delay: Pointer to the delay structure
  * @retval False --> The delay is running.
  *         True  --> The delay ended.
  */
bool_t delayRead(delay_t *delay){

	if (delay == NULL) return false;

	bool_t delay_state = false;

	if (delay->running){
		if((HAL_GetTick() - delay->startTime) >= delay->duration){
			delay->running = false;
			delay_state = true;
		}else{
			delay_state = false;
		}
	}else{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	return delay_state;
}

/**
  * @brief Delay Write Function
  * @param delay: Pointer to the delay structure
  * @param duration: Time duration in milliseconds
  * @retval None
  */
void delayWrite(delay_t *delay, tick_t duration){

	if (delay == NULL || duration == 0) return;

	delay->duration = duration;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
