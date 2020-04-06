/*
 * lcd.c
 *
 *  Created on: Mar 26, 2020
 *      Author: samtm
 */

#include "main.h"
#include "lcd.h"

char bcd_temp[4] = {0};
uint16_t segments[4] = {0};
uint8_t fahrenheit = 0;
uint8_t LCD_seq = 0;


/* Standard iterative function to convert 16-bit integer to BCD */
uint32_t dec2bcd(uint16_t dec)
{
    uint32_t result = 0;
    int shift = 0;

    while (dec)
    {
        result +=  (dec % 10) << shift;
        dec = dec / 10;
        shift += 4;
    }
    return result;
}



void LCD_set_null()
{
	bcd_temp[0] = 1;
	bcd_temp[1] = 2;
	bcd_temp[2] = 3;
	bcd_temp[3] = 4;
}

void LCD_decode_digits()
{
	bcd_temp[0];
	uint16_t com_seg0, com_seg1 , com_seg2, com_seg3;
	segments[0] = 0;
	segments[1] = 0;
	segments[2] = 0;
	segments[3] = 0;
	for(uint8_t i = 0; i < 3; i++)
	{
		switch(bcd_temp[i])
		{
			case 0:
				com_seg0 = LCD1_Pin;
				com_seg1 = LCD1_Pin | LCD2_Pin;
				com_seg2 = LCD2_Pin;
				com_seg3 = LCD1_Pin | LCD2_Pin;
				break;
			case 1:
				com_seg0 = 0;
				com_seg1 = LCD2_Pin;
				com_seg2 = LCD2_Pin;
				com_seg3 = 0;
				break;
			case 2:
				com_seg0 = LCD1_Pin;
				com_seg1 = LCD1_Pin;
				com_seg2 = LCD1_Pin | LCD2_Pin;
				com_seg3 = LCD2_Pin;
				break;
			case 3:
				com_seg0 = LCD1_Pin;
				com_seg1 = LCD2_Pin;
				com_seg2 = LCD1_Pin | LCD2_Pin;
				com_seg3 = LCD2_Pin;
				break;
			case 4:
				com_seg0 = 0;
				com_seg1 = LCD2_Pin;
				com_seg2 = LCD1_Pin | LCD1_Pin;
				com_seg3 = LCD1_Pin;
				break;
			case 5:
				com_seg0 = LCD1_Pin;
				com_seg1 = LCD2_Pin;
				com_seg2 = LCD1_Pin;
				com_seg3 = LCD1_Pin | LCD2_Pin;
				break;
			case 6:
				com_seg0 = LCD1_Pin;
				com_seg1 = LCD1_Pin | LCD2_Pin;
				com_seg2 = LCD1_Pin;
				com_seg3 = LCD1_Pin | LCD2_Pin;
				break;
			case 7:
				com_seg0 = 0;
				com_seg1 = LCD2_Pin;
				com_seg2 = LCD2_Pin;
				com_seg3 = LCD2_Pin;
				break;
			case 8:
				com_seg0 = LCD1_Pin;
				com_seg1 = LCD1_Pin | LCD2_Pin;
				com_seg2 = LCD1_Pin | LCD2_Pin;
				com_seg3 = LCD1_Pin | LCD2_Pin;
				break;
			case 9:
				com_seg0 = LCD1_Pin;
				com_seg1 = LCD2_Pin;
				com_seg2 = LCD1_Pin | LCD2_Pin;
				com_seg3 = LCD1_Pin | LCD2_Pin;
				break;
		}
		segments[0] = segments[0] + (com_seg0 << (i*2));
		segments[1] = segments[1] + (com_seg1 << (i*2));
		segments[2] = segments[2] + (com_seg2 << (i*2));
		segments[3] = segments[3] + (com_seg3 << (i*2));
	}
	if(fahrenheit){
		segments[0] = segments[0] + LCD4_Pin;
		segments[1] = segments[1] + LCD7_Pin;
		segments[2] = segments[2] + LCD7_Pin;
		segments[3] = segments[3] + LCD7_Pin + LCD8_Pin;
	}
	else{
		segments[0] = segments[0] + LCD4_Pin + LCD7_Pin;
		segments[1] = segments[1] + LCD7_Pin;
		segments[2] = segments[2] + LCD7_Pin;
	}

}

