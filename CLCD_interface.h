/*
 * CLCD_interface.h
 *
 *  Created on: Aug 16, 2023
 *      Author: yosef
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidInit(void);
void CLCD_voidSendString(u8 *Copy_pu8String);
void CLCD_voidSetXYPosition(u8 Copy_u8XPos, u8 Copy_u8Ypos);
void CLCD_voidClear(void);

#endif /* CLCD_INTERFACE_H_ */
