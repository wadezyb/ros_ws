#ifndef _ROBOT_H_
#define _ROBOT_H_

#define NUM_OF_AXIS (16)

typedef struct
{
	char io_input;
	int encoder;
	char temperature;
	char status;// On-1 Off-0
	int encoder_zero_ref;
}robotAxisObj;

typedef struct
{
	char status;// Off-0 On-1 Error-2
	char control;// Servo On-1 Servo Off-0
	char run;
	char breakon;
}robotControllerObj;

typedef struct
{

}roboSensorObj;

typedef struct
{
	robotControllerObj Controller;
	robotAxisObj Axis[NUM_OF_AXIS];
}robotObj;


extern robotObj robot;
void roboControlLoop(void);
#endif
