/*
 * hardware.h
 *
 *      Author: prinv
 */

#include <avr/io.h>

#ifndef HARDWARE_H_
#define HARDWARE_H_

#define     FALSE	0
#define     TRUE	1

#define		BIT0	1
#define		BIT1	2
#define		BIT2	4
#define		BIT3	8
#define		BIT4	16
#define		BIT5	32
#define		BIT6	64
#define		BIT7	128

/*
 * LCD дисплей подключен к PORTD
 */

#define	LCD_DIR DDRD
#define	LCD_OUT PORTD

/*
 * Описание подключения контактов дисплея к МК
 */

#define	LCD_RS		BIT0
#define	LCD_EN		BIT1
#define	LCD_D7		BIT7
#define	LCD_D6		BIT6
#define	LCD_D5		BIT5
#define	LCD_D4		BIT4

#define LCD_MASK	(LCD_RS | LCD_EN | LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4)


/*
 *	Подключение светодиодов 
 */

#define LED_PORT	PORTC
#define LED_DDR		DDRC
#define LED_GREEN	BIT2
#define LED_RED		BIT1

/*	
 *	Подключение клавиатуры 4*4
 */

// Используется порт B (все 8 линий)

#define KEYPAD_PIN	PINB
#define KEYPAD_PORT	PORTB
#define KEYPAD_DDR	DDRB

#define	KEYPAD_ROWA	BIT0
#define KEYPAD_ROWB	BIT1
#define KEYPAD_ROWC	BIT2
#define KEYPAD_ROWD	BIT3
#define KEYPAD_COL1	BIT4
#define KEYPAD_COL2 BIT5
#define KEYPAD_COL3	BIT6
#define KEYPAD_COL4 BIT7

#endif /* HARDWARE_H_ */
