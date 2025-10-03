#define F_CPU 8000000UL

#include <util/delay.h>
#include "hardware.h"

#define LENLONG 12	// максимальное количество (включая знак -) десятичных цифр в переменной типа long

void LCD_PulseEN();
void LCD_SendByte(char, int);
void LCD_Send4bits(unsigned char);


void LCD_GoTo(char Row, char Col)    					// Установка курсора в заданные координаты
{
    char address;
	switch(Row)
	{
		case 0:	address = 0;
				break;
		case 1:	address = 0x40;
				break;
		case 2:	address = 0x14;
				break;
		case 3:	address = 0x54;
				break;
		default:address = 0;
	}
    address |= Col;//     Col - zero based col number
    LCD_SendByte(0x80 | address, FALSE);
}

// Clear the screen data and return the
// cursor to home position

void LCD_Clear()										// Очистка экрана дисплея
{
    LCD_SendByte(0x01, FALSE);
    LCD_SendByte(0x02, FALSE);
	_delay_ms(2);
}

void LCD_Init(void)										// Инициализация дисплея (16*2, 5*7, Display on, cursor off, blink cursor off)
{
    LCD_DIR |= LCD_MASK;    							
	_delay_ms(15);
    LCD_Send4bits(3);
    LCD_PulseEN();
    _delay_ms(5);
    LCD_Send4bits(3);
    LCD_PulseEN();
	_delay_us(150);
    LCD_Send4bits(3);
    LCD_PulseEN();
	LCD_Send4bits(2);
    LCD_PulseEN();
    LCD_SendByte(0x28, FALSE);
    LCD_SendByte(0x0C, FALSE);
    LCD_SendByte(0x06, FALSE);
}

void LCD_PrintStr(unsigned char *Text)							// Печать строки
{
    unsigned char *c;

    c = Text;

    while ((c != 0) && (*c != 0))
    {
        LCD_SendByte(*c, TRUE);
        c++;
    }
}

void LCD_PrintDec(long data){	// Печать десятичного числа

	unsigned char s[LENLONG],	// Массив символов для вывода
	sign=0,						// Флаг знака выводимого числа
	i=LENLONG-1;				// Индекс, указывает на последний элемент массива
	long tmp_data;				// Временная переменая для хранения выводимого числа
	
	tmp_data=data;

	if(data<0){
		sign='-';
		tmp_data=-tmp_data;
	}
	
	do
	{
		s[i--]=tmp_data % 10 + '0';			// Заполняем с конца массив выводимых символов
		tmp_data /= 10;
	} while (tmp_data>0);
	
	if(sign)
		s[i]=sign;
	else
		i++;
	do
		LCD_SendByte(s[i++], TRUE);			// Выводим символ на экран
	while (i<LENLONG);
}

void LCD_PulseEN()
{
    LCD_OUT &= ~LCD_EN;									// pull EN bit low
    _delay_us(2);
    LCD_OUT |= LCD_EN;    								// pull EN bit high
    _delay_us(2);
    LCD_OUT &= (~LCD_EN);    							// pull EN bit low again
    _delay_us(100);
}


void LCD_SendByte(char ByteToSend, int IsData)
{
    LCD_Send4bits(ByteToSend >> 4);
    if (IsData == TRUE)
    {
        LCD_OUT |= LCD_RS;
    }
    else
    {
        LCD_OUT &= ~LCD_RS;
    }
    LCD_PulseEN();
    LCD_Send4bits(ByteToSend);
    if (IsData == TRUE)
    {
        LCD_OUT |= LCD_RS;
    }
    else
    {
        LCD_OUT &= ~LCD_RS;
    }
    LCD_PulseEN();
}

void LCD_Send4bits(unsigned char value) {
	const unsigned char data_pin[4]={LCD_D4, LCD_D5, LCD_D6, LCD_D7};
	unsigned char tmp;
	int i;
    LCD_OUT &= (~LCD_MASK);
	tmp = value;
	for (i = 0; i < 4; i++) {
		if (tmp & 01)
			LCD_OUT |= data_pin[i];
		tmp = tmp >> 1;
	}
  }



