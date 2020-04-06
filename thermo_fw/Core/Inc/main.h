/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define COM0_Pin GPIO_PIN_0
#define COM0_GPIO_Port GPIOA
#define COM1_Pin GPIO_PIN_1
#define COM1_GPIO_Port GPIOA
#define COM2_Pin GPIO_PIN_2
#define COM2_GPIO_Port GPIOA
#define COM3_Pin GPIO_PIN_3
#define COM3_GPIO_Port GPIOA
#define LCD1_Pin GPIO_PIN_4
#define LCD1_GPIO_Port GPIOA
#define LCD2_Pin GPIO_PIN_5
#define LCD2_GPIO_Port GPIOA
#define LCD3_Pin GPIO_PIN_6
#define LCD3_GPIO_Port GPIOA
#define LCD4_Pin GPIO_PIN_7
#define LCD4_GPIO_Port GPIOA
#define BUTTON_Pin GPIO_PIN_0
#define BUTTON_GPIO_Port GPIOB
#define VLCD_Pin GPIO_PIN_1
#define VLCD_GPIO_Port GPIOB
#define LCD5_Pin GPIO_PIN_8
#define LCD5_GPIO_Port GPIOA
#define LCD6_Pin GPIO_PIN_9
#define LCD6_GPIO_Port GPIOA
#define LCD7_Pin GPIO_PIN_10
#define LCD7_GPIO_Port GPIOA
#define LCD8_Pin GPIO_PIN_11
#define LCD8_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define BUZZ_Pin GPIO_PIN_15
#define BUZZ_GPIO_Port GPIOA
#define VTEMP_Pin GPIO_PIN_4
#define VTEMP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
