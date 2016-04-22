#include "delta.h"
#include "stdio.h"
void deltaInvK( xMoveLineObj *targetPoint ,xMoveMotorObj *motor)
{
	deltaBodyObj delta;
	delta.la = sqrt((targetPoint->x - AX)*(targetPoint->x - AX)+(targetPoint->y-AY)*(targetPoint->y-AY));
	delta.lb = sqrt((targetPoint->x - BX)*(targetPoint->x - BX)+(targetPoint->y-BY)*(targetPoint->y-BY));
	delta.lc = sqrt((targetPoint->x - CX)*(targetPoint->x - CX)+(targetPoint->y-CY)*(targetPoint->y-CY));

	delta.ha = sqrt( DELTA_ARM_ROD*DELTA_ARM_ROD - delta.la*delta.la );
	delta.hb = sqrt( DELTA_ARM_ROD*DELTA_ARM_ROD - delta.lb*delta.lb );
	delta.hc = sqrt( DELTA_ARM_ROD*DELTA_ARM_ROD - delta.lc*delta.lc );

	delta.ma = Z_OFFSET-delta.ha+targetPoint->z;
	delta.mb = Z_OFFSET-delta.hb+targetPoint->z;
	delta.mc = Z_OFFSET-delta.hc+targetPoint->z;
	//printf("%f,%f,%f\n",delta.ma,delta.mb,delta.mc);
	motor->a = delta.ma;
	motor->b = delta.mb;
	motor->c = delta.mc;
}


void xDeltaLine(xLineObj line, std::queue<xMoveMotorObj> *pqueue)
{
    double p = sqrt(
                (line.endX-line.startX)*(line.endX-line.startX)+
                (line.endY-line.startY)*(line.endY-line.startY)+
                (line.endZ-line.startZ)*(line.endZ-line.startZ));
    double v = line.v;
    double a = line.a;
    double x = line.endX-line.startX;
    double y = line.endY-line.startY;
    double z = line.endZ-line.startZ;
    double theta1;
    double theta2;
    double temp;
    double pi = 3.1415926;
    int length;
    int i;
    int sigx;
    int sigy;
    int sigz;
    if(x>=0)
        sigx = 1;
    else
        sigx = -1;
    if(y>=0)
        sigy = 1;
    else
        sigy = -1;
    if(z>=0)
        sigz = 1;
    else
        sigz = -1;

    std::queue<xMoveObj> queue;
    xMoveLineObj xLine;
    xMoveMotorObj xMotor;


    if(x*x+y*y!=0)
        theta1=atan(fabs(z)/sqrt(x*x+y*y));
    else
        theta1 = pi/2;
    if(x!=0)
        theta2=atan(fabs(y/x));
    else
        theta2 = pi/2;

    xMove(p,v,a,&queue);
    length = queue.size();
    for(i=0;i<length;i++)
    {
        temp = queue.front().p;
        queue.pop();
        xLine.z = sigz*temp*sin(theta1)+line.startZ;
        xLine.x = sigx*temp*cos(theta1)*cos(theta2)+line.startX;
        xLine.y = sigy*temp*cos(theta1)*sin(theta2)+line.startY;
        //printf("%d %f %f %f\n",i,xLine.x,xLine.y,xLine.z);
        deltaInvK(&xLine,&xMotor);
        pqueue->push(xMotor);
    }
}

void motionTest2(void)
{
	float L = 50;//mm
	double resolution = 2.0*16.0/4000.0;
	xLineObj line1;
	xLineObj line2;
	xLineObj line3;

	std::queue<xMoveMotorObj> xMotorQueue;
	xMoveMotorObj lastMotor;
	xMoveMotorObj currentMotor;

	line1.startX = 0;
	line1.startY = 0;
	line1.startZ = 0;

	line1.endX = 0;
	line1.endY = 0;
	line1.endZ = 100;

	line1.v = 0.01;//mm/ms
	line1.a = 0.001;//mm/ms/ms

	line2.startX = 0;
	line2.startY = 0;
	line2.startZ = 0;

	line2.endX = 0;
	line2.endY = -50;
	line2.endZ = 0;

	line2.v = 0.2;//mm/ms
	line2.a = 0.001;//mm/ms/ms

	line3.startX = 0;
	line3.startY = -50;
	line3.startZ = 0;

	line3.endX = 0;
	line3.endY = 0;
	line3.endZ = 0;

	line3.v = 0.2;//mm/ms
	line3.a = 0.001;//mm/ms/ms

	//xDeltaLine(line1,&xMotorQueue);
	xDeltaLine(line2,&xMotorQueue);
	xDeltaLine(line3,&xMotorQueue);
	int size = xMotorQueue.size();
	lastMotor.a = 0;
	lastMotor.b = 0;
	lastMotor.c = 0;
	for(int i=0;i<size;i++)
	{
		currentMotor.a = round(xMotorQueue.front().a/resolution);
		currentMotor.b = round(xMotorQueue.front().b/resolution);
		currentMotor.c = round(xMotorQueue.front().c/resolution);
		xMotorQueue.pop();
		//printf("%d a %f b %f c %f\n",i,currentMotor.a,currentMotor.b,currentMotor.c);
		sendIPM(currentMotor.a - lastMotor.a,currentMotor.b - lastMotor.b,currentMotor.c - lastMotor.c,0);
		lastMotor.a = currentMotor.a;
		lastMotor.b = currentMotor.b;
		lastMotor.c = currentMotor.c;
		//printf("%d a %f b %f c %f\n",i,lastMotor.a,lastMotor.b,lastMotor.c);
	}
}
