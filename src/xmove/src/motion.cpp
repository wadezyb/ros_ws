#include "motion.h"
#include "stdio.h"


void xMove(double p, double v, double a,std::queue<xMoveObj> *pqueue)
{
    double t1=0;
    double t2=0;
    int sig=0;
    int i=0;
    double vx=0;
    double px=0;
    double ax=0;
    xMoveObj xmove;

    if(p<0)
    {
        sig = -1;
        p=-p;
    }
    else
        sig = 1;
    if(v<0)
        v=-v;
    if(a<0)
        a=-a;

    t1=sqrt(p/a);
    t1=ceil(t1);
    if( v < a*t1 )
    {
        t1=v/a;
        t1=ceil(t1);
        t2=(p-a*t1*t1)/v;
        t2=ceil(t2);
    }
    else
    {
        t2=0;
    }
    a=sig*p/(t1*t1+t1*t2);

    for(i=0;i<t1;i++)
    {
        ax=a;
        vx+=ax;
        px+=vx;
        xmove.a=ax;
        xmove.v=vx;
        xmove.p=px;
        pqueue->push(xmove);
    }
    for(i=t1;i<t1+t2;i++)
    {
        ax=0;
        vx+=ax;
        px+=vx;
        xmove.a=ax;
        xmove.v=vx;
        xmove.p=px;
        pqueue->push(xmove);
    }
    for(i=t1+t2;i<t1+t2+t1;i++)
    {
        ax=-a;
        vx+=ax;
        px+=vx;
        xmove.a=ax;
        xmove.v=vx;
        xmove.p=px;
        pqueue->push(xmove);
    }
}

void xCircle(xCircleObj circle, std::queue<xMoveCircleObj> *pqueue)
{
    double p = circle.endTheta - circle.startTheta;
    double v = circle.v;
    double a = circle.a;
    int length=0;
    int i=0;
    double temp;
    xMoveCircleObj xMoveCircle;
    std::queue<xMoveObj> queue;

    xMove(p,v,a,&queue);
    length = queue.size();
    for(i=0;i<length;i++)
    {
        temp = circle.startTheta+queue.front().p;
        queue.pop();
        xMoveCircle.x = circle.R*cos(temp);
        xMoveCircle.y = circle.R*sin(temp);
        pqueue->push(xMoveCircle);
    }
}

void xLine(xLineObj line, std::queue<xMoveLineObj> *pqueue)
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
        pqueue->push(xLine);
    }
}


void motionTest(int n)
{
	float A = 20000;
	float w = 3.1415926*0.004;
	int t=0;
	int out;
	float a;
	float b;
	for(t=0;t<1800;t++)
	{
		a = round(A*cos(w*t));
		b = round(A*cos(w*(t-1)));
		out = a-b;
		//printf("out %d\n",out);
		switch(n)
		{
			case 0:
				sendIPM(out,out/2,0,0);
				break;
			case 1:
				sendIPM(0,out/2,out/3,0);
				break;
			case 2:
				sendIPM(out,0,out/3,0);
				break;
			case 3:
				sendIPM(out,0,0,0);
				break;
			case 4:
				sendIPM(0,out/2,0,0);
				break;
			case 5:
				sendIPM(0,0,out/3,0);
				break;
			case 6:
				sendIPM(out,out/2,out/3,0);
				break;
			default :
				break;
		}

	}
}

