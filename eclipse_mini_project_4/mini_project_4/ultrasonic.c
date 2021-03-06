/**************************************************************************
 * Module: Ultrasonic
 *
 * File name: ultrasonic.c
 *
 * Description: source file for the ultrasonic sensor driver
 *
 * Author: Mohamed Elshafie
 ***********************************************************************/



#include <util/delay.h>
#include "ultrasonic.h"

/*******************************************************************************
 *                          Global variables
 *******************************************************************************/
Icu_ConfigType ICU_Config = {F_CPU_8,RISING};
uint16 g_edgeCount = 0;
uint16 g_timeHigh = 0;

uint16 dist=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Description:
 * Initialize the ICU driver as required.
 * Setup the ICU call back function.
 * Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void){
	Icu_init(&ICU_Config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
}

/* Description:
 * Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void){

	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

/* Description:
 * Send the trigger pulse by using Ultrasonic_Trigger function.
 * Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	g_edgeCount = 0;
	dist = (g_timeHigh*0.017);
	return dist;
}

/* Description:
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
	}
	else if(g_edgeCount == 3){
		g_edgeCount = 0;
	}

}
