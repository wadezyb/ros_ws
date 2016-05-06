/* RoboLink is a Kernel Module in our Robot System */

/* In this file we are doing several things */
/* 1. Communication with RoboMotor using USB2CAN Module with a high resolution timer (1ms) */
/* 2. Establish a RoboServer, which allows RoboClients to connect and read and write some parameters */

#include "robolink.h"
#include "usb2serial.h"
#include "robot.h"
#include <signal.h>
#include <sys/time.h>
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <boost/thread/thread.hpp>

#define BUFLEN 512  //Max length of buffer
#define PORT 10102   //The port on which to listen for incoming data

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
std::queue<sendMsgObj> sendMsgQueue;

int roboLinkInit(void)
{
	char port[]="/dev/ttyUSB0";
	roboLinkId = serialPortInit(port,1500000);
	if(roboLinkId>0)
		timerInit();
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
    //printf("-%d",msg.data[1]);
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

void sendIPM_Pro(short *dp)
{
    sendMsgObj msg1;
    sendMsgObj msg2;
    sendMsgObj msg3;
    sendMsgObj msg4;

    msg1.id=0xaa;
    msg2.id=0xab;
    msg3.id=0xac;
    msg4.id=0xad;

    memcpy(&msg1.data[0],dp,8);
    memcpy(&msg2.data[0],dp+4,8);
    memcpy(&msg3.data[0],dp+8,8);
    memcpy(&msg4.data[0],dp+12,8);

    sendMsgQueue.push(msg1);
    sendMsgQueue.push(msg2);
    sendMsgQueue.push(msg3);
    sendMsgQueue.push(msg4);
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
    sendCAN(1,ModesofOperationIndex, 4);
    sendCAN(2,ModesofOperationIndex, 4);
    sendCAN(3,ModesofOperationIndex, 4);
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
void servoHome(void)
{
	sendCAN(1,ModesofOperationIndex, 5);
    sendCAN(2,ModesofOperationIndex, 5);
    sendCAN(3,ModesofOperationIndex, 5);
    sendCAN(1,ControlWordIndex, 1);
    sendCAN(2,ControlWordIndex, 1);
    sendCAN(3,ControlWordIndex, 1);
}


int sendBufSize(void)
{
	return sendMsgQueue.size();
}

void updateRxMsg(canMsgObj msg)
{
	char id = msg.id;
	char index = msg.data[0];
	switch(index)
	{
	case 54:
		robot.Axis[id].io_input = msg.data[1];
		//printf("id is %d,",id);
		//printf("io is %d\n",robot.Axis[id].io_input);
		break;
	case HeartBeatIndex:
		robot.Axis[id].encoder = *(int *)(&msg.data[1]);
		robot.Axis[id].temperature = *(char *)(&msg.data[5]);
		break;
	default: break;

	}

}

void receiveData(void)
{
	char buf[200];
	int k = read(roboLinkId,&buf[0],200);
	int i=0;
	//printf("k\n");
	for(i=0;i<k;i++)
	{
		char inData = buf[i];
		//printf("m\n");
		if(inData == 0x55)
		{
			serialRx.flag |= 0x01;
			//printf("head\n");
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
					/* If Check Sum OK, then We update the data to Robot */
					canMsg.id=serialRx.buf[5];
					memcpy(&canMsg.data[0],&serialRx.buf[6],8);
					//printf("%d_%d_%d_%d_%d_%d_%d_%d\n",canMsg.data[0],canMsg.data[1],canMsg.data[2],canMsg.data[3],canMsg.data[4],canMsg.data[5],canMsg.data[6],canMsg.data[7]);
					updateRxMsg(canMsg);
				}
				else
				{
					serialRx.error++;
					printf("checksum error %d\n",serialRx.error);
				}
				serialRx.num = 0;
				serialRx.flag &= ~ 0x01;
				serialRx.checkSum=0;
			}
		}
	}
}

/*
 * Timer Update Interrupt Handler
 * */
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

/*
 * Use setitimer function as a high performance timer(1ms)
 * */
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

int serialPortManagementTask(void)
{
	int a;
	while(1)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		a = roboLinkInit();
		printf("%d\n",a);
	}
}

/*
 * UDP Server Task
 * */
int udpServerTask(void)
{
    struct sockaddr_in si_me, si_other;

    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        printf("bind");
    }

    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            printf("recvfrom()");
        }

        //print details of the client/peer and the data received
        printf("\nReceived %d packet from %s:%d\n",recv_len, inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);

        //now reply the client with the same data
        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            printf("sendto()");
        }
    }

    return 0;
}
