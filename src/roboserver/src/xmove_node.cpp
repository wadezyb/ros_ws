#include "ros/ros.h"
#include "robolink.h"
#include <sys/time.h>
#include "motion.h"
#include "delta.h"
#include "imu.h"
#include <ecl/threads.hpp>


// The thread classes
using ecl::Mutex;
using ecl::Thread;
using ecl::Threadable;

// Priorities
using ecl::set_priority;
using ecl::get_priority;
using ecl::print_priority_diagnostics;
using ecl::BackgroundPriority;
using ecl::LowPriority;
using ecl::NormalPriority;
using ecl::HighPriority;
using ecl::CriticalPriority;
using ecl::RealTimePriority1;
using ecl::RealTimePriority2;
using ecl::RealTimePriority3;
using ecl::RealTimePriority4;


void demo_task(void)
{
	int n=0;
	roboLinkInit();
	timerInit();
	servoOn();
	while(sendBufSize()>0);
//	motionTest2();
	for(;;)
	{

		printf("run %d\n",n);
		motionTest(n%7);
		n++;
		sleep(1);
	}
}

int main(int argc, char **argv)
{
	Thread thread1(demo_task);
	//Thread thread2(imu_task);
	for(;;)
	{
		sleep(10);
	}
}
