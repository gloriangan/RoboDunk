#pragma config(Motor,  port10,           rightMotor,    tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port1,          leftMotor,     tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Authors: Chu Jie Zhang, Gloria Ngan

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Moving Forward -                                         *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs your robot to move forward at full power for three seconds.  There is a    *|
|*  two second pause at the beginning of the program.                                                 *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Power levels that can be assigned to a motor port range from -127 (full reverse) to         *|
|*        127 (full forward).                                                                         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 2        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 3        leftMotor           VEX 3-wire module     Left side motor                   *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

//method that moves the robot forward, the beginning and end for loops are to increment the
//speed by which the wheels are turning. This is done to ensure the robot moves initially in
//straight line and to prevent/reduce drift
void moveForward(int x)
{
	for(int i = 10; i < 121; i = i + 10)
	{
		motor[rightMotor] = i;		  // Motor on port10 is run forward
		motor[leftMotor]  = i;		  // Motor on port1 is run forward
		wait1Msec(50);	        // Robot runs previous code for 50 milliseconds before moving on
	}

	motor[rightMotor] = 120;		  // Motor on port10 is run forward
	motor[leftMotor]  = 120;		  // Motor on port1 is run forward
	wait1Msec(x * 10);	        // Robot runs previous code for x * 10 milliseconds before moving on

	for(int i = 120; i >= 0; i = i - 10)
	{
		motor[rightMotor] = i;		  // Motor on port10 is run forward
		motor[leftMotor]  =  i;		  // Motor on port1 is run forward
		wait1Msec(50);	        // Robot runs previous code for 50 milliseconds before moving on
	}
}

//method to turn robot 90 degrees, +1 means the robot turns <>, -1 means the robot turns to the <>
void turn90(int x)
{
	for(int i = 0; i < 111; i = i + 10)
	{
		motor[rightMotor] = i * x;		  // Motor on port10 is run forward
		motor[leftMotor]  = i * -x;		  // Motor on port1 is run forward
		wait1Msec(50);	        // Robot runs previous code for 50 milliseconds before moving on
	}
	for(int i = 110; i >= 0; i = i - 10)
	{
		motor[rightMotor] = i * x;		  // Motor on port10 is run forward
		motor[leftMotor]  = i * -x;		  // Motor on port1 is run forward
		wait1Msec(50);	        // Robot runs previous code for 50 milliseconds before moving on
	}
}
//slower top speed than moveForward
void moveForwardSlower(int x)
{
	for(int i = 10; i < 81; i = i + 10)
	{
		motor[rightMotor] = i;		 // Motor on port10 is run forward
		motor[leftMotor]  = i;		 // Motor on port1 is run forward
		wait1Msec(50);	        	 // Robot runs previous code for 50 milliseconds before moving on
	}

	motor[rightMotor] = 80;		  // Motor on port10 is run forward
	motor[leftMotor]  = 80;		  // Motor on port1 is run forward
	wait1Msec(x * 10);	        // Robot runs previous code for x * 10 milliseconds before moving on

	for(int i = 80; i >= 0; i = i - 10)
	{
		motor[rightMotor] = i;		 // Motor on port10 is run forward
		motor[leftMotor]  =  i;		 // Motor on port1 is run forward
		wait1Msec(50);	       		 // Robot runs previous code for x * 10 milliseconds before moving on
	}
}

task main()
{
	moveForward(50);
	turn90(1);
	moveForward(35);
	turn90(-1);
	moveForward(10);
	turn90(-1);
	moveForwardSlower(5);
}
