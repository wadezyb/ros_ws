#include "robolink.h"
#include "usb2can.h"
#include <signal.h>
#include <sys/time.h>

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

int roboLinkId;
serialRxObj serialRx;
canMsgObj canMsg;
std::queue<canMsgObj> receiveMsgQueue;
std::queue<sendMsgObj> sendMsgQueue;

/*1 500 000 bps = 150 000 Bytes/s = 150 Bytes/ms */

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


int sendBufSize(void)
{
	return sendMsgQueue.size();
}

void receiveData(void)
{
	char buf[200];
	int k = read(roboLinkId,&buf[0],200);
	int i=0;
	char inData;
	for(i=0;i<k;i++)
	{
		if(inData == 0x55)
		{
			serialRx.flag |= 0x01;
		}
		if((serialRx.flag&0x01) == 0x01)
		{
			serialRx.buf[serialRx.num] = inData;
			serialRx.num++;
			if(serialRx.num > serialRx.buf[1]+7)
			{
				for(serialRx.num=1;serialRx.num<=serialRx.buf[1]+5;serialRx.num++)
				{
					serialRx.checkSum+=serialRx.buf[serialRx.num];
				}
				/* Check Sum */
				if(((serialRx.checkSum&0xff)==serialRx.buf[serialRx.buf[1]+6])&&(((serialRx.checkSum&0xff00)>>8)==serialRx.buf[serialRx.buf[1]+7]))
				{
					/* If Check Sum OK, then We append the data to CAN Message Queue */
					canMsg.id=serialRx.buf[5];
					memcpy(&canMsg.data[0],&serialRx.buf[6],8);
					receiveMsgQueue.push(canMsg);
				}
				else
				{
					serialRx.error++;
				}
				serialRx.num = 0;
				serialRx.flag &= ~ 0x01;
				serialRx.checkSum=0;
			}
		}
	}
}

void timerHandler(int signal)
{
	switch(signal)
	{
	case SIGALRM:
		sendData();
		receiveData();
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

