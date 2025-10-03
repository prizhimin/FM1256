/*
 * ht4480.h
 *
 *  Created on: 27 окт. 2014 г.
 *      Author: prinv
 *
 *  За основу взята библиотека с http://www.shelezyakin.ru/?p=711
 */

#ifndef HT4480_H_
#define HT4480_H_


// Управляющие символы дисплея.

#define LCD_CLEAR 0x01	//

#define LCD_HOME			0x00000010
#define LCD_SHIFT			0b00000001	//
#define LCD_DEC				0b00000100
#define LCD_INC				0b00000110

#define LCD_ON				0b00001100	//	Включить дисплей
#define LCD_OFF				0b00001000	//	Выключить дисплей
#define LCD_CURSOR_ON		0b00001101	//	Включить курсор
#define LCD_CURSOR_OFF		0b00001100	//	Выключить курсор
#define LCD_BLINK_ON		0b00001111	//	Включить мигание курсора
#define LCD_BLINK_OFF		0b00001110	//	Выключить мигание курсора

#define LCD_CURSOR_LEFT		0b00010000	//	Курсор влево
#define LCD_CURSOR_RIGHT	0b00010100	//	Курсор вправо
#define LCD_DYSPLAY_LEFT	0b00011000	//	Дисплей влево
#define LCD_DYSPLAY_RIGHT	0b00011100	//	Дисплей вправо

void LCD_Init();										// Инициализация дисплея
void LCD_Clear();										// Очистка экрана дисплея
void LCD_GoTo(char Row, char Col);						// Установка курсора в заданные координаты
void LCD_PrintStr(char *Text);							// Печать строки
void LCD_PrintDec(long data);							// Печать десятичного числа
void LCD_SendByte(char, int);							// Посылка байта на дисплей



#endif /* HT4480_H_ */
