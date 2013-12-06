/*
 * sensor.c
 *
 *  Created on: Dec 3, 2013
 *      Author: C15Payden.McBee
 */
#include "sensor.h"
#include <msp430g2553.h>

void enableADC10Subsystem()
{
	  //enable ADC10 subsystem
	  ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
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
	  ADC10CTL1 = INCH_4;                       // input A4
	  ADC10AE0 |= BIT4;                         // PA.1 ADC option select
	  ADC10CTL0 |= ENC + ADC10SC;            	// Sampling and conversion start, do this for each sensor
	  __bis_SR_register(CPUOFF + GIE);          // LPM0, ADC10_ISR will force exit
	  return ADC10MEM;
}

unsigned int getRightSensorReading()
{
	  ADC10CTL0 &= ~ENC; 						//clearing core, stop the sample and conversion sequence
	  ADC10CTL1 = INCH_5;                       // input A5
	  ADC10AE0 |= BIT5;                         // PA.1 ADC option select
	  ADC10CTL0 |= ENC + ADC10SC;            	// Sampling and conversion start, do this for each sensor
	  __bis_SR_register(CPUOFF + GIE);          // LPM0, ADC10_ISR will force exit
	  return ADC10MEM;
}

unsigned char isLeftSensorCloseToWall()
{
	return (getLeftSensorReading() < 0x2FF);
}

unsigned char isRightSensorCloseToWall()
{
	return (getRightSensorReading() < 0x2FF);
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


