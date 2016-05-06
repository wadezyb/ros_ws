/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "main.h"
#include "motion.h"
#include "robolink.h"

#include "robot.h"
#include "imu.h"

#include <boost/thread/thread.hpp>

roboServerObj ser;
int main(int argc, char **argv)
{
	/* Stage 1: Sensor Actuator and Communication Initialization */
	boost::thread test(&motion_task);
	test.join();
	/* Stage 2: Self Check */

	/* Stage 3:  */
	boost::thread ethernet_server(&udpServerTask);
	ethernet_server.join();
	return 0;
}
