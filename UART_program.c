/*
 * UART_program.c
 *
 *  Created on: Sep 12, 2023
 *      Author: yosef
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_registers.h"


void UART_voidInit(void)
{
	//Because UCSRC is special it must be filled in one CLK cycle so we make a local variable an equaling it to the reg.
	u8 Local_UCSRC=0b10000110;

	//disable double speed
	CLR_BIT(UCSRA,1);

	//Select char size (8bits)
	CLR_BIT(UCSRB,2);

	//Register Select
	SET_BIT(Local_UCSRC,7);

	//Asynchronous mode
	CLR_BIT(Local_UCSRC,6);

	//No Parity
	CLR_BIT(Local_UCSRC,5);
	CLR_BIT(Local_UCSRC,4);

	//1 Stop bit
	CLR_BIT(Local_UCSRC,3);

	//Assign value to the register
	UCSRC=Local_UCSRC;

	//Set the Baud rate to 9600
	UBRRL=51;

	/*Enables are preferable at the end of the function*/

	//Enable Rx
	SET_BIT(UCSRB , 4);

	//Enable Tx
	SET_BIT(UCSRB , 3);

}
void UART_voidSendData(u8 Copy_u8Data)
{
	//Wait until the register is Empty
	while((GET_BIT(UCSRA , 5)!=1))
	{
		asm("NOP");
	}
	//Send the data
	UDR=Copy_u8Data;

}
u8   UART_u8RecieveData(void)
{
	//Wait until receiving the data
	while((GET_BIT(UCSRA , 7)!=1))
		{
			asm("NOP");
		}

	//Read the DATA
	return UDR;
}
