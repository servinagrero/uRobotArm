/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32l1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */
extern uint32_t adc_to_dma_values[NUM_SERVOS];
extern uint32_t adc_to_dma_lastvalues[NUM_SERVOS];
extern uint16_t pose_counter;
extern int get_dma_value_norm_norm_norm_norm(int i);
extern void reset_positions(void);
extern void lcd_manager(uint8_t code, uint32_t code_value);
extern uint8_t playing;
extern int pose_actual;
extern uint8_t syncr_status;
uint8_t debouncer;

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
	  lcd_manager(3, 0);
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	__disable_irq();
	//RESET POSES:
if(playing==0){
	//reset posiciones y continua la toma de datos dma
	if(pose_counter>0){

		//lcd sincronismo al "syncr_status" ciclo
		syncr_status=0;
		lcd_manager(0, 6);

		reset_positions();
		playing=0;
		HAL_TIM_Base_Start(&htim7);
		HAL_TIM_Base_Start_IT(&htim7);
	}
}
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
  __enable_irq();
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */
	__disable_irq();

	//START PLAY POSITIONS:
	if(playing == 0 && pose_counter > 0){
		//lcd sincronismo al "syncr_status" ciclo
		lcd_manager(0, 1);
		syncr_status=0;

		HAL_TIM_Base_Stop(&htim7);
		HAL_TIM_Base_Stop_IT(&htim7);
		playing=1;
	}
  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */
  __enable_irq();
  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */
	__disable_irq();
	//STOP: positions without reset the pose_counter
	if(playing==1){
		//lcd sincronismo al "syncr_status" ciclo
		lcd_manager(0, 3);
		syncr_status=0;

		HAL_TIM_Base_Start(&htim7);
		HAL_TIM_Base_Start_IT(&htim7);
		playing=0;
	}
  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_IRQn 1 */
  __enable_irq();
  /* USER CODE END EXTI2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */
  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
	//LASER LED
	if(debouncer==0){
		debouncer=1;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	}
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  //SAVE POSE
if(playing==0){
	if(debouncer==0){
		if(pose_counter < MAX_POSES){
			for(int i = 0; i<4;i++){
				posiciones.servo1[pose_counter]= TIM2->CCR1;
				posiciones.servo2[pose_counter]= TIM3->CCR1;
				posiciones.servo3[pose_counter]= TIM4->CCR1;
				posiciones.servo4[pose_counter]= TIM9->CCR1;
			}
			pose_counter++;
			//lcd sincronismo al "syncr_status" ciclo
			lcd_manager(0, 2);
			syncr_status=0;

		}else {
			lcd_manager(3, 0);
		}
		debouncer=1;
	}
}
  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt.
  */
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */
	//lcd servo and mode manager call
	HAL_TIM_Base_Stop(&htim6);
	HAL_TIM_Base_Stop_IT(&htim6);

	//el modo solo se actualiza cada "syncr" ciclos
	//debido al delay del lcd si no hacemos cada x ciclos
	//no variamos el modo: stop modo: saved pose
	static uint8_t delay_syncr=4;


	if(playing == 0){
		//modo 0 record (0)
		if(syncr_status<delay_syncr){
			syncr_status++;
		}else if(syncr_status==delay_syncr){

			syncr_status=0;
			lcd_manager(0, 0);		//servo pose updating in lcd (0 have no meaning here)

		}
		lcd_manager(1,0);
	}else if(playing == 1){

		//servo pose updating in lcd (0 have no meaning here)
		lcd_manager(1,0);
	}
	HAL_TIM_Base_Start(&htim6);
	HAL_TIM_Base_Start_IT(&htim6);

	//debouncer reset (usado en el record BTM y laser led BTM)
	debouncer=0;

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */

  /* USER CODE END TIM6_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */

//RECORDING POSE:
HAL_TIM_Base_Stop(&htim7);
HAL_TIM_Base_Stop_IT(&htim7);
	//comparamos los valores de last_dma con dma en cada servo

if(playing==0){
	for(int i=0; i< NUM_SERVOS; i++){
		//variables para evitar desbordamiento en la resta (threshold)
		int value = get_dma_value_norm(i);
		int lastvalue = adc_to_dma_lastvalues[i];

		//(avoid freezing) por si cambia el dma durante el movimiento

		int valor= get_dma_value_norm(i);

		//si la diferencia absoluta last dma y dma que el THRESHOLD_POT

		if(abs(value-lastvalue) > THRESHOLD_POT){

			//como ha cambiado:
			//adc_to_dma_values copiamos para la siguiente iteracion de comprobaciones
			adc_to_dma_lastvalues[i]=adc_to_dma_values[i];

			uint8_t pose_ok=0;//flag de si ha terminado el movimineto
				switch(i){
				case 0:
					while(pose_ok==0){
						if(TIM2->CCR1<valor){
							TIM2->CCR1=TIM2->CCR1+1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else if(TIM2->CCR1>valor){
							TIM2->CCR1=TIM2->CCR1-1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else{
							pose_ok=1;
							break;
						}
					}
					break;
				case 1:
					while(pose_ok==0){
						if(TIM3->CCR1<valor){
							TIM3->CCR1=TIM3->CCR1+1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else if(TIM3->CCR1>valor){
							TIM3->CCR1=TIM3->CCR1-1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else{
							pose_ok=1;
							break;
						}
					}
					break;
				case 2:
					while(pose_ok==0){
						if(TIM4->CCR1<valor){
							TIM4->CCR1=TIM4->CCR1+1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else if(TIM4->CCR1>valor){
							TIM4->CCR1=TIM4->CCR1-1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else{
							pose_ok=1;
							break;
						}
					}
					break;
				case 3:
					while(pose_ok==0){
						if(TIM9->CCR1<valor){
							TIM9->CCR1=TIM9->CCR1+1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else if(TIM9->CCR1>valor){
							TIM9->CCR1=TIM9->CCR1-1;
							for(int time=0; time<DELAY_PASO_ADC; time++){}
						}else{
							pose_ok=1;
							break;
						}
					}
					break;
				default:
					//error
					break;
				}
			}

	}

//lcd recording mode
HAL_TIM_Base_Start(&htim7);
HAL_TIM_Base_Start_IT(&htim7);
}

	//memcpy(adc_to_dma_lastvalues,adc_to_dma_values, NUM_SERVOS*sizeof(uint32_t));

  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */


  /* USER CODE END TIM7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
