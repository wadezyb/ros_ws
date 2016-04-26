/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <boost/thread/thread.hpp>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "roboserver.h"
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string.h>
#include "robolink.h"
#include "robot.h"
#include "udpserver.h"

using namespace std;

roboServerObj ser;

void ethernet_server_task(void)
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        printf("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = 10101;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
         printf("ERROR on binding");
     listen(sockfd,5);

     while(1)
      {
    	 clilen = sizeof(cli_addr);
    	 newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
         if (newsockfd < 0)
              printf("ERROR on accept");
         bzero(buffer,256);
         n = read(newsockfd,buffer,255);
         printf("%s\n",buffer);

         n = write(newsockfd,"I got your message",18);
         if (n < 0) printf("printf writing to socket");
         close(newsockfd);

     }
     close(sockfd);
}

int main(int argc, char **argv)
{
//	if(roboLinkInit())
//		printf("port opened!!\n");
//	timerInit();
	boost::thread ethernet_server(&udpServerTask);
	//boost::thread receiveTaskNode(&receiveTask);
	ethernet_server.join();
	//receiveTaskNode.join();
	return 0;
}
