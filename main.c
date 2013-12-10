#include <msp430g2553.h>
#include "robotMotion.h"
#include "sensor.h"

#define TRUE 0x01
#define FALSE 0x00

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    unsigned char wayIsClear=TRUE;
    enableADC10Subsystem();
    initTimerOutputSignals();
    configureA0andA1Timers();

    while(1)
    {
    	if(isRightSensorCloseToWall())
    	    {
    		 turnSmallLeft();
    		 wayIsClear=FALSE;
    	    } else if(isLeftSensorCloseToWall())
    	    {
    		 turnSmallRight();
    		 wayIsClear=FALSE;
    	    }
    	    else if(wayIsClear)
    	{
    		moveForward();
    	}
    	wayIsClear=TRUE;
    	clearModes();
    }

}
