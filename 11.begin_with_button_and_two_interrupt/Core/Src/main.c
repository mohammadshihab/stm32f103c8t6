/*04 june 2022: 11.begin_with_button_and_two_interrupt
 * this code covers the all about basic menu and sub-menu program.
 * here, you can move pointer or cursor to point a specific menu(WITH INERRUPT B1)
 * and open that pointed menu (WITH INTERRUPT B0).using the same button, you can
 * return back to the main menu page
 * requirement in this code, 1.SETUP OLED DISPLAY
 *                           2.SETUP INTERRUPT PROGRAM
 * 05 june 2022:
 *    moving cursor and selecting menu has been completed without any bug
 *    ++++
 *06 june 2022:(v.1)
 *    additional sub sub-menu or third page has been crated which will
 *    show the individual load details
 *    and cursor can be used to select anyone without any bug
 *07-june 2022:(v.2)
 *display can show ON or OFF based on the input response .
 *1 has been completed just, more to do
 *07-june 2022:(v.2):
 *showing individual on off status in load status (3rd page under 2nd submenu)
 *showing all ON OFF status beside the list of loads(3rd submenu)
 *
 *8 june 2022:(v.3)
 *how capture another extra interrupt using code(DONE) that will be used to count the
 *connected time.
 *8 june 2022:(v.3)
 *INDIVIDUAL ONTIME CAN BE MONITORED NOW. AS WELL AS ON OFF STATUS
 *a 555 TIMER is needed to provide pulse with the duration of 1 second
 *MONITORING PART WITH STM32 AND OLED DISPLAY IS DONE
 *
 */

#include "main.h"
#include "fonts.h"
#include "ssd1306.h"
 I2C_HandleTypeDef hi2c1;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int cursorbutton=0;
int smcursobutton=0;
int enterbutton = 0;

int cleartmmenu=1;
int cleartempmmenu=0;

int cleartssmenu=1;
int cleartempssmenu=0;


//------ GENERAL MENU OR FRONT PAGE STARTS HERE------------------//



void clearmmenuonce(){      // function for clearing screen once before entering main menu
	if (cleartempmmenu==1){
		cleartempmmenu=0;
		SSD1306_Clear();
	}
}



// cursor or pointer for selecting menu usnit keyword '#'
void mmenucursorfnc(void){
    if(cursorbutton==1){
  	  SSD1306_GotoXY(0,13);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(cursorbutton==2){
  	  SSD1306_GotoXY(0,26);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(cursorbutton==3){
  	  SSD1306_GotoXY(0,39);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(cursorbutton==4){
  	  SSD1306_GotoXY(0,52);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
    if(cursorbutton==5){
  	  SSD1306_GotoXY(0,51);
  	  SSD1306_Puts("#",&Font_7x10,1);
    }
}

//MAIN MENU OR general front page
void general_menu(void){
	      // SSD1306_Clear();
	      clearmmenuonce();
	      SSD1306_GotoXY(20, 0);
		  SSD1306_Puts("select menu-", &Font_7x10,1);

   	  	  SSD1306_GotoXY(0,13);
   	  	  SSD1306_Puts("1.about  ",&Font_7x10,1);

   	  	  SSD1306_GotoXY(0,26);
   	  	  SSD1306_Puts("2.load status",&Font_7x10,1);        //KNOWN AS LOADS

   	  	  SSD1306_GotoXY(0,39);
   	  	  SSD1306_Puts("3.list of load",&Font_7x10,1);       // KNOWN AS CONFIG

   	  	  SSD1306_GotoXY(0,52);
   	  	  SSD1306_Puts("4.profile",&Font_7x10,1);

   	  	  //SSD1306_GotoXY(0,51);
   	  	  //SSD1306_Puts("5.manual ",&Font_7x10,1);  //menu 5 has been deleted

   	  	  mmenucursorfnc();   // by this function, cursor or menu selction will work
 	      SSD1306_UpdateScreen();
     }

//------------------- GENERAL MENU OR FRONT PAGE ENDS HERE------------------//



//------------------FUNCTION FOR GPIO INPUT STARTS HERE-------------//

//------function for reading input to show ON OFF status starts here---------//

void input_read_fnc(void){
	if ((enterbutton==2) && (smcursobutton==1)){  //so that this ON or OFF can only been shown when the display is in ssubmenu page; ENTERBUTTON=2 means ssubmenu page
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_8)==1){  // if input from A8 is positive
			SSD1306_GotoXY(60, 13);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			SSD1306_GotoXY(60,13);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
	}
	if ((enterbutton==2) && (smcursobutton==2) ){  //so that this ON or OFF can only been shown when the display is in ssubmenu page; ENTERBUTTON=2 means ssubmenu page
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9)==1){  // if input from A8 is positive
			SSD1306_GotoXY(60, 13);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			SSD1306_GotoXY(60,13);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
	}
	if ((enterbutton==2) && (smcursobutton==3)){  //so that this ON or OFF can only been shown when the display is in ssubmenu page; ENTERBUTTON=2 means ssubmenu page
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_10)==1){  // if input from A8 is positive
			SSD1306_GotoXY(60, 13);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			SSD1306_GotoXY(60,13);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
	}
	if ((enterbutton==2) && (smcursobutton==4)){  //so that this ON or OFF can only been shown when the display is in ssubmenu page; ENTERBUTTON=2 means ssubmenu page
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_11)==1){  // if input from A8 is positive
			SSD1306_GotoXY(60, 13);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			SSD1306_GotoXY(60,13);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
	}
}

