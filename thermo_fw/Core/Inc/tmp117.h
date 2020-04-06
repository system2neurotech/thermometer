/*******************************************************************************
  * tmp117.h
  *
  *  Created on: Mar 25, 2020
  *      Author: samtm
  * Copyright (c) System 2 Neurotechnology Inc.
  *   *
  * This software component is licensed by System 2 Neurotechnology Inc.
  * under BSD 3-Clause license, the "License"; You may not use this file
  * except in compliance with the License. You may obtain a copy of the
  * License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  *
  ******************************************************************************/


#ifndef INC_TMP117_H_
#define INC_TMP117_H_

// register addresses

#define REG_Temp_Result 	0x00
#define REG_Configuration 	0x01
#define REG_THigh_Limit 	0x02
#define REG_TLow_Limit	 	0x03
#define REG_EEPROM_UL	 	0x04
#define REG_EEPROM1		 	0x05
#define REG_EEPROM2		 	0x06
#define REG_Temp_Offset 	0x07
#define REG_EEPROM3		 	0x08
#define REG_Device_ID	 	0x0F


// Configuration register
#define HIGH_Alert			0x8000
#define LOW_Alert			0x4000
#define Data_Ready			0x2000
#define EEPROM_Busy			0x1000
#define MOD_Continuous		0x0000
#define MOD_Shutdown		0x0400
#define MOD_One_Shot		0x0200
#define CONV_TIME_125_AVG_8	0x0020
#define Therm_Mode			0x0010
#define Alert_Mode			0x0000
#define Alert_Pin_POL_H		0x0008
#define Alert_Pin_POL_L		0x0000
#define Alert_Pin_DR		0x0004
#define Alert_Pin_Alert		0x0000
#define Soft_Reset			0x0002

#define Device_ID_tmp117	0x0117




uint16_t tmp_read_temp();
HAL_StatusTypeDef tmp_init(void);
HAL_StatusTypeDef tmp_powerdown(void);
HAL_StatusTypeDef tmp_powerup(void);







#endif /* INC_TMP117_H_ */
