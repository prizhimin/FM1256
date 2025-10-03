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
	//	����������:
	//	255 - ��� �������
	//  0..9 - �����
	//	����� � ����� - ASCII-��� �������
	KEYPAD_PORT = KEYPAD_ROWA | KEYPAD_ROWB | KEYPAD_ROWC | KEYPAD_ROWD;
	if(!(KEYPAD_PIN & (KEYPAD_COL1 | KEYPAD_COL2 | KEYPAD_COL3 | KEYPAD_COL4)))		// ���� �� ���� ������� �� ������
		return 255;																	// �� ������� � ����� 255
	KEYPAD_PORT = KEYPAD_ROWA;			// 1� ������� - ����� 7, 8, 9, ������ A
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
	KEYPAD_PORT = KEYPAD_ROWB;			// 2� ������� - ����� 4, 5, 6, ������ B
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
	KEYPAD_PORT = KEYPAD_ROWC;			// 3� ������� - ����� 1, 2, 3, ������ C
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
	KEYPAD_PORT = KEYPAD_ROWD;			// 4� ������� - ������ *, ����� 0, ������ # � D
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