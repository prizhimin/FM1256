/*
 * ds1307.h
 *
 * Created: 22.02.2016 20:36:55
 *  Author: prizh
 */ 


#ifndef DS1307_H_
#define DS1307_H_

// Функция чтения данных из DS1307
uint8_t DS1307Read(uint8_t address,uint8_t *data);

// Функция записи данных в DS1307
uint8_t DS1307Write(uint8_t address,uint8_t data);

#endif /* DS1307_H_ */