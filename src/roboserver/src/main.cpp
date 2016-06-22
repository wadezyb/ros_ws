/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "main.h"
#include "task/task.h"
#include <boost/thread/thread.hpp>

int main(int argc, char **argv)
{
	boost::thread test(&task_management_process);
	test.join();

	return 0;
}
