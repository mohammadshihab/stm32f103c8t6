/* THIS IS THE CODE FOR WRITING BASIC TEXT IN OLED DISPLAY. where the display use
 * I2C serial communication . 
 * CONFIGURATION-SYS>DEBUG-SERIAL WIRE; CONNECTIVITY>I2C1>I2C & COFIGURATIN> I2C SPEED MODE> STANDERD MODE TO FAST MODE
 * To drive the oled display, 2 header files associated with
 * 2 c files is required . those are- fonts.h and ssd1306.h. see line 92 for more
 * comment info. More functionalities of those header files should be explored
 * ---------------------------------------------------------------------------
 * 5.2: updated : the general_menu() function is created to simplify the code,
 * also there is no blinking here , while updating a text in a same screen.
 * screen blink happens while the SSD1306_clear() function is used.
 * USAGE OF SSD1306_UpdateScreen() AFTER PRINTING A LINE OF TEXT , UPDATE THE
 * THE TEXT IN THE SCREEN NORMALLY AND DOES NOT BLINK THE SCREEN.
 * */

#include "main.h"
#include "fonts.h"
#include "ssd1306.h"
 I2C_HandleTypeDef hi2c1;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int count=0;
int i;

void general_menu(void){
   	  while(count<=5){

   	  	  if (count==0){
   	  	  SSD1306_GotoXY(0,17);
   	  	  SSD1306_Puts("1.about",&Font_7x10,1);
   	  	  HAL_Delay(500);
   	  	  }

   	  	  if(count==1){
   	  	  SSD1306_GotoXY(62,17);
   	  	  SSD1306_Puts("2.choose",&Font_7x10,1);
   	  	  HAL_Delay(500);
   	  	  }

   	  	  if(count==3){
   	  	  SSD1306_GotoXY(0,34);
   	  	  SSD1306_Puts("3.config",&Font_7x10,1);
   	  	  HAL_Delay(500);
   	  	  }

   	  	  if(count==4){
   	  	  SSD1306_GotoXY(62,34);
   	  	  SSD1306_Puts("4.profile",&Font_7x10,1);
   	  	  HAL_Delay(500);
   	  	  }

   	  	  if(count==5){
   	  	  SSD1306_GotoXY(0,51);
   	  	  SSD1306_Puts("5.how to use ",&Font_7x10,1);
   	  	  HAL_Delay(500);
   	  	  }

   	        SSD1306_UpdateScreen();
   	  	 // HAL_Delay(1000);
   	  	  count = count+1;
   	        }
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
	  /*clean and experimented code tested here, there are 3 font size.
	   * To write a line of text:
	   *     1.clear using SSD1306_Clear() if needed
	   *     2.select position of cursor using SSD1306_GotoXY(20, 0)
	   *     3.use SSD1306_Puts( , , ) to write a line
	   *     4.finally update screen using  SSD1306_UpdateScreen()
	   *     */
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
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
