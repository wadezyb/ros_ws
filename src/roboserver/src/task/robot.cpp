#include "robot.h"
#include <boost/thread/thread.hpp>
robotObj robot;


void roboControlLoop(void)
{
	while(1)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));

	}
}
