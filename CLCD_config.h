/*
 * CLCD_config.h
 *
 *  Created on: Aug 16, 2023
 *      Author: yosef
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/*options:
 * 1. DIO_u8PORTA
 * 2. DIO_u8PORTB
 * 3. DIO_u8PORTC
 * 4. DIO_u8PORTD
 */
#define CLCD_DATAPORT    DIO_u8PORTA      //dev. can replace PORTA with any other port according to the app

#define CLCD_CNTRLPORT   DIO_u8PORTC

#define CLCD_Rs_Pin         0
#define CLCD_RW_Pin         1
#define CLCD_E_Pin          2

#endif /* CLCD_CONFIG_H_ */
