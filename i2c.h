/*
 * i2c.h
 *
 * Created: 22.02.2016 20:32:03
 *  Author: prizh
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>


// Функция инициализация шины TWI
void I2CInit(void);

void I2CStart(void);

void I2CStop(void);

// Функция записи данных по шине
uint8_t I2CWriteByte(uint8_t data);

// Функция чтения данных по шине
uint8_t I2CReadByte(uint8_t *data,uint8_t ack);
#endif /* I2C_H_ */