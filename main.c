/*
 * FM1256.c
 *
 * Created: 23.02.2016 12:54:32
 * Author : prizh
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hardware.h"
#include "i2c.h"
#include "hd44780.h"
#include "ds1307.h"
#include "keypad4x4.h"
#include "fm1256.h"



uint32_t freq=100000, old_freq;		// kHz

void Int_Init()
{
	//сбрасываем все биты ISCxx
	EICRA &= ~( (1<<ISC11)|(1<<ISC10)|(1<<ISC01)|(1<<ISC00) );
	//настраиваем на срабатывание INT0 по ниспадающему фронту
	EICRA |= (1<<ISC01)|(0<<ISC00)|(1<<ISC11)|(0<<ISC10);
	//разрешаем внешнее прерывание INT0
	EIMSK|=(1<<INT0)|(1<<INT1);	
}

//функция обработчик внешнего прерывания INT0
ISR( INT0_vect )
{
	if(PINC & BIT3)
		freq += 10;
	else
		freq -= 10;
}

ISR( INT1_vect)
{
	//FM1256_SetStep3125();
	//FM1256_ShowStep();
	//FM1256_update();
	LED_PORT |= LED_RED;
	_delay_ms(1100);
	LED_PORT &= ~LED_RED;
}


int main(void)
{
	LCD_Init();
	I2CInit();
	Int_Init();
	KeyPad_Init();

	// Запускаем ход часов
	uint8_t temp;
	DS1307Read(0x00,&temp);
	temp &= ~(1 << 7); // обнуляем 7 бит
	DS1307Write(0x00,temp);
		
	uint8_t hour, minute, second;
	
	LED_DDR |= LED_GREEN + LED_RED;
	LED_PORT &= ~(LED_GREEN + LED_RED);
			
	sei();

	LCD_Clear();
	LCD_PrintStr("Freq=");
	FM1256_SetFreq(freq);
	while (1) 
    {
		LCD_GoTo(0,5);
		LCD_PrintDec(freq);
		LCD_PrintStr(" KHz ");
		
		// Читаем данные и преобразуем из BCD в двоичную систему
		DS1307Read(0x00,&temp); // Чтение регистра секунд
		second = (((temp & 0xF0) >> 4)*10)+(temp & 0x0F);
		DS1307Read(0x01,&temp); // Чтение регистра минут
		minute = (((temp & 0xF0) >> 4)*10)+(temp & 0x0F);
		DS1307Read(0x02,&temp); // Чтение регистра часов
		hour = (((temp & 0xF0) >> 4)*10)+(temp & 0x0F);

		LCD_GoTo(3,0);
		LCD_PrintStr("Time=");
		if(hour<10) 		LCD_PrintStr("0");
		LCD_PrintDec(hour);
		LCD_PrintStr(":");
		if(minute<10)		LCD_PrintStr("0");
		LCD_PrintDec(minute);
		LCD_PrintStr(":");
		if(second<10)		LCD_PrintStr("0");
		LCD_PrintDec(second);
		//freq -= 20;
		if(freq != old_freq)
		{
			LED_PORT |= LED_GREEN;
			FM1256_SetFreq(freq);
			old_freq=freq;
			_delay_ms(50);
			//uint8_t answer=0, res;
			//I2CStart();
			//I2CWriteByte(FM1256 | 0x01);
			//res = I2CReadByte(&answer,0);
			//I2CStop();
			//if(res)
			//{
				//LCD_GoTo(1,0);
				//LCD_PrintStr("Tuner Read Res=");
				//LCD_PrintDec(answer);
				//LCD_PrintStr(" ");
			//}			
			//else
			//{
				//LCD_GoTo(1,0);
				//LCD_PrintStr("Error!");
			//}
			//I2CStart();
			//I2CWriteByte(TDA9887 | 0x01);
			//res = I2CReadByte(&answer,0);
			//I2CStop();
			//if(res)
			//{
				//LCD_GoTo(2,0);
				//LCD_PrintStr("IF Read Res=");
				//LCD_PrintDec(answer);
				//LCD_PrintStr("  ");
			//}
			//else
			//{
				//LCD_GoTo(2,0);
				//LCD_PrintStr("Error!");
			//}
			
			LED_PORT &= ~LED_GREEN;
					
		} 
	}
}

