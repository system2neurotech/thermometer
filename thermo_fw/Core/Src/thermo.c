/*******************************************************************************
  * thermo.c
  *
  *  Created on: Mar 26, 2020
  *      Author: samtm
  * Additional code Copyright (c) System 2 Neurotechnology Inc.
  *   *
  * This software component is licensed by System 2 Neurotechnology Inc.
  * under BSD 3-Clause license, the "License"; You may not use this file
  * except in compliance with the License. You may obtain a copy of the
  * License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  *
  ******************************************************************************/

#include "main.h"
#include "thermo.h"
#include "tmp117.h"

#define NO_OF_SAMPLES 8
#define MAX_TEMP_DIF 2	// maximum difference in 10ths of a deg C
static uint8_t temp_read_sequence = 0;
static uint16_t temp_measurements[NO_OF_SAMPLES];
THERMO_StatusTypeDef thermo_status = THERMO_IDLE;


uint16_t temp_max_diff()
{
    int max, min;
    max = min = temp_measurements[0];

    for (int i = 1; i < (NO_OF_SAMPLES); i++)
    {
      if (max < temp_measurements[i])
          max = temp_measurements[i];
      else if (min > temp_measurements[i])
          min = temp_measurements[i];
    }
    return max - min;
}

uint16_t temp_average()
{
	uint16_t temp_average = 0;
    for (int i = 0; i < (NO_OF_SAMPLES); i++)
    {
    	temp_average = temp_measurements[i] + temp_average;
    }
    return temp_average / NO_OF_SAMPLES;
}

THERMO_StatusTypeDef get_thermo_status(void)
{
	return thermo_status;
}

void set_thermo_status(THERMO_StatusTypeDef status)
{
	thermo_status = status;
}

void read_temp(){
	temp_measurements[temp_read_sequence] = tmp_read_temp();

	// increment the temp read sequence value and reset it if necessary
	temp_read_sequence++;
	if(temp_read_sequence >= NO_OF_SAMPLES) temp_read_sequence = 0;

	// check if the maximum difference is within spec
	if(temp_max_diff() < 5){
		// turn off flashing LEDs
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2) ;
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4) ;
    	HAL_TIM_Base_Stop(&htim16);
		// buzz to indicated done
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) ;
		HAL_Delay(500);
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1) ;
		HAL_Delay(200);


		volatile uint16_t temperature = temp_average();
		if(temperature < 370){
			// set LED green
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2) ;
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3) ;
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4) ;
		}
		else if(temperature > 380)
		{
			// set LED red
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) ;
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2) ;
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3) ;
		}
		else{
			// set LED orange
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2) ;
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4) ;
		}


		// turn off the timer
		HAL_TIM_Base_Stop(&htim17);
		set_thermo_status(THERMO_DONE);
	}

}

void reset_temp_measurements(void){
	for(int i = 0; i < NO_OF_SAMPLES; i++)
	temp_measurements[i] = 0;
}
