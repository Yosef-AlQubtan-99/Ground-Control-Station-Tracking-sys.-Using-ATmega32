/*
 * CLCD_program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: yosef
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include <avr/delay.h>

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"



void CLCD_voidSendData(u8 Copy_u8Data){

	/* Set Rs to 1 for data */
	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_Rs_Pin , DIO_u8HIGH);
	/* Set R/W' to 0 for write */
	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_RW_Pin , DIO_u8LOW);

	DIO_voidSetPortValue(CLCD_DATAPORT , Copy_u8Data);         //put the data first on portA then enable LCD to read

	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_E_Pin , DIO_u8HIGH);       //E=1
	_delay_ms(2);
	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_E_Pin , DIO_u8LOW);        //E=0

}
void CLCD_voidSendCommand(u8 Copy_u8Command){

	/* Set Rs to 0 for command */
	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_Rs_Pin , DIO_u8LOW);
	/* Set R/W to 0 for write */
	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_RW_Pin , DIO_u8LOW);

	DIO_voidSetPortValue(CLCD_DATAPORT , Copy_u8Command);         //put the data first on portA then enable LCD to read

	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_E_Pin , DIO_u8HIGH);       //E=1
	_delay_ms(2);
	DIO_voidSetPinValue(CLCD_CNTRLPORT , CLCD_E_Pin , DIO_u8LOW);        //E=0

}
void CLCD_voidInit(void){

	_delay_ms(35);
	CLCD_voidSendCommand(0b00111000);    //function set
	CLCD_voidSendCommand(0b00001100);    //Display ON
	CLCD_voidSendCommand(0b00000001);	 //Display clear
}

void CLCD_voidSendString(u8 *Copy_pu8String){
	u8 Local_u8Iterator=0;
	while((Copy_pu8String[Local_u8Iterator])!='\0'){
		CLCD_voidSendData(Copy_pu8String[Local_u8Iterator]);
		Local_u8Iterator++;

		if (Local_u8Iterator%16==0)
		{
			CLCD_voidSetXYPosition(0,1);
		}
		if (Local_u8Iterator%32==0)
		{
			CLCD_voidSetXYPosition(0,0);
		}
	}
}
void CLCD_voidSetXYPosition(u8 Copy_u8XPos, u8 Copy_u8Ypos){
	u8 Local_u8Address;
	if (Copy_u8Ypos==0){
		Local_u8Address=Copy_u8XPos;
	}
	else{
		Local_u8Address=Copy_u8XPos + 0x40;
	}
	SET_BIT(Local_u8Address,7);                                     //??
	CLCD_voidSendCommand(Local_u8Address);
}
void CLCD_voidClear(void){

	CLCD_voidSendCommand(0b00000001);	 //Display clear
}
