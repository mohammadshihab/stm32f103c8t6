/* this code provides how to configure and CONTROL INDIVIDUAL PIN OR REGISTER
 * INDEPENDENTLY . here, no need to configure all pins from ioc figure (except
 * necessary configuration such as clock speed conf.)
 * For this there are 3 things need to write in MX_GPIO_Init(void) function,
 * those are 1.clock configuration for that register (in line 31)
 *           2.reset the pin of that register (in line 36)
 *           3.HAL_GPIO_Init with InitStruct (in line 41,48,55)
 * NOTE: USE DIRECT BINARY NUMBER FOR ANY REGISTER OR PIN      */

#include "main.h"
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  while (1)
  {
	  HAL_GPIO_WritePin(GPIOA, 0B11011, 1);
	  HAL_GPIO_WritePin(GPIOB, 0B01111, 1);
	  HAL_GPIO_WritePin(GPIOC, 0B10000000000000, 1); //PC_13 pin
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOD_CLK_ENABLE();

  //clock configuration of A,B,C:
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  //RESET for A,B,C:
  HAL_GPIO_WritePin(GPIOA, 0B00000000011111, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, 0B00000000011111, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, 0B10000000000000, GPIO_PIN_RESET);

  //for A:
  GPIO_InitStruct.Pin = 0B00000000011111;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  //for B:
  GPIO_InitStruct.Pin = 0B00000000011111;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  //for C:
  GPIO_InitStruct.Pin = 0B10000000000000;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