void LCD_set_temp(uint16_t temp)
{

	// convert raw temp to deg
	uint16_t temp_deg = temp;

	if(fahrenheit){
		temp_deg = temp_deg * 1.8 + 32;// convert to fahrenheit
		bcd_temp[0] = (char)(temp_deg / 1000);
		bcd_temp[1] = (char)((temp_deg - (bcd_temp[0]*1000))/100);
		bcd_temp[2] = (char)((temp_deg  - (bcd_temp[1]*100) - (bcd_temp[0]*1000))/ 10);
		//bcd_temp[3] = (char)(temp_deg - (bcd_temp[2]*10) - (bcd_temp[1]*100) - (bcd_temp[0]*1000));
	}
	else{
		bcd_temp[0] = (char)((temp_deg - (bcd_temp[0]*1000))/100);
		bcd_temp[1] = (char)((temp_deg  - (bcd_temp[1]*100) - (bcd_temp[0]*1000))/ 10);
		bcd_temp[2] = (char)(temp_deg - (bcd_temp[2]*10) - (bcd_temp[1]*100) - (bcd_temp[0]*1000));
	}

	LCD_decode_digits();


}

void LCD_set_fahrenheit(uint8_t value){
	fahrenheit = value;
}


uint8_t LCD_get_fahrenheit(void){
	return fahrenheit;
}




void LCD_run()
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	uint8_t COM_pin;

	uint8_t LCD_phase = LCD_seq / 2;
	if(LCD_phase == 0)
		COM_pin = COM0_Pin;
	else if(LCD_phase == 1)
		COM_pin = COM1_Pin;
	else if(LCD_phase == 2)
		COM_pin = COM2_Pin;
	else if(LCD_phase == 3)
		COM_pin = COM3_Pin;

	if(LCD_seq % 2)
	{

		// switch COM high and the applicable pins low.
		//segments[0] = 0x0550;
		//segments[1] = 0x0230;
		//segments[2] = 0x0AA0;
		//segments[3] = 0x0740;

	//	HAL_GPIO_WritePin(GPIOA, COM_pin + 0x0FF0 - segments[LCD_seq], GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(GPIOA, segments[LCD_seq], GPIO_PIN_SET);



		GPIO_InitStruct.Pin = LCD1_Pin|LCD2_Pin|LCD3_Pin|LCD4_Pin
								|LCD5_Pin|LCD6_Pin|LCD7_Pin|LCD8_Pin;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		HAL_GPIO_WritePin(GPIOA, COM_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, segments[LCD_phase], GPIO_PIN_SET);

		//GPIO_InitStruct.Pin =  COM_pin|LCD1_Pin|LCD2_Pin|LCD3_Pin|LCD4_Pin
		//        |LCD5_Pin|LCD6_Pin|LCD7_Pin|LCD8_Pin;
		GPIO_InitStruct.Pin =  COM_pin | segments[LCD_phase];
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin =  0x000F - COM_pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	}
	else
	{


		GPIO_InitStruct.Pin = LCD1_Pin|LCD2_Pin|LCD3_Pin|LCD4_Pin
								|LCD5_Pin|LCD6_Pin|LCD7_Pin|LCD8_Pin;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		// switch COM low and the applicable pins high.
		HAL_GPIO_WritePin(GPIOA, COM_pin , GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, segments[LCD_phase], GPIO_PIN_RESET);

		GPIO_InitStruct.Pin =  COM_pin | segments[LCD_phase];
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin =  0x000F - COM_pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		// delay 2ms
	}


	LCD_seq++;
	if(LCD_seq >= 8)
		LCD_seq = 0;
}
