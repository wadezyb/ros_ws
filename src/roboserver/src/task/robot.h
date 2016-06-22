#ifndef _ROBOT_H_
#define _ROBOT_H_

#define NUM_OF_AXIS (16)

typedef struct
{
	char io_input;
	int encoder;
	char temperature;
}robotAxisObj;

typedef struct
{
	int status;
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