//------function for reading input to show ON OFF status ends here---------//



//------function for reading input to show ONTIME STATUS starts here---------//

int sec1s=0,sec1m=0,sec1h=0;
char sec11s[5],sec11m[5],sec11h[5];
int sec2s=0,sec2m=0,sec2h=0;
char sec22s[5],sec22m[5],sec22h[5];
int sec3s=0,sec3m=0,sec3h=0;
char sec33s[5],sec33m[5],sec33h[5];
int sec4s=0,sec4m=0,sec4h=0;
char sec44s[5],sec44m[5],sec44h[5];

int sec0s=0,sec0m=0,sec0h=0;                ////at 06-08-22 for showing system ontime too
char sec00s[5],sec00m[5],sec00h[5];

sysontime(void){
	itoa(sec0s,sec00s,10);         //THIS IS A FUNCITON THAT CONVERTS INT TYPE VALUE INTO CHAR TYPE VALUE
	itoa(sec0m,sec00m,10);
	itoa(sec0h,sec00h,10);
	SSD1306_GotoXY(93, 52);
	SSD1306_Puts(":", &Font_7x10, 1);      // : is a time portion divider
	SSD1306_GotoXY(100, 52);
	SSD1306_Puts(sec00s, &Font_7x10, 1);
	SSD1306_GotoXY(73, 52);
	SSD1306_Puts(":", &Font_7x10, 1);
	SSD1306_GotoXY(80, 52);
	SSD1306_Puts(sec00m, &Font_7x10, 1);
	SSD1306_GotoXY(60, 52);
	SSD1306_Puts(sec00h, &Font_7x10, 1);
}

