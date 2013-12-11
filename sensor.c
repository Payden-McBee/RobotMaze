/*
 * sensor.c
 *
 *  Created on: Dec 3, 2013
 *      Author: C15Payden.McBee
 */
#include "sensor.h"
#include <msp430g2553.h>

#define CLOSE_TO_WALL_READING 0x1AA
#define TOO_FAR_FROM_WALL_READING 0x1A0
#define TOO_CLOSE_TO_WALL_READING 0X200

void enableADC10Subsystem()
{
	  //enable ADC10 subsystem
	  ADC10CTL0 |= ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
	  ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;                // Select SMCLK
}

void initLEDs()
{
	  //set up LEDs as outputs
	  P1DIR |= BIT0;                            // Set P1.0 to output direction
	  P1DIR |= BIT6;							// Set P1.6 to output direction
}

unsigned int getLeftSensorReading()
{

	  ADC10CTL0 &= ~ENC; 						//clearing core, stop the sample and conversion sequence
	  ADC10CTL1 &= ~(INCH_0|INCH_1|INCH_2|INCH_3); //clearing the inputs
	  ADC10CTL1 |= INCH_4;                       // input A4
	  ADC10AE0 |= BIT4;                         // PA.1 ADC option select
	  ADC10CTL0 |= ENC + ADC10SC;            	// Sampling and conversion start, do this for each sensor
	  __bis_SR_register(CPUOFF + GIE);          // LPM0, ADC10_ISR will force exit
	  return ADC10MEM;
}

unsigned int getRightSensorReading()
{

	  ADC10CTL0 &= ~ENC; 						//clearing core, stop the sample and conversion sequence
	  ADC10CTL1 &= ~(INCH_0|INCH_1|INCH_2|INCH_3); //clearing the inputs
	  ADC10CTL1 |= INCH_5;                       // input A5
	  ADC10AE0 |= BIT5;                         // PA.1 ADC option select
	  ADC10CTL0 |= ENC + ADC10SC;            	// Sampling and conversion start, do this for each sensor
	  __bis_SR_register(CPUOFF + GIE);          // LPM0, ADC10_ISR will force exit
	  return ADC10MEM;
}

unsigned int getCenterSensorReading()
{

	  ADC10CTL0 &= ~ENC; 						//clearing core, stop the sample and conversion sequence
	  ADC10CTL1 &= ~(INCH_0|INCH_1|INCH_2|INCH_3);
	  ADC10CTL1 |= INCH_3;                       // input A5
	  ADC10AE0 |= BIT3;                         // PA.1 ADC option select
	  ADC10CTL0 |= ENC + ADC10SC;            	// Sampling and conversion start, do this for each sensor
	  __bis_SR_register(CPUOFF + GIE);          // LPM0, ADC10_ISR will force exit
	  return ADC10MEM;
}

//the following five functions use the readings from different sensors to check the proximity to a wall
//if the reading from the sensor is greater than (less than for isLeftSensorTooFarFromWall()) the threshold value, the functions returns a char, either
// 0x1 or 0x0, which is used in logic as true or false
unsigned char isLeftSensorCloseToWall()
{
	return (getLeftSensorReading() > CLOSE_TO_WALL_READING);
}

unsigned char isRightSensorCloseToWall()
{
	return (getRightSensorReading() > CLOSE_TO_WALL_READING);
}

unsigned char isCenterSensorCloseToWall()
{
	return (getCenterSensorReading() > CLOSE_TO_WALL_READING);
}

unsigned char isLeftSensorTooFarFromWall()
{
	return (getLeftSensorReading() < TOO_FAR_FROM_WALL_READING);
}

unsigned char isLeftSensorTooCloseToWall()
{
	return (getLeftSensorReading() > TOO_CLOSE_TO_WALL_READING);
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


