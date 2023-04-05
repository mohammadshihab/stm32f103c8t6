/*03-june-22: this code is the combination of i2c OLED display and external interrupt
 *
 * for oled,select CORE>DEBUGER>SERIAL WIRE; RCC>CLOCK>HSC>CRYSTAL
 *                 CONNECTIVITY>I2C1>I2C; CONFIGURATION>PARAMETER SETTINGS>I2C SPEED MODE>FAST MODE
 *                 then two(.h) and two(.c) will be required. and then using thec header(.h) function
 *                 and some specific function , OLED DISPLAY CAN BE USED
 *
 * for external interrupt, SELECT THE SPECIFIC PIN AS GPIO_STI first.
 *                 then, goto NVIC(above RCC)>SELECT EXTI LINE INTERRUPT(at the bottom last)
 *                 then select enabled.
 *
 * then click save which will generate the code.
 * the following function is responsible for doing all the stuff regarding external interrupt
 * void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
 *if (GPIO_Pin == GPIO_PIN_1){}
 *}
 *
 *
 *
 *03-june-22: updating to add another interrupt button which is B0 (Previous one was B1)
 *
 */


#include "main.h"
#include "fonts.h"
#include "ssd1306.h"
 I2C_HandleTypeDef hi2c1;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int count=0;
int i;

int bpressed=0;


void bpressedfnc(void){
    if(bpressed==1){
  	  SSD1306_GotoXY(0,17);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(bpressed==2){
  	  SSD1306_GotoXY(62,17);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(bpressed==3){
  	  SSD1306_GotoXY(0,34);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(bpressed==4){
  	  SSD1306_GotoXY(62,34);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(bpressed==5){
  	  SSD1306_GotoXY(0,51);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
}


void general_menu(void){


   	  	  SSD1306_GotoXY(0,17);
   	  	  SSD1306_Puts("1.about",&Font_7x10,1);

   	  	  SSD1306_GotoXY(62,17);
   	  	  SSD1306_Puts("2.choose",&Font_7x10,1);

   	  	  SSD1306_GotoXY(0,34);
   	  	  SSD1306_Puts("3.config",&Font_7x10,1);

   	  	  SSD1306_GotoXY(62,34);
   	  	  SSD1306_Puts("4.profile",&Font_7x10,1);

   	  	  SSD1306_GotoXY(0,51);
   	  	  SSD1306_Puts("5.project manual",&Font_7x10,1);

   	  	  bpressedfnc();

 	      SSD1306_UpdateScreen();

     }



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  SSD1306_Init();
      SSD1306_GotoXY (16,0);
      SSD1306_Puts ("shihab", &Font_11x18,1);
      SSD1306_GotoXY (0, 30);
      SSD1306_UpdateScreen();
      HAL_Delay(1000);
      SSD1306_Puts ("MOHHAMMAD", &Font_11x18, 1);
      SSD1306_UpdateScreen();
      HAL_Delay (1000);

      SSD1306_Clear();
      SSD1306_GotoXY (3,3);
      SSD1306_Puts ("welcome", &Font_16x26, 1);
      SSD1306_UpdateScreen();
      HAL_Delay(500);
      SSD1306_GotoXY (0,51);
      SSD1306_Puts ("(largest font)", &Font_7x10, 1);
      SSD1306_UpdateScreen();
      HAL_Delay(3000);
      SSD1306_Clear();

  while (1)
  {
	  SSD1306_GotoXY(20, 0);
	  	  SSD1306_Puts("select menu-", &Font_7x10,1);
	  	  general_menu(); //CALLING THE FUCTION WHICH WILL PRINT THE ALL MENU IN THE SCREEN
  }
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
static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = 0B111;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  //external interrupt for B1
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);




}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
    bpressed=bpressed+1;
    if(bpressed>=6){
    	bpressed=1;
    }
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
