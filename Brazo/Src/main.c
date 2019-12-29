/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint32_t adc_to_dma_values[NUM_SERVOS]={0};
uint32_t adc_to_dma_lastvalues[NUM_SERVOS]={0};
uint32_t pose_counter = 0;
uint8_t playing;
uint32_t pose_actual=0;
char uart_recieve=0;
uint16_t uart_data=0;
uint8_t syncr_status=0;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void user_init();
void reset_positions();
void adc_dma_start_stop(int time);
void stop_adc_dma();
void default_position();
int get_dma_value_norm(int i);
void lcd_manager(uint8_t code, uint16_t servo_pose);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//-----------UART_FUNC---------
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

GETCHAR_PROTOTYPE
{
	char ch;
	HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, 0xFFFF);

	return ch;
}
//-----------UART_FUNC_END------------

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM9_Init();
  MX_TIM7_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  user_init();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
check:  if(playing==1){
	  		static uint8_t ok_servo1=0;
	  		static uint8_t ok_servo2=0;
	  		static uint8_t ok_servo3=0;
	  		static uint8_t ok_servo4=0;
  	  		ok_servo1=0;
  			ok_servo2=0;
  			ok_servo3=0;
  			ok_servo4=0;

	  	  	for(pose_actual=0; pose_actual<pose_counter; pose_actual++){ //todas las posiciones guardadas

				//lcd mode playing
				lcd_manager(0, 1);

	  	  		if(playing==0){//si se pulsa stop se volvera a empezar desde el principio
	  	  			pose_actual=0;
	  	  			goto check;
	  	  		}
	  	  		//reset flag de la position terminada
	  	  		  uint8_t ok_servo1=0;
	  			  uint8_t ok_servo2=0;
	  			  uint8_t ok_servo3=0;
	  			  uint8_t ok_servo4=0;

	  			while(ok_servo1==0 || ok_servo2==0 || ok_servo3==0 || ok_servo4==0){
	  			  for(int servo=0; servo< NUM_SERVOS; servo++ ){
	  					switch(servo){
	  						case 0 :
	  							if(ok_servo1==0){
	  								if(TIM2->CCR1 != posiciones.servo1[pose_actual]){
	  									if(TIM2->CCR1 < posiciones.servo1[pose_actual]){
	  										TIM2->CCR1=TIM2->CCR1+1;
	  									}else if(TIM2->CCR1 > posiciones.servo1[pose_actual]){
	  										TIM2->CCR1=TIM2->CCR1-1;
	  										}
	  								}else if(TIM2->CCR1 == posiciones.servo1[pose_actual]){
	  									ok_servo1=1;
	  							    	}
	  							}else if(ok_servo1==1){
	  								break;
	  							}
	  							 break;
	  						case 1 :
	  							if(ok_servo2==0){
	  								if(TIM3->CCR1 != posiciones.servo2[pose_actual]){
	  									if(TIM3->CCR1 < posiciones.servo2[pose_actual]){
	  										TIM3->CCR1=TIM3->CCR1+1;
	  									}else if(TIM3->CCR1 > posiciones.servo2[pose_actual]){
	  										TIM3->CCR1=TIM3->CCR1-1;
	  										}
	  								}else if(TIM3->CCR1 == posiciones.servo2[pose_actual]){
	  									ok_servo2=1;

	  							    	}
	  							}else if(ok_servo2==1){
	  								break;
	  							}
	  							 break;
	  						case 2 :
	  							if(ok_servo3==0){
	  								if(TIM4->CCR1 != posiciones.servo3[pose_actual]){
	  									if(TIM4->CCR1 < posiciones.servo3[pose_actual]){
	  										TIM4->CCR1=TIM4->CCR1+1;
	  									}else if(TIM4->CCR1 > posiciones.servo3[pose_actual]){
	  										TIM4->CCR1=TIM4->CCR1-1;
	  										}
	  								}else if(TIM4->CCR1 == posiciones.servo3[pose_actual]){
	  									ok_servo3=1;
	  							    	}
	  							}else if(ok_servo3==1){
	  								break;
	  							}
	  							 break;
	  						case 3 :
	  							if(ok_servo4==0){
	  								if(TIM9->CCR1 != posiciones.servo4[pose_actual]){
	  									if(TIM9->CCR1 < posiciones.servo4[pose_actual]){
	  										TIM9->CCR1=TIM9->CCR1+1;
	  									}else if(TIM9->CCR1 > posiciones.servo4[pose_actual]){
	  										TIM9->CCR1=TIM9->CCR1-1;
	  										}
	  								}else if(TIM9->CCR1 == posiciones.servo4[pose_actual]){
	  									ok_servo4=1;
	  							    	}
	  							}else if(ok_servo4==1){
	  								break;
	  							}
	  							 break;
	  						default:
	  							servo=0;
	  							 break;

	  					}//switch
	  				}//for all servos
					for(int time=0; time< PLAYING_DELAY;time++){//tiempo-> smooth servos movement
						if(playing==0){//si se pulsa stop se volvera a empezar desde el principio
							 pose_actual=0;
							goto check;
						}
					}
	  			}//while not ok_posex
	  	  	}//for all poses
	  }//if playing
}//bucle while
  /* USER CODE END 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void user_init(void){

//limpiar la memoria de posiciones

	lcd_init();
	lcd_clear();
	lcd_send_string("Hello there!");
	lcd_print_x_y(2, 0, "proyect: Robot Arm");
	lcd_print_x_y(3, 0, "by: Sergio and David");
//posicion inicial para evitar choques

	default_position();
	playing=0;
//encender adc y DMA

	//aqui "adc_to_dma_values" es el buffer
	//donde el dma va a guardar las conversiones del adc

	HAL_ADC_Start_DMA(&hadc,adc_to_dma_values,NUM_SERVOS);

//encender servos (timers)

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
//canvas inicial

	HAL_Delay(2000);
	lcd_manager(2, 0);
//el timer 7 es para coger valores de forma periodica en el
//dma por el adc
	HAL_TIM_Base_Start(&htim7);
	HAL_TIM_Base_Start_IT(&htim7);
//el timer 6 es para actualizar los valores del lcd prediodicamente
//evita retrasos en la ejecucion de funciones como el posicionamineto de servos
//*el timer 6 tambien es: debouncer reset (usado en el record BTM y laser led BTM)
	HAL_TIM_Base_Start(&htim6);
	HAL_TIM_Base_Start_IT(&htim6);
// Habilitamos poder recibir datos del uart para guardar o cargar las posiciones
	HAL_UART_Receive_IT(&huart2, &uart_recieve, sizeof(uint8_t));

}

//-----------------FUNIONES_PROPIAS------------------

void reset_positions(void){
	for(int i = 0; i<MAX_POSES ;i++){
		posiciones.servo1[i]=0;
		posiciones.servo2[i]=0;
		posiciones.servo3[i]=0;
		posiciones.servo4[i]=0;
		pose_counter=0;
	}
}

void default_position(void){
	TIM2->CCR1=1100;
	TIM3->CCR1=1100;
	TIM4->CCR1=1100;
	TIM9->CCR1=1100;
}

void adc_dma_start_stop(int time){

	if (time==0){
		HAL_ADC_Start_DMA(&hadc,adc_to_dma_values,NUM_SERVOS);
	}else{
		HAL_ADC_Start_DMA(&hadc,adc_to_dma_values,NUM_SERVOS);
		for(int i = 0 ; i<time ; i++){
			// wait x time
		}
		HAL_ADC_Stop_DMA(&hadc);
	}
}
void stop_adc_dma(void){
	HAL_ADC_Stop_DMA(&hadc);
}

int get_dma_value_norm(int i){
	if(i>NUM_SERVOS){
		return 0;
	}
	//la recta es adc*1,3+1500
	return ((adc_to_dma_values[i]*13)/10+1500);


}
//--------------lcd--manager----------------
void lcd_manager(uint8_t code, uint16_t code_value){

	switch (code) {
	case 0: //modo: 0 code_value recording 0 - playing 1 - saved pose 2 - stopped 3-
		switch (code_value) {
		case 0:
			lcd_print_x_y(0,0,"                    ");//clear line 1
			lcd_print_x_y(0, 0, "MODE: recording");
			lcd_print_x_y(1,0,"                    ");//clear line 1
			lcd_print_x_y(1,0,"saved poses:");
			lcd_send_number(1, 13, pose_counter);
			break;
		case 1:
			lcd_print_x_y(0,0,"                    ");//clear line 1
			lcd_print_x_y(0, 0, "MODE: playing");
			lcd_print_x_y(1,0,"                    ");//clear line 1
			lcd_print_x_y(1,0,"playing:");
			lcd_send_number(1, 9, pose_actual);
			lcd_print_x_y(1, 12, "of ");
			lcd_send_number(1, 14, pose_counter);
			break;
		case 2:
			lcd_print_x_y(0,0,"                    ");//clear line 1
			lcd_print_x_y(0, 0, "MODE: pose saved! ");
			lcd_print_x_y(1,0,"                    ");//clear line 1
			lcd_print_x_y(1,0,"saved poses:");
			lcd_send_number(1, 13, pose_counter);

			break;
		case 3:
			lcd_print_x_y(0, 0, "MODE: stopped!!");
			break;
		case 4:
			lcd_print_x_y(0, 0, "MODE: load_pc");
			break;
		case 5:
			lcd_print_x_y(0, 0, "MODE: saved_pc");
			break;
		case 6://reset poses -> recording poses
			lcd_print_x_y(0,0,"                    ");//clear line 1
			lcd_print_x_y(0, 0, "MODE: deleted poses!");
			lcd_print_x_y(1,0,"                    ");//clear line 1
			lcd_print_x_y(1,0,"saved poses:");
			lcd_send_number(1, 13, pose_counter);
			break;
		case 7:
			lcd_print_x_y(0,0,"                    ");//clear line 1
			lcd_print_x_y(0, 0, "MODE: UART SENT");
			break;
		case 8:
			lcd_print_x_y(0,0,"                    ");//clear line 1
			lcd_print_x_y(0, 0, "MODE: UART PC->MICRO");
			break;
		default:
			break;
		}
		break;
	case 1:
		lcd_print_x_y(2, 0, "s1:");
		lcd_send_number(2, 4, TIM2->CCR1);
		//servo2
		lcd_print_x_y(2, 9, "s2:");
		lcd_send_number(2, 13, TIM3->CCR1);
		//servo3
		lcd_print_x_y(3, 0, "s3:");
		lcd_send_number(3, 4, TIM4->CCR1);
		//servo4
		lcd_print_x_y(3, 9, "s4:");
		lcd_send_number(3, 13, TIM9->CCR1);
		break;
	case 2: //canvas inicial
		lcd_clear();
		lcd_print_x_y(0, 0, "MODE: LOADING...");
		lcd_print_x_y(1,0,"saved poses:");
		lcd_print_x_y(2, 0, "s1:");
		lcd_print_x_y(2, 9, "s2:");
		lcd_print_x_y(3, 0, "s3:");
		lcd_print_x_y(3, 9, "s4:");

		break;
	case 3: //error
		lcd_clear();
		lcd_print_x_y(0, 0, "MODE: ERROR");
		break;
	default:
		break;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	//ENVIA LA INFORMACION
	if(uart_recieve!='\n' && (uart_recieve=='s'||uart_recieve=='S')){
		HAL_TIM_Base_Stop(&htim6);
		HAL_TIM_Base_Stop_IT(&htim6);
		lcd_manager(0, 7);
		//printf("saved poses %d \r\n",pose_counter);
		printf("%d \r\n",pose_counter);
		if(playing==0){
			for(int pose=0;pose<pose_counter;pose++){
				printf("%d,%d,%d,%d\r\n",posiciones.servo1[pose],posiciones.servo2[pose],posiciones.servo3[pose],posiciones.servo4[pose]);
			}
		}
		HAL_TIM_Base_Start(&htim6);
		HAL_TIM_Base_Start_IT(&htim6);
	}else if(uart_recieve!='\n' && (uart_recieve=='l'||uart_recieve=='L')){

		HAL_UART_Receive(&huart2,&uart_data, sizeof(uart_data),50);

		pose_counter=uart_data;
		pose_actual=0;//creo que esto sobra

		for(int data=0;data<pose_counter;data++){
			HAL_UART_Receive(&huart2,&uart_data, sizeof(uart_data),50);
			posiciones.servo1[data]=uart_data;
			HAL_UART_Receive(&huart2,&uart_data, sizeof(uart_data),50);
			posiciones.servo2[data]=uart_data;
			HAL_UART_Receive(&huart2,&uart_data, sizeof(uart_data),50);
			posiciones.servo3[data]=uart_data;
			HAL_UART_Receive(&huart2,&uart_data, sizeof(uart_data),50);
			posiciones.servo4[data]=uart_data;
		}
		syncr_status=0;
		lcd_manager(0,8);


	}

	HAL_UART_Receive_IT(&huart2, &uart_recieve, sizeof(uint8_t));

}
//----------------------------------------------------
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