//------------------------- ONTIME OF INPUT OR LOAD COUNTER STARTS HERE------------------//
void input_timer_read_fnc(void){                 //THE FUNCITON IS TO COUNT ONTIME LOAD ; THIS FUNCTION WILL WORK IN LINE 519 WITH PREVIOUSLY DECLARED input_read_fnc()
	// in this function there are total of 4 part which will display ontime for each load

	//display setup for load=1 in 3rd page for showing time (as smcursorbutton==1)

	if ((enterbutton==2)&&(smcursobutton==1)){

		itoa(sec1s,sec11s,10);         //THIS IS A FUNCITON THAT CONVERTS INT TYPE VALUE INTO CHAR TYPE VALUE
		itoa(sec1m,sec11m,10);
		itoa(sec1h,sec11h,10);
		SSD1306_GotoXY(93, 26);
		SSD1306_Puts(":", &Font_7x10, 1);      // : is a time portion divider
		SSD1306_GotoXY(100, 26);
		SSD1306_Puts(sec11s, &Font_7x10, 1);
		SSD1306_GotoXY(73, 26);
		SSD1306_Puts(":", &Font_7x10, 1);
		SSD1306_GotoXY(80, 26);
		SSD1306_Puts(sec11m, &Font_7x10, 1);
		SSD1306_GotoXY(60, 26);
		SSD1306_Puts(sec11h, &Font_7x10, 1);

		sysontime();
	}
	//display setup for load=2 in 3rd page for showing time (as smcursorbutton==2)

	if ((enterbutton==2)&&(smcursobutton==2)){      // ALL THOSE FOUR FUNCTIONS ARE QUITE SIMILAR

		itoa(sec2s,sec22s,10);
		itoa(sec2m,sec22m,10);
		itoa(sec2h,sec22h,10);
		SSD1306_GotoXY(93, 26);
		SSD1306_Puts(":", &Font_7x10, 1);
		SSD1306_GotoXY(100, 26);
		SSD1306_Puts(sec22s, &Font_7x10, 1);
		SSD1306_GotoXY(73, 26);
		SSD1306_Puts(":", &Font_7x10, 1);
		SSD1306_GotoXY(80, 26);
		SSD1306_Puts(sec22m, &Font_7x10, 1);
		SSD1306_GotoXY(60, 26);
		SSD1306_Puts(sec22h, &Font_7x10, 1);

		sysontime();
	}
	//display setup for load=3 in 3rd page for showing time (as smcursorbutton==3)

	if ((enterbutton==2)&&(smcursobutton==3)){

		itoa(sec3s,sec33s,10);
		itoa(sec3m,sec33m,10);
		itoa(sec3h,sec33h,10);
		SSD1306_GotoXY(93, 26);
		SSD1306_Puts(":", &Font_7x10, 1);
		SSD1306_GotoXY(100, 26);
		SSD1306_Puts(sec33s, &Font_7x10, 1);
		SSD1306_GotoXY(73, 26);
		SSD1306_Puts(":", &Font_7x10, 1);
		SSD1306_GotoXY(80, 26);
		SSD1306_Puts(sec33m, &Font_7x10, 1);
		SSD1306_GotoXY(60, 26);
		SSD1306_Puts(sec33h, &Font_7x10, 1);

		sysontime();
	}

	//display setup for load=4 in 3rd page for showing time (as smcursorbutton==4)

	if ((enterbutton==2)&&(smcursobutton==4)){

		itoa(sec4s,sec44s,10);
		itoa(sec4m,sec44m,10);
		itoa(sec4h,sec44h,10);
		SSD1306_GotoXY(93, 26);
		SSD1306_Puts(":", &Font_7x10, 1);
		SSD1306_GotoXY(100, 26);
		SSD1306_Puts(sec44s, &Font_7x10, 1);
		SSD1306_GotoXY(73, 26);
		SSD1306_Puts(":", &Font_7x10, 1);
		SSD1306_GotoXY(80, 26);
		SSD1306_Puts(sec44m, &Font_7x10, 1);
		SSD1306_GotoXY(60, 26);
		SSD1306_Puts(sec44h, &Font_7x10, 1);

		sysontime();
	}

}
//function for reading input to show ONTIME STATUS ends here
//------------------------- ONTIME OF INPUT OR LOAD COUNTER ENDS HERE------------------//



//------------------FUNCTION FOR GPIO INPUT ENDS HERE-------------//





//--------------------FUNCTION FOR SUB-MENU STARTS HERE------------------//

int cleart = 1;   // this variable is taken to count two ENTERBUTTON PRESS or B0 interrupt
int cleartemp=0;    // this button changes for every two ENTERBUTTON PRESS

//function for clearing (SSD1306_Clear()) only once before writing sub-menu; otherwise it will just blinks
void cleardisplay_once(void){
	if(cleartemp==1){
		SSD1306_Clear();
		cleartemp=0;
	}
}

//RAW FUNCTION declaration for all the sub-page or sub-menu under main menu//
//YOU CAN ADD ALL THE CODE HERE THAT WILL SHOW THE MONITORING STATUS

