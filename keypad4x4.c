/*
 * keypad4x4.c
 *
 * Created: 25.02.2016 10:25:03
 *  Author: prizhimin_nv
 */ 

#include "hardware.h"

void KeyPad_Init()
{
	KEYPAD_DDR |= (KEYPAD_ROWA | KEYPAD_ROWB | KEYPAD_ROWC | KEYPAD_ROWD);
	KEYPAD_PORT = 0;
}

unsigned char KeyPad_Scan()
{
	//	Возвращает:
	//	255 - нет нажатия
	//  0..9 - цифры
	//	знаки и буквы - ASCII-код символа
	KEYPAD_PORT = KEYPAD_ROWA | KEYPAD_ROWB | KEYPAD_ROWC | KEYPAD_ROWD;
	if(!(KEYPAD_PIN & (KEYPAD_COL1 | KEYPAD_COL2 | KEYPAD_COL3 | KEYPAD_COL4)))		// Если ни одна клавиша не нажата
		return 255;																	// то выходим с кодом 255
	KEYPAD_PORT = KEYPAD_ROWA;			// 1я строчка - цифры 7, 8, 9, кнопка A
	switch(KEYPAD_PIN & (KEYPAD_COL1 | KEYPAD_COL2 | KEYPAD_COL3 | KEYPAD_COL4))
	{
		case KEYPAD_COL1:
			return 7;
		case KEYPAD_COL2:
			return 8;
		case KEYPAD_COL3:
			return 9;		
		case KEYPAD_COL4:
			return 'A';
	}
	KEYPAD_PORT = KEYPAD_ROWB;			// 2я строчка - цифры 4, 5, 6, кнопка B
	switch(KEYPAD_PIN & (KEYPAD_COL1 | KEYPAD_COL2 | KEYPAD_COL3 | KEYPAD_COL4))
	{
		case KEYPAD_COL1:
			return 4;
		case KEYPAD_COL2:
			return 5;
		case KEYPAD_COL3:
			return 6;
		case KEYPAD_COL4:
			return 'B';
	}
	KEYPAD_PORT = KEYPAD_ROWC;			// 3я строчка - цифры 1, 2, 3, кнопка C
	switch(KEYPAD_PIN & (KEYPAD_COL1 | KEYPAD_COL2 | KEYPAD_COL3 | KEYPAD_COL4))
	{
		case KEYPAD_COL1:
			return 1;
		case KEYPAD_COL2:
			return 2;
		case KEYPAD_COL3:
			return 3;
		case KEYPAD_COL4:
			return 'C';
	}
	KEYPAD_PORT = KEYPAD_ROWD;			// 4я строчка - кнопка *, цифра 0, кнопки # и D
	switch(KEYPAD_PIN & (KEYPAD_COL1 | KEYPAD_COL2 | KEYPAD_COL3 | KEYPAD_COL4))
	{
		case KEYPAD_COL1:
			return '*';
		case KEYPAD_COL2:
			return 0;
		case KEYPAD_COL3:
			return '#';
		case KEYPAD_COL4:
			return 'D';
	}
	KEYPAD_PORT = 0;
	return 255;
}