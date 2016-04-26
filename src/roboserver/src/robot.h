#ifndef _ROBOT_H_
#define _ROBOT_H_

#define NUM_OF_AXIS (16)

typedef struct
{
	char io_input;
	int encoder;
}robotAxisObj;

typedef struct
{
	robotAxisObj Axis[NUM_OF_AXIS];
}robotObj;


extern robotObj robot;
#endif