void about(void){                 //1st sub menu
	cleardisplay_once();
	SSD1306_GotoXY(0,0);
    SSD1306_Puts("This project shows ",&Font_7x10,1);
    SSD1306_GotoXY(0,13);
    SSD1306_Puts("the basic of embed",&Font_7x10,1);
    SSD1306_GotoXY(0,26);
    SSD1306_Puts("-ded OS that can be",&Font_7x10,1);
    SSD1306_GotoXY(0,39);
    SSD1306_Puts("used in monitoring",&Font_7x10,1);
    SSD1306_GotoXY(0,52);
    SSD1306_Puts("purpose of loads ",&Font_7x10,1);
    SSD1306_UpdateScreen();
}

//-------------sub menu cursor selector function-------//
// this will select the load from list from load_status(2nd submenu) fnc//
void smenucursorfnc_2(){
	if (cursorbutton==2){
		if(smcursobutton==1){
			SSD1306_GotoXY(0, 13);
			SSD1306_Puts("#", &Font_7x10,1);
		}
		else if(smcursobutton==2){
			SSD1306_GotoXY(0, 26);
			SSD1306_Puts("#", &Font_7x10,1);
		}
		else if(smcursobutton==3){
			SSD1306_GotoXY(0, 39);
			SSD1306_Puts("#", &Font_7x10,1);
		}
		else if(smcursobutton==4){
			SSD1306_GotoXY(0, 52);
			SSD1306_Puts("#", &Font_7x10,1);
		}
	}
}


void load_status(void){
	cleardisplay_once();
	SSD1306_GotoXY(0,0);
    SSD1306_Puts(" load status:",&Font_7x10,1);
    SSD1306_GotoXY(0,13);
    SSD1306_Puts("1.load_1",&Font_7x10,1);
    SSD1306_GotoXY(0,26);
    SSD1306_Puts("2.load_2",&Font_7x10,1);
    SSD1306_GotoXY(0,39);
    SSD1306_Puts("3.load_3",&Font_7x10,1);
    SSD1306_GotoXY(0,52);
    SSD1306_Puts("4.load_4",&Font_7x10,1);
    smenucursorfnc_2();
    SSD1306_UpdateScreen();
}

//----------------2nd sub menu (for cursorbutton=2) loadstatus function ends here------------//


//---------------3rd submenu (for cursorbutton=3) listofloads starts here---------------//

// function for showing ON OFF status(for cursorbutton=3) in 3rd submenu (list of load)

void onoffinlist_of_load(void){          //THIS FUNCTION IS SIMILAR TO input_read_fnc()
	if((enterbutton==1) && (cursorbutton==3)){
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_8)==1){  // if input from A8 is positive
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,1);
			SSD1306_GotoXY(60, 13);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,0);
			SSD1306_GotoXY(60,13);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_9)==1){  // if input from A9 is positive
			SSD1306_GotoXY(60, 26);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			SSD1306_GotoXY(60,26);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_10)==1){  // if input from A10 is positive
			SSD1306_GotoXY(60, 39);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			SSD1306_GotoXY(60,39);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
		if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_11)==1){  // if input from A11 is positive
			SSD1306_GotoXY(60, 52);
			SSD1306_Puts("ON ",&Font_7x10,1);
		}
		else {
			SSD1306_GotoXY(60,52);
			SSD1306_Puts("OFF", &Font_7x10, 1);
		}
	}
}


//  function for 3rd submenu  cursorbutton=3; list of load
void list_of_load(void){
	cleardisplay_once();
	SSD1306_GotoXY(10,0);
    SSD1306_Puts("list of load:",&Font_7x10,1);
    SSD1306_GotoXY(0,13);
    SSD1306_Puts("1.load_1",&Font_7x10,1);
    SSD1306_GotoXY(0,26);
    SSD1306_Puts("2.load_2",&Font_7x10,1);
    SSD1306_GotoXY(0,39);
    SSD1306_Puts("3.load_3",&Font_7x10,1);
    SSD1306_GotoXY(0,52);
    SSD1306_Puts("4.load_4",&Font_7x10,1);
    onoffinlist_of_load();
    SSD1306_UpdateScreen();
}


