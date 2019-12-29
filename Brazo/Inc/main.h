/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define MAX_POSES 250 //waring: MAX 2^16 POSES;
#define NUM_SERVOS 4
#define THRESHOLD_POT 50
#define PASOS 20
#define DELAY_PASO_ADC 600
#define PLAYING_DELAY 500
//----------UART----------
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif
//---------END_UART----------

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
 uint16_t servo1[MAX_POSES];
 uint16_t servo2[MAX_POSES];
 uint16_t servo3[MAX_POSES];
 uint16_t servo4[MAX_POSES];
 } posiciones_t;

 posiciones_t posiciones;


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTM_SAVE_POSE_Pin GPIO_PIN_13
#define BTM_SAVE_POSE_GPIO_Port GPIOC
#define BTM_SAVE_POSE_EXTI_IRQn EXTI15_10_IRQn
#define BTN_RESET_POSITIONS_Pin GPIO_PIN_0
#define BTN_RESET_POSITIONS_GPIO_Port GPIOC
#define BTN_RESET_POSITIONS_EXTI_IRQn EXTI0_IRQn
#define BTM_PLAY_POSES_Pin GPIO_PIN_1
#define BTM_PLAY_POSES_GPIO_Port GPIOC
#define BTM_PLAY_POSES_EXTI_IRQn EXTI1_IRQn
#define BTM_STOP_POSES_Pin GPIO_PIN_2
#define BTM_STOP_POSES_GPIO_Port GPIOC
#define BTM_STOP_POSES_EXTI_IRQn EXTI2_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SERVO2_Pin GPIO_PIN_6
#define SERVO2_GPIO_Port GPIOA
#define SERVO4_Pin GPIO_PIN_13
#define SERVO4_GPIO_Port GPIOB
#define BTM_LASER_LED_Pin GPIO_PIN_7
#define BTM_LASER_LED_GPIO_Port GPIOC
#define BTM_LASER_LED_EXTI_IRQn EXTI9_5_IRQn
#define LASER_LED_Pin GPIO_PIN_9
#define LASER_LED_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SERVO1_Pin GPIO_PIN_15
#define SERVO1_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SERVO3_Pin GPIO_PIN_6
#define SERVO3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
