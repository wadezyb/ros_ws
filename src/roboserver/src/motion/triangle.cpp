#include "triangle.h"
#include "stdio.h"
#include "../motion/motion.h"

triangleMoveObj currentTri;
triangleMoveObj targetTri;

void triZero(void)
{
	currentTri.n(0) = 0;
	currentTri.n(1) = 0;
	currentTri.n(2) = 1;
	currentTri.height = 0;
}


MatrixXf Rotation(float row, float pitch)
{
	MatrixXf R;
	R.resize(3,3);
	Vector3f w1(1,0,0);
	Vector3f w2(0,1,0);
	R = expr(w1,row)*expr(w2,pitch);
	return R;
}


void triangleInvK( Vector3f w, float theta, float height, xMoveMotorObj *motor)
{
	Vector3f P10(TRIANGLE_R*cos(0),TRIANGLE_R*sin(0),0);
	Vector3f P20(TRIANGLE_R*cos(2*PI/3),TRIANGLE_R*sin(2*PI/3),0);
	Vector3f P30(TRIANGLE_R*cos(4*PI/3),TRIANGLE_R*sin(4*PI/3),0);

	Vector3f P1_New;
	Vector3f P2_New;
	Vector3f P3_New;
	P1_New = expr(w,theta)*P10;
	P2_New = expr(w,theta)*P20;
	P3_New = expr(w,theta)*P30;

	float M0 = sqrt(TRIANGLE_L*TRIANGLE_L-(TRIANGLE_H-TRIANGLE_R)*(TRIANGLE_H-TRIANGLE_R));
	motor->a = sqrt(TRIANGLE_L*TRIANGLE_L-(TRIANGLE_H-sqrt(TRIANGLE_R*TRIANGLE_R - P1_New(2)*P1_New(2) ))*(TRIANGLE_H-sqrt(TRIANGLE_R*TRIANGLE_R - P1_New(2)*P1_New(2)))) + P1_New(2) + height - M0;
	motor->b = sqrt(TRIANGLE_L*TRIANGLE_L-(TRIANGLE_H-sqrt(TRIANGLE_R*TRIANGLE_R - P2_New(2)*P2_New(2) ))*(TRIANGLE_H-sqrt(TRIANGLE_R*TRIANGLE_R - P2_New(2)*P2_New(2)))) + P2_New(2) + height - M0;
	motor->c = sqrt(TRIANGLE_L*TRIANGLE_L-(TRIANGLE_H-sqrt(TRIANGLE_R*TRIANGLE_R - P3_New(2)*P3_New(2) ))*(TRIANGLE_H-sqrt(TRIANGLE_R*TRIANGLE_R - P3_New(2)*P3_New(2)))) + P3_New(2) + height - M0;

	motor->a = round(motor->a/TRI_M_RES);
	motor->b = round(motor->b/TRI_M_RES);
	motor->c = round(motor->c/TRI_M_RES);

}

void triangleFwdK(xMoveMotorObj *motor, triangleMoveObj *targetPoint)
{

}

void triangleMove(triangleMoveObj *targetPoint, triangleMoveObj *currentPoint)
{
	Vector3f w = currentPoint->n.cross(targetPoint->n)/currentPoint->n.norm()/targetPoint->n.norm();
	float theta = acos( currentPoint->n.dot(targetPoint->n)/currentPoint->n.norm()/targetPoint->n.norm() );
	std::queue<xMoveObj> queue;
	std::queue<xMoveMotorObj> xMotorQueue;
	xMoveMotorObj lastMotor;
	xMoveMotorObj motor;
	float p = theta;
	float v = 0.001;
	float a = 0.00001;
	xMove(p,v,a,&queue);
	int num = queue.size();
	for (int i=0;i<num;i++)
	{
		float temp_theta = queue.front().p;
		queue.pop();
		triangleInvK(w,temp_theta,0,&motor);
		if(i>0)
		{
			//printf("%.1f,%.1f,%.1f\n",motor.a - lastMotor.a,motor.b - lastMotor.b,motor.c - lastMotor.c);
			sendIPM((short)(motor.a - lastMotor.a),(short)(motor.b - lastMotor.b),(short)(motor.c - lastMotor.c),0);
		}
		lastMotor.a = motor.a;
		lastMotor.b = motor.b;
		lastMotor.c = motor.c;
	}
}

void triangleMoveTest()
{
	Vector3f n(0,0,1);

	float row = clientData.row/180.0*PI;
	float pitch = clientData.pitch/180.0*PI;
	targetTri.n = Rotation(row,pitch)*n;
	//printf("%f,%f,%f\n",target.n(0),target.n(1),target.n(2));
	triangleMove(&targetTri,&currentTri);
	currentTri.n(0)=targetTri.n(0);
	currentTri.n(1)=targetTri.n(1);
	currentTri.n(2)=targetTri.n(2);
	printf("%f,%f,%f\n",currentTri.n(0),currentTri.n(1),currentTri.n(2));

}

void triangleMoveEach()
{
	float m1 = clientData.row;
	float m2 = clientData.pitch;
	float m3 = clientData.height;
	xMoveMotorObj lastMotor;
	xMoveMotorObj motor;
	xLineObj line;
	line.startX = 0;
	line.startY = 0;
	line.startZ = 0;

	line.endX = m1;
	line.endY = m2;
	line.endZ = m3;

	line.v = clientData.velocity;
	line.a = clientData.acceleration;

	std::queue<xMoveLineObj> pqueue;

	xLine(line,&pqueue);
	int num = pqueue.size();
	for(int i=0;i<num;i++)
	{
		motor.a = round(pqueue.front().x/TRI_M_RES);
		motor.b = round(pqueue.front().y/TRI_M_RES);
		motor.c = round(pqueue.front().z/TRI_M_RES);
		pqueue.pop();
		if(i>0)
		{

			sendIPM((short)(motor.a - lastMotor.a),(short)(motor.b - lastMotor.b),(short)(motor.c - lastMotor.c),0);
		}
		lastMotor.a = motor.a;
		lastMotor.b = motor.b;
		lastMotor.c = motor.c;

	}
}
