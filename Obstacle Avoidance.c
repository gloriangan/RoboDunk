#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in4,    potMeter,       sensorPotentiometer)
#pragma config(Sensor, dgtl7,  redLED,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_inch)
#pragma config(Sensor, dgtl10, rightButton,    sensorTouch)
#pragma config(Sensor, dgtl11, leftButton,     sensorTouch)
#pragma config(Sensor, dgtl12, greenLED,       sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, PIDControl, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, PIDControl, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++++++++++\
																	  SwerveBot: Obstacle Avoidance
																	Authors: Gloria Ngan and CJ Zhang

			A program that begins when the rightButton is pressed. The robot drives in a straight line until
			it detects an obstacle (the distance is based upon the setting or the potentiometer dial). When
			and obstacle is detected, the robot turns ~90 deg and repeats the process. It will stop if the
			leftButton is pressed three times.


																	 Robot Model: Modified Swervebot

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 1        rightMotor          393 Motor             Right side motor
Motor Port 10       leftMotor           393 Motor             Left side motor, Reversed
I2C_1               rightIEM            Integrated Encoder    Encoder mounted on rightMotor
I2C_2               leftIEM             Integrated Encoder    Encoder mounted on leftMotor
Digital Port 8,9    sonar               Sonar Sensor          Sonar sensor mounted on the front.
Analog Port 4       potMeter            Potentiometer         Potentiometer for setting dial.
-------------------------------------------------------------------------------------------------------------*/

//Variable to store values, allowing the distance at which the robot stops before an object to be set.
int senseDistance;

/*+++++++++++++++++++++++++++++++++++++++++++++| Methods |++++++++++++++++++++++++++++++++++++++++++++++*/

//Method to completely stop the motors.
void stopRobot(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

//Resets the encoders integrated into each motor.
void clearEncoders(){
	SensorValue[rightIEM] = 0;
	SensorValue[leftIEM] = 0;
	wait1Msec(1000);						//Pauses robot for one second.
}

//Gets the value from the potentiometer and sets the range of the ultrasonic based on it.
void setSenseDistance(){
	if(SensorValue[potMeter] < 100){				//If tape on the dial is facing up.
		senseDistance = 4;
	}
	else if(SensorValue[potMeter] < 1500){ 	//If the tape is facing left.
		senseDistance = 6;
	}
	else if(SensorValue[potMeter] < 3000){ 	//If the tape is facing down.
		senseDistance = 8;
	}
	else{																		//If the tape is facing right.
		senseDistance = 10;
	}
}

//Called when the robot detects an obstacle; it turns 90 degrees.
void avoidObstacle(){
		clearEncoders();

		while(SensorValue[leftIEM] < 150){
			motor[rightMotor] = 65;
			motor[leftMotor] = -65;
		}
		stopRobot();
		wait1Msec(1000);
}

//Drives until an object within range (senseDistance) is detected.
void senseDrive(){
	while(1 == 1){

		//Code to stop robot if button is pressed.
		if(SensorValue[leftButton] == 1){
			stopRobot();
			break;
			}

			while(SensorValue[sonarSensor] > senseDistance || SensorValue[sonarSensor] == -1){ 	// Loop while robot's Ultrasonic sensor is further than x cm away from an object
				//Code to stop robot if button is pressed.
				if(SensorValue[leftButton] == 1){
					stopRobot();
					break;
				}

				motor[rightMotor] = -40;
				motor[leftMotor] = -40;
				SensorValue[greenLED] = 1; 	//LED remains green if no obstacle is within senseDistance
				SensorValue[redLED] = 0;
			}

			//Code to stop robot if button is pressed.
			if(SensorValue[leftButton] == 1){
				stopRobot();
				break;
			}

			//Executes this if there is an obstacle.
			SensorValue[greenLED] = 0;
			SensorValue[redLED] = 1; 			//LED turns red if an obstacle is within senseDistance
			stopRobot();
			avoidObstacle();							//Turns away from obstacle.

	}
	stopRobot();
}

//Separate method allows robot to pause after turning.
void obstacleAvoidance(){
	senseDrive();
	stopRobot();
	wait1Msec(1000);
}

/*+++++++++++++++++++++++++++++++++++++++++++++| Tasks |++++++++++++++++++++++++++++++++++++++++++++++*/
task main(){
	while(1 == 1){

		setSenseDistance();

		if(SensorValue[rightButton] == 1){

			obstacleAvoidance();
		}
	}
}