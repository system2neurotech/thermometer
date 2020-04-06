/*
 * tmp117.c
 *
 *  Created on: Mar 25, 2020
 *      Author: samtm
 */

#include "main.h"
#include "tmp117.h"

#define TEMP_TIMEOUT 375
#define I2C_ADDRESS        0x92
#define RXBUFFERSIZE 2  // expects 8 bit registers, so a single 16bit register is 2 8 bit
#define TXBUFFERSIZE 3
/* Buffer used for transmission */
uint8_t aTxBuffer[3];
/* Buffer used for reception */
uint8_t aRxBuffer[2];


HAL_StatusTypeDef tmp_write_register(uint8_t register_addr, uint16_t data)
{
	aTxBuffer[0] = register_addr;
	aTxBuffer[1] = (uint8_t) (data && 0xFF) >> 8;
	aTxBuffer[1] = (uint8_t) data && 0x00FF;


	while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t*)aTxBuffer, TXBUFFERSIZE, 1000)!= HAL_OK)
	{
	  /* Error_Handler() function is called when Timeout error occurs.
	     When Acknowledge failure occurs (Slave don't acknowledge its address)
	     Master restarts communication */
		if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
		{
	      Error_Handler();
	    }
	}

}

uint16_t tmp_read_register(uint8_t register_addr)
{
	aTxBuffer[0] = register_addr;

	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t*)aTxBuffer, 1, 1000);


	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)aRxBuffer, RXBUFFERSIZE, 1000) != HAL_OK)
	{
	  /* Error_Handler() function is called when Timeout error occurs.
	     When Acknowledge failure occurs (Slave don't acknowledge it's address)
	     Master restarts communication */
	  if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
	  {
	    Error_Handler();
	  }
	}

	return (uint16_t)(aRxBuffer[1] + (aRxBuffer[0] << 8));

}

HAL_StatusTypeDef tmp_write_eeprom_register(uint8_t register_addr, uint16_t data)
{

}



HAL_StatusTypeDef tmp_init(void){
	uint16_t volatile data_register;

	// turn on power
	HAL_GPIO_WritePin(VTEMP_GPIO_Port, VTEMP_Pin, GPIO_PIN_SET);

	HAL_Delay(10);

	// read device ID
	data_register = tmp_read_register(REG_Device_ID);

	if((data_register & 0x0FFF) != Device_ID_tmp117)
		return HAL_ERROR;

	return HAL_OK;

}


HAL_StatusTypeDef tmp_powerup(void){
	uint16_t volatile data_register;

	// turn on power
	HAL_GPIO_WritePin(VTEMP_GPIO_Port, VTEMP_Pin, GPIO_PIN_SET);

	return HAL_OK;

}


HAL_StatusTypeDef tmp_powerdown(void){
	uint16_t volatile data_register;

	// turn on power
	HAL_GPIO_WritePin(VTEMP_GPIO_Port, VTEMP_Pin, GPIO_PIN_RESET);

	return HAL_OK;

}




uint16_t convert_raw_temperature(uint16_t raw_temp)
{
	return raw_temp / 12.801;
}

uint16_t tmp_read_temp()
{
	// turn on temp sensor and and take single measurement
	// 8 sample average, 125ms conversion time
	tmp_write_register(REG_Configuration, CONV_TIME_125_AVG_8 |
		Therm_Mode | MOD_One_Shot);
	// wait 125ms then loop and read.
	HAL_Delay(125);

	// get current time for
	uint32_t timeout_start = HAL_GetTick();


	while(!(tmp_read_register(REG_Configuration) & Data_Ready))
	{
		// wait 25ms
		HAL_Delay(25);
		// check timeout
		if((timeout_start + TEMP_TIMEOUT) < HAL_GetTick())
			break;
	}



	return convert_raw_temperature(tmp_read_register(REG_Temp_Result));
}


