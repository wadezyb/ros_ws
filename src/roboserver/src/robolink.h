#ifndef _ROBOLINK_H_
#define _ROBOLINK_H_

#include <queue>

/* Command Index */
#define ControlWordIndex (0)
#define ModesofOperationIndex (1)
#define TargetCurrentIndex (2)
#define TargetVelocityIndex (3)
#define TargetPositionIndex (4)
#define MaxCurrentIndex (5)
#define MaxVelocityIndex (6)
#define MaxPositionIndex (7)
#define MinPositionIndex (8)
#define ProfileAccIndex (9)
#define ProfileDecIndex (10)
#define ProfileVelocityIndex (11)
#define InterpolatedPositionIndex (12)
#define InterpolationTimeIndex (13)

/* Status Index */
#define StatusWordIndex (50)
#define ActualCurrentIndex (51)
#define ActualVelocityIndex (52)
#define ActualPositionIndex (53)
#define IO_InputIndex (54)
#define HeartBeatIndex (100)

typedef struct
{
    char id;
    char data[8];
}sendMsgObj;

extern std::queue<sendMsgObj> sendMsgQueue;
int roboLinkInit(void);
void servoOn(void);
void servoOff(void);
void timerInit(void);
void sendCAN(char ID,char Index, int Data);
void sendIPM(short dp1, short dp2, short dp3, short dp4);
void sendIPM_Pro(short *dp);
int sendBufSize(void);
void receiveTask(void);
void servoHome(void);
int udpServerTask(void);
int serialPortManagementTask(void);
#endif
