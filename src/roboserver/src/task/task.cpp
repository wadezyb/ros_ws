#include "task.h"
#include <boost/thread/thread.hpp>
#include <stdio.h>
#include "../link/robolink.h"
#include "robot.h"

void task_management_process(void)
{
	startup();
	for(;;)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
//		printf("ID:%d Encoder:%d\n",1,robot.Axis[1].encoder);
//		printf("ID:%d Encoder:%d\n",2,robot.Axis[2].encoder);
//		printf("ID:%d Encoder:%d\n",3,robot.Axis[3].encoder);
//		printf("Control:%d\n",clientData.control);
//		printf("Row:%f\n",clientData.row);
//		printf("Pitch:%f\n",clientData.pitch);
//		printf("Height:%f\n",clientData.height);
	}
}


void startup(void)
{
	printf("System is Starting...\n");

	printf("Initializing Serial Port...\n");
	if(roboLinkInit()>0)
	{
		printf("RoboLink is Ready.\n");
	}
	else
	{
		printf("RoboLink Init Failed.\n");
	}
	boost::thread udp(&udpServerTask);
	printf("UDP Server is Running!\n");
	boost::thread tcp(&tcpServerTask);
	printf("TCP Server is Running!\n");
	boost::thread control(&roboControlLoop);
	printf("Robot Control Loop is Running!!");
}

void debug(void)
{

}
