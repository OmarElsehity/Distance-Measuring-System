/******************************************************************************
 *
 * Module: HC-SR04 Ultrasonic Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: source file for the HC-SR04 Sensor driver
 *
 * Author: Omar Elsehity
 *
 *******************************************************************************/
#include "ultrasonic.h"
#include "icu.h"
#include "util/delay.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* (g_echo_time variable) to store time for high value in echo pin */
static uint16 g_echo_time = 0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 ******************************************************************************/

/*
 * Description: function responsible for initialization of ultrasonic sensor
 * 1. initialize ICU
 * 2. Setup the ICU call back function.
 * 3. Setup the direction for the trigger pin as output pin
 */
void Ultrasonic_init(void){

	/*  initialize the ICU */
	Icu_ConfigType Config={F_CPU_8,RISING};
	Icu_init(&Config);

	/* set call back function */
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/*
	 * setup direction of trigger pin as OUTPUT
	 * initialize the pin by set it to LOGIC_LOW
	 */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, PIN_OUTPUT);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN,LOGIC_LOW);
}

/*
 * Description : function responsible for Send the Trigger pulse to the sensor
 */
void Ultrasonic_Trigger(void){

	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN,LOGIC_HIGH);
	_delay_us(ULTRASONIC_TRIGGER_PULSE_DURATION);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN,LOGIC_LOW);
}

/*
 * Description: function responsible for reading distance using the ultrasonic sensor
 *  1. send the trigger pulse by using Ultrasonic_Trigger function
 *	2. Start the measurements by the ICU from this moment
 *
 *	Return: The measured distance in cm
 */
uint16 Ultrasonic_readDistance(void){

	Ultrasonic_Trigger();
	return (g_echo_time / 58.8);
}

/*
 * Function description:
 * This is the call back function called by the ICU driver
 * the function calculates the high time from the sensor
 */
void Ultrasonic_edgeProcessing(void){

	static uint8 g_edgeCount = 0;

	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/* Clear the timer counter register to start from the first rising edge */
		Icu_clearTimerValue();

		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{

		/* Store the High time value */
		g_echo_time = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);


		g_edgeCount=0;
	}

}
