/*
 * UART_main.c
 *
 *  Created on: Sep 12, 2023
 *      Author: yosef
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "EasyCom_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "CLCD_interface.h"
#include "PWM_interface.h"

int main (void)
{
	u8 Data;
	u8 not;
//	u8 i=0;
	u8 *AZ_angle;
	u8 AZ__angle;
	u8 EL_angle=0;
	u8 Received_string[]="AZ:000.0,EL:-00.0";      //initial frame
	u8 chr_indx=0;
	//Rx pin is input pin
	DIO_voidSetPinDirection(DIO_u8PORTD, 0 ,DIO_u8INPUT);

	//Tx pin is output pin
	DIO_voidSetPinDirection(DIO_u8PORTD, 1 ,DIO_u8OUTPUT);

	//LCD data port
	DIO_voidSetPortDirection(DIO_u8PORTA , 0b11111111);

	//LCD control port
	DIO_voidSetPortDirection(DIO_u8PORTC , 0b00000111);

	//Servo PWM pin
	DIO_voidSetPinDirection(DIO_u8PORTD, 5 , DIO_u8OUTPUT);
	PWM_voidInit();
	Servo_voidSetAngle(0);


	CLCD_voidInit();
	CLCD_voidSendString("Welcome to UART Protocol");
	_delay_ms(1000);
	CLCD_voidClear();
	CLCD_voidSetXYPosition(0,0);
	UART_voidInit();

	//UART_voidSendData("Y");
	while(1)
	{
//		_delay_ms(500);
//		CLCD_voidClear();
		CLCD_voidSetXYPosition(0,0);

		for(chr_indx=0;Received_string[chr_indx]!='\0';chr_indx++)
		{
			Received_string[chr_indx]='\0';
		}

//		while (UART_u8RecieveData()=='\0')
//		{
//			asm("NOP");
//		}

		for(chr_indx=0;chr_indx<=17;chr_indx++)
		{
//			Received_string[0]=' ';
			Data=UART_u8RecieveData();
			if (Data!='\0')
			{
				Received_string[chr_indx]=Data;
			}
			else break;
		}
		CLCD_voidClear();

		CLCD_voidSendString("AZ= ");
		u8 Local_AzNegFlag=0;
		u8 n=0;     //for units - tens - Hundreds
		u8 Local_AZPtrIndx=0;
		u8 AZangle[] = "";
		u8 *Local_AZptr;
		Local_AZptr=AZangle;


		 for (u8 i = 0; Received_string[i]!= 'E'; i++)                       //looping on the whole frame
		 {

			 if (Received_string[i] -'A'==0  && Received_string[i+1] -'Z'==0 )
		     {



				 for (u8 j =  i+3; Received_string[j]!='.'; j++)
				 {
						DIO_voidSetPinDirection(DIO_u8PORTD, 3 ,DIO_u8OUTPUT);
						DIO_voidSetPinValue(DIO_u8PORTD, 3 ,1);
						_delay_ms(10);
						DIO_voidSetPinValue(DIO_u8PORTD, 3 ,0);

					 if (isdigit(Received_string[j]))     
					 {					

						 AZangle[Local_AZPtrIndx]=Received_string[j];

						 Local_AZPtrIndx++;

						 if (Received_string[j+1]=='.')
							 break;

					 }

				 }
				 		for (u8 i=0 ; Local_AZptr[i]!='\0' ; i++)
				 		{
				 			CLCD_voidSendData(Local_AZptr[i]);
				 		}

		     break;
		     }}




		 AZ__angle =atoi(Local_AZptr);


	 Servo_voidSetAngle(AZ__angle);

//		CLCD_voidSendString("AZ= ");
//		CLCD_voidSendString(Received_string);
//		AZ_angle=*Esy_Com_u16AZFilter(Received_string);    //AZ_angle array is not filled
//		CLCD_voidSendString("QUPT ");
//		for (u8 i=0 ; i<=2 ; i++)
//		{
//			CLCD_voidSendData(AZ_angle[i]);
//		}
		//CLCD_voidSendString(AZ_angle);
		//for(i=0; i<=2 ; i++){
		//CLCD_voidSendData(AZ_angle[i]);
		//}
		//CLCD_voidSendString("Yosef ");

//		CLCD_voidSendString(Received_string);
//		if (chr_indx==17)
//		{
//			CLCD_voidClear();
//			CLCD_voidSetXYPosition(0,0);
//			AZ_angle=Esy_Com_u16AZFilter(Received_string);
//			EL_angle=Esy_Com_u16ELFilter(Received_string);
//			CLCD_voidSetXYPosition(0,0);
//			CLCD_voidSendString("AZ=  ");
//			for(i=0; i<=2 ; i++){
//			CLCD_voidSendData(AZ_angle[i]);}
//			CLCD_voidSetXYPosition(0,1);
//			CLCD_voidSendString("EL=  ");
//			CLCD_voidSendData(EL_angle);
//			 Received_string[55]=NULL;
//		}


//		CLCD_voidSendData(Data);



}
}



