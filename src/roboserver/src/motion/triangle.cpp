#include "triangle.h"

void triangleInvK( triangleMoveObj *targetPoint ,xMoveMotorObj *motor)
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

void triangleFwdK(xMoveMotorObj *motor, triangleMoveObj *targetPoint)
{

}
