/*
 * ds1307.c
 *
 * Created: 22.02.2016 20:36:27
 *  Author: prizh
 */ 

#include <avr/io.h>

#include "i2c.h"

// ������� ������ ������ �� DS1307
uint8_t DS1307Read(uint8_t address,uint8_t *data)
{
	uint8_t res; // ���������
	I2CStart(); // �����
	res = I2CWriteByte(0b11010000); // ����� DS1307 + ��� W
	if(!res)    return 0; // ������
	// �������� ������ ������������ ��������
	res = I2CWriteByte(address);
	if(!res)    return 0; // ������
	I2CStart(); // ��������� �����
	res = I2CWriteByte(0b11010001); // ����� DS1307 + ��� R
	if(!res)    return 0; // ������
	// ������ ������ � ����������������
	res = I2CReadByte(data,0);
	if(!res)    return 0; // ������
	I2CStop(); // ����
	return 1;
}
// ������� ������ ������ � DS1307
uint8_t DS1307Write(uint8_t address,uint8_t data)
{
	uint8_t res; // ���������
	I2CStart(); // �����
	res = I2CWriteByte(0b11010000); // ����� DS1307 + ��� W
	if(!res)    return 0; // ������
	// �������� ������ ������������ ��������
	res = I2CWriteByte(address);
	if(!res)    return 0; // ������
	res = I2CWriteByte(data); // ������ ������
	if(!res)    return 0; // ������
	I2CStop(); // ����
	return 1;
}