//function for 4th submenu; for cursorbutton=4
void profile(void){
	cleardisplay_once();
	SSD1306_GotoXY(0,0);
    SSD1306_Puts("number of loads- 4",&Font_7x10,1);
    SSD1306_GotoXY(0,13);
    SSD1306_Puts("controlling modes:",&Font_7x10,1);
    SSD1306_GotoXY(0,26);
    SSD1306_Puts("   1.WI-FI",&Font_7x10,1);
    SSD1306_GotoXY(0,39);
    SSD1306_Puts("   2.IR remote",&Font_7x10,1);
    SSD1306_GotoXY(0,52);
    SSD1306_Puts("manually - button ",&Font_7x10,1);
    SSD1306_UpdateScreen();
}
void manual(void){               //sub menu for 5th option ; THIS ONE HAS BEEN IGNORED
	cleardisplay_once();
	SSD1306_GotoXY(3,17);
    SSD1306_Puts("5.this is manual",&Font_7x10,1);
    SSD1306_UpdateScreen();
}





//FINAL SUBMENU FUNCIOTN; THIS WILL SHOW ANY SUBMENU ACCORDING TO (cursorbutton=..) THE SELECTED ONE FROM MENU
void sub_menu(void){
    if(cursorbutton==1){
    	if(enterbutton==1){
    		about();
    	}
    }
    if(cursorbutton==2){
    	if(enterbutton==1){
    		load_status();
    	}
    }
    if(cursorbutton==3){
    	if(enterbutton==1){
    		list_of_load();         // LIST OF LOAD WILL BE APPEARED FOR THIS FUNCTION
    	}
    }
    if(cursorbutton==4){
    	if(enterbutton==1){
    		profile();
    	}
    }
    if(cursorbutton==5){             //THIS ONE HAS BEEN IGNORED
    	if(enterbutton==1){
    			manual();
    	}
    }

}
//--------------------FUNCTION FOR SUB-MENU ENDS HERE-------------------//







//-------------------FUNCTION FOR SSUBMENU STARTS HERE-----------------//


void clearssmenuonce(void){  //for clearing the screen
	if (cleartempssmenu==1){
		cleartempssmenu=0;
		SSD1306_Clear();
	}
}




void s_sub_menu(){
	if ((enterbutton==2)&&(cursorbutton==2)){  // enterbutton=2 means it is in 3rd page(started from 0); cursorbutton 2 load_status selected in main menu
		if(smcursobutton==1){
			clearssmenuonce();
			//SSD1306_Clear();
			SSD1306_GotoXY(0,13);
			SSD1306_Puts("load 1:",&Font_7x10, 1);
			SSD1306_GotoXY(0,26);
			SSD1306_Puts("ontime:",&Font_7x10, 1);

                                               //at 06-08-22 for showing system ontime too
            SSD1306_GotoXY(0,39);
            SSD1306_Puts("system",&Font_7x10, 1);
            SSD1306_GotoXY(0,52);
            SSD1306_Puts("ontime:",&Font_7x10, 1);
			SSD1306_UpdateScreen();
		}
		if(smcursobutton==2){
			clearssmenuonce();
			SSD1306_GotoXY(0,13);
			SSD1306_Puts("load 2:",&Font_7x10, 1);
			SSD1306_GotoXY(0,26);
			SSD1306_Puts("ontime:",&Font_7x10, 1);

                               //at 06-08-22 for showing system ontime too
            SSD1306_GotoXY(0,39);
            SSD1306_Puts("system",&Font_7x10, 1);
            SSD1306_GotoXY(0,52);
            SSD1306_Puts("ontime:",&Font_7x10, 1);
			SSD1306_UpdateScreen();
		}
		if(smcursobutton==3){
			clearssmenuonce();
			//SSD1306_Clear();
			SSD1306_GotoXY(0,13);
			SSD1306_Puts("load 3:",&Font_7x10, 1);
			SSD1306_GotoXY(0,26);
			SSD1306_Puts("ontime:",&Font_7x10, 1);

            //at 06-08-22 for showing system ontime too
            SSD1306_GotoXY(0,39);
            SSD1306_Puts("system",&Font_7x10, 1);
            SSD1306_GotoXY(0,52);
            SSD1306_Puts("ontime:",&Font_7x10, 1);
			SSD1306_UpdateScreen();
		}
		if(smcursobutton==4){
			clearssmenuonce();
			SSD1306_GotoXY(0,13);
			SSD1306_Puts("load 4:",&Font_7x10, 1);
			SSD1306_GotoXY(0,26);
			SSD1306_Puts("ontime:",&Font_7x10, 1);

                                //at 06-08-22 for showing system ontime too
            SSD1306_GotoXY(0,39);
            SSD1306_Puts("system",&Font_7x10, 1);
            SSD1306_GotoXY(0,52);
            SSD1306_Puts("ontime:",&Font_7x10, 1);
			SSD1306_UpdateScreen();
		}
		input_read_fnc();  // this will show the show the individual ON OFF status of each load
		input_timer_read_fnc();   // this function will cover how to show the on time of INDIVIDUAL LOAD like prev. fnc input_read_fnc();
	}
}



