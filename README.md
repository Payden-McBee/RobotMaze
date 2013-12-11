# Robot Maze
Documentation: I looked at C2C Colin Busho's code to make tweaks to my RobotMovement library. 

## Navigating the Maze
Example code: This code uses the left sensor to follow the left wall to finish the maze. If the left sensor reads that it is too far away from the wall (too small of a reading) it will make a small left turn. If the left sensor reads that is too close to the wall (too large of a reading), it will make a small turn right. Otherwise, if neighter of the two conditions are met, the robot will move forward a little. This code utiilizes the RobotMotions library and RobotSenisng library. The RobotMotions library was modified in order to take smaller turns and included a function to move forward only a little. The RobotSensing library was modified to check if it was too close or too far from the wall in order to implement the left wall following technique. 
```c
#include <msp430g2553.h>
#include "robotMotion.h"
#include "sensor.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    enableADC10Subsystem();
    initTimerOutputSignals();
    configureA0andA1Timers();

    while(1)
    {
    	if(isLeftSensorTooFarFromWall())
    	{
    		turnSmallLeft();
    		moveSmallForward();
    	}
    	else if(isLeftSensorTooCloseToWall())
    	{
    		turnSmallRight();
    	}
    	else moveForward();
    }

}
```

## Notes

- This code is for a DC motor driver. There are two motors which each power a wheel. The signals delivered to the motor are determined by pulse width modulation, using Timer A and its signals, TA0.0, TA0.1, TA1.0, and TA1.1 to send information to the motor driver.
