/******************************************************************************
 *
 * File Name: Measure_distance.c
 *
 * Description: source file for the program code
 *
 * Author: Omar Elsehity
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "lcd.h"

#include<avr/interrupt.h> /* to use sei function */
#include<util/delay.h>    /* to use delay function */


int main(){

	/* initialization */
	LCD_init();
	Ultrasonic_init();

	/* Enable Global Interrupt I-Bit */
	sei();

	/* variable used to store value returned from ultrasonic */
	uint16 distance = 0;

	LCD_displayString("Distance=     Cm");

	while(1){

		distance = Ultrasonic_readDistance();
		LCD_moveCursor(1, 11);
		LCD_intgerToString(distance);

		_delay_ms(5);
	}

}
