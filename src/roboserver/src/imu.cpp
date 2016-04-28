#include "imu.h"
#include "usb2serial.h"
#include <boost/thread/thread.hpp>
#include "stdio.h"

#define BUF_LENGTH (30)



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

void imu_task(void)
{

	int fd;
	int count = 0;
	char port[] = "/dev/ttyUSB0";
	char r[32];
	char inData;
	int i;
	int k=0;
	serialObj serial;
	imuObject myimu;
	serialObjInit();
	fd = serialPortInit(port,115200);
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
				//printf(",inData is %x\n",inData);
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
							//printf("calc sum is %x\n",serial.sum);
							// printf("get sum is %x\n",serial.buf[BUF_LENGTH]);
							//printf("n is %d\n",serial.n);
							//printf("Total error:%d\n",serial.error);
						  }
						serial.n = 0;
						serial.start = 0;
					  }
				  }
			  }
		  }
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

