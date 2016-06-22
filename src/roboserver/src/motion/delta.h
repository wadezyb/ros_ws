#ifndef _DELTA_H_
#define _DELTA_H_

#include "motion.h"

#define DELTA_ARM_ROD 216.0
#define DELTA_EFFECTOR_OFFSET 24.0
#define DELTA_CARRIAGE_OFFSET 22.0
#define DELTA_ROS_OFFSET 151.0
#define DELTA_RADIUS (DELTA_ROS_OFFSET-DELTA_CARRIAGE_OFFSET-DELTA_EFFECTOR_OFFSET)
#define Z_OFFSET sqrt(DELTA_ARM_ROD*DELTA_ARM_ROD-DELTA_RADIUS*DELTA_RADIUS)

#define AX 0
#define AY (DELTA_RADIUS)
#define BX (DELTA_RADIUS*0.866025404)
#define BY (-DELTA_RADIUS/2.0)
#define CX (-DELTA_RADIUS*0.866025404)
#define CY (-DELTA_RADIUS/2.0)

typedef struct
{
	double la;
	double lb;
	double lc;
	double ha;
	double hb;
	double hc;
	double ma;
	double mb;
	double mc;
}deltaBodyObj;

void deltaInvK( xMoveLineObj *targetPoint ,xMoveMotorObj *motor);
void motionTest2(void);
#endif
