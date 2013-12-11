# Robot Maze
Documentation: I looked at C2C Colin Busho's code to make tweaks to my RobotMovement library. 

## Navigating the Maze
Example code: This code uses the left sensor to follow the left wall to finish the maze. It the sensor reads that it is too far away from the wall (too small of a reading) it will make a small left turn. If the sensor reads that is too close to the wall (too large of a reading), it will make a small turn right. Otherwise, if neighter of the two conditions are met, the robot will move forward a little. This code utiilizes the RobotMotions library and RobotSenisng library. The RobotMotions library was modified in order to take smaller turns and included a function to move forward only a little. The RobotSensing library was modified to check if it was too close or too far from the wall in order to implement the left wall following technique. 
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

- Difference between the turns (big and small) is only one of timing. I change the time they are allowed to turn.
- `moveForward` has a longer time and a larger duty cycle than moveBakcward because there is a knob which slows the 
