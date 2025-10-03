/*
 * fm1256.h
 *
 * Created: 27.02.2016 12:15:17
 *  Author: prizh
 */ 


#ifndef FM1256_H_
#define FM1256_H_

#include <avr/io.h>

#include "hardware.h"

#define FM1256	0xC0
#define TDA9887 0x86




				
// Byte CB				

#define			bitCP	BIT6
#define			bitT2	BIT5
#define			bitT1	BIT4
#define			bitT0	BIT3
#define			bitRSA	BIT2
#define			bitRSB	BIT1
#define			bitOS	BIT0

// Byte BB

#define			bitSW	BIT7
#define			bitFMST	BIT6
#define			bitP5	BIT5
#define			bitTV	BIT4
#define			bitFM	BIT3
#define			bitHigh	BIT2
#define			bitMid	BIT1
#define			bitLow	BIT0

// Byte AB

#define			bitATC	BIT7
#define			bitAL2	BIT6
#define			bitAL1	BIT5
#define			bitAL0	BIT4

// Byte B (Switching)

#define			bitL	BIT7
#define			bitFMS	BIT6
#define			bitFMA	BIT5
#define			bitTVM	BIT4
#define			bitCM	BIT2
#define			bitAMF	BIT1
#define			bitVM	BIT0

// Byte C (Adjust)

#define			bitAG	BIT7
#define			bitDE1	BIT6
#define			bitDE0	BIT5
#define			bitTOP4	BIT4
#define			bitTOP3	BIT3
#define			bitTOP2	BIT2
#define			bitTOP1	BIT1
#define			bitTOP0	BIT0

// Byte E (Data)

#define			bitAGC	BIT7
#define			bitGATE	BIT6
#define			bitGIF	BIT5
#define			bitVIF2	BIT4
#define			bitVIF1	BIT3
#define			bitVIF0	BIT2
#define			bitSIF1	BIT1
#define			bitSIF0	BIT0


				
void FM1256_update();
void FM1256_SetFreq(uint32_t kHzFreq);						// «адать частоту (в к√ц)
void FM1256_SetStep3125();									// ”станавливает шаг изменени€ частоты в 31.25 к√ц
void FM1256_SetStep50();									// ”станавливает шаг изменени€ частоты в 50 к√ц
void FM1256_ShowStep();

#endif /* FM1256_H_ */