//-------------------FUNCTION FOR SSUBMENU ENDS HERE-----------------//









//------------------- MAIN FUNCTION OF THE CODE STARTS HERE--------------//

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  SSD1306_Init();
  while (1)
  {
	  //input_read_fnc();
	 	  	  if(enterbutton==0){
	 	  	  general_menu(); //CALLING THE FUCTION WHICH WILL PRINT THE ALL MENU IN THE SCREEN
	 	  	  }
	 	  	  else if(enterbutton==1){
	 	  		  sub_menu();     //calling the function for sub menu
	 	  	  }
	 	  	  else if(enterbutton==2){
	 	  		  if(cursorbutton==2){
	 	  			  s_sub_menu();
	 	  		  }
	 	  	  }
  }
}

//------------------- MAIN FUNCTION OF THE CODE ENDS HERE--------------//


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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);





  /*Configure GPIO pins : PA1 PA2 */    //work as general purpose OUTPUT
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */   //work as general purpse INPUT
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  /*Configure GPIO pins : PB0 PB1 */   //work as interrupt pin
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/   // another portion to configure interrupt buttton
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);        // ALSO ADD THE FUNCTION void EXTI3_IRQHandler(void){} IN stm32f1xx_it.c FILE LIKE OTHER INTERRUPT PIN

}


//---------------INTERRUPT FUNCTION STARTS HERE--------------//


//this function will count weather the enterbutton has been pressed for TWICE, if so, then , cleart=2
void ctempfnc(void){   //for clearing submenu page once
	if (enterbutton ==0){
		cleart = cleart+1;
	}
	if (enterbutton==1){
		cleart = cleart+1;
	}
}

void ctempmmneufnc(void){   //for clearing main menu page once
	if (enterbutton!=0){
		cleartmmenu=cleartmmenu+1;
	}
	if (enterbutton==0){
		cleartmmenu=cleartmmenu+1;
	}
}


void ctempssmenufnc(void){    // for clearing sub sub menu (or third page
	if (enterbutton!=2){
		cleartssmenu=cleartssmenu+1;
	}
	if(enterbutton==2){
		cleartssmenu=cleartssmenu+1;
	}
}



