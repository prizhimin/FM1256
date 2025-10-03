/*
 * ht4480.h
 *
 *  Created on: 27 ���. 2014 �.
 *      Author: prinv
 *
 *  �� ������ ����� ���������� � http://www.shelezyakin.ru/?p=711
 */

#ifndef HT4480_H_
#define HT4480_H_


// ����������� ������� �������.

#define LCD_CLEAR 0x01	//

#define LCD_HOME			0x00000010
#define LCD_SHIFT			0b00000001	//
#define LCD_DEC				0b00000100
#define LCD_INC				0b00000110

#define LCD_ON				0b00001100	//	�������� �������
#define LCD_OFF				0b00001000	//	��������� �������
#define LCD_CURSOR_ON		0b00001101	//	�������� ������
#define LCD_CURSOR_OFF		0b00001100	//	��������� ������
#define LCD_BLINK_ON		0b00001111	//	�������� ������� �������
#define LCD_BLINK_OFF		0b00001110	//	��������� ������� �������

#define LCD_CURSOR_LEFT		0b00010000	//	������ �����
#define LCD_CURSOR_RIGHT	0b00010100	//	������ ������
#define LCD_DYSPLAY_LEFT	0b00011000	//	������� �����
#define LCD_DYSPLAY_RIGHT	0b00011100	//	������� ������

void LCD_Init();										// ������������� �������
void LCD_Clear();										// ������� ������ �������
void LCD_GoTo(char Row, char Col);						// ��������� ������� � �������� ����������
void LCD_PrintStr(char *Text);							// ������ ������
void LCD_PrintDec(long data);							// ������ ����������� �����
void LCD_SendByte(char, int);							// ������� ����� �� �������



#endif /* HT4480_H_ */
