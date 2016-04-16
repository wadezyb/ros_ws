#ifndef _MOTION_H_
#define _MOTION_H_
#include "robolink.h"
#include <queue>
#include <cmath>
typedef struct
{
    double p;
    double v;
    double a;
}xMoveObj;
typedef struct
{
    double R;
    double startTheta;
    double endTheta;
    double v;
    double a;
}xCircleObj;
typedef struct
{
    double x;
    double y;
}xMoveCircleObj;
typedef struct
{
    double startX;
    double startY;
    double startZ;
    double endX;
    double endY;
    double endZ;
    double v;
    double a;
}xLineObj;
typedef struct
{
    double x;
    double y;
    double z;
}xMoveLineObj;

typedef struct
{
	double a;
	double b;
	double c;
}xMoveMotorObj;
void xMove(double p, double v, double a,std::queue<xMoveObj> *pqueue);
void motionTest(int n);
#endif