int temp1=0,temp2=0,temp3=0,temp4=0;  // used in in B3 interrupt function , those are needed to clear screen ONCE for OFF STATE OF LOAD
//INTERRUPT FUNCTION
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//interrupt for B1 = for cursor button
  if (GPIO_Pin == GPIO_PIN_1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
    if (enterbutton==0){
        cursorbutton=cursorbutton+1;   //for the main menu page
        if(cursorbutton>=5){
        	cursorbutton=1;  // so , cursor button will started from 1 again
        }
    }
    else if((enterbutton==1) && (cursorbutton==2)){
    	smcursobutton=smcursobutton+1;  //for the submenu page
    	if (smcursobutton>=5){
    		smcursobutton=1;   // so, smcursorbutton will start from 1 againg
    	}
    }
  }

 //interrupt for B0 = for enter boutton
  if(GPIO_Pin == GPIO_PIN_0){
	  //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);

	  enterbutton=enterbutton+1;

	  if (cursorbutton==2){   //menu 2 or load is selected, so, an additional page or third page is required
		  if(enterbutton>=3){    //thats why in this condition, enterbutton can be go up to 2 (total, 0,1 and2)
			  enterbutton=0;
		  }
	  }

	  else{              // else or except menu 2 or load status fnc  , additional page is not required
		  if(enterbutton>=2){       // so, it will take up to 1
			  enterbutton=0;
		  }
	  }


	                             // BY THIS, the value of enterbutton will be either 0 , 1 or 2;
	                              // 0 will take to main menu or front page and 1 will take to sub-menu or second page
	                              // and 2 will take to sub-sub page ;see the while loop for details




	  ctempfnc();             //for clearing submenu // function for counting TWO enter button press
	  if (cleart==2){           // clear==2 means the enterbutton has been pressed twice and enterbutton==1  (i.1to0(main menu); ii.0to1(submenu)
		  //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		  cleart=0;              // initially, in declaration, cleart =1; which will works for one entebutton pressing as it dont back from main menu
		  cleartemp=1;           //so, the page is at sub menu and the it should clear the page; thats why cleartemp=1;
	  }


	  ctempmmneufnc();     // for clearing main menu
	  if (cleartmmenu==2){
		  cleartmmenu=0;
		  cleartempmmenu=1;
	  }


	  ctempssmenufnc();       // for clearing sub-sub menu
	  if(cleartssmenu>=2){
		  cleartempssmenu=1;
	  }
  }

  //INTERRUPT PIN 3 PB3 FOR COUNTING THE LOAD ON-TIME
  if(GPIO_Pin == GPIO_PIN_3){
	  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);

		sec0s=sec0s+1;    // at 06-08-22 for updating with system ontime
		                        //incrementing second

		if (sec0s>=60){  // to make a minute
						SSD1306_Clear();
						sec0m=sec0m+1;
						if(sec0m>=60){
							sec0h=sec0h+1;
							sec0m=0;
						}
						sec0s=0;
					}


	  //for load-1 (connected to input pin A8)
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
			sec1s=sec1s+1;    //incrementing second

			if (sec1s>=60){  // to make a minute
							SSD1306_Clear();
							sec1m=sec1m+1;
							if(sec1m>=60){
								sec1h=sec1h+1;
								sec1m=0;
							}
							sec1s=0;
						}
			temp1=0;
		}
		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==0){
			sec1s=0;
			sec1m=0;
			sec1h=0;
			if ((temp1==0)&&(enterbutton==2)){
				SSD1306_Clear();
				temp1=temp1+1;
			}
		}

		//for load-2 (connected to input pin A9)
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			sec2s=sec2s+1;
			if (sec2s>=60){
							SSD1306_Clear();
							sec2m=sec2m+1;
							if(sec2m>=60){
								sec2h=sec2h+1;
								sec2m=0;
							}
							sec2s=0;
						}
			temp2=0;
		}
		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==0){
			sec2s=0;
			sec2m=0;
			sec2h=0;
			if ((temp2==0)&&(enterbutton==2)){
				SSD1306_Clear();
				temp2=temp2+1;
			}
		}

		//for load-3 (connected to input pin A10)
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			sec3s=sec3s+1;
			if (sec3s>=60){
							SSD1306_Clear();
							sec3m=sec3m+1;
							if(sec3m>=60){
								sec3h=sec3h+1;
								sec3m=0;
							}
							sec3s=0;
						}
			temp3=0;
		}
		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==0){
			sec3s=0;
			sec3m=0;
			sec3h=0;
			if ((temp3==0)&&(enterbutton==2)){
				SSD1306_Clear();
				temp3=temp3+1;
			}
		}

		//for load-4 (connected to input pin A11)
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			sec4s=sec4s+1;
			if (sec4s>=60){
							SSD1306_Clear();
							sec4m=sec4m+1;
							if(sec4m>=60){
								sec4h=sec4h+1;
								sec4m=0;
							}
							sec4s=0;
						}
			temp4=0;
		}
		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==0){
			sec4s=0;
			sec4m=0;
			sec4h=0;
			if ((temp4==0)&&(enterbutton==2)){
				SSD1306_Clear();
				temp4=temp4+1;
			}
		}
  }
}
//---------------INTERRUPT FUNCTION ENDS HERE----------------//

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
