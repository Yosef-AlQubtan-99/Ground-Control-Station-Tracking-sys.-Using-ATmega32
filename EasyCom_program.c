/*
 * EasyCom_program.c
 *
 *  Created on: Sep 15, 2023
 *      Author: yosef
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "DIO_interface.h"



u8 *Esy_Com_u16AZFilter(u8 *Copy_ReceivedString)    //ChrData is the received chr from UART
                                                                     //ChrData=UART_u8RecieveData()
{
	u16 Local_AzAngle=0;
			u8 Local_AzNegFlag=0;
			u8 n=0;     //for units - tens - Hundreds
			u8 Local_AZPtrIndx=0;
			u8 AZangle[] = "";
			u8 *Local_AZptr;
			Local_AZptr=AZangle;


			 for (u8 i = 0; Copy_ReceivedString[i]!= 'E'; i++)                       //looping on the whole frame
			 {

				 if (Copy_ReceivedString[i] =='Z')
			     {



					 for (u8 j =  i+1; Copy_ReceivedString[j]!='.'; j++)
					 {
							DIO_voidSetPinDirection(DIO_u8PORTD, 3 ,DIO_u8OUTPUT);
							DIO_voidSetPinValue(DIO_u8PORTD, 3 ,1);
							_delay_ms(10);
							DIO_voidSetPinValue(DIO_u8PORTD, 3 ,0);

						 if (isdigit(Copy_ReceivedString[j]))     //ERROR when using isdigit() and
						 {														 //comparing Ascii codes

							 AZangle[Local_AZPtrIndx]=Copy_ReceivedString[j];

							 Local_AZPtrIndx++;
							 if (Copy_ReceivedString[j+1]=='.')
								 break;

						 }

					 }


			     break;
			     }}
//					 for(u8 i =2 ; i>=0;i--)
//					 {

//						 Local_AzAngle+=(Local_AZptr[i] - '0')*10^n;

//						 n++;     			//switching from units to tens and from tens to hundreds
//					 }
//					 if (Local_AzNegFlag==1)
//					 {
//						 Local_AzAngle *= -1;
//					 }
//	n=0;

	return Local_AZptr;            //the problem is here
}

u16 Esy_Com_u16ELFilter(u8 Copy_ReceivedString[])    //ChrData is the received chr from UART
                                                                     //ChrData=UART_u8RecieveData()
{
	u16 Local_ELAngle=0;
	u8 Local_ELNegFlag=0;
	u8 n=0;     //for units - tens - Hundreds
	u8 Local_ELPtrIndx=2;
	u8 ELangle[3];
	u8 *Local_ELptr;
	Local_ELptr=ELangle;


				 for (u8 i = 0; i <= sizeof(Copy_ReceivedString); i++)                       //looping on the whole frame
				 {

					 if ((Copy_ReceivedString[i]  == 'E')&&(Copy_ReceivedString[i+1] == 'L'))
				     {

						 for (u8 j =  i+3; j <= sizeof(Copy_ReceivedString); j++)   //i+3 when using split AZ&EL
						 {

							 if (isdigit(Copy_ReceivedString[j]))
							 {
								 Local_ELptr[Local_ELPtrIndx]=Copy_ReceivedString[j];
								 Local_ELPtrIndx--;

							 }
							 else if (Copy_ReceivedString[j]== '-')
							 {
								 Local_ELNegFlag=1;
							 }
							 else                          //checked element is not '-' nor a number -> exit the loop
								 break;
						 }
					  }
					 for(u8 i =2 ; i>=0;i--)
					 {
						 Local_ELAngle+=(Local_ELptr[i] - '0')*10^n;

						 n++;     			//switching from units to tens and from tens to hundreds
					 }
					 if (Local_ELNegFlag==1)
					 {
						 Local_ELAngle *= -1;
					 }
				 }
	n=0;
	return Local_ELAngle;
}

