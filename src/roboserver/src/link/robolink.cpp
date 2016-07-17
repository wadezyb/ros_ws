/* RoboLink is a Kernel Module in our Robot System */

/* In this file we are doing several things */
/* 1. Communication with RoboMotor using USB2CAN Module with a high resolution timer (1ms) */
/* 2. Establish a RoboServer, which allows RoboClients to connect and read and write some parameters */

#include "robolink.h"
#include "usb2serial.h"
#include "../task/robot.h"
#include <signal.h>
#include <sys/time.h>
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <boost/thread/thread.hpp>
#include "../motion/triangle.h"
#include "../file/file.h"

int roboLinkId;
serialRxObj serialRx;
canMsgObj canMsg;
std::queue<sendMsgObj> sendMsgQueue;
roboClientUdpObj clientData;


/* Init Serial Port */
int roboLinkInit(void)
{
	char port[]=SERIAL_PORT;
	roboLinkId = serialPortInit(port,1500000);
	if(roboLinkId>0)
		timerInit();
	//printf("roboLinkd=%d\n",roboLinkId);
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
	/* Set Interpolation Time to 1ms */
	sendCAN(1,InterpolationTimeIndex, 1);
	sendCAN(2,InterpolationTimeIndex, 1);
	sendCAN(3,InterpolationTimeIndex, 1);

	/* Set Mode of Operation to Interpolation Mode */
	sendCAN(1,ModesofOperationIndex, 5);
	sendCAN(2,ModesofOperationIndex, 5);
	sendCAN(3,ModesofOperationIndex, 5);

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
	sendCAN(1,ModesofOperationIndex, 6);
    sendCAN(2,ModesofOperationIndex, 6);
    sendCAN(3,ModesofOperationIndex, 6);
    sendCAN(1,ControlWordIndex, 1);
    sendCAN(2,ControlWordIndex, 1);
    sendCAN(3,ControlWordIndex, 1);
}

void breakOff(void)
{
	sendCAN(1,IO_OUT_Index, 2);
	sendCAN(2,IO_OUT_Index, 2);
	sendCAN(3,IO_OUT_Index, 2);
}

void breakOn(void)
{
	sendCAN(1,IO_OUT_Index, 0);
	sendCAN(2,IO_OUT_Index, 0);
	sendCAN(3,IO_OUT_Index, 0);
}

void stopMotion(void)
{
	if(!sendMsgQueue.empty())
	{
		//sendCANMsg(sendMsgQueue.front());
		sendMsgQueue.pop();
	}
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
		//printf("hear beat\n");
		/* Watch Dog here! */
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

unsigned int inet_addr(char *str)
{
    int a, b, c, d;
    char arr[4];
    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
    return *(unsigned int *)arr;
}

/*
 * UDP Server Task
 * */
int udpServerTask(void)
{
    struct sockaddr_in si_me, si_other;

    int s, i, slen = sizeof(si_other) , recv_len;
    socklen_t fromlen=sizeof(si_other);
    char buf[100];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(UDP_PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        printf("bind");
    }
    si_other.sin_family = AF_INET;
    si_other.sin_addr.s_addr = inet_addr(CLIENT_IP);
    si_other.sin_port = htons(UDP_PORT);
    //keep listening for data
    while(1)
    {
    	recv_len = recvfrom(s, buf, sizeof(roboClientUdpObj), 0, (struct sockaddr *) &si_other, &fromlen);
    	if(recv_len == sizeof(roboClientUdpObj))
    	{
    		memcpy(&clientData,buf,sizeof(roboClientUdpObj));
    		//printf("%d %d %f\n",recv_len,buf[0],clientData.height);
    	}
    	sendto(s, &robot, sizeof(robotObj), 0, (struct sockaddr*) &si_other, slen);
		//printf("%d\n",recv_len);
		//boost::this_thread::sleep(boost::posix_time::milliseconds(20));
    }
    return 0;
}

int tcpServerTask(void)
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    roboClientTcpObj tcp_msg;
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( TCP_PORT );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    while(1)
    {
		//Accept and incoming connection
		//puts("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);

		//accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0)
		{
			perror("accept failed");
			return 1;
		}
		//puts("Connection accepted");

		//Receive a message from client
		while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
		{
			//Send the message back to client
			if(read_size == sizeof(roboClientTcpObj))
			{
				memcpy(&tcp_msg,client_message,sizeof(roboClientTcpObj));
				switch(tcp_msg.index)
				{
				case TCP_CMD_INDEX_SERVO_ON:
					robot.Controller.control = tcp_msg.value;
					if(robot.Controller.control == 1)
					{
						printf("Servo On!\n");
						servoOn();
					}
					else if(robot.Controller.control == 0)
					{
						printf("Servo Off!\n");
						servoOff();
					}
					break;
				case TCP_CMD_INDEX_RUN:
					robot.Controller.run = tcp_msg.value;
					if(robot.Controller.run == 1)
					{
						printf("Run!\n");
						//triangleMoveTest();
						//fileRun();
						triangleMoveEach();
					}
					else if(TCP_CMD_INDEX_RUN,robot.Controller.run == 0)
					{
						printf("Stop!\n");
					}
					break;
				case TCP_CMD_INDEX_SETZERO:
					printf("Set Zero!\n");
					triZero();
					break;
				case TCP_CMD_INDEX_BREAK:
					robot.Controller.breakon = tcp_msg.value;
					if(robot.Controller.breakon)
						breakOn();
					else
						breakOff();
					break;

				case TCP_CMD_INDEX_DEMO:
					fileRun();
					break;
				default:
					printf("TCP CMD Not Known!!\n");
					break;
				}
				//memcpy(client_message,&tcp_msg,sizeof(roboClientTcpObj));
				write(client_sock , client_message , read_size);
			}
			printf("TCP rx %d\n",read_size);
		}

		if(read_size == 0)
		{
			//puts("Client disconnected");
			fflush(stdout);
		}
		else if(read_size == -1)
		{
			perror("recv failed");
		}
    }
    return 0;
}
