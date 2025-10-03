/*
 * fm1256.c
 *
 * Created: 27.02.2016 12:19:57
 *  Author: prizh
 */ 

#include "i2c.h"
#include "fm1256.h"
#include "hardware.h"
#include "hd44780.h"

uint16_t		IFFreq = 33250;		// default 33,25 MHz
uint16_t		StepHz = 31250;		// default 31,25 KHz Step-Size

uint8_t			byteDB1	= 0,
				byteDB2	= 0,
				byteCB	= 0x82,
				byteBB	= 0x19,
				byteAB	= 0x40,
				byteSB	= 0;

uint8_t			byteSAD	= 0,
				byteB	= 0xCE,
				byteC	= 0xD0,
				byteE	= 0x7F,
				byteSR	= 0;
			
void FM1256_update()
{
	I2CStart();
	I2CWriteByte(FM1256);
	I2CWriteByte(byteDB1);					// (freq & 0xFF00)>>8);
	I2CWriteByte(byteDB2);					// (freq & 0x00FF));
	I2CWriteByte(byteCB);					// 0x80);
	I2CWriteByte(byteBB);					// 0x19);
	I2CWriteByte(byteAB);					// 0x40);
	I2CStop();
	
	I2CStart();
	I2CWriteByte(TDA9887);
	I2CWriteByte(byteSAD);					// 0);
	I2CWriteByte(byteB);					// 0xСE);
	I2CWriteByte(byteC);					// 0xD0);
	I2CWriteByte(byteE);					// 0x7F);
	I2CStop();
}

void FM1256_SetFreq(uint32_t kHzFreq)
{
	uint16_t Freq;
	
	Freq = (kHzFreq + IFFreq) * 1000 / StepHz;
	byteDB1 = ((Freq & 0xFF00)>>8);
	byteDB2 = ((Freq & 0x00FF));
	
	if (kHzFreq >= 442000)
	{
		byteBB &= ~(bitMid | bitLow);
		byteBB |= bitHigh;
		LCD_GoTo(1,0);
		LCD_PrintStr("Band: HIGH");
	
	}
	else if (kHzFreq >= 160000 && kHzFreq < 442000)
	{
		byteBB &= ~(bitHigh | bitLow);
		byteBB |= bitMid;
		LCD_GoTo(1,0);
		LCD_PrintStr("Band: MEDIUM");
	}
	else
	{
		byteBB &= ~(bitHigh | bitMid);
		byteBB |= bitLow;
		LCD_GoTo(1,0);
		LCD_PrintStr("Band: LOW");
	}
	FM1256_update();	
}

void FM1256_SetStep3125()									// Устанавливает шаг изменения частоты в 31.25 кГц
{
	StepHz = 31250;
	byteCB &= ~bitRSA;
	byteCB |= bitRSB;
	FM1256_update();
}
void FM1256_SetStep50()										// Устанавливает шаг изменения частоты в 50 кГц
{
	StepHz = 50000;
	byteCB &= ~(bitRSA | bitRSB);
	FM1256_update();
}

void FM1256_ShowStep()
{
	LCD_GoTo(2,0);
	LCD_PrintStr("Step: ");
	LCD_PrintDec(StepHz);
	LCD_PrintStr("CB: ");
	LCD_PrintDec(byteCB);
}