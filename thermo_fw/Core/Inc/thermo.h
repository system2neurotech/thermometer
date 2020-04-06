/*******************************************************************************
  * thermo.h
  *
  *  Created on: Mar 26, 2020
  *      Author: samtm
  *  Copyright (c) System 2 Neurotechnology Inc.
  *   *
  * This software component is licensed by System 2 Neurotechnology Inc.
  * under BSD 3-Clause license, the "License"; You may not use this file
  * except in compliance with the License. You may obtain a copy of the
  * License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  *
  ******************************************************************************/

#ifndef INC_THERMO_H_
#define INC_THERMO_H_

void read_temp();

typedef enum
{
	THERMO_IDLE       = 0x00U,
	THERMO_READING    = 0x01U,
	THERMO_DONE  = 0x02U
} THERMO_StatusTypeDef;

THERMO_StatusTypeDef get_thermo_status(void);
void set_thermo_status(THERMO_StatusTypeDef status);
void reset_temp_measurements(void);
#endif /* INC_THERMO_H_ */


