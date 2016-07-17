#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include "../robotics/robotics.h"
#include "motion.h"

#define TRIANGLE_L (115.5)
#define TRIANGLE_R (102.5)
#define TRIANGLE_H (310)

#define TRI_M_RES (PI*60/10/4000.0)


typedef struct
{
	Vector3f n;
	float height;
	Vector3f w;
	float theta;
}triangleMoveObj;

extern triangleMoveObj tri;

void triangleMoveTest();
void triZero(void);
void triangleMoveEach();
#endif
