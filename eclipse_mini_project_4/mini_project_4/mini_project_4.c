/*
 * mini_project_4.c
 *
 *  Created on: Oct 14, 2021
 *      Author: Mohamed Elshafie
 */
#include <avr/io.h>
#include "std_types.h"
#include "ultrasonic.h"
#include "lcd.h"
int main(void){
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	uint16 distance=0;
	Ultrasonic_init();
	LCD_init();
	LCD_moveCursor(0, 0);
	LCD_displayString("Distance =    cm");
	while(1){
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0, 10);
		LCD_intgerToString(distance);
		LCD_displayCharacter(' ');
	}
}

