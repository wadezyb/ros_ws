#include "robolink.h"
#include "usb2can.h"
#include <signal.h>
#include <sys/time.h>

int roboLinkId;
std::queue<sendMsgObj> sendMsgQueue;

int roboLinkInit(void)
{
	char port[]="/dev/ttyUSB0";
	roboLinkId = serialPortInit(port,1500000);
	return roboLinkId;
}

int sendCANMsg(sendMsgObj msg)
{
	unsigned char buf[16];
    short checkSum=0;
	int i;
	buf[0]=0x55;
	buf[1]=8;
	buf[2]=0x00;
	buf[3]=0x00;
	buf[4]=0x00;
	memcpy(&buf[5],&msg,sizeof(sendMsgObj));
	for(i=1;i<14;i++)
	{
		checkSum+=buf[i];
	}
	memcpy(&buf[14],&checkSum,2);
	return write(roboLinkId,buf,16);
}

void sendCAN(char ID,char Index, int Data)
{
    sendMsgObj msg;
    msg.id = ID;
    msg.data[0]=Index;
    *(int *)(&(msg.data[1]))=Data;
    sendMsgQueue.push(msg);
}

void sendIPM(short dp1, short dp2, short dp3, short dp4)
{
    sendMsgObj msg;
    msg.id=0xaa;
    *(short *)(&(msg.data[0]))=dp1;
    *(short *)(&(msg.data[2]))=dp2;
    *(short *)(&(msg.data[4]))=dp3;
    *(short *)(&(msg.data[6]))=dp4;
    sendMsgQueue.push(msg);
}

/* This Function can be called in a 1ms timer update event */
void sendData(void)
{
	if(!sendMsgQueue.empty())
	{
		sendCANMsg(sendMsgQueue.front());
		sendMsgQueue.pop();
	}
}


void servoOn(void)
{
    sendCAN(1,ModesofOperationIndex, 5);
    sendCAN(2,ModesofOperationIndex, 5);
    sendCAN(3,ModesofOperationIndex, 5);
    sendCAN(1,MaxVelocityIndex,200);
    sendCAN(2,MaxVelocityIndex,200);
    sendCAN(3,MaxVelocityIndex,200);
    sendCAN(1,ControlWordIndex, 1);
    sendCAN(2,ControlWordIndex, 1);
    sendCAN(3,ControlWordIndex, 1);
}

void servoOff(void)
{
    sendCAN(1,ControlWordIndex, 0);
    sendCAN(2,ControlWordIndex, 0);
    sendCAN(3,ControlWordIndex, 0);
}

void timerHandler(int signal)
{
	switch(signal)
	{
	case SIGALRM:
		sendData();
		break;
	default:break;
	}
}
/* Use setitimer function as a high performance timer  */
void timerInit(void)
{
	signal(SIGALRM,timerHandler);
    struct itimerval new_value, old_value;
    new_value.it_value.tv_sec = 0;
    new_value.it_value.tv_usec = 1000;
    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_usec = 1000;
    setitimer(ITIMER_REAL, &new_value, &old_value);
}

int sendBufSize(void)
{
	return sendMsgQueue.size();
}
