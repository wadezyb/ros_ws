#ifndef _ROBOLINK_H_
#define _ROBOLINK_H_

#include <queue>

#define SERIAL_PORT ("/dev/ttyUSB0")
#define ETHERNET_IP ("192.168.2.5")
#define CLIENT_IP ("192.168.2.102")
#define UDP_PORT (10102)
#define TCP_PORT (10101)

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

#define TCP_CMD_INDEX_SERVO_ON (1001)
#define TCP_CMD_INDEX_RUN (1002)
#define TCP_CMD_INDEX_SETZERO (1003)

typedef struct
{
	char flag;
	char num;
	short checkSum;
	int error;
	char buf[256];
}serialRxObj;

typedef struct
{
	char id;
	char data[8];
}canMsgObj;

typedef struct
{
    char id;
    char data[8];
}sendMsgObj;

typedef struct
{
    int control;
    double row;
    double pitch;
    double height;
    double velocity;
    double acceleration;
}roboClientUdpObj;

typedef struct
{
    int index;
    int subindex;
    double value;
}roboClientTcpObj;

extern std::queue<sendMsgObj> sendMsgQueue;
extern roboClientUdpObj clientData;
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
int tcpServerTask(void);
#endif
