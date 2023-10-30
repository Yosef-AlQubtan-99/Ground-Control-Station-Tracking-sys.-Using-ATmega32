/*
 * Servo_program.c
 *
 *  Created on: Sep 6, 2023
 *      Author: yosef
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "PWM_interface.h"
#include "Servo_config.h"
#include "Servo_interface.h"
#include "Servo_private.h"

void Servo_voidSetAngle(u8 Copy_Angle)
{
	u16 Time=(Copy_Angle*10.5)+600;
	PWM_voidSetTopValue(20000);
	PWM_voidSetOCRValue(Time);
	_delay_ms(200);
}
