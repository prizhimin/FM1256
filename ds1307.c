/*
 * ds1307.c
 *
 * Created: 22.02.2016 20:36:27
 *  Author: prizh
 */ 

#include <avr/io.h>

#include "i2c.h"

// Функция чтения данных из DS1307
uint8_t DS1307Read(uint8_t address,uint8_t *data)
{
	uint8_t res; // Результат
	I2CStart(); // СТАРТ
	res = I2CWriteByte(0b11010000); // адрес DS1307 + бит W
	if(!res)    return 0; // ОШИБКА
	// Передача адреса необходимого регистра
	res = I2CWriteByte(address);
	if(!res)    return 0; // ОШИБКА
	I2CStart(); // Повторный СТАРТ
	res = I2CWriteByte(0b11010001); // адрес DS1307 + бит R
	if(!res)    return 0; // ОШИБКА
	// Чтение данных с неподтверждением
	res = I2CReadByte(data,0);
	if(!res)    return 0; // ОШИБКА
	I2CStop(); // СТОП
	return 1;
}
// Функция записи данных в DS1307
uint8_t DS1307Write(uint8_t address,uint8_t data)
{
	uint8_t res; // Результат
	I2CStart(); // СТАРТ
	res = I2CWriteByte(0b11010000); // адрес DS1307 + бит W
	if(!res)    return 0; // ОШИБКА
	// Передача адреса необходимого регистра
	res = I2CWriteByte(address);
	if(!res)    return 0; // ОШИБКА
	res = I2CWriteByte(data); // Запись данных
	if(!res)    return 0; // ОШИБКА
	I2CStop(); // СТОП
	return 1;
}
