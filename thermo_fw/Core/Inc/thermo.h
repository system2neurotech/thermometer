/*
 * thermo.h
 *
 *  Created on: Mar 26, 2020
 *      Author: samtm
 */

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


