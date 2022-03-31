 /******************************************************************************
 *
 * Module: HC-SR04 Ultrasonic Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: header file for the HC-SR04 Sensor driver
 *
 * Author: Omar Elsehity
 *
 *******************************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include"std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ULTRASONIC_TRIGGER_PORT PORTB_ID
#define ULTRASONIC_TRIGGER_PIN  PIN5_ID

//as we in atmega16/32 there is only one input capture unit through PD6/ICP1
#define ULTRASONIC_ECHO_PORT PORTD_ID
#define ULTRASONIC_ECHO_PIN  PIN6_ID

#define ULTRASONIC_TRIGGER_PULSE_DURATION 10


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description: function responsible for initialization of ultrasonic sensor
 * 1. initialize ICU
 * 2. Setup the ICU call back function.
 * 3. Setup the direction for the trigger pin as output pin
 */
void Ultrasonic_init(void);

/*
 * Description : function responsible for Send the Trigger pulse to the sensor
 */
void Ultrasonic_Trigger(void);

/*
 * Description: function responsible for reading distance using the ultrasonic sensor
 *  1. send the trigger pulse by using Ultrasonic_Trigger function
 *	2. Start the measurements by the ICU from this moment
 *
 *	Return: The measured distance in cm
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Function description:
 * This is the call back function called by the ICU driver
 * the function calculates the high time from the sensor
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
