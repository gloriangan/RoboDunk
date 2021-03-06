
#pragma config(Motor,  port1,           leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           armMotor,      tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                    - Dual Joystick w Timer -                                       *|
|*                                    Gloria Ngan and CJ Zhang                                        *|
|*                                                                                                    *|
|*  This program uses both the Left and the Right joysticks to run the robot using "tank control".    *|
|*  The right trigger buttons are used to control the arm, allowing the robot to pick up balls in the *|
|*  Arms and Ball Game.                                                                               *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]              [Name]              [Type]              [Description]                   *|
|*    Motor - Port 10         rightMotor           VEX Motor           Right motor                    *|
|*    Motor - Port 1          leftMotor            VEX Motor           Left motor                     *|
|*    Motor - Port 6          armMotor             VEX Motor           Arm motor                      *|
\*----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

	//Method to drive the robot.
  //Each increment increases the power of the motor by 60. speeds ranging from -120 to 120
	void drive(int x){
		motor[leftMotor]  = 60 * x;
    motor[rightMotor] = 60 * x;
	}

	//Method to move the robot's arm.
	//increments of x increases power of arm motor by 10
	void armMove(int x){
		//if x is positive, the arm moves up. if negative, arm moves down
		motor[armMotor] = 10 * x;
	}

task main ()
{
	while(1 == 1)
	{
		// Stops robot if time is greater than 90 secs.
		if(time1[T1] > 90000)
			{
				drive(0);
				armMove(0);
			}

		// Resets timer if L8 button is pressed.
		if(vexRT[Btn8L] == 1)
			{
				clearTimer(T1);
			}

	  //Refreshes joystick values while the program has been running for less than 90 seconds.
    while(time1[T1] < 90000)
    {

		// While upper left trigger is held, the joystick values are halved for a slower speed.
    	if(vexRT[Btn5U] == 1){

    		motor[leftMotor]  = -vexRT[Ch3]/2;   // Left Joystick Y value
      	motor[rightMotor] = -vexRT[Ch2]/2;   // Right Joystick Y value

      	// If upper right trigger is held, arm moves up.
      	if(vexRT[Btn6U] == 1){
      		armMove(2);
      	}
      	//Moves arm down if lower right trigger is held.
      	else if(vexRT[Btn6D] == 1){
      		armMove(-1);
      	}
      	else{
      		armMove(0);
      	}
   		}

			// If left trigger isn't held, the joystick values are directly mapped to the motors.
			else {
      	motor[leftMotor]  = -vexRT[Ch3];   // Left Joystick Y value
      	motor[rightMotor] = -vexRT[Ch2];   // Right Joystick Y value

      	//If upper right trigger is held, arm moves up.
      	if(vexRT[Btn6U] == 1){
      		armMove(4);
      	}
      	//Moves arm down if lower right trigger is held.
      	else if(vexRT[Btn6D] == 1){
      		armMove(-3);
      	}
      	else{
      		armMove(0);
      	}
  		}
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
