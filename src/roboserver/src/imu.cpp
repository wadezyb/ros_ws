#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <assert.h>
#include <linux/serial.h>
#include "imu.h"

#define BUF_LENGTH (30)
serialObj serial;
/*
 * Baudrate Table
 */
static int rate_to_constant(int baudrate)
{
#define B(x) case x: return B##x
  switch(baudrate)
    {
      B(50); B(75); B(110); B(134); B(150);
      B(200); B(300); B(600); B(1200); B(1800);
      B(2400); B(4800); B(9600); B(19200); B(38400);
      B(57600); B(115200); B(230400); B(460800); B(500000);
      B(576000); B(921600); B(1000000);B(1152000);B(1500000);
    default: return 0;
    }
#undef B
}
/*
 * Serial Port Object Parameters Initialize.
 */
void serialObjInit( void )
{
  serial.start = 0;
  serial.lastInData = 0;
  serial.n = 0;
  serial.sum =(char)(0x88+0xaf);
  serial.error = 0;
}


/*
 * Serial Port Init.
 * Attention: In this function, baud is not used.
 * To set baudrate, chage the B230400 to B115200 or some value else.
 */
int elCommInit(char *portName, int rate)
{
  struct termios options;
  int fd;
  char *ip;
  char *tcpPortNumString;
  long int tcpPortNum;
  int sockfd;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  int rv;
  int speed =0;
  if (*portName == '/') { // linux serial port names always begin with /dev
    printf("Opening serial port %s\n", portName);
    //
    fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1){
      //Could not open the port.
      //perror("init(): Unable to open serial port - ");
    }
    else
      {
        speed = rate_to_constant(rate);
        fcntl(fd, F_SETFL, FNDELAY);
        // Sets the read() function to return NOW and not wait for data to
        //enter buffer if there isn't anything there.
        //Configure port for 8N1 transmission
        tcgetattr(fd, &options); //Gets the current options for the port
        cfsetispeed(&options, speed ?: B38400); //Sets the Input Baud Rate
        cfsetospeed(&options, speed ?: B38400); //Sets the Output Baud Rate
        options.c_cflag |= (CLOCAL | CREAD);
        //? all these set options for 8N1 serial operations
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        options.c_cflag &= ~CRTSCTS;
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // set raw mode
        options.c_iflag &= ~(IXON | IXOFF | IXANY); // disable SW flow control
        options.c_iflag&=~(INLCR|ICRNL);
        options.c_oflag &= ~OPOST;
        options.c_oflag&=~(ONLCR|OCRNL);
        tcsetattr(fd, TCSANOW, &options);//Set the new options for the port"NOW"
      }
    return fd;
  }
  return -1;
}


void imu_task(void)
{

	int fd;
	int count = 0;
	char port[] = "/dev/ttyUSB1";
	char r[32];
	char inData;
	int i;
	int k=0;
	imuObject myimu;
	serialObjInit();
	fd = elCommInit(port,115200);
	if(fd<0)
		return;
	for(;;)
	{
		k = read(fd,&r[0],sizeof(r));
		//printf("k is %d\n",k);
		if(k>0)
		  {
			//r[k]='\0';
			// printf("rk is %x\n",r[k]);
			for(i=0;i<k;i++)
			  {
				inData = r[i];
				//printf("i is %d",i);
				// printf(",inData is %x\n",inData);
				if( ((inData&0xff) == 0xaf)&&((serial.lastInData&0xff) == 0x88) )
				  {
					serial.start |= 0x01;
					serial.sum = (char)(0xaf+0x88);
				  }
				serial.lastInData = inData;
				if( serial.start != 0 )
				  {
					serial.buf[serial.n]=inData&0xff;
					serial.n++;
					//printf("here %d\n",serial.buf[serial.n]);
					if( serial.n >BUF_LENGTH )
					  {
						for(serial.n=1;serial.n<BUF_LENGTH;serial.n++)
						  {
							serial.sum += serial.buf[serial.n];
	//                            printf("n is %d",serial.n);
	//                            printf(",buf is %x",serial.buf[serial.n]);
	//                            printf(",sum = %x\n",serial.sum);
						  }
	//                        printf("calc sum is %d\n",serial.sum);
	//                        printf("get sum is %d\n",serial.buf[BUF_LENGTH]);
	//                        printf("n is %d\n",serial.n);
						if( serial.sum == serial.buf[BUF_LENGTH] )
						  {
							//printf("checksum ok\n");
							memcpy(&myimu,&serial.buf[1],sizeof(myimu));
	                        printf("%f %f %f\n",myimu.angle.x*0.01,myimu.angle.y*0.01,myimu.angle.z*0.1);
						  }
						else
						  {
							serial.error++;
							// printf("calc sum is %x\n",serial.sum);
							// printf("get sum is %x\n",serial.buf[BUF_LENGTH]);
							// printf("n is %d\n",serial.n);
							printf("Total error:%d\n",serial.error);
						  }
						serial.n = 0;
						serial.start = 0;
					  }
				  }
			  }
		  }
		usleep(1000);
	}
	return;
}

